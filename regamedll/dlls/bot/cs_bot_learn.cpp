#include "precompiled.h"

const float updateTimesliceDuration = 0.5f;

int _navAreaCount = 0;
int _currentIndex = 0;

inline CNavNode *LadderEndSearch(CBaseEntity *entity, const Vector *pos, NavDirType mountDir)
{
	Vector center = *pos;
	AddDirectionVector(&center, mountDir, HalfHumanWidth);

	// Test the ladder dismount point first, then each cardinal direction one and two steps away
	for (int d = (-1); d < 2 * NUM_DIRECTIONS; ++d)
	{
		Vector tryPos = center;

		if (d >= NUM_DIRECTIONS)
			AddDirectionVector(&tryPos, (NavDirType)(d - NUM_DIRECTIONS), GenerationStepSize * 2.0f);
		else if (d >= 0)
			AddDirectionVector(&tryPos, (NavDirType)d, GenerationStepSize);

		// step up a rung, to ensure adjacent floors are below us
		tryPos.z += GenerationStepSize;
		SnapToGrid(&tryPos);

		// adjust height to account for sloping areas
		Vector tryNormal;
		if (GetGroundHeight(&tryPos, &tryPos.z, &tryNormal) == false)
			continue;

		// make sure this point is not on the other side of a wall
		const float fudge = 2.0f;
		TraceResult result;
		UTIL_TraceLine(center + Vector(0, 0, fudge), tryPos + Vector(0, 0, fudge), ignore_monsters, dont_ignore_glass, ENT(entity->pev), &result);

		if (result.flFraction != 1.0f
#ifdef REGAMEDLL_FIXES
			|| result.fStartSolid
#endif
		)
			continue;

		// if no node exists here, create one and continue the search
		if (CNavNode::GetNode(&tryPos) == NULL)
		{
			return new CNavNode(&tryPos, &tryNormal, NULL);
		}
	}

	return NULL;
}

CNavNode *CCSBot::AddNode(const Vector *destPos, const Vector *normal, NavDirType dir, CNavNode *source)
{
	// check if a node exists at this location
	CNavNode *node = const_cast<CNavNode *>(CNavNode::GetNode(destPos));

	// if no node exists, create one
	bool useNew = false;
	if (node == NULL)
	{
		node = new CNavNode(destPos, normal, source);
		useNew = true;
	}

	// connect source node to new node
	source->ConnectTo(node, dir);

	// optimization: if deltaZ changes very little, assume connection is commutative
	const float zTolerance = 10.0f; // 50.0f;
	if (Q_fabs(source->GetPosition()->z - destPos->z) < zTolerance)
	{
		node->ConnectTo(source, OppositeDirection(dir));
		node->MarkAsVisited(OppositeDirection(dir));
	}

	if (useNew)
	{
		// new node becomes current node
		m_currentNode = node;
	}

	Vector ceiling;
	Vector floor;
	TraceResult result;

	bool crouch = false;
	const float epsilon = 0.1f;

	for (float y = -16.0f; y <= 16.0f + epsilon; y += 16.0f)
	{
		for (float x = -16.0f; x <= 16.0f + epsilon; x += 16.0f)
		{
			floor = *destPos + Vector(x, y, 5.0f);
			ceiling = *destPos + Vector(x, y, 72.0f - epsilon);

			UTIL_TraceLine(floor, ceiling, ignore_monsters, dont_ignore_glass, ENT(pev), &result);

			if (result.flFraction != 1.0f)
			{
				crouch = true;
				break;
			}
		}

		if (crouch)
		{
			node->SetAttributes(NAV_CROUCH);
			break;

		}
	}

	return node;
}

void drawProgressMeter(float progress, char *title)
{
	MESSAGE_BEGIN(MSG_ALL, gmsgBotProgress);
		WRITE_BYTE(FLAG_PROGRESS_DRAW);
		WRITE_BYTE(int(progress * 100.0f));
		WRITE_STRING(title);
	MESSAGE_END();
}

void startProgressMeter(const char *title)
{
	MESSAGE_BEGIN(MSG_ALL, gmsgBotProgress);
		WRITE_BYTE(FLAG_PROGRESS_START);
		WRITE_STRING(title);
	MESSAGE_END();
}

void hideProgressMeter()
{
	MESSAGE_BEGIN(MSG_ALL, gmsgBotProgress);
		WRITE_BYTE(FLAG_PROGRESS_HIDE);
	MESSAGE_END();
}

void CCSBot::StartLearnProcess()
{
	startProgressMeter("#CZero_LearningMap");
	drawProgressMeter(0, "#CZero_LearningMap");
	BuildLadders();

	Vector normal;
	Vector pos = pev->origin;

	SnapToGrid(&pos.x);
	SnapToGrid(&pos.y);

	if (!GetGroundHeight(&pos, &pos.z, &normal))
	{
		CONSOLE_ECHO("ERROR: Start position invalid\n\n");
		m_processMode = PROCESS_NORMAL;
		return;
	}

	m_currentNode = new CNavNode(&pos, &normal);
	m_goalPosition = pev->origin;
	m_processMode = PROCESS_LEARN;
}

// Search the world and build a map of possible movements.
// The algorithm begins at the bot's current location, and does a recursive search
// outwards, tracking all valid steps and generating a directed graph of CNavNodes.
// Sample the map one "step" in a cardinal direction to learn the map.
// Returns true if sampling needs to continue, or false if done.
bool CCSBot::LearnStep()
{
	// take a step
	while (true)
	{
		if (m_currentNode == NULL)
		{
			// search is exhausted - continue search from ends of ladders
			NavLadderList::iterator iter;
			for (iter = TheNavLadderList.begin(); iter != TheNavLadderList.end(); ++iter)
			{
				CNavLadder *ladder = (*iter);

				// check ladder bottom
				if ((m_currentNode = LadderEndSearch(ladder->m_entity, &ladder->m_bottom, ladder->m_dir)) != 0)
					break;

				// check ladder top
				if ((m_currentNode = LadderEndSearch(ladder->m_entity, &ladder->m_top, ladder->m_dir)) != 0)
					break;
			}

			if (m_currentNode == NULL)
			{
				// all seeds exhausted, sampling complete
				GenerateNavigationAreaMesh();
				return false;
			}
		}

		// Take a step from this node
		for (int dir = NORTH; dir < NUM_DIRECTIONS; dir++)
		{
			if (!m_currentNode->HasVisited((NavDirType)dir))
			{
				float feetOffset = pev->origin.z - GetFeetZ();

				// start at current node position
				Vector pos = *m_currentNode->GetPosition();

				// snap to grid
				int cx = SnapToGrid(pos.x);
				int cy = SnapToGrid(pos.y);

				// attempt to move to adjacent node
				switch (dir)
				{
					case NORTH:		cy -= GenerationStepSize; break;
					case SOUTH:		cy += GenerationStepSize; break;
					case EAST:		cx += GenerationStepSize; break;
					case WEST:		cx -= GenerationStepSize; break;
				}

				pos.x = cx;
				pos.y = cy;

				m_generationDir = (NavDirType)dir;

				// mark direction as visited
				m_currentNode->MarkAsVisited(m_generationDir);

				// test if we can move to new position
				TraceResult result;
				Vector from, to;

				// modify position to account for change in ground level during step
				to.x = pos.x;
				to.y = pos.y;
				Vector toNormal;
				if (GetGroundHeight(&pos, &to.z, &toNormal) == false)
				{
					return true;
				}

				from = *m_currentNode->GetPosition();

				Vector fromOrigin = from + Vector(0, 0, feetOffset);
				Vector toOrigin = to + Vector(0, 0, feetOffset);

				UTIL_SetOrigin(pev, toOrigin);
				UTIL_TraceLine(fromOrigin, toOrigin, ignore_monsters, dont_ignore_glass, ENT(pev), &result);

				bool walkable;

				if (result.flFraction == 1.0f && !result.fStartSolid)
				{
					// the trace didnt hit anything - clear
					float toGround = to.z;
					float fromGround = from.z;

					float epsilon = 0.1f;

					// check if ledge is too high to reach or will cause us to fall to our death
					if (toGround - fromGround > JumpCrouchHeight + epsilon || fromGround - toGround > DeathDrop)
					{
						walkable = false;
					}
					else
					{
						// check surface normals along this step to see if we would cross any impassable slopes
						Vector delta = to - from;
						const float inc = 2.0f;
						float along = inc;
						bool done = false;
						float ground;
						Vector normal;

						walkable = true;

						while (!done)
						{
							Vector p;

							// need to guarantee that we test the exact edges
							if (along >= GenerationStepSize)
							{
								p = to;
								done = true;
							}
							else
							{
								p = from + delta * (along / GenerationStepSize);
							}

							if (GetGroundHeight(&p, &ground, &normal) == false)
							{
								walkable = false;
								break;
							}

							// check for maximum allowed slope
							if (normal.z < 0.7f)
							{
								walkable = false;
								break;
							}

							along += inc;
						}
					}
				}
				// TraceLine hit something...
				else
				{
					if (IsEntityWalkable(VARS(result.pHit), WALK_THRU_EVERYTHING))
					{
						walkable = true;
					}
					else
					{
						walkable = false;
					}
				}
#ifdef REGAMEDLL_FIXES
				// if we're incrementally generating, don't overlap existing nav areas
				CNavArea *overlap = TheNavAreaGrid.GetNavArea(&to, HumanHeight);
				if (overlap != NULL)
				{
					walkable = false;
				}
#endif
				if (walkable)
				{
					// we can move here
					// create a new navigation node, and update current node pointer
					CNavNode *newNode = AddNode(&to, &toNormal, m_generationDir, m_currentNode);
				}

				return true;
			}
		}

		// all directions have been searched from this node - pop back to its parent and continue
		m_currentNode = m_currentNode->GetParent();
	}
}

void CCSBot::UpdateLearnProcess()
{
	float startTime = g_engfuncs.pfnTime();
	while (g_engfuncs.pfnTime() - startTime < updateTimesliceDuration)
	{
		if (LearnStep() == false)
		{
			StartAnalyzeAlphaProcess();
			return;
		}
	}
}

void CCSBot::StartAnalyzeAlphaProcess()
{
	m_processMode = PROCESS_ANALYZE_ALPHA;
	m_analyzeIter = TheNavAreaList.begin();

	_navAreaCount = TheNavAreaList.size();
	_currentIndex = 0;

	ApproachAreaAnalysisPrep();
	DestroyHidingSpots();

	startProgressMeter("#CZero_AnalyzingHidingSpots");
	drawProgressMeter(0, "#CZero_AnalyzingHidingSpots");
}

bool CCSBot::AnalyzeAlphaStep()
{
	++_currentIndex;
	if (m_analyzeIter == TheNavAreaList.end())
		return false;

	CNavArea *area = (*m_analyzeIter);
	area->ComputeHidingSpots();
	area->ComputeApproachAreas();
	++m_analyzeIter;

	return true;
}

void CCSBot::UpdateAnalyzeAlphaProcess()
{
	float startTime = g_engfuncs.pfnTime();
	while (g_engfuncs.pfnTime() - startTime < updateTimesliceDuration)
	{
		if (AnalyzeAlphaStep() == false)
		{
			drawProgressMeter(0.5f, "#CZero_AnalyzingHidingSpots");
			CleanupApproachAreaAnalysisPrep();
			StartAnalyzeBetaProcess();
			return;
		}
	}

	float progress = (double(_currentIndex) / double(_navAreaCount)) * 0.5f;
	drawProgressMeter(progress, "#CZero_AnalyzingHidingSpots");
}

void CCSBot::StartAnalyzeBetaProcess()
{
	m_processMode = PROCESS_ANALYZE_BETA;
	m_analyzeIter = TheNavAreaList.begin();

	_navAreaCount = TheNavAreaList.size();
	_currentIndex = 0;
}

bool CCSBot::AnalyzeBetaStep()
{
	++_currentIndex;
	if (m_analyzeIter == TheNavAreaList.end())
		return false;

	CNavArea *area = (*m_analyzeIter);
	area->ComputeSpotEncounters();
	area->ComputeSniperSpots();
	++m_analyzeIter;

	return true;
}

void CCSBot::UpdateAnalyzeBetaProcess()
{
	float startTime = g_engfuncs.pfnTime();
	while (g_engfuncs.pfnTime() - startTime < updateTimesliceDuration)
	{
		if (AnalyzeBetaStep() == false)
		{
			drawProgressMeter(1, "#CZero_AnalyzingApproachPoints");
			StartSaveProcess();
			return;
		}
	}
	
	float progress = (double(_currentIndex) / double(_navAreaCount) + 1.0f) * 0.5f;
	drawProgressMeter(progress, "#CZero_AnalyzingApproachPoints");
}

void CCSBot::StartSaveProcess()
{
	m_processMode = PROCESS_SAVE;
}

void CCSBot::UpdateSaveProcess()
{
	char filename[256];
	char msg[256];
	char cmd[128];

	GET_GAME_DIR(filename);

	Q_strcat(filename, "\\");
	Q_strcat(filename, TheBots->GetNavMapFilename());

	HintMessageToAllPlayers("Saving...");
	SaveNavigationMap(filename);

	Q_sprintf(msg, "Navigation file '%s' saved.", filename);
	HintMessageToAllPlayers(msg);

	hideProgressMeter();
	StartNormalProcess();

#ifndef REGAMEDLL_FIXES
	Q_sprintf(cmd, "map %s\n", STRING(gpGlobals->mapname));
#else
	Q_sprintf(cmd, "changelevel %s\n", STRING(gpGlobals->mapname));
#endif

	SERVER_COMMAND(cmd);
}

void CCSBot::StartNormalProcess()
{
	m_processMode = PROCESS_NORMAL;
}

/*
*
*   This program is free software; you can redistribute it and/or modify it
*   under the terms of the GNU General Public License as published by the
*   Free Software Foundation; either version 2 of the License, or (at
*   your option) any later version.
*
*   This program is distributed in the hope that it will be useful, but
*   WITHOUT ANY WARRANTY; without even the implied warranty of
*   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
*   General Public License for more details.
*
*   You should have received a copy of the GNU General Public License
*   along with this program; if not, write to the Free Software Foundation,
*   Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
*
*   In addition, as a special exception, the author gives permission to
*   link the code of this program with the Half-Life Game Engine ("HL
*   Engine") and Modified Game Libraries ("MODs") developed by Valve,
*   L.L.C ("Valve").  You must obey the GNU General Public License in all
*   respects for all of the code used other than the HL Engine and MODs
*   from Valve.  If you modify this file, you may extend this exception
*   to your version of the file, but you are not obligated to do so.  If
*   you do not wish to do so, delete this exception statement from your
*   version.
*
*/

#include "precompiled.h"

// Determine actual path positions bot will move between along the path
bool CCSBot::ComputePathPositions()
{
	if (m_pathLength == 0)
		return false;

	// start in first area's center
	m_path[0].pos = *m_path[0].area->GetCenter();
	m_path[0].ladder = nullptr;
	m_path[0].how = NUM_TRAVERSE_TYPES;

	for (int i = 1; i < m_pathLength; i++)
	{
		const ConnectInfo *from = &m_path[i - 1];
		ConnectInfo *to = &m_path[i];

		// walk along the floor to the next area
		if (to->how <= GO_WEST)
		{
			to->ladder = nullptr;

			// compute next point, keeping path as straight as possible
			from->area->ComputeClosestPointInPortal(to->area, (NavDirType)to->how, &from->pos, &to->pos);

			// move goal position into the goal area a bit
			// how far to "step into" an area - must be less than min area size
			const float stepInDist = 5.0f;
			AddDirectionVector(&to->pos, (NavDirType)to->how, stepInDist);

			// we need to walk out of "from" area, so keep Z where we can reach it
			to->pos.z = from->area->GetZ(&to->pos);

			// if this is a "jump down" connection, we must insert an additional point on the path
			if (to->area->IsConnected(from->area, NUM_DIRECTIONS) == false)
			{
				// this is a "jump down" link
				// compute direction of path just prior to "jump down"
				Vector2D dir;
				DirectionToVector2D((NavDirType)to->how, &dir);

				// shift top of "jump down" out a bit to "get over the ledge"
				const float pushDist = 25.0f; // 75.0f;
				to->pos.x += pushDist * dir.x;
				to->pos.y += pushDist * dir.y;

				// insert a duplicate node to represent the bottom of the fall
				if (m_pathLength < MAX_PATH_LENGTH - 1)
				{
					// copy nodes down
					for (int j = m_pathLength; j > i; j--)
						m_path[j] = m_path[j - 1];

					// path is one node longer
					m_pathLength++;

					// move index ahead into the new node we just duplicated
					i++;

					m_path[i].pos.x = to->pos.x + pushDist * dir.x;
					m_path[i].pos.y = to->pos.y + pushDist * dir.y;

					// put this one at the bottom of the fall
					m_path[i].pos.z = to->area->GetZ(&m_path[i].pos);
				}
			}
		}
		// to get to next area, must go up a ladder
		else if (to->how == GO_LADDER_UP)
		{
			// find our ladder
			const NavLadderList *list = from->area->GetLadderList(LADDER_UP);
			NavLadderList::const_iterator iter;
			for (iter = list->begin(); iter != list->end(); iter++)
			{
				CNavLadder *ladder = (*iter);

				// can't use "behind" area when ascending...
				if (ladder->m_topForwardArea == to->area || ladder->m_topLeftArea == to->area || ladder->m_topRightArea == to->area)
				{
					to->ladder = ladder;
					to->pos = ladder->m_bottom;
					AddDirectionVector(&to->pos, ladder->m_dir, HalfHumanWidth * 2.0f);
					break;
				}
			}

			if (iter == list->end())
			{
				PrintIfWatched("ERROR: Can't find ladder in path\n");
				return false;
			}
		}
		// to get to next area, must go down a ladder
		else if (to->how == GO_LADDER_DOWN)
		{
			// find our ladder
			const NavLadderList *list = from->area->GetLadderList(LADDER_DOWN);
			NavLadderList::const_iterator iter;
			for (iter = list->begin(); iter != list->end(); iter++)
			{
				CNavLadder *ladder = (*iter);

				if (ladder->m_bottomArea == to->area)
				{
					to->ladder = ladder;
					to->pos = ladder->m_top;
					AddDirectionVector(&to->pos, OppositeDirection(ladder->m_dir), HalfHumanWidth * 2.0f);
					break;
				}
			}

			if (iter == list->end())
			{
				PrintIfWatched("ERROR: Can't find ladder in path\n");
				return false;
			}
		}
	}

	return true;
}

// If next step of path uses a ladder, prepare to traverse it
void CCSBot::SetupLadderMovement()
{
	if (m_pathIndex < 1 || m_pathLength == 0)
		return;

	const ConnectInfo *to = &m_path[m_pathIndex];

	if (to->ladder)
	{
		m_spotEncounter = nullptr;
		m_areaEnteredTimestamp = gpGlobals->time;

		m_pathLadder = to->ladder;
		m_pathLadderTimestamp = gpGlobals->time;

		// to get to next area, we must traverse a ladder
		if (to->how == GO_LADDER_UP)
		{
			m_pathLadderState = APPROACH_ASCENDING_LADDER;
			m_pathLadderFaceIn = true;
			PrintIfWatched("APPROACH_ASCENDING_LADDER\n");
			m_goalPosition = m_pathLadder->m_bottom;

			AddDirectionVector(&m_goalPosition, m_pathLadder->m_dir, HalfHumanWidth * 2.0f);
			m_lookAheadAngle = DirectionToAngle(OppositeDirection(m_pathLadder->m_dir));
		}
		else
		{
			// try to mount ladder "face out" first
			m_goalPosition = m_pathLadder->m_top;
			AddDirectionVector(&m_goalPosition, OppositeDirection(m_pathLadder->m_dir), HalfHumanWidth * 2.0f);

			TraceResult result;
			Vector from = m_pathLadder->m_top;
			Vector to = m_goalPosition;

			UTIL_TraceLine(from, to, ignore_monsters, ENT(m_pathLadder->m_entity->pev), &result);

			if (result.flFraction == 1.0f)
			{
				PrintIfWatched("APPROACH_DESCENDING_LADDER (face out)\n");

				m_pathLadderState = APPROACH_DESCENDING_LADDER;
				m_pathLadderFaceIn = false;
				m_lookAheadAngle = DirectionToAngle(m_pathLadder->m_dir);
			}
			else
			{
				PrintIfWatched("APPROACH_DESCENDING_LADDER (face in)\n");
				m_pathLadderState = APPROACH_DESCENDING_LADDER;
				m_pathLadderFaceIn = true;
				m_lookAheadAngle = DirectionToAngle(OppositeDirection(m_pathLadder->m_dir));
				m_goalPosition = m_pathLadder->m_top;
				AddDirectionVector(&m_goalPosition, m_pathLadder->m_dir, HalfHumanWidth);
			}
		}
	}
}

// TODO: What about ladders whose top AND bottom are messed up?
void CCSBot::ComputeLadderEndpoint(bool isAscending)
{
	TraceResult result;
	Vector from, to;

	if (isAscending)
	{
		// find actual top in case m_pathLadder penetrates the ceiling
		// trace from our chest height at m_pathLadder base
		from = m_pathLadder->m_bottom;
		from.z = pev->origin.z;
		to = m_pathLadder->m_top;
	}
	else
	{
		// find actual bottom in case m_pathLadder penetrates the floor
		// trace from our chest height at m_pathLadder top
		from = m_pathLadder->m_top;
		from.z = pev->origin.z;
		to = m_pathLadder->m_bottom;
	}

	UTIL_TraceLine(from, to, ignore_monsters, ENT(m_pathLadder->m_entity->pev), &result);

	if (result.flFraction == 1.0f)
		m_pathLadderEnd = to.z;
	else
		m_pathLadderEnd = from.z + result.flFraction * (to.z - from.z);
}

// Navigate our current ladder. Return true if we are doing ladder navigation.
// TODO: Need Push() and Pop() for run/walk context to keep ladder speed contained.
bool CCSBot::UpdateLadderMovement()
{
	if (!m_pathLadder)
		return false;

	bool giveUp = false;

	// check for timeout
	const float ladderTimeoutDuration = 10.0f;
	if (gpGlobals->time - m_pathLadderTimestamp > ladderTimeoutDuration)
	{
		PrintIfWatched("Ladder timeout!\n");
		giveUp = true;
	}

	else if (m_pathLadderState == APPROACH_ASCENDING_LADDER
		|| m_pathLadderState == APPROACH_DESCENDING_LADDER
		|| m_pathLadderState == ASCEND_LADDER
		|| m_pathLadderState == DESCEND_LADDER
		|| m_pathLadderState == DISMOUNT_ASCENDING_LADDER
		|| m_pathLadderState == MOVE_TO_DESTINATION)
	{
		if (m_isStuck)
		{
			PrintIfWatched("Giving up ladder - stuck\n");
			giveUp = true;
		}
	}

	if (giveUp)
	{
		// jump off ladder and give up
		Jump(MUST_JUMP);
		Wiggle();
		ResetStuckMonitor();
		DestroyPath();
		Run();
		return false;
	}

	ResetStuckMonitor();

	// check if somehow we totally missed the ladder
	switch (m_pathLadderState)
	{
	case MOUNT_ASCENDING_LADDER:
	case MOUNT_DESCENDING_LADDER:
	case ASCEND_LADDER:
	case DESCEND_LADDER:
	{
		const float farAway = 200.0f;
		Vector2D d = (m_pathLadder->m_top - pev->origin).Make2D();
		if (d.IsLengthGreaterThan(farAway))
		{
			PrintIfWatched("Missed ladder\n");
			Jump(MUST_JUMP);
			DestroyPath();
			Run();
			return false;
		}
		break;
	}
	}

	m_areaEnteredTimestamp = gpGlobals->time;

	const float tolerance = 10.0f;
	const float closeToGoal = 25.0f;

	switch (m_pathLadderState)
	{
	case APPROACH_ASCENDING_LADDER:
	{
		bool approached = false;
		Vector2D d(pev->origin.x - m_goalPosition.x, pev->origin.y - m_goalPosition.y);

		if (d.x * m_pathLadder->m_dirVector.x + d.y * m_pathLadder->m_dirVector.y < 0.0f)
		{
			Vector2D perp(-m_pathLadder->m_dirVector.y, m_pathLadder->m_dirVector.x);

#ifdef REGAMEDLL_FIXES
			if (Q_abs(d.x * perp.x + d.y * perp.y) < tolerance && d.Length() < closeToGoal)
#else
			if (Q_abs(int64(d.x * perp.x + d.y * perp.y)) < tolerance && d.Length() < closeToGoal)
#endif
				approached = true;
		}

		// small radius will just slow them down a little for more accuracy in hitting their spot
		const float walkRange = 50.0f;
		if (d.IsLengthLessThan(walkRange))
		{
			Walk();
			StandUp();
		}

		// TODO: Check that we are on the ladder we think we are
		if (IsOnLadder())
		{
			m_pathLadderState = ASCEND_LADDER;
			PrintIfWatched("ASCEND_LADDER\n");

			// find actual top in case m_pathLadder penetrates the ceiling
			ComputeLadderEndpoint(true);
		}
		else if (approached)
		{
			// face the m_pathLadder
			m_pathLadderState = FACE_ASCENDING_LADDER;
			PrintIfWatched("FACE_ASCENDING_LADDER\n");
		}
		else
		{
			// move toward ladder mount point
			MoveTowardsPosition(&m_goalPosition);
		}
		break;
	}
	case APPROACH_DESCENDING_LADDER:
	{
		// fall check
		if (GetFeetZ() <= m_pathLadder->m_bottom.z + HalfHumanHeight)
		{
			PrintIfWatched("Fell from ladder.\n");

			m_pathLadderState = MOVE_TO_DESTINATION;
			m_path[m_pathIndex].area->GetClosestPointOnArea(&m_pathLadder->m_bottom, &m_goalPosition);

			AddDirectionVector(&m_goalPosition, m_pathLadder->m_dir, HalfHumanWidth);
			PrintIfWatched("MOVE_TO_DESTINATION\n");
		}
		else
		{
			bool approached = false;
			Vector2D d(pev->origin.x - m_goalPosition.x, pev->origin.y - m_goalPosition.y);

			if (d.x * m_pathLadder->m_dirVector.x + d.y * m_pathLadder->m_dirVector.y > 0.0f)
			{
				Vector2D perp(-m_pathLadder->m_dirVector.y, m_pathLadder->m_dirVector.x);

				if (Q_abs(int64(d.x * perp.x + d.y * perp.y)) < tolerance && d.Length() < closeToGoal)
					approached = true;
			}

			// if approaching ladder from the side or "ahead", walk
			if (m_pathLadder->m_topBehindArea != m_lastKnownArea)
			{
				const float walkRange = 150.0f;
				if (!IsCrouching() && d.IsLengthLessThan(walkRange))
					Walk();
			}

			// TODO: Check that we are on the ladder we think we are
			if (IsOnLadder())
			{
				// we slipped onto the ladder - climb it
				m_pathLadderState = DESCEND_LADDER;
				Run();
				PrintIfWatched("DESCEND_LADDER\n");

				// find actual bottom in case m_pathLadder penetrates the floor
				ComputeLadderEndpoint(false);
			}
			else if (approached)
			{
				// face the ladder
				m_pathLadderState = FACE_DESCENDING_LADDER;
				PrintIfWatched("FACE_DESCENDING_LADDER\n");
			}
			else
			{
				// move toward ladder mount point
				MoveTowardsPosition(&m_goalPosition);
			}
		}
		break;
	}
	case FACE_ASCENDING_LADDER:
	{
		// find yaw to directly aim at ladder
		Vector to = m_pathLadder->m_bottom - pev->origin;
		Vector idealAngle = UTIL_VecToAngles(to);

		const float angleTolerance = 5.0f;
		if (AnglesAreEqual(pev->v_angle.y, idealAngle.y, angleTolerance))
		{
			// move toward ladder until we become "on" it
			Run();
			ResetStuckMonitor();
			m_pathLadderState = MOUNT_ASCENDING_LADDER;
			PrintIfWatched("MOUNT_ASCENDING_LADDER\n");
		}
		break;
	}
	case FACE_DESCENDING_LADDER:
	{
		// find yaw to directly aim at ladder
		Vector to = m_pathLadder->m_top - pev->origin;
		Vector idealAngle = UTIL_VecToAngles(to);

		const float angleTolerance = 5.0f;
		if (AnglesAreEqual(pev->v_angle.y, idealAngle.y, angleTolerance))
		{
			// move toward ladder until we become "on" it
			m_pathLadderState = MOUNT_DESCENDING_LADDER;
			ResetStuckMonitor();
			PrintIfWatched("MOUNT_DESCENDING_LADDER\n");
		}
		break;
	}
	case MOUNT_ASCENDING_LADDER:
	{
		if (IsOnLadder())
		{
			m_pathLadderState = ASCEND_LADDER;
			PrintIfWatched("ASCEND_LADDER\n");

			// find actual top in case m_pathLadder penetrates the ceiling
			ComputeLadderEndpoint(true);
		}

		MoveForward();
		break;
	}
	case MOUNT_DESCENDING_LADDER:
	{
		// fall check
		if (GetFeetZ() <= m_pathLadder->m_bottom.z + HalfHumanHeight)
		{
			PrintIfWatched("Fell from ladder.\n");

			m_pathLadderState = MOVE_TO_DESTINATION;
			m_path[m_pathIndex].area->GetClosestPointOnArea(&m_pathLadder->m_bottom, &m_goalPosition);

			AddDirectionVector(&m_goalPosition, m_pathLadder->m_dir, HalfHumanWidth);
			PrintIfWatched("MOVE_TO_DESTINATION\n");
		}
		else
		{
			if (IsOnLadder())
			{
				m_pathLadderState = DESCEND_LADDER;
				PrintIfWatched("DESCEND_LADDER\n");

				// find actual bottom in case m_pathLadder penetrates the floor
				ComputeLadderEndpoint(false);
			}

			// move toward ladder mount point
			MoveForward();
		}
		break;
	}
	case ASCEND_LADDER:
	{
		// run, so we can make our dismount jump to the side, if necessary
		Run();

		// if our destination area requires us to crouch, do it
		if (m_path[m_pathIndex].area->GetAttributes() & NAV_CROUCH)
			Crouch();

		// did we reach the top?
		if (GetFeetZ() >= m_pathLadderEnd)
		{
			// we reached the top - dismount
			m_pathLadderState = DISMOUNT_ASCENDING_LADDER;
			PrintIfWatched("DISMOUNT_ASCENDING_LADDER\n");

			if (m_path[m_pathIndex].area == m_pathLadder->m_topForwardArea)
				m_pathLadderDismountDir = FORWARD;
			else if (m_path[m_pathIndex].area == m_pathLadder->m_topLeftArea)
				m_pathLadderDismountDir = LEFT;
			else if (m_path[m_pathIndex].area == m_pathLadder->m_topRightArea)
				m_pathLadderDismountDir = RIGHT;

			m_pathLadderDismountTimestamp = gpGlobals->time;
		}
		else if (!IsOnLadder())
		{
			// we fall off the ladder, repath
			DestroyPath();
			return false;
		}

		// move up ladder
		MoveForward();
		break;
	}
	case DESCEND_LADDER:
	{
		Run();

		float destHeight = m_pathLadderEnd + HalfHumanHeight;
		if (!IsOnLadder() || GetFeetZ() <= destHeight)
		{
			// we reached the bottom, or we fell off - dismount
			m_pathLadderState = MOVE_TO_DESTINATION;
			m_path[m_pathIndex].area->GetClosestPointOnArea(&m_pathLadder->m_bottom, &m_goalPosition);

			AddDirectionVector(&m_goalPosition, m_pathLadder->m_dir, HalfHumanWidth);
			PrintIfWatched("MOVE_TO_DESTINATION\n");
		}

		// Move down ladder
		MoveForward();
		break;
	}
	case DISMOUNT_ASCENDING_LADDER:
	{
		if (gpGlobals->time - m_pathLadderDismountTimestamp >= 0.4f)
		{
			m_pathLadderState = MOVE_TO_DESTINATION;
			m_path[m_pathIndex].area->GetClosestPointOnArea(&pev->origin, &m_goalPosition);
			PrintIfWatched("MOVE_TO_DESTINATION\n");
		}

		// We should already be facing the dismount point
		if (m_pathLadderFaceIn)
		{
			switch (m_pathLadderDismountDir)
			{
			case LEFT:    StrafeLeft(); break;
			case RIGHT:   StrafeRight(); break;
			case FORWARD: MoveForward(); break;
			}
		}
		else
		{
			switch (m_pathLadderDismountDir)
			{
			case LEFT:    StrafeRight();  break;
			case RIGHT:   StrafeLeft();   break;
			case FORWARD: MoveBackward(); break;
			}
		}
		break;
	}
	case MOVE_TO_DESTINATION:
	{
		if (m_path[m_pathIndex].area->Contains(&pev->origin))
		{
			// successfully traversed ladder and reached destination area
			// exit ladder state machine
			PrintIfWatched("Ladder traversed.\n");
			m_pathLadder = nullptr;

			// incrememnt path index to next step beyond this ladder
			SetPathIndex(m_pathIndex + 1);

			return false;
		}

		MoveTowardsPosition(&m_goalPosition);
		break;
	}
	}

	return true;
}

// Compute closest point on path to given point
// NOTE: This does not do line-of-sight tests, so closest point may be thru the floor, etc
bool CCSBot::FindClosestPointOnPath(const Vector *worldPos, int startIndex, int endIndex, Vector *close) const
{
	if (!HasPath() || !close)
		return false;

	Vector along, toWorldPos;
	Vector pos;
	const Vector *from, *to;
	float length;
	float closeLength;
	float closeDistSq = 9999999999.9f;
	float distSq;

	for (int i = startIndex; i <= endIndex; i++)
	{
		from = &m_path[i - 1].pos;
		to = &m_path[i].pos;

		// compute ray along this path segment
		along = *to - *from;

		// make it a unit vector along the path
		length = along.NormalizeInPlace();

		// compute vector from start of segment to our point
		toWorldPos = *worldPos - *from;

		// find distance of closest point on ray
		closeLength = DotProduct(toWorldPos, along);

		// constrain point to be on path segment
		if (closeLength <= 0.0f)
			pos = *from;
		else if (closeLength >= length)
			pos = *to;
		else
			pos = *from + closeLength * along;

		distSq = (pos - *worldPos).LengthSquared();

		// keep the closest point so far
		if (distSq < closeDistSq)
		{
			closeDistSq = distSq;
			*close = pos;
		}
	}

	return true;
}

// Return the closest point to our current position on our current path
// If "local" is true, only check the portion of the path surrounding m_pathIndex.
int CCSBot::FindOurPositionOnPath(Vector *close, bool local) const
{
	if (!HasPath())
		return -1;

	Vector along, toFeet;
	Vector feet(pev->origin.x, pev->origin.y, GetFeetZ());
	Vector eyes = feet + Vector(0, 0, HalfHumanHeight); // in case we're crouching
	Vector pos;
	const Vector *from, *to;
	real_t length;
	float closeLength;
	float closeDistSq = 9999999999.9;
	int closeIndex = -1;
	real_t distSq;

	int start, end;

	if (local)
	{
		start = m_pathIndex - 3;
		if (start < 1)
			start = 1;

		end = m_pathIndex + 3;
		if (end > m_pathLength)
			end = m_pathLength;
	}
	else
	{
		start = 1;
		end = m_pathLength;
	}

	for (int i = start; i < end; i++)
	{
		from = &m_path[i - 1].pos;
		to = &m_path[i].pos;

		// compute ray along this path segment
		along = *to - *from;

		// make it a unit vector along the path
		length = along.NormalizeInPlace();

		// compute vector from start of segment to our point
		toFeet = feet - *from;

		// find distance of closest point on ray
		closeLength = DotProduct(toFeet, along);

		// constrain point to be on path segment
		if (closeLength <= 0.0f)
			pos = *from;
		else if (closeLength >= length)
			pos = *to;
		else
			pos = *from + closeLength * along;

		distSq = (pos - feet).LengthSquared();

		// keep the closest point so far
		if (distSq < closeDistSq)
		{
			// don't use points we cant see
			Vector probe = pos + Vector(0, 0, HalfHumanHeight);
			if (!IsWalkableTraceLineClear(eyes, probe, WALK_THRU_EVERYTHING))
				continue;

			// don't use points we cant reach
			if (!IsStraightLinePathWalkable(&pos))
				continue;

			closeDistSq = distSq;
			if (close)
				*close = pos;

			closeIndex = i - 1;
		}
	}

	return closeIndex;
}

// Test for un-jumpable height change, or unrecoverable fall
bool CCSBot::IsStraightLinePathWalkable(const Vector *goal) const
{
// this is causing hang-up problems when crawling thru ducts/windows that drop off into rooms (they fail the "falling" check)
return true;

	const float inc = GenerationStepSize;

	Vector feet = pev->origin;
	Vector dir = *goal - feet;
	float length = dir.NormalizeInPlace();

	float lastGround;

	//if (!GetSimpleGroundHeight(&pev->origin, &lastGround))
	//	return false;

	lastGround = feet.z;

	float along = 0.0f;
	Vector pos;
	float ground;
	bool done = false;

	while (!done)
	{
		along += inc;
		if (along > length)
		{
			along = length;
			done = true;
		}

		// compute step along path
		pos = feet + along * dir;
		pos.z += HalfHumanHeight;

		if (!GetSimpleGroundHeight(&pos, &ground))
			return false;

		// check for falling
		if (ground - lastGround < -StepHeight)
			return false;

		// check for unreachable jump
		// use slightly shorter jump limit, to allow for some fudge room
		if (ground - lastGround > JumpHeight)
			return false;

		lastGround = ground;
	}

	return true;
}

// Compute a point a fixed distance ahead along our path.
// Returns path index just after point.
int CCSBot::FindPathPoint(float aheadRange, Vector *point, int *prevIndex)
{
	// find path index just past aheadRange
	int afterIndex;

	// finds the closest point on local area of path, and returns the path index just prior to it
	Vector close;
	int startIndex = FindOurPositionOnPath(&close, true);

	if (prevIndex)
		*prevIndex = startIndex;

	if (startIndex <= 0)
	{
		// went off the end of the path
		// or next point in path is unwalkable (ie: jump-down)
		// keep same point
		return m_pathIndex;
	}

	// if we are crouching, just follow the path exactly
	if (IsCrouching())
	{
		// we want to move to the immediately next point along the path from where we are now
		int index = startIndex + 1;
		if (index >= m_pathLength)
			index = m_pathLength - 1;

		*point = m_path[index].pos;

		// if we are very close to the next point in the path, skip ahead to the next one to avoid wiggling
		// we must do a 2D check here, in case the goal point is floating in space due to jump down, etc
		const float closeEpsilon = 20.0f; // 10.0f
		while ((*point - close).Make2D().IsLengthLessThan(closeEpsilon))
		{
			index++;

			if (index >= m_pathLength)
			{
				index = m_pathLength - 1;
				break;
			}

			*point = m_path[index].pos;
		}

		return index;
	}

	// make sure we use a node a minimum distance ahead of us, to avoid wiggling
	while (startIndex < m_pathLength - 1)
	{
		Vector pos = m_path[startIndex + 1].pos;

		// we must do a 2D check here, in case the goal point is floating in space due to jump down, etc
		const float closeEpsilon = 20.0f;
		if ((pos - close).Make2D().IsLengthLessThan(closeEpsilon))
		{
			startIndex++;
		}
		else
		{
			break;
		}
	}

	// if we hit a ladder, stop, or jump area, must stop (dont use ladder behind us)
	if (startIndex > m_pathIndex && startIndex < m_pathLength
		&& (m_path[startIndex].ladder || (m_path[startIndex].area->GetAttributes() & NAV_JUMP)))
	{
		*point = m_path[startIndex].pos;
		return startIndex;
	}

	// we need the point just *ahead* of us
	if (++startIndex >= m_pathLength)
		startIndex = m_pathLength - 1;

	// if we hit a ladder, stop, or jump area, must stop
	if (startIndex < m_pathLength && (m_path[startIndex].ladder || (m_path[startIndex].area->GetAttributes() & NAV_JUMP)))
	{
		*point = m_path[startIndex].pos;
		return startIndex;
	}

	// note direction of path segment we are standing on
	Vector initDir = m_path[startIndex].pos - m_path[startIndex - 1].pos;
	initDir.NormalizeInPlace();

	Vector feet(pev->origin.x, pev->origin.y, GetFeetZ());
	Vector eyes = feet + Vector(0, 0, HalfHumanHeight);
	float rangeSoFar = 0;

	// this flag is true if our ahead point is visible
	bool visible = true;
	Vector prevDir = initDir;

	// step along the path until we pass aheadRange
	bool isCorner = false;
	int i;
	for (i = startIndex; i < m_pathLength; i++)
	{
		Vector pos = m_path[i].pos;
		Vector to = pos - m_path[i - 1].pos;
		Vector dir = to;
		dir.NormalizeInPlace();

		// don't allow path to double-back from our starting direction (going upstairs, down curved passages, etc)
		if (DotProduct(dir, initDir) < 0.0f) // -0.25f
		{
			i--;
			break;
		}

		// if the path turns a corner, we want to move towards the corner, not into the wall/stairs/etc
		if (DotProduct(dir, prevDir) < 0.5f)
		{
			isCorner = true;
			i--;
			break;
		}

		prevDir = dir;

		// don't use points we cant see
		Vector probe = pos + Vector(0, 0, HalfHumanHeight);
		if (!IsWalkableTraceLineClear(eyes, probe, WALK_THRU_BREAKABLES))
		{
			// presumably, the previous point is visible, so we will interpolate
			visible = false;
			break;
		}

		// if we encounter a ladder or jump area, we must stop
		if (i < m_pathLength && (m_path[i].ladder || (m_path[i].area->GetAttributes() & NAV_JUMP)))
			break;

		// Check straight-line path from our current position to this position
		// Test for un-jumpable height change, or unrecoverable fall
		if (!IsStraightLinePathWalkable(&pos))
		{
			i--;
			break;
		}

		Vector along = (i == startIndex) ? (pos - feet) : (pos - m_path[i - 1].pos);
		rangeSoFar += along.Length2D();

		// stop if we have gone farther than aheadRange
		if (rangeSoFar >= aheadRange)
			break;
	}

	if (i < startIndex)
		afterIndex = startIndex;
	else if (i < m_pathLength)
		afterIndex = i;
	else
		afterIndex = m_pathLength - 1;

	// compute point on the path at aheadRange
	if (afterIndex == 0)
	{
		*point = m_path[0].pos;
	}
	else
	{
		// interpolate point along path segment
		const Vector *afterPoint = &m_path[afterIndex].pos;
		const Vector *beforePoint = &m_path[afterIndex - 1].pos;

		Vector to = *afterPoint - *beforePoint;
		float length = to.Length2D();

		float t = 1.0f - ((rangeSoFar - aheadRange) / length);

		if (t < 0.0f)
			t = 0.0f;
		else if (t > 1.0f)
			t = 1.0f;

		*point = *beforePoint + t * to;

		// if afterPoint wasn't visible, slide point backwards towards beforePoint until it is
		if (!visible)
		{
			const float sightStepSize = 25.0f;
			float dt = sightStepSize / length;

			Vector probe = *point + Vector(0, 0, HalfHumanHeight);
			while (t > 0.0f && !IsWalkableTraceLineClear(eyes, probe, WALK_THRU_BREAKABLES))
			{
				t -= dt;
				*point = *beforePoint + t * to;
			}

			if (t <= 0.0f)
				*point = *beforePoint;
		}
	}

	// if position found is too close to us, or behind us, force it farther down the path so we don't stop and wiggle
	if (!isCorner)
	{
		const float epsilon = 50.0f;
		Vector2D toPoint;
		toPoint.x = point->x - pev->origin.x;
		toPoint.y = point->y - pev->origin.y;
		if (DotProduct(toPoint, initDir.Make2D()) < 0.0f || toPoint.IsLengthLessThan(epsilon))
		{
			int i;
			for (i = startIndex; i < m_pathLength; i++)
			{
				toPoint.x = m_path[i].pos.x - pev->origin.x;
				toPoint.y = m_path[i].pos.y - pev->origin.y;
				if (m_path[i].ladder || (m_path[i].area->GetAttributes() & NAV_JUMP) || toPoint.IsLengthGreaterThan(epsilon))
				{
					*point = m_path[i].pos;
					startIndex = i;
					break;
				}
			}

			if (i == m_pathLength)
			{
				*point = GetPathEndpoint();
				startIndex = m_pathLength - 1;
			}
		}
	}

	// m_pathIndex should always be the next point on the path, even if we're not moving directly towards it
	return startIndex;
}

// Set the current index along the path
void CCSBot::SetPathIndex(int newIndex)
{
	m_pathIndex = Q_min(newIndex, m_pathLength - 1);
	m_areaEnteredTimestamp = gpGlobals->time;

	if (m_path[m_pathIndex].ladder)
	{
		SetupLadderMovement();
	}
	else
	{
		// get our "encounter spots" for this leg of the path
		if (m_pathIndex < m_pathLength && m_pathIndex >= 2)
			m_spotEncounter = m_path[m_pathIndex - 1].area->GetSpotEncounter(m_path[m_pathIndex - 2].area, m_path[m_pathIndex].area);
		else
			m_spotEncounter = nullptr;

		m_pathLadder = nullptr;
	}
}

// Return true if nearing a jump in the path
bool CCSBot::IsNearJump() const
{
	if (m_pathIndex == 0 || m_pathIndex >= m_pathLength)
		return false;

	for (int i = m_pathIndex - 1; i < m_pathIndex; i++)
	{
		if (m_path[i].area->GetAttributes() & NAV_JUMP)
		{
			float dz = m_path[i + 1].pos.z - m_path[i].pos.z;
			if (dz > 0.0f)
			{
				return true;
			}
		}
	}

	return false;
}

// Return approximately how much damage will will take from the given fall height
float CCSBot::GetApproximateFallDamage(float height) const
{
	// empirically discovered height values
	const float slope = 0.2178f;
	const float intercept = 26.0f;

	real_t damage = slope * height - intercept;

	if (damage < 0.0f)
		return 0.0f;

	return damage;
}

// Return true if a friend is between us and the given position
bool CCSBot::IsFriendInTheWay(const Vector *goalPos) const
{
	// do this check less often to ease CPU burden
	if (!m_avoidFriendTimer.IsElapsed())
	{
		return m_isFriendInTheWay;
	}

	const float avoidFriendInterval = 0.5f;
	m_avoidFriendTimer.Start(avoidFriendInterval);

	// compute ray along intended path
	Vector moveDir = *goalPos - pev->origin;

	// make it a unit vector
	float length = moveDir.NormalizeInPlace();

	m_isFriendInTheWay = false;

	// check if any friends are overlapping this linear path
	for (int i = 1; i <= gpGlobals->maxClients; i++)
	{
		CBasePlayer *pPlayer = UTIL_PlayerByIndex(i);

		if (!pPlayer)
			continue;

		if (FNullEnt(pPlayer->pev))
			continue;

		if (!pPlayer->IsAlive())
			continue;

		// ignore enemies
		if (BotRelationship(pPlayer) == BOT_ENEMY)
			continue;

		if (pPlayer == this)
			continue;

		// compute vector from us to our friend
		Vector toFriend = pPlayer->pev->origin - pev->origin;

		// check if friend is in our "personal space"
		const float personalSpace = 100.0f;
		if (toFriend.IsLengthGreaterThan(personalSpace))
			continue;

		// find distance of friend along our movement path
		float friendDistAlong = DotProduct(toFriend, moveDir);

		// if friend is behind us, ignore him
		if (friendDistAlong <= 0.0f)
			continue;

		// constrain point to be on path segment
		Vector pos;
		if (friendDistAlong >= length)
			pos = *goalPos;
		else
			pos = pev->origin + friendDistAlong * moveDir;

		// check if friend overlaps our intended line of movement
		const float friendRadius = 30.0f;
		if ((pos - pPlayer->pev->origin).IsLengthLessThan(friendRadius))
		{
			// friend is in our personal space and overlaps our intended line of movement
			m_isFriendInTheWay = true;
			break;
		}
	}

	return m_isFriendInTheWay;
}

// Do reflex avoidance movements if our "feelers" are touched
void CCSBot::FeelerReflexAdjustment(Vector *goalPosition)
{
	// if we are in a "precise" area, do not do feeler adjustments
	if (m_lastKnownArea && (m_lastKnownArea->GetAttributes() & NAV_PRECISE))
		return;

	Vector dir(BotCOS(m_forwardAngle), BotSIN(m_forwardAngle), 0.0f);
	Vector lat(-dir.y, dir.x, 0.0f);

	const float feelerOffset = (IsCrouching()) ? 15.0f : 20.0f;
	const float feelerLengthRun = 50.0f; // 100 - too long for tight hallways (cs_747)
	const float feelerLengthWalk = 30.0f;
	const float feelerHeight = StepHeight + 0.1f; // if obstacle is lower than StepHeight, we'll walk right over it

	float feelerLength = (IsRunning()) ? feelerLengthRun : feelerLengthWalk;

	feelerLength = (IsCrouching()) ? 20.0f : feelerLength;

	// Feelers must follow floor slope
	float ground;
	Vector normal;

	//m_eyePos = EyePosition();
	m_eyePos.x = pev->origin.x + pev->view_ofs.x;
	m_eyePos.y = pev->origin.y + pev->view_ofs.y;
	m_eyePos.z = pev->origin.z + pev->view_ofs.z;

	if (GetSimpleGroundHeightWithFloor(&m_eyePos, &ground, &normal) == false)
		return;

	// get forward vector along floor
	dir = CrossProduct(lat, normal);

	// correct the sideways vector
	lat = CrossProduct(dir, normal);

	Vector feet(pev->origin.x, pev->origin.y, GetFeetZ());
	feet.z += feelerHeight;

	Vector from = feet + feelerOffset * lat;
	Vector to = from + feelerLength * dir;

	bool leftClear = IsWalkableTraceLineClear(from, to, WALK_THRU_EVERYTHING);

	// avoid ledges, too
	// use 'from' so it doesn't interfere with legitimate gap jumping (its at our feet)
	// TODO: Rethink this - it causes lots of wiggling when bots jump down from vents, etc
/*
	float ground;
	if (GetSimpleGroundHeightWithFloor(&from, &ground))
	{
		if (GetFeetZ() - ground > JumpHeight)
			leftClear = false;
	}
*/

	if ((cv_bot_traceview.value == 1.0f && IsLocalPlayerWatchingMe()) || cv_bot_traceview.value == 10.0f)
	{
		if (leftClear)
			UTIL_DrawBeamPoints(from, to, 1, 0, 255, 0);
		else
			UTIL_DrawBeamPoints(from, to, 1, 255, 0, 0);
	}

	from = feet - feelerOffset * lat;
	to = from + feelerLength * dir;

	bool rightClear = IsWalkableTraceLineClear(from, to, WALK_THRU_EVERYTHING);

/*
	// avoid ledges, too
	if (GetSimpleGroundHeightWithFloor(&from, &ground))
	{
		if (GetFeetZ() - ground > JumpHeight)
			rightClear = false;
	}
*/

	if ((cv_bot_traceview.value == 1.0f && IsLocalPlayerWatchingMe()) || cv_bot_traceview.value == 10.0f)
	{
		if (rightClear)
			UTIL_DrawBeamPoints(from, to, 1, 0, 255, 0);
		else
			UTIL_DrawBeamPoints(from, to, 1, 255, 0, 0);
	}

	const float avoidRange = (IsCrouching()) ? 150.0f : 300.0f; // 50.0f : 300.0f

	if (!rightClear)
	{
		if (leftClear)
		{
			// right hit, left clear - veer left
			*goalPosition = *goalPosition + avoidRange * lat;
		}
	}
	else if (!leftClear)
	{
		// right clear, left hit - veer right
		*goalPosition = *goalPosition - avoidRange * lat;
	}
}

// Move along the path. Return false if end of path reached.
CCSBot::PathResult CCSBot::UpdatePathMovement(bool allowSpeedChange)
{
	if (m_pathLength == 0)
		return PATH_FAILURE;

	if (cv_bot_walk.value != 0.0f)
		Walk();

	// If we are navigating a ladder, it overrides all other path movement until complete
	if (UpdateLadderMovement())
		return PROGRESSING;

	// ladder failure can destroy the path
	if (m_pathLength == 0)
		return PATH_FAILURE;

	// we are not supposed to be on a ladder - if we are, jump off
	if (IsOnLadder())
		Jump(MUST_JUMP);

	assert(m_pathIndex < m_pathLength);

	// Check if reached the end of the path
	bool nearEndOfPath = false;
	if (m_pathIndex >= m_pathLength - 1)
	{
		Vector toEnd(pev->origin.x, pev->origin.y, GetFeetZ());
		Vector d = GetPathEndpoint() - toEnd; // can't use 2D because path end may be below us (jump down)

		const float walkRange = 200.0f;

		// walk as we get close to the goal position to ensure we hit it
		if (d.IsLengthLessThan(walkRange))
		{
			// don't walk if crouching - too slow
			if (allowSpeedChange && !IsCrouching())
				Walk();

			// note if we are near the end of the path
			const float nearEndRange = 50.0f;
			if (d.IsLengthLessThan(nearEndRange))
				nearEndOfPath = true;

			const float closeEpsilon = 20.0f;
			if (d.IsLengthLessThan(closeEpsilon))
			{
				// reached goal position - path complete
				DestroyPath();

				// TODO: We should push and pop walk state here, in case we want to continue walking after reaching goal
				if (allowSpeedChange)
					Run();

				return END_OF_PATH;
			}
		}
	}

	// To keep us moving smoothly, we will move towards
	// a point farther ahead of us down our path.
	int prevIndex = 0;				// closest index on path just prior to where we are now
	const float aheadRange = 300.0f;
	int newIndex = FindPathPoint(aheadRange, &m_goalPosition, &prevIndex);

	// BOTPORT: Why is prevIndex sometimes -1?
	if (prevIndex < 0)
		prevIndex = 0;

	// if goal position is near to us, we must be about to go around a corner - so look ahead!
	const float nearCornerRange = 100.0f;
	if (m_pathIndex < m_pathLength - 1 && (m_goalPosition - pev->origin).IsLengthLessThan(nearCornerRange))
	{
		ClearLookAt();
		InhibitLookAround(0.5f);
	}

	// if we moved to a new node on the path, setup movement
	if (newIndex > m_pathIndex)
	{
		SetPathIndex(newIndex);
	}

	if (!IsUsingLadder())
	{
		// Crouching

		// if we are approaching a crouch area, crouch
		// if there are no crouch areas coming up, stand
		const float crouchRange = 50.0f;
		bool didCrouch = false;
		for (int i = prevIndex; i < m_pathLength; i++)
		{
			const CNavArea *to = m_path[i].area;

			// if there is a jump area on the way to the crouch area, don't crouch as it messes up the jump
			// unless we are already higher than the jump area - we must've jumped already but not moved into next area
			if ((to->GetAttributes() & NAV_JUMP)/* && to->GetCenter()->z > GetFeetZ()*/)
				break;

			Vector close;
			to->GetClosestPointOnArea(&pev->origin, &close);

			if ((close - pev->origin).Make2D().IsLengthGreaterThan(crouchRange))
				break;

			if (to->GetAttributes() & NAV_CROUCH)
			{
				Crouch();
				didCrouch = true;
				break;
			}
		}

		if (!didCrouch && !IsJumping())
		{
			// no crouch areas coming up
			StandUp();
		}
		// end crouching logic
	}

	// compute our forward facing angle
	m_forwardAngle = UTIL_VecToYaw(m_goalPosition - pev->origin);

	// Look farther down the path to "lead" our view around corners
	Vector toGoal;

	if (m_pathIndex == 0)
	{
		toGoal = m_path[1].pos;
	}
	else if (m_pathIndex < m_pathLength)
	{
		toGoal = m_path[m_pathIndex].pos - pev->origin;

		// actually aim our view farther down the path
		const float lookAheadRange = 500.0f;
		if (!m_path[m_pathIndex].ladder && !IsNearJump() && toGoal.Make2D().IsLengthLessThan(lookAheadRange))
		{
			float along = toGoal.Length2D();
			int i;
			for (i = m_pathIndex + 1; i < m_pathLength; i++)
			{
				Vector delta = m_path[i].pos - m_path[i - 1].pos;
				float segmentLength = delta.Length2D();

				if (along + segmentLength >= lookAheadRange)
				{
					// interpolate between points to keep look ahead point at fixed distance
					float t = (lookAheadRange - along) / (segmentLength + along);
					Vector target;

					if (t <= 0.0f)
						target = m_path[i - 1].pos;
					else if (t >= 1.0f)
						target = m_path[i].pos;
					else
						target = m_path[i - 1].pos + t * delta;

					toGoal = target - pev->origin;
					break;
				}

				// if we are coming up to a ladder or a jump, look at it
				if (m_path[i].ladder || (m_path[i].area->GetAttributes() & NAV_JUMP))
				{
					toGoal = m_path[i].pos - pev->origin;
					break;
				}

				along += segmentLength;
			}

			if (i == m_pathLength)
			{
				toGoal = GetPathEndpoint() - pev->origin;
			}
		}
	}
	else
	{
		toGoal = GetPathEndpoint() - pev->origin;
	}

	m_lookAheadAngle = UTIL_VecToYaw(toGoal);

	// initialize "adjusted" goal to current goal
	Vector adjustedGoal = m_goalPosition;

	// Use short "feelers" to veer away from close-range obstacles
	// Feelers come from our ankles, just above StepHeight, so we avoid short walls, too
	// Don't use feelers if very near the end of the path, or about to jump
	// TODO: Consider having feelers at several heights to deal with overhangs, etc.
	if (!nearEndOfPath && !IsNearJump() && !IsJumping())
	{
		FeelerReflexAdjustment(&adjustedGoal);
	}

	// draw debug visualization
	if ((cv_bot_traceview.value == 1.0f && IsLocalPlayerWatchingMe()) || cv_bot_traceview.value == 10.0f)
	{
		DrawPath();

		const Vector *pos = &m_path[m_pathIndex].pos;
		UTIL_DrawBeamPoints(*pos, *pos + Vector(0, 0, 50), 1, 255, 255, 0);
		UTIL_DrawBeamPoints(adjustedGoal, adjustedGoal + Vector(0, 0, 50), 1, 255, 0, 255);
		UTIL_DrawBeamPoints(pev->origin, adjustedGoal + Vector(0, 0, 50), 1, 255, 0, 255);
	}

	// dont use adjustedGoal, as it can vary wildly from the feeler adjustment
	if (!IsAttacking() && IsFriendInTheWay(&m_goalPosition))
	{
		if (!m_isWaitingBehindFriend)
		{
			m_isWaitingBehindFriend = true;

			const float politeDuration = 5.0f - 3.0f * GetProfile()->GetAggression();
			m_politeTimer.Start(politeDuration);
		}
		else if (m_politeTimer.IsElapsed())
		{
			// we have run out of patience
			m_isWaitingBehindFriend = false;
			ResetStuckMonitor();

			// repath to avoid clump of friends in the way
			DestroyPath();
		}
	}
	else if (m_isWaitingBehindFriend)
	{
		// we're done waiting for our friend to move
		m_isWaitingBehindFriend = false;
		ResetStuckMonitor();
	}

	// Move along our path if there are no friends blocking our way,
	// or we have run out of patience
	if (!m_isWaitingBehindFriend || m_politeTimer.IsElapsed())
	{
		// Move along path
		MoveTowardsPosition(&adjustedGoal);

		// Stuck check
		if (m_isStuck && !IsJumping())
		{
			Wiggle();
		}
	}

	// if our goal is high above us, we must have fallen
	bool didFall = false;
	if (m_goalPosition.z - GetFeetZ() > JumpCrouchHeight)
	{
		const float closeRange = 75.0f;
		Vector2D to(pev->origin.x - m_goalPosition.x, pev->origin.y - m_goalPosition.y);
		if (to.IsLengthLessThan(closeRange))
		{
			// we can't reach the goal position
			// check if we can reach the next node, in case this was a "jump down" situation
			if (m_pathIndex < m_pathLength - 1)
			{
				if (m_path[m_pathIndex + 1].pos.z - GetFeetZ() > JumpCrouchHeight)
				{
					// the next node is too high, too - we really did fall of the path
					didFall = true;
				}
			}
			else
			{
				// fell trying to get to the last node in the path
				didFall = true;
			}
		}
	}

	// This timeout check is needed if the bot somehow slips way off
	// of its path and cannot progress, but also moves around
	// enough that it never becomes "stuck"
	const float giveUpDuration = 5.0f; // 4.0f
	if (didFall || gpGlobals->time - m_areaEnteredTimestamp > giveUpDuration)
	{
		if (didFall)
		{
			PrintIfWatched("I fell off!\n");
		}

		// if we havent made any progress in a long time, give up
		if (m_pathIndex < m_pathLength - 1)
		{
			PrintIfWatched("Giving up trying to get to area #%d\n", m_path[m_pathIndex].area->GetID());
		}
		else
		{
			PrintIfWatched("Giving up trying to get to end of path\n");
		}

		Run();
		StandUp();
		DestroyPath();

		return PATH_FAILURE;
	}

	return PROGRESSING;
}

// Build trivial path to goal, assuming we are already in the same area
void CCSBot::BuildTrivialPath(const Vector *goal)
{
	m_pathIndex = 1;
	m_pathLength = 2;

	m_path[0].area = m_lastKnownArea;
	m_path[0].pos = pev->origin;
	m_path[0].pos.z = m_lastKnownArea->GetZ(&pev->origin);
	m_path[0].ladder = nullptr;
	m_path[0].how = NUM_TRAVERSE_TYPES;

	m_path[1].area = m_lastKnownArea;
	m_path[1].pos = *goal;
	m_path[1].pos.z = m_lastKnownArea->GetZ(goal);
	m_path[1].ladder = nullptr;
	m_path[1].how = NUM_TRAVERSE_TYPES;

	m_areaEnteredTimestamp = gpGlobals->time;
	m_spotEncounter = nullptr;
	m_pathLadder = nullptr;

	m_goalPosition = *goal;
}

// Compute shortest path to goal position via A* algorithm
// If 'goalArea' is NULL, path will get as close as it can.
bool CCSBot::ComputePath(CNavArea *goalArea, const Vector *goal, RouteType route)
{
	// Throttle re-pathing
	if (!m_repathTimer.IsElapsed())
		return false;

	// randomize to distribute CPU load
	m_repathTimer.Start(RANDOM_FLOAT(0.4f, 0.6f));

	DestroyPath();

	CNavArea *startArea = m_lastKnownArea;
	if (!startArea)
		return false;

	// note final specific position
	Vector pathEndPosition;

	if (!goal && !goalArea)
		return false;

	if (!goal)
		pathEndPosition = *goalArea->GetCenter();
	else
		pathEndPosition = *goal;

	// make sure path end position is on the ground
	if (goalArea)
		pathEndPosition.z = goalArea->GetZ(&pathEndPosition);
	else
		GetGroundHeight(&pathEndPosition, &pathEndPosition.z);

	// if we are already in the goal area, build trivial path
	if (startArea == goalArea)
	{
		BuildTrivialPath(&pathEndPosition);
		return true;
	}

	// Compute shortest path to goal
	CNavArea *closestArea = nullptr;
	PathCost pathCost(this, route);
	bool pathToGoalExists = NavAreaBuildPath(startArea, goalArea, goal, pathCost, &closestArea);

	CNavArea *effectiveGoalArea = (pathToGoalExists) ? goalArea : closestArea;

	// Build path by following parent links
	// get count
	int count = 0;
	CNavArea *area;
	for (area = effectiveGoalArea; area; area = area->GetParent())
	{
		count++;
	}

	// save room for endpoint
	if (count > MAX_PATH_LENGTH - 1)
		count = MAX_PATH_LENGTH - 1;

	if (count == 0)
		return false;

	if (count == 1)
	{
		BuildTrivialPath(&pathEndPosition);
		return true;
	}

	// build path
	m_pathLength = count;
	for (area = effectiveGoalArea; count && area; area = area->GetParent())
	{
		count--;
		m_path[count].area = area;
		m_path[count].how = area->GetParentHow();
	}

	// compute path positions
	if (ComputePathPositions() == false)
	{
		PrintIfWatched("Error building path\n");
		DestroyPath();
		return false;
	}

	if (!goal)
	{
		switch (m_path[m_pathLength - 1].how)
		{
		case GO_NORTH:
		case GO_SOUTH:
			pathEndPosition.x = m_path[m_pathLength - 1].pos.x;
			pathEndPosition.y = effectiveGoalArea->GetCenter()->y;
			break;

		case GO_EAST:
		case GO_WEST:
			pathEndPosition.x = effectiveGoalArea->GetCenter()->x;
			pathEndPosition.y = m_path[m_pathLength - 1].pos.y;
			break;
		}

		GetGroundHeight(&pathEndPosition, &pathEndPosition.z);
	}

	// append path end position
	m_path[m_pathLength].area = effectiveGoalArea;
	m_path[m_pathLength].pos = pathEndPosition;
	m_path[m_pathLength].ladder = nullptr;
	m_path[m_pathLength].how = NUM_TRAVERSE_TYPES;
	m_pathLength++;

	// do movement setup
	m_pathIndex = 1;
	m_areaEnteredTimestamp = gpGlobals->time;
	m_spotEncounter = nullptr;
	m_goalPosition = m_path[1].pos;

	if (m_path[1].ladder)
		SetupLadderMovement();
	else
		m_pathLadder = nullptr;

	return true;
}

// Return estimated distance left to travel along path
float CCSBot::GetPathDistanceRemaining() const
{
	if (!HasPath())
		return -1.0f;

	int idx = (m_pathIndex < m_pathLength) ? m_pathIndex : m_pathLength - 1;

	float dist = 0.0f;
	const Vector *prevCenter = m_path[m_pathIndex].area->GetCenter();

	for (int i = idx + 1; i < m_pathLength; i++)
	{
		dist += (*m_path[i].area->GetCenter() - *prevCenter).Length();
		prevCenter = m_path[i].area->GetCenter();
	}

	return dist;
}

// Draw a portion of our current path for debugging.
void CCSBot::DrawPath()
{
	if (!HasPath())
		return;

	for (int i = 1; i < m_pathLength; i++)
	{
		UTIL_DrawBeamPoints(m_path[i - 1].pos, m_path[i].pos, 2, 255, 75, 0);
	}

	Vector close;
	if (FindOurPositionOnPath(&close, true) >= 0)
	{
		UTIL_DrawBeamPoints(close + Vector(0, 0, 25), close, 1, 0, 255, 0);
		UTIL_DrawBeamPoints(close + Vector(25, 0, 0), close + Vector(-25, 0, 0), 1, 0, 255, 0);
		UTIL_DrawBeamPoints(close + Vector(0, 25, 0), close + Vector(0, -25, 0), 1, 0, 255, 0);
	}
}

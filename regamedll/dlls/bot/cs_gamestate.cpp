#include "precompiled.h"

/* <3fcd6b> ../cstrike/dlls/bot/cs_gamestate.cpp:27 */
CSGameState::CSGameState(CCSBot *owner)
{
	m_owner = owner;
	m_isRoundOver = false;
	m_bombState = MOVING;

	m_lastSawBomber.Invalidate();
	m_lastSawLooseBomb.Invalidate();
	m_validateInterval.Invalidate();
	m_isPlantedBombPosKnown = false;
	m_plantedBombsite = UNKNOWN;

	m_bombsiteCount = 0;
	m_bombsiteSearchIndex = 0;

	for (int i = 0; i < MAX_HOSTAGES; ++i)
	{
		HostageInfo *info = &m_hostage[i];
		
		info->hostage = NULL;
		info->knownPos = Vector(0, 0, 0);
		info->isValid = false;
		info->isAlive = false;
		info->isFree = true;
	}
}

// Reset at round start

/* <3fd4f4> ../cstrike/dlls/bot/cs_gamestate.cpp:55 */
void CSGameState::Reset(void)
{
	int i;
	CCSBotManager *ctrl = TheCSBots();

	m_isRoundOver = false;

	// bomb
	m_bombState = MOVING;
	m_lastSawBomber.Invalidate();
	m_lastSawLooseBomb.Invalidate();
	m_bombsiteCount = ctrl->GetZoneCount();

	m_isPlantedBombPosKnown = false;
	m_plantedBombsite = UNKNOWN;

	for (i = 0; i < m_bombsiteCount; ++i)
	{
		m_isBombsiteClear[i] = false;
		m_bombsiteSearchOrder[i] = i;
	}

	// shuffle the bombsite search order
	// allows T's to plant at random site, and TEAM_CT's to search in a random order
	// NOTE: VS6 std::random_shuffle() doesn't work well with an array of two elements (most maps)
	for (i = 0; i < m_bombsiteCount; ++i)
	{
		int swap = m_bombsiteSearchOrder[i];
		int rnd = RANDOM_LONG(i, m_bombsiteCount - 1);

		m_bombsiteSearchOrder[i] = m_bombsiteSearchOrder[rnd];
		m_bombsiteSearchOrder[rnd] = swap;
	}

	m_bombsiteSearchIndex = 0;
	InitializeHostageInfo();
}

// Update game state based on events we have received

/* <3fce67> ../cstrike/dlls/bot/cs_gamestate.cpp:97 */
void CSGameState::OnEvent(GameEventType event, CBaseEntity *entity, CBaseEntity *other)
{
	switch (event)
	{
	case EVENT_BOMB_PLANTED:
		SetBombState(PLANTED);
		if (m_owner->m_iTeam == TERRORIST && other != NULL)
		{
			UpdatePlantedBomb(&other->pev->origin);
		}
		break;
	case EVENT_BOMB_DEFUSED:
		SetBombState(DEFUSED);
		break;
	case EVENT_BOMB_EXPLODED:
		SetBombState(EXPLODED);
		break;
	case EVENT_ALL_HOSTAGES_RESCUED:
		m_allHostagesRescued = true;
		break;
	case EVENT_TERRORISTS_WIN:
	case EVENT_CTS_WIN:
	case EVENT_ROUND_DRAW:
		m_isRoundOver = true;
		break;
	default:
		break;
	}
}

// True if round has been won or lost (but not yet reset)

/* <3fcf9c> ../cstrike/dlls/bot/cs_gamestate.cpp:144 */
bool CSGameState::IsRoundOver(void) const
{
	return m_isRoundOver;
}

/* <3fcfc6> ../cstrike/dlls/bot/cs_gamestate.cpp:150 */
void CSGameState::SetBombState(BombState state)
{
	// if state changed, reset "last seen" timestamps
	if (m_bombState != state)
	{
		m_bombState = state;
	}
}

/* <3fcff2> ../cstrike/dlls/bot/cs_gamestate.cpp:160 */
void CSGameState::UpdateLooseBomb(const Vector *pos)
{
	m_looseBombPos = *pos;
	m_lastSawLooseBomb.Reset();

	// we saw the loose bomb, update our state
	SetBombState(LOOSE);
}

/* <3fd06e> ../cstrike/dlls/bot/cs_gamestate.cpp:170 */
float CSGameState::TimeSinceLastSawLooseBomb(void) const
{
	return m_lastSawLooseBomb.GetElapsedTime();
}

/* <3fd0f4> ../cstrike/dlls/bot/cs_gamestate.cpp:176 */
bool CSGameState::IsLooseBombLocationKnown(void) const
{
	if (m_bombState != LOOSE)
		return false;

	return (m_lastSawLooseBomb.HasStarted()) ? true : false;
}

/* <3fd135> ../cstrike/dlls/bot/cs_gamestate.cpp:185 */
void CSGameState::UpdateBomber(const Vector *pos)
{
	m_bomberPos = *pos;
	m_lastSawBomber.Reset();

	// we saw the bomber, update our state
	SetBombState(MOVING);
}

/* <3fd1b1> ../cstrike/dlls/bot/cs_gamestate.cpp:195 */
float CSGameState::TimeSinceLastSawBomber(void) const
{
	return m_lastSawBomber.GetElapsedTime();
}

/* <3fd237> ../cstrike/dlls/bot/cs_gamestate.cpp:201 */
bool CSGameState::IsPlantedBombLocationKnown(void) const
{
	if (m_bombState != PLANTED)
		return false;

	return m_isPlantedBombPosKnown;
}

// Return the zone index of the planted bombsite, or UNKNOWN

/* <3fd25a> ../cstrike/dlls/bot/cs_gamestate.cpp:213 */
int CSGameState::GetPlantedBombsite(void) const
{
	if (m_bombState != PLANTED)
		return UNKNOWN;

	return m_plantedBombsite;
}

// Return true if we are currently in the bombsite where the bomb is planted

/* <3fd284> ../cstrike/dlls/bot/cs_gamestate.cpp:225 */
bool CSGameState::IsAtPlantedBombsite(void) const
{
	if (m_bombState != PLANTED)
		return false;

	CCSBotManager *ctrl = TheCSBots();
	const CCSBotManager::Zone *zone = ctrl->GetClosestZone(&m_owner->pev->origin);

	if (zone != NULL)
	{
		return (m_plantedBombsite == zone->m_index);
	}

	return false;
}

// Return the zone index of the next bombsite to search

/* <3fd2d2> ../cstrike/dlls/bot/cs_gamestate.cpp:246 */
int CSGameState::GetNextBombsiteToSearch(void)
{
	if (m_bombsiteCount <= 0)
		return 0;

	int i;
	// return next non-cleared bombsite index
	for (i = m_bombsiteSearchIndex; i < m_bombsiteCount; ++i)
	{
		int z = m_bombsiteSearchOrder[i];
		if (!m_isBombsiteClear[z])
		{
			m_bombsiteSearchIndex = i;
			return z;
		}
	}

	// all the bombsites are clear, someone must have been mistaken - start search over
	for (i = 0; i < m_bombsiteCount; ++i)
	{
		m_isBombsiteClear[i] = false;
	}

	m_bombsiteSearchIndex = 0;
	return GetNextBombsiteToSearch();
}

// Returns position of bomb in its various states (moving, loose, planted),
// or NULL if we don't know where the bomb is

/* <3fd32c> ../cstrike/dlls/bot/cs_gamestate.cpp:277 */
const Vector *CSGameState::GetBombPosition(void) const
{
	switch (m_bombState)
	{
		case MOVING:
		{
			if (!m_lastSawBomber.HasStarted())
				return NULL;

			return &m_bomberPos;
		}
		case LOOSE:
		{
			if (IsLooseBombLocationKnown())
				return &m_looseBombPos;

			return NULL;
		}
		case PLANTED:
		{
			if (IsPlantedBombLocationKnown())
				return &m_plantedBombPos;

			return NULL;
		}
	}

	return NULL;
}

// We see the planted bomb at 'pos'

/* <3fd373> ../cstrike/dlls/bot/cs_gamestate.cpp:313 */
void CSGameState::UpdatePlantedBomb(const Vector *pos)
{
	CCSBotManager *ctrl = TheCSBots();
	const CCSBotManager::Zone *zone = ctrl->GetClosestZone(pos);

	if (zone == NULL)
	{
		CONSOLE_ECHO("ERROR: Bomb planted outside of a zone!\n");
		m_plantedBombsite = UNKNOWN;
	}
	else
	{
		m_plantedBombsite = zone->m_index;
	}

	m_plantedBombPos = *pos;
	m_isPlantedBombPosKnown = true;
	SetBombState(PLANTED);
}

// Someone told us where the bomb is planted

/* <3fd3dd> ../cstrike/dlls/bot/cs_gamestate.cpp:337 */
void CSGameState::MarkBombsiteAsPlanted(int zoneIndex)
{
	m_plantedBombsite = zoneIndex;
	SetBombState(PLANTED);
}

// Someone told us a bombsite is clear

/* <3fd43a> ../cstrike/dlls/bot/cs_gamestate.cpp:347 */
void CSGameState::ClearBombsite(int zoneIndex)
{
	if (zoneIndex >= 0 && zoneIndex < m_bombsiteCount)
		m_isBombsiteClear[zoneIndex] = true;
}

/* <3fd475> ../cstrike/dlls/bot/cs_gamestate.cpp:354 */
bool CSGameState::IsBombsiteClear(int zoneIndex) const
{
	if (zoneIndex >= 0 && zoneIndex < m_bombsiteCount)
		return m_isBombsiteClear[zoneIndex];

	return false;
}

/* <3fd4b0> ../cstrike/dlls/bot/cs_gamestate.cpp:367 */
void CSGameState::InitializeHostageInfo(void)
{
	m_hostageCount = 0;
	m_allHostagesRescued = 0;
	m_haveSomeHostagesBeenTaken = 0;

	CBaseEntity *hostage = NULL;
	while ((hostage = UTIL_FindEntityByClassname(hostage, "hostage_entity")) != NULL)
	{
		if (m_hostageCount >= MAX_HOSTAGES)
			break;

		if (hostage->pev->takedamage != DAMAGE_YES)
			continue;

		m_hostage[m_hostageCount].hostage = static_cast<CHostage *>(hostage);
		m_hostage[m_hostageCount].knownPos = hostage->pev->origin;
		m_hostage[m_hostageCount].isValid = true;
		m_hostage[m_hostageCount].isAlive = true;
		m_hostage[m_hostageCount].isFree = true;
		++m_hostageCount;
	}
}

// Return the closest free and live hostage
// If we are a CT this information is perfect. 
// Otherwise, this is based on our individual memory of the game state.
// If NULL is returned, we don't think there are any hostages left, or we dont know where they are.
// NOTE: a T can remember a hostage who has died.  knowPos will be filled in, but NULL will be
//	returned, since CHostages get deleted when they die.

/* <3fd5ab> ../cstrike/dlls/bot/cs_gamestate.cpp:398 */
CHostage *CSGameState::GetNearestFreeHostage(Vector *knowPos) const
{
	if (m_owner == NULL)
		return NULL;

	CNavArea *startArea = m_owner->GetLastKnownArea();

	if (startArea == NULL)
		return NULL;

	CHostage *close = NULL;
	const Vector *closePos = NULL;
	float closeDistance = 9999999999.9f;

	for (int i = 0; i < m_hostageCount; ++i)
	{
		CHostage *hostage = m_hostage[i].hostage;
		const Vector *hostagePos = NULL;

		if (m_owner->m_iTeam == CT)
		{
			// we know exactly where the hostages are, and if they are alive
			if (!m_hostage[i].hostage || !m_hostage[i].hostage->IsValid())
				continue;

			if (m_hostage[i].hostage->IsFollowingSomeone())
				continue;

			hostagePos = &hostage->pev->origin;
		}
		else
		{
			// use our memory of where we think the hostages are
			if (m_hostage[i].isValid == false)
				continue;

			hostagePos = &m_hostage[i].knownPos;
		}

		CNavArea *hostageArea = TheNavAreaGrid.GetNearestNavArea(hostagePos);

		if (hostageArea != NULL)
		{
			ShortestPathCost pc;
			float travelDistance = NavAreaTravelDistance(startArea, hostageArea, pc);

			if (travelDistance >= 0.0f && travelDistance < closeDistance)
			{
				closePos = hostagePos;
				closeDistance = travelDistance;
				close = hostage;
			}
		}
	}

	// return where we think the hostage is
	if (knowPos != NULL && closePos != NULL)
	{
		knowPos = const_cast<Vector *>(closePos);
	}

	return close;
}

// Return the location of a "free" hostage, or NULL if we dont know of any

/* <3fdbd3> ../cstrike/dlls/bot/cs_gamestate.cpp:461 */
const Vector *CSGameState::GetRandomFreeHostagePosition(void)
{
	// TODO: use static?
	const Vector *freePos[MAX_HOSTAGES];
	int freeCount = 0;

	if (m_owner == NULL)
		return NULL;

	for (int i = 0; i < m_hostageCount; ++i)
	{
		const HostageInfo *info = &m_hostage[i];
		const Vector *hostagePos = NULL;

		if (m_owner->m_iTeam == CT)
		{
			// we know exactly where the hostages are, and if they are alive
			if (!info->hostage || !info->hostage->IsAlive())
				continue;

			// escorted hostages are not "free"
			if (info->hostage->IsFollowingSomeone())
				continue;

			freePos[ freeCount++ ] = &info->hostage->pev->origin;
		}
		else
		{
			// use our memory of where we think the hostages are
			if (info->isValid == false)
				continue;

			freePos[ freeCount++ ] = &info->knownPos;
		}
	}

	if (freeCount)
	{
		return freePos[RANDOM_LONG(0, freeCount - 1)];
	}

	return NULL;
}

// If we can see any of the positions where we think a hostage is, validate it
// Return status of any changes (a hostage died or was moved)

/* <3fdcd2> ../cstrike/dlls/bot/cs_gamestate.cpp:509 */
CSGameState::ValidateStatusType CSGameState::ValidateHostagePositions(void)
{
	// limit how often we validate
	if (!m_validateInterval.IsElapsed())
		return NO_CHANGE;
	
	const float validateInterval = 0.5f;
	m_validateInterval.Start(validateInterval);

	// check the status of hostages
	ValidateStatusType status = NO_CHANGE;

	int i;
	int startValidCount = 0;
	for (i = 0; i < m_hostageCount; ++i)
	{
		if (m_hostage[i].isValid)
			++startValidCount;
	}

	for (i = 0; i < m_hostageCount; ++i)
	{
		HostageInfo *info = &m_hostage[i];

		if  (!info->hostage)
			continue;

		// if we can see a hostage, update our knowledge of it
		if (m_owner->IsVisible(&info->hostage->pev->origin, CHECK_FOV))
		{
			if (info->hostage->pev->takedamage == DAMAGE_YES)
			{
				// live hostage
				// if hostage is being escorted by a CT, we don't "see" it, we see the CT
				if (info->hostage->IsFollowingSomeone())
				{
					info->isValid = false;
				}
				else
				{
					info->knownPos = info->hostage->pev->origin;
					info->isValid = true;
				}
			}
			else
			{
				// dead hostage
				// if we thought it was alive, this is news to us
				if (info->isAlive)
					status |= HOSTAGE_DIED;

				info->isAlive = false;
				info->isValid = false;
			}

			continue;
		}

		// if we dont know where this hostage is, nothing to validate
		if (!info->isValid)
			continue;

		// can't directly see this hostage
		// check line of sight to where we think this hostage is, to see if we noticed that is has moved
		if (m_owner->IsVisible(&info->knownPos, CHECK_FOV))
		{
			// we can see where we thought the hostage was - verify it is still there and alive
			if (info->hostage->pev->takedamage != DAMAGE_YES)
			{
				// since we have line of sight to an invalid hostage, it must be dead
				// discovered that hostage has been killed
				status |= HOSTAGE_DIED;

				info->isAlive = false;
				info->isValid = false;
				continue;
			}

			if (info->hostage->IsFollowingSomeone())
			{
				// discovered the hostage has been taken
				status |= HOSTAGE_GONE;
				info->isValid = false;
				continue;
			}

			const float tolerance = 50.0f;
			if ((info->hostage->pev->origin - info->knownPos).IsLengthGreaterThan(tolerance))
			{
				// discovered that hostage has been moved
				status |= HOSTAGE_GONE;
				info->isValid = false;
				continue;
			}
		}
	}

	int endValidCount = 0;
	for (i = 0; i < m_hostageCount; ++i)
	{
		if (m_hostage[i].isValid)
			++endValidCount;
	}

	if (endValidCount == 0 && startValidCount > 0)
	{
		// we discovered all the hostages are gone
		status &= ~HOSTAGE_GONE;
		status |= HOSTAGES_ALL_GONE;
	}

	return status;
}

// Return the nearest visible free hostage
// Since we can actually see any hostage we return, we know its actual position

/* <3fdef7> ../cstrike/dlls/bot/cs_gamestate.cpp:626 */
CHostage *CSGameState::GetNearestVisibleFreeHostage(void) const
{
	CHostage *close = NULL;
	float closeRangeSq = 999999999.9f;
	float rangeSq;

	Vector pos;
	
	for (int i = 0; i < m_hostageCount; ++i)
	{
		const HostageInfo *info = &m_hostage[i];

		if (!info->hostage)
			continue;

		// if the hostage is dead or rescued, its not free
		if (info->hostage->pev->takedamage != DAMAGE_YES)
			continue;

		// if this hostage is following someone, its not free
		if (info->hostage->IsFollowingSomeone())
			continue;

		// TODO: Use travel distance here
		pos = info->hostage->pev->origin + Vector(0, 0, HumanHeight * 0.75f);
		rangeSq = (pos - m_owner->pev->origin).LengthSquared();

		if (rangeSq < closeRangeSq)
		{
			if (!m_owner->IsVisible(&pos))
				continue;

			close = info->hostage;
			closeRangeSq = rangeSq;
		}
	}

	return close;
}

// Return true if there are no free hostages

/* <3fe064> ../cstrike/dlls/bot/cs_gamestate.cpp:668 */
bool CSGameState::AreAllHostagesBeingRescued(void) const
{
	// if the hostages have all been rescued, they are not being rescued any longer
	if (m_allHostagesRescued)
		return false;

	bool isAllDead = true;

	for (int i = 0; i < m_hostageCount; ++i)
	{
		const HostageInfo *info = &m_hostage[i];

		if (m_owner->m_iTeam == CT)
		{
			// CT's have perfect knowledge via their radar
			if (info->hostage != NULL && info->hostage->IsValid())
			{
				if (!info->hostage->IsFollowingSomeone())
					return false;

				isAllDead = false;
			}
		}
		else
		{
			if (info->isValid && info->isAlive)
				return false;

			if (info->isAlive)
				isAllDead = false;
		}
	}

	// if all of the remaining hostages are dead, they arent being rescued
	if (isAllDead)
		return false;

	return true;
}

// All hostages have been rescued or are dead

/* <3fe148> ../cstrike/dlls/bot/cs_gamestate.cpp:712 */
bool CSGameState::AreAllHostagesGone(void) const
{
	if (m_allHostagesRescued)
		return true;

	// do we know that all the hostages are dead
	for (int i = 0; i < m_hostageCount; ++i)
	{
		const HostageInfo *info = &m_hostage[i];

		if (m_owner->m_iTeam == CT)
		{
			// CT's have perfect knowledge via their radar
			if (info->hostage->IsAlive())// == DAMAGE_YES)
				return false;
		}
		else
		{
			if (info->isValid && info->isAlive)
				return false;
		}
	}

	return true;
}

// Someone told us all the hostages are gone

/* <3fe1a2> ../cstrike/dlls/bot/cs_gamestate.cpp:742 */
void CSGameState::AllHostagesGone(void)
{
	for (int i = 0; i < m_hostageCount; ++i)
		m_hostage[i].isValid = false;
}

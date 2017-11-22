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

	for (int i = 0; i < MAX_HOSTAGES; i++)
	{
		HostageInfo *info = &m_hostage[i];

		info->hostage = nullptr;
		info->knownPos = Vector(0, 0, 0);
		info->isValid = false;
		info->isAlive = false;
		info->isFree = true;
	}
}

// Reset at round start
void CSGameState::Reset()
{
	int i;
	m_isRoundOver = false;

	// bomb
	m_bombState = MOVING;
	m_lastSawBomber.Invalidate();
	m_lastSawLooseBomb.Invalidate();
	m_bombsiteCount = TheCSBots()->GetZoneCount();

	m_isPlantedBombPosKnown = false;
	m_plantedBombsite = UNKNOWN;

	for (i = 0; i < m_bombsiteCount; i++)
	{
		m_isBombsiteClear[i] = false;
		m_bombsiteSearchOrder[i] = i;
	}

	// shuffle the bombsite search order
	// allows T's to plant at random site, and TEAM_CT's to search in a random order
	// NOTE: VS6 std::random_shuffle() doesn't work well with an array of two elements (most maps)
	for (i = 0; i < m_bombsiteCount; i++)
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
void CSGameState::OnEvent(GameEventType event, CBaseEntity *pEntity, CBaseEntity *pOther)
{
	switch (event)
	{
	case EVENT_BOMB_PLANTED:
	{
		// change state - the event is announced to everyone
		SetBombState(PLANTED);

		// Terrorists always know where the bomb is
		if (m_owner->m_iTeam == TERRORIST && pOther)
		{
			UpdatePlantedBomb(&pOther->pev->origin);
		}
		break;
	}
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
bool CSGameState::IsRoundOver() const
{
	return m_isRoundOver;
}

void CSGameState::SetBombState(BombState state)
{
	// if state changed, reset "last seen" timestamps
	if (m_bombState != state)
	{
		m_bombState = state;
	}
}

void CSGameState::UpdateLooseBomb(const Vector *pos)
{
	m_looseBombPos = *pos;
	m_lastSawLooseBomb.Reset();

	// we saw the loose bomb, update our state
	SetBombState(LOOSE);
}

float CSGameState::TimeSinceLastSawLooseBomb() const
{
	return m_lastSawLooseBomb.GetElapsedTime();
}

bool CSGameState::IsLooseBombLocationKnown() const
{
	if (m_bombState != LOOSE)
		return false;

	return (m_lastSawLooseBomb.HasStarted()) ? true : false;
}

void CSGameState::UpdateBomber(const Vector *pos)
{
	m_bomberPos = *pos;
	m_lastSawBomber.Reset();

	// we saw the bomber, update our state
	SetBombState(MOVING);
}

float CSGameState::TimeSinceLastSawBomber() const
{
	return m_lastSawBomber.GetElapsedTime();
}

bool CSGameState::IsPlantedBombLocationKnown() const
{
	if (m_bombState != PLANTED)
		return false;

	return m_isPlantedBombPosKnown;
}

// Return the zone index of the planted bombsite, or UNKNOWN
int CSGameState::GetPlantedBombsite() const
{
	if (m_bombState != PLANTED)
		return UNKNOWN;

	return m_plantedBombsite;
}

// Return true if we are currently in the bombsite where the bomb is planted
bool CSGameState::IsAtPlantedBombsite() const
{
	if (m_bombState != PLANTED)
		return false;

	const CCSBotManager::Zone *zone = TheCSBots()->GetClosestZone(&m_owner->pev->origin);

	if (zone)
	{
		return (m_plantedBombsite == zone->m_index);
	}

	return false;
}

// Return the zone index of the next bombsite to search
int CSGameState::GetNextBombsiteToSearch()
{
	if (m_bombsiteCount <= 0)
		return 0;

	int i;
	// return next non-cleared bombsite index
	for (i = m_bombsiteSearchIndex; i < m_bombsiteCount; i++)
	{
		int z = m_bombsiteSearchOrder[i];
		if (!m_isBombsiteClear[z])
		{
			m_bombsiteSearchIndex = i;
			return z;
		}
	}

	// all the bombsites are clear, someone must have been mistaken - start search over
	for (i = 0; i < m_bombsiteCount; i++)
	{
		m_isBombsiteClear[i] = false;
	}

	m_bombsiteSearchIndex = 0;
	return GetNextBombsiteToSearch();
}

// Returns position of bomb in its various states (moving, loose, planted),
// or NULL if we don't know where the bomb is
const Vector *CSGameState::GetBombPosition() const
{
	switch (m_bombState)
	{
	case MOVING:
	{
		if (!m_lastSawBomber.HasStarted())
			return nullptr;

		return &m_bomberPos;
	}
	case LOOSE:
	{
		if (IsLooseBombLocationKnown())
			return &m_looseBombPos;

		return nullptr;
	}
	case PLANTED:
	{
		if (IsPlantedBombLocationKnown())
			return &m_plantedBombPos;

		return nullptr;
	}
	}

	return nullptr;
}

// We see the planted bomb at 'pos'
void CSGameState::UpdatePlantedBomb(const Vector *pos)
{
	const CCSBotManager::Zone *zone = TheCSBots()->GetClosestZone(pos);

	if (!zone)
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
void CSGameState::MarkBombsiteAsPlanted(int zoneIndex)
{
	m_plantedBombsite = zoneIndex;
	SetBombState(PLANTED);
}

// Someone told us a bombsite is clear
void CSGameState::ClearBombsite(int zoneIndex)
{
	if (zoneIndex >= 0 && zoneIndex < m_bombsiteCount)
		m_isBombsiteClear[zoneIndex] = true;
}

bool CSGameState::IsBombsiteClear(int zoneIndex) const
{
	if (zoneIndex >= 0 && zoneIndex < m_bombsiteCount)
		return m_isBombsiteClear[zoneIndex];

	return false;
}

void CSGameState::InitializeHostageInfo()
{
	m_hostageCount = 0;
	m_allHostagesRescued = false;
	m_haveSomeHostagesBeenTaken = false;

	CHostage *pHostage = nullptr;
	while ((pHostage = UTIL_FindEntityByClassname(pHostage, "hostage_entity")))
	{
		if (m_hostageCount >= MAX_HOSTAGES)
			break;

		if (!pHostage->IsAlive())
			continue;

		m_hostage[m_hostageCount].hostage = pHostage;
		m_hostage[m_hostageCount].knownPos = pHostage->pev->origin;
		m_hostage[m_hostageCount].isValid = true;
		m_hostage[m_hostageCount].isAlive = true;
		m_hostage[m_hostageCount].isFree = true;
		m_hostageCount++;
	}
}

// Return the closest free and live hostage
// If we are a CT this information is perfect.
// Otherwise, this is based on our individual memory of the game state.
// If NULL is returned, we don't think there are any hostages left, or we dont know where they are.
// NOTE: a T can remember a hostage who has died.  knowPos will be filled in, but NULL will be
// returned, since CHostages get deleted when they die.
CHostage *CSGameState::GetNearestFreeHostage(Vector *knowPos) const
{
	if (!m_owner)
		return nullptr;

	CNavArea *startArea = m_owner->GetLastKnownArea();
	if (!startArea)
		return nullptr;

	CHostage *close = nullptr;
	const Vector *closePos = nullptr;
	float closeDistance = 9999999999.9f;

	for (int i = 0; i < m_hostageCount; i++)
	{
		CHostage *pHostage = m_hostage[i].hostage;
		const Vector *hostagePos = nullptr;

		if (m_owner->m_iTeam == CT)
		{
			// we know exactly where the hostages are, and if they are alive
			if (!m_hostage[i].hostage || !m_hostage[i].hostage->IsAlive())
				continue;

			if (m_hostage[i].hostage->IsFollowingSomeone())
				continue;

			hostagePos = &pHostage->pev->origin;
		}
		else
		{
			// use our memory of where we think the hostages are
			if (m_hostage[i].isValid == false)
				continue;

			hostagePos = &m_hostage[i].knownPos;
		}

		CNavArea *hostageArea = TheNavAreaGrid.GetNearestNavArea(hostagePos);
		if (hostageArea)
		{
			ShortestPathCost pc;
			float travelDistance = NavAreaTravelDistance(startArea, hostageArea, pc);

			if (travelDistance >= 0.0f && travelDistance < closeDistance)
			{
				closePos = hostagePos;
				closeDistance = travelDistance;
				close = pHostage;
			}
		}
	}

	// return where we think the hostage is
	if (knowPos && closePos)
	{
		knowPos = const_cast<Vector *>(closePos);
	}

	return close;
}

// Return the location of a "free" hostage, or NULL if we dont know of any
const Vector *CSGameState::GetRandomFreeHostagePosition()
{
	// TODO: use static?
	const Vector *freePos[MAX_HOSTAGES];
	int freeCount = 0;

	if (!m_owner)
		return nullptr;

	for (int i = 0; i < m_hostageCount; i++)
	{
		const HostageInfo *info = &m_hostage[i];
		const Vector *hostagePos = nullptr;

		if (m_owner->m_iTeam == CT)
		{
			// we know exactly where the hostages are, and if they are alive
			if (!info->hostage || !info->hostage->IsAlive())
				continue;

			// escorted hostages are not "free"
			if (info->hostage->IsFollowingSomeone())
				continue;

			freePos[freeCount++] = &info->hostage->pev->origin;
		}
		else
		{
			// use our memory of where we think the hostages are
			if (info->isValid == false)
				continue;

			freePos[freeCount++] = &info->knownPos;
		}
	}

	if (freeCount)
	{
		return freePos[RANDOM_LONG(0, freeCount - 1)];
	}

	return nullptr;
}

// If we can see any of the positions where we think a hostage is, validate it
// Return status of any changes (a hostage died or was moved)
CSGameState::ValidateStatusType CSGameState::ValidateHostagePositions()
{
	// limit how often we validate
	if (!m_validateInterval.IsElapsed())
		return NO_CHANGE;

	const float validateInterval = 0.5f;
	m_validateInterval.Start(validateInterval);

	// check the status of hostages
	unsigned char status = NO_CHANGE;

	int i;
	int startValidCount = 0;
	for (i = 0; i < m_hostageCount; i++)
	{
		if (m_hostage[i].isValid)
			startValidCount++;
	}

	for (i = 0; i < m_hostageCount; i++)
	{
		HostageInfo *info = &m_hostage[i];

		if (!info->hostage)
			continue;

		// if we can see a hostage, update our knowledge of it
		if (m_owner->IsVisible(&info->hostage->pev->origin, CHECK_FOV))
		{
			if (info->hostage->IsAlive())
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
			if (!info->hostage->IsAlive())
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
	for (i = 0; i < m_hostageCount; i++)
	{
		if (m_hostage[i].isValid)
			endValidCount++;
	}

	if (endValidCount == 0 && startValidCount > 0)
	{
		// we discovered all the hostages are gone
		status &= ~HOSTAGE_GONE;
		status |= HOSTAGES_ALL_GONE;
	}

	return static_cast<ValidateStatusType>(status);
}

// Return the nearest visible free hostage
// Since we can actually see any hostage we return, we know its actual position
CHostage *CSGameState::GetNearestVisibleFreeHostage() const
{
	CHostage *close = nullptr;
	float closeRangeSq = 999999999.9f;
	float rangeSq;

	Vector pos;

	for (int i = 0; i < m_hostageCount; i++)
	{
		const HostageInfo *info = &m_hostage[i];

		if (!info->hostage)
			continue;

		// if the hostage is dead or rescued, its not free
		if (!info->hostage->IsAlive())
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
bool CSGameState::AreAllHostagesBeingRescued() const
{
	// if the hostages have all been rescued, they are not being rescued any longer
	if (m_allHostagesRescued)
		return false;

	bool isAllDead = true;
	for (int i = 0; i < m_hostageCount; i++)
	{
		const HostageInfo *info = &m_hostage[i];

		if (m_owner->m_iTeam == CT)
		{
			// CT's have perfect knowledge via their radar
			if (info->hostage && info->hostage->IsAlive())
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
bool CSGameState::AreAllHostagesGone() const
{
	if (m_allHostagesRescued)
		return true;

	// do we know that all the hostages are dead
	for (int i = 0; i < m_hostageCount; i++)
	{
		const HostageInfo *info = &m_hostage[i];

		if (m_owner->m_iTeam == CT)
		{
			// CT's have perfect knowledge via their radar
			if (info->hostage->IsAlive())
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
void CSGameState::AllHostagesGone()
{
	for (int i = 0; i < m_hostageCount; i++)
		m_hostage[i].isValid = false;
}

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

#ifndef CS_GAMESTATE_H
#define CS_GAMESTATE_H
#ifdef _WIN32
#pragma once
#endif

class CCSBot;
//class CHostage;

class CSGameState
{
public:
	CSGameState(void);
	CSGameState(CCSBot *owner);

	struct HostageInfo
	{
		CHostage *hostage;
		Vector knownPos;
		bool isValid;
		bool isAlive;
		bool isFree;
	};/* size: 20, cachelines: 1, members: 5 */

	NOBODY void Reset(void);
	// Event handling
	NOBODY void OnEvent(GameEventType event, CBaseEntity *entity, CBaseEntity *other);
	// true if round has been won or lost (but not yet reset)
	NOBODY bool IsRoundOver(void) const;

	enum BombState
	{
		MOVING,		// being carried by a Terrorist
		LOOSE,		// loose on the ground somewhere
		PLANTED,	// planted and ticking
		DEFUSED,	// the bomb has been defused
		EXPLODED,	// the bomb has exploded
	};
	bool IsBombMoving(void) const
	{
		return (m_bombState == MOVING);
	}
	bool IsBombLoose(void) const
	{
		return (m_bombState == LOOSE);
	}
	bool IsBombPlanted(void) const
	{
		return (m_bombState == PLANTED);
	}
	bool IsBombDefused(void) const
	{
		return (m_bombState == DEFUSED);
	}
	bool IsBombExploded(void) const
	{
		return (m_bombState == EXPLODED);
	}
	// we see the loose bomb
	NOBODY void UpdateLooseBomb(const Vector *pos);
	// how long has is been since we saw the loose bomb
	NOBODY float TimeSinceLastSawLooseBomb(void) const;
	// do we know where the loose bomb is
	NOBODY bool IsLooseBombLocationKnown(void) const;
	// we see the bomber
	NOBODY void UpdateBomber(const Vector *pos);
	// how long has is been since we saw the bomber
	NOBODY float TimeSinceLastSawBomber(void) const;
	// we see the planted bomb
	NOBODY void UpdatePlantedBomb(const Vector *pos);
	// do we know where the bomb was planted
	NOBODY bool IsPlantedBombLocationKnown(void) const;
	// mark bombsite as the location of the planted bomb
	NOBODY void MarkBombsiteAsPlanted(int zoneIndex);

	enum { UNKNOWN = -1 };
	// return the zone index of the planted bombsite, or UNKNOWN
	NOBODY int GetPlantedBombsite(void) const;
	// return true if we are currently in the bombsite where the bomb is planted
	NOBODY bool IsAtPlantedBombsite(void) const;
	// return the zone index of the next bombsite to search
	NOBODY int GetNextBombsiteToSearch(void);
	// return true if given bombsite has been cleared
	NOBODY bool IsBombsiteClear(int zoneIndex) const;
	// mark bombsite as clear
	NOBODY void ClearBombsite(int zoneIndex);
	// return where we think the bomb is, or NULL if we don't know
	NOBODY const Vector *GetBombPosition(void) const;

	NOBODY CHostage *GetNearestFreeHostage(Vector *knowPos);
	NOBODY const Vector *GetRandomFreeHostagePosition(void);
	NOBODY bool AreAllHostagesBeingRescued(void);
	NOBODY bool AreAllHostagesGone(void);
	NOBODY void AllHostagesGone(void);
	bool HaveSomeHostagesBeenTaken(void)
	{
		return m_haveSomeHostagesBeenTaken;
	}
	void HostageWasTaken(void)
	{
		m_haveSomeHostagesBeenTaken = true;
	}
	NOBODY CHostage *GetNearestVisibleFreeHostage(void);
	NOBODY unsigned char ValidateHostagePositions(void);
	NOBODY void SetBombState(BombState state);
	BombState GetBombState(void)
	{
		return m_bombState;
	}
	CBaseEntity *GetNearestHostage(void)
	{
		UNTESTED
		// TODO: Not implemented

		//CHostage *pHostage = g_pHostages->GetClosestHostage(m_owner->pev->origin);
		//return GetClassPtr((CHostage *)pHostage->pev);
	}
	NOBODY void InitializeHostageInfo(void);
private:
	CCSBot *m_owner;
	bool m_isRoundOver;
	BombState m_bombState;
	IntervalTimer m_lastSawBomber;
	Vector m_bomberPos;
	IntervalTimer m_lastSawLooseBomb;
	Vector m_looseBombPos;
	bool m_isBombsiteClear[4];
	int m_bombsiteSearchOrder[4];
	int m_bombsiteCount;
	int m_bombsiteSearchIndex;
	int m_plantedBombsite;
	bool m_isPlantedBombPosKnown;
	Vector m_plantedBombPos;
	struct HostageInfo m_hostage[12];
	int m_hostageCount;
	CountdownTimer m_validateInterval;
	bool m_allHostagesRescued;
	bool m_haveSomeHostagesBeenTaken;

};/* size: 348, cachelines: 6, members: 19 */

#endif // CS_GAMESTATE_H

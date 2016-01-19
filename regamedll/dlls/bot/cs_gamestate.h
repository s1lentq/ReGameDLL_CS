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

// This class represents the game state as known by a particular bot
class CSGameState
{
public:
	CSGameState() {};
	CSGameState(CCSBot *owner);

	void Reset(void);
	void OnEvent(GameEventType event, CBaseEntity *entity, CBaseEntity *other);		// Event handling
	bool IsRoundOver(void) const;								// true if round has been won or lost (but not yet reset)

	// bomb defuse scenario
	enum BombState
	{
		MOVING,		// being carried by a Terrorist
		LOOSE,		// loose on the ground somewhere
		PLANTED,	// planted and ticking
		DEFUSED,	// the bomb has been defused
		EXPLODED,	// the bomb has exploded
	};

	bool IsBombMoving(void) const { return (m_bombState == MOVING); }
	bool IsBombLoose(void) const { return (m_bombState == LOOSE); }
	bool IsBombPlanted(void) const { return (m_bombState == PLANTED); }
	bool IsBombDefused(void) const { return (m_bombState == DEFUSED); }
	bool IsBombExploded(void) const { return (m_bombState == EXPLODED); }
	
	void UpdateLooseBomb(const Vector *pos);		// we see the loose bomb	
	float TimeSinceLastSawLooseBomb(void) const;		// how long has is been since we saw the loose bomb
	bool IsLooseBombLocationKnown(void) const;		// do we know where the loose bomb is

	void UpdateBomber(const Vector *pos);			// we see the bomber
	float TimeSinceLastSawBomber(void) const;		// how long has is been since we saw the bomber

	void UpdatePlantedBomb(const Vector *pos);		// we see the planted bomb
	bool IsPlantedBombLocationKnown(void) const;		// do we know where the bomb was planted
	void MarkBombsiteAsPlanted(int zoneIndex);		// mark bombsite as the location of the planted bomb

	enum { UNKNOWN = -1 };	
	int GetPlantedBombsite(void) const;			// return the zone index of the planted bombsite, or UNKNOWN
	bool IsAtPlantedBombsite(void) const;			// return true if we are currently in the bombsite where the bomb is planted

	int GetNextBombsiteToSearch(void);			// return the zone index of the next bombsite to search
	bool IsBombsiteClear(int zoneIndex) const;		// return true if given bombsite has been cleared
	void ClearBombsite(int zoneIndex);			// mark bombsite as clear

	const Vector *GetBombPosition(void) const;		// return where we think the bomb is, or NULL if we don't know

	// hostage rescue scenario
	CHostage *GetNearestFreeHostage(Vector *knowPos = NULL) const;					// return the closest free hostage, and where we think it is (knowPos)
	const Vector *GetRandomFreeHostagePosition(void);
	bool AreAllHostagesBeingRescued(void) const;							// return true if there are no free hostages
	bool AreAllHostagesGone(void) const;								// all hostages have been rescued or are dead
	void AllHostagesGone(void);									// someone told us all the hostages are gone
	bool HaveSomeHostagesBeenTaken(void) const { return m_haveSomeHostagesBeenTaken; }		// return true if one or more hostages have been moved by the CT's
	void HostageWasTaken(void) { m_haveSomeHostagesBeenTaken = true; }				// someone told us a CT is talking to a hostage

	CHostage *GetNearestVisibleFreeHostage(void) const;

	// hostage rescue scenario
	enum ValidateStatusType:uint8
	{
		NO_CHANGE = 0x00,
		HOSTAGE_DIED = 0x01,
		HOSTAGE_GONE = 0x02,
		HOSTAGES_ALL_GONE = 0x04
	};
	ValidateStatusType ValidateHostagePositions(void);	// update our knowledge with what we currently see - returns bitflag events

#ifndef HOOK_GAMEDLL
private:
#endif // HOOK_GAMEDLL

	CCSBot *m_owner;			// who owns this gamestate
	bool m_isRoundOver;			// true if round is over, but no yet reset

	// bomb defuse scenario
	void SetBombState(BombState state);
	BombState GetBombState(void) { return m_bombState; }

	BombState m_bombState;			// what we think the bomb is doing

	IntervalTimer m_lastSawBomber;
	Vector m_bomberPos;

	IntervalTimer m_lastSawLooseBomb;
	Vector m_looseBombPos;

	bool m_isBombsiteClear[4];		// corresponds to zone indices in CCSBotManager
	int m_bombsiteSearchOrder[4];		// randomized order of bombsites to search
	int m_bombsiteCount;
	int m_bombsiteSearchIndex;		// the next step in the search

	int m_plantedBombsite;			// zone index of the bombsite where the planted bomb is

	bool m_isPlantedBombPosKnown;		// if true, we know the exact location of the bomb
	Vector m_plantedBombPos;

	// hostage rescue scenario
	struct HostageInfo
	{
		CHostage *hostage;
		Vector knownPos;
		bool isValid;
		bool isAlive;
		bool isFree;		// not being escorted by a CT
	}
	m_hostage[ MAX_HOSTAGES ];
	int m_hostageCount;					// number of hostages left in map
	CountdownTimer m_validateInterval;
	NOXREF CBaseEntity *GetNearestHostage(void) const;	// return the closest live hostage
	void InitializeHostageInfo(void);			// initialize our knowledge of the number and location of hostages

	bool m_allHostagesRescued;				// if true, so every hostages been is rescued
	bool m_haveSomeHostagesBeenTaken;			// true if a hostage has been moved by a CT (and we've seen it)

};/* size: 348, cachelines: 6, members: 19 */

#endif // CS_GAMESTATE_H

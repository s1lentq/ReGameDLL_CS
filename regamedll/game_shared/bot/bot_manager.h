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

#ifndef BOT_MANAGER_H
#define BOT_MANAGER_H
#ifdef _WIN32
#pragma once
#endif

// STL uses exceptions, but we are not compiling with them - ignore warning
#pragma warning(disable : 4530)

#include <list>
#include "game_shared/GameEvent.h"

#ifndef _WIN32

//#ifndef max
//#define max(a,b) ((a) > (b) ? (a) : (b))
//#endif // max

//#ifndef min
//#define min(a,b) ((a) < (b) ? (a) : (b))
//#endif // min

#endif // _WIN32

class CNavArea;
class CGrenade;

class ActiveGrenade
{
public:
	ActiveGrenade(int weaponID, CGrenade *grenadeEntity);

	void OnEntityGone(void);
	bool IsValid(void) const;
	NOXREF bool IsEntity(CGrenade *grenade) const
	{
		return (grenade == m_entity) ? true : false;
	}
	int GetID(void) const
	{
		return m_id;
	}
	const Vector *GetDetonationPosition(void) const
	{
		return &m_detonationPosition;
	}
	NOXREF const Vector *GetPosition(void) const;

private:
	int m_id;
	CGrenade *m_entity;
	Vector m_detonationPosition;
	float m_dieTimestamp;

};/* size: 24, cachelines: 1, members: 4 */

typedef std::list<ActiveGrenade *> ActiveGrenadeList;

class CBotManager
{
public:
	CBotManager(void);

	virtual void ClientDisconnect(CBasePlayer *pPlayer) = 0;
	virtual BOOL ClientCommand(CBasePlayer *pPlayer, const char *pcmd) = 0;

	virtual void ServerActivate(void) = 0;
	virtual void ServerDeactivate(void) = 0;

	virtual void ServerCommand(const char *pcmd) = 0;
	virtual void AddServerCommand(const char *cmd) = 0;
	virtual void AddServerCommands(void) = 0;

	virtual void RestartRound(void);
	virtual void StartFrame(void);

	// Invoked when event occurs in the game (some events have NULL entity).
	// Events are propogated to all bots.
	virtual void OnEvent(GameEventType event, CBaseEntity *entity = NULL, CBaseEntity *other = NULL);

	// return priority of player (0 = max pri)
	virtual unsigned int GetPlayerPriority(CBasePlayer *player) const = 0;

	// return the filename for this map's "nav" file
	const char *GetNavMapFilename(void) const;

	// add an active grenade to the bot's awareness
	void AddGrenade(int type, CGrenade *grenade);

	// the grenade entity in the world is going away
	void RemoveGrenade(CGrenade *grenade);

	// destroy any invalid active grenades
	NOXREF void ValidateActiveGrenades(void);
	void DestroyAllGrenades(void);

	// return true if line intersects smoke volume
	bool IsLineBlockedBySmoke(const Vector *from, const Vector *to);

	// return true if position is inside a smoke cloud
	bool IsInsideSmokeCloud(const Vector *pos);

#ifdef HOOK_GAMEDLL

	void RestartRound_(void);
	void StartFrame_(void);
	void OnEvent_(GameEventType event, CBaseEntity *entity = NULL, CBaseEntity *other = NULL);

#endif // HOOK_GAMEDLL

private:

#if defined(_WIN32) && defined(HOOK_GAMEDLL)
	// The member m_activeGrenadeList on Windows must be with offset +8
	// on Linux : +4

	int unknown_padding;
#endif // HOOK_GAMEDLL

	// the list of active grenades the bots are aware of
	ActiveGrenadeList m_activeGrenadeList;
//
};/* size: 12, cachelines: 1, members: 2 */

#endif // BOT_MANAGER_H

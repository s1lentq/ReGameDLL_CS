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

#pragma once

// STL uses exceptions, but we are not compiling with them - ignore warning
#pragma warning(disable : 4530)

#include <list>

class CNavArea;
class CGrenade;

class ActiveGrenade
{
public:
	ActiveGrenade(int weaponID, CGrenade *grenadeEntity);

	void OnEntityGone();
	bool IsValid() const;

	bool IsEntity(CGrenade *grenade) const { return (grenade == m_entity) ? true : false; }
	int GetID() const { return m_id; }
	const Vector *GetDetonationPosition() const { return &m_detonationPosition; }
	const Vector *GetPosition() const;

private:
	int m_id;
	CGrenade *m_entity;
	Vector m_detonationPosition;
	float m_dieTimestamp;
};

typedef std::list<ActiveGrenade *> ActiveGrenadeList;

class CBotManager
{
public:
	CBotManager();
	virtual ~CBotManager() {}

	virtual void ClientDisconnect(CBasePlayer *pPlayer) = 0;
	virtual BOOL ClientCommand(CBasePlayer *pPlayer, const char *pcmd) = 0;

	virtual void ServerActivate() = 0;
	virtual void ServerDeactivate() = 0;

	virtual void ServerCommand(const char *pcmd) = 0;
	virtual void AddServerCommand(const char *cmd) = 0;
	virtual void AddServerCommands() = 0;

	virtual void RestartRound();
	virtual void StartFrame();

	// Events are propogated to all bots.
	virtual void OnEvent(GameEventType event, CBaseEntity *pEntity = nullptr, CBaseEntity *pOther = nullptr);	// Invoked when event occurs in the game (some events have NULL entity).
	virtual unsigned int GetPlayerPriority(CBasePlayer *pPlayer) const = 0;										// return priority of player (0 = max pri)

public:
	const char *GetNavMapFilename() const;										// return the filename for this map's "nav" file

	void AddGrenade(int type, CGrenade *grenade);								// add an active grenade to the bot's awareness
	void RemoveGrenade(CGrenade *grenade);										// the grenade entity in the world is going away
	void ValidateActiveGrenades();												// destroy any invalid active grenades
	void DestroyAllGrenades();

	bool IsLineBlockedBySmoke(const Vector *from, const Vector *to);			// return true if line intersects smoke volume
	bool IsInsideSmokeCloud(const Vector *pos);									// return true if position is inside a smoke cloud

private:
	// the list of active grenades the bots are aware of
	ActiveGrenadeList m_activeGrenadeList;
};

GameEventType NameToGameEvent(const char *name);

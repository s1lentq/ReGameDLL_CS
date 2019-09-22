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

#include "voice_common.h"

class CGameRules;
class CBasePlayer;

class IVoiceGameMgrHelper
{
public:
	virtual ~IVoiceGameMgrHelper() {}

	// Called each frame to determine which players are allowed to hear each other.	This overrides
	// whatever squelch settings players have.
	virtual bool CanPlayerHearPlayer(CBasePlayer *pListener, CBasePlayer *pTalker) = 0;
};

// CVoiceGameMgr manages which clients can hear which other clients.
class CVoiceGameMgr
{
public:
	CVoiceGameMgr();
	virtual ~CVoiceGameMgr();

	bool Init(IVoiceGameMgrHelper *pHelper, int maxClients);
	void SetHelper(IVoiceGameMgrHelper *pHelper);

	// Updates which players can hear which other players.
	// If gameplay mode is DM, then only players within the PVS can hear each other.
	// If gameplay mode is teamplay, then only players on the same team can hear each other.
	// Player masks are always applied.
	void Update(double frametime);

	// Called when a new client connects (unsquelches its entity for everyone).
	void ClientConnected(edict_t *pEdict);

	// Called on ClientCommand. Checks for the squelch and unsquelch commands.
	// Returns true if it handled the command.
	bool ClientCommand(CBasePlayer *pPlayer, const char *cmd);

	// Called to determine if the Receiver has muted (blocked) the Sender
	// Returns true if the receiver has blocked the sender
	bool PlayerHasBlockedPlayer(CBasePlayer *pReceiver, CBasePlayer *pSender);

private:
	// Force it to update the client masks.
	void UpdateMasks();

private:
	int m_msgPlayerVoiceMask;
	int m_msgRequestState;
	IVoiceGameMgrHelper *m_pHelper;
	int m_nMaxPlayers;
	double m_UpdateInterval; // How long since the last update.
};

extern cvar_t sv_alltalk;

void VoiceGameMgr_RegisterCVars();
void VoiceServerDebug(const char *pFmt, ...);

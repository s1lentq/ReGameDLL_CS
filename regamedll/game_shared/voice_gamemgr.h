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

#ifndef VOICE_GAMEMGR_H
#define VOICE_GAMEMGR_H
#ifdef _WIN32
#pragma once
#endif

#include "voice_common.h"

/* <111716> ../game_shared/voice_gamemgr.h:23 */
class IVoiceGameMgrHelper
{
public:
	virtual ~IVoiceGameMgrHelper() {}
	NOBODY virtual bool CanPlayerHearPlayer(CBasePlayer *pListener, CBasePlayer *pTalker) = 0;
};/* size: 4, cachelines: 1, members: 1 */

class CVoiceGameMgr
{
public:
	CVoiceGameMgr(void);
	virtual ~CVoiceGameMgr(void);
	NOBODY bool Init(IVoiceGameMgrHelper *pHelper, int maxClients);
	NOBODY void SetHelper(IVoiceGameMgrHelper *pHelper);
	NOBODY void Update(double frametime);
	NOBODY void ClientConnected(edict_t *pEdict);
	NOBODY bool ClientCommand(CBasePlayer *pPlayer, const char *cmd);
	NOBODY bool PlayerHasBlockedPlayer(CBasePlayer *pReceiver, CBasePlayer *pSender);
private:
	NOBODY void UpdateMasks(void);
private:
	int m_msgPlayerVoiceMask;
	int m_msgRequestState;
	IVoiceGameMgrHelper *m_pHelper;
	int m_nMaxPlayers;
	double m_UpdateInterval;
};/* size: 28, cachelines: 1, members: 6 */

#endif // VOICE_GAMEMGR_H

/*
*
*    This program is free software; you can redistribute it and/or modify it
*    under the terms of the GNU General Public License as published by the
*    Free Software Foundation; either version 2 of the License, or (at
*    your option) any later version.
*
*    This program is distributed in the hope that it will be useful, but
*    WITHOUT ANY WARRANTY; without even the implied warranty of
*    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
*    General Public License for more details.
*
*    You should have received a copy of the GNU General Public License
*    along with this program; if not, write to the Free Software Foundation,
*    Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
*
*    In addition, as a special exception, the author gives permission to
*    link the code of this program with the Half-Life Game Engine ("HL
*    Engine") and Modified Game Libraries ("MODs") developed by Valve,
*    L.L.C ("Valve").  You must obey the GNU General Public License in all
*    respects for all of the code used other than the HL Engine and MODs
*    from Valve.  If you modify this file, you may extend this exception
*    to your version of the file, but you are not obligated to do so.  If
*    you do not wish to do so, delete this exception statement from your
*    version.
*
*/

#ifndef BOT_UTIL_H
#define BOT_UTIL_H
#ifdef _WIN32
#pragma once
#endif

#define COS_TABLE_SIZE 256

#define CREATE_FAKE_CLIENT		(*g_engfuncs.pfnCreateFakeClient)
#define GET_USERINFO			(*g_engfuncs.pfnGetInfoKeyBuffer)
#define SET_KEY_VALUE			(*g_engfuncs.pfnSetKeyValue)
#define SET_CLIENT_KEY_VALUE		(*g_engfuncs.pfnSetClientKeyValue)

class CBasePlayer;
class BotProfile;

enum PriorityType
{
	PRIORITY_LOW,
	PRIORITY_MEDIUM,
	PRIORITY_HIGH,
	PRIORITY_UNINTERRUPTABLE
};

/* <504550> ../game_shared/bot/bot_util.h:131 */
class IntervalTimer
{
public:
	IntervalTimer(void)
	{
		m_timestamp = -1.0f;
	}
	/* <4c1587> ../game_shared/bot/bot_util.h:136 */
	NOBODY inline void Reset(void)
	{
		m_timestamp = gpGlobals->time;
	}
	/* <5c4948> ../game_shared/bot/bot_util.h:141 */
	NOBODY inline void Start(void)
	{
		m_timestamp = gpGlobals->time;
	}
	/* <568aac> ../game_shared/bot/bot_util.h:146 */
	NOBODY inline void Invalidate(void)
	{
		m_timestamp = -1.0f;
	}
	/* <5687b3> ../game_shared/bot/bot_util.h:151 */
	NOBODY inline bool HasStarted(void) const
	{
		return (m_timestamp > 0.0f);
	}
	/* <5687d1> ../game_shared/bot/bot_util.h:157 */
	NOBODY inline float GetElapsedTime(void) const
	{
		return (HasStarted()) ? (gpGlobals->time - m_timestamp) : 99999.9f;
	}
	/* <2ff607> ../game_shared/bot/bot_util.h:162 */
	NOBODY inline bool IsLessThen(float duration) const
	{
		return (gpGlobals->time - m_timestamp < duration) ? true : false;
	}
	/* <0> (null):0 */
	NOBODY inline bool IsGreaterThen(float duration) const
	{
		return (gpGlobals->time - m_timestamp > duration) ? true : false;
	}
private:
	float m_timestamp;

};/* size: 4, cachelines: 1, members: 1 */

/* <46f878> ../game_shared/bot/bot_util.h:183 */
class CountdownTimer
{
public:
	CountdownTimer(void)
	{
		m_timestamp = -1.0f;
		m_duration = 0.0f;
	}
	/* <569025> ../game_shared/bot/bot_util.h:189 */
	NOBODY inline void Reset(void)
	{
		m_timestamp = gpGlobals->time + m_duration;
	}
	/* <568aca> ../game_shared/bot/bot_util.h:194 */
	NOBODY inline void Start(float duration)
	{
		m_timestamp = gpGlobals->time + duration;
		m_duration = duration;
	}
	/* <5687b3> ../game_shared/bot/bot_util.h:151 */
	NOBODY inline bool HasStarted(void) const
	{
		return (m_timestamp > 0.0f);
	}
	/* <5c4621> ../game_shared/bot/bot_util.h:200 */
	NOBODY inline void Invalidate(void)
	{
		m_timestamp = -1.0f;
	}
	/* <5c463f> ../game_shared/bot/bot_util.h:210 */
	NOBODY inline bool IsElapsed(void) const
	{
		return (gpGlobals->time > m_timestamp);
	}
private:
	float m_duration;
	float m_timestamp;

};/* size: 8, cachelines: 1, members: 2 */

/* <14ed68> ../game_shared/bot/bot_util.h:224 */
inline bool IsEntityValid(CBaseEntity *entity)
{
	if(entity == NULL)
		return false;

	if(FNullEnt(entity->pev))
		return false;

	if(FStrEq(STRING(entity->pev->netname), ""))
		return false;

	if(entity->pev->flags & FL_DORMANT)
		return false;

	return true;
}

/* <4c0851> ../game_shared/bot/bot_util.h:247 */
inline bool IsIntersecting2D(const Vector &startA, const Vector &endA, const Vector &startB, const Vector &endB, Vector *result = NULL)
{
	float denom = (endA.x - startA.x) * (endB.y - startB.y) - (endA.y - startA.y) * (endB.x - startB.x);
	if (denom == 0.0f)
	{
		return false;
	}
	float numS = (startA.y - startB.y) * (endB.x - startB.x) - (startA.x - startB.x) * (endB.y - startB.y);
	if (numS == 0.0f)
	{
		return true;
	}
	float numT = (startA.y - startB.y) * (endA.x - startA.x) - (startA.x - startB.x) * (endA.y - startA.y);
	float s = numS / denom;
	if (s < 0.0f || s > 1.0f)
	{
		return false;
	}
	float t = numT / denom;
	if (t < 0.0f || t > 1.0f)
	{
		return false;
	}
	if (result)
	{
		*result = startA + s * (endA - startA);
		//*result = startA + s * (endA - startA);
		//(*result).x = startA.x + s * (endA.x - startA.x);
		//(*result).y = startA.y + s * (endA.y - startA.y);
		//(*result).z = startA.z + s * (endA.z - startA.z);
	}
	return true;
}

/* <4700e1> ../game_shared/bot/bot_util.h:294 */
template <
	typename Functor
>
INLINEBODY bool ForEachPlayer(Functor &func)
{
	for(int i = 1; i <= gpGlobals->maxClients; i++)
	{
		CBasePlayer *player = static_cast<CBasePlayer *>(UTIL_PlayerByIndex(i));
		if(!IsEntityValid((CBaseEntity *)player))
			continue;

		if(!player->IsPlayer())
			continue;

		if(func(player) == false)
			return false;
	}
	return true;
}

/* <b59bf> ../game_shared/bot/bot_util.h:317 */
inline bool IsZombieGame(void)
{
#ifdef TERRORSTRIKE
	return true;
#else
	return false;
#endif // TERRORSTRIKE
}

#ifdef HOOK_GAMEDLL

#define s_iBeamSprite (*ps_iBeamSprite)
#define cosTable (*pcosTable)

#endif // HOOK_GAMEDLL

extern short s_iBeamSprite;
extern float cosTable[COS_TABLE_SIZE];

NOBODY bool UTIL_IsNameTaken(const char *name, bool ignoreHumans = false);
NOBODY int UTIL_ClientsInGame(void);
NOBODY int UTIL_ActivePlayersInGame(void);
NOBODY int UTIL_HumansInGame(bool ignoreSpectators);
NOBODY int UTIL_HumansOnTeam(int teamID, bool isAlive = false);
NOBODY int UTIL_BotsInGame(void);
NOBODY bool UTIL_KickBotFromTeam(TeamName kickTeam);
NOBODY bool UTIL_IsTeamAllBots(int team);
NOBODY CBasePlayer *UTIL_GetClosestPlayer(const Vector *pos, float *distance = NULL);
NOBODY CBasePlayer *UTIL_GetClosestPlayer(const Vector *pos, int team, float *distance = NULL);
NOBODY const char *UTIL_GetBotPrefix();
NOBODY void UTIL_ConstructBotNetName(char *name, int nameLength, const BotProfile *profile);
NOBODY bool UTIL_IsVisibleToTeam(const Vector &spot, int team, float maxRange = -1.0f);
CBasePlayer *UTIL_GetLocalPlayer(void);
NOBODY Vector UTIL_ComputeOrigin(entvars_t *pevVars);
NOBODY Vector UTIL_ComputeOrigin(CBaseEntity *pEntity);
NOBODY Vector UTIL_ComputeOrigin(edict_t *pentEdict);
NOBODY void UTIL_DrawBeamFromEnt(int iIndex, Vector vecEnd, int iLifetime, byte bRed, byte bGreen, byte bBlue);
NOBODY void UTIL_DrawBeamPoints(Vector vecStart, Vector vecEnd, int iLifetime, byte bRed, byte bGreen, byte bBlue);
void CONSOLE_ECHO(char *pszMsg, ...);
void CONSOLE_ECHO_LOGGED(char *pszMsg, ...);
void BotPrecache(void);
void InitBotTrig(void);
float BotCOS(float angle);
float BotSIN(float angle);
NOBODY bool IsGameEventAudible(enum GameEventType event, CBaseEntity *entity, CBaseEntity *other, float *range, PriorityType *priority, bool *isHostile);
NOBODY void HintMessageToAllPlayers(const char *message);

#ifdef HOOK_GAMEDLL

typedef CBasePlayer *(*UTIL_GETCLOSE_PLAYER)(const Vector *pos, float *distance);
typedef CBasePlayer *(*UTIL_GETCLOSE_TEAM)(const Vector *pos, int team, float *distance);

typedef Vector (*UTIL_CUMPUTE_ENTVARS)(entvars_t *pevVars);
typedef Vector (*UTIL_CUMPUTE_CBASE)(CBaseEntity *pEntity);
typedef Vector (*UTIL_CUMPUTE_EDICT)(edict_t *pentEdict);

#endif // HOOK_GAMEDLL

#endif // BOT_UTIL_H

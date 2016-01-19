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

#define COS_TABLE_SIZE		256

#define RAD_TO_DEG(deg)		((deg) * 180.0 / M_PI)
#define DEG_TO_RAD(rad)		((rad) * M_PI / 180.0)

#define SIGN(num)		(((num) < 0) ? -1 : 1)
#define ABS(num)		(SIGN(num) * (num))

class CBasePlayer;
class BotProfile;

enum PriorityType
{
	PRIORITY_LOW, PRIORITY_MEDIUM, PRIORITY_HIGH, PRIORITY_UNINTERRUPTABLE
};

// Simple class for tracking intervals of game time

/* <504550> ../game_shared/bot/bot_util.h:131 */
class IntervalTimer
{
public:
	IntervalTimer(void)
	{
		m_timestamp = -1.0f;
	}
	/* <4c1587> ../game_shared/bot/bot_util.h:136 */
	void Reset(void)
	{
		m_timestamp = gpGlobals->time;
	}
	/* <5c4948> ../game_shared/bot/bot_util.h:141 */
	void Start(void)
	{
		m_timestamp = gpGlobals->time;
	}
	/* <568aac> ../game_shared/bot/bot_util.h:146 */
	void Invalidate(void)
	{
		m_timestamp = -1.0f;
	}
	/* <5687b3> ../game_shared/bot/bot_util.h:151 */
	bool HasStarted(void) const
	{
		return (m_timestamp > 0.0f);
	}
	// if not started, elapsed time is very large
	/* <5687d1> ../game_shared/bot/bot_util.h:157 */
	float GetElapsedTime(void) const
	{
		return (HasStarted()) ? (gpGlobals->time - m_timestamp) : 99999.9f;
	}
	/* <2ff607> ../game_shared/bot/bot_util.h:162 */
	bool IsLessThen(float duration) const
	{
		return (gpGlobals->time - m_timestamp < duration) ? true : false;
	}
	/* <0> (null):0 */
	bool IsGreaterThen(float duration) const
	{
		return (gpGlobals->time - m_timestamp > duration) ? true : false;
	}

private:
	float m_timestamp;

};/* size: 4, cachelines: 1, members: 1 */

// Simple class for counting down a short interval of time

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
	void Reset(void)
	{
		m_timestamp = gpGlobals->time + m_duration;
	}
	/* <568aca> ../game_shared/bot/bot_util.h:194 */
	void Start(float duration)
	{
		m_timestamp = gpGlobals->time + duration;
		m_duration = duration;
	}
	/* <5687b3> ../game_shared/bot/bot_util.h:151 */
	bool HasStarted(void) const
	{
		return (m_timestamp > 0.0f);
	}
	/* <5c4621> ../game_shared/bot/bot_util.h:200 */
	void Invalidate(void)
	{
		m_timestamp = -1.0f;
	}
	/* <5c463f> ../game_shared/bot/bot_util.h:210 */
	bool IsElapsed(void) const
	{
		return (gpGlobals->time > m_timestamp);
	}

private:
	float m_duration;
	float m_timestamp;

};/* size: 8, cachelines: 1, members: 2 */

// Return true if the given entity is valid

/* <14ed68> ../game_shared/bot/bot_util.h:224 */
inline bool IsEntityValid(CBaseEntity *entity)
{
	if (entity == NULL)
		return false;

	if (FNullEnt(entity->pev))
		return false;

	if (FStrEq(STRING(entity->pev->netname), ""))
		return false;

	if (entity->pev->flags & FL_DORMANT)
		return false;

	return true;
}

// Given two line segments: startA to endA, and startB to endB, return true if they intesect
// and put the intersection point in "result".
// Note that this computes the intersection of the 2D (x,y) projection of the line segments.

/* <4c0851> ../game_shared/bot/bot_util.h:247 */
inline bool IsIntersecting2D(const Vector &startA, const Vector &endA, const Vector &startB, const Vector &endB, Vector *result = NULL)
{
	float denom = (endA.x - startA.x) * (endB.y - startB.y) - (endA.y - startA.y) * (endB.x - startB.x);
	if (denom == 0.0f)
	{
		// parallel
		return false;
	}

	float numS = (startA.y - startB.y) * (endB.x - startB.x) - (startA.x - startB.x) * (endB.y - startB.y);
	if (numS == 0.0f)
	{
		// coincident
		return true;
	}

	float numT = (startA.y - startB.y) * (endA.x - startA.x) - (startA.x - startB.x) * (endA.y - startA.y);
	float s = numS / denom;
	if (s < 0.0f || s > 1.0f)
	{
		// intersection is not within line segment of startA to endA
		return false;
	}

	float t = numT / denom;
	if (t < 0.0f || t > 1.0f)
	{
		// intersection is not within line segment of startB to endB
		return false;
	}

	// compute intesection point
	if (result)
	{
		*result = startA + s * (endA - startA);
	}
	return true;
}

// Iterate over all active players in the game, invoking functor on each.
// If functor returns false, stop iteration and return false.

/* <4700e1> ../game_shared/bot/bot_util.h:294 */
template <typename Functor>
bool ForEachPlayer(Functor &func)
{
	for (int i = 1; i <= gpGlobals->maxClients; ++i)
	{
		CBasePlayer *player = static_cast<CBasePlayer *>(UTIL_PlayerByIndex(i));
		if (!IsEntityValid((CBaseEntity *)player))
			continue;

		if (!player->IsPlayer())
			continue;

		if (func(player) == false)
			return false;
	}

	return true;
}

// For zombie game

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

#define cv_bot_traceview (*pcv_bot_traceview)
#define cv_bot_stop (*pcv_bot_stop)
#define cv_bot_show_nav (*pcv_bot_show_nav)
#define cv_bot_show_danger (*pcv_bot_show_danger)
#define cv_bot_nav_edit (*pcv_bot_nav_edit)
#define cv_bot_nav_zdraw (*pcv_bot_nav_zdraw)
#define cv_bot_walk (*pcv_bot_walk)
#define cv_bot_difficulty (*pcv_bot_difficulty)
#define cv_bot_debug (*pcv_bot_debug)
#define cv_bot_quicksave (*pcv_bot_quicksave)
#define cv_bot_quota (*pcv_bot_quota)
#define cv_bot_quota_match (*pcv_bot_quota_match)
#define cv_bot_prefix (*pcv_bot_prefix)
#define cv_bot_allow_rogues (*pcv_bot_allow_rogues)
#define cv_bot_allow_pistols (*pcv_bot_allow_pistols)
#define cv_bot_allow_shotguns (*pcv_bot_allow_shotguns)
#define cv_bot_allow_sub_machine_guns (*pcv_bot_allow_sub_machine_guns)
#define cv_bot_allow_rifles (*pcv_bot_allow_rifles)
#define cv_bot_allow_machine_guns (*pcv_bot_allow_machine_guns)
#define cv_bot_allow_grenades (*pcv_bot_allow_grenades)
#define cv_bot_allow_snipers (*pcv_bot_allow_snipers)
#define cv_bot_allow_shield (*pcv_bot_allow_shield)
#define cv_bot_join_team (*pcv_bot_join_team)
#define cv_bot_join_after_player (*pcv_bot_join_after_player)
#define cv_bot_auto_vacate (*pcv_bot_auto_vacate)
#define cv_bot_zombie (*pcv_bot_zombie)
#define cv_bot_defer_to_human (*pcv_bot_defer_to_human)
#define cv_bot_chatter (*pcv_bot_chatter)
#define cv_bot_profile_db (*pcv_bot_profile_db)

#endif // HOOK_GAMEDLL

extern short s_iBeamSprite;
extern float cosTable[COS_TABLE_SIZE];

extern cvar_t cv_bot_traceview;
extern cvar_t cv_bot_stop;
extern cvar_t cv_bot_show_nav;
extern cvar_t cv_bot_show_danger;
extern cvar_t cv_bot_nav_edit;
extern cvar_t cv_bot_nav_zdraw;
extern cvar_t cv_bot_walk;
extern cvar_t cv_bot_difficulty;
extern cvar_t cv_bot_debug;
extern cvar_t cv_bot_quicksave;
extern cvar_t cv_bot_quota;
extern cvar_t cv_bot_quota_match;
extern cvar_t cv_bot_prefix;
extern cvar_t cv_bot_allow_rogues;
extern cvar_t cv_bot_allow_pistols;
extern cvar_t cv_bot_allow_shotguns;
extern cvar_t cv_bot_allow_sub_machine_guns;
extern cvar_t cv_bot_allow_rifles;
extern cvar_t cv_bot_allow_machine_guns;
extern cvar_t cv_bot_allow_grenades;
extern cvar_t cv_bot_allow_snipers;
extern cvar_t cv_bot_allow_shield;
extern cvar_t cv_bot_join_team;
extern cvar_t cv_bot_join_after_player;
extern cvar_t cv_bot_auto_vacate;
extern cvar_t cv_bot_zombie;
extern cvar_t cv_bot_defer_to_human;
extern cvar_t cv_bot_chatter;
extern cvar_t cv_bot_profile_db;

#define IS_ALIVE true
int UTIL_HumansOnTeam(int teamID, bool isAlive = false);

#define IGNORE_SPECTATORS true
int UTIL_HumansInGame(bool ignoreSpectators = false);

bool UTIL_IsNameTaken(const char *name, bool ignoreHumans = false);
int UTIL_ClientsInGame(void);
int UTIL_ActivePlayersInGame(void);
int UTIL_BotsInGame(void);
bool UTIL_KickBotFromTeam(TeamName kickTeam);
bool UTIL_IsTeamAllBots(int team);
CBasePlayer *UTIL_GetClosestPlayer(const Vector *pos, float *distance = NULL);
CBasePlayer *UTIL_GetClosestPlayer(const Vector *pos, int team, float *distance = NULL);
const char *UTIL_GetBotPrefix();
void UTIL_ConstructBotNetName(char *name, int nameLength, const BotProfile *profile);
bool UTIL_IsVisibleToTeam(const Vector &spot, int team, float maxRange = -1.0f);
CBasePlayer *UTIL_GetLocalPlayer(void);
NOXREF Vector UTIL_ComputeOrigin(entvars_t *pevVars);
NOXREF Vector UTIL_ComputeOrigin(CBaseEntity *pEntity);
NOXREF Vector UTIL_ComputeOrigin(edict_t *pentEdict);
NOXREF void UTIL_DrawBeamFromEnt(int iIndex, Vector vecEnd, int iLifetime, byte bRed, byte bGreen, byte bBlue);
void UTIL_DrawBeamPoints(Vector vecStart, Vector vecEnd, int iLifetime, byte bRed, byte bGreen, byte bBlue);

// Echos text to the console, and prints it on the client's screen.  This is NOT tied to the developer cvar.
// If you are adding debugging output in cstrike, use UTIL_DPrintf() (debug.h) instead.
void CONSOLE_ECHO(char *pszMsg, ...);
void CONSOLE_ECHO_LOGGED(char *pszMsg, ...);

void BotPrecache(void);
void InitBotTrig(void);
float BotCOS(float angle);
float BotSIN(float angle);
bool IsGameEventAudible(enum GameEventType event, CBaseEntity *entity, CBaseEntity *other, float *range, PriorityType *priority, bool *isHostile);
void HintMessageToAllPlayers(const char *message);

#ifdef HOOK_GAMEDLL

typedef CBasePlayer *(*UTIL_GETCLOSE_PLAYER)(const Vector *pos, float *distance);
typedef CBasePlayer *(*UTIL_GETCLOSE_TEAM)(const Vector *pos, int team, float *distance);

typedef Vector (*UTIL_CUMPUTE_ENTVARS)(entvars_t *pevVars);
typedef Vector (*UTIL_CUMPUTE_CBASE)(CBaseEntity *pEntity);
typedef Vector (*UTIL_CUMPUTE_EDICT)(edict_t *pentEdict);

#endif // HOOK_GAMEDLL

#endif // BOT_UTIL_H

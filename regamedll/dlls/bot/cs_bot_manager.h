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

#ifndef CS_BOT_MANAGER_H
#define CS_BOT_MANAGER_H
#ifdef _WIN32
#pragma once
#endif

#ifdef HOOK_GAMEDLL

#define TheBots (*pTheBots)

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

#define m_flNextCVarCheck (*pm_flNextCVarCheck)
#define m_isMapDataLoaded (*pm_isMapDataLoaded)

#define m_isLearningMap (*pm_isLearningMap)
#define m_isAnalysisRequested (*pm_isAnalysisRequested)

#endif // HOOK_GAMEDLL

extern CBotManager *TheBots;

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

class CCSBotManager: public CBotManager
{
public:
	CCSBotManager(void);
public:
	NOBODY virtual void ClientDisconnect(CBasePlayer *pPlayer);
	NOBODY virtual BOOL ClientCommand(CBasePlayer *pPlayer, const char *pcmd);

	NOBODY virtual void ServerActivate(void);
	NOBODY virtual void ServerDeactivate(void);

	NOBODY virtual void ServerCommand(const char *pcmd);
	NOBODY virtual void AddServerCommand(const char *cmd);
	NOBODY virtual void AddServerCommands(void);

	NOBODY virtual void RestartRound(void);
	NOBODY virtual void StartFrame(void);

	virtual void OnEvent(GameEventType event, CBaseEntity *entity, CBaseEntity *other);
	NOBODY virtual unsigned int GetPlayerPriority(CBasePlayer *player) const;
	NOBODY virtual bool IsImportantPlayer(CBasePlayer *player);

#ifdef HOOK_GAMEDLL

	void ClientDisconnect_(CBasePlayer *pPlayer);
	BOOL ClientCommand_(CBasePlayer *pPlayer, const char *pcmd);
	void ServerActivate_(void);
	void ServerDeactivate_(void);
	void ServerCommand_(const char *pcmd);
	void AddServerCommand_(const char *cmd);
	void AddServerCommands_(void);
	void RestartRound_(void);
	void StartFrame_(void);
	void OnEvent_(GameEventType event, CBaseEntity *entity, CBaseEntity *other);
	unsigned int GetPlayerPriority_(CBasePlayer *player) const;
	bool IsImportantPlayer_(CBasePlayer *player);

#endif // HOOK_GAMEDLL
public:
	NOBODY void ValidateMapData(void);
	bool IsLearningMap(void)
	{
		return m_isLearningMap;
	}
	void SetLearningMapFlag(void)
	{
		m_isLearningMap = true;
	}
	bool IsAnalysisRequested(void)
	{
		return m_isAnalysisRequested;
	}
	void RequestAnalysis(void)
	{
		m_isAnalysisRequested = true;
	}
	void AckAnalysisRequest(void)
	{
		m_isAnalysisRequested = false;
	}
	BotDifficultyType GetDifficultyLevel(void)
	{
		if (cv_bot_difficulty.value < 0.9f)
			return BOT_EASY;

		if (cv_bot_difficulty.value < 1.9f)
			return BOT_NORMAL;

		if (cv_bot_difficulty.value < 2.9f)
			return BOT_HARD;

		return BOT_EXPERT;
	}

	enum GameScenarioType
	{
		SCENARIO_DEATHMATCH,
		SCENARIO_DEFUSE_BOMB,
		SCENARIO_RESCUE_HOSTAGES,
		SCENARIO_ESCORT_VIP,
	};
	GameScenarioType GetScenario(void)
	{
		return m_gameScenario;
	}

	enum { MAX_ZONES = 4, MAX_ZONE_NAV_AREAS = 16 };
	struct Zone
	{
		CBaseEntity *m_entity;
		CNavArea *m_area[MAX_ZONE_NAV_AREAS];
		int m_areaCount;
		Vector m_center;
		bool m_isLegacy;
		int m_index;
		Extent m_extent;
	};/* size: 116, cachelines: 2, members: 7 */

	const Zone *GetZone(int i) const
	{
		return &m_zone[i];
	}
	NOBODY const Zone *GetZone(const Vector *pos) const;
	NOBODY const Zone *GetClosestZone(const Vector *pos) const;
	const Zone *GetClosestZone(const CBaseEntity *entity) const
	{
		return GetClosestZone(&entity->pev->origin);
	}
	template<
		typename CostFunctor
	>
	const Zone *GetClosestZone(CNavArea *startArea, CostFunctor costFunc, float *travelDistance = NULL) const
	{
		const Zone *closeZone = NULL;
		float closeDist = 99999999.9f;

		if (startArea == NULL)
			return NULL;

		for (int i = 0; i < m_zoneCount; i++)
		{
			if (m_zone[i].m_areaCount == 0)
				continue;

			if (m_zone[i].m_isBlocked)
				continue;

			float dist = NavAreaTravelDistance(startArea, m_zone[i].m_area[0], costFunc);
			if (dist >= 0.0f && dist < closeDist)
			{
				closeZone = &m_zone[i];
				closeDist = dist;
			}
		}

		if (travelDistance)
			*travelDistance = closeDist;

		return closeZone;
	}
	int GetZoneCount(void) const
	{
		return m_zoneCount;
	}
	NOBODY const Vector *GetRandomPositionInZone(const Zone *zone) const;
	NOBODY CNavArea *GetRandomAreaInZone(const Zone *zone) const;

	// pick a zone at random and return it
	const Zone *GetRandomZone(void) const
	{
		if (!m_zoneCount)
			return NULL;

		return &m_zone[ RANDOM_LONG(0, m_zoneCount - 1) ];
	}
	// returns true if bomb has been planted
	bool IsBombPlanted(void) const
	{
		return m_isBombPlanted;
	}
	// return time bomb was planted
	float GetBombPlantTimestamp(void)
	{
		return m_bombPlantTimestamp;
	}
	// return true if it's ok to try to plant bomb
	bool IsTimeToPlantBomb(void) const
	{
		return (gpGlobals->time >= m_earliestBombPlantTimestamp);
	}
	CBasePlayer *GetBombDefuser(void) const
	{
		return m_bombDefuser;
	}
	NOBODY float GetBombTimeLeft(void) const;
	// return the bomb if it is loose on the ground
	CBaseEntity *GetLooseBomb(void)
	{
		return m_looseBomb;
	}
	// return area that bomb is in/near
	CNavArea *GetLooseBombArea(void) const
	{
		return m_looseBombArea;
	}
	void SetLooseBomb(CBaseEntity *bomb);
	NOBODY float GetRadioMessageTimestamp(GameEventType event, int teamID);
	NOBODY float GetRadioMessageInterval(GameEventType event, int teamID);
	NOBODY void SetRadioMessageTimestamp(GameEventType event, int teamID);
	NOBODY void ResetRadioMessageTimestamps(void);

	// return the last time anyone has seen an enemy
	float GetLastSeenEnemyTimestamp(void) const
	{
		return m_lastSeenEnemyTimestamp;
	}
	void SetLastSeenEnemyTimestamp(void)
	{
		m_lastSeenEnemyTimestamp = gpGlobals->time;
	}
	float GetRoundStartTime(void) const
	{
		return m_roundStartTimestamp;
	}
	// return the elapsed time since the current round began
	float GetElapsedRoundTime(void) const
	{
		return gpGlobals->time - m_roundStartTimestamp;
	}
	bool AllowRogues(void) const
	{
		return cv_bot_allow_rogues.value != 0;
	}
	bool AllowPistols(void) const
	{
		return cv_bot_allow_pistols.value != 0;
	}
	bool AllowShotguns(void) const
	{
		return cv_bot_allow_shotguns.value != 0;
	}
	bool AllowSubMachineGuns(void) const
	{
		return cv_bot_allow_sub_machine_guns.value != 0;
	}
	bool AllowRifles(void) const
	{
		return cv_bot_allow_rifles.value != 0;
	}
	bool AllowMachineGuns(void) const
	{
		return cv_bot_allow_machine_guns.value != 0;
	}
	bool AllowGrenades(void) const
	{
		return cv_bot_allow_grenades.value != 0;
	}
	bool AllowSnipers(void) const
	{
		return cv_bot_allow_snipers.value != 0;
	}
	bool AllowTacticalShield(void) const
	{
		return cv_bot_allow_shield.value != 0;
	}
	bool AllowFriendlyFireDamage(void) const
	{
		return friendlyfire.value != 0;
	}
	NOBODY bool IsWeaponUseable(CBasePlayerItem *item) const;
	bool IsDefenseRushing(void) const
	{
		return m_isDefenseRushing;
	}
	NOBODY bool IsOnDefense(CBasePlayer *player) const;
	NOBODY bool IsOnOffense(CBasePlayer *player) const;
	bool IsRoundOver(void) const
	{
		return m_isRoundOver;
	}
	unsigned int GetNavPlace(void) const
	{
		return m_navPlace;
	}
	void SetNavPlace(unsigned int place)
	{
		m_navPlace = place;
	}

	enum SkillType
	{
		LOW,
		AVERAGE,
		HIGH,
		RANDOM
	};
	NOXREF NOBODY const char *GetRandomBotName(SkillType skill);

	NOBODY static void MonitorBotCVars(void);
	NOBODY static void MaintainBotQuota(void);
	NOBODY static bool AddBot(BotProfile *profile, BotProfileTeamType team);
	NOBODY static bool BotAddCommand(BotProfileTeamType team, bool isFromConsole);

#ifndef HOOK_GAMEDLL
private:
#else
public:
#endif // HOOK_GAMEDLL
	static float m_flNextCVarCheck;
	static bool m_isMapDataLoaded;
	static bool m_isLearningMap;
	static bool m_isAnalysisRequested;
#ifdef HOOK_GAMEDLL
private:
#endif // HOOK_GAMEDLL

	GameScenarioType m_gameScenario;// TODO: must be on Windows offsetof - 16
	Zone m_zone[ MAX_ZONES ];
	int m_zoneCount;
	bool m_isBombPlanted;
	float m_bombPlantTimestamp;
	float m_earliestBombPlantTimestamp;
	CBasePlayer *m_bombDefuser;
	EHANDLE m_looseBomb;
	CNavArea *m_looseBombArea;
	bool m_isRoundOver;
	float m_radioMsgTimestamp[24][2];
	float m_lastSeenEnemyTimestamp;
	float m_roundStartTimestamp;
	bool m_isDefenseRushing;

	static NavEditCmdType m_editCmd;

	unsigned int m_navPlace;
	CountdownTimer m_respawnTimer;
	bool m_isRespawnStarted;
	bool m_canRespawn;
	bool m_bServerActive;

};/* size: 736, cachelines: 12, members: 25 */

/* <2e81a8> ../cstrike/dlls/bot/cs_bot_manager.h:24 */
NOXREF inline int OtherTeam(int team)
{
	return (team == TERRORIST) ? CT : TERRORIST;
}

/* <111bd2> ../cstrike/dlls/bot/cs_bot_manager.h:266 */
inline CCSBotManager *TheCSBots(void)
{
	return reinterpret_cast<CCSBotManager *>(TheBots);
}

NOBODY void PrintAllEntities(void);
NOBODY void UTIL_DrawBox(Extent *extent, int lifetime, int red, int green, int blue);

#ifdef HOOK_GAMEDLL

typedef const CCSBotManager::Zone *(CCSBotManager::*GET_ZONE_INT)(int) const;
typedef const CCSBotManager::Zone *(CCSBotManager::*GET_ZONE_VECTOR)(const Vector *pos) const;

#endif // HOOK_GAMEDLL

#endif // CS_BOT_MANAGER_H

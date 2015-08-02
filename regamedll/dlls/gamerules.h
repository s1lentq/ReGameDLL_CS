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

#ifndef GAMERULES_H
#define GAMERULES_H
#ifdef _WIN32
#pragma once
#endif

#include "game_shared/voice_gamemgr.h"

#define COM_TOKEN_LEN		1500

#define MAX_RULE_BUFFER		1024
#define MAX_VOTE_MAPS		100
#define ITEM_RESPAWN_TIME	30
#define MAX_VIP_QUEUES		5

enum
{
	GR_NONE = 0,
	GR_WEAPON_RESPAWN_YES,
	GR_WEAPON_RESPAWN_NO,
	GR_AMMO_RESPAWN_YES,
	GR_AMMO_RESPAWN_NO,
	GR_ITEM_RESPAWN_YES,
	GR_ITEM_RESPAWN_NO,
	GR_PLR_DROP_GUN_ALL,
	GR_PLR_DROP_GUN_ACTIVE,
	GR_PLR_DROP_GUN_NO,
	GR_PLR_DROP_AMMO_ALL,
	GR_PLR_DROP_AMMO_ACTIVE,
	GR_PLR_DROP_AMMO_NO,
};

enum
{
	GR_NOTTEAMMATE = 0,
	GR_TEAMMATE,
	GR_ENEMY,
	GR_ALLY,
	GR_NEUTRAL,
};

class CItem;

/* <166901> ../cstrike/dlls/gamerules.h:86 */
class CGameRules
{
public:
	virtual void RefreshSkillData(void);
	virtual void Think(void) = 0;
	virtual BOOL IsAllowedToSpawn(CBaseEntity *pEntity) = 0;
	virtual BOOL FAllowFlashlight(void) = 0;
	virtual BOOL FShouldSwitchWeapon(CBasePlayer *pPlayer, CBasePlayerItem *pWeapon) = 0;
	virtual BOOL GetNextBestWeapon(CBasePlayer *pPlayer, CBasePlayerItem *pCurrentWeapon) = 0;
	virtual BOOL IsMultiplayer(void) = 0;
	virtual BOOL IsDeathmatch(void) = 0;
	virtual BOOL IsTeamplay(void)
	{
		return FALSE;
	}
	virtual BOOL IsCoOp(void) = 0;
	virtual const char *GetGameDescription(void)
	{
		return "Counter-Strike";
	}
	virtual BOOL ClientConnected(edict_t *pEntity, const char *pszName, const char *pszAddress, char *szRejectReason) = 0;
	virtual void InitHUD(CBasePlayer *pl) = 0;
	virtual void ClientDisconnected(edict_t *pClient) = 0;
	virtual void UpdateGameMode(CBasePlayer *pPlayer) {}
	virtual float FlPlayerFallDamage(CBasePlayer *pPlayer) = 0;
	virtual BOOL FPlayerCanTakeDamage(CBasePlayer *pPlayer, CBaseEntity *pAttacker)
	{
		return TRUE;
	}
	virtual BOOL ShouldAutoAim(CBasePlayer *pPlayer, edict_t *target)
	{
		return TRUE;
	}
	virtual void PlayerSpawn(CBasePlayer *pPlayer) = 0;
	virtual void PlayerThink(CBasePlayer *pPlayer) = 0;
	virtual BOOL FPlayerCanRespawn(CBasePlayer *pPlayer) = 0;
	virtual float FlPlayerSpawnTime(CBasePlayer *pPlayer) = 0;
	NOBODY virtual edict_t *GetPlayerSpawnSpot(CBasePlayer *pPlayer);
	virtual BOOL AllowAutoTargetCrosshair(void)
	{
		return TRUE;
	}
	virtual BOOL ClientCommand_DeadOrAlive(CBasePlayer *pPlayer, const char *pcmd)
	{
		return FALSE;
	}
	virtual BOOL ClientCommand(CBasePlayer *pPlayer, const char *pcmd)
	{
		return FALSE;
	}
	virtual void ClientUserInfoChanged(CBasePlayer *pPlayer, char *infobuffer) {}
	virtual int IPointsForKill(CBasePlayer *pAttacker, CBasePlayer *pKilled) = 0;
	virtual void PlayerKilled(CBasePlayer *pVictim, entvars_t *pKiller, entvars_t *pInflictor) = 0;
	virtual void DeathNotice(CBasePlayer *pVictim, entvars_t *pKiller, entvars_t *pevInflictor) = 0;
	NOBODY virtual BOOL CanHavePlayerItem(CBasePlayer *pPlayer, CBasePlayerItem *pItem);
	virtual void PlayerGotWeapon(CBasePlayer *pPlayer, CBasePlayerItem *pWeapon) = 0;
	virtual int WeaponShouldRespawn(CBasePlayerItem *pWeapon) = 0;
	virtual float FlWeaponRespawnTime(CBasePlayerItem *pWeapon) = 0;
	virtual float FlWeaponTryRespawn(CBasePlayerItem *pWeapon) = 0;
	virtual Vector VecWeaponRespawnSpot(CBasePlayerItem *pWeapon) = 0;
	virtual BOOL CanHaveItem(CBasePlayer *pPlayer, CItem *pItem) = 0;
	virtual void PlayerGotItem(CBasePlayer *pPlayer, CItem *pItem) = 0;
	virtual int ItemShouldRespawn(CItem *pItem) = 0;
	virtual float FlItemRespawnTime(CItem *pItem) = 0;
	virtual Vector VecItemRespawnSpot(CItem *pItem) = 0;
	virtual BOOL CanHaveAmmo(CBasePlayer *pPlayer, const char *pszAmmoName, int iMaxCarry);
	virtual void PlayerGotAmmo(CBasePlayer *pPlayer, char *szName, int iCount) = 0;
	virtual int AmmoShouldRespawn(CBasePlayerAmmo *pAmmo) = 0;
	virtual float FlAmmoRespawnTime(CBasePlayerAmmo *pAmmo) = 0;
	virtual Vector VecAmmoRespawnSpot(CBasePlayerAmmo *pAmmo) = 0;
	virtual float FlHealthChargerRechargeTime(void) = 0;
	virtual float FlHEVChargerRechargeTime(void)
	{
		return 0.0f;
	}
	virtual int DeadPlayerWeapons(CBasePlayer *pPlayer) = 0;
	virtual int DeadPlayerAmmo(CBasePlayer *pPlayer) = 0;
	virtual const char *GetTeamID(CBaseEntity *pEntity) = 0;
	virtual int PlayerRelationship(CBasePlayer *pPlayer, CBaseEntity *pTarget) = 0;
	virtual int GetTeamIndex(const char *pTeamName)
	{
		return -1;
	}
	virtual const char *GetIndexedTeamName(int teamIndex)
	{
		return "";
	}
	virtual BOOL IsValidTeam(const char *pTeamName)
	{
		return TRUE;
	}
	virtual void ChangePlayerTeam(CBasePlayer *pPlayer, const char *pTeamName, BOOL bKill, BOOL bGib) {}
	virtual const char *SetDefaultPlayerTeam(CBasePlayer *pPlayer)
	{
		return "";
	}
	virtual BOOL PlayTextureSounds(void)
	{
		return TRUE;
	}
	virtual BOOL FAllowMonsters(void) = 0;
	virtual void EndMultiplayerGame(void) {}
	virtual BOOL IsFreezePeriod(void)
	{
		return m_bFreezePeriod;
	}
	virtual void ServerDeactivate(void) {}
	virtual void CheckMapConditions(void) {}

#ifdef HOOK_GAMEDLL

	void RefreshSkillData_(void);
	NOBODY edict_t *GetPlayerSpawnSpot_(CBasePlayer *pPlayer);
	NOBODY BOOL CanHavePlayerItem_(CBasePlayer *pPlayer, CBasePlayerItem *pItem);
	BOOL CanHaveAmmo_(CBasePlayer *pPlayer, const char *pszAmmoName, int iMaxCarry);

#endif // HOOK_GAMEDLL

public:
	//int **_vptr.CGameRules;
	BOOL m_bFreezePeriod;
	BOOL m_bBombDropped;
};/* size: 12, cachelines: 1, members: 3 */

class CHalfLifeRules: public CGameRules
{
public:
	CHalfLifeRules(void);
	virtual void Think(void);
	virtual BOOL IsAllowedToSpawn(CBaseEntity *pEntity);
	virtual BOOL FAllowFlashlight(void)
	{
		return TRUE;
	};
	virtual BOOL FShouldSwitchWeapon(CBasePlayer *pPlayer, CBasePlayerItem *pWeapon);
	virtual BOOL GetNextBestWeapon(CBasePlayer *pPlayer, CBasePlayerItem *pCurrentWeapon);
	virtual BOOL IsMultiplayer(void);
	virtual BOOL IsDeathmatch(void);
	virtual BOOL IsCoOp(void);
	virtual BOOL ClientConnected(edict_t *pEntity, const char *pszName, const char *pszAddress, char szRejectReason[128]);
	virtual void InitHUD(CBasePlayer *pl);
	virtual void ClientDisconnected(edict_t *pClient);
	virtual float FlPlayerFallDamage(CBasePlayer *pPlayer);
	virtual void PlayerSpawn(CBasePlayer *pPlayer);
	virtual void PlayerThink(CBasePlayer *pPlayer);
	virtual BOOL FPlayerCanRespawn(CBasePlayer *pPlayer);
	virtual float FlPlayerSpawnTime(CBasePlayer *pPlayer);
	virtual edict_t *GetPlayerSpawnSpot(CBasePlayer *pPlayer);
	virtual BOOL AllowAutoTargetCrosshair(void);
	virtual int IPointsForKill(CBasePlayer *pAttacker, CBasePlayer *pKilled);
	virtual void PlayerKilled(CBasePlayer *pVictim, entvars_t *pKiller, entvars_t *pInflictor);
	virtual void DeathNotice(CBasePlayer *pVictim, entvars_t *pKiller, entvars_t *pInflictor);
	virtual void PlayerGotWeapon(CBasePlayer *pPlayer, CBasePlayerItem *pWeapon);
	virtual int WeaponShouldRespawn(CBasePlayerItem *pWeapon);
	virtual float FlWeaponRespawnTime(CBasePlayerItem *pWeapon);
	virtual float FlWeaponTryRespawn(CBasePlayerItem *pWeapon);
	virtual Vector VecWeaponRespawnSpot(CBasePlayerItem *pWeapon);
	virtual BOOL CanHaveItem(CBasePlayer *pPlayer, CItem *pItem);
	virtual void PlayerGotItem(CBasePlayer *pPlayer, CItem *pItem);
	virtual int ItemShouldRespawn(CItem *pItem);
	virtual float FlItemRespawnTime(CItem *pItem);
	virtual Vector VecItemRespawnSpot(CItem *pItem);
	virtual void PlayerGotAmmo(CBasePlayer *pPlayer, char *szName, int iCount);
	virtual int AmmoShouldRespawn(CBasePlayerAmmo *pAmmo);
	virtual float FlAmmoRespawnTime(CBasePlayerAmmo *pAmmo);
	virtual Vector VecAmmoRespawnSpot(CBasePlayerAmmo *pAmmo);
	virtual float FlHealthChargerRechargeTime(void);
	virtual int DeadPlayerWeapons(CBasePlayer *pPlayer);
	virtual int DeadPlayerAmmo(CBasePlayer *pPlayer);
	virtual const char *GetTeamID(CBaseEntity *pEntity)
	{
		return "";
	};
	virtual int PlayerRelationship(CBasePlayer *pPlayer, CBaseEntity *pTarget);
	virtual BOOL FAllowMonsters(void);

#ifdef HOOK_GAMEDLL

	void PlayerSpawn_(CBasePlayer *pPlayer);

#endif // HOOK_GAMEDLL

};/* size: 12, cachelines: 1, members: 1 */

class CHalfLifeMultiplay: public CGameRules
{
public:
	CHalfLifeMultiplay(void);
public:
	virtual void RefreshSkillData(void);
	NOBODY virtual void Think(void);
	NOBODY virtual BOOL IsAllowedToSpawn(CBaseEntity *pEntity);
	virtual BOOL FAllowFlashlight(void);
	virtual BOOL FShouldSwitchWeapon(CBasePlayer *pPlayer, CBasePlayerItem *pWeapon);
	virtual BOOL GetNextBestWeapon(CBasePlayer *pPlayer, CBasePlayerItem *pCurrentWeapon);
	virtual BOOL IsMultiplayer(void);
	virtual BOOL IsDeathmatch(void);
	virtual BOOL IsCoOp(void);
	NOBODY virtual BOOL ClientConnected(edict_t *pEntity, const char *pszName, const char *pszAddress, char szRejectReason[128]);
	NOBODY virtual void InitHUD(CBasePlayer *pl);
	NOBODY virtual void ClientDisconnected(edict_t *pClient);
	NOBODY virtual void UpdateGameMode(CBasePlayer *pPlayer);
	virtual float FlPlayerFallDamage(CBasePlayer *pPlayer);
	NOBODY virtual BOOL FPlayerCanTakeDamage(CBasePlayer *pPlayer, CBaseEntity *pAttacker);
	NOBODY virtual void PlayerSpawn(CBasePlayer *pPlayer);
	NOBODY virtual void PlayerThink(CBasePlayer *pPlayer);
	NOBODY virtual BOOL FPlayerCanRespawn(CBasePlayer *pPlayer);
	NOBODY virtual float FlPlayerSpawnTime(CBasePlayer *pPlayer);
	NOBODY virtual edict_t *GetPlayerSpawnSpot(CBasePlayer *pPlayer);
	NOBODY virtual BOOL AllowAutoTargetCrosshair(void);
	NOBODY virtual BOOL ClientCommand_DeadOrAlive(CBasePlayer *pPlayer, const char *pcmd);
	NOBODY virtual BOOL ClientCommand(CBasePlayer *pPlayer, const char *pcmd);
	NOBODY virtual void ClientUserInfoChanged(CBasePlayer *pPlayer, char *infobuffer);
	NOBODY virtual int IPointsForKill(CBasePlayer *pAttacker, CBasePlayer *pKilled);
	NOBODY virtual void PlayerKilled(CBasePlayer *pVictim, entvars_t *pKiller, entvars_t *pInflictor);
	NOBODY virtual void DeathNotice(CBasePlayer *pVictim, entvars_t *pKiller, entvars_t *pInflictor);
	NOBODY virtual BOOL CanHavePlayerItem(CBasePlayer *pPlayer, CBasePlayerItem *pWeapon);
	virtual void PlayerGotWeapon(CBasePlayer *pPlayer, CBasePlayerItem *pWeapon);
	virtual int WeaponShouldRespawn(CBasePlayerItem *pWeapon);
	NOBODY virtual float FlWeaponRespawnTime(CBasePlayerItem *pWeapon);
	NOBODY virtual float FlWeaponTryRespawn(CBasePlayerItem *pWeapon);
	NOBODY virtual Vector VecWeaponRespawnSpot(CBasePlayerItem *pWeapon);
	virtual BOOL CanHaveItem(CBasePlayer *pPlayer, CItem *pItem);
	virtual void PlayerGotItem(CBasePlayer *pPlayer, CItem *pItem);
	virtual int ItemShouldRespawn(CItem *pItem);
	virtual float FlItemRespawnTime(CItem *pItem);
	virtual Vector VecItemRespawnSpot(CItem *pItem);
	NOBODY virtual void PlayerGotAmmo(CBasePlayer *pPlayer, char *szName, int iCount);
	virtual int AmmoShouldRespawn(CBasePlayerAmmo *pAmmo);
	virtual float FlAmmoRespawnTime(CBasePlayerAmmo *pAmmo);
	virtual Vector VecAmmoRespawnSpot(CBasePlayerAmmo *pAmmo);
	NOBODY virtual float FlHealthChargerRechargeTime(void);
	NOBODY virtual float FlHEVChargerRechargeTime(void);
	NOBODY virtual int DeadPlayerWeapons(CBasePlayer *pPlayer);
	NOBODY virtual int DeadPlayerAmmo(CBasePlayer *pPlayer);
	virtual const char *GetTeamID(CBaseEntity *pEntity)
	{
		return "";
	}
	NOBODY virtual int PlayerRelationship(CBasePlayer *pPlayer, CBaseEntity *pTarget);
	virtual BOOL PlayTextureSounds(void)
	{
		return FALSE;
	}
	NOBODY virtual BOOL FAllowMonsters(void);
	virtual void EndMultiplayerGame(void)
	{
		GoToIntermission();
	};
	NOBODY virtual void ServerDeactivate(void);
	NOBODY virtual void CheckMapConditions(void);
	NOBODY virtual void CleanUpMap(void);
	NOBODY virtual void RestartRound(void);
	NOBODY virtual void CheckWinConditions(void);
	virtual void RemoveGuns(void);
	NOBODY virtual void GiveC4(void);
	NOBODY virtual void ChangeLevel(void);
	NOBODY virtual void GoToIntermission(void);

#ifdef HOOK_GAMEDLL

	void RefreshSkillData_(void);
	void Think_(void);
	BOOL IsAllowedToSpawn_(CBaseEntity *pEntity);
	BOOL FAllowFlashlight_(void);
	BOOL FShouldSwitchWeapon_(CBasePlayer *pPlayer, CBasePlayerItem *pWeapon);
	BOOL GetNextBestWeapon_(CBasePlayer *pPlayer, CBasePlayerItem *pCurrentWeapon);
	BOOL IsMultiplayer_(void);
	BOOL IsDeathmatch_(void);
	BOOL IsCoOp_(void);
	BOOL ClientConnected_(edict_t *pEntity, const char *pszName, const char *pszAddress, char szRejectReason[128]);
	void InitHUD_(CBasePlayer *pl);
	void ClientDisconnected_(edict_t *pClient);
	void UpdateGameMode_(CBasePlayer *pPlayer);
	float FlPlayerFallDamage_(CBasePlayer *pPlayer);
	BOOL FPlayerCanTakeDamage_(CBasePlayer *pPlayer, CBaseEntity *pAttacker);
	void PlayerSpawn_(CBasePlayer *pPlayer);
	void PlayerThink_(CBasePlayer *pPlayer);
	BOOL FPlayerCanRespawn_(CBasePlayer *pPlayer);
	float FlPlayerSpawnTime_(CBasePlayer *pPlayer);
	edict_t *GetPlayerSpawnSpot_(CBasePlayer *pPlayer);
	BOOL AllowAutoTargetCrosshair_(void);
	BOOL ClientCommand_DeadOrAlive_(CBasePlayer *pPlayer, const char *pcmd);
	BOOL ClientCommand_(CBasePlayer *pPlayer, const char *pcmd);
	void ClientUserInfoChanged_(CBasePlayer *pPlayer, char *infobuffer);
	int IPointsForKill_(CBasePlayer *pAttacker, CBasePlayer *pKilled);
	void PlayerKilled_(CBasePlayer *pVictim, entvars_t *pKiller, entvars_t *pInflictor);
	void DeathNotice_(CBasePlayer *pVictim, entvars_t *pKiller, entvars_t *pInflictor);
	BOOL CanHavePlayerItem_(CBasePlayer *pPlayer, CBasePlayerItem *pWeapon);
	void PlayerGotWeapon_(CBasePlayer *pPlayer, CBasePlayerItem *pWeapon);
	int WeaponShouldRespawn_(CBasePlayerItem *pWeapon);
	float FlWeaponRespawnTime_(CBasePlayerItem *pWeapon);
	float FlWeaponTryRespawn_(CBasePlayerItem *pWeapon);
	Vector VecWeaponRespawnSpot_(CBasePlayerItem *pWeapon);
	BOOL CanHaveItem_(CBasePlayer *pPlayer, CItem *pItem);
	void PlayerGotItem_(CBasePlayer *pPlayer, CItem *pItem);
	int ItemShouldRespawn_(CItem *pItem);
	float FlItemRespawnTime_(CItem *pItem);
	Vector VecItemRespawnSpot_(CItem *pItem);
	void PlayerGotAmmo_(CBasePlayer *pPlayer, char *szName, int iCount);
	int AmmoShouldRespawn_(CBasePlayerAmmo *pAmmo);
	float FlAmmoRespawnTime_(CBasePlayerAmmo *pAmmo);
	Vector VecAmmoRespawnSpot_(CBasePlayerAmmo *pAmmo);
	float FlHealthChargerRechargeTime_(void);
	float FlHEVChargerRechargeTime_(void);
	int DeadPlayerWeapons_(CBasePlayer *pPlayer);
	int DeadPlayerAmmo_(CBasePlayer *pPlayer);
	int PlayerRelationship_(CBasePlayer *pPlayer, CBaseEntity *pTarget);
	BOOL FAllowMonsters_(void);
	void ServerDeactivate_(void);
	void CheckMapConditions_(void);
	void CleanUpMap_(void);
	void RestartRound_(void);
	void CheckWinConditions_(void);
	void RemoveGuns_(void);
	void GiveC4_(void);
	void ChangeLevel_(void);
	void GoToIntermission_(void);

#endif // HOOK_GAMEDLL

public:
	BOOL IsCareer(void);
	NOBODY void QueueCareerRoundEndMenu(float tmDelay, int iWinStatus);
	NOBODY void SetCareerMatchLimit(int minWins, int winDifference);
	NOBODY bool IsInCareerRound(void);
	NOBODY void CareerRestart(void);
	bool ShouldSkipSpawn(void)
	{
		return m_bSkipSpawn;
	}
	void MarkSpawnSkipped(void)
	{
		m_bSkipSpawn = false;
	}
	NOBODY void PlayerJoinedTeam(CBasePlayer *pPlayer);
	float TimeRemaining(void)
	{
		return m_iRoundTimeSecs - gpGlobals->time + m_fRoundCount;
	}
	NOBODY BOOL TeamFull(int team_id);
	BOOL TeamStacked(int newTeam_id, int curTeam_id);
	NOBODY bool IsVIPQueueEmpty(void);
	NOBODY bool AddToVIPQueue(CBasePlayer *toAdd);
	NOBODY void PickNextVIP(void);
	NOBODY void StackVIPQueue(void);
	NOBODY void ResetCurrentVIP(void);
	NOBODY void BalanceTeams(void);
	NOBODY void SwapAllPlayers(void);
	NOBODY void UpdateTeamScores(void);
	NOBODY void DisplayMaps(CBasePlayer *player, int iVote);
	NOBODY void ResetAllMapVotes(void);
	NOBODY void ProcessMapVote(CBasePlayer *player, int iVote);
	BOOL IsThereABomber(void);
	BOOL IsThereABomb(void);
	NOBODY bool IsMatchStarted(void);
	NOBODY void SendMOTDToClient(edict_t *client);
private:
	NOBODY bool HasRoundTimeExpired(void);
	NOBODY bool IsBombPlanted(void);
	NOBODY void MarkLivingPlayersOnTeamAsNotReceivingMoneyNextRound(int iTeam);

	inline void TerminateRound(float tmDelay, int iWinStatus)
	{
		m_iRoundWinStatus = iWinStatus;
		m_bRoundTerminating = true;
		m_fTeamCount = gpGlobals->time + tmDelay;
	}
public:
	CVoiceGameMgr m_VoiceGameMgr;
	float m_fTeamCount;
	float m_flCheckWinConditions;
	float m_fRoundCount;
	int m_iRoundTime;
	int m_iRoundTimeSecs;
	int m_iIntroRoundTime;
	float m_fIntroRoundCount;
	int m_iAccountTerrorist;
	int m_iAccountCT;
	int m_iNumTerrorist;
	int m_iNumCT;
	int m_iNumSpawnableTerrorist;
	int m_iNumSpawnableCT;
	int m_iSpawnPointCount_Terrorist;
	int m_iSpawnPointCount_CT;
	int m_iHostagesRescued;
	int m_iHostagesTouched;
	int m_iRoundWinStatus;
	short m_iNumCTWins;
	short m_iNumTerroristWins;
	bool m_bTargetBombed;
	bool m_bBombDefused;
	bool m_bMapHasBombTarget;
	bool m_bMapHasBombZone;
	bool m_bMapHasBuyZone;
	bool m_bMapHasRescueZone;
	bool m_bMapHasEscapeZone;
	int m_iMapHasVIPSafetyZone;
	int m_bMapHasCameras;
	int m_iC4Timer;
	int m_iC4Guy;
	int m_iLoserBonus;
	int m_iNumConsecutiveCTLoses;
	int m_iNumConsecutiveTerroristLoses;
	float m_fMaxIdlePeriod;
	int m_iLimitTeams;
	bool m_bLevelInitialized;
	bool m_bRoundTerminating;
	bool m_bCompleteReset;
	float m_flRequiredEscapeRatio;
	int m_iNumEscapers;
	int m_iHaveEscaped;
	bool m_bCTCantBuy;
	bool m_bTCantBuy;
	float m_flBombRadius;
	int m_iConsecutiveVIP;
	int m_iTotalGunCount;
	int m_iTotalGrenadeCount;
	int m_iTotalArmourCount;
	int m_iUnBalancedRounds;
	int m_iNumEscapeRounds;
	int m_iMapVotes[ MAX_VOTE_MAPS ];
	int m_iLastPick;
	int m_iMaxMapTime;
	int m_iMaxRounds;
	int m_iTotalRoundsPlayed;
	int m_iMaxRoundsWon;
	int m_iStoredSpectValue;
	float m_flForceCameraValue;
	float m_flForceChaseCamValue;
	float m_flFadeToBlackValue;
	CBasePlayer *m_pVIP;
	CBasePlayer *VIPQueue[ MAX_VIP_QUEUES ];
protected:
	float m_flIntermissionEndTime;
	float m_flIntermissionStartTime;
	BOOL m_iEndIntermissionButtonHit;
	float m_tmNextPeriodicThink;
	bool m_bFirstConnected;
	bool m_bInCareerGame;
	float m_fCareerRoundMenuTime;
	int m_iCareerMatchWins;
	int m_iRoundWinDifference;
	float m_fCareerMatchMenuTime;
	bool m_bSkipSpawn;

};/* size: 708, cachelines: 12, members: 76 */

typedef struct mapcycle_item_s
{
	struct mapcycle_item_s *next;
	char mapname[32];
	int minplayers;
	int maxplayers;
	char rulebuffer[MAX_RULE_BUFFER];
} mapcycle_item_t;
/* size: 1068, cachelines: 17, members: 5 */

typedef struct mapcycle_s
{
	struct mapcycle_item_s *items;
	struct mapcycle_item_s *next_item;
} mapcycle_t;
/* size: 8, cachelines: 1, members: 2 */

/* <11192b> ../cstrike/dlls/multiplay_gamerules.cpp:257 */
class CMapInfo: public CPointEntity
{
public:
	virtual void Spawn(void);
	virtual void KeyValue(KeyValueData *pkvd);

#ifdef HOOK_GAMEDLL

	void Spawn_(void);
	void KeyValue_(KeyValueData *pkvd);

#endif // HOOK_GAMEDLL

public:
	int m_iBuyingStatus;
	float m_flBombRadius;

};/* size: 160, cachelines: 3, members: 3 */

/* <111732> ../cstrike/dlls/multiplay_gamerules.cpp:292 */
class CCStrikeGameMgrHelper: public IVoiceGameMgrHelper
{
public:
	virtual bool CanPlayerHearPlayer(CBasePlayer *pListener, CBasePlayer *pSender)
	{
		return CanPlayerHearPlayer_(pListener, pSender);
	}

#ifdef HOOK_GAMEDLL

	bool CanPlayerHearPlayer_(CBasePlayer *pListener, CBasePlayer *pSender)
	{
		if (!pSender->IsPlayer() || pListener->m_iTeam != pSender->m_iTeam)
			return false;

		BOOL bListenerAlive = pListener->IsAlive();
		BOOL bSenderAlive = pSender->IsAlive();

		if (pListener->IsObserver())
			return true;

		if (bListenerAlive)
		{
			if (!bSenderAlive)
				return false;
		}
		else
		{
			if (bSenderAlive)
				return true;
		}

		return (bListenerAlive == bSenderAlive);
	}

#endif // HOOK_GAMEDLL

};/* size: 4, cachelines: 1, members: 1 */

#ifdef HOOK_GAMEDLL

#define g_pGameRules (*pg_pGameRules)
#define g_GameMgrHelper (*pg_GameMgrHelper)
#define sv_clienttrace (*psv_clienttrace)
#define g_pMPGameRules (*pg_pMPGameRules)
#define mp_com_token (*pmp_com_token)

#endif // HOOK_GAMEDLL

extern CHalfLifeMultiplay *g_pGameRules;
extern CCStrikeGameMgrHelper g_GameMgrHelper;
extern cvar_t *sv_clienttrace;
extern CHalfLifeMultiplay *g_pMPGameRules;
extern char mp_com_token[ COM_TOKEN_LEN ];

CGameRules *InstallGameRules(void);

/*
* Multiplay gamerules
*/

NOBODY bool IsBotSpeaking(void);
NOBODY void SV_Continue_f(void);
NOBODY void SV_Tutor_Toggle_f(void);
NOBODY void SV_Career_Restart_f(void);
NOBODY void SV_Career_EndRound_f(void);
NOBODY void SV_CareerAddTask_f(void);
NOBODY void SV_CareerMatchLimit_f(void);
void Broadcast(const char *sentence);
char *GetTeam(int teamNo);
NOBODY void EndRoundMessage(const char *sentence, int event);
NOBODY void ReadMultiplayCvars(CHalfLifeMultiplay *mp);
NOBODY void DestroyMapCycle(mapcycle_t *cycle);

char *MP_COM_GetToken(void);
char *MP_COM_Parse(char *data);
NOXREF int MP_COM_TokenWaiting(char *buffer);

NOBODY int ReloadMapCycleFile(char *filename, mapcycle_t *cycle);
NOBODY int CountPlayers(void);
NOBODY void ExtractCommandString(char *s, char *szCommand);
NOBODY int GetMapCount(void);

#endif // GAMERULES_H

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

#define COM_TOKEN_LEN				1500

#define MAX_RULE_BUFFER				1024
#define MAX_VOTE_MAPS				100
#define MAX_VIP_QUEUES				5

#define MAX_BOMB_RADIUS				2048

#define MAP_VIP_SAFETYZONE_UNINITIALIZED	0	// uninitialized
#define MAP_HAVE_VIP_SAFETYZONE_YES		1	// has VIP safety zone
#define MAP_HAVE_VIP_SAFETYZONE_NO		2	// does not have VIP safetyzone

#define MAP_HAS_CAMERAS_INIT			2	// initial
#define MAP_HAS_CAMERAS_YES			1	// on map have of camera's

#define ITEM_RESPAWN_TIME			30
#define WEAPON_RESPAWN_TIME			20
#define AMMO_RESPAWN_TIME			20

// longest the intermission can last, in seconds
#define MAX_INTERMISSION_TIME			120

// when we are within this close to running out of entities,  items
// marked with the ITEM_FLAG_LIMITINWORLD will delay their respawn
#define ENTITY_INTOLERANCE			100

#define MAX_MOTD_CHUNK				60
#define MAX_MOTD_LENGTH				1536 // (MAX_MOTD_CHUNK * 4)

// custom enum
#define WINNER_NONE			0
#define WINNER_DRAW			1

enum
{
	WINSTATUS_CTS = 1,
	WINSTATUS_TERRORISTS,
	WINSTATUS_DRAW,
};

// custom enum
// used for EndRoundMessage() logged messages
enum ScenarionEventEndRound
{
	ROUND_TARGET_BOMB = 1,
	ROUND_VIP_ESCAPED,
	ROUND_VIP_ASSASSINATED,
	ROUND_TERRORISTS_ESCAPED,
	ROUND_CTS_PREVENT_ESCAPE,
	ROUND_ESCAPING_TERRORISTS_NEUTRALIZED,
	ROUND_BOMB_DEFUSED,
	ROUND_CTS_WIN,
	ROUND_TERRORISTS_WIN,
	ROUND_END_DRAW,
	ROUND_ALL_HOSTAGES_RESCUED,
	ROUND_TARGET_SAVED,
	ROUND_HOSTAGE_NOT_RESCUED,
	ROUND_TERRORISTS_NOT_ESCAPED,
	ROUND_VIP_NOT_ESCAPED,
	ROUND_GAME_COMMENCE,
};

// custom enum
enum RewardAccount
{
	REWARD_TARGET_BOMB		= 3500,
	REWARD_VIP_ESCAPED		= 3500,
	REWARD_VIP_ASSASSINATED		= 3250,
	REWARD_TERRORISTS_ESCAPED	= 3150,
	REWARD_CTS_PREVENT_ESCAPE	= 3500,
	REWARD_ESCAPING_TERRORISTS_NEUTRALIZED	= 3250,
	REWARD_BOMB_DEFUSED		= 3250,
	REWARD_BOMB_PLANTED		= 800,
	REWARD_BOMB_EXPLODED		= 3250,
	REWARD_CTS_WIN			= 3000,
	REWARD_TERRORISTS_WIN		= 3000,
	REWARD_ALL_HOSTAGES_RESCUED	= 2500,

	// the end round was by the expiration time
	REWARD_TARGET_BOMB_SAVED	= 3250,
	REWARD_HOSTAGE_NOT_RESCUED	= 3250,
	REWARD_VIP_NOT_ESCAPED		= 3250,

	// loser bonus
	REWARD_LOSER_BONUS_DEFAULT	= 1400,
	REWARD_LOSER_BONUS_MIN		= 1500,
	REWARD_LOSER_BONUS_MAX		= 3000,
	REWARD_LOSER_BONUS_ADD		= 500,

	REWARD_RESCUED_HOSTAGE		= 750,
	REWARD_KILLED_ENEMY		= 300,
	REWARD_KILLED_VIP		= 2500,
	REWARD_VIP_HAVE_SELF_RESCUED	= 2500,

	REWARD_TAKEN_HOSTAGE		= 1000

};

// custom enum
enum PaybackForBadThing
{
	PAYBACK_FOR_KILLED_TEAMMATES	= -3300,
};

// custom enum
enum InfoMapBuyParam
{
	BUYING_EVERYONE = 0,
	BUYING_ONLY_CTS,
	BUYING_ONLY_TERRORISTS,
	BUYING_NO_ONE,
};

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

// custom enum
enum
{
	SCENARIO_BLOCK_TIME_EXPRIRED		= (1 << 0),
	SCENARIO_BLOCK_NEED_PLAYERS		= (1 << 1),
	SCENARIO_BLOCK_VIP_ESCAPRE		= (1 << 2),
	SCENARIO_BLOCK_PRISON_ESCAPRE		= (1 << 3),
	SCENARIO_BLOCK_BOMB			= (1 << 4),
	SCENARIO_BLOCK_TEAM_EXTERMINATION	= (1 << 5),
	SCENARIO_BLOCK_HOSTAGE_RESCUE		= (1 << 6),
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

class CGameRules
{
public:
	virtual void RefreshSkillData();
	virtual void Think() = 0;
	virtual BOOL IsAllowedToSpawn(CBaseEntity *pEntity) = 0;
	virtual BOOL FAllowFlashlight() = 0;
	virtual BOOL FShouldSwitchWeapon(CBasePlayer *pPlayer, CBasePlayerItem *pWeapon) = 0;
	virtual BOOL GetNextBestWeapon(CBasePlayer *pPlayer, CBasePlayerItem *pCurrentWeapon) = 0;
	virtual BOOL IsMultiplayer() = 0;
	virtual BOOL IsDeathmatch() = 0;
	virtual BOOL IsTeamplay() { return FALSE; }
	virtual BOOL IsCoOp() = 0;
	virtual const char *GetGameDescription() { return "Counter-Strike"; }	// this is the game name that gets seen in the server browser
	virtual BOOL ClientConnected(edict_t *pEntity, const char *pszName, const char *pszAddress, char *szRejectReason) = 0;
	virtual void InitHUD(CBasePlayer *pl) = 0;
	virtual void ClientDisconnected(edict_t *pClient) = 0;
	virtual void UpdateGameMode(CBasePlayer *pPlayer) {};
	virtual float FlPlayerFallDamage(CBasePlayer *pPlayer) = 0;
	virtual BOOL FPlayerCanTakeDamage(CBasePlayer *pPlayer, CBaseEntity *pAttacker) { return TRUE; }
	virtual BOOL ShouldAutoAim(CBasePlayer *pPlayer, edict_t *target) { return TRUE; }
	virtual void PlayerSpawn(CBasePlayer *pPlayer) = 0;
	virtual void PlayerThink(CBasePlayer *pPlayer) = 0;
	virtual BOOL FPlayerCanRespawn(CBasePlayer *pPlayer) = 0;
	virtual float FlPlayerSpawnTime(CBasePlayer *pPlayer) = 0;
	virtual edict_t *GetPlayerSpawnSpot(CBasePlayer *pPlayer);
	virtual BOOL AllowAutoTargetCrosshair() { return TRUE; }
	virtual BOOL ClientCommand_DeadOrAlive(CBasePlayer *pPlayer, const char *pcmd) { return FALSE; }
	virtual BOOL ClientCommand(CBasePlayer *pPlayer, const char *pcmd) { return FALSE; }
	virtual void ClientUserInfoChanged(CBasePlayer *pPlayer, char *infobuffer) {};
	virtual int IPointsForKill(CBasePlayer *pAttacker, CBasePlayer *pKilled) = 0;
	virtual void PlayerKilled(CBasePlayer *pVictim, entvars_t *pKiller, entvars_t *pInflictor) = 0;
	virtual void DeathNotice(CBasePlayer *pVictim, entvars_t *pKiller, entvars_t *pevInflictor) = 0;
	virtual BOOL CanHavePlayerItem(CBasePlayer *pPlayer, CBasePlayerItem *pItem);
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
	virtual float FlHealthChargerRechargeTime() = 0;
	virtual float FlHEVChargerRechargeTime() { return 0.0f; }
	virtual int DeadPlayerWeapons(CBasePlayer *pPlayer) = 0;
	virtual int DeadPlayerAmmo(CBasePlayer *pPlayer) = 0;
	virtual const char *GetTeamID(CBaseEntity *pEntity) = 0;
	virtual int PlayerRelationship(CBasePlayer *pPlayer, CBaseEntity *pTarget) = 0;
	virtual int GetTeamIndex(const char *pTeamName) { return -1; }
	virtual const char *GetIndexedTeamName(int teamIndex) { return ""; }
	virtual BOOL IsValidTeam(const char *pTeamName) { return TRUE; }
	virtual void ChangePlayerTeam(CBasePlayer *pPlayer, const char *pTeamName, BOOL bKill, BOOL bGib) {};
	virtual const char *SetDefaultPlayerTeam(CBasePlayer *pPlayer) { return ""; }
	virtual BOOL PlayTextureSounds() { return TRUE; }
	virtual BOOL FAllowMonsters() = 0;
	virtual void EndMultiplayerGame() {};

	// Stuff that is shared between client and server.
	virtual BOOL IsFreezePeriod() { return m_bFreezePeriod; }
	virtual void ServerDeactivate() {};
	virtual void CheckMapConditions() {};

#ifdef HOOK_GAMEDLL

	void RefreshSkillData_();
	edict_t *GetPlayerSpawnSpot_(CBasePlayer *pPlayer);
	BOOL CanHavePlayerItem_(CBasePlayer *pPlayer, CBasePlayerItem *pItem);
	BOOL CanHaveAmmo_(CBasePlayer *pPlayer, const char *pszAmmoName, int iMaxCarry);

#endif

public:
	BOOL m_bFreezePeriod;
	BOOL m_bBombDropped;
};

class CHalfLifeRules: public CGameRules
{
public:
	CHalfLifeRules();

	virtual void Think();
	virtual BOOL IsAllowedToSpawn(CBaseEntity *pEntity);
	virtual BOOL FAllowFlashlight() { return TRUE; }
	virtual BOOL FShouldSwitchWeapon(CBasePlayer *pPlayer, CBasePlayerItem *pWeapon);
	virtual BOOL GetNextBestWeapon(CBasePlayer *pPlayer, CBasePlayerItem *pCurrentWeapon);
	virtual BOOL IsMultiplayer();
	virtual BOOL IsDeathmatch();
	virtual BOOL IsCoOp();
	virtual BOOL ClientConnected(edict_t *pEntity, const char *pszName, const char *pszAddress, char szRejectReason[128]);
	virtual void InitHUD(CBasePlayer *pl);
	virtual void ClientDisconnected(edict_t *pClient);
	virtual float FlPlayerFallDamage(CBasePlayer *pPlayer);
	virtual void PlayerSpawn(CBasePlayer *pPlayer);
	virtual void PlayerThink(CBasePlayer *pPlayer);
	virtual BOOL FPlayerCanRespawn(CBasePlayer *pPlayer);
	virtual float FlPlayerSpawnTime(CBasePlayer *pPlayer);
	virtual edict_t *GetPlayerSpawnSpot(CBasePlayer *pPlayer);
	virtual BOOL AllowAutoTargetCrosshair();
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
	virtual float FlHealthChargerRechargeTime();
	virtual int DeadPlayerWeapons(CBasePlayer *pPlayer);
	virtual int DeadPlayerAmmo(CBasePlayer *pPlayer);
	virtual const char *GetTeamID(CBaseEntity *pEntity) { return ""; };
	virtual int PlayerRelationship(CBasePlayer *pPlayer, CBaseEntity *pTarget);
	virtual BOOL FAllowMonsters();

#ifdef HOOK_GAMEDLL

	void Think_();
	BOOL IsAllowedToSpawn_(CBaseEntity *pEntity);
	BOOL FShouldSwitchWeapon_(CBasePlayer *pPlayer, CBasePlayerItem *pWeapon);
	BOOL GetNextBestWeapon_(CBasePlayer *pPlayer, CBasePlayerItem *pCurrentWeapon);
	BOOL IsMultiplayer_();
	BOOL IsDeathmatch_();
	BOOL IsCoOp_();
	BOOL ClientConnected_(edict_t *pEntity, const char *pszName, const char *pszAddress, char szRejectReason[128]);
	void InitHUD_(CBasePlayer *pl);
	void ClientDisconnected_(edict_t *pClient);
	float FlPlayerFallDamage_(CBasePlayer *pPlayer);
	void PlayerSpawn_(CBasePlayer *pPlayer);
	void PlayerThink_(CBasePlayer *pPlayer);
	BOOL FPlayerCanRespawn_(CBasePlayer *pPlayer);
	float FlPlayerSpawnTime_(CBasePlayer *pPlayer);
	edict_t *GetPlayerSpawnSpot_(CBasePlayer *pPlayer);
	BOOL AllowAutoTargetCrosshair_();
	int IPointsForKill_(CBasePlayer *pAttacker, CBasePlayer *pKilled);
	void PlayerKilled_(CBasePlayer *pVictim, entvars_t *pKiller, entvars_t *pInflictor);
	void DeathNotice_(CBasePlayer *pVictim, entvars_t *pKiller, entvars_t *pInflictor);
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
	float FlHealthChargerRechargeTime_();
	int DeadPlayerWeapons_(CBasePlayer *pPlayer);
	int DeadPlayerAmmo_(CBasePlayer *pPlayer);
	int PlayerRelationship_(CBasePlayer *pPlayer, CBaseEntity *pTarget);
	BOOL FAllowMonsters_();

#endif // HOOK_GAMEDLL
};

class CHalfLifeMultiplay: public CGameRules
{
public:
	CHalfLifeMultiplay();
public:
	virtual void RefreshSkillData();
	virtual void Think();
	virtual BOOL IsAllowedToSpawn(CBaseEntity *pEntity);
	virtual BOOL FAllowFlashlight();
	virtual BOOL FShouldSwitchWeapon(CBasePlayer *pPlayer, CBasePlayerItem *pWeapon);
	virtual BOOL GetNextBestWeapon(CBasePlayer *pPlayer, CBasePlayerItem *pCurrentWeapon);
	virtual BOOL IsMultiplayer();
	virtual BOOL IsDeathmatch();
	virtual BOOL IsCoOp();
	virtual BOOL ClientConnected(edict_t *pEntity, const char *pszName, const char *pszAddress, char szRejectReason[128]);
	virtual void InitHUD(CBasePlayer *pl);
	virtual void ClientDisconnected(edict_t *pClient);
	virtual void UpdateGameMode(CBasePlayer *pPlayer);
	virtual float FlPlayerFallDamage(CBasePlayer *pPlayer);
	virtual BOOL FPlayerCanTakeDamage(CBasePlayer *pPlayer, CBaseEntity *pAttacker);
	virtual void PlayerSpawn(CBasePlayer *pPlayer);
	virtual void PlayerThink(CBasePlayer *pPlayer);
	virtual BOOL FPlayerCanRespawn(CBasePlayer *pPlayer);
	virtual float FlPlayerSpawnTime(CBasePlayer *pPlayer);
	virtual edict_t *GetPlayerSpawnSpot(CBasePlayer *pPlayer);
	virtual BOOL AllowAutoTargetCrosshair();
	virtual BOOL ClientCommand_DeadOrAlive(CBasePlayer *pPlayer, const char *pcmd);
	virtual BOOL ClientCommand(CBasePlayer *pPlayer, const char *pcmd);
	virtual void ClientUserInfoChanged(CBasePlayer *pPlayer, char *infobuffer);
	virtual int IPointsForKill(CBasePlayer *pAttacker, CBasePlayer *pKilled);
	virtual void PlayerKilled(CBasePlayer *pVictim, entvars_t *pKiller, entvars_t *pInflictor);

	// Death notices
	virtual void DeathNotice(CBasePlayer *pVictim, entvars_t *pKiller, entvars_t *pInflictor);
	virtual BOOL CanHavePlayerItem(CBasePlayer *pPlayer, CBasePlayerItem *pWeapon);
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
	virtual float FlHealthChargerRechargeTime();
	virtual float FlHEVChargerRechargeTime();
	virtual int DeadPlayerWeapons(CBasePlayer *pPlayer);
	virtual int DeadPlayerAmmo(CBasePlayer *pPlayer);
	virtual const char *GetTeamID(CBaseEntity *pEntity) { return ""; }
	virtual int PlayerRelationship(CBasePlayer *pPlayer, CBaseEntity *pTarget);
	virtual BOOL PlayTextureSounds() { return FALSE; }
	virtual BOOL FAllowMonsters();
	virtual void EndMultiplayerGame() { GoToIntermission(); }
	virtual void ServerDeactivate();
	virtual void CheckMapConditions();

	// Recreate all the map entities from the map data (preserving their indices),
	// then remove everything else except the players.
	// Also get rid of all world decals.
	virtual void CleanUpMap();

	virtual void RestartRound();

	// check if the scenario has been won/lost
	virtual void CheckWinConditions();
	virtual void RemoveGuns();
	virtual void GiveC4();
	virtual void ChangeLevel();
	virtual void GoToIntermission();

#ifdef HOOK_GAMEDLL

	void RefreshSkillData_();
	void Think_();
	BOOL IsAllowedToSpawn_(CBaseEntity *pEntity);
	BOOL FAllowFlashlight_();
	BOOL FShouldSwitchWeapon_(CBasePlayer *pPlayer, CBasePlayerItem *pWeapon);
	BOOL GetNextBestWeapon_(CBasePlayer *pPlayer, CBasePlayerItem *pCurrentWeapon);
	BOOL IsMultiplayer_();
	BOOL IsDeathmatch_();
	BOOL IsCoOp_();
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
	BOOL AllowAutoTargetCrosshair_();
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
	float FlHealthChargerRechargeTime_();
	float FlHEVChargerRechargeTime_();
	int DeadPlayerWeapons_(CBasePlayer *pPlayer);
	int DeadPlayerAmmo_(CBasePlayer *pPlayer);
	int PlayerRelationship_(CBasePlayer *pPlayer, CBaseEntity *pTarget);
	BOOL FAllowMonsters_();
	void ServerDeactivate_();
	void CheckMapConditions_();
	void CleanUpMap_();
	void RestartRound_();
	void CheckWinConditions_();
	void RemoveGuns_();
	void GiveC4_();
	void ChangeLevel_();
	void GoToIntermission_();

#endif // HOOK_GAMEDLL

public:
	// Checks if it still needs players to start a round, or if it has enough players to start rounds.
	// Starts a round and returns true if there are enough players.
	bool NeededPlayersCheck(bool &bNeededPlayers);

	// Setup counts for m_iNumTerrorist, m_iNumCT, m_iNumSpawnableTerrorist, m_iNumSpawnableCT, etc.
	void InitializePlayerCounts(int &NumAliveTerrorist, int &NumAliveCT, int &NumDeadTerrorist, int &NumDeadCT);

	// Check to see if the round is over for the various game types. Terminates the round
	// and returns true if the round should end.
	bool PrisonRoundEndCheck(int NumAliveTerrorist, int NumAliveCT, int NumDeadTerrorist, int NumDeadCT, bool bNeededPlayers);
	bool BombRoundEndCheck(bool bNeededPlayers);
	bool HostageRescueRoundEndCheck(bool bNeededPlayers);
	bool VIPRoundEndCheck(bool bNeededPlayers);

	// Check to see if the teams exterminated each other. Ends the round and returns true if so.
	bool TeamExterminationCheck(int NumAliveTerrorist, int NumAliveCT, int NumDeadTerrorist, int NumDeadCT, bool bNeededPlayers);
	void TerminateRound(float tmDelay, int iWinStatus);

	// Check various conditions to end the map.
	bool CheckGameOver();
	bool CheckTimeLimit();
	bool CheckMaxRounds();
	bool CheckWinLimit();

	void CheckFreezePeriodExpired();
	void CheckRoundTimeExpired();

	void CheckLevelInitialized();
	void CheckRestartRound();

	BOOL IsCareer();
	void QueueCareerRoundEndMenu(float tmDelay, int iWinStatus);
	void SetCareerMatchLimit(int minWins, int winDifference);
	bool IsInCareerRound();
	void CareerRestart();
	bool ShouldSkipSpawn() const { return m_bSkipSpawn; }
	void MarkSpawnSkipped() { m_bSkipSpawn = false; }
	void PlayerJoinedTeam(CBasePlayer *pPlayer) { }
	float TimeRemaining() { return m_iRoundTimeSecs - gpGlobals->time + m_fRoundCount; }
	BOOL TeamFull(int team_id);
	BOOL TeamStacked(int newTeam_id, int curTeam_id);
	bool IsVIPQueueEmpty();
	bool AddToVIPQueue(CBasePlayer *toAdd);

	// VIP FUNCTIONS
	void PickNextVIP();
	void StackVIPQueue();
	void ResetCurrentVIP();

	void BalanceTeams();
	void SwapAllPlayers();
	void UpdateTeamScores();
	void DisplayMaps(CBasePlayer *player, int iVote);
	void ResetAllMapVotes();
	void ProcessMapVote(CBasePlayer *player, int iVote);

	// BOMB MAP FUNCTIONS
	BOOL IsThereABomber();
	BOOL IsThereABomb();

	bool IsMatchStarted() { return (m_fTeamCount != 0.0f || m_fCareerRoundMenuTime != 0.0f || m_fCareerMatchMenuTime != 0.0f); }
	void SendMOTDToClient(edict_t *client);

	// allow the mode of fire on a friendly player (FFA)
	inline bool IsFriendlyFireAttack() const
	{
#ifdef REGAMEDLL_ADD
		if (friendlyfire.string[0] == '2')
			return true;
#endif
		return false;
	}

private:
	bool HasRoundTimeExpired();
	bool IsBombPlanted();
	void MarkLivingPlayersOnTeamAsNotReceivingMoneyNextRound(int iTeam);

public:
	CVoiceGameMgr m_VoiceGameMgr;
	float m_fTeamCount;				// m_flRestartRoundTime, the global time when the round is supposed to end, if this is not 0
	float m_flCheckWinConditions;
	float m_fRoundCount;
	int m_iRoundTime;				// (From mp_roundtime) - How many seconds long this round is.
	int m_iRoundTimeSecs;
	int m_iIntroRoundTime;				// (From mp_freezetime) - How many seconds long the intro round (when players are frozen) is.
	float m_fIntroRoundCount;			// The global time when the intro round ends and the real one starts
							// wrote the original "m_flRoundTime" comment for this variable).
	int m_iAccountTerrorist;
	int m_iAccountCT;
	int m_iNumTerrorist;				// The number of terrorists on the team (this is generated at the end of a round)
	int m_iNumCT;					// The number of CTs on the team (this is generated at the end of a round)
	int m_iNumSpawnableTerrorist;
	int m_iNumSpawnableCT;
	int m_iSpawnPointCount_Terrorist;		// Number of Terrorist spawn points
	int m_iSpawnPointCount_CT;			// Number of CT spawn points
	int m_iHostagesRescued;
	int m_iHostagesTouched;
	int m_iRoundWinStatus;				// 1 == CT's won last round, 2 == Terrorists did, 3 == Draw, no winner

	short m_iNumCTWins;
	short m_iNumTerroristWins;

	bool m_bTargetBombed;				// whether or not the bomb has been bombed
	bool m_bBombDefused;				// whether or not the bomb has been defused

	bool m_bMapHasBombTarget;
	bool m_bMapHasBombZone;
	bool m_bMapHasBuyZone;
	bool m_bMapHasRescueZone;
	bool m_bMapHasEscapeZone;

	int m_iMapHasVIPSafetyZone;			// 0 = uninitialized;   1 = has VIP safety zone;   2 = DOES not have VIP safetyzone
	int m_bMapHasCameras;
	int m_iC4Timer;
	int m_iC4Guy;					// The current Terrorist who has the C4.
	int m_iLoserBonus;				// the amount of money the losing team gets. This scales up as they lose more rounds in a row
	int m_iNumConsecutiveCTLoses;			// the number of rounds the CTs have lost in a row.
	int m_iNumConsecutiveTerroristLoses;		// the number of rounds the Terrorists have lost in a row.

	float m_fMaxIdlePeriod;				// For the idle kick functionality. This is tha max amount of time that the player has to be idle before being kicked

	int m_iLimitTeams;
	bool m_bLevelInitialized;
	bool m_bRoundTerminating;
	bool m_bCompleteReset;				// Set to TRUE to have the scores reset next time round restarts
	float m_flRequiredEscapeRatio;
	int m_iNumEscapers;
	int m_iHaveEscaped;
	bool m_bCTCantBuy;
	bool m_bTCantBuy;				// Who can and can't buy.
	float m_flBombRadius;
	int m_iConsecutiveVIP;
	int m_iTotalGunCount;
	int m_iTotalGrenadeCount;
	int m_iTotalArmourCount;
	int m_iUnBalancedRounds;			// keeps track of the # of consecutive rounds that have gone by where one team outnumbers the other team by more than 2
	int m_iNumEscapeRounds;				// keeps track of the # of consecutive rounds of escape played.. Teams will be swapped after 8 rounds
	int m_iMapVotes[MAX_VOTE_MAPS];
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
	CBasePlayer *VIPQueue[MAX_VIP_QUEUES];

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
};

typedef struct mapcycle_item_s
{
	struct mapcycle_item_s *next;
	char mapname[32];
	int minplayers;
	int maxplayers;
	char rulebuffer[MAX_RULE_BUFFER];

} mapcycle_item_t;

typedef struct mapcycle_s
{
	struct mapcycle_item_s *items;
	struct mapcycle_item_s *next_item;

} mapcycle_t;

class CMapInfo: public CPointEntity
{
public:
	virtual void Spawn();
	virtual void KeyValue(KeyValueData *pkvd);

#ifdef HOOK_GAMEDLL

	void Spawn_();
	void KeyValue_(KeyValueData *pkvd);

#endif

public:
	int m_iBuyingStatus;
	float m_flBombRadius;
};

class CCStrikeGameMgrHelper: public IVoiceGameMgrHelper
{
public:
	virtual bool CanPlayerHearPlayer(CBasePlayer *pListener, CBasePlayer *pSender);

#ifdef HOOK_GAMEDLL

	bool CanPlayerHearPlayer_(CBasePlayer *pListener, CBasePlayer *pSender);

#endif

};

extern CGameRules *g_pGameRules;

CGameRules *InstallGameRules();

inline CHalfLifeMultiplay *CSGameRules()
{
	return reinterpret_cast<CHalfLifeMultiplay *>(g_pGameRules);
}

bool IsBotSpeaking();
void SV_Continue_f();
void SV_Tutor_Toggle_f();
void SV_Career_Restart_f();
void SV_Career_EndRound_f();
void SV_CareerAddTask_f();
void SV_CareerMatchLimit_f();
void Broadcast(const char *sentence);
char *GetTeam(int teamNo);
void EndRoundMessage(const char *sentence, int event);
void ReadMultiplayCvars(CHalfLifeMultiplay *mp);
void DestroyMapCycle(mapcycle_t *cycle);

char *MP_COM_GetToken();
char *MP_COM_Parse(char *data);
int MP_COM_TokenWaiting(char *buffer);

int ReloadMapCycleFile(char *filename, mapcycle_t *cycle);
int CountPlayers();
void ExtractCommandString(char *s, char *szCommand);
int GetMapCount();

#endif // GAMERULES_H

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
#define	WINNER_NONE			0
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
	virtual const char *GetGameDescription(void) { return "Counter-Strike"; }	// this is the game name that gets seen in the server browser
	virtual BOOL ClientConnected(edict_t *pEntity, const char *pszName, const char *pszAddress, char *szRejectReason) = 0;
	virtual void InitHUD(CBasePlayer *pl) = 0;
	virtual void ClientDisconnected(edict_t *pClient) = 0;
	virtual void UpdateGameMode(CBasePlayer *pPlayer) {};
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
	virtual edict_t *GetPlayerSpawnSpot(CBasePlayer *pPlayer);
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
	virtual void ChangePlayerTeam(CBasePlayer *pPlayer, const char *pTeamName, BOOL bKill, BOOL bGib) {};
	virtual const char *SetDefaultPlayerTeam(CBasePlayer *pPlayer)
	{
		return "";
	}
	virtual BOOL PlayTextureSounds(void)
	{
		return TRUE;
	}
	virtual BOOL FAllowMonsters(void) = 0;
	virtual void EndMultiplayerGame(void) {};

	// Stuff that is shared between client and server.
	virtual BOOL IsFreezePeriod(void)
	{
		return m_bFreezePeriod;
	}
	virtual void ServerDeactivate(void) {};
	virtual void CheckMapConditions(void) {};

#ifdef HOOK_GAMEDLL

	void RefreshSkillData_(void);
	edict_t *GetPlayerSpawnSpot_(CBasePlayer *pPlayer);
	BOOL CanHavePlayerItem_(CBasePlayer *pPlayer, CBasePlayerItem *pItem);
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
	}
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

	void Think_(void);
	BOOL IsAllowedToSpawn_(CBaseEntity *pEntity);
	BOOL FShouldSwitchWeapon_(CBasePlayer *pPlayer, CBasePlayerItem *pWeapon);
	BOOL GetNextBestWeapon_(CBasePlayer *pPlayer, CBasePlayerItem *pCurrentWeapon);
	BOOL IsMultiplayer_(void);
	BOOL IsDeathmatch_(void);
	BOOL IsCoOp_(void);
	BOOL ClientConnected_(edict_t *pEntity, const char *pszName, const char *pszAddress, char szRejectReason[128]);
	void InitHUD_(CBasePlayer *pl);
	void ClientDisconnected_(edict_t *pClient);
	float FlPlayerFallDamage_(CBasePlayer *pPlayer);
	void PlayerSpawn_(CBasePlayer *pPlayer);
	void PlayerThink_(CBasePlayer *pPlayer);
	BOOL FPlayerCanRespawn_(CBasePlayer *pPlayer);
	float FlPlayerSpawnTime_(CBasePlayer *pPlayer);
	edict_t *GetPlayerSpawnSpot_(CBasePlayer *pPlayer);
	BOOL AllowAutoTargetCrosshair_(void);
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
	float FlHealthChargerRechargeTime_(void);
	int DeadPlayerWeapons_(CBasePlayer *pPlayer);
	int DeadPlayerAmmo_(CBasePlayer *pPlayer);
	int PlayerRelationship_(CBasePlayer *pPlayer, CBaseEntity *pTarget);
	BOOL FAllowMonsters_(void);

#endif // HOOK_GAMEDLL

};/* size: 12, cachelines: 1, members: 1 */

class CHalfLifeMultiplay: public CGameRules
{
public:
	CHalfLifeMultiplay(void);
public:
	virtual void RefreshSkillData(void);
	virtual void Think(void);
	virtual BOOL IsAllowedToSpawn(CBaseEntity *pEntity);
	virtual BOOL FAllowFlashlight(void);
	virtual BOOL FShouldSwitchWeapon(CBasePlayer *pPlayer, CBasePlayerItem *pWeapon);
	virtual BOOL GetNextBestWeapon(CBasePlayer *pPlayer, CBasePlayerItem *pCurrentWeapon);
	virtual BOOL IsMultiplayer(void);
	virtual BOOL IsDeathmatch(void);
	virtual BOOL IsCoOp(void);
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
	virtual BOOL AllowAutoTargetCrosshair(void);
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
	virtual float FlHealthChargerRechargeTime(void);
	virtual float FlHEVChargerRechargeTime(void);
	virtual int DeadPlayerWeapons(CBasePlayer *pPlayer);
	virtual int DeadPlayerAmmo(CBasePlayer *pPlayer);
	virtual const char *GetTeamID(CBaseEntity *pEntity)
	{
		return "";
	}
	virtual int PlayerRelationship(CBasePlayer *pPlayer, CBaseEntity *pTarget);
	virtual BOOL PlayTextureSounds(void)
	{
		return FALSE;
	}
	virtual BOOL FAllowMonsters(void);
	virtual void EndMultiplayerGame(void)
	{
		GoToIntermission();
	}
	virtual void ServerDeactivate(void);
	virtual void CheckMapConditions(void);

	// Recreate all the map entities from the map data (preserving their indices),
	// then remove everything else except the players.
	// Also get rid of all world decals.
	virtual void CleanUpMap(void);

	virtual void RestartRound(void);

	// check if the scenario has been won/lost
	virtual void CheckWinConditions(void);
	virtual void RemoveGuns(void);
	virtual void GiveC4(void);
	virtual void ChangeLevel(void);
	virtual void GoToIntermission(void);

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
	bool CheckGameOver(void);
	bool CheckTimeLimit(void);
	bool CheckMaxRounds(void);
	bool CheckWinLimit(void);

	void CheckFreezePeriodExpired(void);
	void CheckRoundTimeExpired(void);

	void CheckLevelInitialized(void);
	void CheckRestartRound(void);

	BOOL IsCareer(void);
	void QueueCareerRoundEndMenu(float tmDelay, int iWinStatus);
	void SetCareerMatchLimit(int minWins, int winDifference);
	bool IsInCareerRound(void);
	void CareerRestart(void);
	bool ShouldSkipSpawn(void)
	{
		return m_bSkipSpawn;
	}
	void MarkSpawnSkipped(void)
	{
		m_bSkipSpawn = false;
	}
	NOXREF void PlayerJoinedTeam(CBasePlayer *pPlayer)
	{
		;
	}
	float TimeRemaining(void)
	{
		return m_iRoundTimeSecs - gpGlobals->time + m_fRoundCount;
	}
	BOOL TeamFull(int team_id);
	BOOL TeamStacked(int newTeam_id, int curTeam_id);
	bool IsVIPQueueEmpty(void);
	bool AddToVIPQueue(CBasePlayer *toAdd);

	// VIP FUNCTIONS
	void PickNextVIP(void);
	void StackVIPQueue(void);
	void ResetCurrentVIP(void);

	void BalanceTeams(void);
	void SwapAllPlayers(void);
	void UpdateTeamScores(void);
	void DisplayMaps(CBasePlayer *player, int iVote);
	void ResetAllMapVotes(void);
	void ProcessMapVote(CBasePlayer *player, int iVote);

	// BOMB MAP FUNCTIONS
	BOOL IsThereABomber(void);
	BOOL IsThereABomb(void);

	bool IsMatchStarted(void)
	{
		return (m_fTeamCount != 0.0f || m_fCareerRoundMenuTime != 0.0f || m_fCareerMatchMenuTime != 0.0f);
	}
	void SendMOTDToClient(edict_t *client);

private:
	bool HasRoundTimeExpired(void);
	bool IsBombPlanted(void);
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
	bool m_bSkipSpawn;//712

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
	virtual bool CanPlayerHearPlayer(CBasePlayer *pListener, CBasePlayer *pSender);

#ifdef HOOK_GAMEDLL

	bool CanPlayerHearPlayer_(CBasePlayer *pListener, CBasePlayer *pSender);

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

bool IsBotSpeaking(void);
void SV_Continue_f(void);
void SV_Tutor_Toggle_f(void);
void SV_Career_Restart_f(void);
void SV_Career_EndRound_f(void);
void SV_CareerAddTask_f(void);
void SV_CareerMatchLimit_f(void);
void Broadcast(const char *sentence);
char *GetTeam(int teamNo);
void EndRoundMessage(const char *sentence, int event);
void ReadMultiplayCvars(CHalfLifeMultiplay *mp);
void DestroyMapCycle(mapcycle_t *cycle);

char *MP_COM_GetToken(void);
char *MP_COM_Parse(char *data);
int MP_COM_TokenWaiting(char *buffer);

int ReloadMapCycleFile(char *filename, mapcycle_t *cycle);
int CountPlayers(void);
void ExtractCommandString(char *s, char *szCommand);
int GetMapCount(void);

#ifdef HOOK_GAMEDLL

// linked objects
C_DLLEXPORT void info_map_parameters(entvars_t *pev);

#endif // HOOK_GAMEDLL

#endif // GAMERULES_H

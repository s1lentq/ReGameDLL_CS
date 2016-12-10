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

#include "voice_gamemgr.h"

#define MAX_RULE_BUFFER				1024
#define MAX_VOTE_MAPS				100
#define MAX_VIP_QUEUES				5

#define MAX_BOMB_RADIUS				2048

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
enum ScenarioEventEndRound
{
	ROUND_NONE,
	ROUND_TARGET_BOMB,
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
	ROUND_GAME_RESTART,
	ROUND_GAME_OVER
};

enum RewardRules
{
	RR_CTS_WIN,
	RR_TERRORISTS_WIN,
	RR_TARGET_BOMB,
	RR_VIP_ESCAPED,
	RR_VIP_ASSASSINATED,
	RR_TERRORISTS_ESCAPED,
	RR_CTS_PREVENT_ESCAPE,
	RR_ESCAPING_TERRORISTS_NEUTRALIZED,
	RR_BOMB_DEFUSED,
	RR_BOMB_PLANTED,
	RR_BOMB_EXPLODED,
	RR_ALL_HOSTAGES_RESCUED,
	RR_TARGET_BOMB_SAVED,
	RR_HOSTAGE_NOT_RESCUED,
	RR_VIP_NOT_ESCAPED,
	RR_LOSER_BONUS_DEFAULT,
	RR_LOSER_BONUS_MIN,
	RR_LOSER_BONUS_MAX,
	RR_LOSER_BONUS_ADD,
	RR_RESCUED_HOSTAGE,
	RR_TOOK_HOSTAGE_ACC,
	RR_TOOK_HOSTAGE,
	RR_END
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

	REWARD_TAKEN_HOSTAGE		= 1000,
	REWARD_TOOK_HOSTAGE_ACC		= 100,
	REWARD_TOOK_HOSTAGE		= 150,
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

// weapon respawning return codes
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
	SCENARIO_BLOCK_TIME_EXPRIRED		= (1 << 0),	// flag "a"
	SCENARIO_BLOCK_NEED_PLAYERS		= (1 << 1),	// flag "b"
	SCENARIO_BLOCK_VIP_ESCAPE		= (1 << 2),	// flag "c"
	SCENARIO_BLOCK_PRISON_ESCAPE		= (1 << 3),	// flag "d"
	SCENARIO_BLOCK_BOMB			= (1 << 4),	// flag "e"
	SCENARIO_BLOCK_TEAM_EXTERMINATION	= (1 << 5),	// flag "f"
	SCENARIO_BLOCK_HOSTAGE_RESCUE		= (1 << 6),	// flag "g"
};

// Player relationship return codes
enum
{
	GR_NOTTEAMMATE = 0,
	GR_TEAMMATE,
	GR_ENEMY,
	GR_ALLY,
	GR_NEUTRAL,
};

class CItem;

class CGameRules {
protected:
	virtual ~CGameRules() {};
public:
	virtual void RefreshSkillData() = 0;												// fill skill data struct with proper values
	virtual void Think() = 0;													// runs every server frame, should handle any timer tasks, periodic events, etc.
	virtual BOOL IsAllowedToSpawn(CBaseEntity *pEntity) = 0;									// Can this item spawn (eg monsters don't spawn in deathmatch).

	virtual BOOL FAllowFlashlight() = 0;												// Are players allowed to switch on their flashlight?
	virtual BOOL FShouldSwitchWeapon(CBasePlayer *pPlayer, CBasePlayerItem *pWeapon) = 0;						// should the player switch to this weapon?
	virtual BOOL GetNextBestWeapon(CBasePlayer *pPlayer, CBasePlayerItem *pCurrentWeapon) = 0;					// I can't use this weapon anymore, get me the next best one.

	// Functions to verify the single/multiplayer status of a game
	virtual BOOL IsMultiplayer() = 0;												// is this a multiplayer game? (either coop or deathmatch)
	virtual BOOL IsDeathmatch() = 0;												// is this a deathmatch game?
	virtual BOOL IsTeamplay() = 0;													// is this deathmatch game being played with team rules?
	virtual BOOL IsCoOp() = 0;													// is this a coop game?
	virtual const char *GetGameDescription() = 0;											// this is the game name that gets seen in the server browser

	// Client connection/disconnection
	virtual BOOL ClientConnected(edict_t *pEntity, const char *pszName, const char *pszAddress, char *szRejectReason) = 0;		// a client just connected to the server (player hasn't spawned yet)
	virtual void InitHUD(CBasePlayer *pl) = 0;											// the client dll is ready for updating
	virtual void ClientDisconnected(edict_t *pClient) = 0;										// a client just disconnected from the server
	virtual void UpdateGameMode(CBasePlayer *pPlayer) = 0;										// the client needs to be informed of the current game mode

	// Client damage rules
	virtual float FlPlayerFallDamage(CBasePlayer *pPlayer) = 0;
	virtual BOOL FPlayerCanTakeDamage(CBasePlayer *pPlayer, CBaseEntity *pAttacker) = 0;						// can this player take damage from this attacker?
	virtual BOOL ShouldAutoAim(CBasePlayer *pPlayer, edict_t *target) = 0;

	// Client spawn/respawn control
	virtual void PlayerSpawn(CBasePlayer *pPlayer) = 0;										// called by CBasePlayer::Spawn just before releasing player into the game
	virtual void PlayerThink(CBasePlayer *pPlayer) = 0;										// called by CBasePlayer::PreThink every frame, before physics are run and after keys are accepted
	virtual BOOL FPlayerCanRespawn(CBasePlayer *pPlayer) = 0;									// is this player allowed to respawn now?
	virtual float FlPlayerSpawnTime(CBasePlayer *pPlayer) = 0;									// When in the future will this player be able to spawn?
	virtual edict_t *GetPlayerSpawnSpot(CBasePlayer *pPlayer) = 0;									// Place this player on their spawnspot and face them the proper direction.

	virtual BOOL AllowAutoTargetCrosshair() = 0;
	virtual BOOL ClientCommand_DeadOrAlive(CBasePlayer *pPlayer, const char *pcmd) = 0;
	virtual BOOL ClientCommand(CBasePlayer *pPlayer, const char *pcmd) = 0;								// handles the user commands;  returns TRUE if command handled properly
	virtual void ClientUserInfoChanged(CBasePlayer *pPlayer, char *infobuffer) = 0;							// the player has changed userinfo;  can change it now

	// Client kills/scoring
	virtual int IPointsForKill(CBasePlayer *pAttacker, CBasePlayer *pKilled) = 0;							// how many points do I award whoever kills this player?
	virtual void PlayerKilled(CBasePlayer *pVictim, entvars_t *pKiller, entvars_t *pInflictor) = 0;					// Called each time a player dies
	virtual void DeathNotice(CBasePlayer *pVictim, entvars_t *pKiller, entvars_t *pevInflictor) = 0;				// Call this from within a GameRules class to report an obituary.

	// Weapon retrieval
	virtual BOOL CanHavePlayerItem(CBasePlayer *pPlayer, CBasePlayerItem *pItem) = 0;						// The player is touching an CBasePlayerItem, do I give it to him?
	virtual void PlayerGotWeapon(CBasePlayer *pPlayer, CBasePlayerItem *pWeapon) = 0;						// Called each time a player picks up a weapon from the ground

	// Weapon spawn/respawn control
	virtual int WeaponShouldRespawn(CBasePlayerItem *pWeapon) = 0;									// should this weapon respawn?
	virtual float FlWeaponRespawnTime(CBasePlayerItem *pWeapon) = 0;								// when may this weapon respawn?
	virtual float FlWeaponTryRespawn(CBasePlayerItem *pWeapon) = 0;									// can i respawn now,  and if not, when should i try again?
	virtual Vector VecWeaponRespawnSpot(CBasePlayerItem *pWeapon) = 0;								// where in the world should this weapon respawn?

	// Item retrieval
	virtual BOOL CanHaveItem(CBasePlayer *pPlayer, CItem *pItem) = 0;								// is this player allowed to take this item?
	virtual void PlayerGotItem(CBasePlayer *pPlayer, CItem *pItem) = 0;								// call each time a player picks up an item (battery, healthkit, longjump)

	// Item spawn/respawn control
	virtual int ItemShouldRespawn(CItem *pItem) = 0;										// Should this item respawn?
	virtual float FlItemRespawnTime(CItem *pItem) = 0;										// when may this item respawn?
	virtual Vector VecItemRespawnSpot(CItem *pItem) = 0;										// where in the world should this item respawn?

	// Ammo retrieval
	virtual BOOL CanHaveAmmo(CBasePlayer *pPlayer, const char *pszAmmoName, int iMaxCarry) = 0;					// can this player take more of this ammo?
	virtual void PlayerGotAmmo(CBasePlayer *pPlayer, char *szName, int iCount) = 0;							// called each time a player picks up some ammo in the world

	// Ammo spawn/respawn control
	virtual int AmmoShouldRespawn(CBasePlayerAmmo *pAmmo) = 0;									// should this ammo item respawn?
	virtual float FlAmmoRespawnTime(CBasePlayerAmmo *pAmmo) = 0;									// when should this ammo item respawn?
	virtual Vector VecAmmoRespawnSpot(CBasePlayerAmmo *pAmmo) = 0;									// where in the world should this ammo item respawn?

	// Healthcharger respawn control
	virtual float FlHealthChargerRechargeTime() = 0;										// how long until a depleted HealthCharger recharges itself?
	virtual float FlHEVChargerRechargeTime() = 0;											// how long until a depleted HealthCharger recharges itself?

	// What happens to a dead player's weapons
	virtual int DeadPlayerWeapons(CBasePlayer *pPlayer) = 0;									// what do I do with a player's weapons when he's killed?

	// What happens to a dead player's ammo
	virtual int DeadPlayerAmmo(CBasePlayer *pPlayer) = 0;										// Do I drop ammo when the player dies? How much?

	// Teamplay stuff
	virtual const char *GetTeamID(CBaseEntity *pEntity) = 0;									// what team is this entity on?
	virtual int PlayerRelationship(CBasePlayer *pPlayer, CBaseEntity *pTarget) = 0;							// What is the player's relationship with this entity?
	virtual int GetTeamIndex(const char *pTeamName) = 0;
	virtual const char *GetIndexedTeamName(int teamIndex) = 0;
	virtual BOOL IsValidTeam(const char *pTeamName) = 0;
	virtual void ChangePlayerTeam(CBasePlayer *pPlayer, const char *pTeamName, BOOL bKill, BOOL bGib) = 0;
	virtual const char *SetDefaultPlayerTeam(CBasePlayer *pPlayer) = 0;

	// Sounds
	virtual BOOL PlayTextureSounds() = 0;

	// Monsters
	virtual BOOL FAllowMonsters() = 0;												// are monsters allowed

	// Immediately end a multiplayer game
	virtual void EndMultiplayerGame() = 0;

	// Stuff that is shared between client and server.
	virtual BOOL IsFreezePeriod() = 0;
	virtual void ServerDeactivate() = 0;
	virtual void CheckMapConditions() = 0;

	// inline function's
	inline bool IsGameOver() const { return m_bGameOver; }
	inline void SetGameOver() { m_bGameOver = true; }

public:
	BOOL m_bFreezePeriod;				// TRUE at beginning of round, set to FALSE when the period expires
	BOOL m_bBombDropped;

	// custom
	char *m_GameDesc;
	bool m_bGameOver;				// intermission or finale (deprecated name g_fGameOver)
};

// CHalfLifeRules - rules for the single player Half-Life game.
class CHalfLifeRules: public CGameRules {
protected:
	virtual ~CHalfLifeRules() {};
public:
	virtual void Think() = 0;
	virtual BOOL IsAllowedToSpawn(CBaseEntity *pEntity) = 0;
	virtual BOOL FAllowFlashlight() = 0;

	virtual BOOL FShouldSwitchWeapon(CBasePlayer *pPlayer, CBasePlayerItem *pWeapon) = 0;
	virtual BOOL GetNextBestWeapon(CBasePlayer *pPlayer, CBasePlayerItem *pCurrentWeapon) = 0;

	// Functions to verify the single/multiplayer status of a game
	virtual BOOL IsMultiplayer() = 0;
	virtual BOOL IsDeathmatch() = 0;
	virtual BOOL IsCoOp() = 0;

	// Client connection/disconnection
	virtual BOOL ClientConnected(edict_t *pEntity, const char *pszName, const char *pszAddress, char szRejectReason[128]) = 0;
	virtual void InitHUD(CBasePlayer *pl) = 0;											// the client dll is ready for updating
	virtual void ClientDisconnected(edict_t *pClient) = 0;

	// Client damage rules
	virtual float FlPlayerFallDamage(CBasePlayer *pPlayer) = 0;

	// Client spawn/respawn control
	virtual void PlayerSpawn(CBasePlayer *pPlayer) = 0;
	virtual void PlayerThink(CBasePlayer *pPlayer) = 0;
	virtual BOOL FPlayerCanRespawn(CBasePlayer *pPlayer) = 0;
	virtual float FlPlayerSpawnTime(CBasePlayer *pPlayer) = 0;
	virtual edict_t *GetPlayerSpawnSpot(CBasePlayer *pPlayer) = 0;

	virtual BOOL AllowAutoTargetCrosshair() = 0;

	// Client kills/scoring
	virtual int IPointsForKill(CBasePlayer *pAttacker, CBasePlayer *pKilled) = 0;
	virtual void PlayerKilled(CBasePlayer *pVictim, entvars_t *pKiller, entvars_t *pInflictor) = 0;
	virtual void DeathNotice(CBasePlayer *pVictim, entvars_t *pKiller, entvars_t *pInflictor) = 0;

	// Weapon retrieval
	virtual void PlayerGotWeapon(CBasePlayer *pPlayer, CBasePlayerItem *pWeapon) = 0;

	// Weapon spawn/respawn control
	virtual int WeaponShouldRespawn(CBasePlayerItem *pWeapon) = 0;
	virtual float FlWeaponRespawnTime(CBasePlayerItem *pWeapon) = 0;
	virtual float FlWeaponTryRespawn(CBasePlayerItem *pWeapon) = 0;
	virtual Vector VecWeaponRespawnSpot(CBasePlayerItem *pWeapon) = 0;

	// Item retrieval
	virtual BOOL CanHaveItem(CBasePlayer *pPlayer, CItem *pItem) = 0;
	virtual void PlayerGotItem(CBasePlayer *pPlayer, CItem *pItem) = 0;

	// Item spawn/respawn control
	virtual int ItemShouldRespawn(CItem *pItem) = 0;
	virtual float FlItemRespawnTime(CItem *pItem) = 0;
	virtual Vector VecItemRespawnSpot(CItem *pItem) = 0;

	// Ammo retrieval
	virtual void PlayerGotAmmo(CBasePlayer *pPlayer, char *szName, int iCount) = 0;

	// Ammo spawn/respawn control
	virtual int AmmoShouldRespawn(CBasePlayerAmmo *pAmmo) = 0;
	virtual float FlAmmoRespawnTime(CBasePlayerAmmo *pAmmo) = 0;
	virtual Vector VecAmmoRespawnSpot(CBasePlayerAmmo *pAmmo) = 0;

	// Healthcharger respawn control
	virtual float FlHealthChargerRechargeTime() = 0;

	// What happens to a dead player's weapons
	virtual int DeadPlayerWeapons(CBasePlayer *pPlayer) = 0;

	// What happens to a dead player's ammo
	virtual int DeadPlayerAmmo(CBasePlayer *pPlayer) = 0;

	// Teamplay stuff
	virtual const char *GetTeamID(CBaseEntity *pEntity) = 0;
	virtual int PlayerRelationship(CBasePlayer *pPlayer, CBaseEntity *pTarget) = 0;

	// Monsters
	virtual BOOL FAllowMonsters() = 0;
};

// CHalfLifeMultiplay - rules for the basic half life multiplayer competition
class CHalfLifeMultiplay: public CGameRules {
protected:
	virtual ~CHalfLifeMultiplay() {};
public:
	virtual void RefreshSkillData() = 0;
	virtual void Think() = 0;
	virtual BOOL IsAllowedToSpawn(CBaseEntity *pEntity) = 0;
	virtual BOOL FAllowFlashlight() = 0;

	virtual BOOL FShouldSwitchWeapon(CBasePlayer *pPlayer, CBasePlayerItem *pWeapon) = 0;
	virtual BOOL GetNextBestWeapon(CBasePlayer *pPlayer, CBasePlayerItem *pCurrentWeapon) = 0;

	virtual BOOL IsMultiplayer() = 0;
	virtual BOOL IsDeathmatch() = 0;
	virtual BOOL IsCoOp() = 0;

	// Client connection/disconnection
	// If ClientConnected returns FALSE, the connection is rejected and the user is provided the reason specified in szRejectReason
	// Only the client's name and remote address are provided to the dll for verification.
	virtual BOOL ClientConnected(edict_t *pEntity, const char *pszName, const char *pszAddress, char szRejectReason[128]) = 0;
	virtual void InitHUD(CBasePlayer *pl) = 0;
	virtual void ClientDisconnected(edict_t *pClient) = 0;
	virtual void UpdateGameMode(CBasePlayer *pPlayer) = 0;

	// Client damage rules
	virtual float FlPlayerFallDamage(CBasePlayer *pPlayer) = 0;
	virtual BOOL FPlayerCanTakeDamage(CBasePlayer *pPlayer, CBaseEntity *pAttacker) = 0;

	// Client spawn/respawn control
	virtual void PlayerSpawn(CBasePlayer *pPlayer) = 0;
	virtual void PlayerThink(CBasePlayer *pPlayer) = 0;
	virtual BOOL FPlayerCanRespawn(CBasePlayer *pPlayer) = 0;
	virtual float FlPlayerSpawnTime(CBasePlayer *pPlayer) = 0;
	virtual edict_t *GetPlayerSpawnSpot(CBasePlayer *pPlayer) = 0;

	virtual BOOL AllowAutoTargetCrosshair() = 0;

	virtual BOOL ClientCommand_DeadOrAlive(CBasePlayer *pPlayer, const char *pcmd) = 0;
	virtual BOOL ClientCommand(CBasePlayer *pPlayer, const char *pcmd) = 0;
	virtual void ClientUserInfoChanged(CBasePlayer *pPlayer, char *infobuffer) = 0;

	// Client kills/scoring
	virtual int IPointsForKill(CBasePlayer *pAttacker, CBasePlayer *pKilled) = 0;
	virtual void PlayerKilled(CBasePlayer *pVictim, entvars_t *pKiller, entvars_t *pInflictor) = 0;
	virtual void DeathNotice(CBasePlayer *pVictim, entvars_t *pKiller, entvars_t *pInflictor) = 0;

	// Weapon retrieval
	virtual BOOL CanHavePlayerItem(CBasePlayer *pPlayer, CBasePlayerItem *pWeapon) = 0;
	virtual void PlayerGotWeapon(CBasePlayer *pPlayer, CBasePlayerItem *pWeapon) = 0;

	// Weapon spawn/respawn control
	virtual int WeaponShouldRespawn(CBasePlayerItem *pWeapon) = 0;
	virtual float FlWeaponRespawnTime(CBasePlayerItem *pWeapon) = 0;
	virtual float FlWeaponTryRespawn(CBasePlayerItem *pWeapon) = 0;
	virtual Vector VecWeaponRespawnSpot(CBasePlayerItem *pWeapon) = 0;

	// Item retrieval
	virtual BOOL CanHaveItem(CBasePlayer *pPlayer, CItem *pItem) = 0;
	virtual void PlayerGotItem(CBasePlayer *pPlayer, CItem *pItem) = 0;

	// Item spawn/respawn control
	virtual int ItemShouldRespawn(CItem *pItem) = 0;
	virtual float FlItemRespawnTime(CItem *pItem) = 0;
	virtual Vector VecItemRespawnSpot(CItem *pItem) = 0;

	// Ammo retrieval
	virtual void PlayerGotAmmo(CBasePlayer *pPlayer, char *szName, int iCount) = 0;

	// Ammo spawn/respawn control
	virtual int AmmoShouldRespawn(CBasePlayerAmmo *pAmmo) = 0;
	virtual float FlAmmoRespawnTime(CBasePlayerAmmo *pAmmo) = 0;
	virtual Vector VecAmmoRespawnSpot(CBasePlayerAmmo *pAmmo) = 0;

	// Healthcharger respawn control
	virtual float FlHealthChargerRechargeTime() = 0;
	virtual float FlHEVChargerRechargeTime() = 0;

	// What happens to a dead player's weapons
	virtual int DeadPlayerWeapons(CBasePlayer *pPlayer) = 0;

	// What happens to a dead player's ammo
	virtual int DeadPlayerAmmo(CBasePlayer *pPlayer) = 0;

	// Teamplay stuff
	virtual const char *GetTeamID(CBaseEntity *pEntity) = 0;
	virtual int PlayerRelationship(CBasePlayer *pPlayer, CBaseEntity *pTarget) = 0;

	virtual BOOL PlayTextureSounds() = 0;

	// Monsters
	virtual BOOL FAllowMonsters() = 0;

	// Immediately end a multiplayer game
	virtual void EndMultiplayerGame() = 0;
	virtual void ServerDeactivate() = 0;
	virtual void CheckMapConditions() = 0;

	// Recreate all the map entities from the map data (preserving their indices),
	// then remove everything else except the players.
	// Also get rid of all world decals.
	virtual void CleanUpMap() = 0;

	virtual void RestartRound() = 0;

	// check if the scenario has been won/lost
	virtual void CheckWinConditions() = 0;
	virtual void RemoveGuns() = 0;
	virtual void GiveC4() = 0;
	virtual void ChangeLevel() = 0;
	virtual void GoToIntermission() = 0;

	// Setup counts for m_iNumTerrorist, m_iNumCT, m_iNumSpawnableTerrorist, m_iNumSpawnableCT, etc.
	virtual void InitializePlayerCounts(int &NumAliveTerrorist, int &NumAliveCT, int &NumDeadTerrorist, int &NumDeadCT) = 0;

	virtual void BalanceTeams() = 0;
	virtual void SwapAllPlayers() = 0;
	virtual void UpdateTeamScores() = 0;
	virtual void EndRoundMessage(const char *sentence, int event) = 0;
	virtual void SetAccountRules(RewardRules rules, int amount) = 0;
	virtual RewardAccount GetAccountRules(RewardRules rules) const = 0;

	// BOMB MAP FUNCTIONS
	virtual BOOL IsThereABomber() = 0;
	virtual BOOL IsThereABomb() = 0;
	virtual TeamName SelectDefaultTeam() = 0;

	virtual bool HasRoundTimeExpired() = 0;
	virtual bool IsBombPlanted() = 0;

public:
	bool ShouldSkipShowMenu() const { return m_bSkipShowMenu; }
	void MarkShowMenuSkipped() { m_bSkipShowMenu = false; }

	bool ShouldSkipSpawn() const { return m_bSkipSpawn; }
	void MarkSpawnSkipped() { m_bSkipSpawn = false; }

	float GetRoundRemainingTime() const { return m_iRoundTimeSecs - gpGlobals->time + m_fRoundStartTime; }
	float GetRoundRemainingTimeReal() const { return m_iRoundTimeSecs - gpGlobals->time + m_fRoundStartTimeReal; }
	float GetTimeLeft() const { return m_flTimeLimit - gpGlobals->time; }
	bool IsMatchStarted() { return (m_flRestartRoundTime != 0.0f || m_fCareerRoundMenuTime != 0.0f || m_fCareerMatchMenuTime != 0.0f); }

	void TerminateRound(float tmDelay, int iWinStatus);

public:
	CVoiceGameMgr m_VoiceGameMgr;
	float m_flRestartRoundTime;			// The global time when the round is supposed to end, if this is not 0 (deprecated name m_fTeamCount)
	float m_flCheckWinConditions;
	float m_fRoundStartTime;			// Time round has started (deprecated name m_fRoundCount)
	int m_iRoundTime;				// (From mp_roundtime) - How many seconds long this round is.
	int m_iRoundTimeSecs;
	int m_iIntroRoundTime;				// (From mp_freezetime) - How many seconds long the intro round (when players are frozen) is.
	float m_fRoundStartTimeReal;			// The global time when the intro round ends and the real one starts
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

	BOOL m_bMapHasVIPSafetyZone;			// TRUE = has VIP safety zone, FALSE = does not have VIP safetyzone
	BOOL m_bMapHasCameras;
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
	CBasePlayer *m_pVIPQueue[MAX_VIP_QUEUES];
	float m_flIntermissionEndTime;
	float m_flIntermissionStartTime;
	BOOL m_iEndIntermissionButtonHit;
	float m_tmNextPeriodicThink;
	bool m_bGameStarted;				// TRUE = the game commencing when there is at least one CT and T, FALSE = scoring will not start until both teams have players (deprecated name m_bFirstConnected)
	bool m_bInCareerGame;
	float m_fCareerRoundMenuTime;
	int m_iCareerMatchWins;
	int m_iRoundWinDifference;
	float m_fCareerMatchMenuTime;
	bool m_bSkipSpawn;

	// custom
	bool m_bSkipShowMenu;
	bool m_bNeededPlayers;
	float m_flEscapeRatio;
	float m_flTimeLimit;
	float m_flGameStartTime;
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

class CCStrikeGameMgrHelper: public IVoiceGameMgrHelper {
public:
	virtual bool CanPlayerHearPlayer(CBasePlayer *pListener, CBasePlayer *pSender) = 0;
};

extern CGameRules *g_pGameRules;

// Gets us at the CS game rules
inline CHalfLifeMultiplay *CSGameRules()
{
	return static_cast<CHalfLifeMultiplay *>(g_pGameRules);
}

inline void CHalfLifeMultiplay::TerminateRound(float tmDelay, int iWinStatus)
{
	m_iRoundWinStatus = iWinStatus;
	m_flRestartRoundTime = gpGlobals->time + tmDelay;
	m_bRoundTerminating = true;
}

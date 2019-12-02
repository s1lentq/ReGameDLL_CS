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

#include "weapons.h"
#include "pm_materials.h"
#include "hintmessage.h"
#include "unisignals.h"

#define SOUND_FLASHLIGHT_ON  "items/flashlight1.wav"
#define SOUND_FLASHLIGHT_OFF "items/flashlight1.wav"

#ifdef REGAMEDLL_FIXES
const int MIN_BUY_TIME = 0;
#else
const int MIN_BUY_TIME = 15; // the minimum threshold values for cvar mp_buytime 15 sec's
#endif

const int MAX_PLAYER_NAME_LENGTH    = 32;
const int MAX_AUTOBUY_LENGTH        = 256;
const int MAX_REBUY_LENGTH          = 256;

const int MAX_RECENT_PATH           = 20;
const int MAX_HOSTAGE_ICON          = 4;	// the maximum number of icons of the hostages in the HUD

const int MAX_SUIT_NOREPEAT         = 32;
const int MAX_SUIT_PLAYLIST         = 4;	// max of 4 suit sentences queued up at any time

const int MAX_BUFFER_MENU           = 175;
const int MAX_BUFFER_MENU_BRIEFING  = 50;

const float SUIT_UPDATE_TIME        = 3.5f;
const float SUIT_FIRST_UPDATE_TIME  = 0.1f;

const float MAX_PLAYER_FATAL_FALL_SPEED = 1100.0f;
const float MAX_PLAYER_SAFE_FALL_SPEED  = 500.0f;
const float MAX_PLAYER_USE_RADIUS       = 64.0f;

const float ARMOR_RATIO = 0.5f;			// Armor Takes 50% of the damage
const float ARMOR_BONUS = 0.5f;			// Each Point of Armor is work 1/x points of health

const float FLASH_DRAIN_TIME = 1.2f;	// 100 units/3 minutes
const float FLASH_CHARGE_TIME = 0.2f;	// 100 units/20 seconds (seconds per unit)

// damage per unit per second.
const float DAMAGE_FOR_FALL_SPEED   = 100.0f / (MAX_PLAYER_FATAL_FALL_SPEED - MAX_PLAYER_SAFE_FALL_SPEED);
const float PLAYER_MIN_BOUNCE_SPEED = 350.0f;

// won't punch player's screen/make scrape noise unless player falling at least this fast.
const float PLAYER_FALL_PUNCH_THRESHHOLD = 250.0f;

// Money blinks few of times on the freeze period
// NOTE: It works for CZ
const int MONEY_BLINK_AMOUNT = 30;

// Player time based damage
#define AIRTIME                 12		// lung full of air lasts this many seconds
#define PARALYZE_DURATION       2		// number of 2 second intervals to take damage
#define PARALYZE_DAMAGE         1.0f	// damage to take each 2 second interval

#define NERVEGAS_DURATION       2
#define NERVEGAS_DAMAGE         5.0f

#define POISON_DURATION         5
#define POISON_DAMAGE           2.0f

#define RADIATION_DURATION      2
#define RADIATION_DAMAGE        1.0f

#define ACID_DURATION           2
#define ACID_DAMAGE             5.0f

#define SLOWBURN_DURATION       2
#define SLOWBURN_DAMAGE         1.0f

#define SLOWFREEZE_DURATION     2
#define SLOWFREEZE_DAMAGE       1.0f

// Player physics flags bits
// CBasePlayer::m_afPhysicsFlags
#define PFLAG_ONLADDER          BIT(0)
#define PFLAG_ONSWING           BIT(0)
#define PFLAG_ONTRAIN           BIT(1)
#define PFLAG_ONBARNACLE        BIT(2)
#define PFLAG_DUCKING           BIT(3) // In the process of ducking, but not totally squatted yet
#define PFLAG_USING             BIT(4) // Using a continuous entity
#define PFLAG_OBSERVER          BIT(5) // Player is locked in stationary cam mode. Spectators can move, observers can't.

// Player gamestate flags
#define HITGROUP_SHIELD_ENABLED     0
#define HITGROUP_SHIELD_DISABLED    1

#define TRAIN_OFF               0x00
#define TRAIN_NEUTRAL           0x01
#define TRAIN_SLOW              0x02
#define TRAIN_MEDIUM            0x03
#define TRAIN_FAST              0x04
#define TRAIN_BACK              0x05

#define TRAIN_ACTIVE            0x80
#define TRAIN_NEW               0xc0

const bool SUIT_GROUP           = true;
const bool SUIT_SENTENCE        = false;

const int  SUIT_REPEAT_OK       = 0;
const int  SUIT_NEXT_IN_30SEC	= 30;
const int  SUIT_NEXT_IN_1MIN    = 60;
const int  SUIT_NEXT_IN_5MIN    = 300;
const int  SUIT_NEXT_IN_10MIN   = 600;
const int  SUIT_NEXT_IN_30MIN   = 1800;
const int  SUIT_NEXT_IN_1HOUR   = 3600;

const int MAX_TEAM_NAME_LENGTH  = 16;

const auto AUTOAIM_2DEGREES     = 0.0348994967025;
const auto AUTOAIM_5DEGREES     = 0.08715574274766;
const auto AUTOAIM_8DEGREES     = 0.1391731009601;
const auto AUTOAIM_10DEGREES    = 0.1736481776669;

// custom enum
enum RewardType
{
	RT_NONE,
	RT_ROUND_BONUS,
	RT_PLAYER_RESET,
	RT_PLAYER_JOIN,
	RT_PLAYER_SPEC_JOIN,
	RT_PLAYER_BOUGHT_SOMETHING,
	RT_HOSTAGE_TOOK,
	RT_HOSTAGE_RESCUED,
	RT_HOSTAGE_DAMAGED,
	RT_HOSTAGE_KILLED,
	RT_TEAMMATES_KILLED,
	RT_ENEMY_KILLED,
	RT_INTO_GAME,
	RT_VIP_KILLED,
	RT_VIP_RESCUED_MYSELF
};

enum PLAYER_ANIM
{
	PLAYER_IDLE,
	PLAYER_WALK,
	PLAYER_JUMP,
	PLAYER_SUPERJUMP,
	PLAYER_DIE,
	PLAYER_ATTACK1,
	PLAYER_ATTACK2,
	PLAYER_FLINCH,
	PLAYER_LARGE_FLINCH,
	PLAYER_RELOAD,
	PLAYER_HOLDBOMB
};

enum _Menu
{
	Menu_OFF,
	Menu_ChooseTeam,
	Menu_IGChooseTeam,
	Menu_ChooseAppearance,
	Menu_Buy,
	Menu_BuyPistol,
	Menu_BuyRifle,
	Menu_BuyMachineGun,
	Menu_BuyShotgun,
	Menu_BuySubMachineGun,
	Menu_BuyItem,
	Menu_Radio1,
	Menu_Radio2,
	Menu_Radio3,
	Menu_ClientBuy
};

enum TeamName
{
	UNASSIGNED,
	TERRORIST,
	CT,
	SPECTATOR,
};

enum ModelName
{
	MODEL_UNASSIGNED,
	MODEL_URBAN,
	MODEL_TERROR,
	MODEL_LEET,
	MODEL_ARCTIC,
	MODEL_GSG9,
	MODEL_GIGN,
	MODEL_SAS,
	MODEL_GUERILLA,
	MODEL_VIP,
	MODEL_MILITIA,
	MODEL_SPETSNAZ,
	MODEL_AUTO
};

enum JoinState
{
	JOINED,
	SHOWLTEXT,
	READINGLTEXT,
	SHOWTEAMSELECT,
	PICKINGTEAM,
	GETINTOGAME
};

enum TrackCommands
{
	CMD_SAY = 0,
	CMD_SAYTEAM,
	CMD_FULLUPDATE,
	CMD_VOTE,
	CMD_VOTEMAP,
	CMD_LISTMAPS,
	CMD_LISTPLAYERS,
	CMD_NIGHTVISION,
	COMMANDS_TO_TRACK,
};

enum IgnoreChatMsg : int
{
	IGNOREMSG_NONE,  // Nothing to do
	IGNOREMSG_ENEMY, // To ignore any chat messages from the enemy
	IGNOREMSG_TEAM   // Same as IGNOREMSG_ENEMY but ignore teammates
};

struct RebuyStruct
{
	int m_primaryWeapon;
	int m_primaryAmmo;
	int m_secondaryWeapon;
	int m_secondaryAmmo;
	int m_heGrenade;
	int m_flashbang;
	int m_smokeGrenade;
	int m_defuser;
	int m_nightVision;
	ArmorType m_armor;
};

enum ThrowDirection
{
	THROW_NONE,
	THROW_FORWARD,
	THROW_BACKWARD,
	THROW_HITVEL,
	THROW_BOMB,
	THROW_GRENADE,
	THROW_HITVEL_MINUS_AIRVEL
};

const float MAX_ID_RANGE            = 2048.0f;
const float MAX_SPEC_ID_RANGE       = 8192.0f;
const int   MAX_SBAR_STRING         = 128;

const int SBAR_TARGETTYPE_TEAMMATE  = 1;
const int SBAR_TARGETTYPE_ENEMY     = 2;
const int SBAR_TARGETTYPE_HOSTAGE   = 3;

enum sbar_data
{
	SBAR_ID_TARGETTYPE = 1,
	SBAR_ID_TARGETNAME,
	SBAR_ID_TARGETHEALTH,
	SBAR_END
};

enum MusicState { SILENT, CALM, INTENSE };

class CCSPlayer;

class CStripWeapons: public CPointEntity {
public:
	virtual void Use(CBaseEntity *pActivator, CBaseEntity *pCaller, USE_TYPE useType, float value);
};

// Dead HEV suit prop
class CDeadHEV: public CBaseMonster {
public:
	virtual void Spawn();
	virtual void KeyValue(KeyValueData *pkvd);
	virtual int Classify() { return CLASS_HUMAN_MILITARY; }

public:
	int m_iPose;				// which sequence to display -- temporary, don't need to save
	static const char *m_szPoses[];
};

class CSprayCan: public CBaseEntity {
public:
	virtual void Think();
	virtual int ObjectCaps() { return FCAP_DONT_SAVE; }

public:
	void Spawn(entvars_t *pevOwner);
};

class CBloodSplat: public CBaseEntity {
public:
	void Spawn(entvars_t *pevOwner);
	void Spray();
};

class CBasePlayer: public CBaseMonster {
public:
	virtual void Spawn();
	virtual void Precache();
	virtual int Save(CSave &save);
	virtual int Restore(CRestore &restore);
	virtual int ObjectCaps();
	virtual int Classify();
	virtual void TraceAttack(entvars_t *pevAttacker, float flDamage, Vector vecDir, TraceResult *ptr, int bitsDamageType);
	virtual BOOL TakeDamage(entvars_t *pevInflictor, entvars_t *pevAttacker, float flDamage, int bitsDamageType);
	virtual BOOL TakeHealth(float flHealth, int bitsDamageType);
	virtual void Killed(entvars_t *pevAttacker, int iGib);
	virtual void AddPoints(int score, BOOL bAllowNegativeScore);
	virtual void AddPointsToTeam(int score, BOOL bAllowNegativeScore);
	virtual BOOL AddPlayerItem(CBasePlayerItem *pItem);
	virtual BOOL RemovePlayerItem(CBasePlayerItem *pItem);
	virtual int GiveAmmo(int iAmount, const char *szName, int iMax = -1);
#ifndef REGAMEDLL_API
	virtual void StartSneaking() { m_tSneaking = gpGlobals->time - 1; }
	virtual void StopSneaking() { m_tSneaking = gpGlobals->time + 30; }
#else
	virtual void OnCreate();
	virtual void OnDestroy();
	void StartSneaking() { m_tSneaking = gpGlobals->time - 1; };
#endif

	virtual BOOL IsSneaking() { return m_tSneaking <= gpGlobals->time; }
	virtual BOOL IsAlive() { return (pev->deadflag == DEAD_NO && pev->health > 0.0f); }
	virtual BOOL IsPlayer() { return (pev->flags & FL_SPECTATOR) != FL_SPECTATOR; }
	virtual BOOL IsNetClient() { return TRUE; }
	virtual const char *TeamID();
	virtual BOOL FBecomeProne();

	// TODO: Need to investigate for what purposes used random to get relative eyes position
	virtual Vector BodyTarget(const Vector &posSrc) { return Center() + pev->view_ofs * RANDOM_FLOAT(0.5, 1.1); }
	virtual int Illumination();
	virtual BOOL ShouldFadeOnDeath() { return FALSE; }
	virtual void ResetMaxSpeed();
	virtual void Jump();
	virtual void Duck();
	virtual void PreThink();
	virtual void PostThink();
	virtual Vector GetGunPosition();
	virtual BOOL IsBot() { return FALSE; }
	virtual void UpdateClientData();
	virtual void ImpulseCommands();
	virtual void RoundRespawn();
	virtual Vector GetAutoaimVector(float flDelta);
	virtual void Blind(float flUntilTime, float flHoldTime, float flFadeTime, int iAlpha);
	virtual void OnTouchingWeapon(CWeaponBox *pWeapon) { }

#ifdef REGAMEDLL_API
	void Spawn_OrigFunc();
	void Precache_OrigFunc();
	int ObjectCaps_OrigFunc();
	int Classify_OrigFunc();
	void TraceAttack_OrigFunc(entvars_t *pevAttacker, float flDamage, VectorRef vecDir, TraceResult *ptr, int bitsDamageType);
	BOOL TakeDamage_OrigFunc(entvars_t *pevInflictor, entvars_t *pevAttacker, FloatRef flDamage, int bitsDamageType);
	BOOL TakeHealth_OrigFunc(float flHealth, int bitsDamageType);
	void Killed_OrigFunc(entvars_t *pevAttacker, int iGib);
	void AddPoints_OrigFunc(int score, BOOL bAllowNegativeScore);
	void AddPointsToTeam_OrigFunc(int score, BOOL bAllowNegativeScore);
	BOOL AddPlayerItem_OrigFunc(CBasePlayerItem *pItem);
	BOOL RemovePlayerItem_OrigFunc(CBasePlayerItem *pItem);
	int GiveAmmo_OrigFunc(int iAmount, const char *szName, int iMax);
	void ResetMaxSpeed_OrigFunc();
	void Jump_OrigFunc();
	void Duck_OrigFunc();
	void PreThink_OrigFunc();
	void PostThink_OrigFunc();
	void UpdateClientData_OrigFunc();
	void ImpulseCommands_OrigFunc();
	void RoundRespawn_OrigFunc();
	void Blind_OrigFunc(float flUntilTime, float flHoldTime, float flFadeTime, int iAlpha);
	EXT_FUNC CBasePlayer *Observer_IsValidTarget_OrigFunc(int iPlayerIndex, bool bSameTeam);
	void Radio_OrigFunc(const char *msg_id, const char *msg_verbose = nullptr, short pitch = 100, bool showIcon = true);
	void AddAccount_OrigFunc(int amount, RewardType type = RT_NONE, bool bTrackChange = true);
	void Disappear_OrigFunc();
	void MakeVIP_OrigFunc();
	void GiveDefaultItems_OrigFunc();
	bool SetClientUserInfoName_OrigFunc(char *infobuffer, char *szNewName);
	void SetAnimation_OrigFunc(PLAYER_ANIM playerAnim);
	void StartObserver_OrigFunc(Vector &vecPosition, Vector &vecViewAngle);
	CBaseEntity *DropPlayerItem_OrigFunc(const char *pszItemName);
	CBaseEntity *GiveNamedItem_OrigFunc(const char *pszName);
	CBaseEntity *DropShield_OrigFunc(bool bDeploy = true);
	void GiveShield_OrigFunc(bool bDeploy = true);
	bool HasRestrictItem_OrigFunc(ItemID item, ItemRestType type);
	void OnSpawnEquip_OrigFunc(bool addDefault = true, bool equipGame = true);
	bool MakeBomber_OrigFunc();
	bool GetIntoGame_OrigFunc();
	void StartDeathCam_OrigFunc();
	CGrenade *ThrowGrenade_OrigFunc(CBasePlayerWeapon *pWeapon, VectorRef vecSrc, VectorRef vecThrow, float time, unsigned short usEvent = 0);
	void SwitchTeam_OrigFunc();
	bool CanSwitchTeam_OrigFunc(TeamName teamToSwap);
	void SetSpawnProtection_OrigFunc(float flProtectionTime);
	void RemoveSpawnProtection_OrigFunc();
	bool HintMessageEx_OrigFunc(const char *pMessage, float duration = 6.0f, bool bDisplayIfPlayerDead = false, bool bOverride = false);
	void UseEmpty_OrigFunc();
	void DropIdlePlayer_OrigFunc(const char *reason);

	CCSPlayer *CSPlayer() const;
#endif // REGAMEDLL_API

public:
	static CBasePlayer *Instance(edict_t *pEdict) { return GET_PRIVATE<CBasePlayer>(pEdict ? pEdict : ENT(0)); }
	static CBasePlayer *Instance(entvars_t *pev) { return Instance(ENT(pev)); }
	static CBasePlayer *Instance(int offset) { return Instance(ENT(offset)); }

	void SpawnClientSideCorpse();
	void Observer_FindNextPlayer(bool bReverse, const char *name = nullptr);
	CBasePlayer *Observer_IsValidTarget(int iPlayerIndex, bool bSameTeam);
	void Disconnect();
	void Observer_Think();
	void Observer_HandleButtons();
	void Observer_SetMode(int iMode);
	void Observer_CheckTarget();
	void Observer_CheckProperties();
	int GetObserverMode() { return pev->iuser1; }
	void PlantC4();
	void Radio(const char *msg_id, const char *msg_verbose = nullptr, short pitch = 100, bool showIcon = true);
	CBasePlayer *GetNextRadioRecipient(CBasePlayer *pStartPlayer);
	void SmartRadio();
	void ThrowWeapon(char *pszItemName);
	void ThrowPrimary();
	CGrenade *ThrowGrenade(CBasePlayerWeapon *pWeapon, Vector vecSrc, Vector vecThrow, float time, unsigned short usEvent = 0);
	void AddAccount(int amount, RewardType type = RT_NONE, bool bTrackChange = true);
	void Disappear();
	void MakeVIP();
	bool CanPlayerBuy(bool display = false);
	bool CanSwitchTeam(TeamName teamToSwap);
	void SwitchTeam();
	void TabulateAmmo();
	void Pain(int iLastHitGroup, bool bHasArmour);
	BOOL IsBombGuy();
	bool IsLookingAtPosition(Vector *pos, float angleTolerance = 20.0f);
	void Reset();
	void SetScoreboardAttributes(CBasePlayer *destination = nullptr);
	void RenewItems();
	void PackDeadPlayerItems();
	void GiveDefaultItems();
	void RemoveAllItems(BOOL removeSuit);
	void SetBombIcon(BOOL bFlash = FALSE);
	void SetProgressBarTime(int time);
	void SetProgressBarTime2(int time, float timeElapsed);
	void SetPlayerModel(BOOL HasC4);
	bool SetClientUserInfoName(char *infobuffer, char *szNewName);
	void SetClientUserInfoModel(char *infobuffer, char *szNewModel);
	void SetClientUserInfoModel_api(char *infobuffer, char *szNewModel);
	void SetNewPlayerModel(const char *modelName);
	BOOL SwitchWeapon(CBasePlayerItem *pWeapon);
	void CheckPowerups();
	bool CanAffordPrimary();
	bool CanAffordPrimaryAmmo();
	bool CanAffordSecondaryAmmo();
	bool CanAffordArmor();
	bool CanAffordDefuseKit();
	bool CanAffordGrenade();
	bool NeedsPrimaryAmmo();
	bool NeedsSecondaryAmmo();
	bool NeedsArmor();
	bool NeedsDefuseKit();
	bool NeedsGrenade();
	BOOL IsOnLadder();
	BOOL FlashlightIsOn();
	void FlashlightTurnOn();
	void FlashlightTurnOff();
	void UpdatePlayerSound();
	void DeathSound();
	void SetAnimation(PLAYER_ANIM playerAnim);
	void SetWeaponAnimType(const char *szExtention) { Q_strcpy(m_szAnimExtention, szExtention); }
	void CheatImpulseCommands(int iImpulse);
	void StartDeathCam();
	void StartObserver(Vector &vecPosition, Vector &vecViewAngle);
	void HandleSignals();
	CBaseEntity *DropPlayerItem(const char *pszItemName);
	bool HasPlayerItem(CBasePlayerItem *pCheckItem);
	bool HasNamedPlayerItem(const char *pszItemName);
	bool HasWeapons();
	void SelectPrevItem(int iItem);
	void SelectNextItem(int iItem);
	void SelectLastItem();
	void SelectItem(const char *pstr);
	void ItemPreFrame();
	void ItemPostFrame();
	CBaseEntity *GiveNamedItem(const char *pszName);
	CBaseEntity *GiveNamedItemEx(const char *pszName);
	void EnableControl(BOOL fControl);
	bool HintMessage(const char *pMessage, BOOL bDisplayIfPlayerDead = FALSE, BOOL bOverride = FALSE);
	bool HintMessageEx(const char *pMessage, float duration = 6.0f, bool bDisplayIfPlayerDead = false, bool bOverride = false);
	void SendAmmoUpdate();
	void SendFOV(int fov);
	void WaterMove();
	void EXPORT PlayerDeathThink();
	void PlayerRespawnThink();
	void PlayerUse();
	void HostageUsed();
	void JoiningThink();
	void RemoveLevelText();
	void MenuPrint(const char *msg);
	void ResetMenu();
	void SyncRoundTimer();
	void CheckSuitUpdate();
	void SetSuitUpdate(char *name = nullptr, bool group = SUIT_SENTENCE, int iNoRepeatTime = SUIT_REPEAT_OK);
	void UpdateGeigerCounter();
	void CheckTimeBasedDamage();
	void BarnacleVictimBitten(entvars_t *pevBarnacle);
	void BarnacleVictimReleased();
	static int GetAmmoIndex(const char *psz);
	int AmmoInventory(int iAmmoIndex);
	void ResetAutoaim();
	Vector AutoaimDeflection(Vector &vecSrc, float flDist, float flDelta);
	void ForceClientDllUpdate();
	void DeathMessage(entvars_t *pevAttacker) {};
	void SetCustomDecalFrames(int nFrames);
	int GetCustomDecalFrames();
	void InitStatusBar();
	void UpdateStatusBar();
	void StudioEstimateGait();
	void StudioPlayerBlend(int *pBlend, float *pPitch);
	void CalculatePitchBlend();
	void CalculateYawBlend();
	void StudioProcessGait();
	void SendHostagePos();
	void SendHostageIcons();
	void ResetStamina();
	BOOL IsArmored(int nHitGroup);
	BOOL ShouldDoLargeFlinch(int nHitGroup, int nGunType);
	void SetPrefsFromUserinfo(char *infobuffer);
	void SendWeatherInfo();
	void UpdateShieldCrosshair(bool draw);
	bool HasShield();
	bool IsProtectedByShield() { return HasShield() && m_bShieldDrawn; }
	void RemoveShield();
	CBaseEntity *DropShield(bool bDeploy = true);
	void GiveShield(bool bDeploy = true);
	bool IsHittingShield(Vector &vecDirection, TraceResult *ptr);
	bool SelectSpawnSpot(const char *pEntClassName, CBaseEntity* &pSpot);
	bool IsReloading() const;
	bool IsBlind() const { return (m_blindUntilTime > gpGlobals->time); }
	bool IsAutoFollowAllowed() const { return (gpGlobals->time > m_allowAutoFollowTime); }
	void InhibitAutoFollow(float duration) { m_allowAutoFollowTime = gpGlobals->time + duration; }
	void AllowAutoFollow() { m_allowAutoFollowTime = 0; }
	void ClearAutoBuyData();
	void AddAutoBuyData(const char *str);
	void AutoBuy();
	void ClientCommand(const char *cmd, const char *arg1 = nullptr, const char *arg2 = nullptr, const char *arg3 = nullptr);
	void PrioritizeAutoBuyString(char *autobuyString, const char *priorityString);
	const char *PickPrimaryCareerTaskWeapon();
	const char *PickSecondaryCareerTaskWeapon();
	const char *PickFlashKillWeaponString();
	const char *PickGrenadeKillWeaponString();
	bool ShouldExecuteAutoBuyCommand(AutoBuyInfoStruct *commandInfo, bool boughtPrimary, bool boughtSecondary);
	void PostAutoBuyCommandProcessing(AutoBuyInfoStruct *commandInfo, bool &boughtPrimary, bool &boughtSecondary);
	void ParseAutoBuyString(const char *string, bool &boughtPrimary, bool &boughtSecondary);
	AutoBuyInfoStruct *GetAutoBuyCommandInfo(const char *command);
	void InitRebuyData(const char *str);
	void BuildRebuyStruct();
	void Rebuy();
	void RebuyPrimaryWeapon();
	void RebuyPrimaryAmmo();
	void RebuySecondaryWeapon();
	void RebuySecondaryAmmo();
	void RebuyHEGrenade();
	void RebuyFlashbang();
	void RebuySmokeGrenade();
	void RebuyDefuser();
	void RebuyNightVision();
	void RebuyArmor();
	void UpdateLocation(bool forceUpdate = false);
	void SetObserverAutoDirector(bool val) { m_bObserverAutoDirector = val; }
	bool IsObservingPlayer(CBasePlayer *pPlayer);
	bool CanSwitchObserverModes() const { return m_canSwitchObserverModes; }
	void SendItemStatus();
	edict_t *EntSelectSpawnPoint();
	void SetScoreAttrib(CBasePlayer *dest);
	void ReloadWeapons(CBasePlayerItem *pWeapon = nullptr, bool bForceReload = false, bool bForceRefill = false);
	void TeamChangeUpdate();
	bool HasRestrictItem(ItemID item, ItemRestType type);
	void DropSecondary();
	void DropPrimary();
	void OnSpawnEquip(bool addDefault = true, bool equipGame = true);
	void RemoveBomb();
	void RemoveDefuser();
	void HideTimer();
	bool MakeBomber();
	bool GetIntoGame();
	bool ShouldToShowAccount(CBasePlayer *pReceiver) const;
	bool ShouldToShowHealthInfo(CBasePlayer *pReceiver) const;

	CBasePlayerItem *GetItemByName(const char *itemName);
	CBasePlayerItem *GetItemById(WeaponIdType weaponID);

	void SetSpawnProtection(float flProtectionTime);
	void RemoveSpawnProtection();
	void UseEmpty();
	void DropIdlePlayer(const char *reason);

	// templates
	template<typename T = CBasePlayerItem, typename Functor>
	T *ForEachItem(int slot, const Functor &func) const
	{
		auto item = m_rgpPlayerItems[slot];
		while (item)
		{
			if (func(static_cast<T *>(item)))
				return static_cast<T *>(item);

			item = item->m_pNext;
		}

		return nullptr;
	}

	template<typename T = CBasePlayerItem, typename Functor>
	T *ForEachItem(const Functor &func) const
	{
		for (auto item : m_rgpPlayerItems)
		{
			while (item)
			{
				if (func(static_cast<T *>(item)))
					return static_cast<T *>(item);

				item = item->m_pNext;
			}
		}

		return nullptr;
	}

	template<typename T = CBasePlayerItem, typename Functor>
	T *ForEachItem(const char *pszItemName, const Functor &func) const
	{
		if (!pszItemName) {
			return nullptr;
		}

		for (auto item : m_rgpPlayerItems)
		{
			while (item)
			{
				if (FClassnameIs(item->pev, pszItemName) && func(static_cast<T *>(item))) {
					return static_cast<T *>(item);
				}

				item = item->m_pNext;
			}
		}

		return nullptr;
	}

public:
	enum { MaxLocationLen = 32 };

	int random_seed;
	unsigned short m_usPlayerBleed;
	EntityHandle<CBasePlayer> m_hObserverTarget;
	float m_flNextObserverInput;
	int m_iObserverWeapon;
	int m_iObserverC4State;
	bool m_bObserverHasDefuser;
	int m_iObserverLastMode;
	float m_flFlinchTime;
	float m_flAnimTime;
	bool m_bHighDamage;
	float m_flVelocityModifier;
	int m_iLastZoom;
	bool m_bResumeZoom;
	float m_flEjectBrass;
	ArmorType m_iKevlar;
	bool m_bNotKilled;
	TeamName m_iTeam;
	int m_iAccount;
	bool m_bHasPrimary;
	float m_flDeathThrowTime;
	int m_iThrowDirection;
	float m_flLastTalk;
	bool m_bJustConnected;
	bool m_bContextHelp;
	JoinState m_iJoiningState;
	CBaseEntity *m_pIntroCamera;
	float m_fIntroCamTime;
	float m_fLastMovement;
	bool m_bMissionBriefing;
	bool m_bTeamChanged;
	ModelName m_iModelName;
	int m_iTeamKills;
	IgnoreChatMsg m_iIgnoreGlobalChat;
	bool m_bHasNightVision;
	bool m_bNightVisionOn;
	Vector m_vRecentPath[MAX_RECENT_PATH];
	float m_flIdleCheckTime;
	float m_flRadioTime;
	int m_iRadioMessages;
	bool m_bIgnoreRadio;
	bool m_bHasC4;
	bool m_bHasDefuser;
	bool m_bKilledByBomb;
	Vector m_vBlastVector;
	bool m_bKilledByGrenade;
	CHintMessageQueue m_hintMessageQueue;
	int m_flDisplayHistory;
	_Menu m_iMenu;
	int m_iChaseTarget;
	CBaseEntity *m_pChaseTarget;
	float m_fCamSwitch;
	bool m_bEscaped;
	bool m_bIsVIP;
	float m_tmNextRadarUpdate;
	Vector m_vLastOrigin;
	int m_iCurrentKickVote;
	float m_flNextVoteTime;
	bool m_bJustKilledTeammate;
	int m_iHostagesKilled;
	int m_iMapVote;
	bool m_bCanShoot;
	float m_flLastFired;
	float m_flLastAttackedTeammate;
	bool m_bHeadshotKilled;
	bool m_bPunishedForTK;
	bool m_bReceivesNoMoneyNextRound;
	int m_iTimeCheckAllowed;
	bool m_bHasChangedName;
	char m_szNewName[MAX_PLAYER_NAME_LENGTH];
	bool m_bIsDefusing;
	float m_tmHandleSignals;
	CUnifiedSignals m_signals;
	edict_t *m_pentCurBombTarget;
	int m_iPlayerSound;
	int m_iTargetVolume;
	int m_iWeaponVolume;
	int m_iExtraSoundTypes;
	int m_iWeaponFlash;
	float m_flStopExtraSoundTime;
	float m_flFlashLightTime;
	int m_iFlashBattery;
	int m_afButtonLast;
	int m_afButtonPressed;
	int m_afButtonReleased;
	edict_t *m_pentSndLast;
	float m_flSndRoomtype;
	float m_flSndRange;
	float m_flFallVelocity;
	int m_rgItems[MAX_ITEMS];
	int m_fNewAmmo;
	unsigned int m_afPhysicsFlags;
	float m_fNextSuicideTime;
	float m_flTimeStepSound;
	float m_flTimeWeaponIdle;
	float m_flSwimTime;
	float m_flDuckTime;
	float m_flWallJumpTime;
	float m_flSuitUpdate;
	int m_rgSuitPlayList[MAX_SUIT_PLAYLIST];
	int m_iSuitPlayNext;
	int m_rgiSuitNoRepeat[MAX_SUIT_NOREPEAT];
	float m_rgflSuitNoRepeatTime[MAX_SUIT_NOREPEAT];
	int m_lastDamageAmount;
	float m_tbdPrev;
	float m_flgeigerRange;
	float m_flgeigerDelay;
	int m_igeigerRangePrev;
	int m_iStepLeft;
	char m_szTextureName[MAX_TEXTURENAME_LENGHT];
	char m_chTextureType;
	int m_idrowndmg;
	int m_idrownrestored;
	int m_bitsHUDDamage;
	BOOL m_fInitHUD;
	BOOL m_fGameHUDInitialized;
	int m_iTrain;
	BOOL m_fWeapon;
	EHANDLE m_pTank;
	float m_fDeadTime;
	BOOL m_fNoPlayerSound;
	BOOL m_fLongJump;
	float m_tSneaking;
	int m_iUpdateTime;
	int m_iClientHealth;
	int m_iClientBattery;
	int m_iHideHUD;
	int m_iClientHideHUD;
	int m_iFOV;
	int m_iClientFOV;
	int m_iNumSpawns;
	CBaseEntity *m_pObserver;
	CBasePlayerItem *m_rgpPlayerItems[MAX_ITEM_TYPES];
	CBasePlayerItem *m_pActiveItem;
	CBasePlayerItem *m_pClientActiveItem;
	CBasePlayerItem *m_pLastItem;
	int m_rgAmmo[MAX_AMMO_SLOTS];
	int m_rgAmmoLast[MAX_AMMO_SLOTS];
	Vector m_vecAutoAim;
	BOOL m_fOnTarget;
	int m_iDeaths;
	int m_izSBarState[SBAR_END];
	float m_flNextSBarUpdateTime;
	float m_flStatusBarDisappearDelay;
	char m_SbarString0[MAX_SBAR_STRING];
	int m_lastx;
	int m_lasty;
	int m_nCustomSprayFrames;
	float m_flNextDecalTime;
	char m_szTeamName[MAX_TEAM_NAME_LENGTH];

	static TYPEDESCRIPTION m_playerSaveData[];

/*protected:*/
	int m_modelIndexPlayer;
	char m_szAnimExtention[32];
	int m_iGaitsequence;

	float m_flGaitframe;
	float m_flGaityaw;
	Vector m_prevgaitorigin;
	float m_flPitch;
	float m_flYaw;
	float m_flGaitMovement;
	int m_iAutoWepSwitch;
	bool m_bVGUIMenus;
	bool m_bShowHints;
	bool m_bShieldDrawn;
	bool m_bOwnsShield;
	bool m_bWasFollowing;
	float m_flNextFollowTime;
	float m_flYawModifier;
	float m_blindUntilTime;
	float m_blindStartTime;
	float m_blindHoldTime;
	float m_blindFadeTime;
	int m_blindAlpha;
	float m_allowAutoFollowTime;
	char m_autoBuyString[MAX_AUTOBUY_LENGTH];
	char *m_rebuyString;
	RebuyStruct m_rebuyStruct;
	bool m_bIsInRebuy;
	float m_flLastUpdateTime;
	char m_lastLocation[MaxLocationLen];
	float m_progressStart;
	float m_progressEnd;
	bool m_bObserverAutoDirector;
	bool m_canSwitchObserverModes;
	float m_heartBeatTime;
	float m_intenseTimestamp;
	float m_silentTimestamp;
	MusicState m_musicState;
	float m_flLastCommandTime[COMMANDS_TO_TRACK];

#ifdef BUILD_LATEST
	int m_iLastAccount;
	int m_iLastClientHealth;
	float m_tmNextAccountHealthUpdate;
#endif
};

class CWShield: public CBaseEntity
{
public:
	virtual void Spawn();
	virtual void EXPORT Touch(CBaseEntity *pOther);

public:
	void SetCantBePickedUpByUser(CBasePlayer *pPlayer, float time)
	{
		m_hEntToIgnoreTouchesFrom = pPlayer;
		m_flTimeToIgnoreTouches = gpGlobals->time + time;
	}

public:
	EntityHandle<CBasePlayer> m_hEntToIgnoreTouchesFrom;
	float m_flTimeToIgnoreTouches;
};

inline bool CBasePlayer::IsReloading() const
{
	CBasePlayerWeapon *pCurrentWeapon = static_cast<CBasePlayerWeapon *>(m_pActiveItem);
	if (pCurrentWeapon && pCurrentWeapon->m_fInReload)
	{
		return true;
	}

	return false;
}

#ifdef REGAMEDLL_API
inline CCSPlayer *CBasePlayer::CSPlayer() const {
	return reinterpret_cast<CCSPlayer *>(this->m_pEntity);
}
#endif

#ifdef REGAMEDLL_FIXES

// returns a CBaseEntity pointer to a player by index.  Only returns if the player is spawned and connected otherwise returns NULL
// Index is 1 based
inline CBasePlayer *UTIL_PlayerByIndex(int playerIndex)
{
	return GET_PRIVATE<CBasePlayer>(INDEXENT(playerIndex));
}

#endif

inline CBasePlayer *UTIL_PlayerByIndexSafe(int playerIndex)
{
	CBasePlayer *pPlayer = nullptr;
	if (likely(playerIndex > 0 && playerIndex <= gpGlobals->maxClients))
		pPlayer = UTIL_PlayerByIndex(playerIndex);

	return pPlayer;
}

extern entvars_t *g_pevLastInflictor;
extern CBaseEntity *g_pLastSpawn;
extern CBaseEntity *g_pLastCTSpawn;
extern CBaseEntity *g_pLastTerroristSpawn;
extern BOOL gInitHUD;
extern cvar_t *sv_aim;

void OLD_CheckBuyZone(CBasePlayer *pPlayer);
void OLD_CheckBombTarget(CBasePlayer *pPlayer);
void OLD_CheckRescueZone(CBasePlayer *pPlayer);

void BuyZoneIcon_Set(CBasePlayer *pPlayer);
void BuyZoneIcon_Clear(CBasePlayer *pPlayer);
void BombTargetFlash_Set(CBasePlayer *pPlayer);
void BombTargetFlash_Clear(CBasePlayer *pPlayer);
void RescueZoneIcon_Set(CBasePlayer *pPlayer);
void RescueZoneIcon_Clear(CBasePlayer *pPlayer);
void EscapeZoneIcon_Set(CBasePlayer *pPlayer);
void EscapeZoneIcon_Clear(CBasePlayer *pPlayer);
void EscapeZoneIcon_Set(CBasePlayer *pPlayer);
void EscapeZoneIcon_Clear(CBasePlayer *pPlayer);
void VIP_SafetyZoneIcon_Set(CBasePlayer *pPlayer);
void VIP_SafetyZoneIcon_Clear(CBasePlayer *pPlayer);

void SendItemStatus(CBasePlayer *pPlayer);
const char *GetCSModelName(int item_id);
Vector VecVelocityForDamage(float flDamage);
int TrainSpeed(int iSpeed, int iMax);
const char *GetWeaponName(entvars_t *pevInflictor, entvars_t *pKiller);
void LogAttack(CBasePlayer *pAttacker, CBasePlayer *pVictim, int teamAttack, int healthHit, int armorHit, int newHealth, int newArmor, const char *killer_weapon_name);
bool CanSeeUseable(CBasePlayer *me, CBaseEntity *pEntity);
void FixPlayerCrouchStuck(edict_t *pPlayer);
BOOL IsSpawnPointValid(CBaseEntity *pPlayer, CBaseEntity *pSpot);
CBaseEntity *FindEntityForward(CBaseEntity *pMe);
real_t GetPlayerPitch(const edict_t *pEdict);
real_t GetPlayerYaw(const edict_t *pEdict);
int GetPlayerGaitsequence(const edict_t *pEdict);
const char *GetBuyStringForWeaponClass(int weaponClass);
bool IsPrimaryWeaponClass(int classId);
bool IsPrimaryWeaponId(int id);
bool IsSecondaryWeaponClass(int classId);
bool IsSecondaryWeaponId(int id);
const char *GetWeaponAliasFromName(const char *weaponName);
bool CurrentWeaponSatisfies(CBasePlayerWeapon *pWeapon, int id, int classId);

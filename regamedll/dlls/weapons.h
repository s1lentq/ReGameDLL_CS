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

#ifndef WEAPONS_H
#define WEAPONS_H
#ifdef _WIN32
#pragma once
#endif

class CBasePlayer;

#define MAX_WEAPONS			32
#define MAX_NORMAL_BATTERY		100.0f
#define DISTANCE_RELOAD_SOUND		512.0f

#define ITEM_FLAG_SELECTONEMPTY		1
#define ITEM_FLAG_NOAUTORELOAD		2
#define ITEM_FLAG_NOAUTOSWITCHEMPTY	4
#define ITEM_FLAG_LIMITINWORLD		8
#define ITEM_FLAG_EXHAUSTIBLE		16	// A player can totally exhaust their ammo supply and lose this weapon

#define WEAPON_IS_ONTARGET		0x40

// the maximum amount of ammo each weapon's clip can hold
#define WEAPON_NOCLIP			-1

#define LOUD_GUN_VOLUME			1000
#define NORMAL_GUN_VOLUME		600
#define QUIET_GUN_VOLUME		200

#define BRIGHT_GUN_FLASH		512
#define NORMAL_GUN_FLASH		256
#define DIM_GUN_FLASH			128

#define BIG_EXPLOSION_VOLUME		2048
#define NORMAL_EXPLOSION_VOLUME		1024
#define SMALL_EXPLOSION_VOLUME		512

#define WEAPON_ACTIVITY_VOLUME		64

// spawn flags
#define SF_DETONATE			0x0001	// Grenades flagged with this will be triggered when the owner calls detonateSatchelCharges

#include "weapontype.h"
#include "wpn_shared.h"

// custom enum
enum ArmorType
{
	ARMOR_NONE,	// no armor
	ARMOR_KEVLAR,	// body vest only
	ARMOR_VESTHELM,	// vest and helmet
};

enum ArmouryItemPack
{
	ARMOURY_MP5NAVY,
	ARMOURY_TMP,
	ARMOURY_P90,
	ARMOURY_MAC10,
	ARMOURY_AK47,
	ARMOURY_SG552,
	ARMOURY_M4A1,
	ARMOURY_AUG,
	ARMOURY_SCOUT,
	ARMOURY_G3SG1,
	ARMOURY_AWP,
	ARMOURY_M3,
	ARMOURY_XM1014,
	ARMOURY_M249,
	ARMOURY_FLASHBANG,
	ARMOURY_HEGRENADE,
	ARMOURY_KEVLAR,
	ARMOURY_ASSAULT,
	ARMOURY_SMOKEGRENADE,
	ARMOURY_SHIELD,
	ARMOURY_FAMAS,
	ARMOURY_SG550,
	ARMOURY_GALIL,
	ARMOURY_UMP45,
	ARMOURY_GLOCK18,
	ARMOURY_USP,
	ARMOURY_ELITE,
	ARMOURY_FIVESEVEN,
	ARMOURY_P228,
	ARMOURY_DEAGLE
};

struct ItemInfo
{
	int iSlot;
	int iPosition;
	const char *pszAmmo1;
	int iMaxAmmo1;
	const char *pszAmmo2;
	int iMaxAmmo2;
	const char *pszName;
	int iMaxClip;
	int iId;
	int iFlags;
	int iWeight;
};

struct AmmoInfo
{
	const char *pszName;
	int iId;
};

struct MULTIDAMAGE
{
	CBaseEntity *pEntity;
	float amount;
	int type;
};

class CArmoury: public CBaseEntity
{
public:
	virtual void Spawn();
	virtual void Precache();
	virtual void Restart();
	virtual void KeyValue(KeyValueData *pkvd);
#ifdef REGAMEDLL_ADD
	virtual void SetObjectCollisionBox();
#endif

public:
	void EXPORT ArmouryTouch(CBaseEntity *pOther);

private:
	void Draw();
	void Hide();

public:
	ArmouryItemPack m_iItem;
	int m_iCount;
	int m_iInitialCount;
	bool m_bAlreadyCounted;
};

class CGrenade: public CBaseMonster
{
public:
	virtual void Spawn();
	virtual int Save(CSave &save);
	virtual int Restore(CRestore &restore);
	virtual int ObjectCaps() { return m_bIsC4 ? FCAP_CONTINUOUS_USE : 0; }
	virtual void Killed(entvars_t *pevAttacker, int iGib);
	virtual int BloodColor() { return DONT_BLEED; }
	virtual void Use(CBaseEntity *pActivator, CBaseEntity *pCaller, USE_TYPE useType, float value);
	virtual void BounceSound();

public:
	enum SATCHELCODE
	{
		SATCHEL_DETONATE,
		SATCHEL_RELEASE
	};
public:
	static CGrenade *ShootTimed(entvars_t *pevOwner, Vector vecStart, Vector vecVelocity, float time);
	static CGrenade *ShootTimed2(entvars_t *pevOwner, Vector vecStart, Vector vecVelocity, float time, int iTeam, unsigned short usEvent);
	static CGrenade *ShootContact(entvars_t *pevOwner, Vector vecStart, Vector vecVelocity);
	static CGrenade *ShootSmokeGrenade(entvars_t *pevOwner, Vector vecStart, Vector vecVelocity, float time, unsigned short usEvent);
	static CGrenade *ShootSatchelCharge(entvars_t *pevOwner, Vector vecStart, Vector vecVelocity);
	static void UseSatchelCharges(entvars_t *pevOwner, SATCHELCODE code);
public:
	void Explode(Vector vecSrc, Vector vecAim);
	void Explode(TraceResult *pTrace, int bitsDamageType);
	void Explode2(TraceResult *pTrace, int bitsDamageType);
	void Explode3(TraceResult *pTrace, int bitsDamageType);
	void SG_Explode(TraceResult *pTrace, int bitsDamageType);

	void EXPORT Smoke();
	void EXPORT Smoke2();
	void EXPORT Smoke3_A();
	void EXPORT Smoke3_B();
	void EXPORT Smoke3_C();
	void EXPORT SG_Smoke();
	void EXPORT BounceTouch(CBaseEntity *pOther);
	void EXPORT SlideTouch(CBaseEntity *pOther);
	void EXPORT C4Touch(CBaseEntity *pOther);
	void EXPORT ExplodeTouch(CBaseEntity *pOther);
	void EXPORT DangerSoundThink();
	void EXPORT PreDetonate();
	void EXPORT Detonate();
	void EXPORT SG_Detonate();
	void EXPORT Detonate2();
	void EXPORT Detonate3();
	void EXPORT DetonateUse(CBaseEntity *pActivator, CBaseEntity *pCaller, USE_TYPE useType, float value);
	void EXPORT TumbleThink();
	void EXPORT SG_TumbleThink();
	void EXPORT C4Think();

public:
	static TYPEDESCRIPTION IMPL(m_SaveData)[15];

	bool m_bStartDefuse;
	bool m_bIsC4;
	EHANDLE m_pBombDefuser;
	float m_flDefuseCountDown;
	float m_flC4Blow;
	float m_flNextFreqInterval;
	float m_flNextBeep;
	float m_flNextFreq;
	char *m_sBeepName;
	float m_fAttenu;
	float m_flNextBlink;
	float m_fNextDefuse;
	bool m_bJustBlew;
	int m_iTeam;
	int m_iCurWave;
	edict_t *m_pentCurBombTarget;
	int m_SGSmoke;
	int m_angle;
	unsigned short m_usEvent;
	bool m_bLightSmoke;
	bool m_bDetonated;
	Vector m_vSmokeDetonate;
	int m_iBounceCount;
	BOOL m_fRegisteredSound;
};

class CBasePlayerItem: public CBaseAnimating
{
public:
	virtual int Save(CSave &save);
	virtual int Restore(CRestore &restore);
	virtual void SetObjectCollisionBox();
	virtual CBaseEntity *Respawn();
	virtual int AddToPlayer(CBasePlayer *pPlayer);
	virtual int AddDuplicate(CBasePlayerItem *pItem) { return FALSE; }
	virtual int GetItemInfo(ItemInfo *p) { return 0; }
	virtual BOOL CanDeploy() { return TRUE; }
	virtual BOOL CanDrop() { return TRUE; }
	virtual BOOL Deploy() { return TRUE; }
	virtual BOOL IsWeapon() { return FALSE; }
	virtual BOOL CanHolster() { return TRUE; }
	virtual void Holster(int skiplocal = 0);
	virtual void UpdateItemInfo() {}
	virtual void ItemPreFrame() {}
	virtual void ItemPostFrame() {}
	virtual void Drop();
	virtual void Kill();
	virtual void AttachToPlayer(CBasePlayer *pPlayer);
	virtual int PrimaryAmmoIndex() { return -1; }
	virtual int SecondaryAmmoIndex() { return -1; }
	virtual int UpdateClientData(CBasePlayer *pPlayer) { return 0; }
	virtual CBasePlayerItem *GetWeaponPtr() { return NULL; }
	virtual float GetMaxSpeed() { return 260.0f; }
	virtual int iItemSlot() { return 0; }

public:
	void EXPORT DestroyItem();
	void EXPORT DefaultTouch(CBaseEntity *pOther);
	void EXPORT FallThink();
	void EXPORT Materialize();
	void EXPORT AttemptToMaterialize();

	void FallInit();
	void CheckRespawn();

public:
	inline int iItemPosition() const { return IMPL(ItemInfoArray)[ m_iId ].iPosition; }
	inline const char *pszAmmo1() const { return IMPL(ItemInfoArray)[ m_iId ].pszAmmo1; }
	inline int iMaxAmmo1() const { return IMPL(ItemInfoArray)[ m_iId ].iMaxAmmo1; }
	inline const char *pszAmmo2() const { return IMPL(ItemInfoArray)[ m_iId ].pszAmmo2; }
	inline int iMaxAmmo2() const { return IMPL(ItemInfoArray)[ m_iId ].iMaxAmmo2; }
	inline const char *pszName() const { return IMPL(ItemInfoArray)[ m_iId ].pszName; }
	inline int iMaxClip() const { return IMPL(ItemInfoArray)[ m_iId ].iMaxClip; }
	inline int iWeight() const { return IMPL(ItemInfoArray)[ m_iId ].iWeight; }
	inline int iFlags() const { return IMPL(ItemInfoArray)[ m_iId ].iFlags; }

public:
	static TYPEDESCRIPTION IMPL(m_SaveData)[3];
	static ItemInfo IMPL(ItemInfoArray)[MAX_WEAPONS];
	static AmmoInfo IMPL(AmmoInfoArray)[MAX_AMMO_SLOTS];

	CBasePlayer *m_pPlayer;
	CBasePlayerItem *m_pNext;
	int m_iId;
};

class CBasePlayerWeapon: public CBasePlayerItem
{
public:
	virtual int Save(CSave &save);
	virtual int Restore(CRestore &restore);
	virtual int AddToPlayer(CBasePlayer *pPlayer);
	virtual int AddDuplicate(CBasePlayerItem *pItem);
	virtual BOOL CanDeploy();
	virtual BOOL IsWeapon() { return TRUE; }
	virtual void Holster(int skiplocal = 0);
	virtual void UpdateItemInfo() {};
	virtual void ItemPostFrame();
	virtual int PrimaryAmmoIndex();
	virtual int SecondaryAmmoIndex();
	virtual int UpdateClientData(CBasePlayer *pPlayer);
	virtual CBasePlayerItem *GetWeaponPtr() { return (CBasePlayerItem *)this; }
	virtual int ExtractAmmo(CBasePlayerWeapon *pWeapon);
	virtual int ExtractClipAmmo(CBasePlayerWeapon *pWeapon);
	virtual int AddWeapon()
	{
		ExtractAmmo(this);
		return 1;
	}
	virtual BOOL PlayEmptySound();
	virtual void ResetEmptySound();
	virtual void SendWeaponAnim(int iAnim, int skiplocal = 0);
	virtual BOOL IsUseable();
	virtual void PrimaryAttack() {};
	virtual void SecondaryAttack() {};
	virtual void Reload() {};
	virtual void WeaponIdle() {};
	virtual void RetireWeapon();
	virtual BOOL ShouldWeaponIdle() { return FALSE; }
	virtual BOOL UseDecrement() { return FALSE; }

public:
	BOOL AddPrimaryAmmo(int iCount, char *szName, int iMaxClip, int iMaxCarry);
	BOOL AddSecondaryAmmo(int iCount, char *szName, int iMaxCarry);
	BOOL DefaultDeploy(char *szViewModel, char *szWeaponModel, int iAnim, char *szAnimExt, int skiplocal = 0);
	int DefaultReload(int iClipSize, int iAnim, float fDelay);
	void FireRemaining(int &shotsFired, float &shootTime, BOOL isGlock18);
	void KickBack(float up_base, float lateral_base, float up_modifier, float lateral_modifier, float up_max, float lateral_max, int direction_change);
	void EjectBrassLate();
	void MakeBeam();
	void BeamUpdate();
	void ReloadSound();
	float GetNextAttackDelay(float delay);
	float GetNextAttackDelay2(float delay);
	
	#ifndef REGAMEDLL_FIXES
	bool HasSecondaryAttack();
	#endif
	
	BOOL IsPistol() { return (m_iId == WEAPON_USP || m_iId == WEAPON_GLOCK18 || m_iId == WEAPON_P228 || m_iId == WEAPON_DEAGLE || m_iId == WEAPON_ELITE || m_iId == WEAPON_FIVESEVEN); }
	void SetPlayerShieldAnim();
	void ResetPlayerShieldAnim();
	bool ShieldSecondaryFire(int iUpAnim, int iDownAnim);
	void InstantReload(bool bCanRefillBPAmmo = false);

public:
	static TYPEDESCRIPTION IMPL(m_SaveData)[7];

	int m_iPlayEmptySound;
	int m_fFireOnEmpty;
	float m_flNextPrimaryAttack;			// soonest time ItemPostFrame will call PrimaryAttack
	float m_flNextSecondaryAttack;			// soonest time ItemPostFrame will call SecondaryAttack
	float m_flTimeWeaponIdle;			// soonest time ItemPostFrame will call WeaponIdle
	int m_iPrimaryAmmoType;				// "primary" ammo index into players m_rgAmmo[]
	int m_iSecondaryAmmoType;			// "secondary" ammo index into players m_rgAmmo[]
	int m_iClip;					// number of shots left in the primary weapon clip, -1 it not used
	int m_iClientClip;				// the last version of m_iClip sent to hud dll
	int m_iClientWeaponState;			// the last version of the weapon state sent to hud dll (is current weapon, is on target)
	int m_fInReload;				// Are we in the middle of a reload;
	int m_fInSpecialReload;				// Are we in the middle of a reload for the shotguns
	int m_iDefaultAmmo;				// how much ammo you get when you pick up this weapon as placed by a level designer.
	int m_iShellId;
	float m_fMaxSpeed;
	bool m_bDelayFire;
	int m_iDirection;
	bool m_bSecondarySilencerOn;
	float m_flAccuracy;
	float m_flLastFire;
	int m_iShotsFired;
	Vector m_vVecAiming;
	string_t model_name;
	float m_flGlock18Shoot;				// time to shoot the remaining bullets of the glock18 burst fire
	int m_iGlock18ShotsFired;			// used to keep track of the shots fired during the Glock18 burst fire mode.
	float m_flFamasShoot;
	int m_iFamasShotsFired;
	float m_fBurstSpread;
	int m_iWeaponState;
	float m_flNextReload;
	float m_flDecreaseShotsFired;
	unsigned short m_usFireGlock18;
	unsigned short m_usFireFamas;

	// hle time creep vars
	float m_flPrevPrimaryAttack;
	float m_flLastFireTime;
};

class CBasePlayerAmmo: public CBaseEntity
{
public:
	virtual void Spawn();
	virtual BOOL AddAmmo(CBaseEntity *pOther) { return TRUE; }
	virtual CBaseEntity *Respawn();

public:
	void EXPORT DefaultTouch(CBaseEntity *pOther);
	void EXPORT Materialize();
};

class CWeaponBox: public CBaseEntity
{
public:
	virtual void Spawn();
	virtual void Precache();
	virtual void KeyValue(KeyValueData *pkvd);
	virtual int Save(CSave &save);
	virtual int Restore(CRestore &restore);
	virtual void SetObjectCollisionBox();
	virtual void Touch(CBaseEntity *pOther);

public:
	BOOL IsEmpty();
	int GiveAmmo(int iCount, char *szName, int iMax, int *pIndex = NULL);

	void EXPORT Kill();
	void EXPORT BombThink();

	BOOL HasWeapon(CBasePlayerItem *pCheckItem);
	BOOL PackWeapon(CBasePlayerItem *pWeapon);
	BOOL PackAmmo(int iszName, int iCount);

public:
	static TYPEDESCRIPTION IMPL(m_SaveData)[4];

	CBasePlayerItem *m_rgpPlayerItems[ MAX_ITEM_TYPES ];
	int m_rgiszAmmo[ MAX_AMMO_SLOTS ];
	int m_rgAmmo[ MAX_AMMO_SLOTS ];
	int m_cAmmoTypes;
	bool m_bIsBomb;
};

class CUSP: public CBasePlayerWeapon
{
public:
	virtual void Spawn();
	virtual void Precache();
	virtual int GetItemInfo(ItemInfo *p);
	virtual BOOL Deploy();
	virtual float GetMaxSpeed() { return m_fMaxSpeed; }
	virtual int iItemSlot() { return PISTOL_SLOT; }
	virtual void PrimaryAttack();
	virtual void SecondaryAttack();
	virtual void Reload();
	virtual void WeaponIdle();
	virtual BOOL UseDecrement()
	{
	#ifdef CLIENT_WEAPONS
		return TRUE;
	#else
		return FALSE;
	#endif
	}
	virtual BOOL IsPistol() { return TRUE; }

public:
	void USPFire(float flSpread, float flCycleTime, BOOL fUseSemi);
	void MakeBeam();
	void BeamUpdate();

	int m_iShell;

private:
	unsigned short m_usFireUSP;
};

class CMP5N: public CBasePlayerWeapon
{
public:
	virtual void Spawn();
	virtual void Precache();
	virtual int GetItemInfo(ItemInfo *p);
	virtual BOOL Deploy();
	virtual float GetMaxSpeed() { return MP5N_MAX_SPEED; }
	virtual int iItemSlot() { return PRIMARY_WEAPON_SLOT; }
	virtual void PrimaryAttack();
	virtual void Reload();
	virtual void WeaponIdle();
	virtual BOOL UseDecrement()
	{
	#ifdef CLIENT_WEAPONS
		return TRUE;
	#else
		return FALSE;
	#endif
	}

public:
	void MP5NFire(float flSpread, float flCycleTime, BOOL fUseAutoAim);

	int m_iShell;
	int iShellOn;

private:
	unsigned short m_usFireMP5N;
};

class CSG552: public CBasePlayerWeapon
{
public:
	virtual void Spawn();
	virtual void Precache();
	virtual int GetItemInfo(ItemInfo *p);
	virtual BOOL Deploy();
	virtual float GetMaxSpeed();
	virtual int iItemSlot() { return PRIMARY_WEAPON_SLOT; }
	virtual void PrimaryAttack();
	virtual void SecondaryAttack();
	virtual void Reload();
	virtual void WeaponIdle();
	virtual BOOL UseDecrement()
	{
	#ifdef CLIENT_WEAPONS
		return TRUE;
	#else
		return FALSE;
	#endif
	}

public:
	void SG552Fire(float flSpread, float flCycleTime, BOOL fUseAutoAim);

	int m_iShell;
	int iShellOn;

private:
	unsigned short m_usFireSG552;
};

class CAK47: public CBasePlayerWeapon
{
public:
	virtual void Spawn();
	virtual void Precache();
	virtual int GetItemInfo(ItemInfo *p);
	virtual BOOL Deploy();
	virtual float GetMaxSpeed() { return AK47_MAX_SPEED; }
	virtual int iItemSlot() { return PRIMARY_WEAPON_SLOT; }
	virtual void PrimaryAttack();
	virtual void SecondaryAttack();
	virtual void Reload();
	virtual void WeaponIdle();
	virtual BOOL UseDecrement()
	{
	#ifdef CLIENT_WEAPONS
		return TRUE;
	#else
		return FALSE;
	#endif
	}

public:
	void AK47Fire(float flSpread, float flCycleTime, BOOL fUseAutoAim);

	int m_iShell;
	int iShellOn;

private:
	unsigned short m_usFireAK47;
};

class CAUG: public CBasePlayerWeapon
{
public:
	virtual void Spawn();
	virtual void Precache();
	virtual int GetItemInfo(ItemInfo *p);
	virtual BOOL Deploy();
	virtual float GetMaxSpeed() { return AUG_MAX_SPEED; }
	virtual int iItemSlot() { return PRIMARY_WEAPON_SLOT; }
	virtual void PrimaryAttack();
	virtual void SecondaryAttack();
	virtual void Reload();
	virtual void WeaponIdle();
	virtual BOOL UseDecrement()
	{
	#ifdef CLIENT_WEAPONS
		return TRUE;
	#else
		return FALSE;
	#endif
	}

public:
	void AUGFire(float flSpread, float flCycleTime, BOOL fUseAutoAim);

	int m_iShell;
	int iShellOn;

private:
	unsigned short m_usFireAug;
};

class CAWP: public CBasePlayerWeapon
{
public:
	virtual void Spawn();
	virtual void Precache();
	virtual int GetItemInfo(ItemInfo *p);
	virtual BOOL Deploy();
	virtual float GetMaxSpeed();
	virtual int iItemSlot() { return PRIMARY_WEAPON_SLOT; }
	virtual void PrimaryAttack();
	virtual void SecondaryAttack();
	virtual void Reload();
	virtual void WeaponIdle();
	virtual BOOL UseDecrement()
	{
	#ifdef CLIENT_WEAPONS
		return TRUE;
	#else
		return FALSE;
	#endif
	}

public:
	void AWPFire(float flSpread, float flCycleTime, BOOL fUseAutoAim);

	int m_iShell;

private:
	unsigned short m_usFireAWP;
};

// for usermsg BombDrop
#define BOMB_FLAG_DROPPED	0 // if the bomb was dropped due to voluntary dropping or death/disconnect
#define BOMB_FLAG_PLANTED	1 // if the bomb has been planted will also trigger the round timer to hide will also show where the dropped bomb on the Terrorist team's radar.

class CC4: public CBasePlayerWeapon
{
public:
	virtual void Spawn();
	virtual void Precache();
	virtual void KeyValue(KeyValueData *pkvd);
	virtual void Use(CBaseEntity *pActivator, CBaseEntity *pCaller, USE_TYPE useType, float value);
	virtual int GetItemInfo(ItemInfo *p);
	virtual BOOL Deploy();
	virtual void Holster(int skiplocal);
	virtual float GetMaxSpeed();
	virtual int iItemSlot() { return C4_SLOT; }
	virtual void PrimaryAttack();
	virtual void WeaponIdle();
	virtual BOOL UseDecrement()
	{
	#ifdef CLIENT_WEAPONS
		return TRUE;
	#else
		return FALSE;
	#endif
	}

public:
	bool m_bStartedArming;
	bool m_bBombPlacedAnimation;
	float m_fArmedTime;

private:
	bool m_bHasShield;
};

class CDEAGLE: public CBasePlayerWeapon
{
public:
	virtual void Spawn();
	virtual void Precache();
	virtual int GetItemInfo(ItemInfo *p);
	virtual BOOL Deploy();
	virtual float GetMaxSpeed() { return m_fMaxSpeed; }
	virtual int iItemSlot() { return PISTOL_SLOT; }
	virtual void PrimaryAttack();
	virtual void SecondaryAttack();
	virtual void Reload();
	virtual void WeaponIdle();
	virtual BOOL UseDecrement()
	{
	#ifdef CLIENT_WEAPONS
		return TRUE;
	#else
		return FALSE;
	#endif
	}
	virtual BOOL IsPistol() { return TRUE; }

public:
	void DEAGLEFire(float flSpread, float flCycleTime, BOOL fUseSemi);

	int m_iShell;

private:
	unsigned short m_usFireDeagle;
};

class CFlashbang: public CBasePlayerWeapon
{
public:
	virtual void Spawn();
	virtual void Precache();
	virtual int GetItemInfo(ItemInfo *p);
	virtual BOOL CanDeploy();
	virtual BOOL CanDrop() { return FALSE; }
	virtual BOOL Deploy();
	virtual void Holster(int skiplocal);
	virtual float GetMaxSpeed() { return m_fMaxSpeed; }
	virtual int iItemSlot() { return GRENADE_SLOT; }
	virtual void PrimaryAttack();
	virtual void SecondaryAttack();
	virtual void WeaponIdle();
	virtual BOOL UseDecrement()
	{
	#ifdef CLIENT_WEAPONS
		return TRUE;
	#else
		return FALSE;
	#endif
	}
	virtual BOOL IsPistol()
	{
	#ifdef REGAMEDLL_FIXES
		return FALSE;
	#else
		// TODO: why the object flashbang is IsPistol?
		return TRUE;
	#endif
	}

public:
	bool ShieldSecondaryFire(int iUpAnim, int iDownAnim);
	void SetPlayerShieldAnim();
	void ResetPlayerShieldAnim();
};

class CG3SG1: public CBasePlayerWeapon
{
public:
	virtual void Spawn();
	virtual void Precache();
	virtual int GetItemInfo(ItemInfo *p);
	virtual BOOL Deploy();
	virtual float GetMaxSpeed();
	virtual int iItemSlot() { return PRIMARY_WEAPON_SLOT; }
	virtual void PrimaryAttack();
	virtual void SecondaryAttack();
	virtual void Reload();
	virtual void WeaponIdle();
	virtual BOOL UseDecrement()
	{
	#ifdef CLIENT_WEAPONS
		return TRUE;
	#else
		return FALSE;
	#endif
	}

public:
	void G3SG1Fire(float flSpread, float flCycleTime, BOOL fUseAutoAim);

	int m_iShell;

private:
	unsigned short m_usFireG3SG1;
};

class CGLOCK18: public CBasePlayerWeapon
{
public:
	virtual void Spawn();
	virtual void Precache();
	virtual int GetItemInfo(ItemInfo *p);
	virtual BOOL Deploy();
	virtual float GetMaxSpeed() { return m_fMaxSpeed; }
	virtual int iItemSlot() { return PISTOL_SLOT; }
	virtual void PrimaryAttack();
	virtual void SecondaryAttack();
	virtual void Reload();
	virtual void WeaponIdle();
	virtual BOOL UseDecrement()
	{
	#ifdef CLIENT_WEAPONS
		return TRUE;
	#else
		return FALSE;
	#endif
	}
	virtual BOOL IsPistol() { return TRUE; }

public:
	void GLOCK18Fire(float flSpread, float flCycleTime, BOOL bFireBurst);

public:
	int m_iShell;
	bool m_bBurstFire;
};

class CHEGrenade: public CBasePlayerWeapon
{
public:
	virtual void Spawn();
	virtual void Precache();
	virtual int GetItemInfo(ItemInfo *p);
	virtual BOOL CanDeploy();
	virtual BOOL CanDrop() { return FALSE; }
	virtual BOOL Deploy();
	virtual void Holster(int skiplocal);
	virtual float GetMaxSpeed() { return m_fMaxSpeed; }
	virtual int iItemSlot() { return GRENADE_SLOT; }
	virtual void PrimaryAttack();
	virtual void SecondaryAttack();
	virtual void WeaponIdle();
	virtual BOOL UseDecrement()
	{
	#ifdef CLIENT_WEAPONS
		return TRUE;
	#else
		return FALSE;
	#endif
	}

public:
	bool ShieldSecondaryFire(int iUpAnim, int iDownAnim);
	void SetPlayerShieldAnim();
	void ResetPlayerShieldAnim();

public:
	unsigned short m_usCreateExplosion;
};

class CKnife: public CBasePlayerWeapon
{
public:
	virtual void Spawn();
	virtual void Precache();
	virtual int GetItemInfo(ItemInfo *p);
	virtual BOOL CanDrop() { return FALSE; }
	virtual BOOL Deploy();
	virtual void Holster(int skiplocal);
	virtual float GetMaxSpeed() { return m_fMaxSpeed; }
	virtual int iItemSlot() { return KNIFE_SLOT; }
	virtual void PrimaryAttack();
	virtual void SecondaryAttack();
	virtual BOOL UseDecrement()
	{
	#ifdef CLIENT_WEAPONS
		return TRUE;
	#else
		return FALSE;
	#endif
	}
	virtual void WeaponIdle();

public:
	void EXPORT SwingAgain();
	void EXPORT Smack();

	void WeaponAnimation(int iAnimation);
	int Stab(int fFirst);
	int Swing(int fFirst);

public:
	bool ShieldSecondaryFire(int iUpAnim, int iDownAnim);
	void SetPlayerShieldAnim();
	void ResetPlayerShieldAnim();

public:
	TraceResult m_trHit;
	unsigned short m_usKnife;
};

class CM249: public CBasePlayerWeapon
{
public:
	virtual void Spawn();
	virtual void Precache();
	virtual int GetItemInfo(ItemInfo *p);
	virtual BOOL Deploy();
	virtual float GetMaxSpeed() { return M249_MAX_SPEED; }
	virtual int iItemSlot() { return PRIMARY_WEAPON_SLOT; }
	virtual void PrimaryAttack();
	virtual void Reload();
	virtual void WeaponIdle();
	virtual BOOL UseDecrement()
	{
	#ifdef CLIENT_WEAPONS
		return TRUE;
	#else
		return FALSE;
	#endif
	}

public:
	void M249Fire(float flSpread, float flCycleTime, BOOL fUseAutoAim);

	int m_iShell;
	int iShellOn;

private:
	unsigned short m_usFireM249;
};

class CM3: public CBasePlayerWeapon
{
public:
	virtual void Spawn();
	virtual void Precache();
	virtual int GetItemInfo(ItemInfo *p);
	virtual BOOL Deploy();
	virtual float GetMaxSpeed() { return M3_MAX_SPEED; }
	virtual int iItemSlot() { return PRIMARY_WEAPON_SLOT; }
	virtual void PrimaryAttack();
	virtual void Reload();
	virtual void WeaponIdle();
	virtual BOOL UseDecrement()
	{
	#ifdef CLIENT_WEAPONS
		return TRUE;
	#else
		return FALSE;
	#endif
	}

public:
	int m_iShell;
	float m_flPumpTime;

private:
	unsigned short m_usFireM3;
};

class CM4A1: public CBasePlayerWeapon
{
public:
	virtual void Spawn();
	virtual void Precache();
	virtual int GetItemInfo(ItemInfo *p);
	virtual BOOL Deploy();
	virtual float GetMaxSpeed();
	virtual int iItemSlot() { return PRIMARY_WEAPON_SLOT; }
	virtual void PrimaryAttack();
	virtual void SecondaryAttack();
	virtual void Reload();
	virtual void WeaponIdle();
	virtual BOOL UseDecrement()
	{
	#ifdef CLIENT_WEAPONS
		return TRUE;
	#else
		return FALSE;
	#endif
	}

public:
	void M4A1Fire(float flSpread, float flCycleTime, BOOL fUseAutoAim);

	int m_iShell;
	int iShellOn;

private:
	unsigned short m_usFireM4A1;
};

class CMAC10: public CBasePlayerWeapon
{
public:
	virtual void Spawn();
	virtual void Precache();
	virtual int GetItemInfo(ItemInfo *p);
	virtual BOOL Deploy();
	virtual float GetMaxSpeed() { return MAC10_MAX_SPEED; }
	virtual int iItemSlot() { return PRIMARY_WEAPON_SLOT; }
	virtual void PrimaryAttack();
	virtual void Reload();
	virtual void WeaponIdle();
	virtual BOOL UseDecrement()
	{
	#ifdef CLIENT_WEAPONS
		return TRUE;
	#else
		return FALSE;
	#endif
	}

public:
	void MAC10Fire(float flSpread, float flCycleTime, BOOL fUseAutoAim);

	int m_iShell;
	int iShellOn;

private:
	unsigned short m_usFireMAC10;
};

class CP228: public CBasePlayerWeapon
{
public:
	virtual void Spawn();
	virtual void Precache();
	virtual int GetItemInfo(ItemInfo *p);
	virtual BOOL Deploy();
	virtual float GetMaxSpeed() { return m_fMaxSpeed; }
	virtual int iItemSlot() { return PISTOL_SLOT; }
	virtual void PrimaryAttack();
	virtual void SecondaryAttack();
	virtual void Reload();
	virtual void WeaponIdle();
	virtual BOOL UseDecrement()
	{
	#ifdef CLIENT_WEAPONS
		return TRUE;
	#else
		return FALSE;
	#endif
	}
	virtual BOOL IsPistol() { return TRUE; }

public:
	void P228Fire(float flSpread, float flCycleTime, BOOL fUseSemi);
	void MakeBeam();
	void BeamUpdate();

public:
	int m_iShell;

private:
	unsigned short m_usFireP228;
};

class CP90: public CBasePlayerWeapon
{
public:
	virtual void Spawn();
	virtual void Precache();
	virtual int GetItemInfo(ItemInfo *p);
	virtual BOOL Deploy();
	virtual float GetMaxSpeed();
	virtual int iItemSlot() { return PRIMARY_WEAPON_SLOT; }
	virtual void PrimaryAttack();
	virtual void Reload();
	virtual void WeaponIdle();
	virtual BOOL UseDecrement()
	{
	#ifdef CLIENT_WEAPONS
		return TRUE;
	#else
		return FALSE;
	#endif
	}

public:
	void P90Fire(float flSpread, float flCycleTime, BOOL fUseAutoAim);

	int m_iShell;
	int iShellOn;

private:
	unsigned short m_usFireP90;
};

class CSCOUT: public CBasePlayerWeapon
{
public:
	virtual void Spawn();
	virtual void Precache();
	virtual int GetItemInfo(ItemInfo *p);
	virtual BOOL Deploy();
	virtual float GetMaxSpeed();
	virtual int iItemSlot() { return PRIMARY_WEAPON_SLOT; }
	virtual void PrimaryAttack();
	virtual void SecondaryAttack();
	virtual void Reload();
	virtual void WeaponIdle();
	virtual BOOL UseDecrement()
	{
	#ifdef CLIENT_WEAPONS
		return TRUE;
	#else
		return FALSE;
	#endif
	}

public:
	void SCOUTFire(float flSpread, float flCycleTime, BOOL fUseAutoAim);
	int m_iShell;

private:
	unsigned short m_usFireScout;
};

class CSmokeGrenade: public CBasePlayerWeapon
{
public:
	virtual void Spawn();
	virtual void Precache();
	virtual int GetItemInfo(ItemInfo *p);
	virtual BOOL CanDeploy();
	virtual BOOL CanDrop() { return FALSE; }
	virtual BOOL Deploy();
	virtual void Holster(int skiplocal);
	virtual float GetMaxSpeed() { return m_fMaxSpeed; }
	virtual int iItemSlot() { return GRENADE_SLOT; }
	virtual void PrimaryAttack();
	virtual void SecondaryAttack();
	virtual void WeaponIdle();
	virtual BOOL UseDecrement()
	{
	#ifdef CLIENT_WEAPONS
		return TRUE;
	#else
		return FALSE;
	#endif
	}

public:
	bool ShieldSecondaryFire(int iUpAnim, int iDownAnim);
	void SetPlayerShieldAnim();
	void ResetPlayerShieldAnim();

public:
	unsigned short m_usCreateSmoke;
};

class CTMP: public CBasePlayerWeapon
{
public:
	virtual void Spawn();
	virtual void Precache();
	virtual int GetItemInfo(ItemInfo *p);
	virtual BOOL Deploy();
	virtual float GetMaxSpeed() { return TMP_MAX_SPEED; }
	virtual int iItemSlot() { return PRIMARY_WEAPON_SLOT; }
	virtual void PrimaryAttack();
	virtual void Reload();
	virtual void WeaponIdle();
	virtual BOOL UseDecrement()
	{
	#ifdef CLIENT_WEAPONS
		return TRUE;
	#else
		return FALSE;
	#endif
	}

public:
	void TMPFire(float flSpread, float flCycleTime, BOOL fUseAutoAim);

public:
	int m_iShell;
	int iShellOn;

private:
	unsigned short m_usFireTMP;
};

class CXM1014: public CBasePlayerWeapon
{
public:
	virtual void Spawn();
	virtual void Precache();
	virtual int GetItemInfo(ItemInfo *p);
	virtual BOOL Deploy();
	virtual float GetMaxSpeed() { return XM1014_MAX_SPEED; }
	virtual int iItemSlot() { return PRIMARY_WEAPON_SLOT; }
	virtual void PrimaryAttack();
	virtual void Reload();
	virtual void WeaponIdle();
	virtual BOOL UseDecrement()
	{
	#ifdef CLIENT_WEAPONS
		return TRUE;
	#else
		return FALSE;
	#endif
	}

public:
	int m_iShell;
	float m_flPumpTime;

private:
	unsigned short m_usFireXM1014;
};

class CELITE: public CBasePlayerWeapon
{
public:
	virtual void Spawn();
	virtual void Precache();
	virtual int GetItemInfo(ItemInfo *p);
	virtual BOOL Deploy();
	virtual float GetMaxSpeed() { return ELITE_MAX_SPEED; }
	virtual int iItemSlot() { return PISTOL_SLOT; }
	virtual void PrimaryAttack();
	virtual void Reload();
	virtual void WeaponIdle();
	virtual BOOL UseDecrement()
	{
	#ifdef CLIENT_WEAPONS
		return TRUE;
	#else
		return FALSE;
	#endif
	}
	virtual BOOL IsPistol() { return TRUE; }

public:
	void ELITEFire(float flSpread, float flCycleTime, BOOL fUseSemi);

public:
	int m_iShell;
private:
	unsigned short m_usFireELITE_LEFT;
	unsigned short m_usFireELITE_RIGHT;
};

class CFiveSeven: public CBasePlayerWeapon
{
public:
	virtual void Spawn();
	virtual void Precache();
	virtual int GetItemInfo(ItemInfo *p);
	virtual BOOL Deploy();
	virtual float GetMaxSpeed() { return m_fMaxSpeed; }
	virtual int iItemSlot() { return PISTOL_SLOT; }
	virtual void PrimaryAttack();
	virtual void SecondaryAttack();
	virtual void Reload();
	virtual void WeaponIdle();
	virtual BOOL UseDecrement()
	{
	#ifdef CLIENT_WEAPONS
		return TRUE;
	#else
		return FALSE;
	#endif
	}
	virtual BOOL IsPistol() { return TRUE; }

public:
	void FiveSevenFire(float flSpread, float flCycleTime, BOOL fUseSemi);
	void MakeBeam();
	void BeamUpdate();

public:
	int m_iShell;

private:
	unsigned short m_usFireFiveSeven;
};

class CUMP45: public CBasePlayerWeapon
{
public:
	virtual void Spawn();
	virtual void Precache();
	virtual int GetItemInfo(ItemInfo *p);
	virtual BOOL Deploy();
	virtual float GetMaxSpeed() { return UMP45_MAX_SPEED; }
	virtual int iItemSlot() { return PRIMARY_WEAPON_SLOT; }
	virtual void PrimaryAttack();
	virtual void Reload();
	virtual void WeaponIdle();
	virtual BOOL UseDecrement()
	{
	#ifdef CLIENT_WEAPONS
		return TRUE;
	#else
		return FALSE;
	#endif
	}

public:
	void UMP45Fire(float flSpread, float flCycleTime, BOOL fUseAutoAim);

	int m_iShell;
	int iShellOn;

private:
	unsigned short m_usFireUMP45;
};

class CSG550: public CBasePlayerWeapon
{
public:
	virtual void Spawn();
	virtual void Precache();
	virtual int GetItemInfo(ItemInfo *p);
	virtual BOOL Deploy();
	virtual float GetMaxSpeed();
	virtual int iItemSlot() { return PRIMARY_WEAPON_SLOT; }
	virtual void PrimaryAttack();
	virtual void SecondaryAttack();
	virtual void Reload();
	virtual void WeaponIdle();
	virtual BOOL UseDecrement()
	{
	#ifdef CLIENT_WEAPONS
		return TRUE;
	#else
		return FALSE;
	#endif
	}

public:
	void SG550Fire(float flSpread, float flCycleTime, BOOL fUseAutoAim);
	int m_iShell;

private:
	unsigned short m_usFireSG550;
};

class CGalil: public CBasePlayerWeapon
{
public:
	virtual void Spawn();
	virtual void Precache();
	virtual int GetItemInfo(ItemInfo *p);
	virtual BOOL Deploy();
	virtual float GetMaxSpeed() { return GALIL_MAX_SPEED; }
	virtual int iItemSlot() { return PRIMARY_WEAPON_SLOT; }
	virtual void PrimaryAttack();
	virtual void SecondaryAttack();
	virtual void Reload();
	virtual void WeaponIdle();
	virtual BOOL UseDecrement()
	{
	#ifdef CLIENT_WEAPONS
		return TRUE;
	#else
		return FALSE;
	#endif
	}

public:
	void GalilFire(float flSpread, float flCycleTime, BOOL fUseAutoAim);

public:
	int m_iShell;
	int iShellOn;

private:
	unsigned short m_usFireGalil;
};

class CFamas: public CBasePlayerWeapon
{
public:
	virtual void Spawn();
	virtual void Precache();
	virtual int GetItemInfo(ItemInfo *p);
	virtual BOOL Deploy();
	virtual float GetMaxSpeed() { return FAMAS_MAX_SPEED; }
	virtual int iItemSlot() { return PRIMARY_WEAPON_SLOT; }
	virtual void PrimaryAttack();
	virtual void SecondaryAttack();
	virtual void Reload();
	virtual void WeaponIdle();
	virtual BOOL UseDecrement()
	{
	#ifdef CLIENT_WEAPONS
		return TRUE;
	#else
		return FALSE;
	#endif
	}

public:
	void FamasFire(float flSpread, float flCycleTime, BOOL fUseAutoAim, BOOL bFireBurst);

public:
	int m_iShell;
	int iShellOn;
};

extern short g_sModelIndexLaser;
extern const char *g_pModelNameLaser;
extern short g_sModelIndexLaserDot;

extern short g_sModelIndexFireball;
extern short g_sModelIndexSmoke;
extern short g_sModelIndexWExplosion;
extern short g_sModelIndexBubbles;
extern short g_sModelIndexBloodDrop;
extern short g_sModelIndexBloodSpray;
extern short g_sModelIndexSmokePuff;
extern short g_sModelIndexFireball2;
extern short g_sModelIndexFireball3;
extern short g_sModelIndexFireball4;
extern short g_sModelIndexCTGhost;
extern short g_sModelIndexTGhost;
extern short g_sModelIndexC4Glow;

extern short g_sModelIndexRadio;
extern MULTIDAMAGE gMultiDamage;

void FindHullIntersection(const Vector &vecSrc, TraceResult &tr, float *mins, float *maxs, edict_t *pEntity);
void AnnounceFlashInterval(float interval, float offset = 0);

int MaxAmmoCarry(int iszName);
int MaxAmmoCarry(const char *szName);
int MaxAmmoCarry(WeaponIdType ammoType);

void ClearMultiDamage();
void ApplyMultiDamage(entvars_t *pevInflictor, entvars_t *pevAttacker);
void AddMultiDamage(entvars_t *pevInflictor, CBaseEntity *pEntity, float flDamage, int bitsDamageType);
void SpawnBlood(Vector vecSpot, int bloodColor, float flDamage);
int DamageDecal(CBaseEntity *pEntity, int bitsDamageType);
void DecalGunshot(TraceResult *pTrace, int iBulletType, bool ClientOnly, entvars_t *pShooter, bool bHitMetal);
void EjectBrass(const Vector &vecOrigin, const Vector &vecLeft, const Vector &vecVelocity, float rotation, int model, int soundtype, int entityIndex);
void EjectBrass2(const Vector &vecOrigin, const Vector &vecVelocity, float rotation, int model, int soundtype, entvars_t *pev);
void AddAmmoNameToAmmoRegistry(const char *szAmmoname);
void UTIL_PrecacheOtherWeapon(const char *szClassname);
void UTIL_PrecacheOtherWeapon2(const char *szClassname);
void W_Precache();
BOOL CanAttack(float attack_time, float curtime, BOOL isPredicted);

#endif // WEAPONS_H

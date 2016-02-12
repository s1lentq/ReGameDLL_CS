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

#include "weapontype.h"

class CBasePlayer;

#define MAX_WEAPONS			32
#define MAX_NORMAL_BATTERY		100.0f

#define ITEM_FLAG_SELECTONEMPTY		1
#define ITEM_FLAG_NOAUTORELOAD		2
#define ITEM_FLAG_NOAUTOSWITCHEMPTY	4
#define ITEM_FLAG_LIMITINWORLD		8
#define ITEM_FLAG_EXHAUSTIBLE		16	// A player can totally exhaust their ammo supply and lose this weapon

#define WEAPON_IS_ONTARGET		0x40

#define ARMOR_TYPE_EMPTY		0
#define ARMOR_TYPE_KEVLAR		1	// Armor
#define ARMOR_TYPE_HELMET		2	// Armor and helmet

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

// custom enum
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

/* <1d04c6> ../cstrike/dlls/weapons.cpp:2156 */
class CArmoury: public CBaseEntity
{
public:
	virtual void Spawn();
	virtual void Precache();
	virtual void Restart();
	virtual void KeyValue(KeyValueData *pkvd);

#ifdef HOOK_GAMEDLL

	void Spawn_();
	void Precache_();
	void Restart_();
	void KeyValue_(KeyValueData *pkvd);

#endif // HOOK_GAMEDLL

public:
	void EXPORT ArmouryTouch(CBaseEntity *pOther);

public:
	int m_iItem;
	int m_iCount;
	int m_iInitialCount;
	bool m_bAlreadyCounted;
};

/* <14ed46> ../cstrike/dlls/weapons.h:56 */
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

#ifdef HOOK_GAMEDLL

	void Spawn_();
	int Save_(CSave &save);
	int Restore_(CRestore &restore);
	void Killed_(entvars_t *pevAttacker, int iGib);
	void Use_(CBaseEntity *pActivator, CBaseEntity *pCaller, USE_TYPE useType, float value);
	void BounceSound_();

#endif // HOOK_GAMEDLL

public:
	enum SATCHELCODE
	{
		SATCHEL_DETONATE,
		SATCHEL_RELEASE
	};
public:
	static CGrenade *ShootTimed(entvars_t *pevOwner, Vector vecStart, Vector vecVelocity, float time);
	static CGrenade *ShootTimed2(entvars_t *pevOwner, Vector vecStart, Vector vecVelocity, float time, int iTeam, unsigned short usEvent);
	NOXREF static CGrenade *ShootContact(entvars_t *pevOwner, Vector vecStart, Vector vecVelocity);
	static CGrenade *ShootSmokeGrenade(entvars_t *pevOwner, Vector vecStart, Vector vecVelocity, float time, unsigned short usEvent);
	static CGrenade *ShootSatchelCharge(entvars_t *pevOwner, Vector vecStart, Vector vecVelocity);
	NOXREF static void UseSatchelCharges(entvars_t *pevOwner, SATCHELCODE code);
public:
	void Explode(Vector vecSrc, Vector vecAim);
	void Explode(TraceResult *pTrace, int bitsDamageType);
	void Explode2(TraceResult *pTrace, int bitsDamageType);
	void Explode3(TraceResult *pTrace, int bitsDamageType);
	NOXREF void SG_Explode(TraceResult *pTrace, int bitsDamageType);

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

/* <2c9f2c> ../cstrike/dlls/weapons.h:238 */
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

#ifdef HOOK_GAMEDLL

	int Save_(CSave &save);
	int Restore_(CRestore &restore);
	void SetObjectCollisionBox_();
	CBaseEntity *Respawn_();
	int AddToPlayer_(CBasePlayer *pPlayer);
	void Holster_(int skiplocal);
	void Drop_();
	void Kill_();
	void AttachToPlayer_(CBasePlayer *pPlayer);

#endif // HOOK_GAMEDLL

public:
	void EXPORT DestroyItem();
	void EXPORT DefaultTouch(CBaseEntity *pOther);
	void EXPORT FallThink();
	void EXPORT Materialize();
	void EXPORT AttemptToMaterialize();

	void FallInit();
	void CheckRespawn();

public:
	inline int iItemPosition() const	{ return IMPL(ItemInfoArray)[ m_iId ].iPosition; }
	inline const char *pszAmmo1() const	{ return IMPL(ItemInfoArray)[ m_iId ].pszAmmo1; }
	inline int iMaxAmmo1() const		{ return IMPL(ItemInfoArray)[ m_iId ].iMaxAmmo1; }
	inline const char *pszAmmo2() const	{ return IMPL(ItemInfoArray)[ m_iId ].pszAmmo2; }
	inline int iMaxAmmo2() const		{ return IMPL(ItemInfoArray)[ m_iId ].iMaxAmmo2; }
	inline const char *pszName() const	{ return IMPL(ItemInfoArray)[ m_iId ].pszName; }
	inline int iMaxClip() const		{ return IMPL(ItemInfoArray)[ m_iId ].iMaxClip; }
	inline int iWeight() const		{ return IMPL(ItemInfoArray)[ m_iId ].iWeight; }
	inline int iFlags() const		{ return IMPL(ItemInfoArray)[ m_iId ].iFlags; }

public:
	static TYPEDESCRIPTION IMPL(m_SaveData)[3];
	static ItemInfo IMPL(ItemInfoArray)[32];
	static AmmoInfo IMPL(AmmoInfoArray)[32];

	CBasePlayer *m_pPlayer;
	CBasePlayerItem *m_pNext;
	int m_iId;
};

/* <2c9f52> ../cstrike/dlls/weapons.h:307 */
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

#ifdef HOOK_GAMEDLL

	int Save_(CSave &save);
	int Restore_(CRestore &restore);
	int AddToPlayer_(CBasePlayer *pPlayer);
	int AddDuplicate_(CBasePlayerItem *pItem);
	BOOL CanDeploy_();
	void Holster_(int skiplocal = 0);
	void ItemPostFrame_();
	int PrimaryAmmoIndex_();
	int SecondaryAmmoIndex_();
	int UpdateClientData_(CBasePlayer *pPlayer);
	int ExtractAmmo_(CBasePlayerWeapon *pWeapon);
	int ExtractClipAmmo_(CBasePlayerWeapon *pWeapon);
	BOOL PlayEmptySound_();
	void ResetEmptySound_();
	void SendWeaponAnim_(int iAnim, int skiplocal = 0);
	BOOL IsUseable_();
	void RetireWeapon_();

#endif // HOOK_GAMEDLL

public:
	BOOL AddPrimaryAmmo(int iCount, char *szName, int iMaxClip, int iMaxCarry);
	BOOL AddSecondaryAmmo(int iCount, char *szName, int iMaxCarry);
	BOOL DefaultDeploy(char *szViewModel, char *szWeaponModel, int iAnim, char *szAnimExt, int skiplocal = 0);
	int DefaultReload(int iClipSize, int iAnim, float fDelay);
	void FireRemaining(int &shotsFired, float &shootTime, BOOL isGlock18);
	void KickBack(float up_base, float lateral_base, float up_modifier, float lateral_modifier, float up_max, float lateral_max, int direction_change);
	void EjectBrassLate();
	NOXREF void MakeBeam();
	NOXREF void BeamUpdate();
	void ReloadSound();
	float GetNextAttackDelay(float delay);
	float GetNextAttackDelay2(float delay);
	bool HasSecondaryAttack();
	BOOL IsPistol() { return (m_iId == WEAPON_USP || m_iId == WEAPON_GLOCK18 || m_iId == WEAPON_P228 || m_iId == WEAPON_DEAGLE || m_iId == WEAPON_ELITE || m_iId == WEAPON_FIVESEVEN); }
	void SetPlayerShieldAnim();
	void ResetPlayerShieldAnim();
	bool ShieldSecondaryFire(int iUpAnim, int iDownAnim);

public:
	static TYPEDESCRIPTION IMPL(m_SaveData)[7];

	int m_iPlayEmptySound;
	int m_fFireOnEmpty;
	float m_flNextPrimaryAttack;
	float m_flNextSecondaryAttack;
	float m_flTimeWeaponIdle;
	int m_iPrimaryAmmoType;
	int m_iSecondaryAmmoType;
	int m_iClip;
	int m_iClientClip;
	int m_iClientWeaponState;
	int m_fInReload;
	int m_fInSpecialReload;
	int m_iDefaultAmmo;
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
	float m_flPrevPrimaryAttack;
	float m_flLastFireTime;
};

/* <9716> ../cstrike/dlls/weapons.h:429 */
class CBasePlayerAmmo: public CBaseEntity
{
public:
	virtual void Spawn();
	virtual BOOL AddAmmo(CBaseEntity *pOther) { return TRUE; }
	virtual CBaseEntity *Respawn();

#ifdef HOOK_GAMEDLL

	void Spawn_();
	CBaseEntity *Respawn_();

#endif // HOOK_GAMEDLL

public:
	void EXPORT DefaultTouch(CBaseEntity *pOther);
	void EXPORT Materialize();
};

/* <1d03c1> ../cstrike/dlls/weapons.h:508 */
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

#ifdef HOOK_GAMEDLL

	void Spawn_();
	void Precache_();
	void KeyValue_(KeyValueData *pkvd);
	int Save_(CSave &save);
	int Restore_(CRestore &restore);
	void SetObjectCollisionBox_();
	void Touch_(CBaseEntity *pOther);

#endif // HOOK_GAMEDLL

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

/* <2ba15a> ../cstrike/dlls/weapons.h:573 */
class CUSP: public CBasePlayerWeapon
{
public:
	virtual void Spawn();
	virtual void Precache();
	virtual int GetItemInfo(ItemInfo *p);
	virtual BOOL Deploy();
	virtual float GetMaxSpeed()	{ return m_fMaxSpeed; }
	virtual int iItemSlot()		{ return PISTOL_SLOT; }
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
	virtual BOOL IsPistol()		{ return TRUE; }

#ifdef HOOK_GAMEDLL

	void Spawn_();
	void Precache_();
	int GetItemInfo_(ItemInfo *p);
	BOOL Deploy_();
	void PrimaryAttack_();
	void SecondaryAttack_();
	void Reload_();
	void WeaponIdle_();

#endif // HOOK_GAMEDLL

public:
	void USPFire(float flSpread, float flCycleTime, BOOL fUseSemi);
	NOXREF void MakeBeam();
	NOXREF void BeamUpdate();

	int m_iShell;

private:
	unsigned short m_usFireUSP;
};

/* <28adc9> ../cstrike/dlls/weapons.h:599 */
class CMP5N: public CBasePlayerWeapon
{
public:
	virtual void Spawn();
	virtual void Precache();
	virtual int GetItemInfo(ItemInfo *p);
	virtual BOOL Deploy();
	virtual float GetMaxSpeed()	{ return MP5N_MAX_SPEED; }
	int iItemSlot()			{ return PRIMARY_WEAPON_SLOT; }
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

#ifdef HOOK_GAMEDLL

	void Spawn_();
	void Precache_();
	int GetItemInfo_(ItemInfo *p);
	BOOL Deploy_();
	void PrimaryAttack_();
	void Reload_();
	void WeaponIdle_();

#endif // HOOK_GAMEDLL

public:
	void MP5NFire(float flSpread, float flCycleTime, BOOL fUseAutoAim);

	int m_iShell;
	int iShellOn;

private:
	unsigned short m_usFireMP5N;
};

/* <2a553c> ../cstrike/dlls/weapons.h:624 */
class CSG552: public CBasePlayerWeapon
{
public:
	virtual void Spawn();
	virtual void Precache();
	virtual int GetItemInfo(ItemInfo *p);
	virtual BOOL Deploy();
	virtual float GetMaxSpeed();
	virtual int iItemSlot()		{ return PRIMARY_WEAPON_SLOT; }
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

#ifdef HOOK_GAMEDLL

	void Spawn_();
	void Precache_();
	int GetItemInfo_(ItemInfo *p);
	BOOL Deploy_();
	float GetMaxSpeed_();
	void PrimaryAttack_();
	void SecondaryAttack_();
	void Reload_();
	void WeaponIdle_();

#endif // HOOK_GAMEDLL

public:
	void SG552Fire(float flSpread, float flCycleTime, BOOL fUseAutoAim);

	int m_iShell;
	int iShellOn;

private:
	unsigned short m_usFireSG552;
};

/* <234730> ../cstrike/dlls/weapons.h:648 */
class CAK47: public CBasePlayerWeapon
{
public:
	virtual void Spawn();
	virtual void Precache();
	virtual int GetItemInfo(ItemInfo *p);
	virtual BOOL Deploy();
	virtual float GetMaxSpeed()	{ return AK47_MAX_SPEED; }
	virtual int iItemSlot()		{ return PRIMARY_WEAPON_SLOT; }
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

#ifdef HOOK_GAMEDLL

	void Spawn_();
	void Precache_();
	int GetItemInfo_(ItemInfo *p);
	BOOL Deploy_();
	void PrimaryAttack_();
	void SecondaryAttack_();
	void Reload_();
	void WeaponIdle_();

#endif // HOOK_GAMEDLL

public:
	void AK47Fire(float flSpread, float flCycleTime, BOOL fUseAutoAim);

	int m_iShell;
	int iShellOn;

private:
	unsigned short m_usFireAK47;
};

/* <239b82> ../cstrike/dlls/weapons.h:672 */
class CAUG: public CBasePlayerWeapon
{
public:
	virtual void Spawn();
	virtual void Precache();
	virtual int GetItemInfo(ItemInfo *p);
	virtual BOOL Deploy();
	virtual float GetMaxSpeed()	{ return AUG_MAX_SPEED; }
	virtual int iItemSlot()		{ return PRIMARY_WEAPON_SLOT; }
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

#ifdef HOOK_GAMEDLL

	void Spawn_();
	void Precache_();
	int GetItemInfo_(ItemInfo *p);
	BOOL Deploy_();
	void PrimaryAttack_();
	void SecondaryAttack_();
	void Reload_();
	void WeaponIdle_();

#endif // HOOK_GAMEDLL

public:
	void AUGFire(float flSpread, float flCycleTime, BOOL fUseAutoAim);

	int m_iShell;
	int iShellOn;

private:
	unsigned short m_usFireAug;
};

/* <23ef02> ../cstrike/dlls/weapons.h:697 */
class CAWP: public CBasePlayerWeapon
{
public:
	virtual void Spawn();
	virtual void Precache();
	virtual int GetItemInfo(ItemInfo *p);
	virtual BOOL Deploy();
	virtual float GetMaxSpeed();
	virtual int iItemSlot()		{ return PRIMARY_WEAPON_SLOT; }
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

#ifdef HOOK_GAMEDLL

	void Spawn_();
	void Precache_();
	int GetItemInfo_(ItemInfo *p);
	BOOL Deploy_();
	float GetMaxSpeed_();
	void PrimaryAttack_();
	void SecondaryAttack_();
	void Reload_();
	void WeaponIdle_();

#endif // HOOK_GAMEDLL

public:
	void AWPFire(float flSpread, float flCycleTime, BOOL fUseAutoAim);

	int m_iShell;

private:
	unsigned short m_usFireAWP;
};

/* <245949> ../cstrike/dlls/weapons.h:721 */
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
	virtual int iItemSlot()		{ return C4_SLOT; }
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

#ifdef HOOK_GAMEDLL

	void Spawn_();
	void Precache_();
	void KeyValue_(KeyValueData *pkvd);
	void Use_(CBaseEntity *pActivator, CBaseEntity *pCaller, USE_TYPE useType, float value);
	int GetItemInfo_(ItemInfo *p);
	BOOL Deploy_();
	void Holster_(int skiplocal);
	float GetMaxSpeed_();
	void PrimaryAttack_();
	void WeaponIdle_();

#endif // HOOK_GAMEDLL

public:
	bool m_bStartedArming;
	bool m_bBombPlacedAnimation;
	float m_fArmedTime;

private:
	bool m_bHasShield;
};

/* <24afee> ../cstrike/dlls/weapons.h:750 */
class CDEAGLE: public CBasePlayerWeapon
{
public:
	virtual void Spawn();
	virtual void Precache();
	virtual int GetItemInfo(ItemInfo *p);
	virtual BOOL Deploy();
	virtual float GetMaxSpeed()	{ return m_fMaxSpeed; }
	virtual int iItemSlot()		{ return PISTOL_SLOT; }
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
	virtual BOOL IsPistol()		{ return TRUE; }

#ifdef HOOK_GAMEDLL

	void Spawn_();
	void Precache_();
	int GetItemInfo_(ItemInfo *p);
	BOOL Deploy_();
	void PrimaryAttack_();
	void SecondaryAttack_();
	void Reload_();
	void WeaponIdle_();

#endif // HOOK_GAMEDLL

public:
	void DEAGLEFire(float flSpread, float flCycleTime, BOOL fUseSemi);

	int m_iShell;

private:
	unsigned short m_usFireDeagle;
};

/* <25ab17> ../cstrike/dlls/weapons.h:778 */
class CFlashbang: public CBasePlayerWeapon
{
public:
	virtual void Spawn();
	virtual void Precache();
	virtual int GetItemInfo(ItemInfo *p);
	virtual BOOL CanDeploy();
	virtual BOOL CanDrop()		{ return FALSE; }
	virtual BOOL Deploy();
	virtual void Holster(int skiplocal);
	virtual float GetMaxSpeed()	{ return m_fMaxSpeed; }
	virtual int iItemSlot()		{ return GRENADE_SLOT; }
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
	#endif // REGAMEDLL_FIXES
	}

#ifdef HOOK_GAMEDLL

	void Spawn_();
	void Precache_();
	int GetItemInfo_(ItemInfo *p);
	BOOL CanDeploy_();
	BOOL Deploy_();
	void Holster_(int skiplocal);
	void PrimaryAttack_();
	void SecondaryAttack_();
	void WeaponIdle_();

#endif // HOOK_GAMEDLL

public:
	bool ShieldSecondaryFire(int iUpAnim, int iDownAnim);
	void SetPlayerShieldAnim();
	void ResetPlayerShieldAnim();
};

/* <26006d> ../cstrike/dlls/weapons.h:803 */
class CG3SG1: public CBasePlayerWeapon
{
public:
	virtual void Spawn();
	virtual void Precache();
	virtual int GetItemInfo(ItemInfo *p);
	virtual BOOL Deploy();
	virtual float GetMaxSpeed();
	virtual int iItemSlot()		{ return PRIMARY_WEAPON_SLOT; }
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

#ifdef HOOK_GAMEDLL

	void Spawn_();
	void Precache_();
	int GetItemInfo_(ItemInfo *p);
	BOOL Deploy_();
	float GetMaxSpeed_();
	void PrimaryAttack_();
	void SecondaryAttack_();
	void Reload_();
	void WeaponIdle_();

#endif // HOOK_GAMEDLL

public:
	void G3SG1Fire(float flSpread, float flCycleTime, BOOL fUseAutoAim);

	int m_iShell;

private:
	unsigned short m_usFireG3SG1;
};

/* <2655b2> ../cstrike/dlls/weapons.h:828 */
class CGLOCK18: public CBasePlayerWeapon
{
public:
	virtual void Spawn();
	virtual void Precache();
	virtual int GetItemInfo(ItemInfo *p);
	virtual BOOL Deploy();
	virtual float GetMaxSpeed()	{ return m_fMaxSpeed; }
	virtual int iItemSlot()		{ return PISTOL_SLOT; }
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
	virtual BOOL IsPistol()		{ return TRUE; }

#ifdef HOOK_GAMEDLL

	void Spawn_();
	void Precache_();
	int GetItemInfo_(ItemInfo *p);
	BOOL Deploy_();
	void PrimaryAttack_();
	void SecondaryAttack_();
	void Reload_();
	void WeaponIdle_();

#endif // HOOK_GAMEDLL

public:
	void GLOCK18Fire(float flSpread, float flCycleTime, BOOL bFireBurst);

public:
	int m_iShell;
	bool m_bBurstFire;
};

/* <26a48a> ../cstrike/dlls/weapons.h:852 */
class CHEGrenade: public CBasePlayerWeapon
{
public:
	virtual void Spawn();
	virtual void Precache();
	virtual int GetItemInfo(ItemInfo *p);
	virtual BOOL CanDeploy();
	virtual BOOL CanDrop()		{ return FALSE; }
	virtual BOOL Deploy();
	virtual void Holster(int skiplocal);
	virtual float GetMaxSpeed()	{ return m_fMaxSpeed; }
	virtual int iItemSlot()		{ return GRENADE_SLOT; }
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

#ifdef HOOK_GAMEDLL

	void Spawn_();
	void Precache_();
	int GetItemInfo_(ItemInfo *p);
	BOOL CanDeploy_();
	BOOL Deploy_();
	void Holster_(int skiplocal);
	void PrimaryAttack_();
	void SecondaryAttack_();
	void WeaponIdle_();

#endif // HOOK_GAMEDLL

public:
	bool ShieldSecondaryFire(int iUpAnim, int iDownAnim);
	void SetPlayerShieldAnim();
	void ResetPlayerShieldAnim();

public:
	unsigned short m_usCreateExplosion;
};

/* <26f804> ../cstrike/dlls/weapons.h:878 */
class CKnife: public CBasePlayerWeapon
{
public:
	virtual void Spawn();
	virtual void Precache();
	virtual int GetItemInfo(ItemInfo *p);
	virtual BOOL CanDrop()		{ return FALSE; }
	virtual BOOL Deploy();
	virtual void Holster(int skiplocal);
	virtual float GetMaxSpeed()	{ return m_fMaxSpeed; }
	virtual int iItemSlot()		{ return KNIFE_SLOT; }
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

#ifdef HOOK_GAMEDLL

	void Spawn_();
	void Precache_();
	int GetItemInfo_(ItemInfo *p);
	BOOL Deploy_();
	void Holster_(int skiplocal);
	void PrimaryAttack_();
	void SecondaryAttack_();
	void WeaponIdle_();

#endif // HOOK_GAMEDLL

public:
	void EXPORT SwingAgain();
	void EXPORT Smack();

	NOXREF void WeaponAnimation(int iAnimation);
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

/* <275d5a> ../cstrike/dlls/weapons.h:910 */
class CM249: public CBasePlayerWeapon
{
public:
	virtual void Spawn();
	virtual void Precache();
	virtual int GetItemInfo(ItemInfo *p);
	virtual BOOL Deploy();
	virtual float GetMaxSpeed()	{ return M249_MAX_SPEED; }
	virtual int iItemSlot()		{ return PRIMARY_WEAPON_SLOT; }
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

#ifdef HOOK_GAMEDLL

	void Spawn_();
	void Precache_();
	int GetItemInfo_(ItemInfo *p);
	BOOL Deploy_();
	void PrimaryAttack_();
	void Reload_();
	void WeaponIdle_();

#endif // HOOK_GAMEDLL

public:
	void M249Fire(float flSpread, float flCycleTime, BOOL fUseAutoAim);

	int m_iShell;
	int iShellOn;

private:
	unsigned short m_usFireM249;
};

/* <27b175> ../cstrike/dlls/weapons.h:934 */
class CM3: public CBasePlayerWeapon
{
public:
	virtual void Spawn();
	virtual void Precache();
	virtual int GetItemInfo(ItemInfo *p);
	virtual BOOL Deploy();
	virtual float GetMaxSpeed()	{ return M3_MAX_SPEED; }
	virtual int iItemSlot()		{ return PRIMARY_WEAPON_SLOT; }
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

#ifdef HOOK_GAMEDLL

	void Spawn_();
	void Precache_();
	int GetItemInfo_(ItemInfo *p);
	BOOL Deploy_();
	void PrimaryAttack_();
	void Reload_();
	void WeaponIdle_();

#endif // HOOK_GAMEDLL

public:
	int m_iShell;
	float m_flPumpTime;

private:
	unsigned short m_usFireM3;
};

/* <280488> ../cstrike/dlls/weapons.h:961 */
class CM4A1: public CBasePlayerWeapon
{
public:
	virtual void Spawn();
	virtual void Precache();
	virtual int GetItemInfo(ItemInfo *p);
	virtual BOOL Deploy();
	virtual float GetMaxSpeed();
	virtual int iItemSlot()		{ return PRIMARY_WEAPON_SLOT; }
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

#ifdef HOOK_GAMEDLL

	void Spawn_();
	void Precache_();
	int GetItemInfo_(ItemInfo *p);
	BOOL Deploy_();
	float GetMaxSpeed_();
	void PrimaryAttack_();
	void SecondaryAttack_();
	void Reload_();
	void WeaponIdle_();

#endif // HOOK_GAMEDLL

public:
	void M4A1Fire(float flSpread, float flCycleTime, BOOL fUseAutoAim);

	int m_iShell;
	int iShellOn;

private:
	unsigned short m_usFireM4A1;
};

/* <285993> ../cstrike/dlls/weapons.h:987 */
class CMAC10: public CBasePlayerWeapon
{
public:
	virtual void Spawn();
	virtual void Precache();
	virtual int GetItemInfo(ItemInfo *p);
	virtual BOOL Deploy();
	virtual float GetMaxSpeed()	{ return MAC10_MAX_SPEED; }
	virtual int iItemSlot()		{ return PRIMARY_WEAPON_SLOT; }
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

#ifdef HOOK_GAMEDLL

	void Spawn_();
	void Precache_();
	int GetItemInfo_(ItemInfo *p);
	BOOL Deploy_();
	void PrimaryAttack_();
	void Reload_();
	void WeaponIdle_();

#endif // HOOK_GAMEDLL

public:
	void MAC10Fire(float flSpread, float flCycleTime, BOOL fUseAutoAim);

	int m_iShell;
	int iShellOn;

private:
	unsigned short m_usFireMAC10;
};

/* <2902c1> ../cstrike/dlls/weapons.h:1011 */
class CP228: public CBasePlayerWeapon
{
public:
	virtual void Spawn();
	virtual void Precache();
	virtual int GetItemInfo(ItemInfo *p);
	virtual BOOL Deploy();
	virtual float GetMaxSpeed()	{ return m_fMaxSpeed; }
	virtual int iItemSlot()		{ return PISTOL_SLOT; }
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
	virtual BOOL IsPistol()		{ return TRUE; }

#ifdef HOOK_GAMEDLL

	void Spawn_();
	void Precache_();
	int GetItemInfo_(ItemInfo *p);
	BOOL Deploy_();
	void PrimaryAttack_();
	void SecondaryAttack_();
	void Reload_();
	void WeaponIdle_();

#endif // HOOK_GAMEDLL

public:
	void P228Fire(float flSpread, float flCycleTime, BOOL fUseSemi);
	NOXREF void MakeBeam();
	NOXREF void BeamUpdate();

public:
	int m_iShell;

private:
	unsigned short m_usFireP228;
};

/* <295740> ../cstrike/dlls/weapons.h:1039 */
class CP90: public CBasePlayerWeapon
{
public:
	virtual void Spawn();
	virtual void Precache();
	virtual int GetItemInfo(ItemInfo *p);
	virtual BOOL Deploy();
	virtual float GetMaxSpeed();
	virtual int iItemSlot()		{ return PRIMARY_WEAPON_SLOT; }
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

#ifdef HOOK_GAMEDLL

	void Spawn_();
	void Precache_();
	int GetItemInfo_(ItemInfo *p);
	BOOL Deploy_();
	float GetMaxSpeed_();
	void PrimaryAttack_();
	void Reload_();
	void WeaponIdle_();

#endif // HOOK_GAMEDLL

public:
	void P90Fire(float flSpread, float flCycleTime, BOOL fUseAutoAim);

	int m_iShell;
	int iShellOn;

private:
	unsigned short m_usFireP90;
};

/* <29abe0> ../cstrike/dlls/weapons.h:1063 */
class CSCOUT: public CBasePlayerWeapon
{
public:
	virtual void Spawn();
	virtual void Precache();
	virtual int GetItemInfo(ItemInfo *p);
	virtual BOOL Deploy();
	virtual float GetMaxSpeed();
	virtual int iItemSlot()		{ return PRIMARY_WEAPON_SLOT; }
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

#ifdef HOOK_GAMEDLL

	void Spawn_();
	void Precache_();
	int GetItemInfo_(ItemInfo *p);
	BOOL Deploy_();
	float GetMaxSpeed_();
	void PrimaryAttack_();
	void SecondaryAttack_();
	void Reload_();
	void WeaponIdle_();

#endif // HOOK_GAMEDLL

public:
	void SCOUTFire(float flSpread, float flCycleTime, BOOL fUseAutoAim);
	int m_iShell;

private:
	unsigned short m_usFireScout;
};

/* <2aa3d5> ../cstrike/dlls/weapons.h:1089 */
class CSmokeGrenade: public CBasePlayerWeapon
{
public:
	virtual void Spawn();
	virtual void Precache();
	virtual int GetItemInfo(ItemInfo *p);
	virtual BOOL CanDeploy();
	virtual BOOL CanDrop()		{ return FALSE; }
	virtual BOOL Deploy();
	virtual void Holster(int skiplocal);
	virtual float GetMaxSpeed()	{ return m_fMaxSpeed; }
	virtual int iItemSlot()		{ return GRENADE_SLOT; }
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

#ifdef HOOK_GAMEDLL

	void Spawn_();
	void Precache_();
	int GetItemInfo_(ItemInfo *p);
	BOOL CanDeploy_();
	BOOL Deploy_();
	void Holster_(int skiplocal);
	void PrimaryAttack_();
	void SecondaryAttack_();
	void WeaponIdle_();

#endif // HOOK_GAMEDLL

public:
	bool ShieldSecondaryFire(int iUpAnim, int iDownAnim);
	void SetPlayerShieldAnim();
	void ResetPlayerShieldAnim();

public:
	unsigned short m_usCreateSmoke;
};

/* <2af8c3> ../cstrike/dlls/weapons.h:1116 */
class CTMP: public CBasePlayerWeapon
{
public:
	virtual void Spawn();
	virtual void Precache();
	virtual int GetItemInfo(ItemInfo *p);
	virtual BOOL Deploy();
	virtual float GetMaxSpeed()	{ return TMP_MAX_SPEED; }
	virtual int iItemSlot()		{ return PRIMARY_WEAPON_SLOT; }
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

#ifdef HOOK_GAMEDLL

	void Spawn_();
	void Precache_();
	int GetItemInfo_(ItemInfo *p);
	BOOL Deploy_();
	void PrimaryAttack_();
	void Reload_();
	void WeaponIdle_();

#endif // HOOK_GAMEDLL

public:
	void TMPFire(float flSpread, float flCycleTime, BOOL fUseAutoAim);

public:
	int m_iShell;
	int iShellOn;

private:
	unsigned short m_usFireTMP;
};

/* <2c9fce> ../cstrike/dlls/weapons.h:1141 */
class CXM1014: public CBasePlayerWeapon
{
public:
	virtual void Spawn();
	virtual void Precache();
	virtual int GetItemInfo(ItemInfo *p);
	virtual BOOL Deploy();
	virtual float GetMaxSpeed()	{ return XM1014_MAX_SPEED; }
	virtual int iItemSlot()		{ return PRIMARY_WEAPON_SLOT; }
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

#ifdef HOOK_GAMEDLL

	void Spawn_();
	void Precache_();
	int GetItemInfo_(ItemInfo *p);
	BOOL Deploy_();
	void PrimaryAttack_();
	void Reload_();
	void WeaponIdle_();

#endif // HOOK_GAMEDLL

public:
	int m_iShell;
	float m_flPumpTime;

private:
	unsigned short m_usFireXM1014;
};

/* <2503f9> ../cstrike/dlls/weapons.h:1167 */
class CELITE: public CBasePlayerWeapon
{
public:
	virtual void Spawn();
	virtual void Precache();
	virtual int GetItemInfo(ItemInfo *p);
	virtual BOOL Deploy();
	virtual float GetMaxSpeed()	{ return ELITE_MAX_SPEED; }
	virtual int iItemSlot()		{ return PISTOL_SLOT; }
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
	virtual BOOL IsPistol()		{ return TRUE; }

#ifdef HOOK_GAMEDLL

	void Spawn_();
	void Precache_();
	int GetItemInfo_(ItemInfo *p);
	BOOL Deploy_();
	void PrimaryAttack_();
	void Reload_();
	void WeaponIdle_();

#endif // HOOK_GAMEDLL

public:
	void ELITEFire(float flSpread, float flCycleTime, BOOL fUseSemi);

public:
	int m_iShell;
	unsigned short m_usFireELITE_LEFT;
	unsigned short m_usFireELITE_RIGHT;
};

/* <255b29> ../cstrike/dlls/weapons.h:1192 */
class CFiveSeven: public CBasePlayerWeapon
{
public:
	virtual void Spawn();
	virtual void Precache();
	virtual int GetItemInfo(ItemInfo *p);
	virtual BOOL Deploy();
	virtual float GetMaxSpeed()	{ return m_fMaxSpeed; }
	virtual int iItemSlot()		{ return PISTOL_SLOT; }
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
	virtual BOOL IsPistol()		{ return TRUE; }

#ifdef HOOK_GAMEDLL

	void Spawn_();
	void Precache_();
	int GetItemInfo_(ItemInfo *p);
	BOOL Deploy_();
	void PrimaryAttack_();
	void SecondaryAttack_();
	void Reload_();
	void WeaponIdle_();

#endif // HOOK_GAMEDLL

public:
	void FiveSevenFire(float flSpread, float flCycleTime, BOOL fUseSemi);
	NOXREF void MakeBeam();
	NOXREF void BeamUpdate();

public:
	int m_iShell;

private:
	unsigned short m_usFireFiveSeven;
};

/* <2b4cf9> ../cstrike/dlls/weapons.h:1219 */
class CUMP45: public CBasePlayerWeapon
{
public:
	virtual void Spawn();
	virtual void Precache();
	virtual int GetItemInfo(ItemInfo *p);
	virtual BOOL Deploy();
	virtual float GetMaxSpeed()	{ return UMP45_MAX_SPEED; }
	virtual int iItemSlot()		{ return PRIMARY_WEAPON_SLOT; }
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

#ifdef HOOK_GAMEDLL

	void Spawn_();
	void Precache_();
	int GetItemInfo_(ItemInfo *p);
	BOOL Deploy_();
	void PrimaryAttack_();
	void Reload_();
	void WeaponIdle_();

#endif // HOOK_GAMEDLL

public:
	void UMP45Fire(float flSpread, float flCycleTime, BOOL fUseAutoAim);

public:
	int m_iShell;
	int iShellOn;

private:
	unsigned short m_usFireUMP45;
};

/* <2a00b3> ../cstrike/dlls/weapons.h:1244 */
class CSG550: public CBasePlayerWeapon
{
public:
	virtual void Spawn();
	virtual void Precache();
	virtual int GetItemInfo(ItemInfo *p);
	virtual BOOL Deploy();
	virtual float GetMaxSpeed();
	virtual int iItemSlot()		{ return PRIMARY_WEAPON_SLOT; }
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

#ifdef HOOK_GAMEDLL

	void Spawn_();
	void Precache_();
	int GetItemInfo_(ItemInfo *p);
	BOOL Deploy_();
	float GetMaxSpeed_();
	void PrimaryAttack_();
	void SecondaryAttack_();
	void Reload_();
	void WeaponIdle_();

#endif // HOOK_GAMEDLL

public:
	void SG550Fire(float flSpread, float flCycleTime, BOOL fUseAutoAim);

public:
	int m_iShell;

private:
	unsigned short m_usFireSG550;
};

/* <2c4bb9> ../cstrike/dlls/weapons.h:1269 */
class CGalil: public CBasePlayerWeapon
{
public:
	virtual void Spawn();
	virtual void Precache();
	virtual int GetItemInfo(ItemInfo *p);
	virtual BOOL Deploy();
	virtual float GetMaxSpeed()	{ return GALIL_MAX_SPEED; }
	virtual int iItemSlot()		{ return PRIMARY_WEAPON_SLOT; }
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

#ifdef HOOK_GAMEDLL

	void Spawn_();
	void Precache_();
	int GetItemInfo_(ItemInfo *p);
	BOOL Deploy_();
	void PrimaryAttack_();
	void SecondaryAttack_();
	void Reload_();
	void WeaponIdle_();

#endif // HOOK_GAMEDLL

public:
	void GalilFire(float flSpread, float flCycleTime, BOOL fUseAutoAim);

public:
	int m_iShell;
	int iShellOn;

private:
	unsigned short m_usFireGalil;
};

/* <2bf676> ../cstrike/dlls/weapons.h:1293 */
class CFamas: public CBasePlayerWeapon
{
public:
	virtual void Spawn();
	virtual void Precache();
	virtual int GetItemInfo(ItemInfo *p);
	virtual BOOL Deploy();
	virtual float GetMaxSpeed()	{ return FAMAS_MAX_SPEED; }
	virtual int iItemSlot()		{ return PRIMARY_WEAPON_SLOT; }
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

#ifdef HOOK_GAMEDLL

	void Spawn_();
	void Precache_();
	int GetItemInfo_(ItemInfo *p);
	BOOL Deploy_();
	void PrimaryAttack_();
	void SecondaryAttack_();
	void Reload_();
	void WeaponIdle_();

#endif // HOOK_GAMEDLL

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
void ClearMultiDamage();
void ApplyMultiDamage(entvars_t *pevInflictor, entvars_t *pevAttacker);
void AddMultiDamage(entvars_t *pevInflictor, CBaseEntity *pEntity, float flDamage, int bitsDamageType);
void SpawnBlood(Vector vecSpot, int bloodColor, float flDamage);
NOXREF int DamageDecal(CBaseEntity *pEntity, int bitsDamageType);
void DecalGunshot(TraceResult *pTrace, int iBulletType, bool ClientOnly, entvars_t *pShooter, bool bHitMetal);
void EjectBrass(const Vector &vecOrigin, const Vector &vecLeft, const Vector &vecVelocity, float rotation, int model, int soundtype, int entityIndex);
NOXREF void EjectBrass2(const Vector &vecOrigin, const Vector &vecVelocity, float rotation, int model, int soundtype, entvars_t *pev);
void AddAmmoNameToAmmoRegistry(const char *szAmmoname);
void UTIL_PrecacheOtherWeapon(const char *szClassname);
NOXREF void UTIL_PrecacheOtherWeapon2(const char *szClassname);
void W_Precache();
BOOL CanAttack(float attack_time, float curtime, BOOL isPredicted);

#endif // WEAPONS_H

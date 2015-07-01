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
#define MAX_NORMAL_BATTERY		100

#define ITEM_FLAG_SELECTONEMPTY		1
#define ITEM_FLAG_NOAUTORELOAD		2
#define ITEM_FLAG_NOAUTOSWITCHEMPTY	4
#define ITEM_FLAG_LIMITINWORLD		8
#define ITEM_FLAG_EXHAUSTIBLE		16 // A player can totally exhaust their ammo supply and lose this weapon

#define WEAPON_IS_ONTARGET		0x40

#define ARMOR_TYPE_EMPTY		0
#define ARMOR_TYPE_KEVLAR		1	// Armor
#define ARMOR_TYPE_HELMET		2	// Armor and helmet

// the maximum amount of ammo each weapon's clip can hold
#define WEAPON_NOCLIP			-1

typedef struct
{
	WeaponType type;
	bool preferred;
	char *buyAlias;

} BuyInfo;
/* size: 12, cachelines: 1, members: 3 */

typedef struct
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

} ItemInfo;
/* size: 44, cachelines: 1, members: 11 */

typedef struct
{
	const char *pszName;
	int iId;

} AmmoInfo;
/* size: 8, cachelines: 1, members: 2 */

typedef struct
{
	CBaseEntity *pEntity;
	float amount;
	int type;

} MULTIDAMAGE;
/* size: 12, cachelines: 1, members: 3 */

/* <1d04c6> ../cstrike/dlls/weapons.cpp:2156 */
class CArmoury: public CBaseEntity
{
public:
	NOBODY virtual void Spawn(void);
	NOBODY virtual void Precache(void);
	NOBODY virtual void Restart(void);
	NOBODY virtual void KeyValue(KeyValueData *pkvd);
public:
	NOBODY void EXPORT ArmouryTouch(CBaseEntity *pOther);
public:
	int m_iItem;
	int m_iCount;
	int m_iInitialCount;
	bool m_bAlreadyCounted;
};/* size: 168, cachelines: 3, members: 5 */

/* <14ed46> ../cstrike/dlls/weapons.h:56 */
class CGrenade: public CBaseMonster
{
public:
	NOBODY virtual void Spawn(void);
	NOBODY virtual int Save(CSave &save);
	NOBODY virtual int Restore(CRestore &restore);
	NOBODY virtual int ObjectCaps(void)
	{
		return ObjectCaps_();
	}
	NOBODY virtual void Killed(entvars_t *pevAttacker,int iGib);
	NOBODY virtual int BloodColor(void)
	{
		return BloodColor_();
	}
	NOBODY virtual void Use(CBaseEntity *pActivator,CBaseEntity *pCaller,USE_TYPE useType,float value);
	NOBODY virtual void BounceSound(void);

#ifdef HOOK_GAMEDLL

	void Spawn_(void);
	int Save_(CSave &save);
	int Restore_(CRestore &restore);
	int ObjectCaps_(void)
	{
		return m_bIsC4 ? FCAP_CONTINUOUS_USE : 0;
	}
	void Killed_(entvars_t *pevAttacker, int iGib);
	int BloodColor_(void)
	{
		return DONT_BLEED;
	}
	void Use_(CBaseEntity *pActivator, CBaseEntity *pCaller, USE_TYPE useType, float value);
	void BounceSound_(void);

#endif // HOOK_GAMEDLL

public:
	typedef enum
	{
		SATCHEL_DETONATE,
		SATCHEL_RELEASE
	} SATCHELCODE;
public:
	NOBODY static CGrenade *ShootTimed(entvars_t *pevOwner, Vector vecStart, Vector vecVelocity, float time);
	NOBODY static CGrenade *ShootTimed2(entvars_t *pevOwner, Vector vecStart, Vector vecVelocity, float time, int iTeam, unsigned short usEvent);
	NOBODY static CGrenade *ShootContact(entvars_t *pevOwner, Vector vecStart, Vector vecVelocity);
	NOBODY static CGrenade *ShootSmokeGrenade(entvars_t *pevOwner, Vector vecStart, Vector vecVelocity, float time, unsigned short usEvent);
	NOBODY static CGrenade *ShootSatchelCharge(entvars_t *pevOwner, Vector vecStart, Vector vecVelocity);
	NOBODY static void UseSatchelCharges(entvars_t *pevOwner, SATCHELCODE code);
public:
	NOBODY void Explode(Vector vecSrc, Vector vecAim);
	NOBODY void Explode(TraceResult *pTrace, int bitsDamageType);
	NOBODY void Explode2(TraceResult *pTrace, int bitsDamageType);
	NOBODY void Explode3(TraceResult *pTrace, int bitsDamageType);
	NOBODY void SG_Explode(TraceResult *pTrace, int bitsDamageType);

	NOBODY void EXPORT Smoke(void);
	NOBODY void EXPORT Smoke2(void);
	NOBODY void EXPORT Smoke3_A(void);
	NOBODY void EXPORT Smoke3_B(void);
	NOBODY void EXPORT Smoke3_C(void);
	NOBODY void EXPORT SG_Smoke(void);
	NOBODY void EXPORT BounceTouch(CBaseEntity *pOther);
	NOBODY void EXPORT SlideTouch(CBaseEntity *pOther);
	void EXPORT C4Touch(CBaseEntity *pOther);
	NOBODY void EXPORT ExplodeTouch(CBaseEntity *pOther);
	NOBODY void EXPORT DangerSoundThink(void);
	NOBODY void EXPORT PreDetonate(void);
	NOBODY void EXPORT Detonate(void);
	NOBODY void EXPORT SG_Detonate(void);
	NOBODY void EXPORT Detonate2(void);
	NOBODY void EXPORT Detonate3(void);
	NOBODY void EXPORT DetonateUse(CBaseEntity *pActivator, CBaseEntity *pCaller, USE_TYPE useType, float value);
	NOBODY void EXPORT TumbleThink(void);
	NOBODY void EXPORT SG_TumbleThink(void);
	NOBODY void EXPORT C4Think(void);

public:

#ifndef HOOK_GAMEDLL
	static TYPEDESCRIPTION m_SaveData[15];
#else
	static TYPEDESCRIPTION (*m_SaveData)[15];
#endif // HOOK_GAMEDLL

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

};/* size: 500, cachelines: 8, members: 26 */

#ifdef HOOK_GAMEDLL

#define ItemInfoArray (*pItemInfoArray)
#define AmmoInfoArray (*pAmmoInfoArray)

#endif // HOOK_GAMEDLL

/* <2c9f2c> ../cstrike/dlls/weapons.h:238 */
class CBasePlayerItem: public CBaseAnimating
{
public:
	NOBODY virtual int Save(CSave &save);
	NOBODY virtual int Restore(CRestore &restore);
	NOBODY virtual void SetObjectCollisionBox(void);
	NOBODY virtual CBaseEntity *Respawn(void);
	NOXREF virtual int AddToPlayer(CBasePlayer *pPlayer);
	virtual int AddDuplicate(CBasePlayerItem *pItem)
	{
		return FALSE;
	}
	virtual int GetItemInfo(ItemInfo *p)
	{
		return 0;
	}
	virtual BOOL CanDeploy(void)
	{
		return TRUE;
	}
	virtual BOOL CanDrop(void)
	{
		return TRUE;
	}
	virtual BOOL Deploy(void)
	{
		return TRUE;
	}
	virtual BOOL IsWeapon(void)
	{
		return FALSE;
	}
	virtual BOOL CanHolster(void)
	{
		return TRUE;
	}
	virtual void Holster(int skiplocal = 0);

	virtual void UpdateItemInfo(void) {}
	virtual void ItemPreFrame(void) {}
	virtual void ItemPostFrame(void) {}

	virtual void Drop(void);
	virtual void Kill(void);

	NOBODY virtual void AttachToPlayer(CBasePlayer *pPlayer);
	virtual int PrimaryAmmoIndex(void)
	{
		return -1;
	}
	virtual int SecondaryAmmoIndex(void)
	{
		return -1;
	}
	virtual int UpdateClientData(CBasePlayer *pPlayer)
	{
		return 0;
	}
	virtual CBasePlayerItem *GetWeaponPtr(void)
	{
		return NULL;
	}
	virtual float GetMaxSpeed(void)
	{
		return 260.0f;
	}
	virtual int iItemSlot(void)
	{
		return 0;
	}

#ifdef HOOK_GAMEDLL

	int Save_(CSave &save);
	int Restore_(CRestore &restore);
	void SetObjectCollisionBox_(void);
	CBaseEntity *Respawn_(void);
	int AddToPlayer_(CBasePlayer *pPlayer);
	//int AddDuplicate_(CBasePlayerItem *pItem);
	//int GetItemInfo_(ItemInfo *p);
	//BOOL CanDeploy_(void);
	//BOOL CanDrop_(void);
	//BOOL Deploy_(void);
	//BOOL IsWeapon_(void);
	//BOOL CanHolster_(void);
	void Holster_(int skiplocal);
	//void UpdateItemInfo_(void);
	//void ItemPreFrame_(void);
	//void ItemPostFrame_(void);
	void Drop_(void);
	void Kill_(void);
	void AttachToPlayer_(CBasePlayer *pPlayer);
	//int PrimaryAmmoIndex_(void);
	//int SecondaryAmmoIndex_(void);
	//int UpdateClientData_(CBasePlayer *pPlayer);
	//CBasePlayerItem *GetWeaponPtr_(void);
	//float GetMaxSpeed_(void);
	//int iItemSlot_(void);

#endif // HOOK_GAMEDLL

public:
	NOBODY void EXPORT DestroyItem(void);
	void EXPORT DefaultTouch(CBaseEntity *pOther);
	void EXPORT FallThink(void);
	void EXPORT Materialize(void);
	NOBODY void EXPORT AttemptToMaterialize(void);

	void FallInit(void);
	void CheckRespawn(void);
public:
	inline int iItemPosition(void)
	{
		return ItemInfoArray[ m_iId ].iPosition;
	}
	inline const char *pszAmmo1(void)
	{
		return ItemInfoArray[ m_iId ].pszAmmo1;
	}
	inline int iMaxAmmo1(void)
	{
		return ItemInfoArray[ m_iId ].iMaxAmmo1;
	}
	inline const char *pszAmmo2(void)
	{
		return ItemInfoArray[ m_iId ].pszAmmo2;
	}
	inline int iMaxAmmo2(void)
	{
		return ItemInfoArray[ m_iId ].iMaxAmmo2;
	}
	inline const char *pszName(void)
	{
		return ItemInfoArray[ m_iId ].pszName;
	}
	inline int iMaxClip(void)
	{
		return ItemInfoArray[ m_iId ].iMaxClip;
	}
	inline int iWeight(void)
	{
		return ItemInfoArray[ m_iId ].iWeight;
	}
	inline int iFlags(void)
	{
		return ItemInfoArray[ m_iId ].iFlags;
	}
public:
#ifndef HOOK_GAMEDLL
	static TYPEDESCRIPTION m_SaveData[3];
#else
	static TYPEDESCRIPTION (*m_SaveData)[3];
#endif // HOOK_GAMEDLL

	static ItemInfo ItemInfoArray[32];
	static AmmoInfo AmmoInfoArray[32];

	CBasePlayer *m_pPlayer;//180
	CBasePlayerItem *m_pNext;
	int m_iId;

};/* size: 192, cachelines: 3, members: 7 */

/* <2c9f52> ../cstrike/dlls/weapons.h:307 */
class CBasePlayerWeapon: public CBasePlayerItem
{
public:
	NOBODY virtual int Save(CSave &save);
	NOBODY virtual int Restore(CRestore &restore);

	virtual int AddToPlayer(CBasePlayer *pPlayer);
	virtual int AddDuplicate(CBasePlayerItem *pItem);
	NOBODY virtual BOOL CanDeploy(void);
	virtual BOOL IsWeapon(void)
	{
		return TRUE;
	}
	NOBODY virtual void Holster(int skiplocal = 0);
	virtual void UpdateItemInfo(void) {};
	NOBODY virtual void ItemPostFrame(void);
	NOBODY virtual int PrimaryAmmoIndex(void);
	NOBODY virtual int SecondaryAmmoIndex(void);
	virtual int UpdateClientData(CBasePlayer *pPlayer);
	virtual CBasePlayerItem *GetWeaponPtr(void)
	{
		return (CBasePlayerItem *)this;
	}
	virtual int ExtractAmmo(CBasePlayerWeapon *pWeapon);
	virtual int ExtractClipAmmo(CBasePlayerWeapon *pWeapon);
	virtual int AddWeapon(void)
	{
		ExtractAmmo(this);
		return 1;
	}
	virtual BOOL PlayEmptySound(void);
	virtual void ResetEmptySound(void);
	virtual void SendWeaponAnim(int iAnim,int skiplocal = 0);
	NOBODY virtual BOOL IsUseable(void);
	virtual void PrimaryAttack(void) {}
	virtual void SecondaryAttack(void) {}
	virtual void Reload(void) {}
	virtual void WeaponIdle(void) {}
	NOBODY virtual void RetireWeapon(void);
	virtual BOOL ShouldWeaponIdle(void)
	{
		return FALSE;
	}
	virtual BOOL UseDecrement(void)
	{
		return FALSE;
	}

#ifdef HOOK_GAMEDLL

	int Save_(CSave &save);
	int Restore_(CRestore &restore);
	int AddToPlayer_(CBasePlayer *pPlayer);
	int AddDuplicate_(CBasePlayerItem *pItem);
	BOOL CanDeploy_(void);
	void Holster_(int skiplocal = 0);
	void ItemPostFrame_(void);
	int PrimaryAmmoIndex_(void);
	int SecondaryAmmoIndex_(void);
	int UpdateClientData_(CBasePlayer *pPlayer);
	int ExtractAmmo_(CBasePlayerWeapon *pWeapon);
	int ExtractClipAmmo_(CBasePlayerWeapon *pWeapon);
	BOOL PlayEmptySound_(void);
	void ResetEmptySound_(void);
	void SendWeaponAnim_(int iAnim,int skiplocal = 0);
	BOOL IsUseable_(void);
	void RetireWeapon_(void);

#endif // HOOK_GAMEDLL

public:
	BOOL AddPrimaryAmmo(int iCount,char *szName,int iMaxClip,int iMaxCarry);
	NOXREF BOOL AddSecondaryAmmo(int iCount,char *szName,int iMaxCarry);
	BOOL DefaultDeploy(char *szViewModel,char *szWeaponModel,int iAnim,char *szAnimExt,int skiplocal = 0);
	int DefaultReload(int iClipSize,int iAnim,float fDelay);
	NOBODY void FireRemaining(int &shotsFired,float &shootTime,BOOL isGlock18);
	NOBODY void KickBack(float up_base,float lateral_base,float up_modifier,float lateral_modifier,float up_max,float lateral_max,int direction_change);
	NOBODY void EjectBrassLate(void);
	NOBODY void MakeBeam(void);
	NOBODY void BeamUpdate(void);
	void ReloadSound(void);
	float GetNextAttackDelay(float delay);
	float GetNextAttackDelay2(float delay);
	NOBODY bool HasSecondaryAttack(void);
	BOOL IsPistol(void)
	{
		return FALSE;
	}
	void SetPlayerShieldAnim(void);
	void ResetPlayerShieldAnim(void);
	bool ShieldSecondaryFire(int iUpAnim,int iDownAnim);

public:
#ifndef HOOK_GAMEDLL
	static TYPEDESCRIPTION m_SaveData[7];
#else
	static TYPEDESCRIPTION (*m_SaveData)[7];
#endif // HOOK_GAMEDLL

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
	float m_flGlock18Shoot;
	int m_iGlock18ShotsFired;
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

};/* size: 336, cachelines: 6, members: 37 */

/* <9716> ../cstrike/dlls/weapons.h:429 */
class CBasePlayerAmmo: public CBaseEntity
{
public:
	virtual void Spawn(void);
	virtual BOOL AddAmmo(CBaseEntity *pOther)
	{
		return TRUE;
	}
	virtual CBaseEntity *Respawn(void);
public:
	void EXPORT DefaultTouch(CBaseEntity *pOther);
	void EXPORT Materialize(void);

#ifdef HOOK_GAMEDLL
public:
	void Spawn_(void);
	//NOBODY BOOL AddAmmo_(CBaseEntity *pOther);
	CBaseEntity *Respawn_(void);
#endif // HOOK_GAMEDLL

};/* size: 152, cachelines: 3, members: 1 */

/* <1d03c1> ../cstrike/dlls/weapons.h:508 */
class CWeaponBox: public CBaseEntity
{
public:
	NOBODY virtual void Spawn(void);
	NOBODY virtual void Precache(void);
	NOBODY virtual void KeyValue(KeyValueData *pkvd);
	NOBODY virtual int Save(CSave &save);
	NOBODY virtual int Restore(CRestore &restore);
	NOBODY virtual void SetObjectCollisionBox(void);
	NOBODY virtual void Touch(CBaseEntity *pOther);

#ifdef HOOK_GAMEDLL

	void Spawn_(void);
	void Precache_(void);
	void KeyValue_(KeyValueData *pkvd);
	int Save_(CSave &save);
	int Restore_(CRestore &restore);
	void SetObjectCollisionBox_(void);
	void Touch_(CBaseEntity *pOther);

#endif // HOOK_GAMEDLL

public:
	BOOL IsEmpty(void);
	int GiveAmmo(int iCount,char *szName,int iMax,int *pIndex = NULL);

	void EXPORT Kill(void);
	void EXPORT BombThink(void);

	BOOL HasWeapon(CBasePlayerItem *pCheckItem);
	BOOL PackWeapon(CBasePlayerItem *pWeapon);
	BOOL PackAmmo(int iszName, int iCount);
public:

#ifndef HOOK_GAMEDLL
	static TYPEDESCRIPTION m_SaveData[4];
#else
	static TYPEDESCRIPTION (*m_SaveData)[4];
#endif // HOOK_GAMEDLL

	CBasePlayerItem *m_rgpPlayerItems[ MAX_ITEM_TYPES ];
	int m_rgiszAmmo[ MAX_AMMO_SLOTS ];
	int m_rgAmmo[ MAX_AMMO_SLOTS ];
	int m_cAmmoTypes;
	bool m_bIsBomb;

};/* size: 440, cachelines: 7, members: 7 */

/* <2ba15a> ../cstrike/dlls/weapons.h:573 */
class CUSP: public CBasePlayerWeapon
{
public:
	virtual void Spawn(void);
	NOBODY virtual void Precache(void);
	virtual int GetItemInfo(ItemInfo *p);
	virtual BOOL Deploy(void);
	virtual float GetMaxSpeed(void)
	{
		return m_fMaxSpeed;
	}
	virtual int iItemSlot(void)
	{
		return PISTOL_SLOT;
	}
	NOBODY virtual void PrimaryAttack(void);
	NOBODY virtual void SecondaryAttack(void);
	virtual void Reload(void);
	virtual void WeaponIdle(void);
	virtual BOOL UseDecrement(void)
	{
		return TRUE;
	}
	virtual BOOL IsPistol(void)
	{
		return TRUE;
	}
public:
	//TOOD: this func changed access to private?!
	UNTESTED void USPFire(float flSpread,float flCycleTime,BOOL fUseSemi);
	NOXREF void MakeBeam(void);
	NOXREF void BeamUpdate(void);
public:
	int m_iShell;
private:
	unsigned short m_usFireUSP;

#ifdef HOOK_GAMEDLL
public:
	void Spawn_(void);
	void Precache_(void);
	int GetItemInfo_(ItemInfo *p);
	BOOL Deploy_(void);
	float GetMaxSpeed_(void)
	{
		return m_fMaxSpeed;
	}
	int iItemSlot_(void)
	{
		return PISTOL_SLOT;
	}
	NOBODY void PrimaryAttack_(void);
	NOBODY void SecondaryAttack_(void);
	void Reload_(void);
	void WeaponIdle_(void);
	BOOL UseDecrement_(void)
	{
		return TRUE;
	}
	BOOL IsPistol_(void)
	{
		return TRUE;
	}
#endif // HOOK_GAMEDLL

};/* size: 344, cachelines: 6, members: 3 */

/* <28adc9> ../cstrike/dlls/weapons.h:599 */
class CMP5N: public CBasePlayerWeapon
{
public:
	NOBODY virtual void Spawn(void);
	NOBODY virtual void Precache(void);
	NOBODY virtual int GetItemInfo(ItemInfo *p);
	NOBODY virtual BOOL Deploy(void);
	NOBODY virtual float GetMaxSpeed(void)
	{
		return 250.0f;
	}
	int iItemSlot(void)
	{
		return PRIMARY_WEAPON_SLOT;
	}
	NOBODY virtual void PrimaryAttack(void);
	NOBODY virtual void Reload(void);
	NOBODY virtual void WeaponIdle(void);
	NOBODY BOOL UseDecrement(void)
	{
		return TRUE;
	}
public:
	NOBODY void MP5NFire(float flSpread,float flCycleTime,BOOL fUseAutoAim);
public:
	int m_iShell;
	int iShellOn;
private:
	unsigned short m_usFireMP5N;
};/* size: 348, cachelines: 6, members: 4 */

/* <2a553c> ../cstrike/dlls/weapons.h:624 */
class CSG552: public CBasePlayerWeapon
{
public:
	NOBODY virtual void Spawn(void);
	NOBODY virtual void Precache(void);
	NOBODY virtual int GetItemInfo(ItemInfo *p);
	NOBODY virtual BOOL Deploy(void);
	NOBODY virtual float GetMaxSpeed(void);
	virtual int iItemSlot(void)
	{
		return PRIMARY_WEAPON_SLOT;
	}
	NOBODY virtual void PrimaryAttack(void);
	NOBODY virtual void SecondaryAttack(void);
	NOBODY virtual void Reload(void);
	NOBODY virtual void WeaponIdle(void);
	BOOL virtual UseDecrement(void)
	{
		return TRUE;
	}
public:
	NOBODY void SG552Fire(float flSpread,float flCycleTime,BOOL fUseAutoAim);
public:
	int m_iShell;
	int iShellOn;
private:
	unsigned short m_usFireSG552;
};/* size: 348, cachelines: 6, members: 4 */

/* <234730> ../cstrike/dlls/weapons.h:648 */
class CAK47: public CBasePlayerWeapon
{
public:
	NOBODY virtual void Spawn(void);
	NOBODY virtual void Precache(void);
	NOBODY virtual int GetItemInfo(ItemInfo *p);
	NOBODY virtual BOOL Deploy(void);
	virtual float GetMaxSpeed(void)
	{
		return 221.0f;
	}
	virtual int iItemSlot(void)
	{
		return PRIMARY_WEAPON_SLOT;
	}
	NOBODY virtual void PrimaryAttack(void);
	NOBODY virtual void SecondaryAttack(void);
	NOBODY virtual void Reload(void);
	NOBODY virtual void WeaponIdle(void);
	virtual BOOL UseDecrement(void)
	{
		return TRUE;
	}
public:
	NOBODY void AK47Fire(float flSpread,float flCycleTime,BOOL fUseAutoAim);

public:
	int m_iShell;
	int iShellOn;
private:
	unsigned short m_usFireAK47;
};/* size: 348, cachelines: 6, members: 4 */

/* <239b82> ../cstrike/dlls/weapons.h:672 */
class CAUG: public CBasePlayerWeapon
{
public:
	NOBODY virtual void Spawn(void);
	NOBODY virtual void Precache(void);
	NOBODY virtual int GetItemInfo(ItemInfo *p);
	NOBODY virtual BOOL Deploy(void);
	virtual float GetMaxSpeed(void)
	{
		return 240.0f;
	}
	virtual int iItemSlot(void)
	{
		return PRIMARY_WEAPON_SLOT;
	}
	NOBODY virtual void PrimaryAttack(void);
	NOBODY virtual void SecondaryAttack(void);
	NOBODY virtual void Reload(void);
	NOBODY virtual void WeaponIdle(void);
	virtual BOOL UseDecrement(void)
	{
		return TRUE;
	}
public:
	void AUGFire(float flSpread,float flCycleTime,BOOL fUseAutoAim);
public:
	int m_iShell;
	int iShellOn;
private:
	unsigned short m_usFireAug;
};/* size: 348, cachelines: 6, members: 4 */

/* <23ef02> ../cstrike/dlls/weapons.h:697 */
class CAWP: public CBasePlayerWeapon
{
public:
	NOBODY virtual void Spawn(void);
	NOBODY virtual void Precache(void);
	NOBODY virtual int GetItemInfo(ItemInfo *p);
	NOBODY virtual BOOL Deploy(void);
	NOBODY virtual float GetMaxSpeed(void);
	virtual int iItemSlot(void)
	{
		return PRIMARY_WEAPON_SLOT;
	}
	NOBODY virtual void PrimaryAttack(void);
	NOBODY virtual void SecondaryAttack(void);
	NOBODY virtual void Reload(void);
	NOBODY virtual void WeaponIdle(void);
	virtual BOOL UseDecrement(void)
	{
		return TRUE;
	}
public:
	NOBODY void AWPFire(float flSpread,float flCycleTime,BOOL fUseAutoAim);
public:
	int m_iShell;
private:
	unsigned short m_usFireAWP;
};/* size: 344, cachelines: 6, members: 3 */

/* <245949> ../cstrike/dlls/weapons.h:721 */
class CC4: public CBasePlayerWeapon
{
public:
	NOBODY virtual void Spawn(void);
	NOBODY virtual void Precache(void);
	NOBODY virtual void KeyValue(KeyValueData *pkvd);
	NOBODY virtual void Use(CBaseEntity *pActivator,CBaseEntity *pCaller,USE_TYPE useType,float value);
	NOBODY virtual int GetItemInfo(ItemInfo *p);
	NOBODY virtual BOOL Deploy(void);
	NOBODY virtual void Holster(int skiplocal);
	virtual float GetMaxSpeed(void)
	{
		return 250.0f;
	}
	virtual int iItemSlot(void)
	{
		return C4_SLOT;
	}
	NOBODY virtual void PrimaryAttack(void);
	NOBODY virtual void WeaponIdle(void);
	virtual BOOL UseDecrement(void)
	{
		return TRUE;
	}
public:
	bool m_bStartedArming;
	bool m_bBombPlacedAnimation;
	float m_fArmedTime;
private:
	bool m_bHasShield;
};/* size: 348, cachelines: 6, members: 5 */

/* <24afee> ../cstrike/dlls/weapons.h:750 */
class CDEAGLE: public CBasePlayerWeapon
{
public:
	NOBODY virtual void Spawn(void);
	NOBODY virtual void Precache(void);
	NOBODY virtual int GetItemInfo(ItemInfo *p);
	NOBODY virtual BOOL Deploy(void);
	virtual float GetMaxSpeed(void)
	{
		return m_fMaxSpeed;
	}
	virtual int iItemSlot(void)
	{
		return PISTOL_SLOT;
	}
	NOBODY virtual void PrimaryAttack(void);
	NOBODY virtual void SecondaryAttack(void);
	NOBODY virtual void Reload(void);
	NOBODY virtual void WeaponIdle(void);
	virtual BOOL UseDecrement(void)
	{
		return TRUE;
	}
	virtual BOOL IsPistol(void)
	{
		return TRUE;
	}
public:
	NOBODY void DEAGLEFire(float flSpread, float flCycleTime, BOOL fUseSemi);
public:
	int m_iShell;
private:
	unsigned short m_usFireDeagle;
};/* size: 344, cachelines: 6, members: 3 */

/* <25ab17> ../cstrike/dlls/weapons.h:778 */
class CFlashbang: public CBasePlayerWeapon
{
public:
	NOBODY virtual void Spawn(void);
	NOBODY virtual void Precache(void);
	NOBODY virtual int GetItemInfo(ItemInfo *p);
	NOBODY virtual BOOL CanDeploy(void);
	virtual BOOL CanDrop(void)
	{
		return FALSE;
	}
	NOBODY virtual BOOL Deploy(void);
	NOBODY virtual void Holster(int skiplocal);
	virtual float GetMaxSpeed(void)
	{
		return m_fMaxSpeed;
	}
	virtual int iItemSlot(void)
	{
		return GRENADE_SLOT;
	}
	NOBODY virtual void PrimaryAttack(void);
	NOBODY virtual void SecondaryAttack(void);
	NOBODY virtual void WeaponIdle(void);
	virtual BOOL UseDecrement(void)
	{
		return TRUE;
	}
	virtual BOOL IsPistol(void)
	{
		return TRUE;
	}
public:
	NOBODY bool ShieldSecondaryFire(int iUpAnim,int iDownAnim);
	NOBODY void SetPlayerShieldAnim(void);
	NOBODY void ResetPlayerShieldAnim(void);
};/* size: 336, cachelines: 6, members: 1 */

/* <26006d> ../cstrike/dlls/weapons.h:803 */
class CG3SG1: public CBasePlayerWeapon
{
public:
	NOBODY virtual void Spawn(void);
	NOBODY virtual void Precache(void);
	NOBODY virtual int GetItemInfo(ItemInfo *p);
	NOBODY virtual BOOL Deploy(void);
	NOBODY virtual float GetMaxSpeed(void);
	virtual int iItemSlot(void)
	{
		return PRIMARY_WEAPON_SLOT;
	}
	NOBODY virtual void PrimaryAttack(void);
	NOBODY virtual void SecondaryAttack(void);
	NOBODY virtual void Reload(void);
	NOBODY virtual void WeaponIdle(void);
	virtual BOOL UseDecrement(void)
	{
		return TRUE;
	}
public:
	NOBODY void G3SG1Fire(float flSpread,float flCycleTime,BOOL fUseAutoAim);
public:
	int m_iShell;
private:
	unsigned short m_usFireG3SG1;
};/* size: 344, cachelines: 6, members: 3 */

/* <2655b2> ../cstrike/dlls/weapons.h:828 */
class CGLOCK18: public CBasePlayerWeapon
{
public:
	NOBODY virtual void Spawn(void);
	NOBODY virtual void Precache(void);
	NOBODY virtual int GetItemInfo(ItemInfo *p);
	NOBODY virtual BOOL Deploy(void);
	virtual float GetMaxSpeed(void)
	{
		return m_fMaxSpeed;
	}
	virtual int iItemSlot(void)
	{
		return PISTOL_SLOT;
	}
	NOBODY virtual void PrimaryAttack(void);
	NOBODY virtual void SecondaryAttack(void);
	NOBODY virtual void Reload(void);
	NOBODY virtual void WeaponIdle(void);
	virtual BOOL UseDecrement(void)
	{
		return TRUE;
	}
	virtual BOOL IsPistol(void)
	{
		return TRUE;
	}
public:
	NOBODY void GLOCK18Fire(float flSpread, float flCycleTime, BOOL bFireBurst);
public:
	int m_iShell;
	bool m_bBurstFire;
};/* size: 344, cachelines: 6, members: 3 */

/* <26a48a> ../cstrike/dlls/weapons.h:852 */
class CHEGrenade: public CBasePlayerWeapon
{
public:
	NOBODY virtual void Spawn(void);
	NOBODY virtual void Precache(void);
	NOBODY virtual int GetItemInfo(ItemInfo *p);
	NOBODY virtual BOOL CanDeploy(void);
	virtual BOOL CanDrop(void)
	{
		return FALSE;
	}
	NOBODY virtual BOOL Deploy(void);
	NOBODY virtual void Holster(int skiplocal);
	virtual float GetMaxSpeed(void)
	{
		return m_fMaxSpeed;
	}
	virtual int iItemSlot(void)
	{
		return GRENADE_SLOT;
	}
	NOBODY virtual void PrimaryAttack(void);
	NOBODY virtual void SecondaryAttack(void);
	NOBODY virtual void WeaponIdle(void);
	virtual BOOL UseDecrement(void)
	{
		return TRUE;
	}
public:
	NOBODY bool ShieldSecondaryFire(int iUpAnim,int iDownAnim);
	NOBODY void SetPlayerShieldAnim(void);
	NOBODY void ResetPlayerShieldAnim(void);

public:
	unsigned short m_usCreateExplosion;
};/* size: 340, cachelines: 6, members: 2 */

/* <26f804> ../cstrike/dlls/weapons.h:878 */
class CKnife: public CBasePlayerWeapon
{
public:
	NOBODY virtual void Spawn(void);
	NOBODY virtual void Precache(void);
	NOBODY virtual int GetItemInfo(ItemInfo *p);
	virtual BOOL CanDrop(void)
	{
		return FALSE;
	}
	NOBODY virtual BOOL Deploy(void);
	NOBODY virtual void Holster(int skiplocal);
	virtual float GetMaxSpeed(void)
	{
		return m_fMaxSpeed;
	}
	virtual int iItemSlot(void)
	{
		return KNIFE_SLOT;
	}
	NOBODY virtual void PrimaryAttack(void);
	NOBODY virtual void SecondaryAttack(void);
	virtual BOOL UseDecrement(void)
	{
		return TRUE;
	}
	NOBODY virtual void WeaponIdle(void);
public:
	NOBODY void EXPORT SwingAgain(void);
	NOBODY void EXPORT Smack(void);
public:
	NOBODY void WeaponAnimation(int iAnimation);
	NOBODY int Stab(int fFirst);
	NOBODY int Swing(int fFirst);
public:
	NOBODY virtual bool ShieldSecondaryFire(int iUpAnim,int iDownAnim);
	NOBODY virtual void SetPlayerShieldAnim(void);
	NOBODY virtual void ResetPlayerShieldAnim(void);
public:
	TraceResult m_trHit;
	unsigned short m_usKnife;
};/* size: 396, cachelines: 7, members: 3 */

/* <275d5a> ../cstrike/dlls/weapons.h:910 */
class CM249: public CBasePlayerWeapon
{
public:
	NOBODY virtual void Spawn(void);
	NOBODY virtual void Precache(void);
	NOBODY virtual int GetItemInfo(ItemInfo *p);
	NOBODY virtual BOOL Deploy(void);
	virtual float GetMaxSpeed(void)
	{
		return 220.0f;
	}
	virtual int iItemSlot(void)
	{
		return PRIMARY_WEAPON_SLOT;
	}
	NOBODY virtual void PrimaryAttack(void);
	NOBODY virtual void Reload(void);
	NOBODY virtual void WeaponIdle(void);
	BOOL UseDecrement(void)
	{
		return TRUE;
	}
public:
	NOBODY void M249Fire(float flSpread,float flCycleTime,BOOL fUseAutoAim);
public:
	int m_iShell;
	int iShellOn;
private:
	unsigned short m_usFireM249;
};/* size: 348, cachelines: 6, members: 4 */

/* <27b175> ../cstrike/dlls/weapons.h:934 */
class CM3: public CBasePlayerWeapon
{
public:
	NOBODY virtual void Spawn(void);
	NOBODY virtual void Precache(void);
	NOBODY virtual int GetItemInfo(ItemInfo *p);
	NOBODY virtual BOOL Deploy(void);
	virtual float GetMaxSpeed(void)
	{
		return 230.0f;
	}
	virtual int iItemSlot(void)
	{
		return PRIMARY_WEAPON_SLOT;
	}
	NOBODY virtual void PrimaryAttack(void);
	NOBODY virtual void Reload(void);
	NOBODY virtual void WeaponIdle(void);
	virtual BOOL UseDecrement(void)
	{
		return TRUE;
	}
public:
	int m_iShell;
	float m_flPumpTime;
private:
	unsigned short m_usFireM3;
};/* size: 348, cachelines: 6, members: 4 */

/* <280488> ../cstrike/dlls/weapons.h:961 */
class CM4A1: public CBasePlayerWeapon
{
public:
	NOBODY virtual void Spawn(void);
	NOBODY virtual void Precache(void);
	NOBODY virtual int GetItemInfo(ItemInfo *p);
	NOBODY virtual BOOL Deploy(void);
	virtual float GetMaxSpeed(void);
	virtual int iItemSlot(void)
	{
		return PRIMARY_WEAPON_SLOT;
	}
	NOBODY virtual void PrimaryAttack(void);
	NOBODY virtual void SecondaryAttack(void);
	NOBODY virtual void Reload(void);
	NOBODY virtual void WeaponIdle(void);
	virtual BOOL UseDecrement(void)
	{
		return TRUE;
	}
public:
	NOBODY void M4A1Fire(float flSpread,float flCycleTime,BOOL fUseAutoAim);
public:
	int m_iShell;
	int iShellOn;
private:
	unsigned short m_usFireM4A1;
};/* size: 348, cachelines: 6, members: 4 */

/* <285993> ../cstrike/dlls/weapons.h:987 */
class CMAC10: public CBasePlayerWeapon
{
public:
	NOBODY virtual void Spawn(void);
	NOBODY virtual void Precache(void);
	NOBODY virtual int GetItemInfo(ItemInfo *p);
	NOBODY virtual BOOL Deploy(void);
	virtual float GetMaxSpeed(void)
	{
		return 250.0f;
	}
	virtual int iItemSlot(void)
	{
		return PRIMARY_WEAPON_SLOT;
	}
	NOBODY virtual void PrimaryAttack(void);
	NOBODY virtual void Reload(void);
	NOBODY virtual void WeaponIdle(void);
	virtual BOOL UseDecrement(void)
	{
		return TRUE;
	}
public:
	NOBODY void MAC10Fire(float flSpread,float flCycleTime,BOOL fUseAutoAim);
public:
	int m_iShell;
	int iShellOn;
private:
	unsigned short m_usFireMAC10;
};/* size: 348, cachelines: 6, members: 4 */

/* <2902c1> ../cstrike/dlls/weapons.h:1011 */
class CP228: public CBasePlayerWeapon
{
public:
	NOBODY virtual void Spawn(void);
	NOBODY virtual void Precache(void);
	NOBODY virtual int GetItemInfo(ItemInfo *p);
	NOBODY virtual BOOL Deploy(void);
	virtual float GetMaxSpeed(void)
	{
		return m_fMaxSpeed;
	}
	virtual int iItemSlot(void)
	{
		return PISTOL_SLOT;
	}
	NOBODY virtual void PrimaryAttack(void);
	NOBODY virtual void SecondaryAttack(void);
	NOBODY virtual void Reload(void);
	NOBODY virtual void WeaponIdle(void);
	virtual BOOL UseDecrement(void)
	{
		return TRUE;
	}
	virtual BOOL IsPistol(void)
	{
		return TRUE;
	}
public:
	NOBODY void P228Fire(float flSpread,float flCycleTime,BOOL fUseSemi);
public:
	int m_iShell;
private:
	unsigned short m_usFireP228;
};/* size: 344, cachelines: 6, members: 3 */

/* <295740> ../cstrike/dlls/weapons.h:1039 */
class CP90: public CBasePlayerWeapon
{
public:
	NOBODY virtual void Spawn(void);
	NOBODY virtual void Precache(void);
	NOBODY virtual int GetItemInfo(ItemInfo *p);
	NOBODY virtual BOOL Deploy(void);
	virtual float GetMaxSpeed(void)
	{
		return 245.0f;
	}
	virtual int iItemSlot(void)
	{
		return PRIMARY_WEAPON_SLOT;
	}
	NOBODY virtual void PrimaryAttack(void);
	NOBODY virtual void Reload(void);
	NOBODY virtual void WeaponIdle(void);
	virtual BOOL UseDecrement(void)
	{
		return TRUE;
	}
public:
	NOBODY void P90Fire(float flSpread,float flCycleTime,BOOL fUseAutoAim);
public:
	int m_iShell;
	int iShellOn;
private:
	unsigned short m_usFireP90;
};/* size: 348, cachelines: 6, members: 4 */

/* <29abe0> ../cstrike/dlls/weapons.h:1063 */
class CSCOUT: public CBasePlayerWeapon
{
public:
	NOBODY virtual void Spawn(void);
	NOBODY virtual void Precache(void);
	NOBODY virtual int GetItemInfo(ItemInfo *p);
	NOBODY virtual BOOL Deploy(void);
	NOBODY virtual float GetMaxSpeed(void);
	virtual int iItemSlot(void)
	{
		return PRIMARY_WEAPON_SLOT;
	}
	NOBODY virtual void PrimaryAttack(void);
	NOBODY virtual void SecondaryAttack(void);
	NOBODY virtual void Reload(void);
	NOBODY virtual void WeaponIdle(void);
	virtual BOOL UseDecrement(void)
	{
		return TRUE;
	}
public:
	NOBODY void SCOUTFire(float flSpread,float flCycleTime,BOOL fUseAutoAim);
public:
	int m_iShell;
private:
	unsigned short m_usFireScout;
};/* size: 344, cachelines: 6, members: 3 */

/* <2aa3d5> ../cstrike/dlls/weapons.h:1089 */
class CSmokeGrenade: public CBasePlayerWeapon
{
public:
	NOBODY virtual void Spawn(void);
	NOBODY virtual void Precache(void);
	NOBODY virtual int GetItemInfo(ItemInfo *p);
	NOBODY virtual BOOL CanDeploy(void);
	virtual BOOL CanDrop(void)
	{
		return FALSE;
	}
	NOBODY virtual BOOL Deploy(void);
	NOBODY virtual void Holster(int skiplocal);
	virtual float GetMaxSpeed(void)
	{
		return m_fMaxSpeed;
	}
	virtual int iItemSlot(void)
	{
		return GRENADE_SLOT;
	}
	NOBODY virtual void PrimaryAttack(void);
	NOBODY virtual void SecondaryAttack(void);
	NOBODY virtual void WeaponIdle(void);
	virtual BOOL UseDecrement(void)
	{
		return TRUE;
	}
public:
	NOBODY bool ShieldSecondaryFire(int iUpAnim,int iDownAnim);
	NOBODY void SetPlayerShieldAnim(void);
	NOBODY void ResetPlayerShieldAnim(void);
public:
	unsigned short m_usCreateSmoke;
};/* size: 340, cachelines: 6, members: 2 */

/* <2af8c3> ../cstrike/dlls/weapons.h:1116 */
class CTMP: public CBasePlayerWeapon
{
public:
	NOBODY virtual void Spawn(void);
	NOBODY virtual void Precache(void);
	NOBODY virtual int GetItemInfo(ItemInfo *p);
	NOBODY virtual BOOL Deploy(void);
	virtual float GetMaxSpeed(void)
	{
		return 250.0f;
	}
	virtual int iItemSlot(void)
	{
		return PRIMARY_WEAPON_SLOT;
	}
	NOBODY virtual void PrimaryAttack(void);
	NOBODY virtual void Reload(void);
	NOBODY virtual void WeaponIdle(void);
	virtual BOOL UseDecrement(void)
	{
		return TRUE;
	}
public:
	NOBODY void TMPFire(float flSpread,float flCycleTime,BOOL fUseAutoAim);
public:
	int m_iShell;
	int iShellOn;
private:
	unsigned short m_usFireTMP;
};/* size: 348, cachelines: 6, members: 4 */

/* <2c9fce> ../cstrike/dlls/weapons.h:1141 */
class CXM1014: public CBasePlayerWeapon
{
public:
	NOBODY virtual void Spawn(void);
	NOBODY virtual void Precache(void);
	NOBODY virtual int GetItemInfo(ItemInfo *p);
	NOBODY virtual BOOL Deploy(void);
	virtual float GetMaxSpeed(void)
	{
		return 240.0f;
	}
	virtual int iItemSlot(void)
	{
		return PRIMARY_WEAPON_SLOT;
	}
	NOBODY virtual void PrimaryAttack(void);
	NOBODY virtual void Reload(void);
	NOBODY virtual void WeaponIdle(void);
	virtual BOOL UseDecrement(void)
	{
		return TRUE;
	}
public:
	int m_iShell;
	float m_flPumpTime;
private:
	unsigned short m_usFireXM1014;
};/* size: 348, cachelines: 6, members: 4 */

/* <2503f9> ../cstrike/dlls/weapons.h:1167 */
class CELITE: public CBasePlayerWeapon
{
public:
	NOBODY virtual void Spawn(void);
	NOBODY virtual void Precache(void);
	NOBODY virtual int GetItemInfo(ItemInfo *p);
	NOBODY virtual BOOL Deploy(void);
	virtual float GetMaxSpeed(void)
	{
		return 250.0f;
	}
	virtual int iItemSlot(void)
	{
		return PISTOL_SLOT;
	}
	NOBODY virtual void PrimaryAttack(void);
	NOBODY virtual void Reload(void);
	NOBODY virtual void WeaponIdle(void);
	virtual BOOL UseDecrement(void)
	{
		return TRUE;
	}
	virtual BOOL IsPistol(void)
	{
		return TRUE;
	}
public:
	NOBODY void ELITEFire(float flSpread,float flCycleTime,BOOL fUseSemi);
public:
	int m_iShell;
	unsigned short m_usFireELITE_LEFT;
	unsigned short m_usFireELITE_RIGHT;
};/* size: 344, cachelines: 6, members: 4 */

/* <255b29> ../cstrike/dlls/weapons.h:1192 */
class CFiveSeven: public CBasePlayerWeapon
{
public:
	NOBODY virtual void Spawn(void);
	NOBODY virtual void Precache(void);
	NOBODY virtual int GetItemInfo(ItemInfo *p);
	NOBODY virtual BOOL Deploy(void);
	virtual float GetMaxSpeed(void)
	{
		return m_fMaxSpeed;
	}
	virtual int iItemSlot(void)
	{
		return PISTOL_SLOT;
	}
	NOBODY virtual void PrimaryAttack(void);
	NOBODY virtual void SecondaryAttack(void);
	NOBODY virtual void Reload(void);
	NOBODY virtual void WeaponIdle(void);
	virtual BOOL UseDecrement(void)
	{
		return TRUE;
	}
	virtual BOOL IsPistol(void)
	{
		return TRUE;
	}
public:
	NOBODY void FiveSevenFire(float flSpread,float flCycleTime,BOOL fUseSemi);
	NOXREF void MakeBeam(void);
	NOXREF void BeamUpdate(void);
public:
	int m_iShell;
private:
	unsigned short m_usFireFiveSeven;
};/* size: 344, cachelines: 6, members: 3 */

/* <2b4cf9> ../cstrike/dlls/weapons.h:1219 */
class CUMP45: public CBasePlayerWeapon
{
public:
	NOBODY virtual void Spawn(void);
	NOBODY virtual void Precache(void);
	NOBODY virtual int GetItemInfo(ItemInfo *p);
	NOBODY virtual BOOL Deploy(void);
	virtual float GetMaxSpeed(void)
	{
		return 250.0f;
	}
	virtual int iItemSlot(void)
	{
		return PRIMARY_WEAPON_SLOT;
	}
	NOBODY virtual void PrimaryAttack(void);
	NOBODY virtual void Reload(void);
	NOBODY virtual void WeaponIdle(void);
	virtual BOOL UseDecrement(void)
	{
		return TRUE;
	}
public:
	NOBODY void UMP45Fire(float flSpread,float flCycleTime,BOOL fUseAutoAim);
public:
	int m_iShell;
	int iShellOn;
private:
	unsigned short m_usFireUMP45;
};/* size: 348, cachelines: 6, members: 4 */

/* <2a00b3> ../cstrike/dlls/weapons.h:1244 */
class CSG550: public CBasePlayerWeapon
{
public:
	NOBODY virtual void Spawn(void);
	NOBODY virtual void Precache(void);
	NOBODY virtual int GetItemInfo(ItemInfo *p);
	NOBODY virtual BOOL Deploy(void);
	NOBODY virtual float GetMaxSpeed(void);
	virtual int iItemSlot(void)
	{
		return PRIMARY_WEAPON_SLOT;
	}
	NOBODY virtual void PrimaryAttack(void);
	NOBODY virtual void SecondaryAttack(void);
	NOBODY virtual void Reload(void);
	NOBODY virtual void WeaponIdle(void);
	virtual BOOL UseDecrement(void)
	{
		return TRUE;
	}
public:
	NOBODY void SG550Fire(float flSpread,float flCycleTime,BOOL fUseAutoAim);
public:
	int m_iShell;
private:
	unsigned short m_usFireSG550;
};/* size: 344, cachelines: 6, members: 3 */

/* <2c4bb9> ../cstrike/dlls/weapons.h:1269 */
class CGalil: public CBasePlayerWeapon
{
public:
	NOBODY virtual void Spawn(void);
	NOBODY virtual void Precache(void);
	NOBODY virtual int GetItemInfo(ItemInfo *p);
	NOBODY virtual BOOL Deploy(void);
	virtual float GetMaxSpeed(void)
	{
		return 240.0f;
	}
	virtual int iItemSlot(void)
	{
		return PRIMARY_WEAPON_SLOT;
	}
	NOBODY virtual void PrimaryAttack(void);
	NOBODY virtual void SecondaryAttack(void);
	NOBODY virtual void Reload(void);
	NOBODY virtual void WeaponIdle(void);
	virtual BOOL UseDecrement(void)
	{
		return TRUE;
	}
public:
	NOBODY void GalilFire(float flSpread,float flCycleTime,BOOL fUseAutoAim);
public:
	int m_iShell;
	int iShellOn;
private:
	unsigned short m_usFireGalil;
};/* size: 348, cachelines: 6, members: 4 */

/* <2bf676> ../cstrike/dlls/weapons.h:1293 */
class CFamas: public CBasePlayerWeapon
{
public:
	NOBODY virtual void Spawn(void);
	NOBODY virtual void Precache(void);
	NOBODY virtual int GetItemInfo(ItemInfo *p);
	NOBODY virtual BOOL Deploy(void);
	virtual float GetMaxSpeed(void)
	{
		return 240.0f;
	}
	virtual int iItemSlot(void)
	{
		return PRIMARY_WEAPON_SLOT;
	}
	NOBODY virtual void PrimaryAttack(void);
	NOBODY virtual void SecondaryAttack(void);
	NOBODY virtual void Reload(void);
	NOBODY virtual void WeaponIdle(void);
	virtual BOOL UseDecrement(void)
	{
		return TRUE;
	}
public:
	NOBODY void FamasFire(float flSpread,float flCycleTime,BOOL fUseAutoAim,BOOL bFireBurst);
public:
	int m_iShell;
	int iShellOn;
};/* size: 344, cachelines: 6, members: 3 */

#ifdef HOOK_GAMEDLL

#define g_sModelIndexLaser (*pg_sModelIndexLaser)
#define g_pModelNameLaser (*pg_pModelNameLaser)
#define g_sModelIndexLaserDot (*pg_sModelIndexLaserDot)

#define g_sModelIndexFireball (*pg_sModelIndexFireball)
#define g_sModelIndexSmoke (*pg_sModelIndexSmoke)
#define g_sModelIndexWExplosion (*pg_sModelIndexWExplosion)
#define g_sModelIndexBubbles (*pg_sModelIndexBubbles)
#define g_sModelIndexBloodDrop (*pg_sModelIndexBloodDrop)
#define g_sModelIndexBloodSpray (*pg_sModelIndexBloodSpray)
#define g_sModelIndexSmokePuff (*pg_sModelIndexSmokePuff)
#define g_sModelIndexFireball2 (*pg_sModelIndexFireball2)
#define g_sModelIndexFireball3 (*pg_sModelIndexFireball3)
#define g_sModelIndexFireball4 (*pg_sModelIndexFireball4)
#define g_sModelIndexCTGhost (*pg_sModelIndexCTGhost)
#define g_sModelIndexTGhost (*pg_sModelIndexTGhost)
#define g_sModelIndexC4Glow (*pg_sModelIndexC4Glow)
#define giAmmoIndex (*pgiAmmoIndex)
#define g_sModelIndexRadio (*pg_sModelIndexRadio)
#define gMultiDamage (*pgMultiDamage)

#endif // HOOK_GAMEDLL

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

extern int giAmmoIndex;
extern short g_sModelIndexRadio;
extern MULTIDAMAGE gMultiDamage;

//extern "C" _DLLEXPORT void weapon_usp(entvars_t *pev);
//_DLLEXPORT void weapon_usp(entvars_t *pev);

//extern "C" _DLLEXPORT void func_weaponcheck(entvars_t *pev);
//extern "C" _DLLEXPORT void func_grencatch(entvars_t *pev);

//extern "C" _DLLEXPORT void weaponbox(entvars_t *pev);
//extern "C" _DLLEXPORT void armoury_entity(entvars_t *pev);

//extern "C" _DLLEXPORT void weapon_usp(entvars_t *pev);
//extern "C" _DLLEXPORT void weapon_mp5navy(entvars_t *pev);
//extern "C" _DLLEXPORT void weapon_sg552(entvars_t *pev);
//extern "C" _DLLEXPORT void weapon_ak47(entvars_t *pev);
//extern "C" _DLLEXPORT void weapon_aug(entvars_t *pev);
//extern "C" _DLLEXPORT void weapon_awp(entvars_t *pev);
//extern "C" _DLLEXPORT void weapon_c4(entvars_t *pev);
//extern "C" _DLLEXPORT void weapon_deagle(entvars_t *pev);
//extern "C" _DLLEXPORT void weapon_flashbang(entvars_t *pev);
//extern "C" _DLLEXPORT void weapon_g3sg1(entvars_t *pev);
//extern "C" _DLLEXPORT void weapon_glock18(entvars_t *pev);
//extern "C" _DLLEXPORT void weapon_hegrenade(entvars_t *pev);
//extern "C" _DLLEXPORT void weapon_knife(entvars_t *pev);
//extern "C" _DLLEXPORT void weapon_m249(entvars_t *pev);
//extern "C" _DLLEXPORT void weapon_m3(entvars_t *pev);
//extern "C" _DLLEXPORT void weapon_m4a1(entvars_t *pev);
//extern "C" _DLLEXPORT void weapon_mac10(entvars_t *pev);
//extern "C" _DLLEXPORT void weapon_p228(entvars_t *pev);
//extern "C" _DLLEXPORT void weapon_p90(entvars_t *pev);
//extern "C" _DLLEXPORT void weapon_scout(entvars_t *pev);
//extern "C" _DLLEXPORT void weapon_smokegrenade(entvars_t *pev);
//extern "C" _DLLEXPORT void weapon_tmp(entvars_t *pev);
//extern "C" _DLLEXPORT void weapon_elite(entvars_t *pev);
//extern "C" _DLLEXPORT void weapon_xm1014(entvars_t *pev);
//extern "C" _DLLEXPORT void weapon_fiveseven(entvars_t *pev);
//extern "C" _DLLEXPORT void weapon_ump45(entvars_t *pev);
//extern "C" _DLLEXPORT void weapon_sg550(entvars_t *pev);
//extern "C" _DLLEXPORT void weapon_galil(entvars_t *pev);
//extern "C" _DLLEXPORT void weapon_famas(entvars_t *pev);
//extern "C" _DLLEXPORT void grenade(entvars_t *pev);

NOBODY void FindHullIntersection(Vector &vecSrc, TraceResult &tr, float *mins, float *maxs, edict_t *pEntity);

int MaxAmmoCarry(int iszName);
void ClearMultiDamage(void);
void ApplyMultiDamage(entvars_t *pevInflictor, entvars_t *pevAttacker);
void AddMultiDamage(entvars_t *pevInflictor, CBaseEntity *pEntity, float flDamage, int bitsDamageType);
void SpawnBlood(Vector vecSpot, int bloodColor, float flDamage);
NOXREF int DamageDecal(CBaseEntity *pEntity, int bitsDamageType);
NOXREF void DecalGunshot(TraceResult *pTrace, int iBulletType, bool ClientOnly, entvars_t *pShooter, bool bHitMetal);
NOBODY void EjectBrass(Vector &vecOrigin, Vector &vecLeft, Vector &vecVelocity, float rotation, int model, int soundtype, int entityIndex);
NOBODY void EjectBrass2(Vector &vecOrigin, Vector &vecVelocity, float rotation, int model, int soundtype, entvars_t *pev);
NOXREF void AddAmmoNameToAmmoRegistry(const char *szAmmoname);
void UTIL_PrecacheOtherWeapon(const char *szClassname);
NOXREF void UTIL_PrecacheOtherWeapon2(const char *szClassname);
void W_Precache(void);
NOXREF BOOL CanAttack(float attack_time, float curtime, BOOL isPredicted);

#endif // WEAPONS_H

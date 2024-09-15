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

class CBasePlayer;

const float MAX_NORMAL_BATTERY    = 100.0f;
const float MAX_DIST_RELOAD_SOUND = 512.0f;

#define MAX_WEAPONS                 32

#define ITEM_FLAG_SELECTONEMPTY     		BIT(0)
#define ITEM_FLAG_NOAUTORELOAD      		BIT(1)
#define ITEM_FLAG_NOAUTOSWITCHEMPTY 		BIT(2)
#define ITEM_FLAG_LIMITINWORLD      		BIT(3)
#define ITEM_FLAG_EXHAUSTIBLE       		BIT(4) // A player can totally exhaust their ammo supply and lose this weapon
#define ITEM_FLAG_NOFIREUNDERWATER  		BIT(5)
#define ITEM_FLAG_EXHAUST_SECONDARYAMMO		BIT(6) // A player will exhaust weapon's secondary ammo supply if dropped (ITEM_FLAG_EXHAUSTIBLE does both)

// if someone has an idea for another flag pack it here, so client prediction will not be screwed (or something) if PLAY_GAMEDLL is defined
#define ITEM_FLAG_CUSTOM	(ITEM_FLAG_NOFIREUNDERWATER | ITEM_FLAG_EXHAUST_SECONDARYAMMO)

#define WEAPON_IS_ONTARGET          0x40

// the maximum amount of ammo each weapon's clip can hold
#define WEAPON_NOCLIP               -1

#define LOUD_GUN_VOLUME             1000
#define NORMAL_GUN_VOLUME           600
#define QUIET_GUN_VOLUME            200

#define BRIGHT_GUN_FLASH            512
#define NORMAL_GUN_FLASH            256
#define DIM_GUN_FLASH               128

#define BIG_EXPLOSION_VOLUME        2048
#define NORMAL_EXPLOSION_VOLUME     1024
#define SMALL_EXPLOSION_VOLUME      512

#define WEAPON_ACTIVITY_VOLUME      64

// spawn flags
#define SF_DETONATE                 BIT(0) // Grenades flagged with this will be triggered when the owner calls detonateSatchelCharges

// custom enum
enum ArmorType
{
	ARMOR_NONE,     // No armor
	ARMOR_KEVLAR,   // Body vest only
	ARMOR_VESTHELM, // Vest and helmet
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
	ARMOURY_DEAGLE,
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
	EntityHandle<CBaseEntity> hEntity;
	float amount;
	int type;
};

#include "weapontype.h"
#include "items.h"

class CArmoury: public CBaseEntity
{
public:
	virtual void Spawn();
	virtual void Precache();
	virtual void Restart();
	virtual void KeyValue(KeyValueData *pkvd);
#ifdef REGAMEDLL_FIXES
	virtual void SetObjectCollisionBox();
#endif

public:
	void EXPORT ArmouryTouch(CBaseEntity *pOther);

private:
	void Draw();
	void Hide();

public:
	static char *m_ItemModels[];

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
		SATCHEL_RELEASE,
	};
public:
	void DefuseBombStart(CBasePlayer *pPlayer);
	void DefuseBombEnd(CBasePlayer *pPlayer, bool bDefused);

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

#ifdef REGAMEDLL_API
	static CGrenade *ShootTimed_OrigFunc(entvars_t *pevOwner, VectorRef vecStart, VectorRef vecVelocity, float time);
	static CGrenade *ShootTimed2_OrigFunc(entvars_t *pevOwner, VectorRef vecStart, VectorRef vecVelocity, float time, int iTeam, unsigned short usEvent);
	static CGrenade *ShootSmokeGrenade_OrigFunc(entvars_t *pevOwner, VectorRef vecStart, VectorRef vecVelocity, float time, unsigned short usEvent);
	static CGrenade *ShootSatchelCharge_OrigFunc(entvars_t *pevOwner, VectorRef vecStart, VectorRef vecVelocity);

	void DefuseBombStart_OrigFunc(CBasePlayer *pPlayer);
	void DefuseBombEnd_OrigFunc(CBasePlayer *pPlayer, bool bDefused);

	void Explode_OrigFunc(TraceResult *pTrace, int bitsDamageType);
	void Explode3_OrigFunc(TraceResult *pTrace, int bitsDamageType);
	void Explode2_OrigFunc(TraceResult *pTrace, int bitsDamageType);
	void SG_Detonate_OrigFunc();
#endif

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
	static TYPEDESCRIPTION m_SaveData[];

	bool m_bStartDefuse;
	bool m_bIsC4;
	EntityHandle<CBasePlayer> m_pBombDefuser;
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

// Items that the player has in their inventory that they can use
class CCSPlayerItem;
class CBasePlayerItem: public CBaseAnimating
{
public:
	virtual int Save(CSave &save);
	virtual int Restore(CRestore &restore);
	virtual void SetObjectCollisionBox();
	virtual CBaseEntity *Respawn();
	virtual int AddToPlayer(CBasePlayer *pPlayer);							// return TRUE if the item you want the item added to the player inventory
	virtual int AddDuplicate(CBasePlayerItem *pItem) { return FALSE; }		// return TRUE if you want your duplicate removed from world
	virtual int GetItemInfo(ItemInfo *p) { return 0; }						// returns 0 if struct not filled out
	virtual BOOL CanDeploy() { return TRUE; }
	virtual BOOL CanDrop() { return TRUE; }									// returns is deploy was successful
	virtual BOOL Deploy() { return TRUE; }
	virtual BOOL IsWeapon() { return FALSE; }
	virtual BOOL CanHolster() { return TRUE; }								// can this weapon be put away right now?
	virtual void Holster(int skiplocal = 0);
	virtual void UpdateItemInfo() {}
	virtual void ItemPreFrame() {}											// called each frame by the player PreThink
	virtual void ItemPostFrame() {}											// called each frame by the player PostThink
	virtual void Drop();
	virtual void Kill();
	virtual void AttachToPlayer(CBasePlayer *pPlayer);
	virtual int PrimaryAmmoIndex() { return -1; }
	virtual int SecondaryAmmoIndex() { return -1; }
	virtual int UpdateClientData(CBasePlayer *pPlayer) { return 0; }
	virtual CBasePlayerItem *GetWeaponPtr() { return nullptr; }
	virtual float GetMaxSpeed() { return 260.0f; }
	virtual int iItemSlot() { return 0; }									// return 0 to MAX_ITEMS_SLOTS, used in hud

public:
	bool EXPORT DestroyItem();
	void EXPORT DefaultTouch(CBaseEntity *pOther);
	void EXPORT FallThink();
	void EXPORT Materialize();
	void EXPORT AttemptToMaterialize();

	void FallInit();
	void CheckRespawn();

public:
#ifdef REGAMEDLL_API
	CCSPlayerItem *CSPlayerItem() const;
#endif

	const char *pszAmmo1() const;
	int iMaxAmmo1() const;
	const char *pszAmmo2() const;
	int iMaxAmmo2() const;
	const char *pszName() const;
	int iMaxClip() const;
	int iWeight() const;
	int iFlags() const;

public:
	static TYPEDESCRIPTION m_SaveData[];
	static ItemInfo m_ItemInfoArray[MAX_WEAPONS];
	static AmmoInfo m_AmmoInfoArray[MAX_AMMO_SLOTS];

	CBasePlayer *m_pPlayer;
	CBasePlayerItem *m_pNext;
	int m_iId;							// WEAPON_???
};

#ifdef REGAMEDLL_API
inline CCSPlayerItem *CBasePlayerItem::CSPlayerItem() const
{
	return reinterpret_cast<CCSPlayerItem *>(this->m_pEntity);
}
#endif

// inventory items that
class CCSPlayerWeapon;
class CBasePlayerWeapon: public CBasePlayerItem
{
public:
	virtual void Spawn();
	virtual int Save(CSave &save);
	virtual int Restore(CRestore &restore);

	// generic weapon versions of CBasePlayerItem calls
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
	bool HasSecondaryAttack();
	BOOL IsPistol() { return (m_iId == WEAPON_USP || m_iId == WEAPON_GLOCK18 || m_iId == WEAPON_P228 || m_iId == WEAPON_DEAGLE || m_iId == WEAPON_ELITE || m_iId == WEAPON_FIVESEVEN); }
	void SetPlayerShieldAnim();
	void ResetPlayerShieldAnim();
	bool ShieldSecondaryFire(int iUpAnim, int iDownAnim);
	void HandleInfiniteAmmo();
	void InstantReload(bool bCanRefillBPAmmo = false);
	bool DefaultShotgunReload(int iAnim, int iStartAnim, float fDelay, float fStartDelay, const char *pszReloadSound1 = nullptr, const char *pszReloadSound2 = nullptr);

#ifdef REGAMEDLL_API
	BOOL CanDeploy_OrigFunc();
	BOOL DefaultDeploy_OrigFunc(char *szViewModel, char *szWeaponModel, int iAnim, char *szAnimExt, int skiplocal);
	BOOL DefaultReload_OrigFunc(int iClipSize, int iAnim, float fDelay);
	bool DefaultShotgunReload_OrigFunc(int iAnim, int iStartAnim, float fDelay, float fStartDelay, const char *pszReloadSound1, const char *pszReloadSound2);
	void KickBack_OrigFunc(float up_base, float lateral_base, float up_modifier, float lateral_modifier, float up_max, float lateral_max, int direction_change);
	void SendWeaponAnim_OrigFunc(int iAnim, int skiplocal);
	void ItemPostFrame_OrigFunc();

	CCSPlayerWeapon *CSPlayerWeapon() const;
#endif

public:
	static TYPEDESCRIPTION m_SaveData[];

	int m_iPlayEmptySound;
	int m_fFireOnEmpty;
	float m_flNextPrimaryAttack;	// soonest time ItemPostFrame will call PrimaryAttack
	float m_flNextSecondaryAttack;	// soonest time ItemPostFrame will call SecondaryAttack
	float m_flTimeWeaponIdle;		// soonest time ItemPostFrame will call WeaponIdle
	int m_iPrimaryAmmoType;			// "primary" ammo index into players m_rgAmmo[]
	int m_iSecondaryAmmoType;		// "secondary" ammo index into players m_rgAmmo[]
	int m_iClip;					// number of shots left in the primary weapon clip, -1 it not used
	int m_iClientClip;				// the last version of m_iClip sent to hud dll
	int m_iClientWeaponState;		// the last version of the weapon state sent to hud dll (is current weapon, is on target)
	int m_fInReload;				// Are we in the middle of a reload;
	int m_fInSpecialReload;			// Are we in the middle of a reload for the shotguns
	int m_iDefaultAmmo;				// how much ammo you get when you pick up this weapon as placed by a level designer.
	int m_iShellId;
	float m_fMaxSpeed;
	bool m_bDelayFire;
	BOOL m_iDirection;
	bool m_bSecondarySilencerOn;
	float m_flAccuracy;
	float m_flLastFire;
	int m_iShotsFired;
	Vector m_vVecAiming;
	string_t model_name;
	float m_flGlock18Shoot;			// time to shoot the remaining bullets of the glock18 burst fire
	int m_iGlock18ShotsFired;		// used to keep track of the shots fired during the Glock18 burst fire mode.
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

#ifdef REGAMEDLL_API
inline CCSPlayerWeapon *CBasePlayerWeapon::CSPlayerWeapon() const
{
	return reinterpret_cast<CCSPlayerWeapon *>(this->m_pEntity);
}
#endif

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
	int GiveAmmo(int iCount, char *szName, int iMax, int *pIndex = nullptr);
	int GetAmmoIndex(const char *psz) const;
	bool GiveAmmoToPlayer(CBasePlayer *pPlayer, CBasePlayerWeapon *pWeapon,
		int iCurrentAmmo, const char *pszAmmo, int iMaxAmmo, CBasePlayerItem **pGivenItem = NULL);

	void EXPORT Kill();
	void EXPORT BombThink();
	void SetModel(const char *pszModelName);

	BOOL HasWeapon(CBasePlayerItem *pCheckItem);
	BOOL PackWeapon(CBasePlayerItem *pWeapon);
	BOOL PackAmmo(string_t iszName, int iCount);

#ifdef REGAMEDLL_API
	void SetModel_OrigFunc(const char *pszModelName);
#endif

public:
	static TYPEDESCRIPTION m_SaveData[];

	CBasePlayerItem *m_rgpPlayerItems[MAX_ITEM_TYPES];
	string_t m_rgiszAmmo[MAX_AMMO_SLOTS];
	int m_rgAmmo[MAX_AMMO_SLOTS];
	int m_cAmmoTypes;
	bool m_bIsBomb;
};


const float USP_MAX_SPEED       = 250.0f;
const float USP_DAMAGE          = 34.0f;
const float USP_DAMAGE_SIL      = 30.0f;
const float USP_RANGE_MODIFER   = 0.79f;
const float USP_RELOAD_TIME     = 2.7f;

#ifdef REGAMEDLL_FIXES
const float USP_ADJUST_SIL_TIME = 3.13f;
#else
const float USP_ADJUST_SIL_TIME = 3.0f;
#endif

enum usp_e
{
	USP_IDLE,
	USP_SHOOT1,
	USP_SHOOT2,
	USP_SHOOT3,
	USP_SHOOT_EMPTY,
	USP_RELOAD,
	USP_DRAW,
	USP_ATTACH_SILENCER,
	USP_UNSIL_IDLE,
	USP_UNSIL_SHOOT1,
	USP_UNSIL_SHOOT2,
	USP_UNSIL_SHOOT3,
	USP_UNSIL_SHOOT_EMPTY,
	USP_UNSIL_RELOAD,
	USP_UNSIL_DRAW,
	USP_DETACH_SILENCER,
};

enum usp_shield_e
{
	USP_SHIELD_IDLE,
	USP_SHIELD_SHOOT1,
	USP_SHIELD_SHOOT2,
	USP_SHIELD_SHOOT_EMPTY,
	USP_SHIELD_RELOAD,
	USP_SHIELD_DRAW,
	USP_SHIELD_IDLE_UP,
	USP_SHIELD_UP,
	USP_SHIELD_DOWN,
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

#ifdef REGAMEDLL_API
	float m_flBaseDamageSil;
#endif
};


const float MP5N_MAX_SPEED     = 250.0f;
const float MP5N_DAMAGE        = 26.0f;
const float MP5N_RANGE_MODIFER = 0.84f;
const float MP5N_RELOAD_TIME   = 2.63f;
#ifdef REGAMEDLL_FIXES
const float MP5N_ACCURACY_DIVISOR = 220.1f;
#else
const double MP5N_ACCURACY_DIVISOR = 220.1;
#endif

enum mp5n_e
{
	MP5N_IDLE1,
	MP5N_RELOAD,
	MP5N_DRAW,
	MP5N_SHOOT1,
	MP5N_SHOOT2,
	MP5N_SHOOT3,
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


const float SG552_MAX_SPEED      = 235.0f;
const float SG552_MAX_SPEED_ZOOM = 200.0f;
const float SG552_DAMAGE         = 33.0f;
const float SG552_RANGE_MODIFER  = 0.955f;
const float SG552_RELOAD_TIME    = 3.0f;
#ifdef REGAMEDLL_FIXES
const float SG552_ACCURACY_DIVISOR = 220.0f;
#else
const int SG552_ACCURACY_DIVISOR = 220;
#endif

enum sg552_e
{
	SG552_IDLE1,
	SG552_RELOAD,
	SG552_DRAW,
	SG552_SHOOT1,
	SG552_SHOOT2,
	SG552_SHOOT3,
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


const float AK47_MAX_SPEED     = 221.0f;
const float AK47_DAMAGE        = 36.0f;
const float AK47_RANGE_MODIFER = 0.98f;
const float AK47_RELOAD_TIME   = 2.45f;
#ifdef REGAMEDLL_FIXES
const float AK47_ACCURACY_DIVISOR = 200.0f;
#else
const int AK47_ACCURACY_DIVISOR = 200;
#endif

enum ak47_e
{
	AK47_IDLE1,
	AK47_RELOAD,
	AK47_DRAW,
	AK47_SHOOT1,
	AK47_SHOOT2,
	AK47_SHOOT3,
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


const float AUG_MAX_SPEED     = 240.0f;
const float AUG_DAMAGE        = 32.0f;
const float AUG_RANGE_MODIFER = 0.96f;
const float AUG_RELOAD_TIME   = 3.3f;
#ifdef REGAMEDLL_FIXES
const float AUG_ACCURACY_DIVISOR = 215.0f;
#else
const int AUG_ACCURACY_DIVISOR = 215;
#endif

enum aug_e
{
	AUG_IDLE1,
	AUG_RELOAD,
	AUG_DRAW,
	AUG_SHOOT1,
	AUG_SHOOT2,
	AUG_SHOOT3,
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


const float AWP_MAX_SPEED      = 210.0f;
const float AWP_MAX_SPEED_ZOOM = 150.0f;
const float AWP_DAMAGE         = 115.0f;
const float AWP_RANGE_MODIFER  = 0.99f;
const float AWP_RELOAD_TIME    = 2.5f;

enum awp_e
{
	AWP_IDLE,
	AWP_SHOOT,
	AWP_SHOOT2,
	AWP_SHOOT3,
	AWP_RELOAD,
	AWP_DRAW,
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

const float C4_MAX_SPEED      = 250.0f;
const float C4_ARMING_ON_TIME = 3.0f;

enum c4_e
{
	C4_IDLE1,
	C4_DRAW,
	C4_DROP,
	C4_ARM,
};

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


const float DEAGLE_MAX_SPEED     = 250.0f;
const float DEAGLE_DAMAGE        = 54.0f;
const float DEAGLE_RANGE_MODIFER = 0.81f;
const float DEAGLE_RELOAD_TIME   = 2.2f;

enum deagle_e
{
	DEAGLE_IDLE1,
	DEAGLE_SHOOT1,
	DEAGLE_SHOOT2,
	DEAGLE_SHOOT_EMPTY,
	DEAGLE_RELOAD,
	DEAGLE_DRAW,
};

enum deagle_shield_e
{
	DEAGLE_SHIELD_IDLE1,
	DEAGLE_SHIELD_SHOOT,
	DEAGLE_SHIELD_SHOOT2,
	DEAGLE_SHIELD_SHOOT_EMPTY,
	DEAGLE_SHIELD_RELOAD,
	DEAGLE_SHIELD_DRAW,
	DEAGLE_SHIELD_IDLE_UP,
	DEAGLE_SHIELD_UP,
	DEAGLE_SHIELD_DOWN,
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


const float FLASHBANG_MAX_SPEED        = 250.0f;
const float FLASHBANG_MAX_SPEED_SHIELD = 180.0f;

enum flashbang_e
{
	FLASHBANG_IDLE,
	FLASHBANG_PULLPIN,
	FLASHBANG_THROW,
	FLASHBANG_DRAW,
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

#ifdef REGAMEDLL_API
	BOOL CanDeploy_OrigFunc();
#endif

public:
	bool ShieldSecondaryFire(int iUpAnim, int iDownAnim);
	void SetPlayerShieldAnim();
	void ResetPlayerShieldAnim();
};


const float G3SG1_MAX_SPEED      = 210.0f;
const float G3SG1_MAX_SPEED_ZOOM = 150.0f;
const float G3SG1_DAMAGE         = 80.0f;
const float G3SG1_RANGE_MODIFER  = 0.98f;
const float G3SG1_RELOAD_TIME    = 3.5f;

enum g3sg1_e
{
	G3SG1_IDLE,
	G3SG1_SHOOT,
	G3SG1_SHOOT2,
	G3SG1_RELOAD,
	G3SG1_DRAW,
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


const float GLOCK18_MAX_SPEED     = 250.0f;
const float GLOCK18_DAMAGE        = 25.0f;
const float GLOCK18_RANGE_MODIFER = 0.75f;
const float GLOCK18_RELOAD_TIME   = 2.2f;

enum glock18_e
{
	GLOCK18_IDLE1,
	GLOCK18_IDLE2,
	GLOCK18_IDLE3,
	GLOCK18_SHOOT,
	GLOCK18_SHOOT2,
	GLOCK18_SHOOT3,
	GLOCK18_SHOOT_EMPTY,
	GLOCK18_RELOAD,
	GLOCK18_DRAW,
	GLOCK18_HOLSTER,
	GLOCK18_ADD_SILENCER,
	GLOCK18_DRAW2,
	GLOCK18_RELOAD2,
};

enum glock18_shield_e
{
	GLOCK18_SHIELD_IDLE1,
	GLOCK18_SHIELD_SHOOT,
	GLOCK18_SHIELD_SHOOT2,
	GLOCK18_SHIELD_SHOOT_EMPTY,
	GLOCK18_SHIELD_RELOAD,
	GLOCK18_SHIELD_DRAW,
	GLOCK18_SHIELD_IDLE_UP,
	GLOCK18_SHIELD_UP,
	GLOCK18_SHIELD_DOWN,
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


const float HEGRENADE_MAX_SPEED        = 250.0f;
const float HEGRENADE_MAX_SPEED_SHIELD = 180.0f;

enum hegrenade_e
{
	HEGRENADE_IDLE,
	HEGRENADE_PULLPIN,
	HEGRENADE_THROW,
	HEGRENADE_DRAW,
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

#ifdef REGAMEDLL_API
	BOOL CanDeploy_OrigFunc();
#endif

public:
	bool ShieldSecondaryFire(int iUpAnim, int iDownAnim);
	void SetPlayerShieldAnim();
	void ResetPlayerShieldAnim();

public:
	unsigned short m_usCreateExplosion;
};


const float KNIFE_BODYHIT_VOLUME      = 128.0f;
const float KNIFE_WALLHIT_VOLUME      = 512.0f;
const float KNIFE_MAX_SPEED           = 250.0f;
const float KNIFE_MAX_SPEED_SHIELD    = 180.0f;
const float KNIFE_STAB_DAMAGE         = 65.0f;
const float KNIFE_SWING_DAMAGE        = 15.0f;
const float KNIFE_SWING_DAMAGE_FAST   = 20.0f;
const float KNIFE_STAB_DISTANCE       = 32.0f;
const float KNIFE_SWING_DISTANCE      = 48.0f;
const float KNIFE_BACKSTAB_MULTIPLIER = 3.0f;

enum knife_e
{
	KNIFE_IDLE,
	KNIFE_ATTACK1HIT,
	KNIFE_ATTACK2HIT,
	KNIFE_DRAW,
	KNIFE_STABHIT,
	KNIFE_STABMISS,
	KNIFE_MIDATTACK1HIT,
	KNIFE_MIDATTACK2HIT,
};

enum knife_shield_e
{
	KNIFE_SHIELD_IDLE,
	KNIFE_SHIELD_SLASH,
	KNIFE_SHIELD_ATTACKHIT,
	KNIFE_SHIELD_DRAW,
	KNIFE_SHIELD_IDLE_UP,
	KNIFE_SHIELD_UP,
	KNIFE_SHIELD_DOWN,
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
	BOOL Stab(BOOL fFirst);
	BOOL Swing(BOOL fFirst);

public:
	bool ShieldSecondaryFire(int iUpAnim, int iDownAnim);
	void SetPlayerShieldAnim();
	void ResetPlayerShieldAnim();

	float KnifeStabDamage() const;
	float KnifeSwingDamage(bool fast) const;
	float KnifeStabDistance() const;
	float KnifeSwingDistance() const;
	float KnifeBackStabMultiplier() const;

private:
	TraceResult m_trHit;
	unsigned short m_usKnife;

#ifdef REGAMEDLL_API
	float m_flStabBaseDamage;
	float m_flSwingBaseDamage;
	float m_flSwingBaseDamage_Fast;

	float m_flStabDistance;
	float m_flSwingDistance;

	float m_flBackStabMultiplier;
#endif
};

#ifdef REGAMEDLL_API
inline float CKnife::KnifeStabDamage() const			{ return m_flStabBaseDamage; }
inline float CKnife::KnifeSwingDamage(bool fast) const	{ return fast ? m_flSwingBaseDamage_Fast : m_flSwingBaseDamage; }
inline float CKnife::KnifeStabDistance() const			{ return m_flStabDistance; }
inline float CKnife::KnifeSwingDistance() const			{ return m_flSwingDistance; }
inline float CKnife::KnifeBackStabMultiplier() const	{ return m_flBackStabMultiplier; }
#else
inline float CKnife::KnifeStabDamage() const			{ return KNIFE_STAB_DAMAGE; }
inline float CKnife::KnifeSwingDamage(bool fast) const	{ return fast ? KNIFE_SWING_DAMAGE_FAST : KNIFE_SWING_DAMAGE; }
inline float CKnife::KnifeStabDistance() const			{ return KNIFE_STAB_DISTANCE; }
inline float CKnife::KnifeSwingDistance() const			{ return KNIFE_SWING_DISTANCE; }
inline float CKnife::KnifeBackStabMultiplier() const	{ return KNIFE_BACKSTAB_MULTIPLIER; }
#endif // REGAMEDLL_API

const float M249_MAX_SPEED     = 220.0f;
const float M249_DAMAGE        = 32.0f;
const float M249_RANGE_MODIFER = 0.97f;
const float M249_RELOAD_TIME   = 4.7f;
#ifdef REGAMEDLL_FIXES
const float M249_ACCURACY_DIVISOR = 175.0f;
#else
const int M249_ACCURACY_DIVISOR = 175;
#endif

enum m249_e
{
	M249_IDLE1,
	M249_SHOOT1,
	M249_SHOOT2,
	M249_RELOAD,
	M249_DRAW,
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


const float M3_MAX_SPEED   = 230.0f;
const float M3_DAMAGE      = 20.0f;
const Vector M3_CONE_VECTOR = Vector(0.0675, 0.0675, 0.0); // special shotgun spreads

enum m3_e
{
	M3_IDLE,
	M3_FIRE1,
	M3_FIRE2,
	M3_RELOAD,
	M3_PUMP,
	M3_START_RELOAD,
	M3_DRAW,
	M3_HOLSTER,
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
	virtual BOOL PlayEmptySound();
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


const float M4A1_MAX_SPEED         = 230.0f;
const float M4A1_DAMAGE            = 32.0f;
const float M4A1_DAMAGE_SIL        = 33.0f;
const float M4A1_RANGE_MODIFER     = 0.97f;
const float M4A1_RANGE_MODIFER_SIL = 0.95f;
const float M4A1_RELOAD_TIME       = 3.05f;
#ifdef REGAMEDLL_FIXES
const float M4A1_ACCURACY_DIVISOR = 220.0f;
#else
const int M4A1_ACCURACY_DIVISOR = 220;
#endif

enum m4a1_e
{
	M4A1_IDLE,
	M4A1_SHOOT1,
	M4A1_SHOOT2,
	M4A1_SHOOT3,
	M4A1_RELOAD,
	M4A1_DRAW,
	M4A1_ATTACH_SILENCER,
	M4A1_UNSIL_IDLE,
	M4A1_UNSIL_SHOOT1,
	M4A1_UNSIL_SHOOT2,
	M4A1_UNSIL_SHOOT3,
	M4A1_UNSIL_RELOAD,
	M4A1_UNSIL_DRAW,
	M4A1_DETACH_SILENCER,
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

#ifdef REGAMEDLL_API
	float m_flBaseDamageSil;
#endif
};


const float MAC10_MAX_SPEED     = 250.0f;
const float MAC10_DAMAGE        = 29.0f;
const float MAC10_RANGE_MODIFER = 0.82f;
const float MAC10_RELOAD_TIME   = 3.15f;
#ifdef REGAMEDLL_FIXES
const float MAC10_ACCURACY_DIVISOR = 200.0f;
#else
const int MAC10_ACCURACY_DIVISOR = 200;
#endif

enum mac10_e
{
	MAC10_IDLE1,
	MAC10_RELOAD,
	MAC10_DRAW,
	MAC10_SHOOT1,
	MAC10_SHOOT2,
	MAC10_SHOOT3,
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


const float P228_MAX_SPEED     = 250.0f;
const float P228_DAMAGE        = 32.0f;
const float P228_RANGE_MODIFER = 0.8f;
const float P228_RELOAD_TIME   = 2.7f;

enum p228_e
{
	P228_IDLE,
	P228_SHOOT1,
	P228_SHOOT2,
	P228_SHOOT3,
	P228_SHOOT_EMPTY,
	P228_RELOAD,
	P228_DRAW,
};

enum p228_shield_e
{
	P228_SHIELD_IDLE,
	P228_SHIELD_SHOOT1,
	P228_SHIELD_SHOOT2,
	P228_SHIELD_SHOOT_EMPTY,
	P228_SHIELD_RELOAD,
	P228_SHIELD_DRAW,
	P228_SHIELD_IDLE_UP,
	P228_SHIELD_UP,
	P228_SHIELD_DOWN,
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


const float P90_MAX_SPEED     = 245.0f;
const float P90_DAMAGE        = 21.0f;
const float P90_RANGE_MODIFER = 0.885f;
const float P90_RELOAD_TIME   = 3.4f;
#ifdef REGAMEDLL_FIXES
const float P90_ACCURACY_DIVISOR = 175.0f;
#else
const int P90_ACCURACY_DIVISOR = 175;
#endif

enum p90_e
{
	P90_IDLE1,
	P90_RELOAD,
	P90_DRAW,
	P90_SHOOT1,
	P90_SHOOT2,
	P90_SHOOT3,
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


const float SCOUT_MAX_SPEED      = 260.0f;
const float SCOUT_MAX_SPEED_ZOOM = 220.0f;
const float SCOUT_DAMAGE         = 75.0f;
const float SCOUT_RANGE_MODIFER  = 0.98f;
const float SCOUT_RELOAD_TIME    = 2.0f;

enum scout_e
{
	SCOUT_IDLE,
	SCOUT_SHOOT,
	SCOUT_SHOOT2,
	SCOUT_RELOAD,
	SCOUT_DRAW,
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


const float SMOKEGRENADE_MAX_SPEED        = 250.0f;
const float SMOKEGRENADE_MAX_SPEED_SHIELD = 180.0f;

enum smokegrenade_e
{
	SMOKEGRENADE_IDLE,
	SMOKEGRENADE_PINPULL,
	SMOKEGRENADE_THROW,
	SMOKEGRENADE_DRAW,
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

#ifdef REGAMEDLL_API
	BOOL CanDeploy_OrigFunc();
#endif

public:
	bool ShieldSecondaryFire(int iUpAnim, int iDownAnim);
	void SetPlayerShieldAnim();
	void ResetPlayerShieldAnim();

public:
	unsigned short m_usCreateSmoke;
};


const float TMP_MAX_SPEED     = 250.0f;
const float TMP_DAMAGE        = 20.0f;
const float TMP_RANGE_MODIFER = 0.85f;
const float TMP_RELOAD_TIME   = 2.12f;
#ifdef REGAMEDLL_FIXES
const float TMP_ACCURACY_DIVISOR = 200.0f;
#else
const int TMP_ACCURACY_DIVISOR = 200;
#endif

enum tmp_e
{
	TMP_IDLE1,
	TMP_RELOAD,
	TMP_DRAW,
	TMP_SHOOT1,
	TMP_SHOOT2,
	TMP_SHOOT3,
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


const float XM1014_MAX_SPEED   = 240.0f;
const float XM1014_DAMAGE      = 20.0f;
const Vector XM1014_CONE_VECTOR = Vector(0.0725, 0.0725, 0.0); // special shotgun spreads

enum xm1014_e
{
	XM1014_IDLE,
	XM1014_FIRE1,
	XM1014_FIRE2,
	XM1014_RELOAD,
	XM1014_PUMP,
	XM1014_START_RELOAD,
	XM1014_DRAW,
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
	virtual BOOL PlayEmptySound();
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


const float ELITE_MAX_SPEED     = 250.0f;
const float ELITE_RELOAD_TIME   = 4.5f;
const float ELITE_DAMAGE        = 36.0f;
const float ELITE_RANGE_MODIFER = 0.75f;

enum elite_e
{
	ELITE_IDLE,
	ELITE_IDLE_LEFTEMPTY,
	ELITE_SHOOTLEFT1,
	ELITE_SHOOTLEFT2,
	ELITE_SHOOTLEFT3,
	ELITE_SHOOTLEFT4,
	ELITE_SHOOTLEFT5,
	ELITE_SHOOTLEFTLAST,
	ELITE_SHOOTRIGHT1,
	ELITE_SHOOTRIGHT2,
	ELITE_SHOOTRIGHT3,
	ELITE_SHOOTRIGHT4,
	ELITE_SHOOTRIGHT5,
	ELITE_SHOOTRIGHTLAST,
	ELITE_RELOAD,
	ELITE_DRAW,
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


const float FIVESEVEN_MAX_SPEED     = 250.0f;
const float FIVESEVEN_DAMAGE        = 20.0f;
const float FIVESEVEN_RANGE_MODIFER = 0.885f;
const float FIVESEVEN_RELOAD_TIME   = 2.7f;

enum fiveseven_e
{
	FIVESEVEN_IDLE,
	FIVESEVEN_SHOOT1,
	FIVESEVEN_SHOOT2,
	FIVESEVEN_SHOOT_EMPTY,
	FIVESEVEN_RELOAD,
	FIVESEVEN_DRAW,
};

enum fiveseven_shield_e
{
	FIVESEVEN_SHIELD_IDLE1,
	FIVESEVEN_SHIELD_SHOOT,
	FIVESEVEN_SHIELD_SHOOT2,
	FIVESEVEN_SHIELD_SHOOT_EMPTY,
	FIVESEVEN_SHIELD_RELOAD,
	FIVESEVEN_SHIELD_DRAW,
	FIVESEVEN_SHIELD_IDLE_UP,
	FIVESEVEN_SHIELD_UP,
	FIVESEVEN_SHIELD_DOWN,
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


const float UMP45_MAX_SPEED     = 250.0f;
const float UMP45_DAMAGE        = 30.0f;
const float UMP45_RANGE_MODIFER = 0.82f;
const float UMP45_RELOAD_TIME   = 3.5f;
#ifdef REGAMEDLL_FIXES
const float UMP45_ACCURACY_DIVISOR = 210.0f;
#else
const int UMP45_ACCURACY_DIVISOR = 210;
#endif

enum ump45_e
{
	UMP45_IDLE1,
	UMP45_RELOAD,
	UMP45_DRAW,
	UMP45_SHOOT1,
	UMP45_SHOOT2,
	UMP45_SHOOT3,
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


const float SG550_MAX_SPEED      = 210.0f;
const float SG550_MAX_SPEED_ZOOM = 150.0f;
const float SG550_DAMAGE         = 70.0f;
const float SG550_RANGE_MODIFER  = 0.98f;
const float SG550_RELOAD_TIME    = 3.35f;

enum sg550_e
{
	SG550_IDLE,
	SG550_SHOOT,
	SG550_SHOOT2,
	SG550_RELOAD,
	SG550_DRAW,
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


const float GALIL_MAX_SPEED     = 240.0f;
const float GALIL_DAMAGE        = 30.0f;
const float GALIL_RANGE_MODIFER = 0.98f;
const float GALIL_RELOAD_TIME   = 2.45f;
#ifdef REGAMEDLL_FIXES
const float GALIL_ACCURACY_DIVISOR = 200.0f;
#else
const int GALIL_ACCURACY_DIVISOR = 200;
#endif

enum galil_e
{
	GALIL_IDLE1,
	GALIL_RELOAD,
	GALIL_DRAW,
	GALIL_SHOOT1,
	GALIL_SHOOT2,
	GALIL_SHOOT3,
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


const float FAMAS_MAX_SPEED     = 240.0f;
const float FAMAS_RELOAD_TIME   = 3.3f;
const float FAMAS_DAMAGE        = 30.0f;
const float FAMAS_DAMAGE_BURST  = 34.0f;
const float FAMAS_RANGE_MODIFER = 0.96f;
#ifdef REGAMEDLL_FIXES
const float FAMAS_ACCURACY_DIVISOR = 215.0f;
#else
const int FAMAS_ACCURACY_DIVISOR = 215;
#endif

enum famas_e
{
	FAMAS_IDLE1,
	FAMAS_RELOAD,
	FAMAS_DRAW,
	FAMAS_SHOOT1,
	FAMAS_SHOOT2,
	FAMAS_SHOOT3,
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

#ifdef REGAMEDLL_API
	float m_flBaseDamageBurst;
#endif
};

extern short g_sModelIndexLaser;
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

void WeaponsPrecache();
void FindHullIntersection(const Vector &vecSrc, TraceResult &tr, float *mins, float *maxs, edict_t *pEntity);
void AnnounceFlashInterval(float interval, float offset = 0);

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
int AddAmmoNameToAmmoRegistry(const char *szAmmoname);
void UTIL_PrecacheOtherWeapon(const char *szClassname);
BOOL CanAttack(float attack_time, float curtime, BOOL isPredicted);
float GetBaseAccuracy(WeaponIdType id);

#ifdef REGAMEDLL_API
void ClearMultiDamage_OrigFunc();
void ApplyMultiDamage_OrigFunc(entvars_t *pevInflictor, entvars_t *pevAttacker);
void AddMultiDamage_OrigFunc(entvars_t *pevInflictor, CBaseEntity *pEntity, float flDamage, int bitsDamageType);
#endif

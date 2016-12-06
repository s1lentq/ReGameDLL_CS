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

#include "weapontype.h"

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
	ARMOURY_GLOCK18,
	ARMOURY_USP,
	ARMOURY_ELITE,
	ARMOURY_FIVESEVEN,
	ARMOURY_P228,
	ARMOURY_DEAGLE,
	ARMOURY_FAMAS,
	ARMOURY_SG550,
	ARMOURY_GALIL,
	ARMOURY_UMP45,
	ARMOURY_SHIELD
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

class CArmoury: public CBaseEntity {
public:
	virtual void Spawn() = 0;
	virtual void Precache() = 0;
	virtual void Restart() = 0;
	virtual void KeyValue(KeyValueData *pkvd) = 0;
public:
	ArmouryItemPack m_iItem;
	int m_iCount;
	int m_iInitialCount;
	bool m_bAlreadyCounted;
};

// Smoke Grenade / HE grenade / Flashbang grenade / C4
class CGrenade: public CBaseMonster {
public:
	virtual void Spawn() = 0;
	virtual int Save(CSave &save) = 0;
	virtual int Restore(CRestore &restore) = 0;
	virtual int ObjectCaps() = 0;
	virtual void Killed(entvars_t *pevAttacker, int iGib) = 0;
	virtual int BloodColor() = 0;
	virtual void Use(CBaseEntity *pActivator, CBaseEntity *pCaller, USE_TYPE useType, float value) = 0;
	virtual void BounceSound() = 0;
public:
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
	BOOL m_fRegisteredSound;	// whether or not this grenade has issued its DANGER sound to the world sound list yet.
};

// Items that the player has in their inventory that they can use
class CBasePlayerItem: public CBaseAnimating {
public:
	virtual int Save(CSave &save) = 0;
	virtual int Restore(CRestore &restore) = 0;
	virtual void SetObjectCollisionBox() = 0;
	virtual CBaseEntity *Respawn() = 0;
	virtual int AddToPlayer(CBasePlayer *pPlayer) = 0;		// return TRUE if the item you want the item added to the player inventory
	virtual int AddDuplicate(CBasePlayerItem *pItem) = 0;		// return TRUE if you want your duplicate removed from world
	virtual int GetItemInfo(ItemInfo *p) = 0;			// returns 0 if struct not filled out
	virtual BOOL CanDeploy() = 0;
	virtual BOOL CanDrop() = 0;					// returns is deploy was successful
	virtual BOOL Deploy() = 0;
	virtual BOOL IsWeapon() = 0;
	virtual BOOL CanHolster() = 0;					// can this weapon be put away right now?
	virtual void Holster(int skiplocal = 0) = 0;
	virtual void UpdateItemInfo() = 0;
	virtual void ItemPreFrame() = 0;				// called each frame by the player PreThink
	virtual void ItemPostFrame() = 0;				// called each frame by the player PostThink
	virtual void Drop() = 0;
	virtual void Kill() = 0;
	virtual void AttachToPlayer(CBasePlayer *pPlayer) = 0;
	virtual int PrimaryAmmoIndex() = 0;
	virtual int SecondaryAmmoIndex() = 0;
	virtual int UpdateClientData(CBasePlayer *pPlayer) = 0;
	virtual CBasePlayerItem *GetWeaponPtr() = 0;
	virtual float GetMaxSpeed() = 0;
	virtual int iItemSlot() = 0;					// return 0 to MAX_ITEMS_SLOTS, used in hud
public:
	CBasePlayer *m_pPlayer;
	CBasePlayerItem *m_pNext;
	int m_iId;							// WEAPON_???
};

// inventory items that
class CBasePlayerWeapon: public CBasePlayerItem {
public:
	virtual int Save(CSave &save) = 0;
	virtual int Restore(CRestore &restore) = 0;

	// generic weapon versions of CBasePlayerItem calls
	virtual int AddToPlayer(CBasePlayer *pPlayer) = 0;
	virtual int AddDuplicate(CBasePlayerItem *pItem) = 0;
	virtual BOOL CanDeploy() = 0;
	virtual BOOL IsWeapon() = 0;
	virtual void Holster(int skiplocal = 0) = 0;
	virtual void UpdateItemInfo() = 0;
	virtual void ItemPostFrame() = 0;
	virtual int PrimaryAmmoIndex() = 0;
	virtual int SecondaryAmmoIndex() = 0;
	virtual int UpdateClientData(CBasePlayer *pPlayer) = 0;
	virtual CBasePlayerItem *GetWeaponPtr() = 0;
	virtual int ExtractAmmo(CBasePlayerWeapon *pWeapon) = 0;
	virtual int ExtractClipAmmo(CBasePlayerWeapon *pWeapon) = 0;
	virtual int AddWeapon() = 0;
	virtual BOOL PlayEmptySound() = 0;
	virtual void ResetEmptySound() = 0;
	virtual void SendWeaponAnim(int iAnim, int skiplocal = 0) = 0;
	virtual BOOL IsUseable() = 0;
	virtual void PrimaryAttack() = 0;
	virtual void SecondaryAttack() = 0;
	virtual void Reload() = 0;
	virtual void WeaponIdle() = 0;
	virtual void RetireWeapon() = 0;
	virtual BOOL ShouldWeaponIdle() = 0;
	virtual BOOL UseDecrement() = 0;
public:
	BOOL IsPistol() { return (m_iId == WEAPON_USP || m_iId == WEAPON_GLOCK18 || m_iId == WEAPON_P228 || m_iId == WEAPON_DEAGLE || m_iId == WEAPON_ELITE || m_iId == WEAPON_FIVESEVEN); }

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

class CBasePlayerAmmo: public CBaseEntity {
public:
	virtual void Spawn() = 0;
	virtual BOOL AddAmmo(CBaseEntity *pOther) = 0;
	virtual CBaseEntity *Respawn() = 0;
};

class CWeaponBox: public CBaseEntity {
public:
	virtual void Spawn() = 0;
	virtual void Precache() = 0;
	virtual void KeyValue(KeyValueData *pkvd) = 0;
	virtual int Save(CSave &save) = 0;
	virtual int Restore(CRestore &restore) = 0;
	virtual void SetObjectCollisionBox() = 0;
	virtual void Touch(CBaseEntity *pOther) = 0;
public:
	CBasePlayerItem *m_rgpPlayerItems[MAX_ITEM_TYPES];
	int m_rgiszAmmo[MAX_AMMO_SLOTS];
	int m_rgAmmo[MAX_AMMO_SLOTS];
	int m_cAmmoTypes;
	bool m_bIsBomb;
};

class CUSP: public CBasePlayerWeapon {
public:
	virtual void Spawn() = 0;
	virtual void Precache() = 0;
	virtual int GetItemInfo(ItemInfo *p) = 0;
	virtual BOOL Deploy() = 0;
	virtual float GetMaxSpeed() = 0;
	virtual int iItemSlot() = 0;
	virtual void PrimaryAttack() = 0;
	virtual void SecondaryAttack() = 0;
	virtual void Reload() = 0;
	virtual void WeaponIdle() = 0;
	virtual BOOL UseDecrement() = 0;
	virtual BOOL IsPistol() = 0;

public:
	int m_iShell;
	unsigned short GetEventID() const { return m_usFireUSP; }
private:
	unsigned short m_usFireUSP;
};

class CMP5N: public CBasePlayerWeapon {
public:
	virtual void Spawn() = 0;
	virtual void Precache() = 0;
	virtual int GetItemInfo(ItemInfo *p) = 0;
	virtual BOOL Deploy() = 0;
	virtual float GetMaxSpeed() = 0;
	virtual int iItemSlot() = 0;
	virtual void PrimaryAttack() = 0;
	virtual void Reload() = 0;
	virtual void WeaponIdle() = 0;
	virtual BOOL UseDecrement() = 0;
public:
	int m_iShell;
	int iShellOn;
	unsigned short GetEventID() const { return m_usFireMP5N; }
private:
	unsigned short m_usFireMP5N;
};

class CSG552: public CBasePlayerWeapon {
public:
	virtual void Spawn() = 0;
	virtual void Precache() = 0;
	virtual int GetItemInfo(ItemInfo *p) = 0;
	virtual BOOL Deploy() = 0;
	virtual float GetMaxSpeed() = 0;
	virtual int iItemSlot() = 0;
	virtual void PrimaryAttack() = 0;
	virtual void SecondaryAttack() = 0;
	virtual void Reload() = 0;
	virtual void WeaponIdle() = 0;
	virtual BOOL UseDecrement() = 0;
public:
	int m_iShell;
	int iShellOn;
	unsigned short GetEventID() const { return m_usFireSG552; }
private:
	unsigned short m_usFireSG552;
};

class CAK47: public CBasePlayerWeapon {
public:
	virtual void Spawn() = 0;
	virtual void Precache() = 0;
	virtual int GetItemInfo(ItemInfo *p) = 0;
	virtual BOOL Deploy() = 0;
	virtual float GetMaxSpeed() = 0;
	virtual int iItemSlot() = 0;
	virtual void PrimaryAttack() = 0;
	virtual void SecondaryAttack() = 0;
	virtual void Reload() = 0;
	virtual void WeaponIdle() = 0;
	virtual BOOL UseDecrement() = 0;
public:
	int m_iShell;
	int iShellOn;
	unsigned short GetEventID() const { return m_usFireAK47; }
private:
	unsigned short m_usFireAK47;
};

class CAUG: public CBasePlayerWeapon {
public:
	virtual void Spawn() = 0;
	virtual void Precache() = 0;
	virtual int GetItemInfo(ItemInfo *p) = 0;
	virtual BOOL Deploy() = 0;
	virtual float GetMaxSpeed() = 0;
	virtual int iItemSlot() = 0;
	virtual void PrimaryAttack() = 0;
	virtual void SecondaryAttack() = 0;
	virtual void Reload() = 0;
	virtual void WeaponIdle() = 0;
	virtual BOOL UseDecrement() = 0;
public:
	int m_iShell;
	int iShellOn;
	unsigned short GetEventID() const { return m_usFireAug; }
private:
	unsigned short m_usFireAug;
};

class CAWP: public CBasePlayerWeapon {
public:
	virtual void Spawn() = 0;
	virtual void Precache() = 0;
	virtual int GetItemInfo(ItemInfo *p) = 0;
	virtual BOOL Deploy() = 0;
	virtual float GetMaxSpeed() = 0;
	virtual int iItemSlot() = 0;
	virtual void PrimaryAttack() = 0;
	virtual void SecondaryAttack() = 0;
	virtual void Reload() = 0;
	virtual void WeaponIdle() = 0;
	virtual BOOL UseDecrement() = 0;
public:
	int m_iShell;
	unsigned short GetEventID() const { return m_usFireAWP; }
private:
	unsigned short m_usFireAWP;
};

// for usermsg BombDrop
#define BOMB_FLAG_DROPPED	0 // if the bomb was dropped due to voluntary dropping or death/disconnect
#define BOMB_FLAG_PLANTED	1 // if the bomb has been planted will also trigger the round timer to hide will also show where the dropped bomb on the Terrorist team's radar.

class CC4: public CBasePlayerWeapon {
public:
	virtual void Spawn() = 0;
	virtual void Precache() = 0;
	virtual void KeyValue(KeyValueData *pkvd) = 0;
	virtual void Use(CBaseEntity *pActivator, CBaseEntity *pCaller, USE_TYPE useType, float value) = 0;
	virtual int GetItemInfo(ItemInfo *p) = 0;
	virtual BOOL Deploy() = 0;
	virtual void Holster(int skiplocal) = 0;
	virtual float GetMaxSpeed() = 0;
	virtual int iItemSlot() = 0;
	virtual void PrimaryAttack() = 0;
	virtual void WeaponIdle() = 0;
	virtual BOOL UseDecrement() = 0;
public:
	bool m_bStartedArming;
	bool m_bBombPlacedAnimation;
	float m_fArmedTime;
	bool HasShield() const { return m_bHasShield; }
private:
	bool m_bHasShield;
};

class CDEAGLE: public CBasePlayerWeapon {
public:
	virtual void Spawn() = 0;
	virtual void Precache() = 0;
	virtual int GetItemInfo(ItemInfo *p) = 0;
	virtual BOOL Deploy() = 0;
	virtual float GetMaxSpeed() = 0;
	virtual int iItemSlot() = 0;
	virtual void PrimaryAttack() = 0;
	virtual void SecondaryAttack() = 0;
	virtual void Reload() = 0;
	virtual void WeaponIdle() = 0;
	virtual BOOL UseDecrement() = 0;
	virtual BOOL IsPistol() = 0;
public:
	int m_iShell;
	unsigned short GetEventID() const { return m_usFireDeagle; }
private:
	unsigned short m_usFireDeagle;
};

class CFlashbang: public CBasePlayerWeapon {
public:
	virtual void Spawn() = 0;
	virtual void Precache() = 0;
	virtual int GetItemInfo(ItemInfo *p) = 0;
	virtual BOOL CanDeploy() = 0;
	virtual BOOL CanDrop() = 0;
	virtual BOOL Deploy() = 0;
	virtual void Holster(int skiplocal) = 0;
	virtual float GetMaxSpeed() = 0;
	virtual int iItemSlot() = 0;
	virtual void PrimaryAttack() = 0;
	virtual void SecondaryAttack() = 0;
	virtual void WeaponIdle() = 0;
	virtual BOOL UseDecrement() = 0;
	virtual BOOL IsPistol() = 0;
};

class CG3SG1: public CBasePlayerWeapon {
public:
	virtual void Spawn() = 0;
	virtual void Precache() = 0;
	virtual int GetItemInfo(ItemInfo *p) = 0;
	virtual BOOL Deploy() = 0;
	virtual float GetMaxSpeed() = 0;
	virtual int iItemSlot() = 0;
	virtual void PrimaryAttack() = 0;
	virtual void SecondaryAttack() = 0;
	virtual void Reload() = 0;
	virtual void WeaponIdle() = 0;
	virtual BOOL UseDecrement() = 0;
public:
	int m_iShell;
	unsigned short GetEventID() const { return m_usFireG3SG1; }
private:
	unsigned short m_usFireG3SG1;
};

class CGLOCK18: public CBasePlayerWeapon {
public:
	virtual void Spawn() = 0;
	virtual void Precache() = 0;
	virtual int GetItemInfo(ItemInfo *p) = 0;
	virtual BOOL Deploy() = 0;
	virtual float GetMaxSpeed() = 0;
	virtual int iItemSlot() = 0;
	virtual void PrimaryAttack() = 0;
	virtual void SecondaryAttack() = 0;
	virtual void Reload() = 0;
	virtual void WeaponIdle() = 0;
	virtual BOOL UseDecrement() = 0;
	virtual BOOL IsPistol() = 0;
public:
	int m_iShell;
	bool m_bBurstFire;
};

class CHEGrenade: public CBasePlayerWeapon {
public:
	virtual void Spawn() = 0;
	virtual void Precache() = 0;
	virtual int GetItemInfo(ItemInfo *p) = 0;
	virtual BOOL CanDeploy() = 0;
	virtual BOOL CanDrop() = 0;
	virtual BOOL Deploy() = 0;
	virtual void Holster(int skiplocal) = 0;
	virtual float GetMaxSpeed() = 0;
	virtual int iItemSlot() = 0;
	virtual void PrimaryAttack() = 0;
	virtual void SecondaryAttack() = 0;
	virtual void WeaponIdle() = 0;
	virtual BOOL UseDecrement() = 0;
public:
	unsigned short m_usCreateExplosion;
};

class CKnife: public CBasePlayerWeapon {
public:
	virtual void Spawn() = 0;
	virtual void Precache() = 0;
	virtual int GetItemInfo(ItemInfo *p) = 0;
	virtual BOOL CanDrop() = 0;
	virtual BOOL Deploy() = 0;
	virtual void Holster(int skiplocal) = 0;
	virtual float GetMaxSpeed() = 0;
	virtual int iItemSlot() = 0;
	virtual void PrimaryAttack() = 0;
	virtual void SecondaryAttack() = 0;
	virtual BOOL UseDecrement() = 0;
	virtual void WeaponIdle() = 0;
public:
	TraceResult m_trHit;
	unsigned short m_usKnife;
};

class CM249: public CBasePlayerWeapon {
public:
	virtual void Spawn() = 0;
	virtual void Precache() = 0;
	virtual int GetItemInfo(ItemInfo *p) = 0;
	virtual BOOL Deploy() = 0;
	virtual float GetMaxSpeed() = 0;
	virtual int iItemSlot() = 0;
	virtual void PrimaryAttack() = 0;
	virtual void Reload() = 0;
	virtual void WeaponIdle() = 0;
	virtual BOOL UseDecrement() = 0;
public:
	int m_iShell;
	int iShellOn;
	unsigned short GetEventID() const { return m_usFireM249; }
private:
	unsigned short m_usFireM249;
};

class CM3: public CBasePlayerWeapon {
public:
	virtual void Spawn() = 0;
	virtual void Precache() = 0;
	virtual int GetItemInfo(ItemInfo *p) = 0;
	virtual BOOL Deploy() = 0;
	virtual float GetMaxSpeed() = 0;
	virtual int iItemSlot() = 0;
	virtual void PrimaryAttack() = 0;
	virtual void Reload() = 0;
	virtual void WeaponIdle() = 0;
	virtual BOOL UseDecrement() = 0;
public:
	int m_iShell;
	float m_flPumpTime;
	unsigned short GetEventID() const { return m_usFireM3; }
private:
	unsigned short m_usFireM3;
};

class CM4A1: public CBasePlayerWeapon {
public:
	virtual void Spawn() = 0;
	virtual void Precache() = 0;
	virtual int GetItemInfo(ItemInfo *p) = 0;
	virtual BOOL Deploy() = 0;
	virtual float GetMaxSpeed() = 0;
	virtual int iItemSlot() = 0;
	virtual void PrimaryAttack() = 0;
	virtual void SecondaryAttack() = 0;
	virtual void Reload() = 0;
	virtual void WeaponIdle() = 0;
	virtual BOOL UseDecrement() = 0;
public:
	int m_iShell;
	int iShellOn;
	unsigned short GetEventID() const { return m_usFireM4A1; }
private:
	unsigned short m_usFireM4A1;
};

class CMAC10: public CBasePlayerWeapon {
public:
	virtual void Spawn() = 0;
	virtual void Precache() = 0;
	virtual int GetItemInfo(ItemInfo *p) = 0;
	virtual BOOL Deploy() = 0;
	virtual float GetMaxSpeed() = 0;
	virtual int iItemSlot() = 0;
	virtual void PrimaryAttack() = 0;
	virtual void Reload() = 0;
	virtual void WeaponIdle() = 0;
	virtual BOOL UseDecrement() = 0;
public:
	int m_iShell;
	int iShellOn;
	unsigned short GetEventID() const { return m_usFireMAC10; }
private:
	unsigned short m_usFireMAC10;
};

class CP228: public CBasePlayerWeapon {
public:
	virtual void Spawn() = 0;
	virtual void Precache() = 0;
	virtual int GetItemInfo(ItemInfo *p) = 0;
	virtual BOOL Deploy() = 0;
	virtual float GetMaxSpeed() = 0;
	virtual int iItemSlot() = 0;
	virtual void PrimaryAttack() = 0;
	virtual void SecondaryAttack() = 0;
	virtual void Reload() = 0;
	virtual void WeaponIdle() = 0;
	virtual BOOL UseDecrement() = 0;
	virtual BOOL IsPistol() = 0;
public:
	int m_iShell;
	unsigned short GetEventID() const { return m_usFireP228; }
private:
	unsigned short m_usFireP228;
};

class CP90: public CBasePlayerWeapon {
public:
	virtual void Spawn() = 0;
	virtual void Precache() = 0;
	virtual int GetItemInfo(ItemInfo *p) = 0;
	virtual BOOL Deploy() = 0;
	virtual float GetMaxSpeed() = 0;
	virtual int iItemSlot() = 0;
	virtual void PrimaryAttack() = 0;
	virtual void Reload() = 0;
	virtual void WeaponIdle() = 0;
	virtual BOOL UseDecrement() = 0;
public:
	int m_iShell;
	int iShellOn;
	unsigned short GetEventID() const { return m_usFireP90; }
private:
	unsigned short m_usFireP90;
};

class CSCOUT: public CBasePlayerWeapon {
public:
	virtual void Spawn() = 0;
	virtual void Precache() = 0;
	virtual int GetItemInfo(ItemInfo *p) = 0;
	virtual BOOL Deploy() = 0;
	virtual float GetMaxSpeed() = 0;
	virtual int iItemSlot() = 0;
	virtual void PrimaryAttack() = 0;
	virtual void SecondaryAttack() = 0;
	virtual void Reload() = 0;
	virtual void WeaponIdle() = 0;
	virtual BOOL UseDecrement() = 0;
public:
	int m_iShell;
	unsigned short GetEventID() const { return m_usFireScout; }
private:
	unsigned short m_usFireScout;
};

class CSmokeGrenade: public CBasePlayerWeapon {
public:
	virtual void Spawn() = 0;
	virtual void Precache() = 0;
	virtual int GetItemInfo(ItemInfo *p) = 0;
	virtual BOOL CanDeploy() = 0;
	virtual BOOL CanDrop() = 0;
	virtual BOOL Deploy() = 0;
	virtual void Holster(int skiplocal) = 0;
	virtual float GetMaxSpeed() = 0;
	virtual int iItemSlot() = 0;
	virtual void PrimaryAttack() = 0;
	virtual void SecondaryAttack() = 0;
	virtual void WeaponIdle() = 0;
	virtual BOOL UseDecrement() = 0;
public:
	unsigned short m_usCreateSmoke;
};

class CTMP: public CBasePlayerWeapon {
public:
	virtual void Spawn() = 0;
	virtual void Precache() = 0;
	virtual int GetItemInfo(ItemInfo *p) = 0;
	virtual BOOL Deploy() = 0;
	virtual float GetMaxSpeed() = 0;
	virtual int iItemSlot() = 0;
	virtual void PrimaryAttack() = 0;
	virtual void Reload() = 0;
	virtual void WeaponIdle() = 0;
	virtual BOOL UseDecrement() = 0;
public:
	int m_iShell;
	int iShellOn;
	unsigned short GetEventID() const { return m_usFireTMP; }
private:
	unsigned short m_usFireTMP;
};

class CXM1014: public CBasePlayerWeapon {
public:
	virtual void Spawn() = 0;
	virtual void Precache() = 0;
	virtual int GetItemInfo(ItemInfo *p) = 0;
	virtual BOOL Deploy() = 0;
	virtual float GetMaxSpeed() = 0;
	virtual int iItemSlot() = 0;
	virtual void PrimaryAttack() = 0;
	virtual void Reload() = 0;
	virtual void WeaponIdle() = 0;
	virtual BOOL UseDecrement() = 0;
public:
	int m_iShell;
	float m_flPumpTime;
	unsigned short GetEventID() const { return m_usFireXM1014; }
private:
	unsigned short m_usFireXM1014;
};

class CELITE: public CBasePlayerWeapon {
public:
	virtual void Spawn() = 0;
	virtual void Precache() = 0;
	virtual int GetItemInfo(ItemInfo *p) = 0;
	virtual BOOL Deploy() = 0;
	virtual float GetMaxSpeed() = 0;
	virtual int iItemSlot() = 0;
	virtual void PrimaryAttack() = 0;
	virtual void Reload() = 0;
	virtual void WeaponIdle() = 0;
	virtual BOOL UseDecrement() = 0;
	virtual BOOL IsPistol() = 0;
public:
	int m_iShell;
	unsigned short GetEventID_Left() const { return m_usFireELITE_LEFT; }
	unsigned short GetEventID_Right() const { return m_usFireELITE_RIGHT; }
private:
	unsigned short m_usFireELITE_LEFT;
	unsigned short m_usFireELITE_RIGHT;
};

class CFiveSeven: public CBasePlayerWeapon {
public:
	virtual void Spawn() = 0;
	virtual void Precache() = 0;
	virtual int GetItemInfo(ItemInfo *p) = 0;
	virtual BOOL Deploy() = 0;
	virtual float GetMaxSpeed() = 0;
	virtual int iItemSlot() = 0;
	virtual void PrimaryAttack() = 0;
	virtual void SecondaryAttack() = 0;
	virtual void Reload() = 0;
	virtual void WeaponIdle() = 0;
	virtual BOOL UseDecrement() = 0;
	virtual BOOL IsPistol() = 0;
public:
	int m_iShell;
	unsigned short GetEventID() const { return m_usFireFiveSeven; }
private:
	unsigned short m_usFireFiveSeven;
};

class CUMP45: public CBasePlayerWeapon {
public:
	virtual void Spawn() = 0;
	virtual void Precache() = 0;
	virtual int GetItemInfo(ItemInfo *p) = 0;
	virtual BOOL Deploy() = 0;
	virtual float GetMaxSpeed() = 0;
	virtual int iItemSlot() = 0;
	virtual void PrimaryAttack() = 0;
	virtual void Reload() = 0;
	virtual void WeaponIdle() = 0;
	virtual BOOL UseDecrement() = 0;
public:
	int m_iShell;
	int iShellOn;
	unsigned short GetEventID() const { return m_usFireUMP45; }
private:
	unsigned short m_usFireUMP45;
};

class CSG550: public CBasePlayerWeapon {
public:
	virtual void Spawn() = 0;
	virtual void Precache() = 0;
	virtual int GetItemInfo(ItemInfo *p) = 0;
	virtual BOOL Deploy() = 0;
	virtual float GetMaxSpeed() = 0;
	virtual int iItemSlot() = 0;
	virtual void PrimaryAttack() = 0;
	virtual void SecondaryAttack() = 0;
	virtual void Reload() = 0;
	virtual void WeaponIdle() = 0;
	virtual BOOL UseDecrement() = 0;
public:
	int m_iShell;
	unsigned short GetEventID() const { return m_usFireSG550; }
private:
	unsigned short m_usFireSG550;
};

class CGalil: public CBasePlayerWeapon {
public:
	virtual void Spawn() = 0;
	virtual void Precache() = 0;
	virtual int GetItemInfo(ItemInfo *p) = 0;
	virtual BOOL Deploy() = 0;
	virtual float GetMaxSpeed() = 0;
	virtual int iItemSlot() = 0;
	virtual void PrimaryAttack() = 0;
	virtual void SecondaryAttack() = 0;
	virtual void Reload() = 0;
	virtual void WeaponIdle() = 0;
	virtual BOOL UseDecrement() = 0;
public:
	int m_iShell;
	int iShellOn;
	unsigned short GetEventID() const { return m_usFireGalil; }
private:
	unsigned short m_usFireGalil;
};

class CFamas: public CBasePlayerWeapon {
public:
	virtual void Spawn() = 0;
	virtual void Precache() = 0;
	virtual int GetItemInfo(ItemInfo *p) = 0;
	virtual BOOL Deploy() = 0;
	virtual float GetMaxSpeed() = 0;
	virtual int iItemSlot() = 0;
	virtual void PrimaryAttack() = 0;
	virtual void SecondaryAttack() = 0;
	virtual void Reload() = 0;
	virtual void WeaponIdle() = 0;
	virtual BOOL UseDecrement() = 0;
public:
	int m_iShell;
	int iShellOn;
};

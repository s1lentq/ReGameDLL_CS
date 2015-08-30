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

#ifndef CBASE_H
#define CBASE_H
#ifdef _WIN32
#pragma once
#endif

#include "monsterevent.h"

#include <utlvector.h>

#undef CREATE_NAMED_ENTITY
#undef REMOVE_ENTITY

//#define CAREER_MODE_DELETED_SCENE 1	// ??
#define CAREER_MODE_CAMPAIGN 2

#define FCAP_CUSTOMSAVE			0x00000001
#define FCAP_ACROSS_TRANSITION		0x00000002
#define FCAP_MUST_SPAWN			0x00000004
#define FCAP_DONT_SAVE			0x80000000
#define FCAP_IMPULSE_USE		0x00000008
#define FCAP_CONTINUOUS_USE		0x00000010
#define FCAP_ONOFF_USE			0x00000020
#define FCAP_DIRECTIONAL_USE		0x00000040
#define FCAP_MASTER			0x00000080
#define FCAP_FORCE_TRANSITION		0x00000080

#define SetThink(a)\
	m_pfnThink = static_cast<void (CBaseEntity::*)(void)>(a)
#define SetTouch(a)\
	m_pfnTouch = static_cast<void (CBaseEntity::*)(CBaseEntity *)>(a)
#define SetUse(a)\
	m_pfnUse = static_cast<void (CBaseEntity::*)(CBaseEntity *, CBaseEntity *, USE_TYPE, float)>(a)
#define SetBlocked(a)\
	m_pfnBlocked = static_cast<void (CBaseEntity::*)(CBaseEntity *)>(a)

#define SetMoveDone(a)\
	m_pfnCallWhenMoveDone = static_cast<void (CBaseToggle::*)(void)>(a)

#define CLASS_NONE		0
#define CLASS_MACHINE		1
#define CLASS_PLAYER		2
#define CLASS_HUMAN_PASSIVE	3
#define CLASS_HUMAN_MILITARY	4
#define CLASS_ALIEN_MILITARY	5
#define CLASS_ALIEN_PASSIVE	6
#define CLASS_ALIEN_MONSTER	7
#define CLASS_ALIEN_PREY	8
#define CLASS_ALIEN_PREDATOR	9
#define CLASS_INSECT		10
#define CLASS_PLAYER_ALLY	11
#define CLASS_PLAYER_BIOWEAPON	12
#define CLASS_ALIEN_BIOWEAPON	13
#define CLASS_VEHICLE		14
#define CLASS_BARNACLE		99

#define GIB_HEALTH_VALUE	-30

#define ROUTE_SIZE		8
#define MAX_OLD_ENEMIES		4

#define bits_CAP_DUCK		(1<<0)
#define bits_CAP_JUMP		(1<<1)
#define bits_CAP_STRAFE		(1<<2)
#define bits_CAP_SQUAD		(1<<3)
#define bits_CAP_SWIM		(1<<4)
#define bits_CAP_CLIMB		(1<<5)
#define bits_CAP_USE		(1<<6)
#define bits_CAP_HEAR		(1<<7)
#define bits_CAP_AUTO_DOORS	(1<<8)
#define bits_CAP_OPEN_DOORS	(1<<9)
#define bits_CAP_TURN_HEAD	(1<<10)
#define bits_CAP_RANGE_ATTACK1	(1<<11)
#define bits_CAP_RANGE_ATTACK2	(1<<12)
#define bits_CAP_MELEE_ATTACK1	(1<<13)
#define bits_CAP_MELEE_ATTACK2	(1<<14)
#define bits_CAP_FLY		(1<<15)
#define bits_CAP_DOORS_GROUP	(bits_CAP_USE | bits_CAP_AUTO_DOORS | bits_CAP_OPEN_DOORS)

#define DMG_GENERIC		0
#define DMG_CRUSH		(1<<0)
#define DMG_BULLET		(1<<1)
#define DMG_SLASH		(1<<2)
#define DMG_BURN		(1<<3)
#define DMG_FREEZE		(1<<4)
#define DMG_FALL		(1<<5)
#define DMG_BLAST		(1<<6)
#define DMG_CLUB		(1<<7)
#define DMG_SHOCK		(1<<8)
#define DMG_SONIC		(1<<9)
#define DMG_ENERGYBEAM		(1<<10)
#define DMG_NEVERGIB		(1<<12)
#define DMG_ALWAYSGIB		(1<<13)
#define DMG_DROWN		(1<<14)
#define DMG_TIMEBASED		(~(0x3FFF))

#define DMG_PARALYZE		(1<<15)
#define DMG_NERVEGAS		(1<<16)
#define DMG_POISON		(1<<17)
#define DMG_RADIATION		(1<<18)
#define DMG_DROWNRECOVER	(1<<19)
#define DMG_ACID		(1<<20)
#define DMG_SLOWBURN		(1<<21)
#define DMG_SLOWFREEZE		(1<<22)
#define DMG_MORTAR		(1<<23)
#define DMG_EXPLOSION		(1<<24)
#define DMG_GIB_CORPSE		(DMG_CRUSH | DMG_FALL | DMG_BLAST | DMG_SONIC | DMG_CLUB)
#define DMG_SHOWNHUD		(DMG_POISON | DMG_ACID | DMG_FREEZE | DMG_SLOWFREEZE | DMG_DROWN | DMG_BURN | DMG_SLOWBURN | DMG_NERVEGAS | DMG_RADIATION | DMG_SHOCK)

#define SF_NORESPAWN		(1 << 30)

#define AIRTIME			12	// lung full of air lasts this many seconds
#define PARALYZE_DURATION	2	// number of 2 second intervals to take damage
#define PARALYZE_DAMAGE		1.0f	// damage to take each 2 second interval

#define NERVEGAS_DURATION	2
#define NERVEGAS_DAMAGE		5.0f

#define POISON_DURATION		5
#define POISON_DAMAGE		2.0f

#define RADIATION_DURATION	2
#define RADIATION_DAMAGE	1.0f

#define ACID_DURATION		2
#define ACID_DAMAGE		5.0f

#define SLOWBURN_DURATION	2
#define SLOWBURN_DAMAGE		1.0f

#define SLOWFREEZE_DURATION	2
#define SLOWFREEZE_DAMAGE	1.0f

#define itbd_Paralyze		0
#define itbd_NerveGas		1
#define itbd_Poison		2
#define itbd_Radiation		3
#define itbd_DrownRecover	4
#define itbd_Acid		5
#define itbd_SlowBurn		6
#define itbd_SlowFreeze		7
#define CDMG_TIMEBASED		8

#define GIB_NORMAL		0
#define GIB_NEVER		1
#define GIB_ALWAYS		2

#define SF_ITEM_USE_ONLY	256

#define MAX_MULTI_TARGETS	16
#define MS_MAX_TARGETS		32

#ifdef _WIN32
	#define C_EXPORT _declspec(dllexport)
#else
	#define C_EXPORT
#endif

typedef enum
{
	CLASSNAME

} hash_types_e;

typedef struct hash_item_s
{
	entvars_t *pev;
	struct hash_item_s *next;
	struct hash_item_s *lastHash;
	int pevIndex;

} hash_item_t;
/* size: 16, cachelines: 1, members: 4 */

typedef struct locksounds
{
	string_t sLockedSound;
	string_t sLockedSentence;
	string_t sUnlockedSound;
	string_t sUnlockedSentence;
	int iLockedSentence;
	int iUnlockedSentence;
	float flwaitSound;
	float flwaitSentence;
	BYTE bEOFLocked;
	BYTE bEOFUnlocked;

} locksound_t;
/* size: 36, cachelines: 1, members: 10 */

typedef enum
{
	USE_OFF,
	USE_ON,
	USE_SET,
	USE_TOGGLE,
} USE_TYPE;

typedef enum
{
	TRAIN_SAFE,
	TRAIN_BLOCKING,
	TRAIN_FOLLOWING

} TRAIN_CODE;

typedef enum
{
	TS_AT_TOP,
	TS_AT_BOTTOM,
	TS_GOING_UP,
	TS_GOING_DOWN,

} TOGGLE_STATE;

class CGrenade;
class CBaseEntity;
class CBaseMonster;
class CBasePlayerItem;
class CBasePlayerWeapon;
class CSquadMonster;

class CCineMonster;
class CSound;

#ifdef HOOK_GAMEDLL

#define stringsHashTable (*pstringsHashTable)
#define hashItemMemPool (*phashItemMemPool)
#define gTouchDisabled (*pgTouchDisabled)

#define gFunctionTable (*pgFunctionTable)
#define gNewDLLFunctions (*pgNewDLLFunctions)

#define grgszTextureName (*pgrgszTextureName)
#define grgchTextureType (*pgrgchTextureType)
#define fTextureTypeInit (*pfTextureTypeInit)
#define gcTextures (*pgcTextures)

#endif // HOOK_GAMEDLL

extern CMemoryPool hashItemMemPool;
extern BOOL gTouchDisabled;

extern DLL_FUNCTIONS gFunctionTable;
extern NEW_DLL_FUNCTIONS gNewDLLFunctions;

extern char grgszTextureName[ CTEXTURESMAX ][ CBTEXTURENAMEMAX ];
extern char grgchTextureType[ CTEXTURESMAX ];
extern int fTextureTypeInit;
extern int gcTextures;

extern CUtlVector< hash_item_t > stringsHashTable;

class EHANDLE
{
public:
	edict_t *Get(void);
	edict_t *Set(edict_t *pent);

	operator int();
	operator CBaseEntity*();

	CBaseEntity *operator=(CBaseEntity *pEntity);
	CBaseEntity *operator->();

private:
	edict_t *m_pent;
	int m_serialnumber;

};/* size: 8, cachelines: 1, members: 2 */

typedef struct dynpitchvol
{
	int preset;
	int pitchrun;
	int pitchstart;
	int spinup;
	int spindown;
	int volrun;
	int volstart;
	int fadein;
	int fadeout;
	int lfotype;
	int lforate;
	int lfomodpitch;
	int lfomodvol;
	int cspinup;
	int cspincount;
	int pitch;
	int spinupsav;
	int spindownsav;
	int pitchfrac;
	int vol;
	int fadeinsav;
	int fadeoutsav;
	int volfrac;
	int lfofrac;
	int lfomult;

} dynpitchvol_t;
/* size: 100, cachelines: 2, members: 25 */

/* <48e9c1> ../cstrike/dlls/cbase.h:166 */
class CBaseEntity
{
public:
	virtual void Spawn(void) {}
	virtual void Precache(void) {}
	virtual void Restart(void) {}
	virtual void KeyValue(KeyValueData *pkvd)
	{
		pkvd->fHandled = FALSE;
	}
	NOBODY virtual int Save(CSave &save);
	NOBODY virtual int Restore(CRestore &restore);
	virtual int ObjectCaps(void)
	{
		return FCAP_ACROSS_TRANSITION;
	}
	virtual void Activate(void) {}
	virtual void SetObjectCollisionBox(void);
	virtual int Classify(void)
	{
		return CLASS_NONE;
	}
	virtual void DeathNotice(entvars_t *pevChild)
	{
		return DeathNotice_(pevChild);
	}
	virtual void TraceAttack(entvars_t *pevAttacker, float flDamage, Vector vecDir, TraceResult *ptr, int bitsDamageType);
	virtual int TakeDamage(entvars_t *pevInflictor, entvars_t *pevAttacker, float flDamage, int bitsDamageType);
	virtual int TakeHealth(float flHealth, int bitsDamageType);
	virtual void Killed(entvars_t *pevAttacker, int iGib);
	virtual int BloodColor(void)
	{
		return DONT_BLEED;
	}
	virtual void TraceBleed(float flDamage, Vector vecDir, TraceResult *ptr, int bitsDamageType);
	virtual BOOL IsTriggered(CBaseEntity *pActivator)
	{
		return TRUE;
	}
	virtual CBaseMonster *MyMonsterPointer(void)
	{
		return NULL;
	}
	virtual CSquadMonster *MySquadMonsterPointer(void)
	{
		return NULL;
	}
	virtual int GetToggleState(void)
	{
		return GetToggleState_();
	}
	virtual void AddPoints(int score, BOOL bAllowNegativeScore) {}		// __stdcall
	virtual void AddPointsToTeam(int score, BOOL bAllowNegativeScore) {}	// __stdcall
	virtual BOOL AddPlayerItem(CBasePlayerItem *pItem)
	{
		return FALSE;
	}
	virtual BOOL RemovePlayerItem(CBasePlayerItem *pItem)			// __stdcall
	{
		return FALSE;
	}
	virtual int GiveAmmo(int iAmount, char *szName, int iMax)		// __stdcall
	{
		return -1;
	}
	virtual float GetDelay(void)
	{
		return GetDelay_();
	}
	virtual int IsMoving(void)
	{
		return (pev->velocity != g_vecZero);
	}
	virtual void OverrideReset(void) {}
	virtual int DamageDecal(int bitsDamageType);
	virtual void SetToggleState(int state) {}
	virtual void StartSneaking(void) {}
	virtual void StopSneaking(void) {}
	virtual BOOL OnControls(entvars_t *onpev)
	{
		return FALSE;
	}
	virtual BOOL IsSneaking(void)
	{
		return FALSE;
	}
	virtual BOOL IsAlive(void)
	{
		return (pev->deadflag == DEAD_NO && pev->health > 0.0f);
	}
	virtual BOOL IsBSPModel(void)
	{
		return (pev->solid == SOLID_BSP || pev->movetype == MOVETYPE_PUSHSTEP);
	}
	virtual BOOL ReflectGauss(void)
	{
		return (IsBSPModel() && pev->takedamage == DAMAGE_NO);
	}
	virtual BOOL HasTarget(string_t targetname)
	{
		return FStrEq(STRING(targetname),STRING(pev->targetname));
	}
	virtual BOOL IsInWorld(void);
	virtual BOOL IsPlayer(void)
	{
		return FALSE;
	}
	virtual BOOL IsNetClient(void)
	{
		return FALSE;
	}
	virtual const char *TeamID(void)
	{
		return "";
	}
	virtual CBaseEntity *GetNextTarget(void);
	virtual void Think(void)
	{
		if (m_pfnThink)
			(this->*m_pfnThink)();
	}
	virtual void Touch(CBaseEntity *pOther)
	{
		if (m_pfnTouch)
			(this->*m_pfnTouch)(pOther);
	}
	virtual void Use(CBaseEntity *pActivator, CBaseEntity *pCaller, USE_TYPE useType = USE_OFF, float value = 0.0f)
	{
		if (m_pfnUse)
			(this->*m_pfnUse)(pActivator, pCaller, useType, value);
	}
	virtual void Blocked(CBaseEntity *pOther)
	{
		if (m_pfnBlocked)
			(this->*m_pfnBlocked)(pOther);
	}
	virtual CBaseEntity *Respawn(void)
	{
		return NULL;
	}
	virtual void UpdateOwner(void) {}
	virtual BOOL FBecomeProne(void)
	{
		return FALSE;
	}
	virtual Vector Center(void)
	{
		return (pev->absmax + pev->absmin) * 0.5f;
	}
	virtual Vector EyePosition(void)
	{
		return (pev->origin + pev->view_ofs);
	}
	virtual Vector EarPosition(void)
	{
		return (pev->origin + pev->view_ofs);
	}
	virtual Vector BodyTarget(const Vector &posSrc)
	{
		return BodyTarget_(posSrc);
	}
	virtual int Illumination(void)
	{
		return GETENTITYILLUM(ENT(pev));
	}

	NOBODY virtual BOOL FVisible(CBaseEntity *pEntity);
	NOBODY virtual BOOL FVisible(Vector &vecOrigin);

#ifdef HOOK_GAMEDLL

	int Save_(CSave &save);
	int Restore_(CRestore &restore);
	void SetObjectCollisionBox_(void);
	void DeathNotice_(entvars_t *pevChild) { }
	void TraceAttack_(entvars_t *pevAttacker, float flDamage, Vector vecDir, TraceResult *ptr, int bitsDamageType);
	int TakeDamage_(entvars_t *pevInflictor, entvars_t *pevAttacker, float flDamage, int bitsDamageType);
	int TakeHealth_(float flHealth, int bitsDamageType);
	void Killed_(entvars_t *pevAttacker, int iGib);
	void TraceBleed_(float flDamage, Vector vecDir, TraceResult *ptr, int bitsDamageType);
	int GetToggleState_(void)
	{
		return TS_AT_TOP;
	}
	float GetDelay_(void)
	{
		return 0.0f;
	}
	int DamageDecal_(int bitsDamageType);
	BOOL IsInWorld_(void);
	CBaseEntity *GetNextTarget_(void);
	Vector BodyTarget_(const Vector &posSrc)
	{
		return Center();
	}
	BOOL FVisible_(CBaseEntity *pEntity);
	BOOL FVisible_(Vector &vecOrigin);

#endif // HOOK_GAMEDLL

public:
	void *operator new(size_t stAllocateBlock, entvars_t *pevnew)
	{
		return ALLOC_PRIVATE(ENT(pevnew), stAllocateBlock);
	}
	void operator delete(void *pMem, entvars_t *pev)
	{
		pev->flags |= FL_KILLME;
	}
	void UpdateOnRemove(void);
	void EXPORT SUB_Remove(void);
	void EXPORT SUB_DoNothing(void);
	void EXPORT SUB_StartFadeOut(void);
	void EXPORT SUB_FadeOut(void);
	void EXPORT SUB_CallUseToggle(void)
	{
		Use(this, this, USE_TOGGLE, 0);
	}
	NOBODY int ShouldToggle(USE_TYPE useType, BOOL currentState);
	NOBODY void FireBullets(ULONG cShots, Vector vecSrc, Vector vecDirShooting, Vector vecSpread, float flDistance, int iBulletType, int iTracerFreq = 4, int iDamage = 0, entvars_t *pevAttacker = NULL);
	Vector FireBullets3(Vector vecSrc, Vector vecDirShooting, float vecSpread, float flDistance, int iPenetration, int iBulletType, int iDamage, float flRangeModifier, entvars_t *pevAttacker, bool bPistol, int shared_rand = 0);
	void SUB_UseTargets(CBaseEntity *pActivator, USE_TYPE useType, float value);
	int Intersects(CBaseEntity *pOther);
	void MakeDormant(void);
	int IsDormant(void);
	BOOL IsLockedByMaster(void)
	{
		return FALSE;
	}
public:
	static CBaseEntity *Instance(edict_t *pent)
	{
		return (CBaseEntity *)GET_PRIVATE(pent ? pent : ENT(0));
	}
	static CBaseEntity *Instance(entvars_t *pev)
	{
		return Instance(ENT(pev));
	}
	static CBaseEntity *Instance(int offset)
	{
		return Instance(ENT(offset));
	}
	CBaseMonster *GetMonsterPointer(entvars_t *pevMonster)
	{
		CBaseEntity *pEntity = Instance(pevMonster);
		if (pEntity != NULL)
		{
			return pEntity->MyMonsterPointer();
		}
		return NULL;
	}
	CBaseMonster *GetMonsterPointer(edict_t *pentMonster)
	{
		CBaseEntity *pEntity = Instance(pentMonster);
		if (pEntity)
			return pEntity->MyMonsterPointer();
		return NULL;
	}
	static CBaseEntity *Create(char *szName, const Vector &vecOrigin, const Vector &vecAngles, edict_t *pentOwner = NULL);
	edict_t *edict(void)
	{
		return ENT(pev);
	}
	EOFFSET eoffset(void)
	{
		return OFFSET(pev);
	}
	int entindex(void)
	{
		return ENTINDEX(edict());
	}
public:
	entvars_t *pev;
	CBaseEntity *m_pGoalEnt;
	CBaseEntity *m_pLink;

	static TYPEDESCRIPTION IMPLEMENT_ARRAY(m_SaveData)[5];

	void (CBaseEntity::*m_pfnThink)(void);
	//int m_pfnThink_Flag;

	void (CBaseEntity::*m_pfnTouch)(CBaseEntity *pOther);
	//int m_pfnTouch_Flag;

	void (CBaseEntity::*m_pfnUse)(CBaseEntity *pActivator, CBaseEntity *pCaller, USE_TYPE useType, float value);
	//int m_pfnUse_Flag;

	void (CBaseEntity::*m_pfnBlocked)(CBaseEntity *pOther);
	//int m_pfnBlocked_Flag;

	int *current_ammo;
	float currentammo;
	int maxammo_buckshot;
	int ammo_buckshot;
	int maxammo_9mm;
	int ammo_9mm;
	int maxammo_556nato;
	int ammo_556nato;
	int maxammo_556natobox;
	int ammo_556natobox;
	int maxammo_762nato;
	int ammo_762nato;
	int maxammo_45acp;
	int ammo_45acp;
	int maxammo_50ae;
	int ammo_50ae;
	int maxammo_338mag;
	int ammo_338mag;
	int maxammo_57mm;
	int ammo_57mm;
	int maxammo_357sig;
	int ammo_357sig;
	float m_flStartThrow;
	float m_flReleaseThrow;
	int m_iSwing;
	bool has_disconnected;

};/* size: 152, cachelines: 3, members: 35 */

/* <48d2a5> ../cstrike/dlls/cbase.h:273 */
inline int FNullEnt(CBaseEntity *ent)
{
	return (ent == NULL || FNullEnt(ent->edict()));
}

/* <48d67d> ../cstrike/dlls/cbase.h:273 */
inline int FNullEnt(EHANDLE hent)
{
	return (hent == NULL || FNullEnt(OFFSET(hent.Get())));
}

/* <19e6b5> ../cstrike/dlls/cbase.h:450 */
class CPointEntity: public CBaseEntity
{
public:
	NOBODY virtual void Spawn(void);
	NOBODY virtual int ObjectCaps(void)
	{
		return ObjectCaps_();
	}

#ifdef HOOK_GAMEDLL

	void Spawn_(void);
	int ObjectCaps_(void)
	{
		return (CBaseEntity::ObjectCaps() & ~FCAP_ACROSS_TRANSITION);
	}

#endif // HOOK_GAMEDLL

};/* size: 152, cachelines: 3, members: 1 */

/* <249f0> ../cstrike/dlls/cbase.h:484 */
class CMultiSource: public CPointEntity
{
public:
	NOBODY virtual void Spawn(void);
	NOBODY virtual void KeyValue(KeyValueData *pkvd);
	NOBODY virtual void Use(CBaseEntity *pActivator, CBaseEntity *pCaller, USE_TYPE useType, float value);
	NOBODY virtual int ObjectCaps(void)
	{
		return ObjectCaps_();
	}
	NOBODY virtual BOOL IsTriggered(CBaseEntity *pActivator);
	NOBODY virtual int Save(CSave &save);
	NOBODY virtual int Restore(CRestore &restore);

#ifdef HOOK_GAMEDLL

	void Spawn_(void);
	void KeyValue_(KeyValueData *pkvd);
	void Use_(CBaseEntity *pActivator, CBaseEntity *pCaller, USE_TYPE useType, float value);
	int ObjectCaps_(void)
	{
		return (CPointEntity::ObjectCaps() | FCAP_MASTER);
	}
	BOOL IsTriggered_(CBaseEntity *pActivator);
	int Save_(CSave &save);
	int Restore_(CRestore &restore);

#endif // HOOK_GAMEDLL

public:
	NOBODY void EXPORT Register(void);

public:
	static TYPEDESCRIPTION IMPLEMENT_ARRAY(m_SaveData)[4];

	EHANDLE m_rgEntities[MS_MAX_TARGETS];
	int m_rgTriggered[MS_MAX_TARGETS];
	int m_iTotal;
	string_t m_globalstate;

};/* size: 544, cachelines: 9, members: 6 */

/* <48ea00> ../cstrike/dlls/cbase.h:509 */
class CBaseDelay: public CBaseEntity
{
public:
	virtual void KeyValue(KeyValueData *pkvd);
	NOBODY virtual int Save(CSave &save);
	NOBODY virtual int Restore(CRestore &restore);

#ifdef HOOK_GAMEDLL

	void KeyValue_(KeyValueData *pkvd);
	int Save_(CSave &save);
	int Restore_(CRestore &restore);

#endif // HOOK_GAMEDLL

public:
	void SUB_UseTargets(CBaseEntity *pActivator, USE_TYPE useType, float value);
	void EXPORT DelayThink(void);
public:
	static TYPEDESCRIPTION IMPLEMENT_ARRAY(m_SaveData)[2];

	float m_flDelay;
	int m_iszKillTarget;

};/* size: 160, cachelines: 3, members: 4 */

/* <48ea6f> ../cstrike/dlls/cbase.h:526 */
class CBaseAnimating: public CBaseDelay
{
public:
	NOBODY virtual int Save(CSave &save);
	NOBODY virtual int Restore(CRestore &restore);
	virtual void HandleAnimEvent(MonsterEvent_t *pEvent) {}

#ifdef HOOK_GAMEDLL

	int Save_(CSave &save);
	int Restore_(CRestore &restore);

#endif // HOOK_GAMEDLL

public:
	float StudioFrameAdvance(float flInterval = 0.0f);
	BOOL GetSequenceFlags(void);
	int LookupActivity(int activity);
	int LookupActivityHeaviest(int activity);
	int LookupSequence(const char *label);
	void ResetSequenceInfo(void);
	void DispatchAnimEvents(float flFutureInterval = 0.1f);
	float SetBoneController(int iController, float flValue);
	void InitBoneControllers(void);

	NOXREF float SetBlending(int iBlender, float flValue);
	NOXREF void GetBonePosition(int iBone, Vector &origin, Vector &angles);
	NOXREF void GetAutomovement(Vector &origin, Vector &angles, float flInterval = 0.1f);
	NOXREF int FindTransition(int iEndingSequence, int iGoalSequence, int *piDir);
	NOXREF void GetAttachment(int iAttachment, Vector &origin, Vector &angles);
	NOXREF void SetBodygroup(int iGroup, int iValue);
	NOXREF int GetBodygroup(int iGroup);

	int ExtractBbox(int sequence, float *mins, float *maxs);
	void SetSequenceBox(void);
public:
	static TYPEDESCRIPTION IMPLEMENT_ARRAY(m_SaveData)[5];

	float m_flFrameRate;
	float m_flGroundSpeed;
	float m_flLastEventCheck;
	BOOL m_fSequenceFinished;
	BOOL m_fSequenceLoops;

};/* size: 180, cachelines: 3, members: 7 */

/* <48eb06> ../cstrike/dlls/cbase.h:569 */
class CBaseToggle: public CBaseAnimating
{
public:
	virtual void KeyValue(KeyValueData *pkvd);
	virtual int Save(CSave &save);
	virtual int Restore(CRestore &restore);
	virtual int GetToggleState(void)
	{
		return m_toggle_state;
	}
	virtual float GetDelay(void)
	{
		return m_flWait;
	}
#ifdef HOOK_GAMEDLL

	void KeyValue_(KeyValueData *pkvd);
	int Save_(CSave &save);
	int Restore_(CRestore &restore);

#endif // HOOK_GAMEDLL
public:
	NOBODY void LinearMove(Vector vecDest, float flSpeed);
	NOBODY void EXPORT LinearMoveDone(void);
	NOBODY void AngularMove(Vector vecDestAngle, float flSpeed);
	NOBODY void EXPORT AngularMoveDone(void);
	NOBODY BOOL IsLockedByMaster(void);

public:
	NOBODY static float AxisValue(int flags, Vector &angles);
	NOBODY static void AxisDir(entvars_t *pev);
	NOBODY static float AxisDelta(int flags, Vector &angle1, Vector &angle2);

public:
	static TYPEDESCRIPTION IMPLEMENT_ARRAY(m_SaveData)[19];

	TOGGLE_STATE m_toggle_state;
	float m_flActivateFinished;
	float m_flMoveDistance;
	float m_flWait;
	float m_flLip;
	float m_flTWidth;
	float m_flTLength;
	Vector m_vecPosition1;
	Vector m_vecPosition2;
	Vector m_vecAngle1;
	Vector m_vecAngle2;
	int m_cTriggersLeft;
	float m_flHeight;
	EHANDLE m_hActivator;
	void (CBaseToggle::*m_pfnCallWhenMoveDone)(void);
	Vector m_vecFinalDest;
	Vector m_vecFinalAngle;
	int m_bitsDamageInflict;
	string_t m_sMaster;
};/* size: 312, cachelines: 5, members: 21 */

#include "basemonster.h"

/* <24b19> ../cstrike/dlls/cbase.h:745 */
class CBaseButton: public CBaseToggle
{
	enum BUTTON_CODE
	{
		BUTTON_NOTHING,
		BUTTON_ACTIVATE,
		BUTTON_RETURN
	};
public:

	NOBODY virtual void Spawn(void);
	NOBODY virtual void Precache(void);
	NOBODY virtual void KeyValue(KeyValueData *pkvd);
	NOBODY virtual int TakeDamage(entvars_t *pevInflictor, entvars_t *pevAttacker, float flDamage, int bitsDamageType);
	NOBODY virtual int Save(CSave &save);
	NOBODY virtual int Restore(CRestore &restore);
	virtual int ObjectCaps(void)
	{
		return ObjectCaps_();
	}

#ifdef HOOK_GAMEDLL

	void Spawn_(void);
	void Precache_(void);
	void KeyValue_(KeyValueData *pkvd);
	int TakeDamage_(entvars_t *pevInflictor, entvars_t *pevAttacker, float flDamage, int bitsDamageType);
	int Save_(CSave &save);
	int Restore_(CRestore &restore);
	int ObjectCaps_(void)
	{
		if (pev->takedamage == DAMAGE_NO)
			return FCAP_IMPULSE_USE;

		return (CBaseToggle::ObjectCaps() & ~FCAP_ACROSS_TRANSITION);
	}

#endif // HOOK_GAMEDLL

public:
	NOBODY void RotSpawn(void);
	NOBODY void ButtonActivate(void);
	NOBODY void SparkSoundCache(void);

	NOBODY void EXPORT ButtonShot(void);
	NOBODY void EXPORT ButtonTouch(CBaseEntity *pOther);
	NOBODY void EXPORT ButtonSpark(void);
	NOBODY void EXPORT TriggerAndWait(void);
	NOBODY void EXPORT ButtonReturn(void);
	NOBODY void EXPORT ButtonBackHome(void);
	NOBODY void EXPORT ButtonUse(CBaseEntity *pActivator, CBaseEntity *pCaller, USE_TYPE useType, float value);

	NOBODY BUTTON_CODE ButtonResponseToTouch(void);

public:
	static TYPEDESCRIPTION IMPLEMENT_ARRAY(m_SaveData)[8];

	BOOL m_fStayPushed;
	BOOL m_fRotating;
	string_t m_strChangeTarget;
	locksound_t m_ls;
	BYTE m_bLockedSound;
	BYTE m_bLockedSentence;
	BYTE m_bUnlockedSound;
	BYTE m_bUnlockedSentence;
	int m_sounds;
};/* size: 368, cachelines: 6, members: 11 */

/* <1da023> ../cstrike/dlls/cbase.h:861 */
class CWorld: public CBaseEntity
{
public:
	virtual void Spawn(void);
	virtual void Precache(void);
	virtual void KeyValue(KeyValueData *pkvd);

#ifdef HOOK_GAMEDLL

	void Spawn_(void);
	void Precache_(void);
	void KeyValue_(KeyValueData *pkvd);

#endif // HOOK_GAMEDLL

};/* size: 152, cachelines: 3, members: 1 */

/* <1d9f84> ../cstrike/dlls/world.cpp:111 */
class CDecal: public CBaseEntity
{
public:
	virtual void Spawn(void);
	virtual void KeyValue(KeyValueData *);

#ifdef HOOK_GAMEDLL

	void Spawn_(void);
	void KeyValue_(KeyValueData *);

#endif // HOOK_GAMEDLL

public:
	void EXPORT StaticDecal(void);
	void EXPORT TriggerDecal(CBaseEntity *pActivator, CBaseEntity *pCaller, USE_TYPE useType, float value);

};/* size: 152, cachelines: 3, members: 1 */

// Body queue class here.... It's really just CBaseEntity

/* <1d9fd1> ../cstrike/dlls/world.cpp:207 */
class CCorpse: public CBaseEntity
{
public:
	/* <1dabe0> ../cstrike/dlls/world.cpp:209 */
	virtual int ObjectCaps(void)
	{
		ObjectCaps_();
	}

#ifdef HOOK_GAMEDLL

	int ObjectCaps_(void)
	{
		return FCAP_DONT_SAVE;
	}

#endif // HOOK_GAMEDLL

};/* size: 152, cachelines: 3, members: 1 */

/* <170b59> ../cstrike/dlls/sound.cpp:117 */
class CAmbientGeneric: public CBaseEntity
{
public:
	NOBODY virtual void Spawn(void);
	NOBODY virtual void Precache(void);
	NOBODY virtual void Restart(void);
	NOBODY virtual void KeyValue(KeyValueData *pkvd);
	NOBODY virtual int Save(CSave &save);
	NOBODY virtual int Restore(CRestore &restore);
	virtual int ObjectCaps(void)
	{
		return (CBaseEntity::ObjectCaps() & ~FCAP_ACROSS_TRANSITION);
	}

#ifdef HOOK_GAMEDLL

	int Save_(CSave &save);
	int Restore_(CRestore &restore);

#endif // HOOK_GAMEDLL

public:
	NOBODY void EXPORT ToggleUse(CBaseEntity *pActivator, CBaseEntity *pCaller, USE_TYPE useType, float value);
	NOBODY void EXPORT RampThink(void);
	NOBODY void InitModulationParms(void);

public:
	static TYPEDESCRIPTION IMPLEMENT_ARRAY(m_SaveData)[4];

	float m_flAttenuation;
	dynpitchvol_t m_dpv;
	BOOL m_fActive;
	BOOL m_fLooping;

};/* size: 264, cachelines: 5, members: 6 */

/* <170bc2> ../cstrike/dlls/sound.cpp:875 */
class CEnvSound: public CPointEntity
{
public:
	NOBODY virtual void Spawn(void);
	NOBODY virtual void KeyValue(KeyValueData *pkvd);
	NOBODY virtual int Save(CSave &save);
	NOBODY virtual int Restore(CRestore &restore);
	NOBODY virtual void Think(void);

#ifdef HOOK_GAMEDLL

	int Save_(CSave &save);
	int Restore_(CRestore &restore);

#endif // HOOK_GAMEDLL

public:
	static TYPEDESCRIPTION IMPLEMENT_ARRAY(m_SaveData)[2];

	float m_flRadius;
	float m_flRoomtype;
};/* size: 160, cachelines: 3, members: 4 */

/* <170ced> ../cstrike/dlls/sound.cpp:1867 */
class CSpeaker: public CBaseEntity
{
public:
	NOBODY virtual void Spawn(void);
	NOBODY virtual void Precache(void);
	NOBODY virtual void KeyValue(KeyValueData *pkvd);
	NOBODY virtual int Save(CSave &save);
	NOBODY virtual int Restore(CRestore &restore);
	virtual int ObjectCaps(void)
	{
		return (CBaseEntity::ObjectCaps() & ~FCAP_ACROSS_TRANSITION);
	}

#ifdef HOOK_GAMEDLL

	int Save_(CSave &save);
	int Restore_(CRestore &restore);

#endif // HOOK_GAMEDLL

public:
	NOBODY void EXPORT ToggleUse(CBaseEntity *pActivator, CBaseEntity *pCaller, USE_TYPE useType, float value);
	NOBODY void EXPORT SpeakerThink(void);
public:
	static TYPEDESCRIPTION IMPLEMENT_ARRAY(m_SaveData)[1];

	int m_preset;

};/* size: 156, cachelines: 3, members: 3 */

template <class T>
T *GetClassPtr(T *a)
{
	entvars_t *pev = (entvars_t *)a;
	if (!pev)
		pev = VARS(CREATE_ENTITY());
	a = (T *)GET_PRIVATE(ENT(pev));
	if (!a)
	{
		a = new(pev) T;
		a->pev = pev;

#if defined(_WIN32) && !defined(REGAMEDLL_UNIT_TESTS)
		VirtualTableInit((void *)a, stripClass(typeid(T).name()));
#endif // _WIN32 && HOOK_GAMEDLL

	}
	return a;
}

int CaseInsensitiveHash(const char *string, int iBounds);
void EmptyEntityHashTable(void);
void AddEntityHashValue(entvars_t *pev, const char *value, hash_types_e fieldType);
void RemoveEntityHashValue(entvars_t *pev, const char *value, hash_types_e fieldType);
void printEntities(void);
edict_t *CREATE_NAMED_ENTITY(string_t iClass);
void REMOVE_ENTITY(edict_t *e);
void CONSOLE_ECHO_(char *pszMsg, ...);
void loopPerformance(void);

extern "C" C_EXPORT int GetEntityAPI(DLL_FUNCTIONS *pFunctionTable, int interfaceVersion);
NOXREF extern "C" C_EXPORT int GetEntityAPI2(DLL_FUNCTIONS *pFunctionTable, int *interfaceVersion);
extern "C" C_EXPORT int GetNewDLLFunctions(NEW_DLL_FUNCTIONS *pFunctionTable, int *interfaceVersion);

int DispatchSpawn(edict_t *pent);
void DispatchKeyValue(edict_t *pentKeyvalue, KeyValueData *pkvd);
void DispatchTouch(edict_t *pentTouched, edict_t *pentOther);
void DispatchUse(edict_t *pentUsed, edict_t *pentOther);
void DispatchThink(edict_t *pent);
void DispatchBlocked(edict_t *pentBlocked, edict_t *pentOther);
void DispatchSave(edict_t *pent, SAVERESTOREDATA *pSaveData);
int DispatchRestore(edict_t *pent, SAVERESTOREDATA *pSaveData, int globalEntity);
CBaseEntity *FindGlobalEntity(string_t classname, string_t globalname);
void DispatchObjectCollsionBox(edict_t *pent);
void SaveWriteFields(SAVERESTOREDATA *pSaveData, const char *pname, void *pBaseData, TYPEDESCRIPTION *pFields, int fieldCount);
void SaveReadFields(SAVERESTOREDATA *pSaveData, const char *pname, void *pBaseData, TYPEDESCRIPTION *pFields, int fieldCount);
void SetObjectCollisionBox(entvars_t *pev);
void OnFreeEntPrivateData(edict_t *pEnt);

#ifdef HOOK_GAMEDLL

typedef BOOL (CBaseEntity::*FVISIBLE_ENTITY)(CBaseEntity *);
typedef BOOL (CBaseEntity::*FVISIBLE_VECTOR)(Vector &);

typedef void (CGrenade::*EXPLODE_VECTOR)(Vector, Vector);
typedef void (CGrenade::*EXPLODE_TRACERESULT)(TraceResult *, int);

typedef CBaseEntity *(CBaseEntity::*CBASE_ISTANCE_EDICT)(edict_t *);
typedef CBaseEntity *(CBaseEntity::*CBASE_ISTANCE_ENTVARS)(entvars_t *);
typedef CBaseEntity *(CBaseEntity::*CBASE_ISTANCE_INT)(int);

#endif // HOOK_GAMEDLL

//Refs
extern void (*pCGib__SpawnHeadGib)(void);

#endif // CBASE_H

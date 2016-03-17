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

#include "saverestore.h"
#include "schedule.h"
#include "monsterevent.h"

#undef CREATE_NAMED_ENTITY
#undef REMOVE_ENTITY

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
	m_pfnThink = static_cast<void (CBaseEntity::*)()>(a)
#define SetTouch(a)\
	m_pfnTouch = static_cast<void (CBaseEntity::*)(CBaseEntity *)>(a)
#define SetUse(a)\
	m_pfnUse = static_cast<void (CBaseEntity::*)(CBaseEntity *, CBaseEntity *, USE_TYPE, float)>(a)
#define SetBlocked(a)\
	m_pfnBlocked = static_cast<void (CBaseEntity::*)(CBaseEntity *)>(a)

#define SetMoveDone(a)\
	m_pfnCallWhenMoveDone = static_cast<void (CBaseToggle::*)()>(a)

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
	#define EXPORT __declspec(dllexport)
#else
	#define EXPORT /**/
#endif // _WIN32

enum hash_types_e { CLASSNAME };

typedef struct hash_item_s
{
	entvars_t *pev;
	struct hash_item_s *next;
	struct hash_item_s *lastHash;
	int pevIndex;

} hash_item_t;

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

class CGrenade;
class CBaseEntity;
class CBaseMonster;
class CBasePlayerItem;
class CBasePlayerWeapon;
class CSquadMonster;

class CCineMonster;
class CSound;

class EHANDLE
{
public:
	edict_t *Get();
	edict_t *Set(edict_t *pent);

	operator int();
	operator CBaseEntity*();
	operator CBasePlayer*() { return static_cast<CBasePlayer *>(GET_PRIVATE(Get())); }

	CBaseEntity *operator=(CBaseEntity *pEntity);
	CBaseEntity *operator->();

private:
	edict_t *m_pent;
	int m_serialnumber;
};

class CBaseEntity
{
public:
	virtual void Spawn() {}
	virtual void Precache() {}
	virtual void Restart() {}
	virtual void KeyValue(KeyValueData *pkvd) { pkvd->fHandled = FALSE; }
	virtual int Save(CSave &save);
	virtual int Restore(CRestore &restore);
	virtual int ObjectCaps() { return FCAP_ACROSS_TRANSITION; }
	virtual void Activate() {}
	virtual void SetObjectCollisionBox();
	virtual int Classify() { return CLASS_NONE; }
	virtual void DeathNotice(entvars_t *pevChild) {}
	virtual void TraceAttack(entvars_t *pevAttacker, float flDamage, Vector vecDir, TraceResult *ptr, int bitsDamageType);
	virtual int TakeDamage(entvars_t *pevInflictor, entvars_t *pevAttacker, float flDamage, int bitsDamageType);
	virtual int TakeHealth(float flHealth, int bitsDamageType);
	virtual void Killed(entvars_t *pevAttacker, int iGib);
	virtual int BloodColor() { return DONT_BLEED; }
	virtual void TraceBleed(float flDamage, Vector vecDir, TraceResult *ptr, int bitsDamageType);
	virtual BOOL IsTriggered(CBaseEntity *pActivator) { return TRUE; }
	virtual CBaseMonster *MyMonsterPointer() { return NULL; }
	virtual CSquadMonster *MySquadMonsterPointer() { return NULL; }
	virtual int GetToggleState() { return TS_AT_TOP; }
	virtual void AddPoints(int score, BOOL bAllowNegativeScore) {}
	virtual void AddPointsToTeam(int score, BOOL bAllowNegativeScore) {}
	virtual BOOL AddPlayerItem(CBasePlayerItem *pItem) { return FALSE; }
	virtual BOOL RemovePlayerItem(CBasePlayerItem *pItem) { return FALSE; }
	virtual int GiveAmmo(int iAmount, char *szName, int iMax) { return -1; }
	virtual float GetDelay() { return 0.0f; }
	virtual int IsMoving() { return (pev->velocity != g_vecZero); }
	virtual void OverrideReset() {}
	virtual int DamageDecal(int bitsDamageType);
	virtual void SetToggleState(int state) {}
	virtual void StartSneaking() {}
	virtual void StopSneaking() {}
	virtual BOOL OnControls(entvars_t *onpev) { return FALSE; }
	virtual BOOL IsSneaking() { return FALSE; }
	virtual BOOL IsAlive() { return (pev->deadflag == DEAD_NO && pev->health > 0.0f); }
	virtual BOOL IsBSPModel() { return (pev->solid == SOLID_BSP || pev->movetype == MOVETYPE_PUSHSTEP); }
	virtual BOOL ReflectGauss() { return (IsBSPModel() && pev->takedamage == DAMAGE_NO); }
	virtual BOOL HasTarget(string_t targetname) { return FStrEq(STRING(targetname), STRING(pev->targetname)); }
	virtual BOOL IsInWorld();
	virtual BOOL IsPlayer() { return FALSE; }
	virtual BOOL IsNetClient() { return FALSE; }
	virtual const char *TeamID() { return ""; }
	virtual CBaseEntity *GetNextTarget();
	virtual void Think()
	{
		if (m_pfnThink)
		{
			(this->*m_pfnThink)();
		}
	}
	virtual void Touch(CBaseEntity *pOther)
	{
		if (m_pfnTouch)
		{
			(this->*m_pfnTouch)(pOther);
		}
	}
	virtual void Use(CBaseEntity *pActivator, CBaseEntity *pCaller, USE_TYPE useType = USE_OFF, float value = 0.0f)
	{
		if (m_pfnUse)
		{
			(this->*m_pfnUse)(pActivator, pCaller, useType, value);
		}
	}
	virtual void Blocked(CBaseEntity *pOther)
	{
		if (m_pfnBlocked)
		{
			(this->*m_pfnBlocked)(pOther);
		}
	}
	virtual CBaseEntity *Respawn() { return NULL; }
	virtual void UpdateOwner() {}
	virtual BOOL FBecomeProne() { return FALSE; }
	virtual Vector Center() { return (pev->absmax + pev->absmin) * 0.5f; }
	virtual Vector EyePosition() { return (pev->origin + pev->view_ofs); }
	virtual Vector EarPosition() { return (pev->origin + pev->view_ofs); }
	virtual Vector BodyTarget(const Vector &posSrc) { return Center(); }
	virtual int Illumination() { return GETENTITYILLUM(ENT(pev)); }

	virtual BOOL FVisible(CBaseEntity *pEntity);
	virtual BOOL FVisible(const Vector &vecOrigin);

#ifdef HOOK_GAMEDLL

	int Save_(CSave &save);
	int Restore_(CRestore &restore);
	void SetObjectCollisionBox_();
	void TraceAttack_(entvars_t *pevAttacker, float flDamage, Vector vecDir, TraceResult *ptr, int bitsDamageType);
	int TakeDamage_(entvars_t *pevInflictor, entvars_t *pevAttacker, float flDamage, int bitsDamageType);
	int TakeHealth_(float flHealth, int bitsDamageType);
	void Killed_(entvars_t *pevAttacker, int iGib);
	void TraceBleed_(float flDamage, Vector vecDir, TraceResult *ptr, int bitsDamageType);
	int DamageDecal_(int bitsDamageType);
	BOOL IsInWorld_();
	CBaseEntity *GetNextTarget_();
	BOOL FVisible_(CBaseEntity *pEntity);
	BOOL FVisible_(const Vector &vecOrigin);

#endif

public:
	void *operator new(size_t stAllocateBlock, entvars_t *pevnew) { return ALLOC_PRIVATE(ENT(pevnew), stAllocateBlock); }
	void operator delete(void *pMem, entvars_t *pevnew) { pevnew->flags |= FL_KILLME; }
	void UpdateOnRemove();
	void EXPORT SUB_Remove();
	void EXPORT SUB_DoNothing();
	void EXPORT SUB_StartFadeOut();
	void EXPORT SUB_FadeOut();
	void EXPORT SUB_CallUseToggle() { Use(this, this, USE_TOGGLE, 0); }
	int ShouldToggle(USE_TYPE useType, BOOL currentState);
	void FireBullets(ULONG cShots, Vector vecSrc, Vector vecDirShooting, Vector vecSpread, float flDistance, int iBulletType, int iTracerFreq = 4, int iDamage = 0, entvars_t *pevAttacker = NULL);
	Vector FireBullets3(Vector vecSrc, Vector vecDirShooting, float vecSpread, float flDistance, int iPenetration, int iBulletType, int iDamage, float flRangeModifier, entvars_t *pevAttacker, bool bPistol, int shared_rand = 0);
	void SUB_UseTargets(CBaseEntity *pActivator, USE_TYPE useType, float value);
	int Intersects(CBaseEntity *pOther);
	void MakeDormant();
	int IsDormant();
	BOOL IsLockedByMaster() { return FALSE; }

public:
	static CBaseEntity *Instance(edict_t *pent) { return (CBaseEntity *)GET_PRIVATE(pent ? pent : ENT(0)); }
	static CBaseEntity *Instance(entvars_t *pev) { return Instance(ENT(pev)); }
	static CBaseEntity *Instance(int offset) { return Instance(ENT(offset)); }

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
	edict_t *edict() { return ENT(pev); }
	EOFFSET eoffset() { return OFFSET(pev); }
	int entindex() { return ENTINDEX(edict()); }

public:
	entvars_t *pev;
	CBaseEntity *m_pGoalEnt;
	CBaseEntity *m_pLink;

	static TYPEDESCRIPTION IMPL(m_SaveData)[5];

	void (CBaseEntity::*m_pfnThink)();
	void (CBaseEntity::*m_pfnTouch)(CBaseEntity *pOther);
	void (CBaseEntity::*m_pfnUse)(CBaseEntity *pActivator, CBaseEntity *pCaller, USE_TYPE useType, float value);
	void (CBaseEntity::*m_pfnBlocked)(CBaseEntity *pOther);

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
};

inline int FNullEnt(CBaseEntity *ent) { return (ent == NULL || FNullEnt(ent->edict())); }
inline int FNullEnt(EHANDLE hent) { return (hent == NULL || FNullEnt(OFFSET(hent.Get()))); }

class CPointEntity: public CBaseEntity
{
public:
	virtual void Spawn();
	virtual int ObjectCaps() { return (CBaseEntity::ObjectCaps() & ~FCAP_ACROSS_TRANSITION); }

#ifdef HOOK_GAMEDLL

	void Spawn_();

#endif

};

class CMultiSource: public CPointEntity
{
public:
	virtual void Spawn();
	virtual void KeyValue(KeyValueData *pkvd);
	virtual int Save(CSave &save);
	virtual int Restore(CRestore &restore);
	virtual int ObjectCaps() { return (CPointEntity::ObjectCaps() | FCAP_MASTER); }
	virtual BOOL IsTriggered(CBaseEntity *pActivator);
	virtual void Use(CBaseEntity *pActivator, CBaseEntity *pCaller, USE_TYPE useType, float value);

#ifdef HOOK_GAMEDLL

	void Spawn_();
	void KeyValue_(KeyValueData *pkvd);
	int Save_(CSave &save);
	int Restore_(CRestore &restore);
	BOOL IsTriggered_(CBaseEntity *pActivator);
	void Use_(CBaseEntity *pActivator, CBaseEntity *pCaller, USE_TYPE useType, float value);

#endif

public:
	void EXPORT Register();

public:
	static TYPEDESCRIPTION IMPL(m_SaveData)[4];

	EHANDLE m_rgEntities[MS_MAX_TARGETS];
	int m_rgTriggered[MS_MAX_TARGETS];
	int m_iTotal;
	string_t m_globalstate;
};

class CBaseDelay: public CBaseEntity
{
public:
	virtual void KeyValue(KeyValueData *pkvd);
	virtual int Save(CSave &save);
	virtual int Restore(CRestore &restore);

#ifdef HOOK_GAMEDLL

	void KeyValue_(KeyValueData *pkvd);
	int Save_(CSave &save);
	int Restore_(CRestore &restore);

#endif

public:
	void SUB_UseTargets(CBaseEntity *pActivator, USE_TYPE useType, float value);
	void EXPORT DelayThink();
public:
	static TYPEDESCRIPTION IMPL(m_SaveData)[2];

	float m_flDelay;
	int m_iszKillTarget;
};

class CBaseAnimating: public CBaseDelay
{
public:
	virtual int Save(CSave &save);
	virtual int Restore(CRestore &restore);
	virtual void HandleAnimEvent(MonsterEvent_t *pEvent) {}

#ifdef HOOK_GAMEDLL

	int Save_(CSave &save);
	int Restore_(CRestore &restore);

#endif

public:
	float StudioFrameAdvance(float flInterval = 0.0f);
	BOOL GetSequenceFlags();
	int LookupActivity(int activity);
	int LookupActivityHeaviest(int activity);
	int LookupSequence(const char *label);
	void ResetSequenceInfo();
	void DispatchAnimEvents(float flFutureInterval = 0.1f);
	float SetBoneController(int iController, float flValue = 0.0f);
	void InitBoneControllers();

	float SetBlending(int iBlender, float flValue);
	void GetBonePosition(int iBone, Vector &origin, Vector &angles);
	void GetAutomovement(Vector &origin, Vector &angles, float flInterval = 0.1f);
	int FindTransition(int iEndingSequence, int iGoalSequence, int *piDir);
	void GetAttachment(int iAttachment, Vector &origin, Vector &angles);
	void SetBodygroup(int iGroup, int iValue);
	int GetBodygroup(int iGroup);

	int ExtractBbox(int sequence, float *mins, float *maxs);
	void SetSequenceBox();
public:
	static TYPEDESCRIPTION IMPL(m_SaveData)[5];

	float m_flFrameRate;
	float m_flGroundSpeed;
	float m_flLastEventCheck;
	BOOL m_fSequenceFinished;
	BOOL m_fSequenceLoops;
};

class CBaseToggle: public CBaseAnimating
{
public:
	virtual void KeyValue(KeyValueData *pkvd);
	virtual int Save(CSave &save);
	virtual int Restore(CRestore &restore);
	virtual int GetToggleState() { return m_toggle_state; }
	virtual float GetDelay() { return m_flWait; }

#ifdef HOOK_GAMEDLL

	void KeyValue_(KeyValueData *pkvd);
	int Save_(CSave &save);
	int Restore_(CRestore &restore);

#endif

public:
	void LinearMove(Vector vecDest, float flSpeed);
	void EXPORT LinearMoveDone();
	void AngularMove(Vector vecDestAngle, float flSpeed);
	void EXPORT AngularMoveDone();
	BOOL IsLockedByMaster();

public:
	static float AxisValue(int flags, const Vector &angles);
	static void AxisDir(entvars_t *pev);
	static float AxisDelta(int flags, const Vector &angle1, const Vector &angle2);

public:
	static TYPEDESCRIPTION IMPL(m_SaveData)[19];

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
	void (CBaseToggle::*m_pfnCallWhenMoveDone)();
	Vector m_vecFinalDest;
	Vector m_vecFinalAngle;
	int m_bitsDamageInflict;
	string_t m_sMaster;
};

#include "basemonster.h"

// Generic Button
class CBaseButton: public CBaseToggle
{
	enum BUTTON_CODE
	{
		BUTTON_NOTHING,
		BUTTON_ACTIVATE,
		BUTTON_RETURN
	};
public:
	virtual void Spawn();
	virtual void Precache();
	virtual void KeyValue(KeyValueData *pkvd);
	virtual int TakeDamage(entvars_t *pevInflictor, entvars_t *pevAttacker, float flDamage, int bitsDamageType);
	virtual int Save(CSave &save);
	virtual int Restore(CRestore &restore);
	virtual int ObjectCaps()
	{
		if (pev->takedamage == DAMAGE_NO)
		{
			return FCAP_IMPULSE_USE;
		}

		return (CBaseToggle::ObjectCaps() & ~FCAP_ACROSS_TRANSITION);
	}

#ifdef HOOK_GAMEDLL

	void Spawn_();
	void Precache_();
	void KeyValue_(KeyValueData *pkvd);
	int TakeDamage_(entvars_t *pevInflictor, entvars_t *pevAttacker, float flDamage, int bitsDamageType);
	int Save_(CSave &save);
	int Restore_(CRestore &restore);

#endif

public:
	void RotSpawn();
	void ButtonActivate();
	void SparkSoundCache();

	void EXPORT ButtonShot();
	void EXPORT ButtonTouch(CBaseEntity *pOther);
	void EXPORT ButtonSpark();
	void EXPORT TriggerAndWait();
	void EXPORT ButtonReturn();
	void EXPORT ButtonBackHome();
	void EXPORT ButtonUse(CBaseEntity *pActivator, CBaseEntity *pCaller, USE_TYPE useType, float value);

	BUTTON_CODE ButtonResponseToTouch();

public:
	static TYPEDESCRIPTION IMPL(m_SaveData)[8];

	BOOL m_fStayPushed;
	BOOL m_fRotating;
	string_t m_strChangeTarget;
	locksound_t m_ls;
	BYTE m_bLockedSound;
	BYTE m_bLockedSentence;
	BYTE m_bUnlockedSound;
	BYTE m_bUnlockedSentence;
	int m_sounds;
};

class CWorld: public CBaseEntity
{
public:
	virtual void Spawn();
	virtual void Precache();
	virtual void KeyValue(KeyValueData *pkvd);

#ifdef HOOK_GAMEDLL

	void Spawn_();
	void Precache_();
	void KeyValue_(KeyValueData *pkvd);

#endif

};

#ifdef REGAMEDLL_SELF
extern class CCSEntity **g_GameEntities;
#endif

template <class TWrap, class T>
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

#ifdef REGAMEDLL_SELF
		g_GameEntities[a->entindex()] = new TWrap (a);
#endif

#if defined(HOOK_GAMEDLL) && defined(_WIN32) && !defined(REGAMEDLL_UNIT_TESTS)
		VirtualTableInit((void *)a, stripClass(typeid(T).name()));
#endif
	}

	return a;
}

#ifdef REGAMEDLL_SELF
extern CUtlVector<hash_item_t> stringsHashTable;
#endif

C_DLLEXPORT int GetEntityAPI(DLL_FUNCTIONS *pFunctionTable, int interfaceVersion);
C_DLLEXPORT int GetNewDLLFunctions(NEW_DLL_FUNCTIONS *pFunctionTable, int *interfaceVersion);

int CaseInsensitiveHash(const char *string, int iBounds);
void EmptyEntityHashTable();
void AddEntityHashValue(entvars_t *pev, const char *value, hash_types_e fieldType);
void RemoveEntityHashValue(entvars_t *pev, const char *value, hash_types_e fieldType);
void printEntities();
edict_t *CREATE_NAMED_ENTITY(string_t iClass);
void REMOVE_ENTITY(edict_t *e);
void CONSOLE_ECHO_(char *pszMsg, ...);
void loopPerformance();
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

#endif // CBASE_H

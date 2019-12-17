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

#include "util.h"
#include "schedule.h"
#include "saverestore.h"
#include "scriptevent.h"
#include "monsterevent.h"

class CSave;
class CRestore;
class CBasePlayer;
class CBaseEntity;
class CBaseMonster;
class CBasePlayerItem;
class CSquadMonster;
class CCSEntity;

#undef CREATE_NAMED_ENTITY
#undef REMOVE_ENTITY

// Base Entity.  All entity types derive from this
class CBaseEntity {
public:
	virtual void Spawn() {}
	virtual void Precache() {}
	virtual void Restart() {}
	virtual void KeyValue(KeyValueData *pkvd) { pkvd->fHandled = FALSE; }
	virtual int Save(CSave &save);
	virtual int Restore(CRestore &restore);
	virtual int ObjectCaps() { return FCAP_ACROSS_TRANSITION; }
	virtual void Activate() {}

	// Setup the object->object collision box (pev->mins / pev->maxs is the object->world collision box)
	virtual void SetObjectCollisionBox();

	// Classify - returns the type of group (i.e, "houndeye", or "human military" so that monsters with different classnames
	// still realize that they are teammates. (overridden for monsters that form groups)
	virtual int Classify() { return CLASS_NONE; }

	virtual void DeathNotice(entvars_t *pevChild) {}
	virtual void TraceAttack(entvars_t *pevAttacker, float flDamage, Vector vecDir, TraceResult *ptr, int bitsDamageType);
	virtual BOOL TakeDamage(entvars_t *pevInflictor, entvars_t *pevAttacker, float flDamage, int bitsDamageType);
	virtual BOOL TakeHealth(float flHealth, int bitsDamageType);
	virtual void Killed(entvars_t *pevAttacker, int iGib);
	virtual int BloodColor() { return DONT_BLEED; }
	virtual void TraceBleed(float flDamage, Vector vecDir, TraceResult *ptr, int bitsDamageType);
	virtual BOOL IsTriggered(CBaseEntity *pActivator) { return TRUE; }
	virtual CBaseMonster *MyMonsterPointer() { return nullptr; }
	virtual CSquadMonster *MySquadMonsterPointer() { return nullptr; }
	virtual int GetToggleState() { return TS_AT_TOP; }
	virtual void AddPoints(int score, BOOL bAllowNegativeScore) {}
	virtual void AddPointsToTeam(int score, BOOL bAllowNegativeScore) {}
	virtual BOOL AddPlayerItem(CBasePlayerItem *pItem) { return FALSE; }
	virtual BOOL RemovePlayerItem(CBasePlayerItem *pItem) { return FALSE; }
	virtual int GiveAmmo(int iAmount, const char *szName, int iMax = -1) { return -1; }
	virtual float GetDelay() { return 0.0f; }
	virtual int IsMoving() { return (pev->velocity != g_vecZero); }
	virtual void OverrideReset() {}
	virtual int DamageDecal(int bitsDamageType);

	// This is ONLY used by the node graph to test movement through a door
	virtual void SetToggleState(int state) {}

#ifndef REGAMEDLL_API
	virtual void StartSneaking() {}
	virtual void StopSneaking() {}
#else
	virtual void OnCreate();
	virtual void OnDestroy();
#endif

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
	virtual void Think() { if (m_pfnThink) (this->*m_pfnThink)(); }
	virtual void Touch(CBaseEntity *pOther) { if (m_pfnTouch) (this->*m_pfnTouch)(pOther); }
	virtual void Use(CBaseEntity *pActivator, CBaseEntity *pCaller, USE_TYPE useType = USE_OFF, float value = 0.0f) { if (m_pfnUse) (this->*m_pfnUse)(pActivator, pCaller, useType, value); }
	virtual void Blocked(CBaseEntity *pOther) { if (m_pfnBlocked) (this->*m_pfnBlocked)(pOther); }
	virtual CBaseEntity *Respawn() { return nullptr; }

	// used by monsters that are created by the MonsterMaker
	virtual void UpdateOwner() {}
	virtual BOOL FBecomeProne() { return FALSE; }

	virtual Vector Center() { return (pev->absmax + pev->absmin) * 0.5f; }		// center point of entity
	virtual Vector EyePosition() { return (pev->origin + pev->view_ofs); }		// position of eyes
	virtual Vector EarPosition() { return (pev->origin + pev->view_ofs); }		// position of ears
	virtual Vector BodyTarget(const Vector &posSrc) { return Center(); }		// position to shoot at

	virtual int Illumination() { return GETENTITYILLUM(ENT(pev)); }

	virtual BOOL FVisible(CBaseEntity *pEntity);
	virtual BOOL FVisible(const Vector &vecOrigin);

public:
	// allow engine to allocate instance data
	void *operator new(size_t stAllocateBlock, entvars_t *pevnew) { return ALLOC_PRIVATE(ENT(pevnew), stAllocateBlock); }

	// don't use this.
#if _MSC_VER >= 1200 // only build this code if MSVC++ 6.0 or higher
	void operator delete(void *pMem, entvars_t *pevnew) { pevnew->flags |= FL_KILLME; }
#endif

	void UpdateOnRemove();

	void EXPORT SUB_Remove();
	void EXPORT SUB_DoNothing();
	void EXPORT SUB_StartFadeOut();
	void EXPORT SUB_FadeOut();
	void EXPORT SUB_CallUseToggle() { Use(this, this, USE_TOGGLE, 0); }
	int ShouldToggle(USE_TYPE useType, BOOL currentState);
	void FireBullets(ULONG cShots, Vector vecSrc, Vector vecDirShooting, Vector vecSpread, float flDistance, int iBulletType, int iTracerFreq = 4, int iDamage = 0, entvars_t *pevAttacker = nullptr);
	void FireBuckshots(ULONG cShots, Vector vecSrc, Vector vecDirShooting, Vector vecSpread, float flDistance, int iTracerFreq, int iDamage, entvars_t *pevAttacker = nullptr);
	Vector FireBullets3(Vector vecSrc, Vector vecDirShooting, float vecSpread, float flDistance, int iPenetration, int iBulletType, int iDamage, float flRangeModifier, entvars_t *pevAttacker, bool bPistol, int shared_rand = 0);
	void SUB_UseTargets(CBaseEntity *pActivator, USE_TYPE useType, float value);
	bool Intersects(CBaseEntity *pOther);
	bool Intersects(const Vector &mins, const Vector &maxs);
	bool CanTakeHealth(float flHealth = 0.0f) const;
	void MakeDormant();

	// This entity's classname.
	const char *GetClassname() const { return pev->classname.str(); }

	bool IsProxy()   const { return (pev->flags & FL_PROXY) == FL_PROXY; }
	bool IsDormant() const { return (pev->flags & FL_DORMANT) == FL_DORMANT; }
	BOOL IsLockedByMaster() { return FALSE; }

public:
	static CBaseEntity *Instance(edict_t *pEdict)
	{
		if (!pEdict)
			pEdict = ENT(0);

		return GET_PRIVATE<CBaseEntity>(pEdict);
	}

	static CBaseEntity *Instance(entvars_t *pev) { return Instance(ENT(pev)); }
	static CBaseEntity *Instance(EOFFSET offset) { return Instance(ENT(offset)); }

	CBaseMonster *GetMonsterPointer(entvars_t *pevMonster)
	{
		CBaseEntity *pEntity = Instance(pevMonster);
		if (pEntity) {
			return pEntity->MyMonsterPointer();
		}

		return nullptr;
	}
	CBaseMonster *GetMonsterPointer(edict_t *pentMonster)
	{
		CBaseEntity *pEntity = Instance(pentMonster);
		if (pEntity) {
			return pEntity->MyMonsterPointer();
		}

		return nullptr;
	}
	static CBaseEntity *Create(const char *szName, const Vector &vecOrigin, const Vector &vecAngles, edict_t *pentOwner = nullptr);
	edict_t *edict() { return ENT(pev); }
	EOFFSET eoffset() { return OFFSET(pev); }
	int entindex() { return ENTINDEX(edict()); }

public:
	// Constructor. Set engine to use C/C++ callback functions
	// pointers to engine data
	entvars_t *pev;					// Don't need to save/restore this pointer, the engine resets it

	// path corners
	CBaseEntity *m_pGoalEnt;		// path corner we are heading towards
	CBaseEntity *m_pLink;			// used for temporary link-list operations.

	static TYPEDESCRIPTION m_SaveData[];

	// fundamental callbacks
	void (CBaseEntity::*m_pfnThink)();
	void (CBaseEntity::*m_pfnTouch)(CBaseEntity *pOther);
	void (CBaseEntity::*m_pfnUse)(CBaseEntity *pActivator, CBaseEntity *pCaller, USE_TYPE useType, float value);
	void (CBaseEntity::*m_pfnBlocked)(CBaseEntity *pOther);

	using thinkfn_t = decltype(m_pfnThink);
	template <typename T>
	void SetThink(void (T::*pfn)());
	void SetThink(std::nullptr_t);

	using touchfn_t = decltype(m_pfnTouch);
	template <typename T>
	void SetTouch(void (T::*pfn)(CBaseEntity *pOther));
	void SetTouch(std::nullptr_t);

	using usefn_t = decltype(m_pfnUse);
	template <typename T>
	void SetUse(void (T::*pfn)(CBaseEntity *pActivator, CBaseEntity *pCaller, USE_TYPE useType, float value));
	void SetUse(std::nullptr_t);

	using blockedfn_t = decltype(m_pfnBlocked);
	template <typename T>
	void SetBlocked(void (T::*pfn)(CBaseEntity *pOther));
	void SetBlocked(std::nullptr_t);

#ifdef REGAMEDLL_API
	CCSEntity *m_pEntity;
#else
	// We use this variables to store each ammo count.
	// let's sacrifice this unused member, for its own needs in favor of m_pEntity
	int *current_ammo;
#endif

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

	// Special stuff for grenades and knife.
	float m_flStartThrow;
	float m_flReleaseThrow;
	int m_iSwing;

	// client has left the game
	bool has_disconnected;
};

// Inlines
inline BOOL FNullEnt(CBaseEntity *pEntity) { return (pEntity == nullptr || FNullEnt(pEntity->edict())); }

template <typename T>
inline void CBaseEntity::SetThink(void (T::*pfn)())
{
	m_pfnThink = static_cast<thinkfn_t>(pfn);
}

inline void CBaseEntity::SetThink(std::nullptr_t)
{
	m_pfnThink = nullptr;
}

template <typename T>
inline void CBaseEntity::SetTouch(void (T::*pfn)(CBaseEntity *pOther))
{
	m_pfnTouch = static_cast<touchfn_t>(pfn);
}

inline void CBaseEntity::SetTouch(std::nullptr_t)
{
	m_pfnTouch = nullptr;
}

template <typename T>
inline void CBaseEntity::SetUse(void (T::*pfn)(CBaseEntity *pActivator, CBaseEntity *pCaller, USE_TYPE useType, float value))
{
	m_pfnUse = static_cast<usefn_t>(pfn);
}

inline void CBaseEntity::SetUse(std::nullptr_t)
{
	m_pfnUse = nullptr;
}

template <typename T>
inline void CBaseEntity::SetBlocked(void (T::*pfn)(CBaseEntity *pOther))
{
	m_pfnBlocked = static_cast<blockedfn_t>(pfn);
}

inline void CBaseEntity::SetBlocked(std::nullptr_t)
{
	m_pfnBlocked = nullptr;
}

class CPointEntity: public CBaseEntity {
public:
	virtual void Spawn();
	virtual int ObjectCaps() { return (CBaseEntity::ObjectCaps() & ~FCAP_ACROSS_TRANSITION); }
};

// generic Delay entity.
class CBaseDelay: public CBaseEntity {
public:
	virtual void KeyValue(KeyValueData *pkvd);
	virtual int Save(CSave &save);
	virtual int Restore(CRestore &restore);

public:
	void SUB_UseTargets(CBaseEntity *pActivator, USE_TYPE useType, float value);
	void EXPORT DelayThink();
public:
	static TYPEDESCRIPTION m_SaveData[];

	float m_flDelay;
	string_t m_iszKillTarget;
};

class CBaseAnimating: public CBaseDelay {
public:
	virtual int Save(CSave &save);
	virtual int Restore(CRestore &restore);
	virtual void HandleAnimEvent(MonsterEvent_t *pEvent) {}

public:
	// Basic Monster Animation functions
	float StudioFrameAdvance(float flInterval = 0.0f);					// accumulate animation frame time from last time called until now
	int GetSequenceFlags();
	int LookupActivity(int activity);
	int LookupActivityHeaviest(int activity);
	int LookupSequence(const char *label);
	void ResetSequenceInfo();
	void DispatchAnimEvents(float flFutureInterval = 0.1f);				// Handle events that have happend since last time called up until X seconds into the future
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

#ifdef REGAMEDLL_API
	void ResetSequenceInfo_OrigFunc();
#endif

public:
	static TYPEDESCRIPTION m_SaveData[];

	// animation needs
	float m_flFrameRate;		// computed FPS for current sequence
	float m_flGroundSpeed;		// computed linear movement rate for current sequence
	float m_flLastEventCheck;	// last time the event list was checked
	BOOL m_fSequenceFinished;	// flag set when StudioAdvanceFrame moves across a frame boundry
	BOOL m_fSequenceLoops;		// true if the sequence loops
};

// generic Toggle entity.
class CBaseToggle: public CBaseAnimating {
public:
	virtual void KeyValue(KeyValueData *pkvd);
	virtual int Save(CSave &save);
	virtual int Restore(CRestore &restore);
	virtual int GetToggleState() { return m_toggle_state; }
	virtual float GetDelay() { return m_flWait; }

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
	static TYPEDESCRIPTION m_SaveData[];

	TOGGLE_STATE m_toggle_state;
	float m_flActivateFinished;	// like attack_finished, but for doors
	float m_flMoveDistance;		// how far a door should slide or rotate
	float m_flWait;
	float m_flLip;
	float m_flTWidth;			// for plats
	float m_flTLength;			// for plats

	Vector m_vecPosition1;
	Vector m_vecPosition2;
	Vector m_vecAngle1;
	Vector m_vecAngle2;

	int m_cTriggersLeft;		// trigger_counter only, # of activations remaining
	float m_flHeight;
	EHandle m_hActivator;
	void (CBaseToggle::*m_pfnCallWhenMoveDone)();

	using movedonefn_t = decltype(m_pfnCallWhenMoveDone);
	template <typename T>
	void SetMoveDone(void (T::*pfn)());
	void SetMoveDone(std::nullptr_t);

	Vector m_vecFinalDest;
	Vector m_vecFinalAngle;

	int m_bitsDamageInflict;	// DMG_ damage type that the door or tigger does

	string_t m_sMaster;			// If this button has a master switch, this is the targetname.
								// A master switch must be of the multisource type. If all
								// of the switches in the multisource have been triggered, then
								// the button will be allowed to operate. Otherwise, it will be
								// deactivated.
};

template <typename T>
inline void CBaseToggle::SetMoveDone(void (T::*pfn)())
{
	m_pfnCallWhenMoveDone = static_cast<movedonefn_t>(pfn);
}

inline void CBaseToggle::SetMoveDone(std::nullptr_t)
{
	m_pfnCallWhenMoveDone = nullptr;
}

#include "world.h"
#include "basemonster.h"
#include "player.h"

#define SF_BUTTON_DONTMOVE      BIT(0)
#define SF_BUTTON_TOGGLE        BIT(5) // button stays pushed until reactivated
#define SF_BUTTON_SPARK_IF_OFF  BIT(6) // button sparks in OFF state
#define SF_BUTTON_TOUCH_ONLY    BIT(8) // button only fires as a result of USE key.

// Generic Button
class CBaseButton: public CBaseToggle {
public:
	virtual void Spawn();
	virtual void Precache();
	virtual void KeyValue(KeyValueData *pkvd);
	virtual BOOL TakeDamage(entvars_t *pevInflictor, entvars_t *pevAttacker, float flDamage, int bitsDamageType);
	virtual int Save(CSave &save);
	virtual int Restore(CRestore &restore);

	// Buttons that don't take damage can be IMPULSE used
	virtual int ObjectCaps()
	{
		if (pev->takedamage == DAMAGE_NO)
		{
			return FCAP_IMPULSE_USE;
		}

		return (CBaseToggle::ObjectCaps() & ~FCAP_ACROSS_TRANSITION);
	}

#ifdef REGAMEDLL_FIXES
	virtual void Restart();
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

	enum BUTTON_CODE { BUTTON_NOTHING, BUTTON_ACTIVATE, BUTTON_RETURN };
	BUTTON_CODE ButtonResponseToTouch();

public:
	static TYPEDESCRIPTION m_SaveData[];

	BOOL m_fStayPushed;				// button stays pushed in until touched again?
	BOOL m_fRotating;				// a rotating button?  default is a sliding button.

	string_t m_strChangeTarget;		// if this field is not null, this is an index into the engine string array.
									// when this button is touched, it's target entity's TARGET field will be set
									// to the button's ChangeTarget. This allows you to make a func_train switch paths, etc.

	locksound_t m_ls;				// door lock sounds

	byte m_bLockedSound;			// ordinals from entity selection
	byte m_bLockedSentence;
	byte m_bUnlockedSound;
	byte m_bUnlockedSentence;
	int m_sounds;
};

// MultiSouce
#define MAX_MS_TARGETS 32 // maximum number of targets a single multisource entity may be assigned.
#define SF_MULTI_INIT BIT(0)

class CMultiSource: public CPointEntity {
public:
	virtual void Spawn();
	virtual void KeyValue(KeyValueData *pkvd);
	virtual int Save(CSave &save);
	virtual int Restore(CRestore &restore);
	virtual int ObjectCaps() { return (CPointEntity::ObjectCaps() | FCAP_MASTER); }
	virtual BOOL IsTriggered(CBaseEntity *pActivator);
	virtual void Use(CBaseEntity *pActivator, CBaseEntity *pCaller, USE_TYPE useType, float value);

#ifdef REGAMEDLL_FIXES
	virtual void Restart();
#endif

public:
	void EXPORT Register();

public:
	static TYPEDESCRIPTION m_SaveData[];

	EHandle m_rgEntities[MAX_MS_TARGETS];
	int m_rgTriggered[MAX_MS_TARGETS];
	int m_iTotal;
	string_t m_globalstate;
};

// Converts a entvars_t * to a class pointer
// It will allocate the class and entity if necessary
template <class W, class T>
T *GetClassPtr(T *a)
{
	entvars_t *pev = (entvars_t *)a;

	// allocate entity if necessary
	if (pev == nullptr)
		pev = VARS(CREATE_ENTITY());

	// get the private data
	a = (T *)GET_PRIVATE(ENT(pev));

	if (a == nullptr)
	{
		// allocate private data
		a = new(pev) T;
		a->pev = pev;

#ifdef REGAMEDLL_API
		a->OnCreate();
		a->m_pEntity = new W();
		a->m_pEntity->m_pContainingEntity = a;
#endif

	}

	return a;
}

extern CUtlVector<hash_item_t> stringsHashTable;

C_DLLEXPORT int GetEntityAPI(DLL_FUNCTIONS *pFunctionTable, int interfaceVersion);
C_DLLEXPORT int GetNewDLLFunctions(NEW_DLL_FUNCTIONS *pFunctionTable, int *interfaceVersion);

void REMOVE_ENTITY(edict_t *pEntity);

int CaseInsensitiveHash(const char *string, int iBounds);
void EmptyEntityHashTable();

EXT_FUNC edict_t *CREATE_NAMED_ENTITY(string_t iClass);
EXT_FUNC void AddEntityHashValue(entvars_t *pev, const char *value, hash_types_e fieldType);
EXT_FUNC void RemoveEntityHashValue(entvars_t *pev, const char *value, hash_types_e fieldType);

EXT_FUNC int  DispatchSpawn(edict_t *pent);
EXT_FUNC void DispatchKeyValue(edict_t *pentKeyvalue, KeyValueData *pkvd);
EXT_FUNC void DispatchTouch(edict_t *pentTouched, edict_t *pentOther);
EXT_FUNC void DispatchUse(edict_t *pentUsed, edict_t *pentOther);
EXT_FUNC void DispatchThink(edict_t *pent);
EXT_FUNC void DispatchBlocked(edict_t *pentBlocked, edict_t *pentOther);
EXT_FUNC void DispatchSave(edict_t *pent, SAVERESTOREDATA *pSaveData);
EXT_FUNC int  DispatchRestore(edict_t *pent, SAVERESTOREDATA *pSaveData, int globalEntity);
EXT_FUNC void DispatchObjectCollsionBox(edict_t *pent);
EXT_FUNC void SaveWriteFields(SAVERESTOREDATA *pSaveData, const char *pname, void *pBaseData, TYPEDESCRIPTION *pFields, int fieldCount);
EXT_FUNC void SaveReadFields(SAVERESTOREDATA *pSaveData, const char *pname, void *pBaseData, TYPEDESCRIPTION *pFields, int fieldCount);
EXT_FUNC void OnFreeEntPrivateData(edict_t *pEnt);
EXT_FUNC void OnGameShutdown();

void SetObjectCollisionBox(entvars_t *pev);
CBaseEntity *FindGlobalEntity(string_t classname, string_t globalname);

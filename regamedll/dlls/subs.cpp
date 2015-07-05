#include "precompiled.h"

/*
* Globals initialization
*/
#ifndef HOOK_GAMEDLL

TYPEDESCRIPTION CBaseDelay::m_SaveData[] =
{
	DEFINE_FIELD(CBaseDelay, m_flDelay, FIELD_FLOAT),
	DEFINE_FIELD(CBaseDelay, m_iszKillTarget, FIELD_STRING),
};

TYPEDESCRIPTION CBaseToggle::m_SaveData[] =
{
	DEFINE_FIELD(CBaseToggle, m_toggle_state, FIELD_INTEGER),
	DEFINE_FIELD(CBaseToggle, m_flActivateFinished, FIELD_TIME),
	DEFINE_FIELD(CBaseToggle, m_flMoveDistance, FIELD_FLOAT),
	DEFINE_FIELD(CBaseToggle, m_flWait, FIELD_FLOAT),
	DEFINE_FIELD(CBaseToggle, m_flLip, FIELD_FLOAT),
	DEFINE_FIELD(CBaseToggle, m_flTWidth, FIELD_FLOAT),
	DEFINE_FIELD(CBaseToggle, m_flTLength, FIELD_FLOAT),
	DEFINE_FIELD(CBaseToggle, m_vecPosition1, FIELD_POSITION_VECTOR),
	DEFINE_FIELD(CBaseToggle, m_vecPosition2, FIELD_POSITION_VECTOR),
	DEFINE_FIELD(CBaseToggle, m_vecAngle1, FIELD_VECTOR),
	DEFINE_FIELD(CBaseToggle, m_vecAngle2, FIELD_VECTOR),
	DEFINE_FIELD(CBaseToggle, m_cTriggersLeft, FIELD_INTEGER),
	DEFINE_FIELD(CBaseToggle, m_flHeight, FIELD_FLOAT),
	DEFINE_FIELD(CBaseToggle, m_hActivator, FIELD_EHANDLE),
	DEFINE_FIELD(CBaseToggle, m_pfnCallWhenMoveDone, FIELD_FUNCTION),
	DEFINE_FIELD(CBaseToggle, m_vecFinalDest, FIELD_POSITION_VECTOR),
	DEFINE_FIELD(CBaseToggle, m_vecFinalAngle, FIELD_VECTOR),
	DEFINE_FIELD(CBaseToggle, m_sMaster, FIELD_STRING),
	DEFINE_FIELD(CBaseToggle, m_bitsDamageInflict, FIELD_INTEGER),
};

#else // HOOK_GAMEDLL

TYPEDESCRIPTION (*CBaseDelay::pm_SaveData)[2];
TYPEDESCRIPTION (*CBaseToggle::pm_SaveData)[19];

#endif // HOOK_GAMEDLL

/* <1832bc> ../cstrike/dlls/subs.cpp:38 */
NOBODY void CPointEntity::Spawn_(void)
{
}

/* <183417> ../cstrike/dlls/subs.cpp:53 */
NOBODY void CNullEntity::Spawn_(void)
{
}

/* <1838f5> ../cstrike/dlls/subs.cpp:57 */
LINK_ENTITY_TO_CLASS(info_null, CNullEntity);

/* <1839f1> ../cstrike/dlls/subs.cpp:69 */
LINK_ENTITY_TO_CLASS(info_player_deathmatch, CBaseDMStart);

/* <183aed> ../cstrike/dlls/subs.cpp:70 */
LINK_ENTITY_TO_CLASS(info_player_start, CPointEntity);

/* <183bb7> ../cstrike/dlls/subs.cpp:71 */
LINK_ENTITY_TO_CLASS(info_vip_start, CBaseDMStart);

/* <183c81> ../cstrike/dlls/subs.cpp:72 */
LINK_ENTITY_TO_CLASS(info_landmark, CPointEntity);

/* <183d4b> ../cstrike/dlls/subs.cpp:75 */
LINK_ENTITY_TO_CLASS(info_hostage_rescue, CPointEntity);

/* <183e15> ../cstrike/dlls/subs.cpp:77 */
LINK_ENTITY_TO_CLASS(info_bomb_target, CPointEntity);

/* <183647> ../cstrike/dlls/subs.cpp:79 */
NOBODY void CBaseDMStart::KeyValue_(KeyValueData *pkvd)
{
//	FStrEq(const char *sz1,
//		const char *sz2);  //    81
//	KeyValue(CBaseEntity *const this,
//		KeyValueData *pkvd);  //    87
//	KeyValue(CBaseDMStart *const this,
//		KeyValueData *pkvd);  //    79
}

/* <18331c> ../cstrike/dlls/subs.cpp:90 */
NOBODY BOOL CBaseDMStart::IsTriggered_(CBaseEntity *pEntity)
{
//	{
//		BOOL master;                                          //    92
//	}
}

/* <183f03> ../cstrike/dlls/subs.cpp:98 */
void CBaseEntity::UpdateOnRemove(void)
{
	if (pev->flags & FL_GRAPHED) // NOXREF
	{
		for (int i = 0; i < WorldGraph.m_cLinks; i++)
		{
			if (WorldGraph.m_pLinkPool[i].m_pLinkEnt == pev)
				WorldGraph.m_pLinkPool[i].m_pLinkEnt = NULL;
		}
	}
	if (pev->globalname)
		gGlobalState.EntitySetState(pev->globalname, GLOBAL_DEAD);
}

/* <183f38> ../cstrike/dlls/subs.cpp:120 */
void CBaseEntity::SUB_Remove(void)
{
	UpdateOnRemove();
	if (pev->health > 0)
	{
		pev->health = 0;
		ALERT(at_aiconsole, "SUB_Remove called on entity with health > 0\n");
	}
	REMOVE_ENTITY(ENT(pev));
}

/* <183f8a> ../cstrike/dlls/subs.cpp:135 */
void CBaseEntity::SUB_DoNothing(void)
{
	;
}

/* <183523> ../cstrike/dlls/subs.cpp:147 */
IMPLEMENT_SAVERESTORE(CBaseDelay, CBaseEntity);

/* <18356f> ../cstrike/dlls/subs.cpp:149 */
void CBaseDelay::KeyValue_(KeyValueData *pkvd)
{
	if (FStrEq(pkvd->szKeyName, "delay"))
	{
		m_flDelay = atof(pkvd->szValue);
		pkvd->fHandled = TRUE;
	}
	else if (FStrEq(pkvd->szKeyName, "killtarget"))
	{
		m_iszKillTarget = ALLOC_STRING(pkvd->szValue);
		pkvd->fHandled = TRUE;
	}
	else
		CBaseEntity::KeyValue(pkvd);
}

/* <1840d5> ../cstrike/dlls/subs.cpp:183 */
void CBaseEntity::SUB_UseTargets(CBaseEntity *pActivator, USE_TYPE useType, float value)
{
	if (!FStringNull(pev->target))
		FireTargets(STRING(pev->target), pActivator, this, useType, value);
}

/* <183fb0> ../cstrike/dlls/subs.cpp:195 */
void FireTargets(const char *targetName, CBaseEntity *pActivator, CBaseEntity *pCaller, USE_TYPE useType, float value)
{
	edict_t *pentTarget = NULL;
	if (!targetName)
		return;

	ALERT(at_aiconsole, "Firing: (%s)\n", targetName);
	while (1)
	{
		pentTarget = FIND_ENTITY_BY_TARGETNAME(pentTarget, targetName);
		if (FNullEnt(pentTarget))
			break;

		CBaseEntity *pTarget = CBaseEntity::Instance(pentTarget);
		if (pTarget && !(pTarget->pev->flags & FL_KILLME))
		{
			ALERT(at_aiconsole, "Found: %s, firing (%s)\n", STRING(pTarget->pev->classname), targetName);
			pTarget->Use(pActivator, pCaller, useType, value);
		}
	}
}

/* <1843f8> ../cstrike/dlls/subs.cpp:249 */
LINK_ENTITY_TO_CLASS(DelayedUse, CBaseDelay);

/* <1844c2> ../cstrike/dlls/subs.cpp:252 */
void CBaseDelay::SUB_UseTargets(CBaseEntity *pActivator, USE_TYPE useType, float value)
{
	if (!pev->target && !m_iszKillTarget)
		return;

	if (!m_flDelay)
	{
		if (m_iszKillTarget)
		{
			ALERT(at_aiconsole, "KillTarget: %s\n", STRING(m_iszKillTarget));
			edict_t *pentKillTarget = FIND_ENTITY_BY_TARGETNAME(NULL, STRING(m_iszKillTarget));

			while (!FNullEnt(pentKillTarget))
			{
				UTIL_Remove(CBaseEntity::Instance(pentKillTarget));
				ALERT(at_aiconsole, "killing %s\n", STRING(pentKillTarget->v.classname));
				pentKillTarget = FIND_ENTITY_BY_TARGETNAME(pentKillTarget, STRING(m_iszKillTarget));
			}
		}
		if (pev->target)
			FireTargets(STRING(pev->target), pActivator, this, useType, value);
	}
	else
	{
		CBaseDelay *pTemp = GetClassPtr((CBaseDelay *)NULL);
		if (pTemp->pev->classname)
			RemoveEntityHashValue(pTemp->pev, STRING(pTemp->pev->classname), CLASSNAME);

		MAKE_STRING_CLASS("DelayedUse",pTemp->pev);
		AddEntityHashValue(pTemp->pev, STRING(pTemp->pev->classname), CLASSNAME);

		pTemp->pev->nextthink = gpGlobals->time + m_flDelay;
		pTemp->SetThink(&CBaseDelay::DelayThink);
		pTemp->pev->button = (int)useType;
		pTemp->m_iszKillTarget = m_iszKillTarget;
		pTemp->m_flDelay = 0.0f;
		pTemp->pev->target = pev->target;

		if (pActivator && pActivator->IsPlayer())
			pTemp->pev->owner = pActivator->edict();
		else
			pTemp->pev->owner = NULL;
	}
}

/* <1846d9> ../cstrike/dlls/subs.cpp:335 */
void SetMovedir(entvars_t *pev)
{
	if (pev->angles == Vector(0, -1, 0))
		pev->movedir = Vector(0, 0, 1);

	else if (pev->angles == Vector(0, -2, 0))
		pev->movedir = Vector(0, 0, -1);
	else
	{
		UTIL_MakeVectors(pev->angles);
		pev->movedir = gpGlobals->v_forward;
	}
	pev->angles = g_vecZero;
}

/* <184158> ../cstrike/dlls/subs.cpp:357 */
void CBaseDelay::DelayThink(void)
{
	CBaseEntity *pActivator = NULL;
	if (pev->owner)
		pActivator = CBaseEntity::Instance(pev->owner);

	SUB_UseTargets(pActivator, (USE_TYPE)pev->button, 0.0f);
	REMOVE_ENTITY(ENT(pev));
}

/* <1834d6> ../cstrike/dlls/subs.cpp:394 */
IMPLEMENT_SAVERESTORE(CBaseToggle, CBaseAnimating);

/* <1836dc> ../cstrike/dlls/subs.cpp:397 */
void CBaseToggle::KeyValue_(KeyValueData *pkvd)
{
	if (FStrEq(pkvd->szKeyName, "lip"))
	{
		m_flLip = atof(pkvd->szValue);
		pkvd->fHandled = TRUE;
	}
	else if (FStrEq(pkvd->szKeyName, "wait"))
	{
		m_flWait = atof(pkvd->szValue);
		pkvd->fHandled = TRUE;
	}
	else if (FStrEq(pkvd->szKeyName, "master"))
	{
		m_sMaster = ALLOC_STRING(pkvd->szValue);
		pkvd->fHandled = TRUE;
	}
	else if (FStrEq(pkvd->szKeyName, "distance"))
	{
		m_flMoveDistance = atof(pkvd->szValue);
		pkvd->fHandled = TRUE;
	}
	else
		CBaseDelay::KeyValue(pkvd);
}

/* <18474d> ../cstrike/dlls/subs.cpp:431 */
NOBODY void CBaseToggle::LinearMove(Vector vecDest, float flSpeed)
{
//	{
//		class Vector vecDestDelta;                            //   446
//		float flTravelTime;                                   //   449
//		operator==(const class Vector *const this,
//				const class Vector &v);  //   439
//		operator-(const class Vector *const this,
//				const class Vector &v);  //   446
//		Length(const class Vector *const this);  //   449
//		operator/(const class Vector *const this,
//				float fl);  //   456
//		LinearMoveDone(CBaseToggle *const this);  //   441
//	} 
}

/* <18337e> ../cstrike/dlls/subs.cpp:465 */
NOBODY void CBaseToggle::LinearMoveDone(void)
{
}

/* <184855> ../cstrike/dlls/subs.cpp:474 */
NOBODY BOOL CBaseToggle::IsLockedByMaster(void)
{
}

/* <18487c> ../cstrike/dlls/subs.cpp:491 */
NOBODY void CBaseToggle::AngularMove(Vector vecDestAngle, float flSpeed)
{
//	{
//		class Vector vecDestDelta;                            //   506
//		float flTravelTime;                                   //   509
//		operator==(const class Vector *const this,
//				const class Vector &v);  //   499
//		operator-(const class Vector *const this,
//				const class Vector &v);  //   506
//		Length(const class Vector *const this);  //   509
//		operator/(const class Vector *const this,
//				float fl);  //   516
//		AngularMoveDone(CBaseToggle *const this);  //   501
//	} 
}

/* <1832fb> ../cstrike/dlls/subs.cpp:525 */
NOBODY void CBaseToggle::AngularMoveDone(void)
{
}

/* <184984> ../cstrike/dlls/subs.cpp:535 */
NOBODY float CBaseToggle::AxisValue(int flags, Vector &angles)
{
}

/* <1849bd> ../cstrike/dlls/subs.cpp:546 */
NOBODY void CBaseToggle::AxisDir(entvars_t *pev)
{
}

/* <1849e3> ../cstrike/dlls/subs.cpp:557 */
NOBODY float CBaseToggle::AxisDelta(int flags, Vector &angle1, Vector &angle2)
{
}

/* <184a30> ../cstrike/dlls/subs.cpp:577 */
NOBODY BOOL FEntIsVisible(entvars_t *pev, entvars_t *pevTarget)
{
//	{ 
//		class Vector vecSpot1;                                //   581
//		class Vector vecSpot2;                                //   582
//		TraceResult tr;                                       //   583
//		operator+(const class Vector *const this,
//				const class Vector &v);  //   581
//		operator+(const class Vector *const this,
//				const class Vector &v);  //   582
//	} 
}

#ifdef HOOK_GAMEDLL

void CNullEntity::Spawn(void)
{
	Spawn_();
}

void CPointEntity::Spawn(void)
{
	Spawn_();
}

void CBaseDelay::KeyValue(KeyValueData *pkvd)
{
	KeyValue_(pkvd);
}

int CBaseDelay::Save(CSave &save)
{
	return Save_(save);
}

int CBaseDelay::Restore(CRestore &restore)
{
	return Restore_(restore);
}

void CBaseToggle::KeyValue(KeyValueData *pkvd)
{
	KeyValue_(pkvd);
}

int CBaseToggle::Save(CSave &save)
{
	return Save_(save);
}

int CBaseToggle::Restore(CRestore &restore)
{
	return Restore_(restore);
}

void CBaseDMStart::KeyValue(KeyValueData *pkvd)
{
	KeyValue_(pkvd);
}

BOOL CBaseDMStart::IsTriggered(CBaseEntity *pEntity)
{
	return IsTriggered_(pEntity);
}

#endif // HOOK_GAMEDLL

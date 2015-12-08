#include "precompiled.h"

/*
* Globals initialization
*/
#ifndef HOOK_GAMEDLL

// Global Savedata for changelevel friction modifier
TYPEDESCRIPTION CFrictionModifier::m_SaveData[] =
{
	DEFINE_FIELD(CFrictionModifier, m_frictionFraction, FIELD_FLOAT),
};

TYPEDESCRIPTION CAutoTrigger::m_SaveData[] =
{
	DEFINE_FIELD(CAutoTrigger, m_globalstate, FIELD_STRING),
	DEFINE_FIELD(CAutoTrigger, triggerType, FIELD_INTEGER),
};

TYPEDESCRIPTION CTriggerRelay::m_SaveData[1] =
{
	DEFINE_FIELD(CTriggerRelay, triggerType, FIELD_INTEGER),
};

// Global Savedata for multi_manager
TYPEDESCRIPTION CMultiManager::m_SaveData[] =
{
	DEFINE_FIELD(CMultiManager, m_cTargets, FIELD_INTEGER),
	DEFINE_FIELD(CMultiManager, m_index, FIELD_INTEGER),
	DEFINE_FIELD(CMultiManager, m_startTime, FIELD_TIME),
	DEFINE_ARRAY(CMultiManager, m_iTargetName, FIELD_STRING, MAX_MULTI_TARGETS),
	DEFINE_ARRAY(CMultiManager, m_flTargetDelay, FIELD_FLOAT, MAX_MULTI_TARGETS),
};

// Global Savedata for changelevel trigger
TYPEDESCRIPTION CChangeLevel::m_SaveData[] =
{
	DEFINE_ARRAY(CChangeLevel, m_szMapName, FIELD_CHARACTER, 32),
	DEFINE_ARRAY(CChangeLevel, m_szLandmarkName, FIELD_CHARACTER, 32),
	DEFINE_FIELD(CChangeLevel, m_changeTarget, FIELD_STRING),
	DEFINE_FIELD(CChangeLevel, m_changeTargetDelay, FIELD_FLOAT),
};
TYPEDESCRIPTION CTriggerChangeTarget::m_SaveData[] =
{
	DEFINE_FIELD(CTriggerChangeTarget, m_iszNewTarget, FIELD_STRING),
};

// Global Savedata for changelevel friction modifier
TYPEDESCRIPTION CTriggerCamera::m_SaveData[] =
{
	DEFINE_FIELD(CTriggerCamera, m_hPlayer, FIELD_EHANDLE),
	DEFINE_FIELD(CTriggerCamera, m_hTarget, FIELD_EHANDLE),
	DEFINE_FIELD(CTriggerCamera, m_pentPath, FIELD_CLASSPTR),
	DEFINE_FIELD(CTriggerCamera, m_sPath, FIELD_STRING),
	DEFINE_FIELD(CTriggerCamera, m_flWait, FIELD_FLOAT),
	DEFINE_FIELD(CTriggerCamera, m_flReturnTime, FIELD_TIME),
	DEFINE_FIELD(CTriggerCamera, m_flStopTime, FIELD_TIME),
	DEFINE_FIELD(CTriggerCamera, m_moveDistance, FIELD_FLOAT),
	DEFINE_FIELD(CTriggerCamera, m_targetSpeed, FIELD_FLOAT),
	DEFINE_FIELD(CTriggerCamera, m_initialSpeed, FIELD_FLOAT),
	DEFINE_FIELD(CTriggerCamera, m_acceleration, FIELD_FLOAT),
	DEFINE_FIELD(CTriggerCamera, m_deceleration, FIELD_FLOAT),
	DEFINE_FIELD(CTriggerCamera, m_state, FIELD_INTEGER),
};

FILE_GLOBAL char st_szNextMap[cchMapNameMost];
FILE_GLOBAL char st_szNextSpot[cchMapNameMost];

#else

TYPEDESCRIPTION IMPL_CLASS(CFrictionModifier, m_SaveData)[1];
TYPEDESCRIPTION IMPL_CLASS(CAutoTrigger, m_SaveData)[2];
TYPEDESCRIPTION IMPL_CLASS(CTriggerRelay, m_SaveData)[1];
TYPEDESCRIPTION IMPL_CLASS(CMultiManager, m_SaveData)[5];
TYPEDESCRIPTION IMPL_CLASS(CChangeLevel, m_SaveData)[4];
TYPEDESCRIPTION IMPL_CLASS(CTriggerChangeTarget, m_SaveData)[1];
TYPEDESCRIPTION IMPL_CLASS(CTriggerCamera, m_SaveData)[13];

char st_szNextMap[cchMapNameMost];
char st_szNextSpot[cchMapNameMost];

#endif // HOOK_GAMEDLL

/* <1a257e> ../cstrike/dlls/triggers.cpp:60 */
LINK_ENTITY_TO_CLASS(func_friction, CFrictionModifier);

/* <1a0ad7> ../cstrike/dlls/triggers.cpp:68 */
IMPLEMENT_SAVERESTORE(CFrictionModifier, CBaseEntity);

/* <19fa7d> ../cstrike/dlls/triggers.cpp:72 */
void CFrictionModifier::__MAKE_VHOOK(Spawn)(void)
{
	pev->solid = SOLID_TRIGGER;

	// set size and link into world
	SET_MODEL(ENT(pev), STRING(pev->model));

	pev->movetype = MOVETYPE_NONE;
	SetTouch(&CFrictionModifier::ChangeFriction);
}

// Sets toucher's friction to m_frictionFraction (1.0 = normal friction)

/* <19faa6> ../cstrike/dlls/triggers.cpp:82 */
void CFrictionModifier::ChangeFriction(CBaseEntity *pOther)
{
	if (pOther->pev->movetype != MOVETYPE_BOUNCEMISSILE && pOther->pev->movetype != MOVETYPE_BOUNCE)
	{
		pOther->pev->friction = m_frictionFraction;
	}
}

// Sets toucher's friction to m_frictionFraction (1.0 = normal friction)

/* <1a1c39> ../cstrike/dlls/triggers.cpp:91 */
void CFrictionModifier::__MAKE_VHOOK(KeyValue)(KeyValueData *pkvd)
{
	if (FStrEq(pkvd->szKeyName, "modifier"))
	{
		m_frictionFraction = Q_atof(pkvd->szValue) / 100.0;
		pkvd->fHandled = TRUE;
	}
	else
		CBaseEntity::KeyValue(pkvd);
}

/* <1a2657> ../cstrike/dlls/triggers.cpp:126 */
LINK_ENTITY_TO_CLASS(trigger_auto, CAutoTrigger);

/* <1a0a85> ../cstrike/dlls/triggers.cpp:134 */
IMPLEMENT_SAVERESTORE(CAutoTrigger, CBaseDelay);

/* <1a1b64> ../cstrike/dlls/triggers.cpp:136 */
void CAutoTrigger::__MAKE_VHOOK(KeyValue)(KeyValueData *pkvd)
{
	if (FStrEq(pkvd->szKeyName, "globalstate"))
	{
		m_globalstate = ALLOC_STRING(pkvd->szValue);
		pkvd->fHandled = TRUE;
	}
	else if (FStrEq(pkvd->szKeyName, "triggerstate"))
	{
		int type = Q_atoi(pkvd->szValue);
		switch (type)
		{
		case 0:
			triggerType = USE_OFF;
			break;
		case 2:
			triggerType = USE_TOGGLE;
			break;
		default:
			triggerType = USE_ON;
			break;
		}
		pkvd->fHandled = TRUE;
	}
	else
		CBaseDelay::KeyValue(pkvd);
}

/* <19fb05> ../cstrike/dlls/triggers.cpp:165 */
void CAutoTrigger::__MAKE_VHOOK(Spawn)(void)
{
	Precache();
}

/* <19fb2d> ../cstrike/dlls/triggers.cpp:171 */
void CAutoTrigger::__MAKE_VHOOK(Precache)(void)
{
	pev->nextthink = gpGlobals->time + 0.1;
}

/* <19d48c> ../cstrike/dlls/triggers.cpp:177 */
void CAutoTrigger::__MAKE_VHOOK(Think)(void)
{
	if (!m_globalstate || gGlobalState.EntityGetState(m_globalstate) == GLOBAL_ON)
	{
		SUB_UseTargets(this, triggerType, 0);

		if (pev->spawnflags & SF_AUTO_FIREONCE)
		{
			UTIL_Remove(this);
		}
	}
}

/* <1a2730> ../cstrike/dlls/triggers.cpp:207 */
LINK_ENTITY_TO_CLASS(trigger_relay, CTriggerRelay);

/* <1a0a33> ../cstrike/dlls/triggers.cpp:214 */
IMPLEMENT_SAVERESTORE(CTriggerRelay, CBaseDelay);

/* <1a1abc> ../cstrike/dlls/triggers.cpp:216 */
void CTriggerRelay::__MAKE_VHOOK(KeyValue)(KeyValueData *pkvd)
{
	if (FStrEq(pkvd->szKeyName, "triggerstate"))
	{
		int type = Q_atoi(pkvd->szValue);
		switch (type)
		{
		case 0:
			triggerType = USE_OFF;
			break;
		case 2:
			triggerType = USE_TOGGLE;
			break;
		default:
			triggerType = USE_ON;
			break;
		}
		pkvd->fHandled = TRUE;
	}
	else
		CBaseDelay::KeyValue(pkvd);
}

/* <19fb7e> ../cstrike/dlls/triggers.cpp:240 */
void CTriggerRelay::__MAKE_VHOOK(Spawn)(void)
{
	;
}

/* <1a01d7> ../cstrike/dlls/triggers.cpp:247 */
void CTriggerRelay::__MAKE_VHOOK(Use)(CBaseEntity *pActivator, CBaseEntity *pCaller, USE_TYPE useType, float value)
{
	SUB_UseTargets(this, triggerType, 0);
	if (pev->spawnflags & SF_RELAY_FIREONCE)
	{
		UTIL_Remove(this);
	}
}

/* <1a283f> ../cstrike/dlls/triggers.cpp:304 */
LINK_ENTITY_TO_CLASS(multi_manager, CMultiManager);

/* <1a09e0> ../cstrike/dlls/triggers.cpp:316 */
IMPLEMENT_SAVERESTORE(CMultiManager, CBaseToggle);

/* <1a19ed> ../cstrike/dlls/triggers.cpp:318 */
void CMultiManager::__MAKE_VHOOK(KeyValue)(KeyValueData *pkvd)
{
	if (FStrEq(pkvd->szKeyName, "wait"))
	{
		m_flWait = Q_atof(pkvd->szValue);
		pkvd->fHandled = TRUE;
	}
	else // add this field to the target list
	{
		// this assumes that additional fields are targetnames and their values are delay values.
		if (m_cTargets < MAX_MULTI_TARGETS)
		{
			char tmp[128];

			UTIL_StripToken(pkvd->szKeyName, tmp);
			m_iTargetName[m_cTargets] = ALLOC_STRING(tmp);
			m_flTargetDelay[m_cTargets] = Q_atof(pkvd->szValue);
			m_cTargets++;

			pkvd->fHandled = TRUE;
		}
	}
}

/* <19fbce> ../cstrike/dlls/triggers.cpp:347 */
void CMultiManager::__MAKE_VHOOK(Spawn)(void)
{
	pev->solid = SOLID_NOT;
	SetUse(&CMultiManager::ManagerUse);
	SetThink(&CMultiManager::ManagerThink);

	// Sort targets
	// Quick and dirty bubble sort
	int swapped = 1;

	while (swapped)
	{
		swapped = 0;
		for (int i = 1; i < m_cTargets; i++)
		{
			if (m_flTargetDelay[i] < m_flTargetDelay[i - 1])
			{
				// Swap out of order elements
				int name = m_iTargetName[i];
				float delay = m_flTargetDelay[i];

				m_iTargetName[i] = m_iTargetName[i - 1];
				m_flTargetDelay[i] = m_flTargetDelay[i - 1];
				m_iTargetName[i - 1] = name;
				m_flTargetDelay[i - 1] = delay;
				swapped = 1;
			}
		}
	}
}

/* <1a03e5> ../cstrike/dlls/triggers.cpp:377 */
void CMultiManager::__MAKE_VHOOK(Restart)(void)
{
	edict_t *pentTarget = NULL;

	for (int i = 0; i < m_cTargets; i++)
	{
		const char *name = STRING(m_iTargetName[i]);

		if (!name)
			continue;

		pentTarget = FIND_ENTITY_BY_TARGETNAME(pentTarget, STRING(pev->target));

		if (FNullEnt(pentTarget))
			break;

		CBaseEntity *pTarget = (CBaseEntity *)CBaseEntity::Instance(pentTarget);

		if (pTarget && !(pTarget->pev->flags & FL_KILLME))
		{
			pTarget->Restart();
		}
	}

	SetThink(NULL);

	if (IsClone())
	{
		UTIL_Remove(this);
		return;
	}

	SetUse(&CMultiManager::ManagerUse);
	m_index = 0;
}

/* <1a1402> ../cstrike/dlls/triggers.cpp:420 */
BOOL CMultiManager::__MAKE_VHOOK(HasTarget)(string_t targetname)
{
	for (int i = 0; i < m_cTargets; i++)
	{
		if (FStrEq(STRING(targetname), STRING(m_iTargetName[i])))
		{
			return TRUE;
		}
	}

	return FALSE;
}

// Designers were using this to fire targets that may or may not exist --
// so I changed it to use the standard target fire code, made it a little simpler.

/* <1a0393> ../cstrike/dlls/triggers.cpp:432 */
void CMultiManager::ManagerThink(void)
{
	float time;

	time = gpGlobals->time - m_startTime;
	while (m_index < m_cTargets && m_flTargetDelay[ m_index ] <= time)
	{
		FireTargets(STRING(m_iTargetName[ m_index ]), m_hActivator, this, USE_TOGGLE, 0);
		m_index++;
	}

	// have we fired all targets?
	if (m_index >= m_cTargets)
	{
		SetThink(NULL);
		if (IsClone())
		{
			UTIL_Remove(this);
			return;
		}

		// allow manager re-use
		SetUse(&CMultiManager::ManagerUse);
	}
	else
		pev->nextthink = m_startTime + m_flTargetDelay[ m_index ];
}

/* <1a291b> ../cstrike/dlls/triggers.cpp:457 */
CMultiManager *CMultiManager::Clone(void)
{
	CMultiManager *pMulti = GetClassPtr((CMultiManager *)NULL);

	edict_t *pEdict = pMulti->pev->pContainingEntity;
	Q_memcpy(pMulti->pev, pev, sizeof(*pev));

	pMulti->pev->pContainingEntity = pEdict;
	pMulti->pev->spawnflags |= SF_MULTIMAN_CLONE;
	pMulti->m_cTargets = m_cTargets;

	Q_memcpy(pMulti->m_iTargetName, m_iTargetName, sizeof(m_iTargetName));
	Q_memcpy(pMulti->m_flTargetDelay, m_flTargetDelay, sizeof(m_flTargetDelay));

	return pMulti;
}

// The USE function builds the time table and starts the entity thinking.

/* <1a2a24> ../cstrike/dlls/triggers.cpp:475 */
void CMultiManager::ManagerUse(CBaseEntity *pActivator, CBaseEntity *pCaller, USE_TYPE useType, float value)
{
	// In multiplayer games, clone the MM and execute in the clone (like a thread)
	// to allow multiple players to trigger the same multimanager
	if (ShouldClone())
	{
		CMultiManager *pClone = Clone();
		pClone->ManagerUse(pActivator, pCaller, useType, value);
		return;
	}

	m_hActivator = pActivator;
	m_index = 0;
	m_startTime = gpGlobals->time;

	// disable use until all targets have fired
	SetUse(NULL);
	SetThink(&CMultiManager::ManagerThink);

	pev->nextthink = gpGlobals->time;
}

/* <1a2ada> ../cstrike/dlls/triggers.cpp:532 */
LINK_ENTITY_TO_CLASS(env_render, CRenderFxManager);

/* <19fc52> ../cstrike/dlls/triggers.cpp:535 */
void CRenderFxManager::__MAKE_VHOOK(Spawn)(void)
{
	pev->solid = SOLID_NOT;
}

/* <1a0c95> ../cstrike/dlls/triggers.cpp:540 */
void CRenderFxManager::__MAKE_VHOOK(Use)(CBaseEntity *pActivator, CBaseEntity *pCaller, USE_TYPE useType, float value)
{
	if (!FStringNull(pev->target))
	{
		edict_t *pentTarget = NULL;
		while (true)
		{
			pentTarget = FIND_ENTITY_BY_TARGETNAME(pentTarget, STRING(pev->target));

			if (FNullEnt(pentTarget))
				break;

			entvars_t *pevTarget = VARS(pentTarget);

			if (!(pev->spawnflags & SF_RENDER_MASKFX))
				pevTarget->renderfx = pev->renderfx;

			if (!(pev->spawnflags & SF_RENDER_MASKAMT))
				pevTarget->renderamt = pev->renderamt;

			if (!(pev->spawnflags & SF_RENDER_MASKMODE))
				pevTarget->rendermode = pev->rendermode;

			if (!(pev->spawnflags & SF_RENDER_MASKCOLOR))
				pevTarget->rendercolor = pev->rendercolor;
		}
	}
}

/* <1a2bb6> ../cstrike/dlls/triggers.cpp:583 */
LINK_ENTITY_TO_CLASS(trigger, CBaseTrigger);

/* <1a2c92> ../cstrike/dlls/triggers.cpp:590 */
void CBaseTrigger::InitTrigger(void)
{
	// trigger angles are used for one-way touches.  An angle of 0 is assumed
	// to mean no restrictions, so use a yaw of 360 instead.
	if (pev->angles != g_vecZero)
	{
		SetMovedir(pev);
	}

	pev->solid = SOLID_TRIGGER;
	pev->movetype = MOVETYPE_NONE;

	// set size and link into world
	SET_MODEL(ENT(pev), STRING(pev->model));

	if (CVAR_GET_FLOAT("showtriggers") == 0)
	{
		pev->effects |= EF_NODRAW;
	}
}

// Cache user-entity-field values until spawn is called.

/* <1a17cf> ../cstrike/dlls/triggers.cpp:608 */
void CBaseTrigger::__MAKE_VHOOK(KeyValue)(KeyValueData *pkvd)
{
	if (FStrEq(pkvd->szKeyName, "damage"))
	{
		pev->dmg = Q_atof(pkvd->szValue);
		pkvd->fHandled = TRUE;
	}
	else if (FStrEq(pkvd->szKeyName, "count"))
	{
		m_cTriggersLeft = (int)Q_atof(pkvd->szValue);
		pkvd->fHandled = TRUE;
	}
	else if (FStrEq(pkvd->szKeyName, "damagetype"))
	{
		m_bitsDamageInflict = Q_atoi(pkvd->szValue);
		pkvd->fHandled = TRUE;
	}
	else
		CBaseToggle::KeyValue(pkvd);
}

/* <1a3060> ../cstrike/dlls/triggers.cpp:636 */
LINK_ENTITY_TO_CLASS(trigger_hurt, CTriggerHurt);

/* <1a313c> ../cstrike/dlls/triggers.cpp:649 */
LINK_ENTITY_TO_CLASS(trigger_monsterjump, CTriggerMonsterJump);

/* <1a2fdc> ../cstrike/dlls/triggers.cpp:652 */
void CTriggerMonsterJump::__MAKE_VHOOK(Spawn)(void)
{
	SetMovedir(pev);

	InitTrigger();

	pev->nextthink = 0;
	pev->speed = 200;
	m_flHeight = 150;

	if (!FStringNull(pev->targetname))
	{
		// if targetted, spawn turned off
		pev->solid = SOLID_NOT;

		// Unlink from trigger list
		UTIL_SetOrigin(pev, pev->origin);
		SetUse(&CTriggerMonsterJump::ToggleUse);
	}
}

/* <1a00e4> ../cstrike/dlls/triggers.cpp:671 */
void CTriggerMonsterJump::__MAKE_VHOOK(Think)(void)
{
	// kill the trigger for now !!!UNDONE
	pev->solid = SOLID_NOT;

	// Unlink from trigger list
	UTIL_SetOrigin(pev, pev->origin);
	SetThink(NULL);
}

/* <19fca2> ../cstrike/dlls/triggers.cpp:678 */
void CTriggerMonsterJump::__MAKE_VHOOK(Touch)(CBaseEntity *pOther)
{
	entvars_t *pevOther = pOther->pev;

	if (!(pevOther->flags & FL_MONSTER))
	{
		// touched by a non-monster.
		return;
	}

	pevOther->origin.z += 1;

	if ((pevOther->flags & FL_ONGROUND))
	{
		// clear the onground so physics don't bitch
		pevOther->flags &= ~FL_ONGROUND;
	}

	// toss the monster!
	pevOther->velocity = pev->movedir * pev->speed;
	pevOther->velocity.z += m_flHeight;
	pev->nextthink = gpGlobals->time;
}

/* <1a3218> ../cstrike/dlls/triggers.cpp:715 */
LINK_ENTITY_TO_CLASS(trigger_cdaudio, CTriggerCDAudio);

// Changes tracks or stops CD when player touches
// !!!HACK - overloaded HEALTH to avoid adding new field

/* <1a2382> ../cstrike/dlls/triggers.cpp:721 */
void CTriggerCDAudio::__MAKE_VHOOK(Touch)(CBaseEntity *pOther)
{
	// only clients may trigger these events
	if (!pOther->IsPlayer())
	{
		return;
	}

	PlayTrack();
}

/* <1a2fb4> ../cstrike/dlls/triggers.cpp:731 */
void CTriggerCDAudio::__MAKE_VHOOK(Spawn)(void)
{
	InitTrigger();
}

/* <1a2288> ../cstrike/dlls/triggers.cpp:736 */
void CTriggerCDAudio::__MAKE_VHOOK(Use)(CBaseEntity *pActivator, CBaseEntity *pCaller, USE_TYPE useType, float value)
{
	PlayTrack();
}

/* <19e08b> ../cstrike/dlls/triggers.cpp:741 */
void PlayCDTrack(int iTrack)
{
	edict_t *pClient;

	// manually find the single player.
	pClient = INDEXENT(1);

	// Can't play if the client is not connected!
	if (!pClient)
		return;

	if (iTrack < -1 || iTrack > 30)
	{
		ALERT(at_console, "TriggerCDAudio - Track %d out of range\n");
		return;
	}

	if (iTrack == -1)
	{
		CLIENT_COMMAND(pClient, "cd stop\n");
	}
	else
	{
		char string[64];
		Q_sprintf(string, "cd play %3d\n", iTrack);
		CLIENT_COMMAND(pClient, string);
	}

}

// only plays for ONE client, so only use in single play!

/* <1a3372> ../cstrike/dlls/triggers.cpp:773 */
void CTriggerCDAudio::PlayTrack(void)
{
	PlayCDTrack((int)pev->health);

	SetTouch(NULL);
	UTIL_Remove(this);
}

/* <1a340c> ../cstrike/dlls/triggers.cpp:794 */
LINK_ENTITY_TO_CLASS(target_cdaudio, CTargetCDAudio);

/* <1a170f> ../cstrike/dlls/triggers.cpp:796 */
void CTargetCDAudio::__MAKE_VHOOK(KeyValue)(KeyValueData *pkvd)
{
	if (FStrEq(pkvd->szKeyName, "radius"))
	{
		pev->scale = Q_atof(pkvd->szValue);
		pkvd->fHandled = TRUE;
	}
	else
		CPointEntity::KeyValue(pkvd);
}

/* <1a066a> ../cstrike/dlls/triggers.cpp:807 */
void CTargetCDAudio::__MAKE_VHOOK(Spawn)(void)
{
	pev->solid = SOLID_NOT;
	pev->movetype = MOVETYPE_NONE;

	if (pev->scale > 0)
	{
		pev->nextthink = gpGlobals->time + 1.0;
	}
}

/* <1a2175> ../cstrike/dlls/triggers.cpp:816 */
void CTargetCDAudio::__MAKE_VHOOK(Use)(CBaseEntity *pActivator, CBaseEntity *pCaller, USE_TYPE useType, float value)
{
	Play();
}

// only plays for ONE client, so only use in single play!

/* <1a2465> ../cstrike/dlls/triggers.cpp:822 */
void CTargetCDAudio::__MAKE_VHOOK(Think)(void)
{
	edict_t *pClient;

	// manually find the single player.
	pClient = INDEXENT(1);

	// Can't play if the client is not connected!
	if (!pClient)
		return;

	pev->nextthink = gpGlobals->time + 0.5;

	if ((pClient->v.origin - pev->origin).Length() <= pev->scale)
	{
		Play();
	}
}

/* <1a34e8> ../cstrike/dlls/triggers.cpp:840 */
void CTargetCDAudio::Play(void)
{
	PlayCDTrack((int)pev->health);
	UTIL_Remove(this);
}

/* <1a2f8b> ../cstrike/dlls/triggers.cpp:853 */
void CTriggerHurt::__MAKE_VHOOK(Spawn)(void)
{
	InitTrigger();
	SetTouch(&CTriggerHurt::HurtTouch);

	if (!FStringNull(pev->targetname))
	{
		SetUse(&CTriggerHurt::ToggleUse);
	}
	else
	{
		SetUse(NULL);
	}

	if (m_bitsDamageInflict & DMG_RADIATION)
	{
		SetThink(&CTriggerHurt::RadiationThink);
		pev->nextthink = gpGlobals->time + RANDOM_FLOAT(0.0, 0.5);
	}

	if (pev->spawnflags & SF_TRIGGER_HURT_START_OFF)
	{
		// if flagged to Start Turned Off, make trigger nonsolid.
		pev->solid = SOLID_NOT;
	}

	// Link into the list
	UTIL_SetOrigin(pev, pev->origin);
}

// trigger hurt that causes radiation will do a radius
// check and set the player's geiger counter level
// according to distance from center of trigger

/* <1a5df2> ../cstrike/dlls/triggers.cpp:883 */
void CTriggerHurt::RadiationThink(void)
{
	edict_t *pentPlayer;
	CBasePlayer *pPlayer = NULL;
	float_precision flRange;
	entvars_t *pevTarget;
	Vector vecSpot1;
	Vector vecSpot2;
	Vector vecRange;
	Vector origin;
	Vector view_ofs;

	// check to see if a player is in pvs
	// if not, continue

	// set origin to center of trigger so that this check works
	origin = pev->origin;
	view_ofs = pev->view_ofs;

	pev->origin = (pev->absmin + pev->absmax) * 0.5;
	pev->view_ofs = pev->view_ofs * 0.0;

	pentPlayer = FIND_CLIENT_IN_PVS(edict());

	pev->origin = origin;
	pev->view_ofs = view_ofs;

	// reset origin
	if (!FNullEnt(pentPlayer))
	{
		pPlayer = GetClassPtr((CBasePlayer *)VARS(pentPlayer));

		pevTarget = VARS(pentPlayer);

		// get range to player;
		vecSpot1 = (pev->absmin + pev->absmax) * 0.5;
		vecSpot2 = (pevTarget->absmin + pevTarget->absmax) * 0.5;

		vecRange = vecSpot1 - vecSpot2;
		flRange = vecRange.Length();

		// if player's current geiger counter range is larger
		// than range to this trigger hurt, reset player's
		// geiger counter range

		if (pPlayer->m_flgeigerRange >= flRange)
		{
			pPlayer->m_flgeigerRange = flRange;
		}
	}

	pev->nextthink = gpGlobals->time + 0.25;
}

// ToggleUse - If this is the USE function for a trigger, its state will toggle every time it's fired

/* <1a007c> ../cstrike/dlls/triggers.cpp:942 */
void CBaseTrigger::ToggleUse(CBaseEntity *pActivator, CBaseEntity *pCaller, USE_TYPE useType, float value)
{
	if (pev->solid == SOLID_NOT)
	{
		// if the trigger is off, turn it on
		pev->solid = SOLID_TRIGGER;

		// Force retouch
		gpGlobals->force_retouch++;
	}
	else
	{
		// turn the trigger off
		pev->solid = SOLID_NOT;
	}

	UTIL_SetOrigin(pev, pev->origin);
}

// When touched, a hurt trigger does DMG points of damage each half-second

/* <1a0d93> ../cstrike/dlls/triggers.cpp:959 */
void CBaseTrigger::HurtTouch(CBaseEntity *pOther)
{
	float fldmg;

	if (!pOther->pev->takedamage)
	{
		return;
	}

	if ((pev->spawnflags & SF_TRIGGER_HURT_CLIENTONLYTOUCH) && !pOther->IsPlayer())
	{
		// this trigger is only allowed to touch clients, and this ain't a client.
		return;
	}

	if ((pev->spawnflags & SF_TRIGGER_HURT_NO_CLIENTS) && pOther->IsPlayer())
	{
		return;
	}

	// HACKHACK -- In multiplayer, players touch this based on packet receipt.
	// So the players who send packets later aren't always hurt.  Keep track of
	// how much time has passed and whether or not you've touched that player
	if (g_pGameRules->IsMultiplayer())
	{
		if (pev->dmgtime > gpGlobals->time)
		{
			if (gpGlobals->time != pev->pain_finished)
			{
				// too early to hurt again, and not same frame with a different entity
				if (!pOther->IsPlayer())
				{
					return;
				}

				int playerMask = 1 << (pOther->entindex() - 1);

				// If I've already touched this player (this time), then bail out
				if (pev->impulse & playerMask)
					return;

				// Mark this player as touched
				// BUGBUG - There can be only 32 players!
				pev->impulse |= playerMask;
			}
		}
		else
		{
			// New clock, "un-touch" all players
			pev->impulse = 0;
			if (pOther->IsPlayer())
			{
				int playerMask = 1 << (pOther->entindex() - 1);

				// Mark this player as touched
				// BUGBUG - There can be only 32 players!
				pev->impulse |= playerMask;
			}
		}
	}
	else
	{
		// Original code -- single player
		if (pev->dmgtime > gpGlobals->time && gpGlobals->time != pev->pain_finished)
		{
			// too early to hurt again, and not same frame with a different entity
			return;
		}
	}

	// If this is time_based damage (poison, radiation), override the pev->dmg with a
	// default for the given damage type.  Monsters only take time-based damage
	// while touching the trigger.  Player continues taking damage for a while after
	// leaving the trigger

	// 0.5 seconds worth of damage, pev->dmg is damage/second
	fldmg = pev->dmg * 0.5;

	if (fldmg < 0)
	{
		pOther->TakeHealth(-fldmg, m_bitsDamageInflict);
	}
	else
	{
		pOther->TakeDamage(pev, pev, fldmg, m_bitsDamageInflict);
	}

	// Store pain time so we can get all of the other entities on this frame
	pev->pain_finished = gpGlobals->time;

	// Apply damage every half second
	// half second delay until this trigger can hurt toucher again
	pev->dmgtime = gpGlobals->time + 0.5;

	if (pev->target)
	{
		// trigger has a target it wants to fire.
		if (pev->spawnflags & SF_TRIGGER_HURT_CLIENTONLYFIRE)
		{
			// if the toucher isn't a client, don't fire the target!
			if (!pOther->IsPlayer())
			{
				return;
			}
		}

		SUB_UseTargets(pOther, USE_TOGGLE, 0);
		if (pev->spawnflags & SF_TRIGGER_HURT_TARGETONCE)
		{
			pev->target = 0;
		}
	}
}

/* <1a3582> ../cstrike/dlls/triggers.cpp:1086 */
LINK_ENTITY_TO_CLASS(trigger_multiple, CTriggerMultiple);

/* <1a2f67> ../cstrike/dlls/triggers.cpp:1089 */
void CTriggerMultiple::__MAKE_VHOOK(Spawn)(void)
{
	if (m_flWait == 0)
		m_flWait = 0.2;

	InitTrigger();

	assert(("trigger_multiple with health", pev->health == 0));

	//UTIL_SetOrigin(pev, pev->origin);
	//SET_MODEL(ENT(pev), STRING(pev->model));

	//if (pev->health > 0)
	//{
	//	if (pev->spawnflags & SPAWNFLAG_NOTOUCH)
	//	{
	//		ALERT(at_error, "trigger_multiple spawn: health and notouch don't make sense");
	//	}
	//	pev->max_health = pev->health;
	//	//UNDONE: where to get pfnDie from?
	//	pev->pfnDie = multi_killed;
	//	pev->takedamage = DAMAGE_YES;
	//	pev->solid = SOLID_BBOX;
	//	// make sure it links into the world
	//	UTIL_SetOrigin(pev, pev->origin);
	//}
	//else
	{
			SetTouch(&CTriggerMultiple::MultiTouch);
	}
}

/* <1a365e> ../cstrike/dlls/triggers.cpp:1135 */
LINK_ENTITY_TO_CLASS(trigger_once, CTriggerOnce);

/* <1a301c> ../cstrike/dlls/triggers.cpp:1136 */
void CTriggerOnce::__MAKE_VHOOK(Spawn)(void)
{
	m_flWait = -1;
	CTriggerMultiple::Spawn();
}

/* <1a20a4> ../cstrike/dlls/triggers.cpp:1145 */
void CBaseTrigger::MultiTouch(CBaseEntity *pOther)
{
	entvars_t *pevToucher;

	pevToucher = pOther->pev;

	// Only touch clients, monsters, or pushables (depending on flags)
	if ((pevToucher->flags & FL_CLIENT && !(pev->spawnflags & SF_TRIGGER_NOCLIENTS))
		|| (pevToucher->flags & FL_MONSTER && (pev->spawnflags & SF_TRIGGER_ALLOWMONSTERS))
		|| (pev->spawnflags & SF_TRIGGER_PUSHABLES && FClassnameIs(pevToucher,"func_pushable")))
	{
		ActivateMultiTrigger(pOther);
	}
}

// the trigger was just touched/killed/used
// self.enemy should be set to the activator so it can be held through a delay
// so wait for the delay time before firing

/* <1a373a> ../cstrike/dlls/triggers.cpp:1167 */
void CBaseTrigger::ActivateMultiTrigger(CBaseEntity *pActivator)
{
	if (pev->nextthink > gpGlobals->time)
	{
		// still waiting for reset time
		return;
	}

	if (!UTIL_IsMasterTriggered(m_sMaster, pActivator))
	{
		return;
	}

	if (FClassnameIs(pev, "trigger_secret"))
	{
		if (pev->enemy == NULL || !FClassnameIs(pev->enemy, "player"))
			return;

		gpGlobals->found_secrets++;
	}

	if (!FStringNull(pev->noise))
	{
		EMIT_SOUND(ENT(pev), CHAN_VOICE, (char *)STRING(pev->noise), VOL_NORM, ATTN_NORM);
	}

	// don't trigger again until reset
	// pev->takedamage = DAMAGE_NO;
	m_hActivator = pActivator;
	SUB_UseTargets(m_hActivator, USE_TOGGLE, 0);

	if (pev->message && pActivator->IsPlayer())
	{
		UTIL_ShowMessage(STRING(pev->message), pActivator);
	}

	if (m_flWait > 0)
	{
		SetThink(&CBaseTrigger::MultiWaitOver);
		pev->nextthink = gpGlobals->time + m_flWait;
	}
	else
	{
		// we can't just remove (self) here, because this is a touch function
		// called while C code is looping through area links...
		SetTouch(NULL);
		pev->nextthink = gpGlobals->time + 0.1;
		SetThink(&CBaseTrigger::SUB_Remove);
	}
}

// the wait time has passed, so set back up for another activation

/* <19fd1a> ../cstrike/dlls/triggers.cpp:1214 */
void CBaseTrigger::MultiWaitOver(void)
{
	SetThink(NULL);
}

/* <1a1f98> ../cstrike/dlls/triggers.cpp:1231 */
void CBaseTrigger::CounterUse(CBaseEntity *pActivator, CBaseEntity *pCaller, USE_TYPE useType, float value)
{
	m_cTriggersLeft--;
	m_hActivator = pActivator;

	if (m_cTriggersLeft < 0)
	{
		return;
	}

	BOOL fTellActivator = (m_hActivator != 0 && FClassnameIs(m_hActivator->pev, "player") && !(pev->spawnflags & SPAWNFLAG_NOMESSAGE));

	if (m_cTriggersLeft != 0)
	{
		if (fTellActivator)
		{
			// UNDONE: I don't think we want these Quakesque messages
			switch (m_cTriggersLeft)
			{
			case 1: ALERT(at_console, "Only 1 more to go..."); break;
			case 2: ALERT(at_console, "Only 2 more to go..."); break;
			case 3: ALERT(at_console, "Only 3 more to go..."); break;
			default: ALERT(at_console, "There are more to go..."); break;
			}
		}

		return;
	}

	// !!!UNDONE: I don't think we want these Quakesque messages
	if (fTellActivator)
	{
		ALERT(at_console, "Sequence completed!");
	}

	ActivateMultiTrigger(m_hActivator);
}

/* <1a3767> ../cstrike/dlls/triggers.cpp:1278 */
LINK_ENTITY_TO_CLASS(trigger_counter, CTriggerCounter);

/* <19fd42> ../cstrike/dlls/triggers.cpp:1280 */
void CTriggerCounter::__MAKE_VHOOK(Spawn)(void)
{
	// By making the flWait be -1, this counter-trigger will disappear after it's activated
	// (but of course it needs cTriggersLeft "uses" before that happens).
	m_flWait = -1;

	if (m_cTriggersLeft == 0)
	{
		m_cTriggersLeft = 2;
	}

	SetUse(&CTriggerCounter::CounterUse);
}

/* <1a3843> ../cstrike/dlls/triggers.cpp:1299 */
LINK_ENTITY_TO_CLASS(trigger_transition, CTriggerVolume);

// Define space that travels across a level transition

/* <19fd6a> ../cstrike/dlls/triggers.cpp:1302 */
void CTriggerVolume::__MAKE_VHOOK(Spawn)(void)
{
	pev->solid = SOLID_NOT;
	pev->movetype = MOVETYPE_NONE;

	// set size and link into world
	SET_MODEL(ENT(pev), STRING(pev->model));

	pev->model = NULL;
	pev->modelindex = 0;
}

/* <1a3955> ../cstrike/dlls/triggers.cpp:1321 */
LINK_ENTITY_TO_CLASS(fireanddie, CFireAndDie);

/* <1a0618> ../cstrike/dlls/triggers.cpp:1323 */
void CFireAndDie::__MAKE_VHOOK(Spawn)(void)
{
	if (pev->classname)
	{
		RemoveEntityHashValue(pev, STRING(pev->classname), CLASSNAME);
	}

	MAKE_STRING_CLASS("fireanddie", pev);
	AddEntityHashValue(pev, STRING(pev->classname), CLASSNAME);
	// Don't call Precache() - it should be called on restore
}

/* <19fdbb> ../cstrike/dlls/triggers.cpp:1330 */
void CFireAndDie::__MAKE_VHOOK(Precache)(void)
{
	pev->nextthink = gpGlobals->time + m_flDelay;
}

/* <1a01ae> ../cstrike/dlls/triggers.cpp:1337 */
void CFireAndDie::__MAKE_VHOOK(Think)(void)
{
	SUB_UseTargets(this, USE_TOGGLE, 0);
	UTIL_Remove(this);
}

/* <1a3a67> ../cstrike/dlls/triggers.cpp:1371 */
LINK_ENTITY_TO_CLASS(trigger_changelevel, CChangeLevel);

/* <1a098d> ../cstrike/dlls/triggers.cpp:1382 */
IMPLEMENT_SAVERESTORE(CChangeLevel, CBaseTrigger);

// Cache user-entity-field values until spawn is called.

/* <1a1d4a> ../cstrike/dlls/triggers.cpp:1388 */
void CChangeLevel::__MAKE_VHOOK(KeyValue)(KeyValueData *pkvd)
{
	if (FStrEq(pkvd->szKeyName, "map"))
	{
		if (Q_strlen(pkvd->szValue) >= cchMapNameMost)
		{
			ALERT(at_error, "Map name '%s' too long (32 chars)\n", pkvd->szValue);
		}

		Q_strcpy(m_szMapName, pkvd->szValue);
		pkvd->fHandled = TRUE;
	}
	else if (FStrEq(pkvd->szKeyName, "landmark"))
	{
		if (Q_strlen(pkvd->szValue) >= cchMapNameMost)
		{
			ALERT(at_error, "Landmark name '%s' too long (32 chars)\n", pkvd->szValue);
		}

		Q_strcpy(m_szLandmarkName, pkvd->szValue);
		pkvd->fHandled = TRUE;
	}
	else if (FStrEq(pkvd->szKeyName, "changetarget"))
	{
		m_changeTarget = ALLOC_STRING(pkvd->szValue);
		pkvd->fHandled = TRUE;
	}
	else if (FStrEq(pkvd->szKeyName, "changedelay"))
	{
		m_changeTargetDelay = Q_atof(pkvd->szValue);
		pkvd->fHandled = TRUE;
	}
	else
		CBaseTrigger::KeyValue(pkvd);
}

/* <1a2f25> ../cstrike/dlls/triggers.cpp:1423 */
void CChangeLevel::__MAKE_VHOOK(Spawn)(void)
{
	if (FStrEq(m_szMapName, ""))
	{
		ALERT(at_console, "a trigger_changelevel doesn't have a map");
	}

	if (FStrEq(m_szLandmarkName, ""))
	{
		ALERT(at_console, "trigger_changelevel to %s doesn't have a landmark", m_szMapName);
	}

	if (!FStringNull(pev->targetname))
	{
		SetUse(&CChangeLevel::UseChangeLevel);
	}

	InitTrigger();
	if (!(pev->spawnflags & SF_CHANGELEVEL_USEONLY))
	{
		SetTouch(&CChangeLevel::TouchChangeLevel);
	}
}

/* <19fde3> ../cstrike/dlls/triggers.cpp:1441 */
void CChangeLevel::ExecuteChangeLevel(void)
{
	MESSAGE_BEGIN(MSG_ALL, SVC_CDTRACK);
		WRITE_BYTE(3);
		WRITE_BYTE(3);
	MESSAGE_END();

	MESSAGE_BEGIN(MSG_ALL, SVC_INTERMISSION);
	MESSAGE_END();
}

/* <1a3b43> ../cstrike/dlls/triggers.cpp:1456 */
edict_t *CChangeLevel::FindLandmark(const char *pLandmarkName)
{
	edict_t	*pentLandmark = FIND_ENTITY_BY_STRING(NULL, "targetname", pLandmarkName);
	while (!FNullEnt(pentLandmark))
	{
		// Found the landmark
		if (FClassnameIs(pentLandmark, "info_landmark"))
			return pentLandmark;
		else
			pentLandmark = FIND_ENTITY_BY_STRING(pentLandmark, "targetname", pLandmarkName);
	}

	ALERT(at_error, "Can't find landmark %s\n", pLandmarkName);
	return NULL;
}

// CChangeLevel::Use - allows level transitions to be
// triggered by buttons, etc.

/* <1a3e4f> ../cstrike/dlls/triggers.cpp:1479 */
void CChangeLevel::UseChangeLevel(CBaseEntity *pActivator, CBaseEntity *pCaller, USE_TYPE useType, float value)
{
	ChangeLevelNow(pActivator);
}

/* <1a3fb2> ../cstrike/dlls/triggers.cpp:1484 */
void CChangeLevel::ChangeLevelNow(CBaseEntity *pActivator)
{
	edict_t *pentLandmark;
	LEVELLIST levels[16];

	// Don't work in deathmatch
	if (g_pGameRules->IsDeathmatch())
	{
		return;
	}

	// Some people are firing these multiple times in a frame, disable
	if (gpGlobals->time == pev->dmgtime)
	{
		return;
	}

	pev->dmgtime = gpGlobals->time;

	CBaseEntity *pPlayer = CBaseEntity::Instance(INDEXENT(1));
	if (!InTransitionVolume(pPlayer, m_szLandmarkName))
	{
		ALERT(at_aiconsole, "Player isn't in the transition volume %s, aborting\n", m_szLandmarkName);
		return;
	}

	// Create an entity to fire the changetarget
	if (m_changeTarget)
	{
		CFireAndDie *pFireAndDie = GetClassPtr((CFireAndDie *)NULL);

		if (pFireAndDie)
		{
			// Set target and delay
			pFireAndDie->pev->target = m_changeTarget;
			pFireAndDie->m_flDelay = m_changeTargetDelay;
			pFireAndDie->pev->origin = pPlayer->pev->origin;

			// Call spawn
			DispatchSpawn(pFireAndDie->edict());
		}
	}

	// This object will get removed in the call to CHANGE_LEVEL, copy the params into "safe" memory
	Q_strcpy(st_szNextMap, m_szMapName);

	m_hActivator = pActivator;
	SUB_UseTargets(pActivator, USE_TOGGLE, 0);

	// Init landmark to NULL
	st_szNextSpot[0] = '\0';

	// look for a landmark entity
	pentLandmark = FindLandmark(m_szLandmarkName);

	if (!FNullEnt(pentLandmark))
	{
		Q_strcpy(st_szNextSpot, m_szLandmarkName);
		gpGlobals->vecLandmarkOffset = VARS(pentLandmark)->origin;
	}

	ALERT(at_console, "CHANGE LEVEL: %s %s\n", st_szNextMap, st_szNextSpot);
	CHANGE_LEVEL(st_szNextMap, st_szNextSpot);
}

/* <1a3ef5> ../cstrike/dlls/triggers.cpp:1545 */
void CChangeLevel::TouchChangeLevel(CBaseEntity *pOther)
{
	if (!FClassnameIs(pOther->pev, "player"))
	{
		return;
	}

	ChangeLevelNow(pOther);
}

// Add a transition to the list, but ignore duplicates
// (a designer may have placed multiple trigger_changelevels with the same landmark)

/* <1a3ff8> ../cstrike/dlls/triggers.cpp:1556 */
int CChangeLevel::AddTransitionToList(LEVELLIST *pLevelList, int listCount, const char *pMapName, const char *pLandmarkName, edict_t *pentLandmark)
{
	int i;

	if (!pLevelList || !pMapName || !pLandmarkName || !pentLandmark)
	{
		return 0;
	}

	for (i = 0; i < listCount; i++)
	{
		if (pLevelList[i].pentLandmark == pentLandmark && Q_strcmp(pLevelList[i].mapName, pMapName) == 0)
		{
			return 0;
		}
	}

	Q_strcpy(pLevelList[ listCount ].mapName, pMapName);
	Q_strcpy(pLevelList[ listCount ].landmarkName, pLandmarkName);

	pLevelList[ listCount ].pentLandmark = pentLandmark;
	pLevelList[ listCount ].vecLandmarkOrigin = VARS(pentLandmark)->origin;

	return 1;
}

/* <1a44ba> ../cstrike/dlls/triggers.cpp:1576 */
int BuildChangeList(LEVELLIST *pLevelList, int maxList)
{
	CChangeLevel::ChangeList(pLevelList, maxList);
}

/* <1a4075> ../cstrike/dlls/triggers.cpp:1582 */
int CChangeLevel::InTransitionVolume(CBaseEntity *pEntity, char *pVolumeName)
{
	edict_t	*pentVolume;

	if (pEntity->ObjectCaps() & FCAP_FORCE_TRANSITION)
	{
		return 1;
	}

	// If you're following another entity, follow it through the transition (weapons follow the player)
	if (pEntity->pev->movetype == MOVETYPE_FOLLOW)
	{
		if (pEntity->pev->aiment != NULL)
		{
			pEntity = CBaseEntity::Instance(pEntity->pev->aiment);
		}
	}

	// Unless we find a trigger_transition, everything is in the volume
	int inVolume = 1;

	pentVolume = FIND_ENTITY_BY_TARGETNAME(NULL, pVolumeName);
	while (!FNullEnt(pentVolume))
	{
		CBaseEntity *pVolume = CBaseEntity::Instance(pentVolume);

		if (pVolume && FClassnameIs(pVolume->pev, "trigger_transition"))
		{
			// It touches one, it's in the volume
			if (pVolume->Intersects(pEntity))
				return 1;
			else
			{
				// Found a trigger_transition, but I don't intersect it -- if I don't find another, don't go!
				inVolume = 0;
			}
		}

		pentVolume = FIND_ENTITY_BY_TARGETNAME(pentVolume, pVolumeName);
	}

	return inVolume;
}

// This has grown into a complicated beast
// Can we make this more elegant?
// This builds the list of all transitions on this level and which entities are in their PVS's and can / should
// be moved across.

/* <1a40b1> ../cstrike/dlls/triggers.cpp:1625 */
int CChangeLevel::ChangeList(LEVELLIST *pLevelList, int maxList)
{
	edict_t	*pentChangelevel, *pentLandmark;
	int i, count = 0;

	// Find all of the possible level changes on this BSP
	pentChangelevel = FIND_ENTITY_BY_STRING(NULL, "classname", "trigger_changelevel");

	if (FNullEnt(pentChangelevel))
		return 0;

	while (!FNullEnt(pentChangelevel))
	{
		CChangeLevel *pTrigger = GetClassPtr((CChangeLevel *)VARS(pentChangelevel));

		if (pTrigger != NULL)
		{
			// Find the corresponding landmark
			pentLandmark = FindLandmark(pTrigger->m_szLandmarkName);
			if (pentLandmark)
			{
				// Build a list of unique transitions
				if (AddTransitionToList(pLevelList, count, pTrigger->m_szMapName, pTrigger->m_szLandmarkName, pentLandmark))
				{
					count++;

					// FULL!!
					if (count >= maxList)
						break;
				}
			}
		}

		pentChangelevel = FIND_ENTITY_BY_STRING(pentChangelevel, "classname", "trigger_changelevel");
	}

	if (gpGlobals->pSaveData && ((SAVERESTOREDATA *)gpGlobals->pSaveData)->pTable)
	{
		CSave saveHelper((SAVERESTOREDATA *)gpGlobals->pSaveData);

		for (i = 0; i < count; i++)
		{
			int j, entityCount = 0;
			CBaseEntity *pEntList[ MAX_ENTITY ];
			int entityFlags[ MAX_ENTITY ];

			// Follow the linked list of entities in the PVS of the transition landmark
			edict_t *pent = FIND_ENTITY_IN_PVS(pLevelList[i].pentLandmark);

			// Build a list of valid entities in this linked list (we're going to use pent->v.chain again)
			while (!FNullEnt(pent))
			{
				CBaseEntity *pEntity = CBaseEntity::Instance(pent);
				if (pEntity)
				{
					int caps = pEntity->ObjectCaps();

					if (!(caps & FCAP_DONT_SAVE))
					{
						int flags = 0;

						// If this entity can be moved or is global, mark it
						if (caps & FCAP_ACROSS_TRANSITION)
							flags |= FENTTABLE_MOVEABLE;

						if (pEntity->pev->globalname && !pEntity->IsDormant())
							flags |= FENTTABLE_GLOBAL;

						if (flags)
						{
							pEntList[ entityCount ] = pEntity;
							entityFlags[ entityCount ] = flags;
							entityCount++;

							if (entityCount > MAX_ENTITY)
							{
								ALERT(at_error, "Too many entities across a transition!");
							}
						}
					}
				}
				pent = pent->v.chain;
			}

			for (j = 0; j < entityCount; j++)
			{
				// Check to make sure the entity isn't screened out by a trigger_transition
				if (entityFlags[j] && InTransitionVolume(pEntList[j], pLevelList[i].landmarkName))
				{
					// Mark entity table with 1<<i
					int index = saveHelper.EntityIndex(pEntList[j]);
					// Flag it with the level number
					saveHelper.EntityFlagsSet(index, entityFlags[j] | (1 << i));
				}
			}
		}
	}

	return count;
}

// go to the next level for deathmatch
// only called if a time or frag limit has expired

/* <1a44fc> ../cstrike/dlls/triggers.cpp:1722 */
NOXREF void NextLevel(void)
{
	edict_t *pent;
	CChangeLevel *pChange;

	// find a trigger_changelevel
	pent = FIND_ENTITY_BY_CLASSNAME(NULL, "trigger_changelevel");

	// go back to start if no trigger_changelevel
	if (FNullEnt(pent))
	{
		gpGlobals->mapname = ALLOC_STRING("start");
		pChange = GetClassPtr((CChangeLevel *)NULL);
		Q_strcpy(pChange->m_szMapName, "start");
	}
	else
		pChange = GetClassPtr((CChangeLevel *)VARS(pent));

	Q_strcpy(st_szNextMap, pChange->m_szMapName);
	g_fGameOver = TRUE;

	if (pChange->pev->nextthink < gpGlobals->time)
	{
		pChange->SetThink(&CChangeLevel::ExecuteChangeLevel);
		pChange->pev->nextthink = gpGlobals->time + 0.1;
	}
}

/* <1a4709> ../cstrike/dlls/triggers.cpp:1760 */
LINK_ENTITY_TO_CLASS(func_ladder, CLadder);

/* <1a1937> ../cstrike/dlls/triggers.cpp:1763 */
void CLadder::__MAKE_VHOOK(KeyValue)(KeyValueData *pkvd)
{
	CBaseTrigger::KeyValue(pkvd);
}

// func_ladder - makes an area vertically negotiable

/* <19fe6c> ../cstrike/dlls/triggers.cpp:1772 */
void CLadder::__MAKE_VHOOK(Precache)(void)
{
	// Do all of this in here because we need to 'convert' old saved games
	pev->solid = SOLID_NOT;
	pev->skin = CONTENTS_LADDER;

	if (CVAR_GET_FLOAT("showtriggers") == 0)
	{
		pev->rendermode = kRenderTransTexture;
		pev->renderamt = 0;
	}

	pev->effects &= ~EF_NODRAW;
}

/* <19fe95> ../cstrike/dlls/triggers.cpp:1786 */
void CLadder::__MAKE_VHOOK(Spawn)(void)
{
	Precache();

	// set size and link into world
	SET_MODEL(ENT(pev), STRING(pev->model));
	pev->movetype = MOVETYPE_PUSH;
}

/* <1a47e5> ../cstrike/dlls/triggers.cpp:1804 */
LINK_ENTITY_TO_CLASS(trigger_push, CTriggerPush);

/* <1a18ff> ../cstrike/dlls/triggers.cpp:1807 */
void CTriggerPush::__MAKE_VHOOK(KeyValue)(KeyValueData *pkvd)
{
	CBaseTrigger::KeyValue(pkvd);
}

/* <1a2eda> ../cstrike/dlls/triggers.cpp:1817 */
void CTriggerPush::__MAKE_VHOOK(Spawn)(void)
{
	if (pev->angles == g_vecZero)
	{
		pev->angles.y = 360;
	}

	InitTrigger();

	if (pev->speed == 0)
	{
		pev->speed = 100;
	}

	// if flagged to Start Turned Off, make trigger nonsolid.
	if (pev->spawnflags & SF_TRIGGER_PUSH_START_OFF)
	{
		pev->solid = SOLID_NOT;
	}

	SetUse(&CTriggerPush::ToggleUse);

	// Link into the list
	UTIL_SetOrigin(pev, pev->origin);
}

/* <1a023c> ../cstrike/dlls/triggers.cpp:1835 */
void CTriggerPush::__MAKE_VHOOK(Touch)(CBaseEntity *pOther)
{
	entvars_t *pevToucher = pOther->pev;

	// UNDONE: Is there a better way than health to detect things that have physics? (clients/monsters)
	switch (pevToucher->movetype)
	{
	case MOVETYPE_NONE:
	case MOVETYPE_PUSH:
	case MOVETYPE_NOCLIP:
	case MOVETYPE_FOLLOW:
		return;
	}

	if (pevToucher->solid != SOLID_NOT && pevToucher->solid != SOLID_BSP)
	{
		// Instant trigger, just transfer velocity and remove
		if (pev->spawnflags & SF_TRIG_PUSH_ONCE)
		{
			pevToucher->velocity = pevToucher->velocity + (pev->speed * pev->movedir);

			if (pevToucher->velocity.z > 0)
			{
				pevToucher->flags &= ~FL_ONGROUND;
			}

			UTIL_Remove(this);
		}
		else
		{
			// Push field, transfer to base velocity
			Vector vecPush = (pev->speed * pev->movedir);
			if (pevToucher->flags & FL_BASEVELOCITY)
			{
				vecPush = vecPush +  pevToucher->basevelocity;
			}

			pevToucher->basevelocity = vecPush;
			pevToucher->flags |= FL_BASEVELOCITY;
		}
	}
}

/* <1a051f> ../cstrike/dlls/triggers.cpp:1878 */
void CBaseTrigger::TeleportTouch(CBaseEntity *pOther)
{
	entvars_t *pevToucher = pOther->pev;
	edict_t	*pentTarget = NULL;

	// Only teleport monsters or clients
	if (!(pevToucher->flags & (FL_CLIENT | FL_MONSTER)))
	{
		return;
	}

	if (!UTIL_IsMasterTriggered(m_sMaster, pOther))
	{
		return;
	}

	if (!(pev->spawnflags & SF_TRIGGER_ALLOWMONSTERS))
	{
		// no monsters allowed!
		if (pevToucher->flags & FL_MONSTER)
		{
			return;
		}
	}

	if ((pev->spawnflags & SF_TRIGGER_NOCLIENTS))
	{
		// no clients allowed
		if (pOther->IsPlayer())
		{
			return;
		}
	}

	pentTarget = FIND_ENTITY_BY_TARGETNAME(pentTarget, STRING(pev->target));
	if (FNullEnt(pentTarget))
	{
		return;
	}

	Vector tmp = VARS(pentTarget)->origin;

	if (pOther->IsPlayer())
	{
		// make origin adjustments in case the teleportee is a player. (origin in center, not at feet)
		tmp.z -= pOther->pev->mins.z;
	}

	tmp.z++;

	pevToucher->flags &= ~FL_ONGROUND;

	UTIL_SetOrigin(pevToucher, tmp);

	pevToucher->angles = pentTarget->v.angles;

	if (pOther->IsPlayer())
	{
		pevToucher->v_angle = pentTarget->v.angles;
	}

	pevToucher->fixangle = 1;
	pevToucher->velocity = pevToucher->basevelocity = g_vecZero;
}

/* <1a48c1> ../cstrike/dlls/triggers.cpp:1940 */
LINK_ENTITY_TO_CLASS(trigger_teleport, CTriggerTeleport);

/* <1a2eb1> ../cstrike/dlls/triggers.cpp:1942 */
void CTriggerTeleport::__MAKE_VHOOK(Spawn)(void)
{
	InitTrigger();
	SetTouch(&CTriggerTeleport::TeleportTouch);
}

/* <1a499d> ../cstrike/dlls/triggers.cpp:1950 */
LINK_ENTITY_TO_CLASS(info_teleport_destination, CPointEntity);

/* <1a4a79> ../cstrike/dlls/triggers.cpp:1970 */
LINK_ENTITY_TO_CLASS(func_buyzone, CBuyZone);

/* <1a2e71> ../cstrike/dlls/triggers.cpp:1973 */
void CBuyZone::__MAKE_VHOOK(Spawn)(void)
{
	InitTrigger();
	SetTouch(&CBuyZone::BuyTouch);

	if (pev->team > CT || pev->team < UNASSIGNED)
	{
		ALERT(at_console, "Bad team number (%i) in func_buyzone\n", pev->team);
		pev->team = UNASSIGNED;
	}
}

/* <1a116b> ../cstrike/dlls/triggers.cpp:1986 */
void CBuyZone::BuyTouch(CBaseEntity *pOther)
{
	if (!pOther->IsPlayer())
		return;

	CBasePlayer *p = reinterpret_cast<CBasePlayer *>(pOther);

	if (pev->team == UNASSIGNED || pev->team == p->m_iTeam)
	{
		p->m_signals.Signal(SIGNAL_BUY);
	}
}

/* <1a4b55> ../cstrike/dlls/triggers.cpp:2016 */
LINK_ENTITY_TO_CLASS(func_bomb_target, CBombTarget);

/* <1a2e48> ../cstrike/dlls/triggers.cpp:2019 */
void CBombTarget::__MAKE_VHOOK(Spawn)(void)
{
	InitTrigger();

	SetTouch(&CBombTarget::BombTargetTouch);
	SetUse(&CBombTarget::BombTargetUse);
}

/* <1a10c1> ../cstrike/dlls/triggers.cpp:2027 */
void CBombTarget::BombTargetTouch(CBaseEntity *pOther)
{
	if (!pOther->IsPlayer())
		return;

	CBasePlayer *p = reinterpret_cast<CBasePlayer *>(pOther);

	if (p->m_bHasC4)
	{
		p->m_signals.Signal(SIGNAL_BOMB);
		p->m_pentCurBombTarget = ENT(pev);
	}
}

/* <1a0014> ../cstrike/dlls/triggers.cpp:2042 */
void CBombTarget::BombTargetUse(CBaseEntity *pActivator, CBaseEntity *pCaller, USE_TYPE useType, float value)
{
	SUB_UseTargets(NULL, USE_TOGGLE, 0);
}

/* <1a4c31> ../cstrike/dlls/triggers.cpp:2064 */
LINK_ENTITY_TO_CLASS(func_hostage_rescue, CHostageRescue);

/* <1a2e1f> ../cstrike/dlls/triggers.cpp:2067 */
void CHostageRescue::__MAKE_VHOOK(Spawn)(void)
{
	InitTrigger();
	SetTouch(&CHostageRescue::HostageRescueTouch);
}

/* <19ffbf> ../cstrike/dlls/triggers.cpp:2074 */
void CHostageRescue::HostageRescueTouch(CBaseEntity *pOther)
{
	if (pOther->IsPlayer())
	{
		((CBasePlayer *)pOther)->m_signals.Signal(SIGNAL_RESCUE);
	}

	if (FClassnameIs(pOther->pev, "hostage_entity"))
	{
		((CHostage *)pOther)->m_bRescueMe = TRUE;
	}
}

/* <1a4d0d> ../cstrike/dlls/triggers.cpp:2105 */
LINK_ENTITY_TO_CLASS(func_escapezone, CEscapeZone);

/* <1a2df6> ../cstrike/dlls/triggers.cpp:2108 */
void CEscapeZone::__MAKE_VHOOK(Spawn)(void)
{
	InitTrigger();
	SetTouch(&CEscapeZone::EscapeTouch);
}

/* <1a0f88> ../cstrike/dlls/triggers.cpp:2115 */
void CEscapeZone::EscapeTouch(CBaseEntity *pOther)
{
	if (!pOther->IsPlayer())
		return;

	CBasePlayer *p = reinterpret_cast<CBasePlayer *>(pOther);

	switch (p->m_iTeam)
	{
	case TERRORIST:
		if (!p->m_bEscaped)
		{
			p->m_bEscaped = true;
			g_pGameRules->CheckWinConditions();

			UTIL_LogPrintf
			(
				"\"%s<%i><%s><TERRORIST>\" triggered \"Terrorist_Escaped\"\n",
				STRING(p->pev->netname),
				GETPLAYERUSERID(p->edict()),
				GETPLAYERAUTHID(p->edict())
			);

			for (int i = 1; i <= gpGlobals->maxClients; i++)
			{
				CBasePlayer *pPlayer = reinterpret_cast<CBasePlayer *>(UTIL_PlayerByIndex(i));

				if (pPlayer == NULL || FNullEnt(pPlayer->pev))
					continue;

				if (pPlayer->m_iTeam == p->m_iTeam)
				{
					ClientPrint(pPlayer->pev, HUD_PRINTCENTER, "#Terrorist_Escaped");
				}
			}
		}
		break;
	case CT:
		p->m_signals.Signal(SIGNAL_ESCAPE);
		break;
	}
}

/* <1a4de9> ../cstrike/dlls/triggers.cpp:2163 */
LINK_ENTITY_TO_CLASS(func_vip_safetyzone, CVIP_SafetyZone);

/* <1a2dcd> ../cstrike/dlls/triggers.cpp:2166 */
void CVIP_SafetyZone::__MAKE_VHOOK(Spawn)(void)
{
	InitTrigger();
	SetTouch(&CVIP_SafetyZone::VIP_SafetyTouch);
}

/* <1a0ec7> ../cstrike/dlls/triggers.cpp:2173 */
void CVIP_SafetyZone::VIP_SafetyTouch(CBaseEntity *pOther)
{
	if (!pOther->IsPlayer())
		return;

	CBasePlayer *p = reinterpret_cast<CBasePlayer *>(pOther);
	p->m_signals.Signal(SIGNAL_VIPSAFETY);

	if (p->m_bIsVIP)
	{
		UTIL_LogPrintf
		(
			"\"%s<%i><%s><CT>\" triggered \"Escaped_As_VIP\"\n",
			STRING(p->pev->netname),
			GETPLAYERUSERID(p->edict()),
			GETPLAYERAUTHID(p->edict())
		);

		p->m_bEscaped = true;

		p->Disappear();
		p->AddAccount(REWARD_VIP_HAVE_SELF_RESCUED);
	}
}

/* <1a4ec5> ../cstrike/dlls/triggers.cpp:2204 */
LINK_ENTITY_TO_CLASS(trigger_autosave, CTriggerSave);

/* <1a2d8e> ../cstrike/dlls/triggers.cpp:2206 */
void CTriggerSave::__MAKE_VHOOK(Spawn)(void)
{
	if (g_pGameRules->IsDeathmatch())
	{
		REMOVE_ENTITY(ENT(pev));
		return;
	}

	InitTrigger();
	SetTouch(&CTriggerSave::SaveTouch);
}

/* <1a0c01> ../cstrike/dlls/triggers.cpp:2218 */
void CTriggerSave::SaveTouch(CBaseEntity *pOther)
{
	if (!UTIL_IsMasterTriggered(m_sMaster, pOther))
		return;

	// Only save on clients
	if (!pOther->IsPlayer())
		return;

	SetTouch(NULL);
	UTIL_Remove(this);
	SERVER_COMMAND("autosave\n");
}

/* <1a4fa1> ../cstrike/dlls/triggers.cpp:2242 */
LINK_ENTITY_TO_CLASS(trigger_endsection, CTriggerEndSection);

/* <1a0b7f> ../cstrike/dlls/triggers.cpp:2245 */
void CTriggerEndSection::EndSectionUse(CBaseEntity *pActivator, CBaseEntity *pCaller, USE_TYPE useType, float value)
{
	// Only save on clients
	if (pActivator && !pActivator->IsNetClient())
		return;

	SetUse(NULL);
	if (!FStringNull(pev->message))
	{
		END_SECTION(STRING(pev->message));
	}

	UTIL_Remove(this);
}

/* <1a2d4f> ../cstrike/dlls/triggers.cpp:2260 */
void CTriggerEndSection::__MAKE_VHOOK(Spawn)(void)
{
	if (g_pGameRules->IsDeathmatch())
	{
		REMOVE_ENTITY(ENT(pev));
		return;
	}

	InitTrigger();
	SetUse(&CTriggerEndSection::EndSectionUse);

	// If it is a "use only" trigger, then don't set the touch function.
	if (!(pev->spawnflags & SF_ENDSECTION_USEONLY))
	{
		SetTouch(&CTriggerEndSection::EndSectionTouch);
	}
}

/* <1a0b29> ../cstrike/dlls/triggers.cpp:2276 */
void CTriggerEndSection::EndSectionTouch(CBaseEntity *pOther)
{
	// Only save on clients
	if (!pOther->IsNetClient())
		return;

	SetTouch(NULL);
	if (!FStringNull(pev->message))
	{
		END_SECTION(STRING(pev->message));
	}

	UTIL_Remove(this);
}

/* <1a196f> ../cstrike/dlls/triggers.cpp:2291 */
void CTriggerEndSection::__MAKE_VHOOK(KeyValue)(KeyValueData *pkvd)
{
	if (FStrEq(pkvd->szKeyName, "section"))
	{
		// Store this in message so we don't have to write save/restore for this ent
		pev->message = ALLOC_STRING(pkvd->szValue);
		pkvd->fHandled = TRUE;
	}
	else
		CBaseTrigger::KeyValue(pkvd);
}

/* <1a507d> ../cstrike/dlls/triggers.cpp:2311 */
LINK_ENTITY_TO_CLASS(trigger_gravity, CTriggerGravity);

/* <1a2d26> ../cstrike/dlls/triggers.cpp:2313 */
void CTriggerGravity::__MAKE_VHOOK(Spawn)(void)
{
	InitTrigger();
	SetTouch(&CTriggerGravity::GravityTouch);
}

/* <19febe> ../cstrike/dlls/triggers.cpp:2319 */
void CTriggerGravity::GravityTouch(CBaseEntity *pOther)
{
	// Only save on clients
	if (!pOther->IsPlayer())
		return;

	pOther->pev->gravity = pev->gravity;
}

/* <1a5159> ../cstrike/dlls/triggers.cpp:2351 */
LINK_ENTITY_TO_CLASS(trigger_changetarget, CTriggerChangeTarget);

/* <1a093a> ../cstrike/dlls/triggers.cpp:2358 */
IMPLEMENT_SAVERESTORE(CTriggerChangeTarget, CBaseDelay);

/* <1a1691> ../cstrike/dlls/triggers.cpp:2360 */
void CTriggerChangeTarget::__MAKE_VHOOK(KeyValue)(KeyValueData *pkvd)
{
	if (FStrEq(pkvd->szKeyName, "m_iszNewTarget"))
	{
		m_iszNewTarget = ALLOC_STRING(pkvd->szValue);
		pkvd->fHandled = TRUE;
	}
	else
		CBaseDelay::KeyValue(pkvd);
}

/* <19ff1f> ../cstrike/dlls/triggers.cpp:2371 */
void CTriggerChangeTarget::__MAKE_VHOOK(Spawn)(void)
{
	;
}

/* <1a010d> ../cstrike/dlls/triggers.cpp:2376 */
void CTriggerChangeTarget::__MAKE_VHOOK(Use)(CBaseEntity *pActivator, CBaseEntity *pCaller, USE_TYPE useType, float value)
{
	CBaseEntity *pTarget = UTIL_FindEntityByString(NULL, "targetname", STRING(pev->target));

	if (pTarget != NULL)
	{
		pTarget->pev->target = m_iszNewTarget;

		CBaseMonster *pMonster = pTarget->MyMonsterPointer();

		if (pMonster)
		{
			pMonster->m_pGoalEnt = NULL;
		}
	}
}

/* <1a5235> ../cstrike/dlls/triggers.cpp:2425 */
LINK_ENTITY_TO_CLASS(trigger_camera, CTriggerCamera);

/* <1a08e7> ../cstrike/dlls/triggers.cpp:2445 */
IMPLEMENT_SAVERESTORE(CTriggerCamera, CBaseDelay);

/* <19ff6f> ../cstrike/dlls/triggers.cpp:2447 */
void CTriggerCamera::__MAKE_VHOOK(Spawn)(void)
{
	pev->movetype = MOVETYPE_NOCLIP;

	// Remove model & collisions
	pev->solid = SOLID_NOT;

	// The engine won't draw this model if this is set to 0 and blending is on
	pev->renderamt = 0;
	pev->rendermode = kRenderTransTexture;

	m_initialSpeed = pev->speed;

	if (m_acceleration == 0)
	{
		m_acceleration = 500;
	}
	if (m_deceleration == 0)
	{
		m_deceleration = 500;
	}
}

/* <1a1537> ../cstrike/dlls/triggers.cpp:2462 */
void CTriggerCamera::__MAKE_VHOOK(KeyValue)(KeyValueData *pkvd)
{
	if (FStrEq(pkvd->szKeyName, "wait"))
	{
		m_flWait = Q_atof(pkvd->szValue);
		pkvd->fHandled = TRUE;
	}
	else if (FStrEq(pkvd->szKeyName, "moveto"))
	{
		m_sPath = ALLOC_STRING(pkvd->szValue);
		pkvd->fHandled = TRUE;
	}
	else if (FStrEq(pkvd->szKeyName, "acceleration"))
	{
		m_acceleration = Q_atof(pkvd->szValue);
		pkvd->fHandled = TRUE;
	}
	else if (FStrEq(pkvd->szKeyName, "deceleration"))
	{
		m_deceleration = Q_atof(pkvd->szValue);
		pkvd->fHandled = TRUE;
	}
	else
		CBaseDelay::KeyValue(pkvd);
}

/* <1a55e4> ../cstrike/dlls/triggers.cpp:2490 */
void CTriggerCamera::__MAKE_VHOOK(Use)(CBaseEntity *pActivator, CBaseEntity *pCaller, USE_TYPE useType, float value)
{
	if (!ShouldToggle(useType, m_state))
		return;

	// Toggle state
	m_state = !m_state;
	if (m_state == 0)
	{
		m_flReturnTime = gpGlobals->time;

		if (pActivator->IsPlayer())
		{
			((CBasePlayer *)pActivator)->ResetMaxSpeed();
		}

		return;
	}

	if (!pActivator || !pActivator->IsPlayer())
	{
		pActivator = CBaseEntity::Instance(INDEXENT(1));
	}

	m_hPlayer = pActivator;
	m_flReturnTime = gpGlobals->time + m_flWait;

	pev->speed = m_initialSpeed;
	m_targetSpeed = m_initialSpeed;

	if (pev->spawnflags & SF_CAMERA_PLAYER_TARGET)
	{
		m_hTarget = m_hPlayer;
	}
	else
	{
		m_hTarget = GetNextTarget();
	}

	// Nothing to look at!
	if (m_hTarget == NULL)
	{
		return;
	}

	if (pActivator->IsPlayer())
	{
		SET_CLIENT_MAXSPEED(pActivator->edict(), 0.001);
	}

	if (pev->spawnflags & SF_CAMERA_PLAYER_TAKECONTROL)
	{
		((CBasePlayer *)pActivator)->EnableControl(FALSE);
	}

	if (m_sPath)
	{
		m_pentPath = Instance(FIND_ENTITY_BY_TARGETNAME(NULL, STRING(m_sPath)));
	}
	else
	{
		m_pentPath = NULL;
	}

	m_flStopTime = gpGlobals->time;
	if (m_pentPath)
	{
		if (m_pentPath->pev->speed != 0)
			m_targetSpeed = m_pentPath->pev->speed;

		m_flStopTime += m_pentPath->GetDelay();
	}

	// copy over player information
	if (pev->spawnflags & SF_CAMERA_PLAYER_POSITION)
	{
		UTIL_SetOrigin(pev, pActivator->pev->origin + pActivator->pev->view_ofs);

		pev->angles.x = -pActivator->pev->angles.x;
		pev->angles.y = pActivator->pev->angles.y;
		pev->angles.z = 0;
		pev->velocity = pActivator->pev->velocity;
	}
	else
	{
		pev->velocity = Vector(0, 0, 0);
	}

	SET_VIEW(pActivator->edict(), edict());
	SET_MODEL(ENT(pev), STRING(pActivator->pev->model));

	// follow the player down
	SetThink(&CTriggerCamera::FollowTarget);

	pev->nextthink = gpGlobals->time;
	m_moveDistance = 0;
	Move();
}

/* <1a5494> ../cstrike/dlls/triggers.cpp:2587 */
void CTriggerCamera::FollowTarget(void)
{
	if (m_hPlayer == NULL)
		return;

	if (m_hTarget == NULL || m_flReturnTime < gpGlobals->time)
	{
		if (m_hPlayer->IsAlive())
		{
			SET_VIEW(m_hPlayer->edict(), m_hPlayer->edict());
			((CBasePlayer *)((CBaseEntity *)m_hPlayer))->EnableControl(TRUE);
		}

		SUB_UseTargets(this, USE_TOGGLE, 0);
		pev->avelocity = Vector(0, 0, 0);
		m_state = 0;
		return;
	}

	Vector vecGoal = UTIL_VecToAngles(m_hTarget->pev->origin - pev->origin);
	vecGoal.x = -vecGoal.x;

	if (pev->angles.y > 360)
		pev->angles.y -= 360;

	if (pev->angles.y < 0)
		pev->angles.y += 360;

	float_precision dx = vecGoal.x - pev->angles.x;
	float_precision dy = vecGoal.y - pev->angles.y;

	if (dx < -180)
		dx += 360;
	if (dx > 180)
		dx = dx - 360;

	if (dy < -180)
		dy += 360;
	if (dy > 180)
		dy = dy - 360;

	pev->avelocity.x = dx * 40 * gpGlobals->frametime;
	pev->avelocity.y = dy * 40 * gpGlobals->frametime;

	if (!(pev->spawnflags & SF_CAMERA_PLAYER_TAKECONTROL))
	{
		pev->velocity = pev->velocity * 0.8;

		if (pev->velocity.Length() < 10.0)
		{
			pev->velocity = g_vecZero;
		}
	}

	pev->nextthink = gpGlobals->time;
	Move();
}

/* <1a5311> ../cstrike/dlls/triggers.cpp:2644 */
void CTriggerCamera::Move(void)
{
	// Not moving on a path, return
	if (!m_pentPath)
		return;

	// Subtract movement from the previous frame
	m_moveDistance -= pev->speed * gpGlobals->frametime;

	// Have we moved enough to reach the target?
	if (m_moveDistance <= 0)
	{
		// Fire the passtarget if there is one
		if (!FStringNull(m_pentPath->pev->message))
		{
			FireTargets(STRING(m_pentPath->pev->message), this, this, USE_TOGGLE, 0);

			if (m_pentPath->pev->spawnflags & SF_CORNER_FIREONCE)
			{
				m_pentPath->pev->message = 0;
			}
		}

		// Time to go to the next target
		m_pentPath = m_pentPath->GetNextTarget();

		// Set up next corner
		if (!m_pentPath)
		{
			pev->velocity = g_vecZero;
		}
		else
		{
			if (m_pentPath->pev->speed != 0)
			{
				m_targetSpeed = m_pentPath->pev->speed;
			}

			Vector delta = m_pentPath->pev->origin - pev->origin;
			m_moveDistance = delta.Length();
			pev->movedir = delta.Normalize();
			m_flStopTime = gpGlobals->time + m_pentPath->GetDelay();
		}
	}

	if (m_flStopTime > gpGlobals->time)
	{
		pev->speed = UTIL_Approach(0, pev->speed, m_deceleration * gpGlobals->frametime);
	}
	else
	{
		pev->speed = UTIL_Approach(m_targetSpeed, pev->speed, m_acceleration * gpGlobals->frametime);
	}

	float_precision fraction = 2 * gpGlobals->frametime;
	pev->velocity = ((pev->movedir * pev->speed) * fraction) + (pev->velocity * (1 - fraction));
}

/* <1a5815> ../cstrike/dlls/triggers.cpp:2699 */
LINK_ENTITY_TO_CLASS(env_snow, CWeather);

/* <1a58f1> ../cstrike/dlls/triggers.cpp:2700 */
LINK_ENTITY_TO_CLASS(func_snow, CWeather);

/* <1a59cd> ../cstrike/dlls/triggers.cpp:2701 */
LINK_ENTITY_TO_CLASS(env_rain, CWeather);

/* <1a5aa9> ../cstrike/dlls/triggers.cpp:2702 */
LINK_ENTITY_TO_CLASS(func_rain, CWeather);

/* <1a2cfe> ../cstrike/dlls/triggers.cpp:2704 */
void CWeather::__MAKE_VHOOK(Spawn)(void)
{
	InitTrigger();
}

/* <1a1477> ../cstrike/dlls/triggers.cpp:2716 */
void CClientFog::__MAKE_VHOOK(KeyValue)(KeyValueData *pkvd)
{
#if 0
	if (FStrEq(pkvd->szKeyName, "startdist"))
	{
		m_iStartDist = Q_atoi(pkvd->szValue);
		pkvd->fHandled = TRUE;
	}
	else if (FStrEq(pkvd->szKeyName, "enddist"))
	{
		m_iEndDist = Q_atoi(pkvd->szValue);
		pkvd->fHandled = TRUE;
	}
	else
#endif
	if (FStrEq(pkvd->szKeyName, "density"))
	{
		m_fDensity = Q_atof(pkvd->szValue);

		if (m_fDensity < 0 || m_fDensity > 0.01)
			m_fDensity = 0;

		pkvd->fHandled = TRUE;
	}
	else
		CBaseEntity::KeyValue(pkvd);
}

/* <19ff97> ../cstrike/dlls/triggers.cpp:2735 */
void CClientFog::__MAKE_VHOOK(Spawn)(void)
{
	pev->movetype = MOVETYPE_NOCLIP;
	pev->solid = SOLID_NOT;				// Remove model & collisions
	pev->renderamt = 0;				// The engine won't draw this model if this is set to 0 and blending is on
	pev->rendermode = kRenderTransTexture;
}

/* <1a5ba9> ../cstrike/dlls/triggers.cpp:2744 */
LINK_ENTITY_TO_CLASS(env_fog, CClientFog);

#ifdef HOOK_GAMEDLL

void CFrictionModifier::Spawn(void)
{
	Spawn_();
}

void CFrictionModifier::KeyValue(KeyValueData *pkvd)
{
	KeyValue_(pkvd);
}

int CFrictionModifier::Save(CSave &save)
{
	return Save_(save);
}

int CFrictionModifier::Restore(CRestore &restore)
{
	return Restore_(restore);
}

void CAutoTrigger::Spawn(void)
{
	Spawn_();
}

void CAutoTrigger::Precache(void)
{
	Precache_();
}

void CAutoTrigger::KeyValue(KeyValueData *pkvd)
{
	KeyValue_(pkvd);
}

int CAutoTrigger::Save(CSave &save)
{
	return Save_(save);
}

int CAutoTrigger::Restore(CRestore &restore)
{
	return Restore_(restore);
}

void CAutoTrigger::Think(void)
{
	Think_();
}

void CTriggerRelay::Spawn(void)
{
	Spawn_();
}

void CTriggerRelay::KeyValue(KeyValueData *pkvd)
{
	KeyValue_(pkvd);
}

int CTriggerRelay::Save(CSave &save)
{
	return Save_(save);
}

int CTriggerRelay::Restore(CRestore &restore)
{
	return Restore_(restore);
}

void CTriggerRelay::Use(CBaseEntity *pActivator, CBaseEntity *pCaller, USE_TYPE useType, float value)
{
	Use_(pActivator, pCaller, useType, value);
}

void CMultiManager::Spawn(void)
{
	Spawn_();
}

void CMultiManager::Restart(void)
{
	Restart_();
}

void CMultiManager::KeyValue(KeyValueData *pkvd)
{
	KeyValue_(pkvd);
}

int CMultiManager::Save(CSave &save)
{
	return Save_(save);
}

int CMultiManager::Restore(CRestore &restore)
{
	return Restore_(restore);
}

BOOL CMultiManager::HasTarget(string_t targetname)
{
	return HasTarget_(targetname);
}

void CRenderFxManager::Spawn(void)
{
	Spawn_();
}

void CRenderFxManager::Use(CBaseEntity *pActivator, CBaseEntity *pCaller, USE_TYPE useType, float value)
{
	Use_(pActivator, pCaller, useType, value);
}

void CBaseTrigger::KeyValue(KeyValueData *pkvd)
{
	KeyValue_(pkvd);
}

void CTriggerHurt::Spawn(void)
{
	Spawn_();
}

void CTriggerMonsterJump::Spawn(void)
{
	Spawn_();
}

void CTriggerMonsterJump::Think(void)
{
	Think_();
}

void CTriggerMonsterJump::Touch(CBaseEntity *pOther)
{
	Touch_(pOther);
}

void CTriggerCDAudio::Spawn(void)
{
	Spawn_();
}

void CTriggerCDAudio::Touch(CBaseEntity *pOther)
{
	Touch_(pOther);
}

void CTriggerCDAudio::Use(CBaseEntity *pActivator, CBaseEntity *pCaller, USE_TYPE useType, float value)
{
	Use_(pActivator, pCaller, useType, value);
}

void CTargetCDAudio::Spawn(void)
{
	Spawn_();
}

void CTargetCDAudio::KeyValue(KeyValueData *pkvd)
{
	KeyValue_(pkvd);
}

void CTargetCDAudio::Think(void)
{
	Think_();
}

void CTargetCDAudio::Use(CBaseEntity *pActivator, CBaseEntity *pCaller, USE_TYPE useType, float value)
{
	Use_(pActivator, pCaller, useType, value);
}

void CTriggerMultiple::Spawn(void)
{
	Spawn_();
}

void CTriggerOnce::Spawn(void)
{
	Spawn_();
}

void CTriggerCounter::Spawn(void)
{
	Spawn_();
}

void CTriggerVolume::Spawn(void)
{
	Spawn_();
}

void CFireAndDie::Spawn(void)
{
	Spawn_();
}

void CFireAndDie::Precache(void)
{
	Precache_();
}

void CFireAndDie::Think(void)
{
	Think_();
}

void CChangeLevel::Spawn(void)
{
	Spawn_();
}

void CChangeLevel::KeyValue(KeyValueData *pkvd)
{
	KeyValue_(pkvd);
}

int CChangeLevel::Save(CSave &save)
{
	return Save_(save);
}

int CChangeLevel::Restore(CRestore &restore)
{
	return Restore_(restore);
}

void CLadder::Spawn(void)
{
	Spawn_();
}

void CLadder::Precache(void)
{
	Precache_();
}

void CLadder::KeyValue(KeyValueData *pkvd)
{
	KeyValue_(pkvd);
}

void CTriggerPush::Spawn(void)
{
	Spawn_();
}

void CTriggerPush::KeyValue(KeyValueData *pkvd)
{
	KeyValue_(pkvd);
}

void CTriggerPush::Touch(CBaseEntity *pOther)
{
	Touch_(pOther);
}

void CTriggerTeleport::Spawn(void)
{
	Spawn_();
}

void CBuyZone::Spawn(void)
{
	Spawn_();
}

void CBombTarget::Spawn(void)
{
	Spawn_();
}

void CHostageRescue::Spawn(void)
{
	Spawn_();
}

void CEscapeZone::Spawn(void)
{
	Spawn_();
}

void CVIP_SafetyZone::Spawn(void)
{
	Spawn_();
}

void CTriggerSave::Spawn(void)
{
	Spawn_();
}

void CTriggerEndSection::Spawn(void)
{
	Spawn_();
}

void CTriggerEndSection::KeyValue(KeyValueData *pkvd)
{
	KeyValue_(pkvd);
}

void CTriggerGravity::Spawn(void)
{
	Spawn_();
}

void CTriggerChangeTarget::Spawn(void)
{
	Spawn_();
}
void CTriggerChangeTarget::KeyValue(KeyValueData *pkvd)
{
	KeyValue_(pkvd);
}

int CTriggerChangeTarget::Save(CSave &save)
{
	return Save_(save);
}

int CTriggerChangeTarget::Restore(CRestore &restore)
{
	return Restore_(restore);
}

void CTriggerChangeTarget::Use(CBaseEntity *pActivator, CBaseEntity *pCaller, USE_TYPE useType, float value)
{
	Use_(pActivator, pCaller, useType, value);
}

void CTriggerCamera::Spawn(void)
{
	Spawn_();
}
void CTriggerCamera::KeyValue(KeyValueData *pkvd)
{
	KeyValue_(pkvd);
}

int CTriggerCamera::Save(CSave &save)
{
	return Save_(save);
}

int CTriggerCamera::Restore(CRestore &restore)
{
	return Restore_(restore);
}

void CTriggerCamera::Use(CBaseEntity *pActivator, CBaseEntity *pCaller, USE_TYPE useType, float value)
{
	Use_(pActivator, pCaller, useType, value);
}

void CClientFog::Spawn(void)
{
	Spawn_();
}
void CClientFog::KeyValue(KeyValueData *pkvd)
{
	KeyValue_(pkvd);
}

void CWeather::Spawn(void)
{
	Spawn_();
}

#endif // HOOK_GAMEDLL

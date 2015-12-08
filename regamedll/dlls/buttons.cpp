#include "precompiled.h"

/*
* Globals initialization
*/
#ifndef HOOK_GAMEDLL

TYPEDESCRIPTION CEnvGlobal::m_SaveData[] =
{
	DEFINE_FIELD(CEnvGlobal, m_globalstate, FIELD_STRING),
	DEFINE_FIELD(CEnvGlobal, m_triggermode, FIELD_INTEGER),
	DEFINE_FIELD(CEnvGlobal, m_initialstate, FIELD_INTEGER),
};

TYPEDESCRIPTION CMultiSource::m_SaveData[] =
{
	//!!!BUGBUG FIX
	DEFINE_ARRAY(CMultiSource, m_rgEntities, FIELD_EHANDLE, MS_MAX_TARGETS),
	DEFINE_ARRAY(CMultiSource, m_rgTriggered, FIELD_INTEGER, MS_MAX_TARGETS),
	DEFINE_FIELD(CMultiSource, m_iTotal, FIELD_INTEGER),
	DEFINE_FIELD(CMultiSource, m_globalstate, FIELD_STRING),
};

// CBaseButton
TYPEDESCRIPTION CBaseButton::m_SaveData[] =
{
	DEFINE_FIELD(CBaseButton, m_fStayPushed, FIELD_BOOLEAN),
	DEFINE_FIELD(CBaseButton, m_fRotating, FIELD_BOOLEAN),
	DEFINE_FIELD(CBaseButton, m_sounds, FIELD_INTEGER),
	DEFINE_FIELD(CBaseButton, m_bLockedSound, FIELD_CHARACTER),
	DEFINE_FIELD(CBaseButton, m_bLockedSentence, FIELD_CHARACTER),
	DEFINE_FIELD(CBaseButton, m_bUnlockedSound, FIELD_CHARACTER),
	DEFINE_FIELD(CBaseButton, m_bUnlockedSentence, FIELD_CHARACTER),
	DEFINE_FIELD(CBaseButton, m_strChangeTarget, FIELD_STRING),
//	DEFINE_FIELD(CBaseButton, m_ls, FIELD_???),   // This is restored in Precache()
};

TYPEDESCRIPTION CMomentaryRotButton::m_SaveData[] =
{
	DEFINE_FIELD(CMomentaryRotButton, m_lastUsed, FIELD_INTEGER),
	DEFINE_FIELD(CMomentaryRotButton, m_direction, FIELD_INTEGER),
	DEFINE_FIELD(CMomentaryRotButton, m_returnSpeed, FIELD_FLOAT),
	DEFINE_FIELD(CMomentaryRotButton, m_start, FIELD_VECTOR),
	DEFINE_FIELD(CMomentaryRotButton, m_end, FIELD_VECTOR),
	DEFINE_FIELD(CMomentaryRotButton, m_sounds, FIELD_INTEGER),
};

TYPEDESCRIPTION CEnvSpark::m_SaveData[] =
{
	DEFINE_FIELD(CEnvSpark, m_flDelay, FIELD_FLOAT),
};

#else

TYPEDESCRIPTION IMPL_CLASS(CEnvGlobal, m_SaveData)[3];
TYPEDESCRIPTION IMPL_CLASS(CMultiSource, m_SaveData)[4];
TYPEDESCRIPTION IMPL_CLASS(CBaseButton, m_SaveData)[8];
TYPEDESCRIPTION IMPL_CLASS(CMomentaryRotButton, m_SaveData)[6];
TYPEDESCRIPTION IMPL_CLASS(CEnvSpark, m_SaveData)[1];

#endif // HOOK_GAMEDLL

/* <260d6> ../cstrike/dlls/buttons.cpp:62 */
IMPLEMENT_SAVERESTORE(CEnvGlobal, CBaseEntity);

/* <272af> ../cstrike/dlls/buttons.cpp:64 */
LINK_ENTITY_TO_CLASS(env_global, CEnvGlobal);

/* <26863> ../cstrike/dlls/buttons.cpp:66 */
void CEnvGlobal::__MAKE_VHOOK(KeyValue)(KeyValueData *pkvd)
{
	pkvd->fHandled = TRUE;

	// State name
	if (FStrEq(pkvd->szKeyName, "globalstate"))
	{
		m_globalstate = ALLOC_STRING(pkvd->szValue);
	}
	else if (FStrEq(pkvd->szKeyName, "triggermode"))
	{
		m_triggermode = Q_atoi(pkvd->szValue);
	}
	else if (FStrEq(pkvd->szKeyName, "initialstate"))
	{
		m_initialstate = Q_atoi(pkvd->szValue);
	}
	else
		CPointEntity::KeyValue(pkvd);
}

/* <26486> ../cstrike/dlls/buttons.cpp:80 */
void CEnvGlobal::__MAKE_VHOOK(Spawn)(void)
{
	if (!m_globalstate)
	{
		REMOVE_ENTITY(ENT(pev));
		return;
	}

	if (pev->spawnflags & SF_GLOBAL_SET)
	{
		if (!gGlobalState.EntityInTable(m_globalstate))
		{
			gGlobalState.EntityAdd(m_globalstate, gpGlobals->mapname, (GLOBALESTATE)m_initialstate);
		}
	}
}

/* <25ee7> ../cstrike/dlls/buttons.cpp:95 */
void CEnvGlobal::__MAKE_VHOOK(Use)(CBaseEntity *pActivator, CBaseEntity *pCaller, USE_TYPE useType, float value)
{
	GLOBALESTATE oldState = gGlobalState.EntityGetState(m_globalstate);
	GLOBALESTATE newState;

	switch (m_triggermode)
	{
	case 0:
		newState = GLOBAL_OFF;
		break;

	case 1:
		newState = GLOBAL_ON;
		break;

	case 2:
		newState = GLOBAL_DEAD;
		break;

	default:
	case 3:
		if (oldState == GLOBAL_ON)
		{
			newState = GLOBAL_OFF;
		}
		else if (oldState == GLOBAL_OFF)
		{
			newState = GLOBAL_ON;
		}
		else
			newState = oldState;
	}

	if (gGlobalState.EntityInTable(m_globalstate))
	{
		gGlobalState.EntitySetState(m_globalstate, newState);
	}
	else
		gGlobalState.EntityAdd(m_globalstate, gpGlobals->mapname, newState);
}

/* <2616f> ../cstrike/dlls/buttons.cpp:141 */
IMPLEMENT_SAVERESTORE(CMultiSource, CBaseEntity);

/* <27379> ../cstrike/dlls/buttons.cpp:143 */
LINK_ENTITY_TO_CLASS(multisource, CMultiSource);

// Cache user-entity-field values until spawn is called.

/* <26d1e> ../cstrike/dlls/buttons.cpp:148 */
void CMultiSource::__MAKE_VHOOK(KeyValue)(KeyValueData *pkvd)
{
	if (FStrEq(pkvd->szKeyName, "style")
			|| FStrEq(pkvd->szKeyName, "height")
			|| FStrEq(pkvd->szKeyName, "killtarget")
			|| FStrEq(pkvd->szKeyName, "value1")
			|| FStrEq(pkvd->szKeyName, "value2")
			|| FStrEq(pkvd->szKeyName, "value3"))
		pkvd->fHandled = TRUE;

	else if (FStrEq(pkvd->szKeyName, "globalstate"))
	{
		m_globalstate = ALLOC_STRING(pkvd->szValue);
		pkvd->fHandled = TRUE;
	}
	else
		CPointEntity::KeyValue(pkvd);
}

/* <256e2> ../cstrike/dlls/buttons.cpp:168 */
void CMultiSource::__MAKE_VHOOK(Spawn)(void)
{
	// set up think for later registration
	pev->solid = SOLID_NOT;
	pev->movetype = MOVETYPE_NONE;
	pev->nextthink = gpGlobals->time + 0.1;

	// Until it's initialized
	pev->spawnflags |= SF_MULTI_INIT;

	SetThink(&CMultiSource::Register);
}

/* <2633b> ../cstrike/dlls/buttons.cpp:179 */
void CMultiSource::__MAKE_VHOOK(Use)(CBaseEntity *pActivator, CBaseEntity *pCaller, USE_TYPE useType, float value)
{
	int i = 0;

	// Find the entity in our list
	while (i < m_iTotal)
	{
		if (m_rgEntities[i++] == pCaller)
			break;
	}

	// if we didn't find it, report error and leave
	if (i > m_iTotal)
	{
		ALERT(at_console, "MultiSrc:Used by non member %s.\n", STRING(pCaller->pev->classname));
		return;
	}

	// CONSIDER: a Use input to the multisource always toggles.
	// Could check useType for ON/OFF/TOGGLE
	m_rgTriggered[i - 1] ^= 1;

	if (IsTriggered(pActivator))
	{
		ALERT(at_aiconsole, "Multisource %s enabled (%d inputs)\n", STRING(pev->targetname), m_iTotal);
		USE_TYPE useType = USE_TOGGLE;

		if (!FStringNull(m_globalstate))
		{
			useType = USE_ON;
		}

		SUB_UseTargets(NULL, useType, 0);
	}
}

/* <26419> ../cstrike/dlls/buttons.cpp:211 */
BOOL CMultiSource::__MAKE_VHOOK(IsTriggered)(CBaseEntity *)
{
	// Is everything triggered?
	int i = 0;

	// Still initializing?
	if (pev->spawnflags & SF_MULTI_INIT)
		return 0;

	while (i < m_iTotal)
	{
		if (m_rgTriggered[i] == 0)
			break;
		i++;
	}

	if (i == m_iTotal)
	{
		if (FStringNull(m_globalstate) || gGlobalState.EntityGetState(m_globalstate) == GLOBAL_ON)
		{
			return 1;
		}
	}

	return 0;
}

/* <25d5a> ../cstrike/dlls/buttons.cpp:236 */
void CMultiSource::Register(void)
{
	edict_t *pentTarget = NULL;

	m_iTotal = 0;
	Q_memset(m_rgEntities, 0, MS_MAX_TARGETS * sizeof(EHANDLE));

	SetThink(&CMultiSource::SUB_DoNothing);

	// search for all entities which target this multisource (pev->targetname)
	pentTarget = FIND_ENTITY_BY_STRING(NULL, "target", STRING(pev->targetname));

	while (!FNullEnt(pentTarget) && m_iTotal < MS_MAX_TARGETS)
	{
		CBaseEntity *pTarget = CBaseEntity::Instance(pentTarget);

		if (pTarget != NULL)
		{
			m_rgEntities[m_iTotal++] = pTarget;
		}

		pentTarget = FIND_ENTITY_BY_STRING(pentTarget, "target", STRING(pev->targetname));
	}

	pentTarget = FIND_ENTITY_BY_STRING(NULL, "classname", "multi_manager");

	while (!FNullEnt(pentTarget) && m_iTotal < MS_MAX_TARGETS)
	{
		CBaseEntity *pTarget = CBaseEntity::Instance(pentTarget);
		if (pTarget != NULL && pTarget->HasTarget(pev->targetname))
		{
			m_rgEntities[m_iTotal++] = pTarget;
		}

		pentTarget = FIND_ENTITY_BY_STRING(pentTarget, "classname", "multi_manager");
	}

	pev->spawnflags &= ~SF_MULTI_INIT;
}

/* <262ee> ../cstrike/dlls/buttons.cpp:287 */
IMPLEMENT_SAVERESTORE(CBaseButton, CBaseToggle);

/* <25709> ../cstrike/dlls/buttons.cpp:289 */
void CBaseButton::__MAKE_VHOOK(Precache)(void)
{
	char *pszSound;

	// this button should spark in OFF state
	if (pev->spawnflags & SF_BUTTON_SPARK_IF_OFF)
	{
		PRECACHE_SOUND("buttons/spark1.wav");
		PRECACHE_SOUND("buttons/spark2.wav");
		PRECACHE_SOUND("buttons/spark3.wav");
		PRECACHE_SOUND("buttons/spark4.wav");
		PRECACHE_SOUND("buttons/spark5.wav");
		PRECACHE_SOUND("buttons/spark6.wav");
	}

	// get door button sounds, for doors which require buttons to open
	if (m_bLockedSound)
	{
		pszSound = ButtonSound((int)m_bLockedSound);
		PRECACHE_SOUND(pszSound);
		m_ls.sLockedSound = ALLOC_STRING(pszSound);
	}

	if (m_bUnlockedSound)
	{
		pszSound = ButtonSound((int)m_bUnlockedSound);
		PRECACHE_SOUND(pszSound);
		m_ls.sUnlockedSound = ALLOC_STRING(pszSound);
	}

	// get sentence group names, for doors which are directly 'touched' to open
	switch (m_bLockedSentence)
	{
	case 1: m_ls.sLockedSentence = MAKE_STRING("NA"); break;	// access denied
	case 2: m_ls.sLockedSentence = MAKE_STRING("ND"); break;	// security lockout
	case 3: m_ls.sLockedSentence = MAKE_STRING("NF"); break;	// blast door
	case 4: m_ls.sLockedSentence = MAKE_STRING("NFIRE"); break;	// fire door
	case 5: m_ls.sLockedSentence = MAKE_STRING("NCHEM"); break;	// chemical door
	case 6: m_ls.sLockedSentence = MAKE_STRING("NRAD"); break;	// radiation door
	case 7: m_ls.sLockedSentence = MAKE_STRING("NCON"); break;	// gen containment
	case 8: m_ls.sLockedSentence = MAKE_STRING("NH"); break;	// maintenance door
	case 9: m_ls.sLockedSentence = MAKE_STRING("NG"); break;	// broken door
	default: m_ls.sLockedSentence = 0; break;
	}

	switch (m_bUnlockedSentence)
	{
	case 1: m_ls.sUnlockedSentence = MAKE_STRING("EA"); break;	// access granted
	case 2: m_ls.sUnlockedSentence = MAKE_STRING("ED"); break;	// security door
	case 3: m_ls.sUnlockedSentence = MAKE_STRING("EF"); break;	// blast door
	case 4: m_ls.sUnlockedSentence = MAKE_STRING("EFIRE"); break;	// fire door
	case 5: m_ls.sUnlockedSentence = MAKE_STRING("ECHEM"); break;	// chemical door
	case 6: m_ls.sUnlockedSentence = MAKE_STRING("ERAD"); break;	// radiation door
	case 7: m_ls.sUnlockedSentence = MAKE_STRING("ECON"); break;	// gen containment
	case 8: m_ls.sUnlockedSentence = MAKE_STRING("EH"); break;	// maintenance door
	default: m_ls.sUnlockedSentence = 0; break;
	}
}

// Cache user-entity-field values until spawn is called.

/* <269cb> ../cstrike/dlls/buttons.cpp:355 */
void CBaseButton::__MAKE_VHOOK(KeyValue)(KeyValueData *pkvd)
{
	if (FStrEq(pkvd->szKeyName, "changetarget"))
	{
		m_strChangeTarget = ALLOC_STRING(pkvd->szValue);
		pkvd->fHandled = TRUE;
	}
	else if (FStrEq(pkvd->szKeyName, "locked_sound"))
	{
		m_bLockedSound = (int)Q_atof(pkvd->szValue);
		pkvd->fHandled = TRUE;
	}
	else if (FStrEq(pkvd->szKeyName, "locked_sentence"))
	{
		m_bLockedSentence = (int)Q_atof(pkvd->szValue);
		pkvd->fHandled = TRUE;
	}
	else if (FStrEq(pkvd->szKeyName, "unlocked_sound"))
	{
		m_bUnlockedSound = (int)Q_atof(pkvd->szValue);
		pkvd->fHandled = TRUE;
	}
	else if (FStrEq(pkvd->szKeyName, "unlocked_sentence"))
	{
		m_bUnlockedSentence = (int)Q_atof(pkvd->szValue);
		pkvd->fHandled = TRUE;
	}
	else if (FStrEq(pkvd->szKeyName, "sounds"))
	{
		m_sounds = Q_atoi(pkvd->szValue);
		pkvd->fHandled = TRUE;
	}
	else
		CBaseToggle::KeyValue(pkvd);
}

// ButtonShot

/* <26e90> ../cstrike/dlls/buttons.cpp:394 */
int CBaseButton::__MAKE_VHOOK(TakeDamage)(entvars_t *pevInflictor, entvars_t *pevAttacker, float flDamage, int bitsDamageType)
{
	BUTTON_CODE code = ButtonResponseToTouch();

	if (code == BUTTON_NOTHING)
	{
		return 0;
	}

	// Temporarily disable the touch function, until movement is finished.
	SetTouch(NULL);

	m_hActivator = CBaseEntity::Instance(pevAttacker);
	if (m_hActivator == NULL)
		return 0;

	if (code == BUTTON_RETURN)
	{
		EMIT_SOUND(ENT(pev), CHAN_VOICE, (char*)STRING(pev->noise), 1, ATTN_NORM);

		// Toggle buttons fire when they get back to their "home" position
		if (!(pev->spawnflags & SF_BUTTON_TOGGLE))
		{
			SUB_UseTargets(m_hActivator, USE_TOGGLE, 0);
		}

		ButtonReturn();
	}
	else
	{
		// code == BUTTON_ACTIVATE
		ButtonActivate();
	}

	return 0;
}

// QUAKED func_button (0 .5 .8) ?
// When a button is touched, it moves some distance in the direction of it's angle,
// triggers all of it's targets, waits some time, then returns to it's original position
// where it can be triggered again.
//
// "angle"	determines the opening direction
// "target"	all entities with a matching targetname will be used
// "speed"	override the default 40 speed
// "wait"	override the default 1 second wait (-1 = never return)
// "lip"	override the default 4 pixel lip remaining at end of move
// "health"	if set, the button must be killed instead of touched
// "sounds"
// 0) steam metal
// 1) wooden clunk
// 2) metallic click
// 3) in-out

/* <27443> ../cstrike/dlls/buttons.cpp:439 */
LINK_ENTITY_TO_CLASS(func_button, CBaseButton);

/* <25c2c> ../cstrike/dlls/buttons.cpp:442 */
void CBaseButton::__MAKE_VHOOK(Spawn)(void)
{
	char  *pszSound;

	//----------------------------------------------------
	//determine sounds for buttons
	//a sound of 0 should not make a sound
	//----------------------------------------------------
	pszSound = ButtonSound(m_sounds);
	PRECACHE_SOUND(pszSound);
	pev->noise = ALLOC_STRING(pszSound);

	Precache();

	// this button should spark in OFF state
	if (pev->spawnflags & SF_BUTTON_SPARK_IF_OFF)
	{
		SetThink(&CBaseButton::ButtonSpark);

		// no hurry, make sure everything else spawns
		pev->nextthink = gpGlobals->time + 0.5;
	}

	SetMovedir(pev);

	pev->movetype = MOVETYPE_PUSH;
	pev->solid = SOLID_BSP;

	SET_MODEL(ENT(pev), STRING(pev->model));

	if (pev->speed == 0)
		pev->speed = 40;

	if (pev->health > 0)
	{
		pev->takedamage = DAMAGE_YES;
	}

	if (m_flWait == 0)
	{
		m_flWait = 1;
	}

	if (m_flLip == 0)
	{
		m_flLip = 4;
	}

	m_toggle_state = TS_AT_BOTTOM;
	m_vecPosition1 = pev->origin;

	// Subtract 2 from size because the engine expands bboxes by 1 in all directions making the size too big
	m_vecPosition2	= m_vecPosition1 + (pev->movedir * (fabs((float_precision)(pev->movedir.x * (pev->size.x - 2))) + fabs((float_precision)(pev->movedir.y * (pev->size.y - 2))) + fabs((float_precision)(pev->movedir.z * (pev->size.z - 2))) - m_flLip));

	// Is this a non-moving button?
	if (((m_vecPosition2 - m_vecPosition1).Length() < 1) || (pev->spawnflags & SF_BUTTON_DONTMOVE))
	{
		m_vecPosition2 = m_vecPosition1;
	}

	m_fStayPushed = (m_flWait == -1 ? TRUE : FALSE);
	m_fRotating = FALSE;

	// if the button is flagged for USE button activation only, take away it's touch function and add a use function
	// touchable button
	if (pev->spawnflags & SF_BUTTON_TOUCH_ONLY)
	{
		SetTouch(&CBaseButton::ButtonTouch);
	}
	else
	{
		SetTouch(NULL);
		SetUse(&CBaseButton::ButtonUse);
	}
}

// Button sound table.
// Also used by CBaseDoor to get 'touched' door lock/unlock sounds

/* <24738> ../cstrike/dlls/buttons.cpp:511 */
char *ButtonSound(int sound)
{
	char *pszSound;

	switch (sound)
	{
		case 0: pszSound = "common/null.wav"; break;
		case 1: pszSound = "buttons/button1.wav"; break;
		case 2: pszSound = "buttons/button2.wav"; break;
		case 3: pszSound = "buttons/button3.wav"; break;
		case 4: pszSound = "buttons/button4.wav"; break;
		case 5: pszSound = "buttons/button5.wav"; break;
		case 6: pszSound = "buttons/button6.wav"; break;
		case 7: pszSound = "buttons/button7.wav"; break;
		case 8: pszSound = "buttons/button8.wav"; break;
		case 9: pszSound = "buttons/button9.wav"; break;
		case 10: pszSound = "buttons/button10.wav"; break;
		case 11: pszSound = "buttons/button11.wav"; break;
		case 12: pszSound = "buttons/latchlocked1.wav"; break;
		case 13: pszSound = "buttons/latchunlocked1.wav"; break;
		case 14: pszSound = "buttons/lightswitch2.wav"; break;

		// next 6 slots reserved for any additional sliding button sounds we may add
		case 21: pszSound = "buttons/lever1.wav"; break;
		case 22: pszSound = "buttons/lever2.wav"; break;
		case 23: pszSound = "buttons/lever3.wav"; break;
		case 24: pszSound = "buttons/lever4.wav"; break;
		case 25: pszSound = "buttons/lever5.wav"; break;
		default: pszSound = "buttons/button9.wav"; break;
	}

	return pszSound;
}

// Makes flagged buttons spark when turned off

/* <2752e> ../cstrike/dlls/buttons.cpp:551 */
void DoSpark(entvars_t *pev, const Vector &location)
{
	Vector tmp = location + (pev->size * 0.5);
	UTIL_Sparks(tmp);

	//random volume range
	float flVolume = RANDOM_FLOAT(0.25 , 0.75) * 0.4;

	switch ((int)(RANDOM_FLOAT(0, 1) * 6))
	{
		case 0: EMIT_SOUND(ENT(pev), CHAN_VOICE, "buttons/spark1.wav", flVolume, ATTN_NORM); break;
		case 1: EMIT_SOUND(ENT(pev), CHAN_VOICE, "buttons/spark2.wav", flVolume, ATTN_NORM); break;
		case 2: EMIT_SOUND(ENT(pev), CHAN_VOICE, "buttons/spark3.wav", flVolume, ATTN_NORM); break;
		case 3: EMIT_SOUND(ENT(pev), CHAN_VOICE, "buttons/spark4.wav", flVolume, ATTN_NORM); break;
		case 4: EMIT_SOUND(ENT(pev), CHAN_VOICE, "buttons/spark5.wav", flVolume, ATTN_NORM); break;
		case 5: EMIT_SOUND(ENT(pev), CHAN_VOICE, "buttons/spark6.wav", flVolume, ATTN_NORM); break;
	}
}

/* <277fa> ../cstrike/dlls/buttons.cpp:568 */
void CBaseButton::ButtonSpark(void)
{
	SetThink(&CBaseButton::ButtonSpark);

	// spark again at random interval
	pev->nextthink = gpGlobals->time + (0.1 + RANDOM_FLOAT(0, 1.5));

	DoSpark(pev, pev->mins);
}

// Button's Use function

/* <2719b> ../cstrike/dlls/buttons.cpp:580 */
void CBaseButton::ButtonUse(CBaseEntity *pActivator, CBaseEntity *pCaller, USE_TYPE useType, float value)
{
	// Ignore touches if button is moving, or pushed-in and waiting to auto-come-out.
	// UNDONE: Should this use ButtonResponseToTouch() too?
	if (m_toggle_state == TS_GOING_UP || m_toggle_state == TS_GOING_DOWN)
		return;

	m_hActivator = pActivator;
	if (m_toggle_state == TS_AT_TOP)
	{
		if (!m_fStayPushed && (pev->spawnflags & SF_BUTTON_TOGGLE))
		{
			EMIT_SOUND(ENT(pev), CHAN_VOICE, (char *)STRING(pev->noise), VOL_NORM, ATTN_NORM);
			//SUB_UseTargets(m_eoActivator);
			ButtonReturn();
		}
	}
	else
		ButtonActivate();
}

/* <27821> ../cstrike/dlls/buttons.cpp:603 */
CBaseButton::BUTTON_CODE CBaseButton::ButtonResponseToTouch(void)
{
	// Ignore touches if button is moving, or pushed-in and waiting to auto-come-out.
	if (m_toggle_state == TS_GOING_UP || m_toggle_state == TS_GOING_DOWN || (m_toggle_state == TS_AT_TOP && !m_fStayPushed && !(pev->spawnflags & SF_BUTTON_TOGGLE)))
	{
		return BUTTON_NOTHING;
	}

	if (m_toggle_state == TS_AT_TOP)
	{
		if ((pev->spawnflags & SF_BUTTON_TOGGLE) && !m_fStayPushed)
		{
			return BUTTON_RETURN;
		}
	}
	else
		return BUTTON_ACTIVATE;

	return BUTTON_NOTHING;
}

// Touching a button simply "activates" it.

/* <27047> ../cstrike/dlls/buttons.cpp:628 */
void CBaseButton::ButtonTouch(CBaseEntity *pOther)
{
	// Ignore touches by anything but players
	if (!FClassnameIs(pOther->pev, "player"))
		return;

	m_hActivator = pOther;

	BUTTON_CODE code = ButtonResponseToTouch();

	if (code == BUTTON_NOTHING)
		return;

	if (!UTIL_IsMasterTriggered(m_sMaster, pOther))
	{
		// play button locked sound
		PlayLockSounds(pev, &m_ls, TRUE, TRUE);
		return;
	}

	// Temporarily disable the touch function, until movement is finished.
	SetTouch(NULL);

	if (code == BUTTON_RETURN)
	{
		EMIT_SOUND(ENT(pev), CHAN_VOICE, (char *)STRING(pev->noise), VOL_NORM, ATTN_NORM);
		SUB_UseTargets(m_hActivator, USE_TOGGLE, 0);
		ButtonReturn();
	}
	else // code == BUTTON_ACTIVATE
	{
		ButtonActivate();
	}
}

// Starts the button moving "in/up".

/* <27843> ../cstrike/dlls/buttons.cpp:664 */
void CBaseButton::ButtonActivate(void)
{
	EMIT_SOUND(ENT(pev), CHAN_VOICE, (char *)STRING(pev->noise), VOL_NORM, ATTN_NORM);

	if (!UTIL_IsMasterTriggered(m_sMaster, m_hActivator))
	{
		// button is locked, play locked sound
		PlayLockSounds(pev, &m_ls, TRUE, TRUE);
		return;
	}
	else
	{
		// button is unlocked, play unlocked sound
		PlayLockSounds(pev, &m_ls, FALSE, TRUE);
	}

	assert(m_toggle_state == TS_AT_BOTTOM);
	m_toggle_state = TS_GOING_UP;

	SetMoveDone(&CBaseButton::TriggerAndWait);
	if (!m_fRotating)
	{
		LinearMove(m_vecPosition2, pev->speed);
	}
	else
	{
		AngularMove(m_vecAngle2, pev->speed);
	}
}

// Button has reached the "in/up" position.  Activate its "targets", and pause before "popping out".

/* <263dd> ../cstrike/dlls/buttons.cpp:693 */
void CBaseButton::TriggerAndWait(void)
{
	assert(m_toggle_state == TS_GOING_UP);

	if (!UTIL_IsMasterTriggered(m_sMaster, m_hActivator))
		return;

	m_toggle_state = TS_AT_TOP;

	// If button automatically comes back out, start it moving out.
	// Else re-instate touch method
	if (m_fStayPushed || (pev->spawnflags & SF_BUTTON_TOGGLE))
	{
		// this button only works if USED, not touched!
		if (!(pev->spawnflags & SF_BUTTON_TOUCH_ONLY))
		{
			// ALL buttons are now use only
			SetTouch(NULL);
		}
		else
			SetTouch(&CBaseButton::ButtonTouch);
	}
	else
	{
		pev->nextthink = pev->ltime + m_flWait;
		SetThink(&CBaseButton::ButtonReturn);
	}

	// use alternate textures
	pev->frame = 1;
	SUB_UseTargets(m_hActivator, USE_TOGGLE, 0);
}

// Starts the button moving "out/down".

/* <25bb7> ../cstrike/dlls/buttons.cpp:730 */
void CBaseButton::ButtonReturn(void)
{
	assert(m_toggle_state == TS_AT_TOP);
	m_toggle_state = TS_GOING_DOWN;

	SetMoveDone(&CBaseButton::ButtonBackHome);
	if (!m_fRotating)
	{
		LinearMove(m_vecPosition1, pev->speed);
	}
	else
	{
		AngularMove(m_vecAngle1, pev->speed);
	}

	// use normal textures
	pev->frame = 0;
}

// Button has returned to start state. Quiesce it.

/* <26658> ../cstrike/dlls/buttons.cpp:748 */
void CBaseButton::ButtonBackHome(void)
{
	assert(m_toggle_state == TS_GOING_DOWN);
	m_toggle_state = TS_AT_BOTTOM;

	if (pev->spawnflags & SF_BUTTON_TOGGLE)
	{
		//EMIT_SOUND(ENT(pev), CHAN_VOICE, (char *)STRING(pev->noise), 1, ATTN_NORM);
		SUB_UseTargets(m_hActivator, USE_TOGGLE, 0);
	}

	if (!FStringNull(pev->target))
	{
		edict_t *pentTarget = NULL;

		while (true)
		{
			pentTarget = FIND_ENTITY_BY_TARGETNAME(pentTarget, STRING(pev->target));

			if (FNullEnt(pentTarget))
				break;

			if (!FClassnameIs(pentTarget, "multisource"))
				continue;

			CBaseEntity *pTarget = CBaseEntity::Instance(pentTarget);

			if (pTarget != NULL)
			{
				pTarget->Use(m_hActivator, this, USE_TOGGLE, 0);
			}
		}
	}

	// Re-instate touch method, movement cycle is complete.
	// this button only works if USED, not touched!
	if (!(pev->spawnflags & SF_BUTTON_TOUCH_ONLY))
	{
		// All buttons are now use only
		SetTouch(NULL);
	}
	else
		SetTouch(&CBaseButton::ButtonTouch);

	// reset think for a sparking button
	if (pev->spawnflags & SF_BUTTON_SPARK_IF_OFF)
	{
		SetThink(&CBaseButton::ButtonSpark);

		// no hurry.
		pev->nextthink = gpGlobals->time + 0.5;
	}
}

/* <278a4> ../cstrike/dlls/buttons.cpp:806 */
LINK_ENTITY_TO_CLASS(func_rot_button, CRotButton);

/* <25a06> ../cstrike/dlls/buttons.cpp:808 */
void CRotButton::__MAKE_VHOOK(Spawn)(void)
{
	char *pszSound;

	//----------------------------------------------------
	//determine sounds for buttons
	//a sound of 0 should not make a sound
	//----------------------------------------------------
	pszSound = ButtonSound(m_sounds);
	PRECACHE_SOUND(pszSound);
	pev->noise = ALLOC_STRING(pszSound);

	// set the axis of rotation
	CBaseToggle::AxisDir(pev);

	// check for clockwise rotation
	if (pev->spawnflags & SF_DOOR_ROTATE_BACKWARDS)
	{
		pev->movedir = pev->movedir * -1;
	}

	pev->movetype = MOVETYPE_PUSH;

	if (pev->spawnflags & SF_ROTBUTTON_NOTSOLID)
		pev->solid = SOLID_NOT;
	else
		pev->solid = SOLID_BSP;

	SET_MODEL(ENT(pev), STRING(pev->model));

	if (pev->speed == 0)
		pev->speed = 40;

	if (m_flWait == 0)
	{
		m_flWait = 1;
	}

	if (pev->health > 0)
	{
		pev->takedamage = DAMAGE_YES;
	}

	m_toggle_state = TS_AT_BOTTOM;
	m_vecAngle1 = pev->angles;
	m_vecAngle2 = pev->angles + pev->movedir * m_flMoveDistance;

	assert(("rotating button start/end positions are equal", m_vecAngle1 != m_vecAngle2));

	m_fStayPushed = (m_flWait == -1 ? TRUE : FALSE);
	m_fRotating = TRUE;

	// if the button is flagged for USE button activation only, take away it's touch function and add a use function
	if (!(pev->spawnflags & SF_BUTTON_TOUCH_ONLY))
	{
		SetTouch(NULL);
		SetUse(&CRotButton::ButtonUse);
	}
	else // touchable button
		SetTouch(&CRotButton::ButtonTouch);

	//SetTouch(ButtonTouch);
}

/* <262a1> ../cstrike/dlls/buttons.cpp:918 */
IMPLEMENT_SAVERESTORE(CMomentaryRotButton, CBaseToggle);

/* <27971> ../cstrike/dlls/buttons.cpp:920 */
LINK_ENTITY_TO_CLASS(momentary_rot_button, CMomentaryRotButton);

/* <25acc> ../cstrike/dlls/buttons.cpp:922 */
void CMomentaryRotButton::__MAKE_VHOOK(Spawn)(void)
{
	CBaseToggle::AxisDir(pev);

	if (pev->speed == 0)
		pev->speed = 100;

	if (m_flMoveDistance < 0)
	{
		m_start = pev->angles + pev->movedir * m_flMoveDistance;
		m_end = pev->angles;

		// This will toggle to -1 on the first use()
		m_direction = 1;
		m_flMoveDistance = -m_flMoveDistance;
	}
	else
	{
		m_start = pev->angles;
		m_end = pev->angles + pev->movedir * m_flMoveDistance;

		// This will toggle to +1 on the first use()
		m_direction = -1;
	}

	if (pev->spawnflags & SF_MOMENTARY_DOOR)
		pev->solid = SOLID_BSP;
	else
		pev->solid = SOLID_NOT;

	pev->movetype = MOVETYPE_PUSH;
	UTIL_SetOrigin(pev, pev->origin);
	SET_MODEL(ENT(pev), STRING(pev->model));

	char *pszSound = ButtonSound(m_sounds);
	PRECACHE_SOUND(pszSound);
	pev->noise = ALLOC_STRING(pszSound);
	m_lastUsed = 0;
}

/* <2678f> ../cstrike/dlls/buttons.cpp:958 */
void CMomentaryRotButton::__MAKE_VHOOK(KeyValue)(KeyValueData *pkvd)
{
	if (FStrEq(pkvd->szKeyName, "returnspeed"))
	{
		m_returnSpeed = Q_atof(pkvd->szValue);
		pkvd->fHandled = TRUE;
	}
	else if (FStrEq(pkvd->szKeyName, "sounds"))
	{
		m_sounds = Q_atoi(pkvd->szValue);
		pkvd->fHandled = TRUE;
	}
	else
		CBaseToggle::KeyValue(pkvd);
}

/* <27a57> ../cstrike/dlls/buttons.cpp:974 */
void CMomentaryRotButton::PlaySound(void)
{
	EMIT_SOUND(ENT(pev), CHAN_VOICE, (char *)STRING(pev->noise), VOL_NORM, ATTN_NORM);
}

// BUGBUG: This design causes a latentcy.  When the button is retriggered, the first impulse
// will send the target in the wrong direction because the parameter is calculated based on the
// current, not future position.

/* <27dc0> ../cstrike/dlls/buttons.cpp:982 */
void CMomentaryRotButton::__MAKE_VHOOK(Use)(CBaseEntity *pActivator, CBaseEntity *pCaller, USE_TYPE useType, float value)
{
	pev->ideal_yaw = CBaseToggle::AxisDelta(pev->spawnflags, pev->angles, m_start) / m_flMoveDistance;

	UpdateAllButtons(pev->ideal_yaw, 1);
	UpdateTarget(pev->ideal_yaw);

#if 0
	// Calculate destination angle and use it to predict value, this prevents sending target in wrong direction on retriggering
	Vector dest = pev->angles + pev->avelocity * (pev->nextthink - pev->ltime);
	float value1 = CBaseToggle::AxisDelta(pev->spawnflags, dest, m_start) / m_flMoveDistance;
	UpdateTarget(value1);
#endif
}

/* <27c49> ../cstrike/dlls/buttons.cpp:990 */
void CMomentaryRotButton::UpdateAllButtons(float value, int start)
{
	// Update all rot buttons attached to the same target
	edict_t *pentTarget = NULL;
	while (true)
	{

		pentTarget = FIND_ENTITY_BY_STRING(pentTarget, "target", STRING(pev->target));

		if (FNullEnt(pentTarget))
			break;

		if (FClassnameIs(VARS(pentTarget), "momentary_rot_button"))
		{
			CMomentaryRotButton *pEntity = CMomentaryRotButton::Instance(pentTarget);

			if (pEntity != NULL)
			{
				if (start)
					pEntity->UpdateSelf(value);
				else
					pEntity->UpdateSelfReturn(value);
			}
		}
	}
}

/* <27ab8> ../cstrike/dlls/buttons.cpp:1015 */
void CMomentaryRotButton::UpdateSelf(float value)
{
	BOOL fplaysound = FALSE;

	if (!m_lastUsed)
	{
		fplaysound = TRUE;
		m_direction = -m_direction;
	}

	m_lastUsed = 1;
	pev->nextthink = pev->ltime + 0.1f;

	if (m_direction > 0 && value >= 1.0f)
	{
		pev->avelocity = g_vecZero;
		pev->angles = m_end;
		return;
	}
	else if (m_direction < 0 && value <= 0.0f)
	{
		pev->avelocity = g_vecZero;
		pev->angles = m_start;
		return;
	}

	if (fplaysound)
	{
		PlaySound();
	}

	// HACKHACK -- If we're going slow, we'll get multiple player packets per frame, bump nexthink on each one to avoid stalling
	if (pev->nextthink < pev->ltime)
		pev->nextthink = pev->ltime + 0.1;
	else
		pev->nextthink += 0.1;

	pev->avelocity = (m_direction * pev->speed) * pev->movedir;
	SetThink(&CMomentaryRotButton::Off);
}

/* <26550> ../cstrike/dlls/buttons.cpp:1053 */
void CMomentaryRotButton::UpdateTarget(float value)
{
	if (!FStringNull(pev->target))
	{
		edict_t *pentTarget = NULL;

		while (true)
		{
			pentTarget = FIND_ENTITY_BY_TARGETNAME(pentTarget, STRING(pev->target));

			if (FNullEnt(pentTarget))
				break;

			CBaseEntity *pEntity = CBaseEntity::Instance(pentTarget);

			if (pEntity != NULL)
			{
				pEntity->Use(this, this, USE_SET, value);
			}
		}
	}
}

/* <25f88> ../cstrike/dlls/buttons.cpp:1072 */
void CMomentaryRotButton::Off(void)
{
	pev->avelocity = g_vecZero;
	m_lastUsed = 0;

	if ((pev->spawnflags & SF_PENDULUM_AUTO_RETURN) && m_returnSpeed > 0)
	{
		SetThink(&CMomentaryRotButton::Return);
		pev->nextthink = pev->ltime + 0.1f;
		m_direction = -1;
	}
	else
		SetThink(NULL);
}

/* <27d60> ../cstrike/dlls/buttons.cpp:1086 */
void CMomentaryRotButton::Return(void)
{
	float value = CBaseToggle::AxisDelta(pev->spawnflags, pev->angles, m_start) / m_flMoveDistance;

	// This will end up calling UpdateSelfReturn() n times, but it still works right
	UpdateAllButtons(value, 0);

	if (value > 0)
	{
		UpdateTarget(value);
	}
}

/* <27bce> ../cstrike/dlls/buttons.cpp:1096 */
void CMomentaryRotButton::UpdateSelfReturn(float value)
{
	if (value <= 0)
	{
		pev->avelocity = g_vecZero;
		pev->angles = m_start;
		pev->nextthink = -1;
		SetThink(NULL);
	}
	else
	{
		pev->avelocity = -m_returnSpeed * pev->movedir;
		pev->nextthink = pev->ltime + 0.1;
	}
}

/* <26122> ../cstrike/dlls/buttons.cpp:1141 */
IMPLEMENT_SAVERESTORE(CEnvSpark, CBaseEntity);

/* <27e77> ../cstrike/dlls/buttons.cpp:1143 */
LINK_ENTITY_TO_CLASS(env_spark, CEnvSpark);

/* <27f44> ../cstrike/dlls/buttons.cpp:1144 */
LINK_ENTITY_TO_CLASS(env_debris, CEnvSpark);

/* <257b7> ../cstrike/dlls/buttons.cpp:1146 */
void CEnvSpark::__MAKE_VHOOK(Spawn)(void)
{
	SetThink(NULL);
	SetUse(NULL);

	// Use for on/off
	if (pev->spawnflags & SF_SPARK_TOOGLE)
	{
		// Start on
		if (pev->spawnflags & SF_SPARK_IF_OFF)
		{
			// start sparking
			SetThink(&CEnvSpark::SparkThink);

			// set up +USE to stop sparking
			SetUse(&CEnvSpark::SparkStop);
		}
		else
			SetUse(&CEnvSpark::SparkStart);
	}
	else
		SetThink(&CEnvSpark::SparkThink);

	pev->nextthink = gpGlobals->time + (0.1 + RANDOM_FLOAT(0, 1.5));

	if (m_flDelay <= 0)
	{
		m_flDelay = 1.5;
	}

	Precache();
}

/* <257de> ../cstrike/dlls/buttons.cpp:1173 */
void CEnvSpark::__MAKE_VHOOK(Precache)(void)
{
	PRECACHE_SOUND("buttons/spark1.wav");
	PRECACHE_SOUND("buttons/spark2.wav");
	PRECACHE_SOUND("buttons/spark3.wav");
	PRECACHE_SOUND("buttons/spark4.wav");
	PRECACHE_SOUND("buttons/spark5.wav");
	PRECACHE_SOUND("buttons/spark6.wav");
}

/* <26b97> ../cstrike/dlls/buttons.cpp:1183 */
void CEnvSpark::__MAKE_VHOOK(KeyValue)(KeyValueData *pkvd)
{
	if (FStrEq(pkvd->szKeyName, "MaxDelay"))
	{
		m_flDelay = Q_atof(pkvd->szValue);
		pkvd->fHandled = TRUE;
	}
	else if (FStrEq(pkvd->szKeyName, "style")
			|| FStrEq(pkvd->szKeyName, "height")
			|| FStrEq(pkvd->szKeyName, "killtarget")
			|| FStrEq(pkvd->szKeyName, "value1")
			|| FStrEq(pkvd->szKeyName, "value2")
			|| FStrEq(pkvd->szKeyName, "value3"))
		pkvd->fHandled = TRUE;
	else
		CBaseEntity::KeyValue(pkvd);
}

/* <277d3> ../cstrike/dlls/buttons.cpp:1201 */
void CEnvSpark::SparkThink(void)
{
	pev->nextthink = gpGlobals->time + 0.1 + RANDOM_FLOAT(0, m_flDelay);
	DoSpark(pev, pev->origin);
}

/* <25805> ../cstrike/dlls/buttons.cpp:1207 */
void CEnvSpark::SparkStart(CBaseEntity *pActivator, CBaseEntity *pCaller, USE_TYPE useType, float value)
{
	SetUse(&CEnvSpark::SparkStop);
	SetThink(&CEnvSpark::SparkThink);
	pev->nextthink = gpGlobals->time + (0.1 + RANDOM_FLOAT(0, m_flDelay));
}

/* <25868> ../cstrike/dlls/buttons.cpp:1214 */
void CEnvSpark::SparkStop(CBaseEntity *pActivator, CBaseEntity *pCaller, USE_TYPE useType, float value)
{
	SetUse(&CEnvSpark::SparkStart);
	SetThink(NULL);
}

/* <28011> ../cstrike/dlls/buttons.cpp:1233 */
LINK_ENTITY_TO_CLASS(button_target, CButtonTarget);

/* <258ca> ../cstrike/dlls/buttons.cpp:1235 */
void CButtonTarget::__MAKE_VHOOK(Spawn)(void)
{
	pev->movetype = MOVETYPE_PUSH;
	pev->solid = SOLID_BSP;

	SET_MODEL(ENT(pev), STRING(pev->model));
	pev->takedamage = DAMAGE_YES;

	if (pev->spawnflags & SF_BTARGET_ON)
	{
		pev->frame = 1;
	}
}

/* <25fc3> ../cstrike/dlls/buttons.cpp:1246 */
void CButtonTarget::__MAKE_VHOOK(Use)(CBaseEntity *pActivator, CBaseEntity *pCaller, USE_TYPE useType, float value)
{
	if (!ShouldToggle(useType, (int)pev->frame))
		return;

	pev->frame = 1 - pev->frame;

	if (pev->frame)
	{
		SUB_UseTargets(pActivator, USE_ON, 0);
	}
	else
		SUB_UseTargets(pActivator, USE_OFF, 0);
}

/* <258f1> ../cstrike/dlls/buttons.cpp:1258 */
int CButtonTarget::__MAKE_VHOOK(ObjectCaps)(void)
{
	int caps = CBaseEntity::ObjectCaps() & ~FCAP_ACROSS_TRANSITION;

	if (pev->spawnflags & SF_BTARGET_USE)
		return caps | FCAP_IMPULSE_USE;
	else
		return caps;
}

/* <2592e> ../cstrike/dlls/buttons.cpp:1269 */
int CButtonTarget::__MAKE_VHOOK(TakeDamage)(entvars_t *pevInflictor, entvars_t *pevAttacker, float flDamage, int bitsDamageType)
{
	Use(Instance(pevAttacker), this, USE_TOGGLE, 0);

	return 1;
}

#ifdef HOOK_GAMEDLL

void CBaseButton::Spawn(void)
{
	Spawn_();
}

void CBaseButton::Precache(void)
{
	Precache_();
}

void CBaseButton::KeyValue(KeyValueData *pkvd)
{
	KeyValue_(pkvd);
}

int CBaseButton::TakeDamage(entvars_t *pevInflictor, entvars_t *pevAttacker, float flDamage, int bitsDamageType)
{
	return TakeDamage_(pevInflictor, pevAttacker, flDamage, bitsDamageType);
}

int CBaseButton::Save(CSave &save)
{
	return Save_(save);
}

int CBaseButton::Restore(CRestore &restore)
{
	return Restore_(restore);
}

void CEnvGlobal::Spawn(void)
{
	Spawn_();
}

void CEnvGlobal::KeyValue(KeyValueData *pkvd)
{
	KeyValue_(pkvd);
}

int CEnvGlobal::Save(CSave &save)
{
	return Save_(save);
}

int CEnvGlobal::Restore(CRestore &restore)
{
	return Restore_(restore);
}

void CEnvGlobal::Use(CBaseEntity *pActivator, CBaseEntity *pCaller, USE_TYPE useType, float value)
{
	Use_(pActivator, pCaller, useType, value);
}

void CMultiSource::Spawn(void)
{
	Spawn_();
}

void CMultiSource::KeyValue(KeyValueData *pkvd)
{
	KeyValue_(pkvd);
}

void CMultiSource::Use(CBaseEntity *pActivator, CBaseEntity *pCaller, USE_TYPE useType, float value)
{
	Use_(pActivator, pCaller, useType, value);
}

BOOL CMultiSource::IsTriggered(CBaseEntity *pActivator)
{
	return IsTriggered_(pActivator);
}

int CMultiSource::Save(CSave &save)
{
	return Save_(save);
}

int CMultiSource::Restore(CRestore &restore)
{
	return Restore_(restore);
}

void CRotButton::Spawn(void)
{
	Spawn_();
}

void CMomentaryRotButton::Spawn(void)
{
	Spawn_();
}

void CMomentaryRotButton::KeyValue(KeyValueData *pkvd)
{
	KeyValue_(pkvd);
}

int CMomentaryRotButton::Save(CSave &save)
{
	return Save_(save);
}

int CMomentaryRotButton::Restore(CRestore &restore)
{
	return Restore_(restore);
}

void CMomentaryRotButton::Use(CBaseEntity *pActivator, CBaseEntity *pCaller, USE_TYPE useType, float value)
{
	Use_(pActivator, pCaller, useType, value);
}

void CEnvSpark::Spawn(void)
{
	Spawn_();
}

void CEnvSpark::Precache(void)
{
	Precache_();
}

void CEnvSpark::KeyValue(KeyValueData *pkvd)
{
	KeyValue_(pkvd);
}

int CEnvSpark::Save(CSave &save)
{
	return Save_(save);
}

int CEnvSpark::Restore(CRestore &restore)
{
	return Restore_(restore);
}

void CButtonTarget::Spawn(void)
{
	Spawn_();
}

int CButtonTarget::ObjectCaps(void)
{
	return ObjectCaps_();
}

int CButtonTarget::TakeDamage(entvars_t *pevInflictor, entvars_t *pevAttacker, float flDamage, int bitsDamageType)
{
	return TakeDamage_(pevInflictor, pevAttacker, flDamage, bitsDamageType);
}

void CButtonTarget::Use(CBaseEntity *pActivator, CBaseEntity *pCaller, USE_TYPE useType, float value)
{
	Use_(pActivator, pCaller, useType, value);
}

#endif // HOOK_GAMEDLL

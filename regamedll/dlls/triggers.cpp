#include "precompiled.h"

// Global Savedata for changelevel friction modifier
TYPEDESCRIPTION CFrictionModifier::m_SaveData[] =
{
	DEFINE_FIELD(CFrictionModifier, m_frictionFraction, FIELD_FLOAT),
};

LINK_ENTITY_TO_CLASS(func_friction, CFrictionModifier, CCSFrictionModifier)
IMPLEMENT_SAVERESTORE(CFrictionModifier, CBaseEntity)

void CFrictionModifier::Spawn()
{
	pev->solid = SOLID_TRIGGER;

	// set size and link into world
	SET_MODEL(ENT(pev), STRING(pev->model));

	pev->movetype = MOVETYPE_NONE;
	SetTouch(&CFrictionModifier::ChangeFriction);
}

// Sets toucher's friction to m_frictionFraction (1.0 = normal friction)
void CFrictionModifier::ChangeFriction(CBaseEntity *pOther)
{
	if (pOther->pev->movetype != MOVETYPE_BOUNCEMISSILE && pOther->pev->movetype != MOVETYPE_BOUNCE)
	{
		pOther->pev->friction = m_frictionFraction;
	}
}

// Sets toucher's friction to m_frictionFraction (1.0 = normal friction)
void CFrictionModifier::KeyValue(KeyValueData *pkvd)
{
	if (FStrEq(pkvd->szKeyName, "modifier"))
	{
		m_frictionFraction = Q_atof(pkvd->szValue) / 100.0f;
		pkvd->fHandled = TRUE;
	}
	else
	{
		CBaseEntity::KeyValue(pkvd);
	}
}

TYPEDESCRIPTION CAutoTrigger::m_SaveData[] =
{
	DEFINE_FIELD(CAutoTrigger, m_globalstate, FIELD_STRING),
	DEFINE_FIELD(CAutoTrigger, m_triggerType, FIELD_INTEGER),
};

LINK_ENTITY_TO_CLASS(trigger_auto, CAutoTrigger, CCSAutoTrigger)
IMPLEMENT_SAVERESTORE(CAutoTrigger, CBaseDelay)

void CAutoTrigger::KeyValue(KeyValueData *pkvd)
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
			m_triggerType = USE_OFF;
			break;
		case 2:
			m_triggerType = USE_TOGGLE;
			break;
		default:
			m_triggerType = USE_ON;
			break;
		}
		pkvd->fHandled = TRUE;
	}
	else
	{
		CBaseDelay::KeyValue(pkvd);
	}
}

void CAutoTrigger::Spawn()
{
	Precache();
}

void CAutoTrigger::Precache()
{
	pev->nextthink = gpGlobals->time + 0.1f;
}

void CAutoTrigger::Think()
{
	if (!m_globalstate || gGlobalState.EntityGetState(m_globalstate) == GLOBAL_ON)
	{
		SUB_UseTargets(this, m_triggerType, 0);

#ifdef REGAMEDLL_FIXES
		if (pev->spawnflags & SF_AUTO_NORESET)
#else
		if (pev->spawnflags & SF_AUTO_FIREONCE)
#endif
		{
			UTIL_Remove(this);
		}
	}
}

#ifdef REGAMEDLL_FIXES
void CAutoTrigger::Restart()
{
	if (pev->spawnflags & SF_AUTO_NORESET)
		return;

	pev->nextthink = gpGlobals->time + 0.1f;
}
#endif

TYPEDESCRIPTION CTriggerRelay::m_SaveData[] =
{
	DEFINE_FIELD(CTriggerRelay, m_triggerType, FIELD_INTEGER),
};

LINK_ENTITY_TO_CLASS(trigger_relay, CTriggerRelay, CCSTriggerRelay)
IMPLEMENT_SAVERESTORE(CTriggerRelay, CBaseDelay)

void CTriggerRelay::KeyValue(KeyValueData *pkvd)
{
	if (FStrEq(pkvd->szKeyName, "triggerstate"))
	{
		int type = Q_atoi(pkvd->szValue);
		switch (type)
		{
		case 0:
			m_triggerType = USE_OFF;
			break;
		case 2:
			m_triggerType = USE_TOGGLE;
			break;
		default:
			m_triggerType = USE_ON;
			break;
		}
		pkvd->fHandled = TRUE;
	}
	else
	{
		CBaseDelay::KeyValue(pkvd);
	}
}

void CTriggerRelay::Spawn()
{
	;
}

void CTriggerRelay::Use(CBaseEntity *pActivator, CBaseEntity *pCaller, USE_TYPE useType, float value)
{
	SUB_UseTargets(this, m_triggerType, 0);
	if (pev->spawnflags & SF_RELAY_FIREONCE)
	{
		UTIL_Remove(this);
	}
}

// Global Savedata for multi_manager
TYPEDESCRIPTION CMultiManager::m_SaveData[] =
{
	DEFINE_FIELD(CMultiManager, m_cTargets, FIELD_INTEGER),
	DEFINE_FIELD(CMultiManager, m_index, FIELD_INTEGER),
	DEFINE_FIELD(CMultiManager, m_startTime, FIELD_TIME),
	DEFINE_ARRAY(CMultiManager, m_iTargetName, FIELD_STRING, MAX_MM_TARGETS),
	DEFINE_ARRAY(CMultiManager, m_flTargetDelay, FIELD_FLOAT, MAX_MM_TARGETS),
};

LINK_ENTITY_TO_CLASS(multi_manager, CMultiManager, CCSMultiManager)
IMPLEMENT_SAVERESTORE(CMultiManager, CBaseToggle)

void CMultiManager::KeyValue(KeyValueData *pkvd)
{
	if (FStrEq(pkvd->szKeyName, "wait"))
	{
		m_flWait = Q_atof(pkvd->szValue);
		pkvd->fHandled = TRUE;
	}
	else // add this field to the target list
	{
		// this assumes that additional fields are targetnames and their values are delay values.
		if (m_cTargets < MAX_MM_TARGETS)
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

void CMultiManager::Spawn()
{
	pev->solid = SOLID_NOT;
	SetUse(&CMultiManager::ManagerUse);
	SetThink(&CMultiManager::ManagerThink);

	// Sort targets
	// Quick and dirty bubble sort
	bool bSwapped = true;

	while (bSwapped)
	{
		bSwapped = false;
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
				bSwapped = true;
			}
		}
	}
}

void CMultiManager::Restart()
{
#ifndef REGAMEDLL_FIXES
	edict_t *pentTarget = nullptr;

	for (int i = 0; i < m_cTargets; i++)
	{
		const char *name = STRING(m_iTargetName[i]);

		if (!name)
			continue;

		pentTarget = FIND_ENTITY_BY_TARGETNAME(pentTarget, STRING(pev->target));

		if (FNullEnt(pentTarget))
			break;

		CBaseEntity *pTarget = static_cast<CBaseEntity *>(CBaseEntity::Instance(pentTarget));
		if (pTarget && !(pTarget->pev->flags & FL_KILLME))
		{
			pTarget->Restart();
		}
	}
#endif

	SetThink(nullptr);

	if (IsClone())
	{
		UTIL_Remove(this);
		return;
	}

	SetUse(&CMultiManager::ManagerUse);
	m_index = 0;
}

BOOL CMultiManager::HasTarget(string_t targetname)
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
void CMultiManager::ManagerThink()
{
	float time;

	time = gpGlobals->time - m_startTime;
	while (m_index < m_cTargets && m_flTargetDelay[m_index] <= time)
	{
		FireTargets(STRING(m_iTargetName[m_index]), m_hActivator, this, USE_TOGGLE, 0);
		m_index++;
	}

	// have we fired all targets?
	if (m_index >= m_cTargets)
	{
		SetThink(nullptr);
		if (IsClone())
		{
			UTIL_Remove(this);
			return;
		}

		// allow manager re-use
		SetUse(&CMultiManager::ManagerUse);
	}
	else
	{
		pev->nextthink = m_startTime + m_flTargetDelay[m_index];
	}
}

CMultiManager *CMultiManager::Clone()
{
	CMultiManager *pMulti = GetClassPtr<CCSMultiManager>((CMultiManager *)nullptr);

	edict_t *pEdict = pMulti->pev->pContainingEntity;
	Q_memcpy(pMulti->pev, pev, sizeof(*pev));

	pMulti->pev->pContainingEntity = pEdict;
	pMulti->pev->spawnflags |= SF_MULTIMAN_CLONE;
	pMulti->m_cTargets = m_cTargets;

	Q_memcpy(pMulti->m_iTargetName, m_iTargetName, sizeof(m_iTargetName));
	Q_memcpy(pMulti->m_flTargetDelay, m_flTargetDelay, sizeof(m_flTargetDelay));

#ifdef REGAMEDLL_FIXES
	// Add entity in hash table, otherwise,
	// it will not be reset for the entity via UTIL_RestartRound
	MAKE_STRING_CLASS("multi_manager", pMulti->pev);
#endif

	return pMulti;
}

// The USE function builds the time table and starts the entity thinking.
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
	SetUse(nullptr);
	SetThink(&CMultiManager::ManagerThink);

	pev->nextthink = gpGlobals->time;
}

LINK_ENTITY_TO_CLASS(env_render, CRenderFxManager, CCSRenderFxManager)

void CRenderFxManager::Spawn()
{
	pev->solid = SOLID_NOT;
}

#ifdef REGAMEDLL_FIXES

void CRenderFxManager::OnDestroy()
{
	m_RenderGroups.Purge();
}

void CRenderFxManager::Restart()
{
	if (FStringNull(pev->target))
		return;

	edict_t *pentTarget = nullptr;
	while ((pentTarget = FIND_ENTITY_BY_TARGETNAME(pentTarget, STRING(pev->target))))
	{
		if (FNullEnt(pentTarget))
			break;

		entvars_t *pevTarget = VARS(pentTarget);

		// find render groups in our list of backup
		int index = m_RenderGroups.Find(ENTINDEX(pevTarget));
		if (index == m_RenderGroups.InvalidIndex()) {
			// not found
			continue;
		}

		RenderGroup_t *pGroup = &m_RenderGroups[index];
		if (!(pev->spawnflags & SF_RENDER_MASKFX))
			pevTarget->renderfx = pGroup->renderfx;

		if (!(pev->spawnflags & SF_RENDER_MASKAMT))
			pevTarget->renderamt = pGroup->renderamt;

		if (!(pev->spawnflags & SF_RENDER_MASKMODE))
			pevTarget->rendermode = pGroup->rendermode;

		if (!(pev->spawnflags & SF_RENDER_MASKCOLOR))
			pevTarget->rendercolor = pGroup->rendercolor;
	}
}

#endif // REGAMEDLL_FIXES

void CRenderFxManager::Use(CBaseEntity *pActivator, CBaseEntity *pCaller, USE_TYPE useType, float value)
{
	if (FStringNull(pev->target))
		return;

	edict_t *pentTarget = nullptr;
	while ((pentTarget = FIND_ENTITY_BY_TARGETNAME(pentTarget, STRING(pev->target))))
	{
		if (FNullEnt(pentTarget))
			break;

		entvars_t *pevTarget = VARS(pentTarget);

#ifdef REGAMEDLL_FIXES
		RenderGroup_t group;
		group.renderfx = pevTarget->renderfx;
		group.renderamt = pevTarget->renderamt;
		group.rendermode = pevTarget->rendermode;
		group.rendercolor = pevTarget->rendercolor;

		int entityIndex = ENTINDEX(pevTarget);
		if (m_RenderGroups.Find(entityIndex) == m_RenderGroups.InvalidIndex()) {
			m_RenderGroups.Insert(entityIndex, group);
		}
#endif

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

LINK_ENTITY_TO_CLASS(trigger, CBaseTrigger, CCSTrigger)

void CBaseTrigger::InitTrigger()
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
void CBaseTrigger::KeyValue(KeyValueData *pkvd)
{
	if (FStrEq(pkvd->szKeyName, "damage"))
	{
		pev->dmg = Q_atof(pkvd->szValue);
		pkvd->fHandled = TRUE;
	}
	else if (FStrEq(pkvd->szKeyName, "count"))
	{
		m_cTriggersLeft = Q_atoi(pkvd->szValue);
		pkvd->fHandled = TRUE;
	}
	else if (FStrEq(pkvd->szKeyName, "damagetype"))
	{
		m_bitsDamageInflict = Q_atoi(pkvd->szValue);
		pkvd->fHandled = TRUE;
	}
	else
	{
		CBaseToggle::KeyValue(pkvd);
	}
}

LINK_ENTITY_TO_CLASS(trigger_monsterjump, CTriggerMonsterJump, CCSTriggerMonsterJump)

void CTriggerMonsterJump::Spawn()
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

void CTriggerMonsterJump::Think()
{
	// kill the trigger for now UNDONE
	pev->solid = SOLID_NOT;

	// Unlink from trigger list
	UTIL_SetOrigin(pev, pev->origin);
	SetThink(nullptr);
}

void CTriggerMonsterJump::Touch(CBaseEntity *pOther)
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

LINK_ENTITY_TO_CLASS(trigger_cdaudio, CTriggerCDAudio, CCSTriggerCDAudio)

// Changes tracks or stops CD when player touches
// HACK: overloaded HEALTH to avoid adding new field
void CTriggerCDAudio::Touch(CBaseEntity *pOther)
{
	// only clients may trigger these events
	if (!pOther->IsPlayer())
	{
		return;
	}

	PlayTrack(pOther->edict());
}

void CTriggerCDAudio::Spawn()
{
	InitTrigger();
}

void CTriggerCDAudio::Use(CBaseEntity *pActivator, CBaseEntity *pCaller, USE_TYPE useType, float value)
{
	PlayTrack(pCaller->edict());
}

#ifdef REGAMEDLL_FIXES
const char *g_szMP3trackFileMap[] =
{
	"", "",
	"media/Half-Life01.mp3",
	"media/Prospero01.mp3",
	"media/Half-Life12.mp3",
	"media/Half-Life07.mp3",
	"media/Half-Life10.mp3",
	"media/Suspense01.mp3",
	"media/Suspense03.mp3",
	"media/Half-Life09.mp3",
	"media/Half-Life02.mp3",
	"media/Half-Life13.mp3",
	"media/Half-Life04.mp3",
	"media/Half-Life15.mp3",
	"media/Half-Life14.mp3",
	"media/Half-Life16.mp3",
	"media/Suspense02.mp3",
	"media/Half-Life03.mp3",
	"media/Half-Life08.mp3",
	"media/Prospero02.mp3",
	"media/Half-Life05.mp3",
	"media/Prospero04.mp3",
	"media/Half-Life11.mp3",
	"media/Half-Life06.mp3",
	"media/Prospero03.mp3",
	"media/Half-Life17.mp3",
	"media/Prospero05.mp3",
	"media/Suspense05.mp3",
	"media/Suspense07.mp3"
};
#endif

void PlayCDTrack(edict_t *pClient, int iTrack)
{
	// Can't play if the client is not connected!
	if (!pClient)
		return;

	if (iTrack < -1 || iTrack > 30)
	{
		ALERT(at_console, "TriggerCDAudio - Track %d out of range\n", iTrack);
		return;
	}

	if (iTrack == -1)
	{
#ifdef REGAMEDLL_FIXES
		CLIENT_COMMAND(pClient, "mp3 stop\n");
#else
		CLIENT_COMMAND(pClient, "cd stop\n");
#endif
	}
	else
	{
#ifdef REGAMEDLL_FIXES
		CLIENT_COMMAND(pClient, UTIL_VarArgs("mp3 play %s\n", g_szMP3trackFileMap[iTrack]));
#else
		char string[64];
		Q_sprintf(string, "cd play %3d\n", iTrack);
		CLIENT_COMMAND(pClient, string);
#endif
	}
}

// only plays for ONE client, so only use in single play!
void CTriggerCDAudio::PlayTrack(edict_t *pEdict)
{
	PlayCDTrack(pEdict, int(pev->health));

	SetTouch(nullptr);
	UTIL_Remove(this);
}

LINK_ENTITY_TO_CLASS(target_cdaudio, CTargetCDAudio, CCSTargetCDAudio)

void CTargetCDAudio::KeyValue(KeyValueData *pkvd)
{
	if (FStrEq(pkvd->szKeyName, "radius"))
	{
		pev->scale = Q_atof(pkvd->szValue);
		pkvd->fHandled = TRUE;
	}
	else
	{
		CPointEntity::KeyValue(pkvd);
	}
}

void CTargetCDAudio::Spawn()
{
	pev->solid = SOLID_NOT;
	pev->movetype = MOVETYPE_NONE;

	if (pev->scale > 0)
	{
		pev->nextthink = gpGlobals->time + 1.0f;
	}
}

void CTargetCDAudio::Use(CBaseEntity *pActivator, CBaseEntity *pCaller, USE_TYPE useType, float value)
{
	Play(pCaller->edict());
}

// only plays for ONE client, so only use in single play!
void CTargetCDAudio::Think()
{
	// manually find the single player.
	edict_t *pClient = INDEXENT(1);

	// Can't play if the client is not connected!
	if (!pClient)
		return;

	pev->nextthink = gpGlobals->time + 0.5f;

	if ((pClient->v.origin - pev->origin).Length() <= pev->scale)
	{
		Play(pClient);
	}
}

void CTargetCDAudio::Play(edict_t *pEdict)
{
	PlayCDTrack(pEdict, int(pev->health));
	UTIL_Remove(this);
}

LINK_ENTITY_TO_CLASS(trigger_hurt, CTriggerHurt, CCSTriggerHurt)

void CTriggerHurt::Spawn()
{
	InitTrigger();
	SetTouch(&CTriggerHurt::HurtTouch);

	if (!FStringNull(pev->targetname))
	{
		SetUse(&CTriggerHurt::ToggleUse);
	}
	else
	{
		SetUse(nullptr);
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

#ifdef REGAMEDLL_FIXES
void CTriggerHurt::Restart()
{
	Vector mins, maxs;

	// Set model is about to destroy these
	mins = pev->mins;
	maxs = pev->maxs;

	Spawn();

	UTIL_SetSize(pev, mins, maxs);
}
#endif

// trigger hurt that causes radiation will do a radius
// check and set the player's geiger counter level
// according to distance from center of trigger
void CTriggerHurt::RadiationThink()
{
	edict_t *pentPlayer;
	CBasePlayer *pPlayer = nullptr;
	real_t flRange;
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

	pev->origin = (pev->absmin + pev->absmax) * 0.5f;
	pev->view_ofs = pev->view_ofs * 0.0f;

	pentPlayer = FIND_CLIENT_IN_PVS(edict());

	pev->origin = origin;
	pev->view_ofs = view_ofs;

	// reset origin
	if (!FNullEnt(pentPlayer))
	{
		pPlayer = GetClassPtr<CCSPlayer>((CBasePlayer *)VARS(pentPlayer));

		pevTarget = VARS(pentPlayer);

		// get range to player;
		vecSpot1 = (pev->absmin + pev->absmax) * 0.5f;
		vecSpot2 = (pevTarget->absmin + pevTarget->absmax) * 0.5f;

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

	pev->nextthink = gpGlobals->time + 0.25f;
}

// ToggleUse - If this is the USE function for a trigger, its state will toggle every time it's fired
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

	// HACKHACK: In multiplayer, players touch this based on packet receipt.
	// So the players who send packets later aren't always hurt.  Keep track of
	// how much time has passed and whether or not you've touched that player
	if (g_pGameRules->IsMultiplayer())
	{
		if (pev->dmgtime > gpGlobals->time)
		{
#ifdef REGAMEDLL_FIXES
			if (gpGlobals->time >= pev->pain_finished)
#else
			if (gpGlobals->time != pev->pain_finished)
#endif
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
		// Original code: single player
#ifdef REGAMEDLL_FIXES
		if (pev->dmgtime > gpGlobals->time && gpGlobals->time >= pev->pain_finished)
#else
		if (pev->dmgtime > gpGlobals->time && gpGlobals->time != pev->pain_finished)
#endif
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
	fldmg = pev->dmg * 0.5f;

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
	pev->dmgtime = gpGlobals->time + 0.5f;

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

LINK_ENTITY_TO_CLASS(trigger_multiple, CTriggerMultiple, CCSTriggerMultiple)

void CTriggerMultiple::Spawn()
{
	if (m_flWait == 0.0f)
		m_flWait = 0.2f;

	InitTrigger();

	assert(("trigger_multiple with health", pev->health == 0));

	//UTIL_SetOrigin(pev, pev->origin);
	//SET_MODEL(ENT(pev), STRING(pev->model));

	//if (pev->health > 0)
	//{
	//	if (pev->spawnflags & SF_TRIGGER_MULTIPLE_NOTOUCH)
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

LINK_ENTITY_TO_CLASS(trigger_once, CTriggerOnce, CCSTriggerOnce)

void CTriggerOnce::Spawn()
{
#ifdef REGAMEDLL_FIXES
	m_flWait = -2;
#else
	m_flWait = -1;
#endif

	CTriggerMultiple::Spawn();
}

#ifdef REGAMEDLL_FIXES
void CTriggerOnce::Restart()
{
	m_flWait = -2;
	CTriggerMultiple::Spawn();
}
#endif

void CBaseTrigger::MultiTouch(CBaseEntity *pOther)
{
	entvars_t *pevToucher = pOther->pev;

	// Only touch clients, monsters, or pushables (depending on flags)
	if (((pevToucher->flags & FL_CLIENT) && !(pev->spawnflags & SF_TRIGGER_NOCLIENTS))
		|| ((pevToucher->flags & FL_MONSTER) && (pev->spawnflags & SF_TRIGGER_ALLOWMONSTERS))
		|| ((pev->spawnflags & SF_TRIGGER_PUSHABLES) && FClassnameIs(pevToucher, "func_pushable")))
	{
		ActivateMultiTrigger(pOther);
	}
}

// the trigger was just touched/killed/used
// self.enemy should be set to the activator so it can be held through a delay
// so wait for the delay time before firing
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
		if (pev->enemy == nullptr || !FClassnameIs(pev->enemy, "player"))
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
		SetTouch(nullptr);
		pev->nextthink = gpGlobals->time + 0.1f;

#ifdef REGAMEDLL_FIXES
		if (!(pev->spawnflags & SF_TRIGGER_NORESET) && m_flWait == -2)
			SetThink(nullptr);
		else
#endif
			SetThink(&CBaseTrigger::SUB_Remove);
	}
}

// the wait time has passed, so set back up for another activation
void CBaseTrigger::MultiWaitOver()
{
	SetThink(nullptr);
}

void CBaseTrigger::CounterUse(CBaseEntity *pActivator, CBaseEntity *pCaller, USE_TYPE useType, float value)
{
	m_cTriggersLeft--;
	m_hActivator = pActivator;

	if (m_cTriggersLeft < 0)
	{
		return;
	}

	BOOL fTellActivator = (m_hActivator && FClassnameIs(m_hActivator->pev, "player") && !(pev->spawnflags & SF_TRIGGER_COUNTER_NOMESSAGE));

	if (m_cTriggersLeft != 0)
	{
		if (fTellActivator)
		{
			// UNDONE: I don't think we want these Quakesque messages
			switch (m_cTriggersLeft)
			{
			case 1:  ALERT(at_console, "Only 1 more to go..."); break;
			case 2:  ALERT(at_console, "Only 2 more to go..."); break;
			case 3:  ALERT(at_console, "Only 3 more to go..."); break;
			default: ALERT(at_console, "There are more to go..."); break;
			}
		}

		return;
	}

	// UNDONE: I don't think we want these Quakesque messages
	if (fTellActivator)
	{
		ALERT(at_console, "Sequence completed!");
	}

	ActivateMultiTrigger(m_hActivator);
}

LINK_ENTITY_TO_CLASS(trigger_counter, CTriggerCounter, CCSTriggerCounter)

void CTriggerCounter::Spawn()
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

LINK_ENTITY_TO_CLASS(trigger_transition, CTriggerVolume, CCSTriggerVolume)

// Define space that travels across a level transition
void CTriggerVolume::Spawn()
{
	pev->solid = SOLID_NOT;
	pev->movetype = MOVETYPE_NONE;

	// set size and link into world
	SET_MODEL(ENT(pev), STRING(pev->model));

	pev->model = 0;
	pev->modelindex = 0;
}

LINK_ENTITY_TO_CLASS(fireanddie, CFireAndDie, CCSFireAndDie)

void CFireAndDie::Spawn()
{
	MAKE_STRING_CLASS("fireanddie", pev);
	// Don't call Precache() - it should be called on restore
}

void CFireAndDie::Precache()
{
	pev->nextthink = gpGlobals->time + m_flDelay;
}

void CFireAndDie::Think()
{
	SUB_UseTargets(this, USE_TOGGLE, 0);
	UTIL_Remove(this);
}

// Global Savedata for changelevel trigger
TYPEDESCRIPTION CChangeLevel::m_SaveData[] =
{
	DEFINE_ARRAY(CChangeLevel, m_szMapName, FIELD_CHARACTER, MAX_MAPNAME_LENGHT),
	DEFINE_ARRAY(CChangeLevel, m_szLandmarkName, FIELD_CHARACTER, MAX_MAPNAME_LENGHT),
	DEFINE_FIELD(CChangeLevel, m_changeTarget, FIELD_STRING),
	DEFINE_FIELD(CChangeLevel, m_changeTargetDelay, FIELD_FLOAT),
};

LINK_ENTITY_TO_CLASS(trigger_changelevel, CChangeLevel, CCSChangeLevel)
IMPLEMENT_SAVERESTORE(CChangeLevel, CBaseTrigger)

// Cache user-entity-field values until spawn is called.
void CChangeLevel::KeyValue(KeyValueData *pkvd)
{
	if (FStrEq(pkvd->szKeyName, "map"))
	{
		if (Q_strlen(pkvd->szValue) >= MAX_MAPNAME_LENGHT)
		{
			ALERT(at_error, "Map name '%s' too long (32 chars)\n", pkvd->szValue);
		}

		Q_strcpy(m_szMapName, pkvd->szValue);
		pkvd->fHandled = TRUE;
	}
	else if (FStrEq(pkvd->szKeyName, "landmark"))
	{
		if (Q_strlen(pkvd->szValue) >= MAX_MAPNAME_LENGHT)
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
#ifdef REGAMEDLL_FIXES
	else if (FStrEq(pkvd->szKeyName, "percent_of_players"))
	{
		m_flPercentOfPlayers = Q_atof(pkvd->szValue);
		m_flPercentOfPlayers = clamp(m_flPercentOfPlayers, 0.0f, 1.0f);
		pkvd->fHandled = TRUE;
	}
#endif
	else
	{
		CBaseTrigger::KeyValue(pkvd);
	}
}

void CChangeLevel::Spawn()
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

void CChangeLevel::ExecuteChangeLevel()
{
	MESSAGE_BEGIN(MSG_ALL, SVC_CDTRACK);
		WRITE_BYTE(3);
		WRITE_BYTE(3);
	MESSAGE_END();

	MESSAGE_BEGIN(MSG_ALL, SVC_INTERMISSION);
	MESSAGE_END();
}

edict_t *CChangeLevel::FindLandmark(const char *pLandmarkName)
{
	edict_t	*pentLandmark = FIND_ENTITY_BY_STRING(nullptr, "targetname", pLandmarkName);
	while (!FNullEnt(pentLandmark))
	{
		// Found the landmark
		if (FClassnameIs(pentLandmark, "info_landmark"))
			return pentLandmark;
		else
			pentLandmark = FIND_ENTITY_BY_STRING(pentLandmark, "targetname", pLandmarkName);
	}

	ALERT(at_error, "Can't find landmark %s\n", pLandmarkName);
	return nullptr;
}

// CChangeLevel::Use - allows level transitions to be
// triggered by buttons, etc.
void CChangeLevel::UseChangeLevel(CBaseEntity *pActivator, CBaseEntity *pCaller, USE_TYPE useType, float value)
{
	ChangeLevelNow(pActivator);
}

char st_szNextMap[MAX_MAPNAME_LENGHT];
char st_szNextSpot[MAX_MAPNAME_LENGHT];

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
		CFireAndDie *pFireAndDie = GetClassPtr<CCSFireAndDie>((CFireAndDie *)nullptr);

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

	// Init landmark to nullptr
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

void CChangeLevel::TouchChangeLevel(CBaseEntity *pOther)
{
	if (!pOther->IsPlayer())
		return;

#ifdef REGAMEDLL_FIXES
	if (m_flPercentOfPlayers > 0.0f)
	{
		int playersInCount = 0;
		int playersOutCount = 0;
		int playersCount = UTIL_CountPlayersInBrushVolume(true, this, playersInCount, playersOutCount);

		if (m_flPercentOfPlayers > float(playersInCount / playersCount))
			return;
	}
#endif

	ChangeLevelNow(pOther);
}

// Add a transition to the list, but ignore duplicates
// (a designer may have placed multiple trigger_changelevels with the same landmark)
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

	Q_strcpy(pLevelList[listCount].mapName, pMapName);
	Q_strcpy(pLevelList[listCount].landmarkName, pLandmarkName);

	pLevelList[listCount].pentLandmark = pentLandmark;
	pLevelList[listCount].vecLandmarkOrigin = VARS(pentLandmark)->origin;

	return 1;
}

int BuildChangeList(LEVELLIST *pLevelList, int maxList)
{
	return CChangeLevel::ChangeList(pLevelList, maxList);
}

int CChangeLevel::InTransitionVolume(CBaseEntity *pEntity, char *pVolumeName)
{
	if (pEntity->ObjectCaps() & FCAP_FORCE_TRANSITION)
		return 1;

	// If you're following another entity, follow it through the transition (weapons follow the player)
	if (pEntity->pev->movetype == MOVETYPE_FOLLOW)
	{
		if (pEntity->pev->aiment)
		{
			pEntity = CBaseEntity::Instance(pEntity->pev->aiment);
		}
	}

	// Unless we find a trigger_transition, everything is in the volume
	int inVolume = 1;

	edict_t	*pentVolume = FIND_ENTITY_BY_TARGETNAME(nullptr, pVolumeName);
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
int CChangeLevel::ChangeList(LEVELLIST *pLevelList, int maxList)
{
	edict_t	*pentChangelevel, *pentLandmark;
	int i, count = 0;

	// Find all of the possible level changes on this BSP
	pentChangelevel = FIND_ENTITY_BY_STRING(nullptr, "classname", "trigger_changelevel");

	if (FNullEnt(pentChangelevel))
		return 0;

	while (!FNullEnt(pentChangelevel))
	{
		CChangeLevel *pTrigger = GetClassPtr<CCSChangeLevel>((CChangeLevel *)VARS(pentChangelevel));
		if (pTrigger)
		{
			// Find the corresponding landmark
			pentLandmark = FindLandmark(pTrigger->m_szLandmarkName);
			if (pentLandmark)
			{
				// Build a list of unique transitions
				if (AddTransitionToList(pLevelList, count, pTrigger->m_szMapName, pTrigger->m_szLandmarkName, pentLandmark))
				{
					count++;

					// FULL!
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
			// We can only ever move 512 entities across a transition
			const int MAX_ENTITY = 512;

			int j, entityCount = 0;
			CBaseEntity *pEntList[MAX_ENTITY];
			int entityFlags[MAX_ENTITY];

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
							pEntList[entityCount] = pEntity;
							entityFlags[entityCount] = flags;
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
NOXREF void NextLevel()
{
	edict_t *pent;
	CChangeLevel *pChange;

	// find a trigger_changelevel
	pent = FIND_ENTITY_BY_CLASSNAME(nullptr, "trigger_changelevel");

	// go back to start if no trigger_changelevel
	if (FNullEnt(pent))
	{
		gpGlobals->mapname = ALLOC_STRING("start");
		pChange = GetClassPtr<CCSChangeLevel>((CChangeLevel *)nullptr);
		Q_strcpy(pChange->m_szMapName, "start");
	}
	else
		pChange = GetClassPtr<CCSChangeLevel>((CChangeLevel *)VARS(pent));

	Q_strcpy(st_szNextMap, pChange->m_szMapName);
	g_pGameRules->SetGameOver();

	if (pChange->pev->nextthink < gpGlobals->time)
	{
		pChange->SetThink(&CChangeLevel::ExecuteChangeLevel);
		pChange->pev->nextthink = gpGlobals->time + 0.1f;
	}
}

LINK_ENTITY_TO_CLASS(func_ladder, CLadder, CCSLadder)

void CLadder::KeyValue(KeyValueData *pkvd)
{
	CBaseTrigger::KeyValue(pkvd);
}

// func_ladder - makes an area vertically negotiable
void CLadder::Precache()
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

void CLadder::Spawn()
{
	Precache();

	// set size and link into world
	SET_MODEL(ENT(pev), STRING(pev->model));
	pev->movetype = MOVETYPE_PUSH;
}

LINK_ENTITY_TO_CLASS(trigger_push, CTriggerPush, CCSTriggerPush)

void CTriggerPush::KeyValue(KeyValueData *pkvd)
{
	CBaseTrigger::KeyValue(pkvd);
}

void CTriggerPush::Spawn()
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

#ifdef REGAMEDLL_FIXES
void CTriggerPush::Restart()
{
	auto tempDir = pev->movedir;
	Spawn();
	pev->movedir = tempDir;
}
#endif

void CTriggerPush::Touch(CBaseEntity *pOther)
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
		if (pev->spawnflags & SF_TRIGGER_PUSH_ONCE)
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

void CBaseTrigger::TeleportTouch(CBaseEntity *pOther)
{
	entvars_t *pevToucher = pOther->pev;
	edict_t	*pentTarget = nullptr;

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

LINK_ENTITY_TO_CLASS(trigger_teleport, CTriggerTeleport, CCSTriggerTeleport)

void CTriggerTeleport::Spawn()
{
	InitTrigger();
	SetTouch(&CTriggerTeleport::TeleportTouch);
}

LINK_ENTITY_TO_CLASS(info_teleport_destination, CPointEntity, CCSPointEntity)
LINK_ENTITY_TO_CLASS(func_buyzone, CBuyZone, CCSBuyZone)

void CBuyZone::Spawn()
{
	InitTrigger();
	SetTouch(&CBuyZone::BuyTouch);

	if (pev->team > CT || pev->team < UNASSIGNED)
	{
		ALERT(at_console, "Bad team number (%i) in func_buyzone\n", pev->team);
		pev->team = UNASSIGNED;
	}
}

void CBuyZone::BuyTouch(CBaseEntity *pOther)
{
#ifdef REGAMEDLL_ADD
	if (buytime.value == 0.0f)
		return;
#endif

	if (!pOther->IsPlayer())
		return;

	CBasePlayer *pPlayer = static_cast<CBasePlayer *>(pOther);

	if (pev->team == UNASSIGNED || pev->team == pPlayer->m_iTeam)
	{
#ifdef REGAMEDLL_FIXES
		if (!CSGameRules()->CanPlayerBuy(pPlayer))
			return;
#endif

		pPlayer->m_signals.Signal(SIGNAL_BUY);
	}
}

LINK_ENTITY_TO_CLASS(func_bomb_target, CBombTarget, CCSBombTarget)

void CBombTarget::Spawn()
{
	InitTrigger();

	SetTouch(&CBombTarget::BombTargetTouch);
	SetUse(&CBombTarget::BombTargetUse);
}

bool CBombTarget::IsPlayerInBombSite(CBasePlayer *pPlayer)
{
	const Vector &absmin = pPlayer->pev->absmin;
	const Vector &absmax = pPlayer->pev->absmax;

	// Ensure that player's body is inside func_bomb_target's X,Y axes.
	if (pev->absmin.x > absmin.x || pev->absmin.y > absmin.y)
	{
		return false;
	}
	if (pev->absmax.x < absmax.x || pev->absmax.y < absmax.y)
	{
		return false;
	}

	return true;
}

void CBombTarget::BombTargetTouch(CBaseEntity *pOther)
{
	if (!pOther->IsPlayer())
		return;

	CBasePlayer *pPlayer = static_cast<CBasePlayer *>(pOther);

	if (pPlayer->m_bHasC4
#ifdef REGAMEDLL_FIXES
		&& (legacy_bombtarget_touch.value || IsPlayerInBombSite(pPlayer))
#endif
	)
	{
		pPlayer->m_signals.Signal(SIGNAL_BOMB);
		pPlayer->m_pentCurBombTarget = ENT(pev);
	}
}

void CBombTarget::BombTargetUse(CBaseEntity *pActivator, CBaseEntity *pCaller, USE_TYPE useType, float value)
{
	SUB_UseTargets(nullptr, USE_TOGGLE, 0);
}

LINK_ENTITY_TO_CLASS(func_hostage_rescue, CHostageRescue, CCSHostageRescue)

void CHostageRescue::Spawn()
{
	InitTrigger();
	SetTouch(&CHostageRescue::HostageRescueTouch);
}

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

LINK_ENTITY_TO_CLASS(func_escapezone, CEscapeZone, CCSEscapeZone)

void CEscapeZone::Spawn()
{
	InitTrigger();
	SetTouch(&CEscapeZone::EscapeTouch);
}

void CEscapeZone::EscapeTouch(CBaseEntity *pOther)
{
	if (!pOther->IsPlayer())
		return;

	CBasePlayer *pEscapee = static_cast<CBasePlayer *>(pOther);

	switch (pEscapee->m_iTeam)
	{
	case TERRORIST:
		if (!pEscapee->m_bEscaped)
		{
			pEscapee->m_bEscaped = true;
			CSGameRules()->CheckWinConditions();

			UTIL_LogPrintf("\"%s<%i><%s><TERRORIST>\" triggered \"Terrorist_Escaped\"\n",
				STRING(pEscapee->pev->netname), GETPLAYERUSERID(pEscapee->edict()), GETPLAYERAUTHID(pEscapee->edict()));

			for (int i = 1; i <= gpGlobals->maxClients; i++)
			{
				CBasePlayer *pPlayer = UTIL_PlayerByIndex(i);

				if (!pPlayer || FNullEnt(pPlayer->pev))
					continue;

				if (pPlayer->m_iTeam == pEscapee->m_iTeam)
				{
					ClientPrint(pPlayer->pev, HUD_PRINTCENTER, "#Terrorist_Escaped");
				}
			}
		}
		break;
	case CT:
		pEscapee->m_signals.Signal(SIGNAL_ESCAPE);
		break;
	}
}

LINK_ENTITY_TO_CLASS(func_vip_safetyzone, CVIP_SafetyZone, CCSVIP_SafetyZone)

void CVIP_SafetyZone::Spawn()
{
	InitTrigger();
	SetTouch(&CVIP_SafetyZone::VIP_SafetyTouch);
}

void CVIP_SafetyZone::VIP_SafetyTouch(CBaseEntity *pOther)
{
	if (!pOther->IsPlayer())
		return;

	CBasePlayer *pEscapee = static_cast<CBasePlayer *>(pOther);
	pEscapee->m_signals.Signal(SIGNAL_VIPSAFETY);

	if (pEscapee->m_bIsVIP)
	{
		UTIL_LogPrintf("\"%s<%i><%s><CT>\" triggered \"Escaped_As_VIP\"\n",
			STRING(pEscapee->pev->netname), GETPLAYERUSERID(pEscapee->edict()), GETPLAYERAUTHID(pEscapee->edict()));

		pEscapee->m_bEscaped = true;

		pEscapee->Disappear();
		pEscapee->AddAccount(REWARD_VIP_HAVE_SELF_RESCUED, RT_VIP_RESCUED_MYSELF);
	}
}

LINK_ENTITY_TO_CLASS(trigger_autosave, CTriggerSave, CCSTriggerSave)

void CTriggerSave::Spawn()
{
	if (g_pGameRules->IsDeathmatch())
	{
		REMOVE_ENTITY(ENT(pev));
		return;
	}

	InitTrigger();
	SetTouch(&CTriggerSave::SaveTouch);
}

void CTriggerSave::SaveTouch(CBaseEntity *pOther)
{
	if (!UTIL_IsMasterTriggered(m_sMaster, pOther))
		return;

	// Only save on clients
	if (!pOther->IsPlayer())
		return;

	SetTouch(nullptr);
	UTIL_Remove(this);
	SERVER_COMMAND("autosave\n");
}

LINK_ENTITY_TO_CLASS(trigger_endsection, CTriggerEndSection, CCSTriggerEndSection)

void CTriggerEndSection::EndSectionUse(CBaseEntity *pActivator, CBaseEntity *pCaller, USE_TYPE useType, float value)
{
	// Only save on clients
	if (pActivator && !pActivator->IsNetClient())
		return;

	SetUse(nullptr);
	if (!FStringNull(pev->message))
	{
		END_SECTION(STRING(pev->message));
	}

	UTIL_Remove(this);
}

void CTriggerEndSection::Spawn()
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

void CTriggerEndSection::EndSectionTouch(CBaseEntity *pOther)
{
	// Only save on clients
	if (!pOther->IsNetClient())
		return;

	SetTouch(nullptr);
	if (!FStringNull(pev->message))
	{
		END_SECTION(STRING(pev->message));
	}

	UTIL_Remove(this);
}

void CTriggerEndSection::KeyValue(KeyValueData *pkvd)
{
	if (FStrEq(pkvd->szKeyName, "section"))
	{
		// Store this in message so we don't have to write save/restore for this ent
		pev->message = ALLOC_STRING(pkvd->szValue);
		pkvd->fHandled = TRUE;
	}
	else
	{
		CBaseTrigger::KeyValue(pkvd);
	}
}

LINK_ENTITY_TO_CLASS(trigger_gravity, CTriggerGravity, CCSTriggerGravity)

void CTriggerGravity::Spawn()
{
	InitTrigger();
	SetTouch(&CTriggerGravity::GravityTouch);
}

void CTriggerGravity::GravityTouch(CBaseEntity *pOther)
{
	// Only save on clients
	if (!pOther->IsPlayer())
		return;

	pOther->pev->gravity = pev->gravity;
}

TYPEDESCRIPTION CTriggerChangeTarget::m_SaveData[] =
{
	DEFINE_FIELD(CTriggerChangeTarget, m_iszNewTarget, FIELD_STRING),
};

LINK_ENTITY_TO_CLASS(trigger_changetarget, CTriggerChangeTarget, CCSTriggerChangeTarget)
IMPLEMENT_SAVERESTORE(CTriggerChangeTarget, CBaseDelay)

void CTriggerChangeTarget::KeyValue(KeyValueData *pkvd)
{
	if (FStrEq(pkvd->szKeyName, "m_iszNewTarget"))
	{
		m_iszNewTarget = ALLOC_STRING(pkvd->szValue);
		pkvd->fHandled = TRUE;
	}
	else
	{
		CBaseDelay::KeyValue(pkvd);
	}
}

void CTriggerChangeTarget::Spawn()
{
	;
}

void CTriggerChangeTarget::Use(CBaseEntity *pActivator, CBaseEntity *pCaller, USE_TYPE useType, float value)
{
	CBaseEntity *pTarget = UTIL_FindEntityByTargetname(nullptr, pev->target);
	if (pTarget)
	{
		pTarget->pev->target = m_iszNewTarget;

		CBaseMonster *pMonster = pTarget->MyMonsterPointer();
		if (pMonster)
		{
			pMonster->m_pGoalEnt = nullptr;
		}
	}
}

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

LINK_ENTITY_TO_CLASS(trigger_camera, CTriggerCamera, CCSTriggerCamera)
IMPLEMENT_SAVERESTORE(CTriggerCamera, CBaseDelay)

void CTriggerCamera::Spawn()
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

void CTriggerCamera::KeyValue(KeyValueData *pkvd)
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
	{
		CBaseDelay::KeyValue(pkvd);
	}
}

void CTriggerCamera::Use(CBaseEntity *pActivator, CBaseEntity *pCaller, USE_TYPE useType, float value)
{
	if (!ShouldToggle(useType, m_state))
		return;

	// Toggle state
	m_state = !m_state;
	if (m_state == 0)
	{
		m_flReturnTime = gpGlobals->time;

		if (pActivator && pActivator->IsPlayer())
		{
			((CBasePlayer *)pActivator)->ResetMaxSpeed();
		}

		return;
	}

	if (!pActivator || !pActivator->IsPlayer())
	{
		pActivator = CBaseEntity::Instance(INDEXENT(1));
	}

	m_hPlayer = static_cast<CBasePlayer *>(pActivator);
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
	if (!m_hTarget)
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
		m_pentPath = Instance(FIND_ENTITY_BY_TARGETNAME(nullptr, STRING(m_sPath)));
	}
	else
	{
		m_pentPath = nullptr;
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

void CTriggerCamera::FollowTarget()
{
	if (!m_hPlayer)
		return;

	if (!m_hTarget || m_flReturnTime < gpGlobals->time)
	{
		if (m_hPlayer->IsAlive())
		{
			SET_VIEW(m_hPlayer->edict(), m_hPlayer->edict());

			m_hPlayer->EnableControl(TRUE);
			m_hPlayer->ResetMaxSpeed();
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

	real_t dx = vecGoal.x - pev->angles.x;
	real_t dy = vecGoal.y - pev->angles.y;

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
		pev->velocity = pev->velocity * 0.8f;

		if (pev->velocity.Length() < 10.0)
		{
			pev->velocity = g_vecZero;
		}
	}

	pev->nextthink = gpGlobals->time;
	Move();
}

void CTriggerCamera::Move()
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

	real_t fraction = 2 * gpGlobals->frametime;
	pev->velocity = ((pev->movedir * pev->speed) * fraction) + (pev->velocity * (1 - fraction));
}

LINK_ENTITY_TO_CLASS(env_snow, CWeather, CCSWeather)
LINK_ENTITY_TO_CLASS(func_snow, CWeather, CCSWeather)
LINK_ENTITY_TO_CLASS(env_rain, CWeather, CCSWeather)
LINK_ENTITY_TO_CLASS(func_rain, CWeather, CCSWeather)

void CWeather::Spawn()
{
	InitTrigger();
}

void CClientFog::KeyValue(KeyValueData *pkvd)
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
	{
		CBaseEntity::KeyValue(pkvd);
	}
}

void CClientFog::Spawn()
{
	pev->movetype = MOVETYPE_NOCLIP;
	pev->solid = SOLID_NOT;				// Remove model & collisions
	pev->renderamt = 0;				// The engine won't draw this model if this is set to 0 and blending is on
	pev->rendermode = kRenderTransTexture;
}

LINK_ENTITY_TO_CLASS(env_fog, CClientFog, CCSClientFog)

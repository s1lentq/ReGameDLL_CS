#include "precompiled.h"

/*
* Globals initialization
*/
#ifndef HOOK_GAMEDLL

TYPEDESCRIPTION CRuleEntity::m_SaveData[] =
{
	DEFINE_FIELD(CRuleEntity, m_iszMaster, FIELD_STRING),
};

// Save parms as a block.  Will break save/restore if the structure changes, but this entity didn't ship with Half-Life, so
// it can't impact saved Half-Life games.
TYPEDESCRIPTION CGameText::m_SaveData[] =
{
	DEFINE_ARRAY(CGameText, m_textParms, FIELD_CHARACTER, sizeof(hudtextparms_t)),
};

TYPEDESCRIPTION CGamePlayerZone::m_SaveData[] =
{
	DEFINE_FIELD(CGamePlayerZone, m_iszInTarget, FIELD_STRING),
	DEFINE_FIELD(CGamePlayerZone, m_iszOutTarget, FIELD_STRING),
	DEFINE_FIELD(CGamePlayerZone, m_iszInCount, FIELD_STRING),
	DEFINE_FIELD(CGamePlayerZone, m_iszOutCount, FIELD_STRING),
};

#else

TYPEDESCRIPTION IMPL_CLASS(CRuleEntity, m_SaveData)[1];
TYPEDESCRIPTION IMPL_CLASS(CGameText, m_SaveData)[1];
TYPEDESCRIPTION IMPL_CLASS(CGamePlayerZone, m_SaveData)[4];

#endif // HOOK_GAMEDLL

/* <eef33> ../cstrike/dlls/maprules.cpp:57 */
IMPLEMENT_SAVERESTORE(CRuleEntity, CBaseEntity);

/* <eed18> ../cstrike/dlls/maprules.cpp:60 */
void CRuleEntity::__MAKE_VHOOK(Spawn)(void)
{
	pev->solid = SOLID_NOT;
	pev->movetype = MOVETYPE_NONE;
	pev->effects = EF_NODRAW;
}

/* <eeff6> ../cstrike/dlls/maprules.cpp:68 */
void CRuleEntity::__MAKE_VHOOK(KeyValue)(KeyValueData *pkvd)
{
	if (FStrEq(pkvd->szKeyName, "master"))
	{
		SetMaster(ALLOC_STRING(pkvd->szValue));
		pkvd->fHandled = TRUE;
	}
	else
		CBaseEntity::KeyValue(pkvd);
}

/* <f0955> ../cstrike/dlls/maprules.cpp:79 */
BOOL CRuleEntity::CanFireForActivator(CBaseEntity *pActivator)
{
	if (!FStringNull(m_iszMaster))
	{
		if (UTIL_IsMasterTriggered(m_iszMaster, pActivator))
			return TRUE;
		else
			return FALSE;
	}

	return TRUE;
}

/* <eed39> ../cstrike/dlls/maprules.cpp:101 */
void CRulePointEntity::__MAKE_VHOOK(Spawn)(void)
{
	CRuleEntity::Spawn();
	pev->frame = 0;
	pev->model = 0;
}

/* <eed72> ../cstrike/dlls/maprules.cpp:120 */
void CRuleBrushEntity::__MAKE_VHOOK(Spawn)(void)
{
	SET_MODEL(edict(), STRING(pev->model));
	CRuleEntity::Spawn();
}

/* <f099d> ../cstrike/dlls/maprules.cpp:151 */
LINK_ENTITY_TO_CLASS(game_score, CGameScore);

/* <eedb1> ../cstrike/dlls/maprules.cpp:154 */
void CGameScore::__MAKE_VHOOK(Spawn)(void)
{
	CRulePointEntity::Spawn();
}

/* <efc68> ../cstrike/dlls/maprules.cpp:160 */
void CGameScore::__MAKE_VHOOK(KeyValue)(KeyValueData *pkvd)
{
	if (FStrEq(pkvd->szKeyName, "points"))
	{
		SetPoints(Q_atoi(pkvd->szValue));
		pkvd->fHandled = TRUE;
	}
	else
		CRulePointEntity::KeyValue(pkvd);
}

/* <ef54c> ../cstrike/dlls/maprules.cpp:173 */
void CGameScore::__MAKE_VHOOK(Use)(CBaseEntity *pActivator, CBaseEntity *pCaller, USE_TYPE useType, float value)
{
	if (!CanFireForActivator(pActivator))
		return;

	// Only players can use this
	if (pActivator->IsPlayer())
	{
		if (AwardToTeam())
		{
			pActivator->AddPointsToTeam(Points(), AllowNegativeScore());
		}
		else
		{
			pActivator->AddPoints(Points(), AllowNegativeScore());
		}
	}
}

/* <f0a68> ../cstrike/dlls/maprules.cpp:202 */
LINK_ENTITY_TO_CLASS(game_end, CGameEnd);

/* <ef497> ../cstrike/dlls/maprules.cpp:205 */
void CGameEnd::__MAKE_VHOOK(Use)(CBaseEntity *pActivator, CBaseEntity *pCaller, USE_TYPE useType, float value)
{
	if (!CanFireForActivator(pActivator))
		return;

	g_pGameRules->EndMultiplayerGame();
}

/* <f0b33> ../cstrike/dlls/maprules.cpp:242 */
LINK_ENTITY_TO_CLASS(game_text, CGameText);

/* <ef252> ../cstrike/dlls/maprules.cpp:251 */
IMPLEMENT_SAVERESTORE(CGameText, CRulePointEntity);

/* <f00dd> ../cstrike/dlls/maprules.cpp:254 */
void CGameText::__MAKE_VHOOK(KeyValue)(KeyValueData *pkvd)
{
	if (FStrEq(pkvd->szKeyName, "channel"))
	{
		m_textParms.channel = Q_atoi(pkvd->szValue);
		pkvd->fHandled = TRUE;
	}
	else if (FStrEq(pkvd->szKeyName, "x"))
	{
		m_textParms.x = Q_atof(pkvd->szValue);
		pkvd->fHandled = TRUE;
	}
	else if (FStrEq(pkvd->szKeyName, "y"))
	{
		m_textParms.y = Q_atof(pkvd->szValue);
		pkvd->fHandled = TRUE;
	}
	else if (FStrEq(pkvd->szKeyName, "effect"))
	{
		m_textParms.effect = Q_atoi(pkvd->szValue);
		pkvd->fHandled = TRUE;
	}
	else if (FStrEq(pkvd->szKeyName, "color"))
	{
		int color[4];
		UTIL_StringToIntArray(color, ARRAYSIZE(color), pkvd->szValue);

		m_textParms.r1 = color[0];
		m_textParms.g1 = color[1];
		m_textParms.b1 = color[2];
		m_textParms.a1 = color[3];

		pkvd->fHandled = TRUE;
	}
	else if (FStrEq(pkvd->szKeyName, "color2"))
	{
		int color[4];
		UTIL_StringToIntArray(color, ARRAYSIZE(color), pkvd->szValue);

		m_textParms.r2 = color[0];
		m_textParms.g2 = color[1];
		m_textParms.b2 = color[2];
		m_textParms.a2 = color[3];

		pkvd->fHandled = TRUE;
	}
	else if (FStrEq(pkvd->szKeyName, "fadein"))
	{
		m_textParms.fadeinTime = Q_atof(pkvd->szValue);
		pkvd->fHandled = TRUE;
	}
	else if (FStrEq(pkvd->szKeyName, "fadeout"))
	{
		m_textParms.fadeoutTime = Q_atof(pkvd->szValue);
		pkvd->fHandled = TRUE;
	}
	else if (FStrEq(pkvd->szKeyName, "holdtime"))
	{
		m_textParms.holdTime = Q_atof(pkvd->szValue);
		pkvd->fHandled = TRUE;
	}
	else if (FStrEq(pkvd->szKeyName, "fxtime"))
	{
		m_textParms.fxTime = Q_atof(pkvd->szValue);
		pkvd->fHandled = TRUE;
	}
	else
		CRulePointEntity::KeyValue(pkvd);
}

/* <ef655> ../cstrike/dlls/maprules.cpp:321 */
void CGameText::__MAKE_VHOOK(Use)(CBaseEntity *pActivator, CBaseEntity *pCaller, USE_TYPE useType, float value)
{
	if (!CanFireForActivator(pActivator))
		return;

	if (MessageToAll())
	{
		UTIL_HudMessageAll(m_textParms, MessageGet());
	}
	else
	{
		if (pActivator->IsNetClient())
		{
			UTIL_HudMessage(pActivator, m_textParms, MessageGet());
		}
	}
}

/* <f0bfe> ../cstrike/dlls/maprules.cpp:371 */
LINK_ENTITY_TO_CLASS(game_team_master, CGameTeamMaster);

/* <eff4f> ../cstrike/dlls/maprules.cpp:373 */
void CGameTeamMaster::__MAKE_VHOOK(KeyValue)(KeyValueData *pkvd)
{
	if (FStrEq(pkvd->szKeyName, "teamindex"))
	{
		m_teamIndex = Q_atoi(pkvd->szValue);
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
		CRulePointEntity::KeyValue(pkvd);
}

/* <f0474> ../cstrike/dlls/maprules.cpp:402 */
void CGameTeamMaster::__MAKE_VHOOK(Use)(CBaseEntity *pActivator, CBaseEntity *pCaller, USE_TYPE useType, float value)
{
	if (!CanFireForActivator(pActivator))
		return;

	if (useType == USE_SET)
	{
		if (value < 0)
		{
			m_teamIndex = -1;
		}
		else
		{
			m_teamIndex = g_pGameRules->GetTeamIndex(pActivator->TeamID());
		}

		return;
	}

	if (TeamMatch(pActivator))
	{
		SUB_UseTargets(pActivator, triggerType, value);

		if (RemoveOnFire())
		{
			UTIL_Remove(this);
		}
	}
}

/* <ef2e0> ../cstrike/dlls/maprules.cpp:429 */
BOOL CGameTeamMaster::__MAKE_VHOOK(IsTriggered)(CBaseEntity *pActivator)
{
	return TeamMatch(pActivator);
}

/* <eeeaf> ../cstrike/dlls/maprules.cpp:435 */
const char *CGameTeamMaster::__MAKE_VHOOK(TeamID)(void)
{
	// Currently set to "no team"
	if (m_teamIndex < 0)
	{
		return "";
	}

	// UNDONE: Fill this in with the team from the "teamlist"
	return g_pGameRules->GetIndexedTeamName(m_teamIndex);
}

/* <f0ccd> ../cstrike/dlls/maprules.cpp:444 */
BOOL CGameTeamMaster::TeamMatch(CBaseEntity *pActivator)
{
	if (m_teamIndex < 0 && AnyTeam())
		return TRUE;

	if (!pActivator)
		return FALSE;

	return UTIL_TeamsMatch(pActivator->TeamID(), TeamID());
}

/* <f0d2e> ../cstrike/dlls/maprules.cpp:474 */
LINK_ENTITY_TO_CLASS(game_team_set, CGameTeamSet);

/* <ef735> ../cstrike/dlls/maprules.cpp:477 */
void CGameTeamSet::__MAKE_VHOOK(Use)(CBaseEntity *pActivator, CBaseEntity *pCaller, USE_TYPE useType, float value)
{
	if (!CanFireForActivator(pActivator))
		return;

	if (ShouldClearTeam())
	{
		SUB_UseTargets(pActivator, USE_SET, -1);
	}
	else
	{
		SUB_UseTargets(pActivator, USE_SET, 0);
	}

	if (RemoveOnFire())
	{
		UTIL_Remove(this);
	}
}

/* <f0dfd> ../cstrike/dlls/maprules.cpp:519 */
LINK_ENTITY_TO_CLASS(game_zone_player, CGamePlayerZone);

/* <ef0a2> ../cstrike/dlls/maprules.cpp:528 */
IMPLEMENT_SAVERESTORE(CGamePlayerZone, CRuleBrushEntity);

/* <efdbc> ../cstrike/dlls/maprules.cpp:530 */
void CGamePlayerZone::__MAKE_VHOOK(KeyValue)(KeyValueData *pkvd)
{
	if (FStrEq(pkvd->szKeyName, "intarget"))
	{
		m_iszInTarget = ALLOC_STRING(pkvd->szValue);
		pkvd->fHandled = TRUE;
	}
	else if (FStrEq(pkvd->szKeyName, "outtarget"))
	{
		m_iszOutTarget = ALLOC_STRING(pkvd->szValue);
		pkvd->fHandled = TRUE;
	}
	else if (FStrEq(pkvd->szKeyName, "incount"))
	{
		m_iszInCount = ALLOC_STRING(pkvd->szValue);
		pkvd->fHandled = TRUE;
	}
	else if (FStrEq(pkvd->szKeyName, "outcount"))
	{
		m_iszOutCount = ALLOC_STRING(pkvd->szValue);
		pkvd->fHandled = TRUE;
	}
	else
		CRuleBrushEntity::KeyValue(pkvd);
}

/* <ef36e> ../cstrike/dlls/maprules.cpp:556 */
void CGamePlayerZone::__MAKE_VHOOK(Use)(CBaseEntity *pActivator, CBaseEntity *pCaller, USE_TYPE useType, float value)
{
	int playersInCount = 0;
	int playersOutCount = 0;

	if (!CanFireForActivator(pActivator))
		return;

	CBaseEntity *pPlayer = NULL;

	for (int i = 1; i <= gpGlobals->maxClients; ++i)
	{
		pPlayer = static_cast<CBasePlayer *>(UTIL_PlayerByIndex(i));

		if (pPlayer)
		{
			TraceResult trace;
			int hullNumber;

			hullNumber = human_hull;
			if (pPlayer->pev->flags & FL_DUCKING)
			{
				hullNumber = head_hull;
			}

			UTIL_TraceModel(pPlayer->pev->origin, pPlayer->pev->origin, hullNumber, edict(), &trace);

			if (trace.fStartSolid)
			{
				++playersInCount;
				if (!FStringNull(m_iszInTarget))
				{
					FireTargets(STRING(m_iszInTarget), pPlayer, pActivator, useType, value);
				}
			}
			else
			{
				++playersOutCount;
				if (!FStringNull(m_iszOutTarget))
				{
					FireTargets(STRING(m_iszOutTarget), pPlayer, pActivator, useType, value);
				}
			}
		}
	}

	if (!FStringNull(m_iszInCount))
	{
		FireTargets(STRING(m_iszInCount), pActivator, this, USE_SET, playersInCount);
	}

	if (!FStringNull(m_iszOutCount))
	{
		FireTargets(STRING(m_iszOutCount), pActivator, this, USE_SET, playersOutCount);
	}

}

/* <f0ecc> ../cstrike/dlls/maprules.cpp:628 */
LINK_ENTITY_TO_CLASS(game_player_hurt, CGamePlayerHurt);

/* <ef815> ../cstrike/dlls/maprules.cpp:631 */
void CGamePlayerHurt::__MAKE_VHOOK(Use)(CBaseEntity *pActivator, CBaseEntity *pCaller, USE_TYPE useType, float value)
{
	if (!CanFireForActivator(pActivator))
		return;

	if (pActivator->IsPlayer())
	{
		if (pev->dmg < 0)
			pActivator->TakeHealth(-pev->dmg, DMG_GENERIC);
		else
			pActivator->TakeDamage(pev, pev, pev->dmg, DMG_GENERIC);
	}

	SUB_UseTargets(pActivator, useType, value);

	if (RemoveOnFire())
	{
		UTIL_Remove(this);
	}
}

/* <f0f9b> ../cstrike/dlls/maprules.cpp:684 */
LINK_ENTITY_TO_CLASS(game_counter, CGameCounter);

/* <eee2d> ../cstrike/dlls/maprules.cpp:686 */
void CGameCounter::__MAKE_VHOOK(Spawn)(void)
{
	// Save off the initial count
	SetInitialValue(CountValue());
	CRulePointEntity::Spawn();
}

/* <ef8ef> ../cstrike/dlls/maprules.cpp:694 */
void CGameCounter::__MAKE_VHOOK(Use)(CBaseEntity *pActivator, CBaseEntity *pCaller, USE_TYPE useType, float value)
{
	if (!CanFireForActivator(pActivator))
		return;

	switch (useType)
	{
	case USE_ON:
	case USE_TOGGLE:
		CountUp();
		break;

	case USE_OFF:
		CountDown();
		break;

	case USE_SET:
		SetCountValue((int)value);
		break;
	}

	if (HitLimit())
	{
		SUB_UseTargets(pActivator, USE_TOGGLE, 0);

		if (RemoveOnFire())
		{
			UTIL_Remove(this);
		}

		if (ResetOnFire())
		{
			ResetCount();
		}
	}
}

/* <f106a> ../cstrike/dlls/maprules.cpp:747 */
LINK_ENTITY_TO_CLASS(game_counter_set, CGameCounterSet);

/* <efa65> ../cstrike/dlls/maprules.cpp:750 */
void CGameCounterSet::__MAKE_VHOOK(Use)(CBaseEntity *pActivator, CBaseEntity *pCaller, USE_TYPE useType, float value)
{
	if (!CanFireForActivator(pActivator))
		return;

	SUB_UseTargets(pActivator, USE_SET, pev->frags);

	if (RemoveOnFire())
	{
		UTIL_Remove(this);
	}
}

/* <f1139> ../cstrike/dlls/maprules.cpp:788 */
LINK_ENTITY_TO_CLASS(game_player_equip, CGamePlayerEquip);

/* <ed81f> ../cstrike/dlls/maprules.cpp:791 */
void CGamePlayerEquip::__MAKE_VHOOK(KeyValue)(KeyValueData *pkvd)
{
	CRulePointEntity::KeyValue(pkvd);

	if (!pkvd->fHandled)
	{
		for (int i = 0; i < MAX_EQUIP; ++i)
		{
			if (FStringNull(m_weaponNames[i]))
			{
				char tmp[128];
				UTIL_StripToken(pkvd->szKeyName, tmp);

				m_weaponNames[i] = ALLOC_STRING(tmp);
				m_weaponCount[i] = Q_atoi(pkvd->szValue);
				m_weaponCount[i] = Q_max(1, m_weaponCount[i]);

				pkvd->fHandled = TRUE;
				break;
			}
		}
	}
}

/* <f06ad> ../cstrike/dlls/maprules.cpp:816 */
void CGamePlayerEquip::__MAKE_VHOOK(Touch)(CBaseEntity *pOther)
{
	if (!CanFireForActivator(pOther))
		return;

	if (UseOnly())
		return;

	EquipPlayer(pOther);
}

/* <f1208> ../cstrike/dlls/maprules.cpp:827 */
void CGamePlayerEquip::EquipPlayer(CBaseEntity *pEntity)
{
	CBasePlayer *pPlayer = NULL;

	if (pEntity->IsPlayer())
	{
		pPlayer = reinterpret_cast<CBasePlayer *>(pEntity);
	}

	if (!pPlayer)
		return;

	for (int i = 0; i < MAX_EQUIP; ++i)
	{
		if (FStringNull(m_weaponNames[i]))
			break;

		for (int j = 0; j < m_weaponCount[i]; ++j)
		{
 			pPlayer->GiveNamedItem(STRING(m_weaponNames[i]));
		}
	}
}

/* <f05f3> ../cstrike/dlls/maprules.cpp:851 */
void CGamePlayerEquip::__MAKE_VHOOK(Use)(CBaseEntity *pActivator, CBaseEntity *pCaller, USE_TYPE useType, float value)
{
	EquipPlayer(pActivator);
}

/* <f1268> ../cstrike/dlls/maprules.cpp:881 */
LINK_ENTITY_TO_CLASS(game_player_team, CGamePlayerTeam);

/* <f1337> ../cstrike/dlls/maprules.cpp:884 */
const char *CGamePlayerTeam::TargetTeamName(const char *pszTargetName)
{
	CBaseEntity *pTeamEntity = NULL;

	while ((pTeamEntity = UTIL_FindEntityByTargetname(pTeamEntity, pszTargetName)) != NULL)
	{
		if (FClassnameIs(pTeamEntity->pev, "game_team_master"))
			return pTeamEntity->TeamID();
	}

	return NULL;
}

/* <f07df> ../cstrike/dlls/maprules.cpp:898 */
void CGamePlayerTeam::__MAKE_VHOOK(Use)(CBaseEntity *pActivator, CBaseEntity *pCaller, USE_TYPE useType, float value)
{
	if (!CanFireForActivator(pActivator))
		return;

	if (pActivator->IsPlayer())
	{
		const char *pszTargetTeam = TargetTeamName(STRING(pev->target));

		if (pszTargetTeam != NULL)
		{
			CBasePlayer *pPlayer = reinterpret_cast<CBasePlayer *>(pActivator);
			g_pGameRules->ChangePlayerTeam(pPlayer, pszTargetTeam, ShouldKillPlayer(), ShouldGibPlayer());
		}
	}

	if (RemoveOnFire())
	{
		UTIL_Remove(this);
	}
}

#ifdef HOOK_GAMEDLL

void CRuleEntity::Spawn(void)
{
	Spawn_();
}

void CRuleEntity::KeyValue(KeyValueData *pkvd)
{
	KeyValue_(pkvd);
}

int CRuleEntity::Save(CSave &save)
{
	return Save_(save);
}

int CRuleEntity::Restore(CRestore &restore)
{
	return Restore_(restore);
}

void CRulePointEntity::Spawn(void)
{
	Spawn_();
}

void CRuleBrushEntity::Spawn(void)
{
	Spawn_();
}

void CGameScore::Spawn(void)
{
	Spawn_();
}

void CGameScore::KeyValue(KeyValueData *pkvd)
{
	KeyValue_(pkvd);
}

void CGameScore::Use(CBaseEntity *pActivator, CBaseEntity *pCaller, USE_TYPE useType, float value)
{
	Use_(pActivator, pCaller, useType, value);
}

void CGameEnd::Use(CBaseEntity *pActivator, CBaseEntity *pCaller, USE_TYPE useType, float value)
{
	Use_(pActivator, pCaller, useType, value);
}

void CGameText::KeyValue(KeyValueData *pkvd)
{
	KeyValue_(pkvd);
}

int CGameText::Save(CSave &save)
{
	return Save_(save);
}

int CGameText::Restore(CRestore &restore)
{
	return Restore_(restore);
}

void CGameText::Use(CBaseEntity *pActivator, CBaseEntity *pCaller, USE_TYPE useType, float value)
{
	Use_(pActivator, pCaller, useType, value);
}

void CGameTeamMaster::KeyValue(KeyValueData *pkvd)
{
	KeyValue_(pkvd);
}

BOOL CGameTeamMaster::IsTriggered(CBaseEntity *pActivator)
{
	return IsTriggered_(pActivator);
}

const char *CGameTeamMaster::TeamID(void)
{
	return TeamID_();
}

void CGameTeamMaster::Use(CBaseEntity *pActivator, CBaseEntity *pCaller, USE_TYPE useType, float value)
{
	Use_(pActivator, pCaller, useType, value);
}

void CGameTeamSet::Use(CBaseEntity *pActivator, CBaseEntity *pCaller, USE_TYPE useType, float value)
{
	Use_(pActivator, pCaller, useType, value);
}

void CGamePlayerZone::KeyValue(KeyValueData *pkvd)
{
	KeyValue_(pkvd);
}

int CGamePlayerZone::Save(CSave &save)
{
	return Save_(save);
}

int CGamePlayerZone::Restore(CRestore &restore)
{
	return Restore_(restore);
}

void CGamePlayerZone::Use(CBaseEntity *pActivator, CBaseEntity *pCaller, USE_TYPE useType, float value)
{
	Use_(pActivator, pCaller, useType, value);
}

void CGamePlayerHurt::Use(CBaseEntity *pActivator, CBaseEntity *pCaller, USE_TYPE useType, float value)
{
	Use_(pActivator, pCaller, useType, value);
}

void CGameCounter::Spawn(void)
{
	Spawn_();
}

void CGameCounter::Use(CBaseEntity *pActivator, CBaseEntity *pCaller, USE_TYPE useType, float value)
{
	Use_(pActivator, pCaller, useType, value);
}

void CGameCounterSet::Use(CBaseEntity *pActivator, CBaseEntity *pCaller, USE_TYPE useType, float value)
{
	Use_(pActivator, pCaller, useType, value);
}

void CGamePlayerEquip::KeyValue(KeyValueData *pkvd)
{
	KeyValue_(pkvd);
}

void CGamePlayerEquip::Touch(CBaseEntity *pOther)
{
	Touch_(pOther);
}

void CGamePlayerEquip::Use(CBaseEntity *pActivator, CBaseEntity *pCaller, USE_TYPE useType, float value)
{
	Use_(pActivator, pCaller, useType, value);
}

void CGamePlayerTeam::Use(CBaseEntity *pActivator, CBaseEntity *pCaller, USE_TYPE useType, float value)
{
	Use_(pActivator, pCaller, useType, value);
}

#endif // HOOK_GAMEDLL

#include "precompiled.h"

CHalfLifeTraining::CHalfLifeTraining()
{
	PRECACHE_MODEL("models/w_weaponbox.mdl");
}

BOOL CHalfLifeTraining::IsDeathmatch()
{
	return FALSE;
}

void CHalfLifeTraining::InitHUD(CBasePlayer *pl)
{
	;
}

void CHalfLifeTraining::HostageDied()
{
	CBasePlayer *pPlayer = UTIL_PlayerByIndex(1);

	if (pPlayer)
	{
		pPlayer->pev->radsuit_finished = gpGlobals->time + 3.0f;
	}
}

edict_t *CHalfLifeTraining::GetPlayerSpawnSpot(CBasePlayer *pPlayer)
{
	CBaseEntity *pSpot = UTIL_FindEntityByClassname(nullptr, "info_player_start");

	if (FNullEnt(pSpot))
	{
		ALERT(at_error, "PutClientInServer: no info_player_start on level");
		return INDEXENT(0);
	}

	pPlayer->pev->origin = pSpot->pev->origin + Vector(0, 0, 1);
	pPlayer->pev->v_angle = g_vecZero;
	pPlayer->pev->velocity = g_vecZero;
	pPlayer->pev->angles = pSpot->pev->angles;
	pPlayer->pev->punchangle = g_vecZero;
	pPlayer->pev->fixangle = 1;

	return pSpot->edict();
}

void CHalfLifeTraining::PlayerThink(CBasePlayer *pPlayer)
{
	if (pPlayer->pev->radsuit_finished && gpGlobals->time > pPlayer->pev->radsuit_finished)
	{
		SERVER_COMMAND("reload\n");
	}

	if (!pPlayer->m_iAccount)
	{
		if (pPlayer->pev->scale)
		{
			pPlayer->m_iAccount = int(pPlayer->pev->scale);
		}
	}

	if (pPlayer->m_iTeam == UNASSIGNED)
	{
		pPlayer->SetProgressBarTime(0);
		pPlayer->m_bHasDefuser = pPlayer->pev->ideal_yaw != 0;
	}

	m_iHostagesRescued = 0;
	m_iRoundTimeSecs = int(gpGlobals->time + 1.0f);
	m_bFreezePeriod = FALSE;
	m_bGameOver = false;

	pPlayer->m_iTeam = CT;
	pPlayer->m_bCanShoot = true;
	pPlayer->m_fLastMovement = gpGlobals->time;

	if (pPlayer->m_pActiveItem)
		pPlayer->m_iHideHUD &= ~HIDEHUD_WEAPONS;
	else
		pPlayer->m_iHideHUD |= HIDEHUD_WEAPONS;

	if (pPlayer->HasNamedPlayerItem("weapon_c4"))
	{
		if (pPlayer->m_rgAmmo[pPlayer->GetAmmoIndex("C4")] <= 0)
		{
			pPlayer->m_bHasC4 = false;

			CBasePlayerWeapon *pWeapon = (CBasePlayerWeapon *)pPlayer->m_pActiveItem;

			if (FClassnameIs(pWeapon->pev, "weapon_c4"))
			{
				pPlayer->pev->weapons &= ~(1 << pWeapon->m_iId);
				pPlayer->RemovePlayerItem(pWeapon);
				pWeapon->Drop();
			}
		}
		else
			pPlayer->m_bHasC4 = true;
	}

	if (!pPlayer->m_bVGUIMenus)
	{
		if (fVGUIMenus)
		{
			pPlayer->m_bVGUIMenus = fVGUIMenus;
		}
	}

	CGrenade *pBomb = nullptr;
	while ((pBomb = UTIL_FindEntityByClassname(pBomb, "grenade")))
	{
		if (pBomb->m_pentCurBombTarget)
			pBomb->m_bStartDefuse = true;
	}

	if (pPlayer->m_signals.GetState() & SIGNAL_BUY)
	{
		if (!fInBuyArea)
		{
			FillAccountTime = 1;

			if (!fVisitedBuyArea)
			{
				MESSAGE_BEGIN(MSG_ONE, gmsgStatusIcon, nullptr, pPlayer->pev);
					WRITE_BYTE(STATUSICON_FLASH);
					WRITE_STRING("buyzone");
					WRITE_BYTE(0);
					WRITE_BYTE(160);
					WRITE_BYTE(0);
				MESSAGE_END();
			}
		}

		fInBuyArea = TRUE;

		if (pPlayer->m_iAccount < 16000 && FillAccountTime == 0.0f)
			FillAccountTime = gpGlobals->time + 5.0f;

		if (FillAccountTime != 0.0f && gpGlobals->time > FillAccountTime)
		{
			if (!fVisitedBuyArea)
			{
				MESSAGE_BEGIN(MSG_ONE, gmsgBlinkAcct, nullptr, pPlayer->pev);
					WRITE_BYTE(3);
				MESSAGE_END();

				MESSAGE_BEGIN(MSG_ONE, gmsgStatusIcon, nullptr, pPlayer->pev);
					WRITE_BYTE(STATUSICON_SHOW);
					WRITE_STRING("buyzone");
					WRITE_BYTE(0);
					WRITE_BYTE(160);
					WRITE_BYTE(0);
				MESSAGE_END();

				fVisitedBuyArea = TRUE;
			}

			pPlayer->AddAccount(16000 - pPlayer->m_iAccount);
			FillAccountTime = 0;
		}
	}
	else if (fInBuyArea && fVisitedBuyArea)
	{
		fInBuyArea = FALSE;
	}

	pPlayer->pev->scale = pPlayer->m_iAccount;
	pPlayer->pev->ideal_yaw = pPlayer->m_bHasDefuser;

	if (TheBots)
	{
		TheBots->OnEvent(EVENT_PLAYER_CHANGED_TEAM, pPlayer);
	}
}

void CHalfLifeTraining::PlayerSpawn(CBasePlayer *pPlayer)
{
	if (pPlayer->m_bNotKilled)
		return;

	fInBuyArea = TRUE;
	fVisitedBuyArea = FALSE;
	FillAccountTime = 0;

	pPlayer->m_iJoiningState = JOINED;
	pPlayer->m_iTeam = CT;
	pPlayer->m_bNotKilled = true;
	pPlayer->pev->body = 0;
	pPlayer->m_iModelName = MODEL_URBAN;

	fVGUIMenus = pPlayer->m_bVGUIMenus;
	SET_MODEL(ENT(pPlayer->pev), "models/player.mdl");

	CBaseEntity *pWeaponEntity = nullptr;

	while ((pWeaponEntity = UTIL_FindEntityByClassname(pWeaponEntity, "game_player_equip")))
	{
		pWeaponEntity->Touch(pPlayer);
	}

	pPlayer->SetPlayerModel(false);
	pPlayer->Spawn();
	pPlayer->m_iHideHUD |= (HIDEHUD_WEAPONS | HIDEHUD_HEALTH | HIDEHUD_TIMER | HIDEHUD_MONEY);
}

int CHalfLifeTraining::ItemShouldRespawn(CItem *pItem)
{
	return GR_ITEM_RESPAWN_NO;
}

BOOL CHalfLifeTraining::FPlayerCanRespawn(CBasePlayer *pPlayer)
{
	return TRUE;
}

bool CHalfLifeTraining::PlayerCanBuy(CBasePlayer *pPlayer)
{
	return (pPlayer->m_signals.GetState() & SIGNAL_BUY) != 0;
}

void CHalfLifeTraining::PlayerKilled(CBasePlayer *pVictim, entvars_t *pKiller, entvars_t *pInflictor)
{
	SET_VIEW(pVictim->edict(), pVictim->edict());
	FireTargets("game_playerdie", pVictim, pVictim, USE_TOGGLE, 0);
}

void CHalfLifeTraining::CheckWinConditions()
{
	if (m_bBombDefused)
	{
		CGrenade *pBomb = nullptr;

		while ((pBomb = UTIL_FindEntityByClassname(pBomb, "grenade")))
		{
			if (!pBomb->m_bIsC4 || !pBomb->m_bJustBlew)
				continue;

			pBomb->m_bJustBlew = false;
			m_bBombDefused = false;
			FireTargets(STRING(pBomb->pev->target), CBaseEntity::Instance(pBomb->pev->owner), CBaseEntity::Instance(pBomb->pev->owner), USE_TOGGLE, 0);
			break;
		}
	}
	else if (m_bTargetBombed)
	{
		CGrenade *pBomb = nullptr;

		while ((pBomb = UTIL_FindEntityByClassname(pBomb, "grenade")))
		{
			if (!pBomb->m_bIsC4 || !pBomb->m_bJustBlew)
				continue;

			if (FStringNull(pBomb->pev->noise1))
				continue;

			pBomb->m_bJustBlew = false;
			m_bTargetBombed = false;
			FireTargets(STRING(pBomb->pev->noise1), CBaseEntity::Instance(pBomb->pev->owner), CBaseEntity::Instance(pBomb->pev->owner), USE_TOGGLE, 0);
			break;
		}
	}

	CBaseEntity *pHostage = nullptr;
	while ((pHostage = UTIL_FindEntityByClassname(pHostage, "hostage_entity")))
	{
		if (pHostage->pev->deadflag != DEAD_RESPAWNABLE || !FStringNull(pHostage->pev->noise1))
			continue;

		UTIL_SetSize(pHostage->pev, Vector(-16, -16, 0), Vector(16, 16, 72));

		CBaseEntity *pRescueArea = nullptr;
		while ((pRescueArea = UTIL_FindEntityByClassname(pRescueArea, "func_hostage_rescue")))
		{
			if (!pRescueArea->Intersects(pHostage))
				break;
		}

		if (pRescueArea)
		{
			pHostage->pev->noise1 = 1;
			FireTargets(STRING(pRescueArea->pev->target), nullptr, nullptr, USE_TOGGLE, 0);
		}
	}
}

TYPEDESCRIPTION CBaseGrenCatch::m_SaveData[] =
{
	DEFINE_FIELD(CBaseGrenCatch, m_NeedGrenadeType, FIELD_INTEGER),
	DEFINE_FIELD(CBaseGrenCatch, m_fSmokeTouching, FIELD_BOOLEAN),
	DEFINE_FIELD(CBaseGrenCatch, m_fFlashTouched, FIELD_BOOLEAN),
	DEFINE_FIELD(CBaseGrenCatch, sTriggerOnGrenade, FIELD_STRING),
	DEFINE_FIELD(CBaseGrenCatch, sDisableOnGrenade, FIELD_STRING),
};

IMPLEMENT_SAVERESTORE(CBaseGrenCatch, CBaseEntity)
LINK_ENTITY_TO_CLASS(func_grencatch, CBaseGrenCatch, CCSGrenCatch)

void CBaseGrenCatch::Spawn()
{
	pev->solid = SOLID_TRIGGER;
	pev->flags |= FL_WORLDBRUSH;
	pev->effects |= EF_NODRAW;

	SET_MODEL(ENT(pev), STRING(pev->model));
	pev->nextthink = gpGlobals->time + 0.1f;
}

void CBaseGrenCatch::Touch(CBaseEntity *pOther)
{
	if (!pOther)
	{
		return;
	}

	if (Q_strstr(STRING(pev->model), "flash"))
	{
		m_fFlashTouched = true;
	}
}

void CBaseGrenCatch::Think()
{
	bool m_fSmokeTouchingLastFrame;
	Vector vMax, vMin;

	m_fSmokeTouchingLastFrame = m_fSmokeTouching;
	m_fSmokeTouching = false;

	CGrenade *pGrenade = nullptr;
	while ((pGrenade = UTIL_FindEntityByClassname(pGrenade, "grenade")))
	{
		vMin = pGrenade->pev->mins;
		vMax = pGrenade->pev->maxs;

		UTIL_SetSize(pGrenade->pev, Vector(-8, -8, 0), Vector(8, 8, 0));

		if (pGrenade->Intersects(this) && Q_strstr(STRING(pGrenade->pev->model), "smoke"))
		{
			if (pGrenade->pev->velocity.Length() == 0)
				m_fSmokeTouching = true;
		}

		pGrenade->pev->mins = vMin;
		pGrenade->pev->maxs = vMax;
	}

	if ((m_NeedGrenadeType == GRENADETYPE_SMOKE && m_fSmokeTouching && !m_fSmokeTouchingLastFrame)
		|| (m_NeedGrenadeType == GRENADETYPE_FLASH && m_fFlashTouched))
	{
		FireTargets(STRING(sTriggerOnGrenade), this, this, USE_TOGGLE, 0);

		if (m_NeedGrenadeType == GRENADETYPE_SMOKE)
		{
			CBaseEntity *pTrigger = nullptr;
			while ((pTrigger = UTIL_FindEntityByTargetname(pTrigger, STRING(sDisableOnGrenade))))
			{
				// save solid
				pTrigger->pev->team = pTrigger->pev->solid;
				pTrigger->pev->solid = SOLID_NOT;
			}
		}
		else if (m_NeedGrenadeType == GRENADETYPE_FLASH)
		{
			pev->flags |= FL_KILLME;
		}
	}

	if (m_fSmokeTouchingLastFrame && !m_fSmokeTouching)
	{
		CBaseEntity *pTrigger = nullptr;
		while ((pTrigger = UTIL_FindEntityByTargetname(pTrigger, STRING(sDisableOnGrenade))))
		{
			// restore solid
			pTrigger->pev->solid = pTrigger->pev->team;
			pTrigger->pev->team = 0;
			UTIL_SetOrigin(pTrigger->pev, pTrigger->pev->origin);
		}
	}

	pev->nextthink = gpGlobals->time + 0.1f;
}

void CBaseGrenCatch::KeyValue(KeyValueData *pkvd)
{
	if (FStrEq(pkvd->szKeyName, "triggerongrenade"))
	{
		sTriggerOnGrenade = ALLOC_STRING(pkvd->szValue);
		pkvd->fHandled = TRUE;
	}
	else if (FStrEq(pkvd->szKeyName, "disableongrenade"))
	{
		sDisableOnGrenade = ALLOC_STRING(pkvd->szValue);
		pkvd->fHandled = TRUE;
	}
	else if (FStrEq(pkvd->szKeyName, "grenadetype"))
	{
		if (FStrEq(pkvd->szValue, "smoke"))
		{
			m_NeedGrenadeType = GRENADETYPE_SMOKE;
			pkvd->fHandled = TRUE;
		}
		else if (FStrEq(pkvd->szValue, "flash"))
		{
			m_NeedGrenadeType = GRENADETYPE_FLASH;
			pkvd->fHandled = TRUE;
		}
	}
	else
	{
		CBaseEntity::KeyValue(pkvd);
	}
}

TYPEDESCRIPTION CFuncWeaponCheck::m_SaveData[] =
{
	DEFINE_FIELD(CFuncWeaponCheck, sTriggerWithItems, FIELD_STRING),
	DEFINE_FIELD(CFuncWeaponCheck, sTriggerNoItems, FIELD_STRING),
	DEFINE_FIELD(CFuncWeaponCheck, iItemCount, FIELD_INTEGER),
	DEFINE_FIELD(CFuncWeaponCheck, sMaster, FIELD_STRING),
	DEFINE_ARRAY(CFuncWeaponCheck, sItemName, FIELD_STRING, MAX_ITEM_COUNTS),
	DEFINE_FIELD(CFuncWeaponCheck, iAnyWeapon, FIELD_INTEGER),
};

IMPLEMENT_SAVERESTORE(CFuncWeaponCheck, CBaseEntity)
LINK_ENTITY_TO_CLASS(func_weaponcheck, CFuncWeaponCheck, CCSFuncWeaponCheck)

void CFuncWeaponCheck::Spawn()
{
	pev->dmgtime = 0;
	pev->solid = SOLID_TRIGGER;
	pev->flags |= FL_WORLDBRUSH;
	pev->solid |= EF_NODRAW;

	SET_MODEL(ENT(pev), STRING(pev->model));
}

void CFuncWeaponCheck::KeyValue(KeyValueData *pkvd)
{
	if (FStrEq(pkvd->szKeyName, "trigger_items"))
	{
		sTriggerWithItems = ALLOC_STRING(pkvd->szValue);
		pkvd->fHandled = TRUE;
	}
	else if (FStrEq(pkvd->szKeyName, "trigger_noitems"))
	{
		sTriggerNoItems = ALLOC_STRING(pkvd->szValue);
		pkvd->fHandled = TRUE;
	}
	else if (FStrEq(pkvd->szKeyName, "trigger_noitems_delay"))
	{
		pev->speed = Q_atof(pkvd->szValue);
		pkvd->fHandled = TRUE;
	}
	else if (Q_strstr(pkvd->szKeyName, "item"))
	{
		if (iItemCount < MAX_ITEM_COUNTS)
		{
			sItemName[iItemCount++] = ALLOC_STRING(pkvd->szValue);
		}

		pkvd->fHandled = TRUE;
	}
	else if (FStrEq(pkvd->szKeyName, "master"))
	{
		sMaster = ALLOC_STRING(pkvd->szValue);
		pkvd->fHandled = TRUE;
	}
	else if (FStrEq(pkvd->szKeyName, "any_weapon"))
	{
		iAnyWeapon = Q_atoi(pkvd->szValue);
		pkvd->fHandled = TRUE;
	}
	else
	{
		CBaseEntity::KeyValue(pkvd);
	}
}

void CFuncWeaponCheck::Touch(CBaseEntity *pOther)
{
	if (!UTIL_IsMasterTriggered(sMaster, pOther))
		return;

	if (!pOther)
		return;

	if (!pOther->IsPlayer())
		return;

	CBasePlayer *pPlayer = static_cast<CBasePlayer *>(pOther);
	for (int i = 1; i <= iItemCount; i++)
	{
		if (iAnyWeapon)
		{
			if (pPlayer->HasNamedPlayerItem(STRING(sItemName[i])))
			{
				break;
			}
		}
		else
		{
			if (!pPlayer->HasNamedPlayerItem(STRING(sItemName[i])))
			{
				if (pev->dmgtime < gpGlobals->time)
				{
					if (pev->speed > -1.0f)
					{
						FireTargets(STRING(sTriggerNoItems), pOther, pOther, USE_TOGGLE, 0);
						pev->dmgtime = pev->speed + gpGlobals->time;

						if (!pev->speed)
							pev->speed = -1;
					}
				}

				return;
			}
		}
	}

	FireTargets(STRING(sTriggerWithItems), pOther, pOther, USE_TOGGLE, 0);
	SUB_Remove();
}

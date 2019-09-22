#include "precompiled.h"

LINK_ENTITY_TO_CLASS(item_healthkit, CHealthKit, CCSHealthKit)

void CHealthKit::Spawn()
{
	Precache();
	SET_MODEL(ENT(pev), "models/w_medkit.mdl");

	CItem::Spawn();
}

void CHealthKit::Precache()
{
	PRECACHE_MODEL("models/w_medkit.mdl");
	PRECACHE_SOUND("items/smallmedkit1.wav");
}

BOOL CHealthKit::MyTouch(CBasePlayer *pPlayer)
{
#ifdef REGAMEDLL_ADD
	if (pPlayer->HasRestrictItem(ITEM_HEALTHKIT, ITEM_TYPE_TOUCHED))
		return FALSE;
#endif

	auto healthValue = gSkillData.healthkitCapacity;

#ifdef REGAMEDLL_FIXES
	if (pev->health != 0.0f) {
		healthValue = pev->health;
	}
#endif

	if (pPlayer->TakeHealth(healthValue, DMG_GENERIC))
	{
		MESSAGE_BEGIN(MSG_ONE, gmsgItemPickup, nullptr, pPlayer->pev);
			WRITE_STRING(pev->classname);
		MESSAGE_END();

		EMIT_SOUND(ENT(pPlayer->pev), CHAN_ITEM, "items/smallmedkit1.wav", VOL_NORM, ATTN_NORM);

		if (g_pGameRules->ItemShouldRespawn(this))
			Respawn();
		else
			UTIL_Remove(this);

		return TRUE;
	}

	return FALSE;
}

TYPEDESCRIPTION CWallHealth::m_SaveData[] =
{
	DEFINE_FIELD(CWallHealth, m_flNextCharge, FIELD_TIME),
	DEFINE_FIELD(CWallHealth, m_iReactivate, FIELD_INTEGER),
	DEFINE_FIELD(CWallHealth, m_iJuice, FIELD_INTEGER),
	DEFINE_FIELD(CWallHealth, m_iOn, FIELD_INTEGER),
	DEFINE_FIELD(CWallHealth, m_flSoundTime, FIELD_TIME),
};

IMPLEMENT_SAVERESTORE(CWallHealth, CBaseEntity)
LINK_ENTITY_TO_CLASS(func_healthcharger, CWallHealth, CCSWallHealth)

void CWallHealth::KeyValue(KeyValueData *pkvd)
{
	if (FStrEq(pkvd->szKeyName, "style") || FStrEq(pkvd->szKeyName, "height") || FStrEq(pkvd->szKeyName, "value1") || FStrEq(pkvd->szKeyName, "value2") || FStrEq(pkvd->szKeyName, "value3"))
	{
		pkvd->fHandled = TRUE;
	}
	else if (FStrEq(pkvd->szKeyName, "dmdelay"))
	{
		m_iReactivate = Q_atoi(pkvd->szValue);
		pkvd->fHandled = TRUE;
	}
	else
	{
		CBaseToggle::KeyValue(pkvd);
	}
}

void CWallHealth::Spawn()
{
	Precache();

	pev->solid = SOLID_BSP;
	pev->movetype = MOVETYPE_PUSH;

	// set size and link into world
	UTIL_SetOrigin(pev, pev->origin);
	UTIL_SetSize(pev, pev->mins, pev->maxs);

	SET_MODEL(ENT(pev), pev->model);

	int healthValue = (int)gSkillData.healthchargerCapacity;
#ifdef REGAMEDLL_FIXES
	if (pev->health != 0.0f) {
		healthValue = (int)pev->health;
	}
#endif

	m_iJuice = healthValue;
	pev->frame = 0.0f;
}

#ifdef REGAMEDLL_FIXES
void CWallHealth::Restart()
{
	pev->solid = SOLID_BSP;
	pev->movetype = MOVETYPE_PUSH;

	// set size and link into world
	UTIL_SetOrigin(pev, pev->origin);
	UTIL_SetSize(pev, pev->mins, pev->maxs);

	SET_MODEL(ENT(pev), pev->model);

	pev->nextthink = pev->ltime + 0.1f;
	SetThink(&CWallHealth::Recharge);
}
#endif // #ifdef REGAMEDLL_FIXES

void CWallHealth::Precache()
{
	PRECACHE_SOUND("items/medshot4.wav");
	PRECACHE_SOUND("items/medshotno1.wav");
	PRECACHE_SOUND("items/medcharge4.wav");
}

void CWallHealth::Use(CBaseEntity *pActivator, CBaseEntity *pCaller, USE_TYPE useType, float value)
{
	// Make sure that we have a caller
	if (!pActivator)
		return;

	// if it's not a player, ignore
	if (!pActivator->IsPlayer())
		return;

	// if there is no juice left, turn it off
	if (m_iJuice <= 0
#ifdef REGAMEDLL_FIXES
		&& pev->frame != 1.0f // recharging... don't reset think
#endif
		)
	{
		pev->frame = 1.0f;
		Off();
	}

	// if the player doesn't have the suit, or there is no juice left, make the deny noise
	if (m_iJuice <= 0 || !(pActivator->pev->weapons & (1 << WEAPON_SUIT))
#ifdef REGAMEDLL_FIXES
		|| !pActivator->CanTakeHealth(AMOUNT_CHARGE_HEALTH) // don't charge health if we can't more, prevent thinking entity
#endif // REGAMEDLL_FIXES
		)
	{
		if (gpGlobals->time >= m_flSoundTime)
		{
			m_flSoundTime = gpGlobals->time + 0.62f;
			EMIT_SOUND(ENT(pev), CHAN_ITEM, "items/medshotno1.wav", VOL_NORM, ATTN_NORM);
		}

		return;
	}

	pev->nextthink = pev->ltime + 0.25f;
	SetThink(&CWallHealth::Off);

	// Time to recharge yet?

	if (m_flNextCharge >= gpGlobals->time)
		return;

	// Play the on sound or the looping charging sound
	if (!m_iOn)
	{
		m_iOn++;
		EMIT_SOUND(ENT(pev), CHAN_ITEM, "items/medshot4.wav", VOL_NORM, ATTN_NORM);
		m_flSoundTime = gpGlobals->time + 0.56f;
	}

	if (m_iOn == 1 && gpGlobals->time >= m_flSoundTime)
	{
		m_iOn++;
		EMIT_SOUND(ENT(pev), CHAN_STATIC, "items/medcharge4.wav", VOL_NORM, ATTN_NORM);
	}

	// charge the player
	if (pActivator->TakeHealth(AMOUNT_CHARGE_HEALTH, DMG_GENERIC))
		m_iJuice--;

	// govern the rate of charge
	m_flNextCharge = gpGlobals->time + 0.1f;
}

void CWallHealth::Recharge()
{
	EMIT_SOUND(ENT(pev), CHAN_ITEM, "items/medshot4.wav", VOL_NORM, ATTN_NORM);

	int healthValue = (int)gSkillData.healthchargerCapacity;
#ifdef REGAMEDLL_FIXES
	if (pev->health != 0.0f) {
		healthValue = (int)pev->health;
	}
#endif

	m_iJuice = healthValue;

	pev->frame = 0.0f;
	SetThink(&CWallHealth::SUB_DoNothing);
}

void CWallHealth::Off()
{
	// Stop looping sound.
	if (m_iOn > 1)
		STOP_SOUND(ENT(pev), CHAN_STATIC, "items/medcharge4.wav");

	m_iOn = 0;

	if (!m_iJuice)
	{
		int iReactivate = m_iReactivate;

#ifdef REGAMEDLL_FIXES
		if (iReactivate <= 0)
#endif // #ifdef REGAMEDLL_FIXES
		{
			if ((iReactivate = g_pGameRules->FlHealthChargerRechargeTime()) <= 0)
				return;
		}

		if (m_iReactivate <= 0)
			m_iReactivate = iReactivate;

		pev->nextthink = pev->ltime + m_iReactivate;
		SetThink(&CWallHealth::Recharge);
	}
	else
	{
		SetThink(&CWallHealth::SUB_DoNothing);
	}
}

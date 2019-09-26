#include "precompiled.h"

TYPEDESCRIPTION CRecharge::m_SaveData[] =
{
	DEFINE_FIELD(CRecharge, m_flNextCharge, FIELD_TIME),
	DEFINE_FIELD(CRecharge, m_iReactivate, FIELD_INTEGER),
	DEFINE_FIELD(CRecharge, m_iJuice, FIELD_INTEGER),
	DEFINE_FIELD(CRecharge, m_iOn, FIELD_INTEGER),
	DEFINE_FIELD(CRecharge, m_flSoundTime, FIELD_TIME),
};

IMPLEMENT_SAVERESTORE(CRecharge, CBaseEntity)
LINK_ENTITY_TO_CLASS(func_recharge, CRecharge, CCSRecharge)

void CRecharge::KeyValue(KeyValueData *pkvd)
{
	if (FStrEq(pkvd->szKeyName, "style")
		|| FStrEq(pkvd->szKeyName, "height")
		|| FStrEq(pkvd->szKeyName, "value1")
		|| FStrEq(pkvd->szKeyName, "value2")
		|| FStrEq(pkvd->szKeyName, "value3"))
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

void CRecharge::Spawn()
{
	Precache();

	pev->solid = SOLID_BSP;
	pev->movetype = MOVETYPE_PUSH;

	// set size and link into world
	UTIL_SetOrigin(pev, pev->origin);
	UTIL_SetSize(pev, pev->mins, pev->maxs);
	SET_MODEL(ENT(pev), STRING(pev->model));

	int armorValue = (int)gSkillData.suitchargerCapacity;
#ifdef REGAMEDLL_FIXES
	if (pev->armorvalue != 0.0f) {
		armorValue = (int)pev->armorvalue;
	}
#endif

	m_iJuice = armorValue;
	pev->frame = 0;
}

#ifdef REGAMEDLL_FIXES
void CRecharge::Restart()
{
	pev->solid = SOLID_BSP;
	pev->movetype = MOVETYPE_PUSH;

	// set size and link into world
	UTIL_SetOrigin(pev, pev->origin);
	UTIL_SetSize(pev, pev->mins, pev->maxs);
	SET_MODEL(ENT(pev), STRING(pev->model));

	pev->nextthink = pev->ltime + 0.1f;
	SetThink(&CRecharge::Recharge);
}

#endif
void CRecharge::Precache()
{
	PRECACHE_SOUND("items/suitcharge1.wav");
	PRECACHE_SOUND("items/suitchargeno1.wav");
	PRECACHE_SOUND("items/suitchargeok1.wav");
}

void CRecharge::Use(CBaseEntity *pActivator, CBaseEntity *pCaller, USE_TYPE useType, float value)
{
#ifdef REGAMEDLL_FIXES
	// Make sure that we have a caller
	if (!pActivator)
		return;
	
	// if it's not a player, ignore
	if (!pActivator->IsPlayer())
		return;
#else
	if (!FClassnameIs(pActivator->pev, "player"))
		return;	
#endif // #ifdef REGAMEDLL_FIXES
	
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
		|| pActivator->pev->armorvalue >= MAX_CHARGE_ARMOR // don't charge health if we can't more, prevent thinking entity
#endif
		)
	{
		if (m_flSoundTime <= gpGlobals->time)
		{
			m_flSoundTime = gpGlobals->time + 0.62f;
			EMIT_SOUND(ENT(pev), CHAN_ITEM, "items/suitchargeno1.wav", 0.85, ATTN_NORM);
		}

		return;
	}

	pev->nextthink = pev->ltime + 0.25f;
	SetThink(&CRecharge::Off);

	// Time to recharge yet?
	if (m_flNextCharge >= gpGlobals->time)
		return;

	// Make sure that we have a caller
	if (!pActivator)
		return;

	m_hActivator = pActivator;//EHANDLE::CBaseEntity *operator=

	// only recharge the player
	if (!m_hActivator->IsPlayer())
		return;

	// Play the on sound or the looping charging sound
	if (!m_iOn)
	{
		m_iOn++;
		EMIT_SOUND(ENT(pev), CHAN_ITEM, "items/suitchargeok1.wav", 0.85, ATTN_NORM);
		m_flSoundTime = gpGlobals->time + 0.56f;
	}

	if (m_iOn == 1 && m_flSoundTime <= gpGlobals->time)
	{
		m_iOn++;
		EMIT_SOUND(ENT(pev), CHAN_STATIC, "items/suitcharge1.wav", 0.85, ATTN_NORM);
	}

	// charge the player
	if (m_hActivator->pev->armorvalue < MAX_CHARGE_ARMOR)
	{
#ifdef REGAMEDLL_FIXES
		CBasePlayer *pPlayer = m_hActivator.Get<CBasePlayer>();
		if (pPlayer->m_iKevlar == ARMOR_NONE)
			pPlayer->m_iKevlar = ARMOR_KEVLAR;
#endif

		m_iJuice--;
		m_hActivator->pev->armorvalue += AMOUNT_CHARGE_ARMOR;

		if (m_hActivator->pev->armorvalue > MAX_CHARGE_ARMOR)
			m_hActivator->pev->armorvalue = MAX_CHARGE_ARMOR;
	}

	// govern the rate of charge
	m_flNextCharge = gpGlobals->time + 0.1f;
}

void CRecharge::Recharge()
{
	int armorValue = (int)gSkillData.suitchargerCapacity;
#ifdef REGAMEDLL_FIXES
	if (pev->armorvalue != 0.0f) {
		armorValue = (int)pev->armorvalue;
	}
#endif

	m_iJuice = armorValue;

	pev->frame = 0;
	SetThink(&CRecharge::SUB_DoNothing);
}

void CRecharge::Off()
{
	// Stop looping sound.
	if (m_iOn > 1)
		STOP_SOUND(ENT(pev), CHAN_STATIC, "items/suitcharge1.wav");

	m_iOn = 0;

	if (!m_iJuice)
	{
		int iReactivate = m_iReactivate;

#ifdef REGAMEDLL_FIXES
		if (iReactivate <= 0)
#endif // #ifdef REGAMEDLL_FIXES
		{
			if ((iReactivate = g_pGameRules->FlHEVChargerRechargeTime()) <= 0)
				return;
		}

		if (m_iReactivate <= 0)
			m_iReactivate = iReactivate;

		pev->nextthink = pev->ltime + m_iReactivate;
		SetThink(&CRecharge::Recharge);
	}
	else
	{
		SetThink(&CRecharge::SUB_DoNothing);
	}
}

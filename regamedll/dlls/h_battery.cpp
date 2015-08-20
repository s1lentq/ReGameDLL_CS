#include "precompiled.h"

/*
* Globals initialization
*/
#ifndef HOOK_GAMEDLL

TYPEDESCRIPTION CRecharge::m_SaveData[] =
{
	DEFINE_FIELD(CRecharge, m_flNextCharge, FIELD_TIME),
	DEFINE_FIELD(CRecharge, m_iReactivate, FIELD_INTEGER),
	DEFINE_FIELD(CRecharge, m_iJuice, FIELD_INTEGER),
	DEFINE_FIELD(CRecharge, m_iOn, FIELD_INTEGER),
	DEFINE_FIELD(CRecharge, m_flSoundTime, FIELD_TIME),
};

#else

TYPEDESCRIPTION (*CRecharge::pm_SaveData)[5];

#endif // HOOK_GAMEDLL

/* <c61e2> ../cstrike/dlls/h_battery.cpp:61 */
IMPLEMENT_SAVERESTORE(CRecharge, CBaseEntity);

/* <c65cc> ../cstrike/dlls/h_battery.cpp:63 */
LINK_ENTITY_TO_CLASS(func_recharge, CRecharge);

/* <c648b> ../cstrike/dlls/h_battery.cpp:66 */
void CRecharge::__MAKE_VHOOK(KeyValue)(KeyValueData *pkvd)
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
		CBaseToggle::KeyValue(pkvd);
}

/* <c616f> ../cstrike/dlls/h_battery.cpp:85 */
void CRecharge::__MAKE_VHOOK(Spawn)(void)
{
	Precache();

	pev->solid = SOLID_BSP;
	pev->movetype = MOVETYPE_PUSH;

	UTIL_SetOrigin(pev, pev->origin);	// set size and link into world
	UTIL_SetSize(pev, pev->mins, pev->maxs);
	SET_MODEL(ENT(pev), STRING(pev->model));

	m_iJuice = (int)gSkillData.suitchargerCapacity;
	pev->frame = 0;
}

/* <c6122> ../cstrike/dlls/h_battery.cpp:99 */
void CRecharge::__MAKE_VHOOK(Precache)(void)
{
	PRECACHE_SOUND("items/suitcharge1.wav");
	PRECACHE_SOUND("items/suitchargeno1.wav");
	PRECACHE_SOUND("items/suitchargeok1.wav");
}

/* <c630e> ../cstrike/dlls/h_battery.cpp:107 */
void CRecharge::__MAKE_VHOOK(Use)(CBaseEntity *pActivator, CBaseEntity *pCaller, USE_TYPE useType, float value)
{
	// if it's not a player, ignore
	if (!FClassnameIs(pActivator->pev, "player"))
		return;

	// if there is no juice left, turn it off
	if (m_iJuice <= 0)
	{
		pev->frame = 1;
		Off();
	}

	// if the player doesn't have the suit, or there is no juice left, make the deny noise
	if (m_iJuice <= 0 || !(pActivator->pev->weapons & (1 << WEAPON_SUIT)))
	{
		if (m_flSoundTime <= gpGlobals->time)
		{
			m_flSoundTime = gpGlobals->time + 0.62;
			EMIT_SOUND(ENT(pev), CHAN_ITEM, "items/suitchargeno1.wav", 0.85, ATTN_NORM);
		}

		return;
	}

	pev->nextthink = pev->ltime + 0.25;
	SetThink(&CRecharge::Off);

	// Time to recharge yet?
	if (m_flNextCharge >= gpGlobals->time)
		return;

	// Make sure that we have a caller
	if (!pActivator)
		return;

	m_hActivator = pActivator;//EHANDLE::CBaseEntity *operator=

	//only recharge the player
	if (!m_hActivator->IsPlayer())
		return;

	// Play the on sound or the looping charging sound
	if (!m_iOn)
	{
		m_iOn++;
		EMIT_SOUND(ENT(pev), CHAN_ITEM, "items/suitchargeok1.wav", 0.85, ATTN_NORM);
		m_flSoundTime = gpGlobals->time + 0.56;
	}

	if (m_iOn == 1 && m_flSoundTime <= gpGlobals->time)
	{
		m_iOn++;
		EMIT_SOUND(ENT(pev), CHAN_STATIC, "items/suitcharge1.wav", 0.85, ATTN_NORM);
	}

	// charge the player
	if (m_hActivator->pev->armorvalue < 100)
	{
		m_iJuice--;
		m_hActivator->pev->armorvalue += 1;

		if (m_hActivator->pev->armorvalue > 100)
			m_hActivator->pev->armorvalue = 100;
	}

	// govern the rate of charge
	m_flNextCharge = gpGlobals->time + 0.1;
}

/* <c6149> ../cstrike/dlls/h_battery.cpp:178 */
void CRecharge::Recharge(void)
{
	m_iJuice = gSkillData.suitchargerCapacity;
	pev->frame = 0;			
	SetThink(&CRecharge::SUB_DoNothing);
}

/* <c622e> ../cstrike/dlls/h_battery.cpp:185 */
void CRecharge::Off(void)
{
	// Stop looping sound.
	if (m_iOn > 1)
		STOP_SOUND(ENT(pev), CHAN_STATIC, "items/suitcharge1.wav");

	m_iOn = 0;

	if (!m_iJuice &&  (m_iReactivate = g_pGameRules->FlHEVChargerRechargeTime()) > 0)
	{
		pev->nextthink = pev->ltime + m_iReactivate;
		SetThink(&CRecharge::Recharge);
	}
	else
		SetThink(&CRecharge::SUB_DoNothing);
}

#ifdef HOOK_GAMEDLL

void CRecharge::Spawn(void)
{
	Spawn_();
}

void CRecharge::Precache(void)
{
	Precache_();
}

void CRecharge::KeyValue(KeyValueData *pkvd)
{
	KeyValue_(pkvd);
}

int CRecharge::Save(CSave &save)
{
	return Save_(save);
}

int CRecharge::Restore(CRestore &restore)
{
	return Restore_(restore);
}

void CRecharge::Use(CBaseEntity *pActivator, CBaseEntity *pCaller, USE_TYPE useType, float value)
{
	Use_(pActivator, pCaller, useType, value);
}

#endif // HOOK_GAMEDLL

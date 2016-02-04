#include "precompiled.h"

/*
* Globals initialization
*/
#ifndef HOOK_GAMEDLL

TYPEDESCRIPTION CWallHealth::m_SaveData[] =
{
	DEFINE_FIELD(CWallHealth, m_flNextCharge, FIELD_TIME),
	DEFINE_FIELD(CWallHealth, m_iReactivate, FIELD_INTEGER),
	DEFINE_FIELD(CWallHealth, m_iJuice, FIELD_INTEGER),
	DEFINE_FIELD(CWallHealth, m_iOn, FIELD_INTEGER),
	DEFINE_FIELD(CWallHealth, m_flSoundTime, FIELD_TIME),
};

#endif // HOOK_GAMEDLL

/* <d637a> ../cstrike/dlls/healthkit.cpp:43 */
LINK_ENTITY_TO_CLASS(item_healthkit, CHealthKit);

/* <d5e25> ../cstrike/dlls/healthkit.cpp:55 */
void CHealthKit::__MAKE_VHOOK(Spawn)()
{
	Precache();
	SET_MODEL(ENT(pev), "models/w_medkit.mdl");

	CItem::Spawn();
}

/* <d5d8a> ../cstrike/dlls/healthkit.cpp:63 */
void CHealthKit::__MAKE_VHOOK(Precache)()
{
	PRECACHE_MODEL("models/w_medkit.mdl");
	PRECACHE_SOUND("items/smallmedkit1.wav");
}

/* <d5fb9> ../cstrike/dlls/healthkit.cpp:69 */
BOOL CHealthKit::__MAKE_VHOOK(MyTouch)(CBasePlayer *pPlayer)
{
	if (pPlayer->TakeHealth(gSkillData.healthkitCapacity, DMG_GENERIC))
	{
		MESSAGE_BEGIN(MSG_ONE, gmsgItemPickup, NULL, pPlayer->pev);
			WRITE_STRING(STRING(pev->classname));
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

/* <d5e98> ../cstrike/dlls/healthkit.cpp:130 */
IMPLEMENT_SAVERESTORE(CWallHealth, CBaseEntity);

/* <d6444> ../cstrike/dlls/healthkit.cpp:132 */
LINK_ENTITY_TO_CLASS(func_healthcharger, CWallHealth);

/* <d60ed> ../cstrike/dlls/healthkit.cpp:135 */
void CWallHealth::__MAKE_VHOOK(KeyValue)(KeyValueData *pkvd)
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
		CBaseToggle::KeyValue(pkvd);
}

/* <d5dfe> ../cstrike/dlls/healthkit.cpp:154 */
void CWallHealth::__MAKE_VHOOK(Spawn)()
{
	Precache();

	pev->solid = SOLID_BSP;
	pev->movetype = MOVETYPE_PUSH;

	// set size and link into world
	UTIL_SetOrigin(pev, pev->origin);
	UTIL_SetSize(pev, pev->mins, pev->maxs);

	SET_MODEL(ENT(pev), STRING(pev->model));

	m_iJuice = (int)gSkillData.healthchargerCapacity;
	pev->frame = 0.0f;
}

/* <d5dd7> ../cstrike/dlls/healthkit.cpp:169 */
void CWallHealth::__MAKE_VHOOK(Precache)()
{
	PRECACHE_SOUND("items/medshot4.wav");
	PRECACHE_SOUND("items/medshotno1.wav");
	PRECACHE_SOUND("items/medcharge4.wav");
}

/* <d622e> ../cstrike/dlls/healthkit.cpp:177 */
void CWallHealth::__MAKE_VHOOK(Use)(CBaseEntity *pActivator, CBaseEntity *pCaller, USE_TYPE useType, float value)
{
	// Make sure that we have a caller
	if (!pActivator)
		return;

	// if it's not a player, ignore
	if (!pActivator->IsPlayer())
		return;

	// if there is no juice left, turn it off
	if (m_iJuice <= 0)
	{
		pev->frame = 1.0f;
		Off();
	}

	// if the player doesn't have the suit, or there is no juice left, make the deny noise
	if (m_iJuice <= 0 || !(pActivator->pev->weapons & (1 << WEAPON_SUIT)))
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
	if (pActivator->TakeHealth(1, DMG_GENERIC))
		m_iJuice--;

	// govern the rate of charge
	m_flNextCharge = gpGlobals->time + 0.1f;
}

/* <d5f4d> ../cstrike/dlls/healthkit.cpp:236 */
void CWallHealth::Recharge()
{
	EMIT_SOUND(ENT(pev), CHAN_ITEM, "items/medshot4.wav", VOL_NORM, ATTN_NORM);
	m_iJuice = gSkillData.healthchargerCapacity;
	pev->frame = 0.0f;
	SetThink(&CWallHealth::SUB_DoNothing);
}

/* <d5ee4> ../cstrike/dlls/healthkit.cpp:244 */
void CWallHealth::Off()
{
	// Stop looping sound.
	if (m_iOn > 1)
		STOP_SOUND(ENT(pev), CHAN_STATIC, "items/medcharge4.wav");

	m_iOn = 0;

	if (!m_iJuice &&  ((m_iReactivate = g_pGameRules->FlHealthChargerRechargeTime()) > 0))
	{
		pev->nextthink = pev->ltime + m_iReactivate;
		SetThink(&CWallHealth::Recharge);
	}
	else
		SetThink(&CWallHealth::SUB_DoNothing);
}

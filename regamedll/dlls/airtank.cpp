#include "precompiled.h"

TYPEDESCRIPTION CAirtank::m_SaveData[] =
{
	DEFINE_FIELD(CAirtank, m_state, FIELD_INTEGER)
};

LINK_ENTITY_TO_CLASS(item_airtank, CAirtank, CCSAirtank)
IMPLEMENT_SAVERESTORE(CAirtank, CGrenade)

void CAirtank::Spawn()
{
	Precache();

	// motor
	pev->movetype = MOVETYPE_FLY;
	pev->solid = SOLID_BBOX;

	SET_MODEL(ENT(pev), "models/w_oxygen.mdl");
	UTIL_SetSize(pev, Vector(-16, -16, 0), Vector(16, 16, 36));
	UTIL_SetOrigin(pev, pev->origin);

	SetTouch(&CAirtank::TankTouch);
	SetThink(&CAirtank::TankThink);

	pev->flags |= FL_MONSTER;
	pev->takedamage = DAMAGE_YES;
	pev->health = 20;
	pev->dmg = 50;
	m_state = 1;
}

void CAirtank::Precache()
{
	PRECACHE_MODEL("models/w_oxygen.mdl");
	PRECACHE_SOUND("doors/aliendoor3.wav");
}

void CAirtank::Killed(entvars_t *pevAttacker, int iGib)
{
	pev->owner = ENT(pevAttacker);

	// UNDONE: this should make a big bubble cloud, not an explosion
	Explode(pev->origin, Vector(0, 0, -1));
}

void CAirtank::TankThink()
{
	// Fire trigger
	m_state = 1;
	SUB_UseTargets(this, USE_TOGGLE, 0);
}

void CAirtank::TankTouch(CBaseEntity *pOther)
{
	if (!pOther->IsPlayer())
	{
		return;
	}

	if (!m_state)
	{
		// "no oxygen" sound
		EMIT_SOUND(ENT(pev), CHAN_BODY, "player/pl_swim2.wav", VOL_NORM, ATTN_NORM);
		return;
	}

	// give player 12 more seconds of air
	pOther->pev->air_finished = gpGlobals->time + 12.0f;

	// suit recharge sound
	EMIT_SOUND(ENT(pev), CHAN_VOICE, "doors/aliendoor3.wav", VOL_NORM, ATTN_NORM);

	// recharge airtank in 30 seconds
	pev->nextthink = gpGlobals->time + 30.0f;
	m_state = 0;
	SUB_UseTargets(this, USE_TOGGLE, 1);
}

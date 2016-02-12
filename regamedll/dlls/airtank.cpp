#include "precompiled.h"

/*
* Globals initialization
*/
#ifndef HOOK_GAMEDLL

TYPEDESCRIPTION CAirtank::m_SaveData[] =
{
	DEFINE_FIELD(CAirtank, m_state, FIELD_INTEGER)
};

#endif // HOOK_GAMEDLL

/* <5329> ../cstrike/dlls/airtank.cpp:41 */
LINK_ENTITY_TO_CLASS(item_airtank, CAirtank);

/* <5211> ../cstrike/dlls/airtank.cpp:47 */
IMPLEMENT_SAVERESTORE(CAirtank, CGrenade);

/* <50dd> ../cstrike/dlls/airtank.cpp:50 */
void CAirtank::__MAKE_VHOOK(Spawn)()
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

/* <4fef> ../cstrike/dlls/airtank.cpp:71 */
void CAirtank::__MAKE_VHOOK(Precache)()
{
	PRECACHE_MODEL("models/w_oxygen.mdl");
	PRECACHE_SOUND("doors/aliendoor3.wav");
}

/* <503d> ../cstrike/dlls/airtank.cpp:78 */
void CAirtank::__MAKE_VHOOK(Killed)(entvars_t *pevAttacker, int iGib)
{
	pev->owner = ENT(pevAttacker);

	// UNDONE: this should make a big bubble cloud, not an explosion
	Explode(pev->origin, Vector(0, 0, -1));
}

/* <5016> ../cstrike/dlls/airtank.cpp:88 */
void CAirtank::TankThink()
{
	// Fire trigger
	m_state = 1;
	SUB_UseTargets(this, USE_TOGGLE, 0);
}

/* <525d> ../cstrike/dlls/airtank.cpp:96 */
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

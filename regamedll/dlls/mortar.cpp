#include "precompiled.h"

/*
* Globals initialization
*/
#ifndef HOOK_GAMEDLL

TYPEDESCRIPTION CFuncMortarField::m_SaveData[] =
{
	DEFINE_FIELD(CFuncMortarField, m_iszXController, FIELD_STRING),
	DEFINE_FIELD(CFuncMortarField, m_iszYController, FIELD_STRING),
	DEFINE_FIELD(CFuncMortarField, m_flSpread, FIELD_FLOAT),
	DEFINE_FIELD(CFuncMortarField, m_flDelay, FIELD_FLOAT),
	DEFINE_FIELD(CFuncMortarField, m_iCount, FIELD_INTEGER),
	DEFINE_FIELD(CFuncMortarField, m_fControl, FIELD_INTEGER),
};

#else

TYPEDESCRIPTION IMPL_CLASS(CFuncMortarField, m_SaveData)[6];

#endif // HOOK_GAMEDLL

/* <f6ee7> ../cstrike/dlls/mortar.cpp:56 */
LINK_ENTITY_TO_CLASS(func_mortar_field, CFuncMortarField);

/* <f6d3b> ../cstrike/dlls/mortar.cpp:68 */
IMPLEMENT_SAVERESTORE(CFuncMortarField, CBaseToggle);

/* <f6d87> ../cstrike/dlls/mortar.cpp:71 */
void CFuncMortarField::__MAKE_VHOOK(KeyValue)(KeyValueData *pkvd)
{
	if (FStrEq(pkvd->szKeyName, "m_iszXController"))
	{
		m_iszXController = ALLOC_STRING(pkvd->szValue);
		pkvd->fHandled = TRUE;
	}
	else if (FStrEq(pkvd->szKeyName, "m_iszYController"))
	{
		m_iszYController = ALLOC_STRING(pkvd->szValue);
		pkvd->fHandled = TRUE;
	}
	else if (FStrEq(pkvd->szKeyName, "m_flSpread"))
	{
		m_flSpread = Q_atof(pkvd->szValue);
		pkvd->fHandled = TRUE;
	}
	else if (FStrEq(pkvd->szKeyName, "m_fControl"))
	{
		m_fControl = Q_atoi(pkvd->szValue);
		pkvd->fHandled = TRUE;
	}
	else if (FStrEq(pkvd->szKeyName, "m_iCount"))
	{
		m_iCount = Q_atoi(pkvd->szValue);
		pkvd->fHandled = TRUE;
	}
}

// Drop bombs from above

/* <f694a> ../cstrike/dlls/mortar.cpp:102 */
void CFuncMortarField::__MAKE_VHOOK(Spawn)(void)
{
	pev->solid = SOLID_NOT;

	// set size and link into world
	SET_MODEL(ENT(pev), STRING(pev->model));
	pev->movetype = MOVETYPE_NONE;
	pev->effects |= EF_NODRAW;

	SetUse(&CFuncMortarField::FieldUse);
	Precache();
}

/* <f6971> ../cstrike/dlls/mortar.cpp:113 */
void CFuncMortarField::__MAKE_VHOOK(Precache)(void)
{
	PRECACHE_SOUND("weapons/mortar.wav");
	PRECACHE_SOUND("weapons/mortarhit.wav");
	PRECACHE_MODEL("sprites/lgtning.spr");
}

// If connected to a table, then use the table controllers, else hit where the trigger is.

/* <f6ae4> ../cstrike/dlls/mortar.cpp:122 */
void CFuncMortarField::FieldUse(CBaseEntity *pActivator, CBaseEntity *pCaller, USE_TYPE useType, float value)
{
	Vector vecStart;

	vecStart.x = RANDOM_FLOAT(pev->mins.x, pev->maxs.x);
	vecStart.y = RANDOM_FLOAT(pev->mins.y, pev->maxs.y);
	vecStart.z = pev->maxs.z;

	switch (m_fControl)
	{
	// random
	case 0:
		break;
	// Trigger Activator
	case 1:
	{
		if (pActivator != NULL)
		{
			vecStart.x = pActivator->pev->origin.x;
			vecStart.y = pActivator->pev->origin.y;
		}
		break;
	}
	// table
	case 2:
	{
		CBaseEntity *pController;

		if (!FStringNull(m_iszXController))
		{
			pController = UTIL_FindEntityByTargetname(NULL, STRING(m_iszXController));

			if (pController != NULL)
			{
				vecStart.x = pev->mins.x + pController->pev->ideal_yaw * pev->size.x;
			}
		}
		if (!FStringNull(m_iszYController))
		{
			pController = UTIL_FindEntityByTargetname(NULL, STRING(m_iszYController));

			if (pController != NULL)
			{
				vecStart.y = pev->mins.y + pController->pev->ideal_yaw * pev->size.y;
			}
		}
		break;
	}
	}

	int pitch = RANDOM_LONG(95, 124);

	EMIT_SOUND_DYN(ENT(pev), CHAN_VOICE, "weapons/mortar.wav", VOL_NORM, ATTN_NONE, 0, pitch);

	float t = 2.5;
	for (int i = 0; i < m_iCount; ++i)
	{
		Vector vecSpot = vecStart;
		vecSpot.x += RANDOM_FLOAT(-m_flSpread, m_flSpread);
		vecSpot.y += RANDOM_FLOAT(-m_flSpread, m_flSpread);

		TraceResult tr;
		UTIL_TraceLine(vecSpot, vecSpot + Vector(0, 0, -1) * 4096, ignore_monsters, ENT(pev), &tr);

		edict_t *pentOwner = NULL;
		if (pActivator)
		{
			pentOwner = pActivator->edict();
		}

		CBaseEntity *pMortar = Create("monster_mortar", tr.vecEndPos, Vector(0, 0, 0), pentOwner);
		pMortar->pev->nextthink = gpGlobals->time + t;
		t += RANDOM_FLOAT(0.2, 0.5);

		if (i == 0)
		{
			CSoundEnt::InsertSound(bits_SOUND_DANGER, tr.vecEndPos, 400, 0.3);
		}
	}
}

/* <f6fb1> ../cstrike/dlls/mortar.cpp:203 */
LINK_ENTITY_TO_CLASS(monster_mortar, CMortar);

/* <f6998> ../cstrike/dlls/mortar.cpp:205 */
void CMortar::__MAKE_VHOOK(Spawn)(void)
{
	pev->movetype = MOVETYPE_NONE;
	pev->solid = SOLID_NOT;
	pev->dmg = 200;

	SetThink(&CMortar::MortarExplode);
	pev->nextthink = 0;
	Precache();
}

/* <f69be> ../cstrike/dlls/mortar.cpp:221 */
void CMortar::__MAKE_VHOOK(Precache)(void)
{
	m_spriteTexture = PRECACHE_MODEL("sprites/lgtning.spr");
}

/* <f69e5> ../cstrike/dlls/mortar.cpp:226 */
void CMortar::MortarExplode(void)
{
	// mortar beam
	MESSAGE_BEGIN(MSG_BROADCAST, SVC_TEMPENTITY);
		WRITE_BYTE(TE_BEAMPOINTS);
		WRITE_COORD(pev->origin.x);
		WRITE_COORD(pev->origin.y);
		WRITE_COORD(pev->origin.z);
		WRITE_COORD(pev->origin.x);
		WRITE_COORD(pev->origin.y);
		WRITE_COORD(pev->origin.z + 1024);
		WRITE_SHORT(m_spriteTexture);
		WRITE_BYTE(0); // framerate
		WRITE_BYTE(0); // framerate
		WRITE_BYTE(1); // life
		WRITE_BYTE(40); // width
		WRITE_BYTE(0); // noise
		WRITE_BYTE(255); // r, g, b
		WRITE_BYTE(160); // r, g, b
		WRITE_BYTE(100); // r, g, b
		WRITE_BYTE(128); // brightness
		WRITE_BYTE(0); // speed
	MESSAGE_END();

	TraceResult tr;
	UTIL_TraceLine(pev->origin + Vector(0, 0, 1024), pev->origin - Vector(0, 0, 1024), dont_ignore_monsters, ENT(pev), &tr);

	Explode(&tr, (DMG_BLAST | DMG_MORTAR));
	UTIL_ScreenShake(tr.vecEndPos, 25.0, 150.0, 1.0, 750);
}

#ifdef HOOK_GAMEDLL

void CFuncMortarField::Spawn(void)
{
	Spawn_();
}

void CFuncMortarField::Precache(void)
{
	Precache_();
}

void CFuncMortarField::KeyValue(KeyValueData *pkvd)
{
	KeyValue_(pkvd);
}

int CFuncMortarField::Save(CSave &save)
{
	return Save_(save);
}

int CFuncMortarField::Restore(CRestore &restore)
{
	return Restore_(restore);
}

void CMortar::Spawn(void)
{
	Spawn_();
}

void CMortar::Precache(void)
{
	Precache_();
}

#endif // HOOK_GAMEDLL

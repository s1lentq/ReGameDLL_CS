#include "precompiled.h"

/*
* Globals initialization
*/
#ifndef HOOK_GAMEDLL

TYPEDESCRIPTION CLight::m_SaveData[] =
{
	DEFINE_FIELD(CLight, m_iStyle, FIELD_INTEGER),
	DEFINE_FIELD(CLight, m_iszPattern, FIELD_STRING),
};

#endif

LINK_ENTITY_TO_CLASS(light, CLight, CCSLight);
IMPLEMENT_SAVERESTORE(CLight, CPointEntity);

// Cache user-entity-field values until spawn is called.
void CLight::__MAKE_VHOOK(KeyValue)(KeyValueData *pkvd)
{
	if (FStrEq(pkvd->szKeyName, "style"))
	{
		m_iStyle = Q_atoi(pkvd->szValue);
		pkvd->fHandled = TRUE;
	}
	else if (FStrEq(pkvd->szKeyName, "pitch"))
	{
		pev->angles.x = Q_atof(pkvd->szValue);
		pkvd->fHandled = TRUE;
	}
	else if (FStrEq(pkvd->szKeyName, "pattern"))
	{
		m_iszPattern = ALLOC_STRING(pkvd->szValue);
		pkvd->fHandled = TRUE;
	}
	else
		CPointEntity::KeyValue(pkvd);
}

void CLight::__MAKE_VHOOK(Spawn)()
{
	// inert light
	if (FStringNull(pev->targetname))
	{
		REMOVE_ENTITY(ENT(pev));
		return;
	}

	m_iStartedOff = (pev->spawnflags & SF_LIGHT_START_OFF) != 0;

	if (m_iStyle >= 32)
	{
		if (pev->spawnflags & SF_LIGHT_START_OFF)
			LIGHT_STYLE(m_iStyle, "a");

		else if (m_iszPattern)
			LIGHT_STYLE(m_iStyle, (char *)STRING(m_iszPattern));
		else
			LIGHT_STYLE(m_iStyle, "m");
	}
}

void CLight::__MAKE_VHOOK(Restart)()
{
	if (m_iStyle >= 32)
	{
		if (m_iStartedOff)
		{
			pev->spawnflags |= SF_LIGHT_START_OFF;
			LIGHT_STYLE(m_iStyle, "a");
		}
		else
		{
			pev->spawnflags &= ~SF_LIGHT_START_OFF;

			if (m_iszPattern)
				LIGHT_STYLE(m_iStyle, (char *)STRING(m_iszPattern));
			else
				LIGHT_STYLE(m_iStyle, "m");
		}
	}
}

void CLight::__MAKE_VHOOK(Use)(CBaseEntity *pActivator, CBaseEntity *pCaller, USE_TYPE useType, float value)
{
	if (m_iStyle >= 32)
	{
		if (!ShouldToggle(useType, !(pev->spawnflags & SF_LIGHT_START_OFF)))
			return;

		if (pev->spawnflags & SF_LIGHT_START_OFF)
		{
			if (m_iszPattern)
				LIGHT_STYLE(m_iStyle, (char *)STRING(m_iszPattern));
			else
				LIGHT_STYLE(m_iStyle, "m");

			pev->spawnflags &= ~SF_LIGHT_START_OFF;
		}
		else
		{
			LIGHT_STYLE(m_iStyle, "a");
			pev->spawnflags |= SF_LIGHT_START_OFF;
		}
	}
}

LINK_ENTITY_TO_CLASS(light_spot, CLight, CCSLight);
LINK_ENTITY_TO_CLASS(light_environment, CEnvLight, CCSEnvLight);

void CEnvLight::__MAKE_VHOOK(KeyValue)(KeyValueData *pkvd)
{
	if (FStrEq(pkvd->szKeyName, "_light"))
	{
		int r, g, b, v, j;
		j = Q_sscanf(pkvd->szValue, "%d %d %d %d\n", &r, &g, &b, &v);

		if (j == 1)
			g = b = r;

		else if (j == 4)
		{
			r = r * (v / 255.0);
			g = g * (v / 255.0);
			b = b * (v / 255.0);
		}

		// simulate qrad direct, ambient,and gamma adjustments, as well as engine scaling
		r = Q_pow(r / 114.0, 0.6) * 264;
		g = Q_pow(g / 114.0, 0.6) * 264;
		b = Q_pow(b / 114.0, 0.6) * 264;

		pkvd->fHandled = TRUE;

		char szColor[64];
		Q_sprintf(szColor, "%d", r);
		CVAR_SET_STRING("sv_skycolor_r", szColor);
		Q_sprintf(szColor, "%d", g);
		CVAR_SET_STRING("sv_skycolor_g", szColor);
		Q_sprintf(szColor, "%d", b);
		CVAR_SET_STRING("sv_skycolor_b", szColor);
	}
	else
		CLight::KeyValue(pkvd);
}

void CEnvLight::__MAKE_VHOOK(Spawn)()
{
#ifdef HOOK_GAMEDLL
// NOTE: fix negative the values for function sprintf from STD C++:
// expected - sv_skyvec_y "0.000000"
// with using sprintf from STD C++, got - sv_skyvec_y "-0.000000"
// If we not doing it then the test will be failed!
#define SPRINTF_OLD_STD_FIX + 0
#else
#define SPRINTF_OLD_STD_FIX
#endif

	char szVector[64];
	UTIL_MakeAimVectors(pev->angles);

	Q_sprintf(szVector, "%f", gpGlobals->v_forward.x SPRINTF_OLD_STD_FIX);
	CVAR_SET_STRING("sv_skyvec_x", szVector);

	Q_sprintf(szVector, "%f", gpGlobals->v_forward.y SPRINTF_OLD_STD_FIX);
	CVAR_SET_STRING("sv_skyvec_y", szVector);

	Q_sprintf(szVector, "%f", gpGlobals->v_forward.z SPRINTF_OLD_STD_FIX);
	CVAR_SET_STRING("sv_skyvec_z", szVector);

	CLight::Spawn();
}

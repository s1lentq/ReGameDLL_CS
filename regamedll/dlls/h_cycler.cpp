#include "precompiled.h"

TYPEDESCRIPTION CCycler::m_SaveData[] =
{
	DEFINE_FIELD(CCycler, m_animate, FIELD_INTEGER),
};

IMPLEMENT_SAVERESTORE(CCycler, CBaseToggle)

void CGenericCycler::Spawn()
{
	GenericCyclerSpawn(pev->model, Vector(-16, -16, 0), Vector(16, 16, 72));
}

LINK_ENTITY_TO_CLASS(cycler, CGenericCycler, CCSGenericCycler)
LINK_ENTITY_TO_CLASS(cycler_prdroid, CCyclerProbe, CCSCyclerProbe)

void CCyclerProbe::Spawn()
{
	pev->origin = pev->origin + Vector(0, 0, 16);
	GenericCyclerSpawn("models/prdroid.mdl", Vector(-16, -16, -16), Vector(16, 16, 16));
}

// Cycler member functions
void CCycler::GenericCyclerSpawn(const char *szModel, Vector vecMin, Vector vecMax)
{
	if (!szModel || !szModel[0])
	{
		ALERT(at_error, "cycler at %.0f %.0f %0.f missing modelname", pev->origin.x, pev->origin.y, pev->origin.z);
		REMOVE_ENTITY(ENT(pev));
		return;
	}

	MAKE_STRING_CLASS("cycler", pev);

	PRECACHE_MODEL(szModel);
	SET_MODEL(ENT(pev), szModel);

	CCycler::Spawn();

	UTIL_SetSize(pev, vecMin, vecMax);
}

void CCycler::Spawn()
{
	InitBoneControllers();

	pev->solid = SOLID_SLIDEBOX;
	pev->movetype = MOVETYPE_NONE;
	pev->takedamage = DAMAGE_YES;
	pev->effects = 0;

	// no cycler should die
	pev->health = 80000;

	pev->yaw_speed = 5;
	pev->ideal_yaw = pev->angles.y;
	ChangeYaw(360);

	m_flFrameRate = 75;
	m_flGroundSpeed = 0;

	pev->nextthink += 1.0f;

	ResetSequenceInfo();

	if (pev->sequence != 0 || pev->frame != 0.0f)
	{
		m_animate = 0;
		pev->framerate = 0;
	}
	else
	{
		m_animate = 1;
	}
}

// cycler think
void CCycler::Think()
{
	pev->nextthink = gpGlobals->time + 0.1f;

	if (m_animate)
	{
		StudioFrameAdvance();
	}

	if (m_fSequenceFinished && !m_fSequenceLoops)
	{
		// ResetSequenceInfo();
		// hack to avoid reloading model every frame
		pev->animtime = gpGlobals->time;
		pev->framerate = 1.0f;
		m_fSequenceFinished = FALSE;
		m_flLastEventCheck = gpGlobals->time;
		pev->frame = 0;

		if (!m_animate)
		{
			// FIX: don't reset framerate
			pev->framerate = 0.0f;
		}
	}
}

// CyclerUse - starts a rotation trend
void CCycler::Use(CBaseEntity *pActivator, CBaseEntity *pCaller, USE_TYPE useType, float value)
{
	m_animate = !m_animate;

	if (m_animate)
		pev->framerate = 1.0f;
	else
		pev->framerate = 0.0f;
}

// CyclerPain , changes sequences when shot
BOOL CCycler::TakeDamage(entvars_t *pevInflictor, entvars_t *pevAttacker, float flDamage, int bitsDamageType)
{
	if (m_animate)
	{
		pev->sequence++;
		ResetSequenceInfo();

		if (m_flFrameRate == 0.0)
		{
			pev->sequence = 0;
			ResetSequenceInfo();
		}

		pev->frame = 0;
	}
	else
	{
		pev->framerate = 1.0;
		StudioFrameAdvance(0.1);
		pev->framerate = 0;

		ALERT(at_console, "sequence: %d, frame %.0f\n", pev->sequence, pev->frame);
	}

	return FALSE;
}

TYPEDESCRIPTION CCyclerSprite::m_SaveData[] =
{
	DEFINE_FIELD(CCyclerSprite, m_animate, FIELD_INTEGER),
	DEFINE_FIELD(CCyclerSprite, m_lastTime, FIELD_TIME),
	DEFINE_FIELD(CCyclerSprite, m_maxFrame, FIELD_FLOAT),
};

LINK_ENTITY_TO_CLASS(cycler_sprite, CCyclerSprite, CCSCyclerSprite)
IMPLEMENT_SAVERESTORE(CCyclerSprite, CBaseEntity)

void CCyclerSprite::Spawn()
{
	pev->solid = SOLID_SLIDEBOX;
	pev->movetype = MOVETYPE_NONE;
	pev->takedamage = DAMAGE_YES;
	pev->effects = 0;

	pev->frame = 0;
	pev->nextthink = gpGlobals->time + 0.1f;
	m_animate = 1;
	m_lastTime = gpGlobals->time;

	PRECACHE_MODEL(pev->model);
	SET_MODEL(ENT(pev), pev->model);

	m_maxFrame = float(MODEL_FRAMES(pev->modelindex) - 1);

	m_renderfx = pev->renderfx;
	m_rendermode = pev->rendermode;
	m_renderamt = pev->renderamt;
	m_rendercolor = pev->rendercolor;
}

void CCyclerSprite::Restart()
{
	pev->solid = SOLID_SLIDEBOX;
	pev->movetype = MOVETYPE_NONE;
	pev->takedamage = DAMAGE_YES;
	pev->effects = 0;

	pev->frame = 0;
	pev->nextthink = gpGlobals->time + 0.1f;
	m_animate = 1;
	m_lastTime = gpGlobals->time;

	pev->renderfx = m_renderfx;
	pev->rendermode = m_rendermode;
	pev->renderamt = m_renderamt;
	pev->rendercolor = m_rendercolor;
}

void CCyclerSprite::Think()
{
	if (ShouldAnimate())
	{
		Animate(pev->framerate * (gpGlobals->time - m_lastTime));
	}

	pev->nextthink = gpGlobals->time + 0.1f;
	m_lastTime = gpGlobals->time;
}

void CCyclerSprite::Use(CBaseEntity *pActivator, CBaseEntity *pCaller, USE_TYPE useType, float value)
{
	m_animate = !m_animate;
	ALERT(at_console, "Sprite: %s\n", STRING(pev->model));
}

BOOL CCyclerSprite::TakeDamage(entvars_t *pevInflictor, entvars_t *pevAttacker, float flDamage, int bitsDamageType)
{
	if (m_maxFrame > 1.0)
	{
		Animate(1.0);
	}

	return TRUE;
}

void CCyclerSprite::Animate(float frames)
{
	pev->frame += frames;

	if (m_maxFrame > 0)
	{
		pev->frame = Q_fmod(real_t(pev->frame), real_t(m_maxFrame));
	}
}

LINK_ENTITY_TO_CLASS(cycler_weapon, CWeaponCycler, CCSWeaponCycler)

void CWeaponCycler::Spawn()
{
	pev->solid = SOLID_SLIDEBOX;
	pev->movetype = MOVETYPE_NONE;

	PRECACHE_MODEL(pev->model);
	SET_MODEL(ENT(pev), pev->model);

	m_iszModel = pev->model;
	m_iModel = pev->modelindex;

	UTIL_SetOrigin(pev, pev->origin);
	UTIL_SetSize(pev, Vector(-16, -16, 0), Vector(16, 16, 16));
	SetTouch(&CWeaponCycler::DefaultTouch);
}

BOOL CWeaponCycler::Deploy()
{
	m_pPlayer->pev->viewmodel = m_iszModel;
	m_pPlayer->m_flNextAttack = UTIL_WeaponTimeBase() + 1.0f;

	SendWeaponAnim(0);
	m_iClip = 0;

	return TRUE;
}

void CWeaponCycler::Holster(int skiplocal)
{
	m_pPlayer->m_flNextAttack = UTIL_WeaponTimeBase() + 0.5f;
}

void CWeaponCycler::PrimaryAttack()
{
	SendWeaponAnim(pev->sequence);
	m_flNextPrimaryAttack = gpGlobals->time + 0.3f;
}

void CWeaponCycler::SecondaryAttack()
{
	float flFrameRate, flGroundSpeed;

	pev->sequence = (pev->sequence + 1) % 8;

	pev->modelindex = m_iModel;
	void *pmodel = GET_MODEL_PTR(ENT(pev));
	GetSequenceInfo(pmodel, pev, &flFrameRate, &flGroundSpeed);
	pev->modelindex = 0;

	if (flFrameRate == 0.0)
	{
		pev->sequence = 0;
	}

	SendWeaponAnim(pev->sequence);
	m_flNextSecondaryAttack = gpGlobals->time + 0.3f;
}

TYPEDESCRIPTION CWreckage::m_SaveData[] =
{
	DEFINE_FIELD(CWreckage, m_flStartTime, FIELD_TIME),
};

IMPLEMENT_SAVERESTORE(CWreckage, CBaseToggle)
LINK_ENTITY_TO_CLASS(cycler_wreckage, CWreckage, CCSWreckage)

void CWreckage::Spawn()
{
	pev->solid = SOLID_NOT;
	pev->movetype = MOVETYPE_NONE;
	pev->takedamage = DAMAGE_NO;
	pev->effects = 0;

	pev->frame = 0;
	pev->nextthink = gpGlobals->time + 0.1f;

	if (!pev->model.IsNull())
	{
		PRECACHE_MODEL(pev->model);
		SET_MODEL(ENT(pev), pev->model);
	}

	// pev->scale = 5.0;
	m_flStartTime = int(gpGlobals->time);
}

void CWreckage::Precache()
{
	if (!pev->model.IsNull())
	{
		PRECACHE_MODEL(pev->model);
	}
}

void CWreckage::Think()
{
	StudioFrameAdvance();
	pev->nextthink = gpGlobals->time + 0.2f;

	if (pev->dmgtime)
	{
		if (pev->dmgtime < gpGlobals->time)
		{
			UTIL_Remove(this);
			return;
		}
		else if (RANDOM_FLOAT(0, pev->dmgtime - m_flStartTime) > pev->dmgtime - gpGlobals->time)
		{
			return;
		}
	}

	Vector vecSrc;
	vecSrc.x = RANDOM_FLOAT(pev->absmin.x, pev->absmax.x);
	vecSrc.y = RANDOM_FLOAT(pev->absmin.y, pev->absmax.y);
	vecSrc.z = RANDOM_FLOAT(pev->absmin.z, pev->absmax.z);

	MESSAGE_BEGIN(MSG_PVS, SVC_TEMPENTITY, vecSrc);
		WRITE_BYTE(TE_SMOKE);
		WRITE_COORD(vecSrc.x);
		WRITE_COORD(vecSrc.y);
		WRITE_COORD(vecSrc.z);
		WRITE_SHORT(g_sModelIndexSmoke);
		WRITE_BYTE(RANDOM_LONG(0, 49) + 50);	// scale * 10
		WRITE_BYTE(RANDOM_LONG(0, 3) + 8);		// framerate
	MESSAGE_END();
}

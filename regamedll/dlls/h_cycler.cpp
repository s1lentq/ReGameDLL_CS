#include "precompiled.h"

/*
* Globals initialization
*/
#ifndef HOOK_GAMEDLL

TYPEDESCRIPTION CCycler::m_SaveData[] =
{
	DEFINE_FIELD(CCycler, m_animate, FIELD_INTEGER),
};

TYPEDESCRIPTION CCyclerSprite::m_SaveData[] =
{
	DEFINE_FIELD(CCyclerSprite, m_animate, FIELD_INTEGER),
	DEFINE_FIELD(CCyclerSprite, m_lastTime, FIELD_TIME),
	DEFINE_FIELD(CCyclerSprite, m_maxFrame, FIELD_FLOAT),
};

TYPEDESCRIPTION CWreckage::m_SaveData[] =
{
	DEFINE_FIELD(CWreckage, m_flStartTime, FIELD_TIME),
};

#else

TYPEDESCRIPTION IMPL_CLASS(CCycler, m_SaveData)[1];
TYPEDESCRIPTION IMPL_CLASS(CCyclerSprite, m_SaveData)[3];
TYPEDESCRIPTION IMPL_CLASS(CWreckage, m_SaveData)[1];

#endif // HOOK_GAMEDLL

/* <cce5f> ../cstrike/dlls/h_cycler.cpp:61 */
IMPLEMENT_SAVERESTORE(CCycler, CBaseToggle);

/* <cd01f> ../cstrike/dlls/h_cycler.cpp:70 */
void CGenericCycler::__MAKE_VHOOK(Spawn)(void)
{
	GenericCyclerSpawn((char *)STRING(pev->model), Vector(-16, -16, 0), Vector(16, 16, 72));
}

/* <cd2d2> ../cstrike/dlls/h_cycler.cpp:72 */
LINK_ENTITY_TO_CLASS(cycler, CGenericCycler);

/* <cd39c> ../cstrike/dlls/h_cycler.cpp:85 */
LINK_ENTITY_TO_CLASS(cycler_prdroid, CCyclerProbe);

/* <cd16d> ../cstrike/dlls/h_cycler.cpp:86 */
void CCyclerProbe::__MAKE_VHOOK(Spawn)(void)
{
	pev->origin = pev->origin + Vector(0, 0, 16);
	GenericCyclerSpawn("models/prdroid.mdl", Vector(-16, -16, -16), Vector(16, 16, 16));
}

// Cycler member functions

/* <cd466> ../cstrike/dlls/h_cycler.cpp:96 */
void CCycler::GenericCyclerSpawn(char *szModel, Vector vecMin, Vector vecMax)
{
	if (!szModel || !*szModel)
	{
		ALERT(at_error, "cycler at %.0f %.0f %0.f missing modelname", pev->origin.x, pev->origin.y, pev->origin.z);
		REMOVE_ENTITY(ENT(pev));
		return;
	}

	if (pev->classname)
	{
		RemoveEntityHashValue(pev, STRING(pev->classname), CLASSNAME);
	}

	MAKE_STRING_CLASS("cycler", pev);
	AddEntityHashValue(pev, STRING(pev->classname), CLASSNAME);

	PRECACHE_MODEL(szModel);
	SET_MODEL(ENT(pev), szModel);

	CCycler::Spawn();

	UTIL_SetSize(pev, vecMin, vecMax);
}

/* <ccc91> ../cstrike/dlls/h_cycler.cpp:115 */
void CCycler::__MAKE_VHOOK(Spawn)(void)
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

	pev->nextthink += 1.0;

	ResetSequenceInfo();

	if (pev->sequence != 0 || pev->frame != 0)
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

/* <ccd3e> ../cstrike/dlls/h_cycler.cpp:151 */
void CCycler::__MAKE_VHOOK(Think)(void)
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
		pev->framerate = 1.0;
		m_fSequenceFinished = FALSE;
		m_flLastEventCheck = gpGlobals->time;
		pev->frame = 0;

		if (!m_animate)
		{
			// FIX: don't reset framerate
			pev->framerate = 0.0;
		}
	}
}

// CyclerUse - starts a rotation trend

/* <cc8bf> ../cstrike/dlls/h_cycler.cpp:176 */
void CCycler::__MAKE_VHOOK(Use)(CBaseEntity *pActivator, CBaseEntity *pCaller, USE_TYPE useType, float value)
{
	m_animate = !m_animate;

	if (m_animate)
		pev->framerate = 1.0;
	else
		pev->framerate = 0.0;
}

// CyclerPain , changes sequences when shot

/* <ccf43> ../cstrike/dlls/h_cycler.cpp:189 */
int CCycler::__MAKE_VHOOK(TakeDamage)(entvars_t *pevInflictor, entvars_t *pevAttacker, float flDamage, int bitsDamageType)
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

	return 0;
}

/* <cd4f8> ../cstrike/dlls/h_cycler.cpp:246 */
LINK_ENTITY_TO_CLASS(cycler_sprite, CCyclerSprite);

/* <ccef7> ../cstrike/dlls/h_cycler.cpp:255 */
IMPLEMENT_SAVERESTORE(CCyclerSprite, CBaseEntity);

/* <cc943> ../cstrike/dlls/h_cycler.cpp:258 */
void CCyclerSprite::__MAKE_VHOOK(Spawn)(void)
{
	pev->solid = SOLID_SLIDEBOX;
	pev->movetype = MOVETYPE_NONE;
	pev->takedamage = DAMAGE_YES;
	pev->effects = 0;

	pev->frame = 0;
	pev->nextthink = gpGlobals->time + 0.1f;
	m_animate = 1;
	m_lastTime = gpGlobals->time;

	PRECACHE_MODEL((char *)STRING(pev->model));
	SET_MODEL(ENT(pev), STRING(pev->model));

	m_maxFrame = (float)MODEL_FRAMES(pev->modelindex) - 1;

	m_renderfx = pev->renderfx;
	m_rendermode = pev->rendermode;
	m_renderamt = pev->renderamt;

	for (int i = 0; i < ARRAYSIZE(pev->rendercolor); i++)
	{
		pev->rendercolor[i] = m_rendercolor[i];
	}
}

/* <cc982> ../cstrike/dlls/h_cycler.cpp:284 */
void CCyclerSprite::__MAKE_VHOOK(Restart)(void)
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

	for (int i = 0; i < ARRAYSIZE(pev->rendercolor); i++)
	{
		pev->rendercolor[i] = m_rendercolor[i];
	}
}

/* <cd0ef> ../cstrike/dlls/h_cycler.cpp:305 */
void CCyclerSprite::__MAKE_VHOOK(Think)(void)
{
	if (ShouldAnimate())
	{
		Animate(pev->framerate * (gpGlobals->time - m_lastTime));
	}

	pev->nextthink = gpGlobals->time + 0.1f;
	m_lastTime = gpGlobals->time;
}

/* <cc9c1> ../cstrike/dlls/h_cycler.cpp:315 */
void CCyclerSprite::__MAKE_VHOOK(Use)(CBaseEntity *pActivator, CBaseEntity *pCaller, USE_TYPE useType, float value)
{
	m_animate = !m_animate;
	ALERT(at_console, "Sprite: %s\n", STRING(pev->model));
}

/* <cd228> ../cstrike/dlls/h_cycler.cpp:322 */
int CCyclerSprite::__MAKE_VHOOK(TakeDamage)(entvars_t *pevInflictor, entvars_t *pevAttacker, float flDamage, int bitsDamageType)
{
	if (m_maxFrame > 1.0)
	{
		Animate(1.0);
	}

	return 1;
}

/* <cd5c2> ../cstrike/dlls/h_cycler.cpp:331 */
void CCyclerSprite::Animate(float frames)
{
	pev->frame += frames;

	if (m_maxFrame > 0)
	{
		pev->frame = fmod((float_precision)pev->frame, (float_precision)m_maxFrame);
	}
}

/* <cd610> ../cstrike/dlls/h_cycler.cpp:358 */
LINK_ENTITY_TO_CLASS(cycler_weapon, CWeaponCycler);

/* <ccbf6> ../cstrike/dlls/h_cycler.cpp:361 */
void CWeaponCycler::__MAKE_VHOOK(Spawn)(void)
{
	pev->solid = SOLID_SLIDEBOX;
	pev->movetype = MOVETYPE_NONE;

	PRECACHE_MODEL((char *)STRING(pev->model));
	SET_MODEL(ENT(pev), STRING(pev->model));

	m_iszModel = pev->model;
	m_iModel = pev->modelindex;

	UTIL_SetOrigin(pev, pev->origin);
	UTIL_SetSize(pev, Vector(-16, -16, 0), Vector(16, 16, 16));
	SetTouch(&CWeaponCycler::DefaultTouch);
}

/* <cca7c> ../cstrike/dlls/h_cycler.cpp:378 */
BOOL CWeaponCycler::__MAKE_VHOOK(Deploy)(void)
{
	m_pPlayer->pev->viewmodel = m_iszModel;
	m_pPlayer->m_flNextAttack = UTIL_WeaponTimeBase() + 1.0;

	SendWeaponAnim(0);
	m_iClip = 0;

	return TRUE;
}

/* <ccaa3> ../cstrike/dlls/h_cycler.cpp:388 */
void CWeaponCycler::__MAKE_VHOOK(Holster)(int skiplocal)
{
	m_pPlayer->m_flNextAttack = UTIL_WeaponTimeBase() + 0.5;
}

/* <ccad8> ../cstrike/dlls/h_cycler.cpp:394 */
void CWeaponCycler::__MAKE_VHOOK(PrimaryAttack)(void)
{
	SendWeaponAnim(pev->sequence);
	m_flNextPrimaryAttack = gpGlobals->time + 0.3;
}

/* <ccb97> ../cstrike/dlls/h_cycler.cpp:403 */
void CWeaponCycler::__MAKE_VHOOK(SecondaryAttack)(void)
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
	m_flNextSecondaryAttack = gpGlobals->time + 0.3;
}

/* <cce12> ../cstrike/dlls/h_cycler.cpp:443 */
IMPLEMENT_SAVERESTORE(CWreckage, CBaseToggle);

/* <cd6dd> ../cstrike/dlls/h_cycler.cpp:446 */
LINK_ENTITY_TO_CLASS(cycler_wreckage, CWreckage);

/* <ccaff> ../cstrike/dlls/h_cycler.cpp:448 */
void CWreckage::__MAKE_VHOOK(Spawn)(void)
{
	pev->solid = SOLID_NOT;
	pev->movetype = MOVETYPE_NONE;
	pev->takedamage = DAMAGE_NO;
	pev->effects = 0;

	pev->frame = 0;
	pev->nextthink = gpGlobals->time + 0.1f;

	if (!FStringNull(pev->model))
	{
		PRECACHE_MODEL((char *)STRING(pev->model));
		SET_MODEL(ENT(pev), STRING(pev->model));
	}

	// pev->scale = 5.0;
	m_flStartTime = (int)gpGlobals->time;
}

/* <ccd07> ../cstrike/dlls/h_cycler.cpp:468 */
void CWreckage::__MAKE_VHOOK(Precache)(void)
{
	if (!FStringNull(pev->model))
	{
		PRECACHE_MODEL((char *)STRING(pev->model));
	}
}

/* <ccb26> ../cstrike/dlls/h_cycler.cpp:474 */
void CWreckage::__MAKE_VHOOK(Think)(void)
{
	StudioFrameAdvance();
	pev->nextthink = gpGlobals->time + 0.2;

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

	Vector VecSrc;

	VecSrc.x = RANDOM_FLOAT(pev->absmin.x, pev->absmax.x);
	VecSrc.y = RANDOM_FLOAT(pev->absmin.y, pev->absmax.y);
	VecSrc.z = RANDOM_FLOAT(pev->absmin.z, pev->absmax.z);

	MESSAGE_BEGIN(MSG_PVS, SVC_TEMPENTITY, VecSrc);
		WRITE_BYTE(TE_SMOKE);
		WRITE_COORD(VecSrc.x);
		WRITE_COORD(VecSrc.y);
		WRITE_COORD(VecSrc.z);
		WRITE_SHORT(g_sModelIndexSmoke);
		WRITE_BYTE(RANDOM_LONG(0, 49) + 50);	// scale * 10
		WRITE_BYTE(RANDOM_LONG(0, 3) + 8);		// framerate
	MESSAGE_END();
}

#ifdef HOOK_GAMEDLL

void CWreckage::Spawn(void)
{
	Spawn_();
}

void CWreckage::Precache(void)
{
	Precache_();
}

int CWreckage::Save(CSave &save)
{
	return Save_(save);
}

int CWreckage::Restore(CRestore &restore)
{
	return Restore_(restore);
}

void CWreckage::Think(void)
{
	Think_();
}

void CWeaponCycler::Spawn(void)
{
	Spawn_();
}

BOOL CWeaponCycler::Deploy(void)
{
	return Deploy_();
}

void CWeaponCycler::Holster(int skiplocal)
{
	Holster_(skiplocal);
}

void CWeaponCycler::PrimaryAttack(void)
{
	PrimaryAttack_();
}

void CWeaponCycler::SecondaryAttack(void)
{
	SecondaryAttack_();
}

void CCyclerSprite::Spawn(void)
{
	Spawn_();
}

void CCyclerSprite::Restart(void)
{
	Restart_();
}

int CCyclerSprite::Save(CSave &save)
{
	return Save_(save);
}

int CCyclerSprite::Restore(CRestore &restore)
{
	return Restore_(restore);
}

int CCyclerSprite::TakeDamage(entvars_t *pevInflictor, entvars_t *pevAttacker, float flDamage, int bitsDamageType)
{
	return TakeDamage_(pevInflictor,pevAttacker,flDamage,bitsDamageType);
}

void CCyclerSprite::Think(void)
{
	Think_();
}

void CCyclerSprite::Use(CBaseEntity *pActivator, CBaseEntity *pCaller, USE_TYPE useType, float value)
{
	Use_(pActivator,pCaller,useType,value);
}

void CCycler::Spawn(void)
{
	Spawn_();
}

int CCycler::Save(CSave &save)
{
	return Save_(save);
}

int CCycler::Restore(CRestore &restore)
{
	return Restore_(restore);
}

int CCycler::TakeDamage(entvars_t *pevInflictor, entvars_t *pevAttacker, float flDamage, int bitsDamageType)
{
	return TakeDamage_(pevInflictor,pevAttacker,flDamage,bitsDamageType);
}

void CCycler::Think(void)
{
	Think_();
}

void CCycler::Use(CBaseEntity *pActivator, CBaseEntity *pCaller, USE_TYPE useType, float value)
{
	Use_(pActivator,pCaller,useType,value);
}

void CGenericCycler::Spawn(void)
{
	Spawn_();
}

void CCyclerProbe::Spawn(void)
{
	Spawn_();
}

#endif // HOOK_GAMEDLL

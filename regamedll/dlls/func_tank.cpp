#include "precompiled.h"

/*
* Globals initialization
*/
#ifndef HOOK_GAMEDLL

TYPEDESCRIPTION CFuncTank::m_SaveData[] =
{
	DEFINE_FIELD(CFuncTank, m_yawCenter, FIELD_FLOAT),
	DEFINE_FIELD(CFuncTank, m_yawRate, FIELD_FLOAT),
	DEFINE_FIELD(CFuncTank, m_yawRange, FIELD_FLOAT),
	DEFINE_FIELD(CFuncTank, m_yawTolerance, FIELD_FLOAT),
	DEFINE_FIELD(CFuncTank, m_pitchCenter, FIELD_FLOAT),
	DEFINE_FIELD(CFuncTank, m_pitchRate, FIELD_FLOAT),
	DEFINE_FIELD(CFuncTank, m_pitchRange, FIELD_FLOAT),
	DEFINE_FIELD(CFuncTank, m_pitchTolerance, FIELD_FLOAT),
	DEFINE_FIELD(CFuncTank, m_fireLast, FIELD_TIME),
	DEFINE_FIELD(CFuncTank, m_fireRate, FIELD_FLOAT),
	DEFINE_FIELD(CFuncTank, m_lastSightTime, FIELD_TIME),
	DEFINE_FIELD(CFuncTank, m_persist, FIELD_FLOAT),
	DEFINE_FIELD(CFuncTank, m_minRange, FIELD_FLOAT),
	DEFINE_FIELD(CFuncTank, m_maxRange, FIELD_FLOAT),
	DEFINE_FIELD(CFuncTank, m_barrelPos, FIELD_VECTOR),
	DEFINE_FIELD(CFuncTank, m_spriteScale, FIELD_FLOAT),
	DEFINE_FIELD(CFuncTank, m_iszSpriteSmoke, FIELD_STRING),
	DEFINE_FIELD(CFuncTank, m_iszSpriteFlash, FIELD_STRING),
	DEFINE_FIELD(CFuncTank, m_bulletType, FIELD_INTEGER),
	DEFINE_FIELD(CFuncTank, m_sightOrigin, FIELD_VECTOR),
	DEFINE_FIELD(CFuncTank, m_spread, FIELD_INTEGER),
	DEFINE_FIELD(CFuncTank, m_pController, FIELD_CLASSPTR),
	DEFINE_FIELD(CFuncTank, m_vecControllerUsePos, FIELD_VECTOR),
	DEFINE_FIELD(CFuncTank, m_flNextAttack, FIELD_TIME),
	DEFINE_FIELD(CFuncTank, m_iBulletDamage, FIELD_INTEGER),
	DEFINE_FIELD(CFuncTank, m_iszMaster, FIELD_STRING),
};

TYPEDESCRIPTION CFuncTankLaser::m_SaveData[] =
{
	DEFINE_FIELD(CFuncTankLaser, m_pLaser, FIELD_CLASSPTR),
	DEFINE_FIELD(CFuncTankLaser, m_laserTime, FIELD_TIME),
};

TYPEDESCRIPTION CFuncTankControls::m_SaveData[] =
{
	DEFINE_FIELD(CFuncTankControls, m_pTank, FIELD_CLASSPTR),
};

static Vector gTankSpread[] =
{
	Vector(0, 0, 0),		// perfect
	Vector(0.025, 0.025, 0.025),	// small cone
	Vector(0.05, 0.05, 0.05),	// medium cone
	Vector(0.1, 0.1, 0.1),		// large cone
	Vector(0.25, 0.25, 0.25),	// extra-large cone
};

#else

TYPEDESCRIPTION IMPL_CLASS(CFuncTank, m_SaveData)[26];
TYPEDESCRIPTION IMPL_CLASS(CFuncTankLaser, m_SaveData)[2];
TYPEDESCRIPTION IMPL_CLASS(CFuncTankControls, m_SaveData)[1];
Vector gTankSpread[5];

#endif // HOOK_GAMEDLL

#define MAX_FIRING_SPREADS ARRAYSIZE(gTankSpread)

/* <8d76a> ../cstrike/dlls/func_tank.cpp:164 */
IMPLEMENT_SAVERESTORE(CFuncTank, CBaseEntity);

/* <8ea25> ../cstrike/dlls/func_tank.cpp:177 */
void CFuncTank::__MAKE_VHOOK(Spawn)(void)
{
	Precache();

	// so it doesn't get pushed by anything
	pev->movetype = MOVETYPE_PUSH;
	pev->solid = SOLID_BSP;
	SET_MODEL(ENT(pev), STRING(pev->model));

	m_yawCenter = pev->angles.y;
	m_pitchCenter = pev->angles.x;

	if (IsActive())
	{
		pev->nextthink = pev->ltime + 1.0;
	}

	// Point at the end of the barrel
	m_sightOrigin = BarrelPosition();

	if (m_fireRate <= 0)
		m_fireRate = 1;

	if (m_spread > MAX_FIRING_SPREADS)
		m_spread = 0;

	pev->oldorigin = pev->origin;
}

/* <8d64d> ../cstrike/dlls/func_tank.cpp:202 */
void CFuncTank::__MAKE_VHOOK(Precache)(void)
{
	if (m_iszSpriteSmoke)
	{
		PRECACHE_MODEL((char *)STRING(m_iszSpriteSmoke));
	}

	if (m_iszSpriteFlash)
	{
		PRECACHE_MODEL((char *)STRING(m_iszSpriteFlash));
	}

	if (pev->noise)
	{
		PRECACHE_SOUND((char *)STRING(pev->noise));
	}
}

/* <8e19e> ../cstrike/dlls/func_tank.cpp:214 */
void CFuncTank::__MAKE_VHOOK(KeyValue)(KeyValueData *pkvd)
{
	if (FStrEq(pkvd->szKeyName, "yawrate"))
	{
		m_yawRate = Q_atof(pkvd->szValue);
		pkvd->fHandled = TRUE;
	}
	else if (FStrEq(pkvd->szKeyName, "yawrange"))
	{
		m_yawRange = Q_atof(pkvd->szValue);
		pkvd->fHandled = TRUE;
	}
	else if (FStrEq(pkvd->szKeyName, "yawtolerance"))
	{
		m_yawTolerance = Q_atof(pkvd->szValue);
		pkvd->fHandled = TRUE;
	}
	else if (FStrEq(pkvd->szKeyName, "pitchrange"))
	{
		m_pitchRange = Q_atof(pkvd->szValue);
		pkvd->fHandled = TRUE;
	}
	else if (FStrEq(pkvd->szKeyName, "pitchrate"))
	{
		m_pitchRate = Q_atof(pkvd->szValue);
		pkvd->fHandled = TRUE;
	}
	else if (FStrEq(pkvd->szKeyName, "pitchtolerance"))
	{
		m_pitchTolerance = Q_atof(pkvd->szValue);
		pkvd->fHandled = TRUE;
	}
	else if (FStrEq(pkvd->szKeyName, "firerate"))
	{
		m_fireRate = Q_atof(pkvd->szValue);
		pkvd->fHandled = TRUE;
	}
	else if (FStrEq(pkvd->szKeyName, "barrel"))
	{
		m_barrelPos.x = Q_atof(pkvd->szValue);
		pkvd->fHandled = TRUE;
	}
	else if (FStrEq(pkvd->szKeyName, "barrely"))
	{
		m_barrelPos.y = Q_atof(pkvd->szValue);
		pkvd->fHandled = TRUE;
	}
	else if (FStrEq(pkvd->szKeyName, "barrelz"))
	{
		m_barrelPos.z = Q_atof(pkvd->szValue);
		pkvd->fHandled = TRUE;
	}
	else if (FStrEq(pkvd->szKeyName, "spritescale"))
	{
		m_spriteScale = Q_atof(pkvd->szValue);
		pkvd->fHandled = TRUE;
	}
	else if (FStrEq(pkvd->szKeyName, "spritesmoke"))
	{
		m_iszSpriteSmoke = ALLOC_STRING(pkvd->szValue);
		pkvd->fHandled = TRUE;
	}
	else if (FStrEq(pkvd->szKeyName, "spriteflash"))
	{
		m_iszSpriteFlash = ALLOC_STRING(pkvd->szValue);
		pkvd->fHandled = TRUE;
	}
	else if (FStrEq(pkvd->szKeyName, "rotatesound"))
	{
		pev->noise = ALLOC_STRING(pkvd->szValue);
		pkvd->fHandled = TRUE;
	}
	else if (FStrEq(pkvd->szKeyName, "persistence"))
	{
		m_persist = Q_atof(pkvd->szValue);
		pkvd->fHandled = TRUE;
	}
	else if (FStrEq(pkvd->szKeyName, "bullet"))
	{
		m_bulletType = (TANKBULLET)Q_atoi(pkvd->szValue);
		pkvd->fHandled = TRUE;
	}
	else if (FStrEq(pkvd->szKeyName, "bullet_damage"))
	{
		m_iBulletDamage = Q_atoi(pkvd->szValue);
		pkvd->fHandled = TRUE;
	}
	else if (FStrEq(pkvd->szKeyName, "firespread"))
	{
		m_spread = Q_atoi(pkvd->szValue);
		pkvd->fHandled = TRUE;
	}
	else if (FStrEq(pkvd->szKeyName, "minRange"))
	{
		m_minRange = Q_atof(pkvd->szValue);
		pkvd->fHandled = TRUE;
	}
	else if (FStrEq(pkvd->szKeyName, "maxRange"))
	{
		m_maxRange = Q_atof(pkvd->szValue);
		pkvd->fHandled = TRUE;
	}
	else if (FStrEq(pkvd->szKeyName, "master"))
	{
		m_iszMaster = ALLOC_STRING(pkvd->szValue);
		pkvd->fHandled = TRUE;
	}
	else
		CBaseEntity::KeyValue(pkvd);
}

/* <8dca8> ../cstrike/dlls/func_tank.cpp:329 */
BOOL CFuncTank::__MAKE_VHOOK(OnControls)(entvars_t *pevTest)
{
	if (!(pev->spawnflags & SF_TANK_CANCONTROL))
		return FALSE;

	Vector offset = pevTest->origin - pev->origin;

	if ((m_vecControllerUsePos - pevTest->origin).Length() < 30)
	{
		return TRUE;
	}

	return FALSE;
}

/* <8eba8> ../cstrike/dlls/func_tank.cpp:342 */
BOOL CFuncTank::StartControl(CBasePlayer *pController)
{
	if (m_pController != NULL)
		return FALSE;

	// Team only or disabled?
	if (m_iszMaster)
	{
		if (!UTIL_IsMasterTriggered(m_iszMaster, pController))
		{
			return FALSE;
		}
	}

	ALERT(at_console, "using TANK!\n");

	m_pController = pController;

	if (m_pController->m_pActiveItem != NULL)
	{
		m_pController->m_pActiveItem->Holster();
		m_pController->pev->weaponmodel = 0;
		//m_pController->pev->viewmodel = 0;
	}

	m_pController->m_iHideHUD |= HIDEHUD_WEAPONS;
	m_vecControllerUsePos = m_pController->pev->origin;

	pev->nextthink = pev->ltime + 0.1;

	return TRUE;
}

/* <8ebde> ../cstrike/dlls/func_tank.cpp:372 */
void CFuncTank::StopControl(void)
{
	// TODO: bring back the controllers current weapon
	if (!m_pController)
		return;

	if (m_pController->m_pActiveItem != NULL)
	{
		m_pController->m_pActiveItem->Deploy();

		if (m_pController->IsPlayer())
		{
			m_pController->ResetMaxSpeed();
		}
	}

	ALERT(at_console, "stopped using TANK\n");

	m_pController->m_iHideHUD &= ~HIDEHUD_WEAPONS;

	pev->nextthink = 0;
	m_pController = NULL;

	if (IsActive())
	{
		pev->nextthink = pev->ltime + 1.0;
	}
}

/* <8ec15> ../cstrike/dlls/func_tank.cpp:398 */
void CFuncTank::ControllerPostFrame(void)
{
	assert(m_pController != NULL);

	if (gpGlobals->time < m_flNextAttack)
		return;

	if (m_pController->pev->button & IN_ATTACK)
	{
		Vector vecForward;
		UTIL_MakeVectorsPrivate(pev->angles, vecForward, NULL, NULL);

		m_fireLast = gpGlobals->time - (1 / m_fireRate) - 0.01;
		Fire(BarrelPosition(), vecForward, m_pController->pev);

		if (m_pController && m_pController->IsPlayer())
		{
			m_pController->m_iWeaponVolume = LOUD_GUN_VOLUME;
		}

		m_flNextAttack = gpGlobals->time + (1 / m_fireRate);
	}
}

/* <8ee12> ../cstrike/dlls/func_tank.cpp:424 */
void CFuncTank::__MAKE_VHOOK(Use)(CBaseEntity *pActivator, CBaseEntity *pCaller, USE_TYPE useType, float value)
{
	// player controlled turret
	if (pev->spawnflags & SF_TANK_CANCONTROL)
	{
		if (pActivator->Classify() != CLASS_PLAYER)
			return;

		if (value == 2 && useType == USE_SET)
		{
			ControllerPostFrame();
		}
		else if (!m_pController && useType != USE_OFF)
		{
			((CBasePlayer*)pActivator)->m_pTank = this;
			StartControl((CBasePlayer*)pActivator);
		}
		else
		{
			StopControl();
		}
	}
	else
	{
		if (!ShouldToggle(useType, IsActive()))
			return;

		if (IsActive())
			TankDeactivate();
		else
			TankActivate();
	}
}

/* <8ef04> ../cstrike/dlls/func_tank.cpp:459 */
edict_t *CFuncTank::FindTarget(edict_t *pPlayer)
{
	return pPlayer;
}

/* <8ef2d> ../cstrike/dlls/func_tank.cpp:466 */
BOOL CFuncTank::InRange(float range)
{
	if (range < m_minRange)
		return FALSE;

	if (m_maxRange > 0 && range > m_maxRange)
		return FALSE;

	return TRUE;
}

/* <8f717> ../cstrike/dlls/func_tank.cpp:477 */
void CFuncTank::__MAKE_VHOOK(Think)(void)
{
	pev->avelocity = g_vecZero;
	TrackTarget();

	if (fabs((float_precision)pev->avelocity.x) > 1 || fabs((float_precision)pev->avelocity.y) > 1)
		StartRotSound();
	else
		StopRotSound();
}

/* <8efe4> ../cstrike/dlls/func_tank.cpp:488 */
void CFuncTank::TrackTarget(void)
{
	TraceResult tr;
	edict_t *pPlayer = FIND_CLIENT_IN_PVS(edict());
	BOOL updateTime = FALSE, lineOfSight;
	Vector angles, direction, targetPosition, barrelEnd;
	edict_t *pTarget = NULL;

	// Get a position to aim for
	if (m_pController != NULL)
	{
		// Tanks attempt to mirror the player's angles
		angles = m_pController->pev->v_angle;
		angles.x = 0 - angles.x;
		pev->nextthink = pev->ltime + 0.05;
	}
	else
	{
		if (IsActive())
			pev->nextthink = pev->ltime + 0.1;
		else
			return;

		if (FNullEnt(pPlayer))
		{
			if (IsActive())
			{
				// Wait 2 secs
				pev->nextthink = pev->ltime + 2;
			}

			return;
		}

		pTarget = FindTarget(pPlayer);
		if (!pTarget)
		{
			return;
		}

		// Calculate angle needed to aim at target
		barrelEnd = BarrelPosition();
		targetPosition = pTarget->v.origin + pTarget->v.view_ofs;
		float range = (targetPosition - barrelEnd).Length();

		if (!InRange(range))
			return;

		UTIL_TraceLine(barrelEnd, targetPosition, dont_ignore_monsters, edict(), &tr);
		lineOfSight = FALSE;

		// No line of sight, don't track
		if (tr.flFraction == 1.0f || tr.pHit == pTarget)
		{
			lineOfSight = TRUE;

			CBaseEntity *pInstance = CBaseEntity::Instance(pTarget);
			if (InRange(range) && pInstance && pInstance->IsAlive())
			{
				updateTime = TRUE;
				m_sightOrigin = UpdateTargetPosition(pInstance);
			}
		}

		// Track sight origin
		// !!! I'm not sure what i changed
		direction = m_sightOrigin - pev->origin;
		//direction = m_sightOrigin - barrelEnd;
		angles = UTIL_VecToAngles(direction);

		// Calculate the additional rotation to point the end of the barrel at the target (not the gun's center)
		AdjustAnglesForBarrel(angles, direction.Length());
	}

	angles.x = -angles.x;

	// Force the angles to be relative to the center position
	angles.y = m_yawCenter + UTIL_AngleDistance(angles.y, m_yawCenter);
	angles.x = m_pitchCenter + UTIL_AngleDistance(angles.x, m_pitchCenter);

	// Limit against range in y
	if (angles.y > m_yawCenter + m_yawRange)
	{
		angles.y = m_yawCenter + m_yawRange;

		// Don't update if you saw the player, but out of range
		updateTime = FALSE;
	}
	else if (angles.y < (m_yawCenter - m_yawRange))
	{
		angles.y = (m_yawCenter - m_yawRange);

		// Don't update if you saw the player, but out of range
		updateTime = FALSE;
	}

	if (updateTime)
	{
		m_lastSightTime = gpGlobals->time;
	}

	// Move toward target at rate or less
	float_precision distY = UTIL_AngleDistance(angles.y, pev->angles.y);
	pev->avelocity.y = distY * 10;

	if (pev->avelocity.y > m_yawRate)
	{
		pev->avelocity.y = m_yawRate;
	}
	else if (pev->avelocity.y < -m_yawRate)
	{
		pev->avelocity.y = -m_yawRate;
	}

	// Limit against range in x
	if (angles.x > m_pitchCenter + m_pitchRange)
	{
		angles.x = m_pitchCenter + m_pitchRange;
	}
	else if (angles.x < m_pitchCenter - m_pitchRange)
	{
		angles.x = m_pitchCenter - m_pitchRange;
	}

	// Move toward target at rate or less
	float_precision distX = UTIL_AngleDistance(angles.x, pev->angles.x);
	pev->avelocity.x = distX  * 10;

	if (pev->avelocity.x > m_pitchRate)
	{
		pev->avelocity.x = m_pitchRate;
	}
	else if (pev->avelocity.x < -m_pitchRate)
	{
		pev->avelocity.x = -m_pitchRate;
	}

	if (m_pController != NULL)
	{
		return;
	}

	if (CanFire() && ((fabs(distX) < m_pitchTolerance && fabs(distY) < m_yawTolerance) || (pev->spawnflags & SF_TANK_LINEOFSIGHT)))
	{
		BOOL fire = FALSE;
		Vector forward;
		UTIL_MakeVectorsPrivate(pev->angles, forward, NULL, NULL);

		if (pev->spawnflags & SF_TANK_LINEOFSIGHT)
		{
			float length = direction.Length();
			UTIL_TraceLine(barrelEnd, barrelEnd + forward * length, dont_ignore_monsters, edict(), &tr);

			if (tr.pHit == pTarget)
			{
				fire = TRUE;
			}
		}
		else
			fire = TRUE;

		if (fire)
		{
			Fire(BarrelPosition(), forward, pev);
		}
		else
			m_fireLast = 0;
	}
	else
		m_fireLast = 0;
}

// If barrel is offset, add in additional rotation

/* <8ef79> ../cstrike/dlls/func_tank.cpp:632 */
void CFuncTank::AdjustAnglesForBarrel(Vector &angles, float distance)
{
	float_precision r2, d2;

	if (m_barrelPos.y != 0 || m_barrelPos.z != 0)
	{
		distance -= m_barrelPos.z;
		d2 = distance * distance;

		if (m_barrelPos.y)
		{
			r2 = m_barrelPos.y * m_barrelPos.y;
			angles.y += (180.0 / M_PI) * atan2(m_barrelPos.y, sqrt(d2 - r2));
		}

		if (m_barrelPos.z)
		{
			r2 = m_barrelPos.z * m_barrelPos.z;
			angles.x += (180.0 / M_PI) * atan2(-m_barrelPos.z, sqrt(d2 - r2));
		}
	}
}

// Fire targets and spawn sprites

/* <8d4ad> ../cstrike/dlls/func_tank.cpp:656 */
void CFuncTank::__MAKE_VHOOK(Fire)(const Vector &barrelEnd, const Vector &forward, entvars_t *pevAttacker)
{
	if (m_fireLast != 0)
	{
		if (m_iszSpriteSmoke)
		{
			CSprite *pSprite = CSprite::SpriteCreate(STRING(m_iszSpriteSmoke), barrelEnd, TRUE);

			pSprite->AnimateAndDie(RANDOM_FLOAT(15, 20));
			pSprite->SetTransparency(kRenderTransAlpha, pev->rendercolor.x, pev->rendercolor.y, pev->rendercolor.z, 255, kRenderFxNone);
			pSprite->pev->velocity.z = RANDOM_FLOAT(40, 80);
			pSprite->SetScale(m_spriteScale);
		}

		if (m_iszSpriteFlash)
		{
			CSprite *pSprite = CSprite::SpriteCreate(STRING(m_iszSpriteFlash), barrelEnd, TRUE);

			pSprite->AnimateAndDie(60);
			pSprite->SetTransparency(kRenderTransAdd, 255, 255, 255, 255, kRenderFxNoDissipation);
			pSprite->SetScale(m_spriteScale);

			// Hack Hack, make it stick around for at least 100 ms.
			pSprite->pev->nextthink += 0.1;
		}

		SUB_UseTargets(this, USE_TOGGLE, 0);
	}

	m_fireLast = gpGlobals->time;
}

/* <8f830> ../cstrike/dlls/func_tank.cpp:684 */
void CFuncTank::TankTrace(const Vector &vecStart, const Vector &vecForward, const Vector &vecSpread, TraceResult &tr)
{
	// get circular gaussian spread
	float x, z;
	float_precision y;

	do
	{
		x = RANDOM_FLOAT(-0.5, 0.5) + RANDOM_FLOAT(-0.5, 0.5);
		y = RANDOM_FLOAT(-0.5, 0.5) + RANDOM_FLOAT(-0.5, 0.5);
		z = x * x + y * y;
	}
	while (z > 1);

	Vector vecDir = vecForward + x * vecSpread.x * gpGlobals->v_right + y * vecSpread.y * gpGlobals->v_up;
	Vector vecEnd;

	vecEnd = vecStart + vecDir * 4096;
	UTIL_TraceLine(vecStart, vecEnd, dont_ignore_monsters, edict(), &tr);
}

/* <8f9c0> ../cstrike/dlls/func_tank.cpp:703 */
void CFuncTank::StartRotSound(void)
{
	if (!pev->noise || (pev->spawnflags & SF_TANK_SOUNDON))
	{
		return;
	}

	pev->spawnflags |= SF_TANK_SOUNDON;
	EMIT_SOUND(edict(), CHAN_STATIC, (char *)STRING(pev->noise), 0.85, ATTN_NORM);
}

/* <8fa1b> ../cstrike/dlls/func_tank.cpp:712 */
void CFuncTank::StopRotSound(void)
{
	if (pev->spawnflags & SF_TANK_SOUNDON)
	{
		STOP_SOUND(edict(), CHAN_STATIC, (char *)STRING(pev->noise));
	}

	pev->spawnflags &= ~SF_TANK_SOUNDON;
}

/* <8fa65> ../cstrike/dlls/func_tank.cpp:724 */
LINK_ENTITY_TO_CLASS(func_tank, CFuncTankGun);

/* <8c3d5> ../cstrike/dlls/func_tank.cpp:726 */
void CFuncTankGun::__MAKE_VHOOK(Fire)(const Vector &barrelEnd, const Vector &forward, entvars_t *pevAttacker)
{
	int i;

	if (m_fireLast != 0)
	{
		// FireBullets needs gpGlobals->v_up, etc.
		UTIL_MakeAimVectors(pev->angles);

		int bulletCount = (int)((gpGlobals->time - m_fireLast) * m_fireRate);

		if (bulletCount > 0)
		{
			for (i = 0; i < bulletCount; i++)
			{
				switch(m_bulletType)
				{
				case TANK_BULLET_9MM:
					FireBullets(1, barrelEnd, forward, gTankSpread[m_spread], 4096, BULLET_MONSTER_9MM, 1, m_iBulletDamage, pevAttacker);
					break;
				case TANK_BULLET_MP5:
					FireBullets(1, barrelEnd, forward, gTankSpread[m_spread], 4096, BULLET_MONSTER_MP5, 1, m_iBulletDamage, pevAttacker);
					break;
				case TANK_BULLET_12MM:
					FireBullets(1, barrelEnd, forward, gTankSpread[m_spread], 4096, BULLET_MONSTER_12MM, 1, m_iBulletDamage, pevAttacker);
					break;
				default:
				case TANK_BULLET_NONE:
					break;
				}
			}

			CFuncTank::Fire(barrelEnd, forward, pevAttacker);
		}
	}
	else
		CFuncTank::Fire(barrelEnd, forward, pevAttacker);
}

/* <8fb34> ../cstrike/dlls/func_tank.cpp:785 */
LINK_ENTITY_TO_CLASS(func_tanklaser, CFuncTankLaser);

/* <8e07c> ../cstrike/dlls/func_tank.cpp:793 */
IMPLEMENT_SAVERESTORE(CFuncTankLaser, CFuncTank);

/* <8deed> ../cstrike/dlls/func_tank.cpp:795 */
void CFuncTankLaser::__MAKE_VHOOK(Activate)(void)
{
	if (!GetLaser())
	{
		UTIL_Remove(this);
		ALERT(at_error, "Laser tank with no env_laser!\n");
	}
	else
	{
		m_pLaser->TurnOff();
	}
}

/* <8e8ca> ../cstrike/dlls/func_tank.cpp:809 */
void CFuncTankLaser::__MAKE_VHOOK(KeyValue)(KeyValueData *pkvd)
{
	if (FStrEq(pkvd->szKeyName, "laserentity"))
	{
		pev->message = ALLOC_STRING(pkvd->szValue);
		pkvd->fHandled = TRUE;
	}
	else
		CFuncTank::KeyValue(pkvd);
}

/* <8dd79> ../cstrike/dlls/func_tank.cpp:821 */
CLaser *CFuncTankLaser::GetLaser(void)
{
	if (m_pLaser != NULL)
	{
		return m_pLaser;
	}

	edict_t	*pentLaser;

	pentLaser = FIND_ENTITY_BY_TARGETNAME(NULL, STRING(pev->message));

	while (!FNullEnt(pentLaser))
	{
		// Found the landmark
		if (FClassnameIs(pentLaser, "env_laser"))
		{
			m_pLaser = (CLaser *)CBaseEntity::Instance(pentLaser);
			break;
		}
		else
			pentLaser = FIND_ENTITY_BY_TARGETNAME(pentLaser, STRING(pev->message));
	}

	return m_pLaser;
}

/* <8f809> ../cstrike/dlls/func_tank.cpp:845 */
void CFuncTankLaser::__MAKE_VHOOK(Think)(void)
{
	if (m_pLaser != NULL && gpGlobals->time > m_laserTime)
	{
		m_pLaser->TurnOff();
	}

	CFuncTank::Think();
}

/* <8df51> ../cstrike/dlls/func_tank.cpp:854 */
void CFuncTankLaser::__MAKE_VHOOK(Fire)(const Vector &barrelEnd, const Vector &forward, entvars_t *pevAttacker)
{
	int i;
	TraceResult tr;

	if (m_fireLast != 0 && GetLaser())
	{
		// TankTrace needs gpGlobals->v_up, etc.
		UTIL_MakeAimVectors(pev->angles);

		int bulletCount = (int)((gpGlobals->time - m_fireLast) * m_fireRate);

		if (bulletCount)
		{
			for (i = 0; i < bulletCount; i++)
			{
				m_pLaser->pev->origin = barrelEnd;
				TankTrace(barrelEnd, forward, gTankSpread[m_spread], tr);

				m_laserTime = gpGlobals->time;
				m_pLaser->TurnOn();
				m_pLaser->pev->dmgtime = gpGlobals->time - 1.0;
				m_pLaser->FireAtPoint(tr);
				m_pLaser->pev->nextthink = 0;
			}

			CFuncTank::Fire(barrelEnd, forward, pev);
		}
	}
	else
	{
		CFuncTank::Fire(barrelEnd, forward, pev);
	}
}

/* <8fc2f> ../cstrike/dlls/func_tank.cpp:893 */
LINK_ENTITY_TO_CLASS(func_tankrocket, CFuncTankRocket);

/* <8e736> ../cstrike/dlls/func_tank.cpp:895 */
void CFuncTankRocket::__MAKE_VHOOK(Precache)(void)
{
	UTIL_PrecacheOther("rpg_rocket");
	CFuncTank::Precache();
}

/* <8d7b6> ../cstrike/dlls/func_tank.cpp:903 */
void CFuncTankRocket::__MAKE_VHOOK(Fire)(const Vector &barrelEnd, const Vector &forward, entvars_t *pevAttacker)
{
	int i;

	if (m_fireLast != 0)
	{
		int bulletCount = (int)((gpGlobals->time - m_fireLast) * m_fireRate);

		if (bulletCount > 0)
		{
			for (i = 0; i < bulletCount; i++)
			{
				CBaseEntity *pRocket = CBaseEntity::Create("rpg_rocket", barrelEnd, pev->angles, edict());
			}

			CFuncTank::Fire(barrelEnd, forward, pev);
		}
	}
	else
		CFuncTank::Fire(barrelEnd, forward, pev);
}

/* <8fcfe> ../cstrike/dlls/func_tank.cpp:930 */
LINK_ENTITY_TO_CLASS(func_tankmortar, CFuncTankMortar);

/* <8e790> ../cstrike/dlls/func_tank.cpp:933 */
void CFuncTankMortar::__MAKE_VHOOK(KeyValue)(KeyValueData *pkvd)
{
	if (FStrEq(pkvd->szKeyName, "iMagnitude"))
	{
		pev->impulse = Q_atoi(pkvd->szValue);
		pkvd->fHandled = TRUE;
	}
	else
		CFuncTank::KeyValue(pkvd);
}

/* <8dbfa> ../cstrike/dlls/func_tank.cpp:945 */
void CFuncTankMortar::__MAKE_VHOOK(Fire)(const Vector &barrelEnd, const Vector &forward, entvars_t *pevAttacker)
{
	if (m_fireLast != 0)
	{
		int bulletCount = (int)((gpGlobals->time - m_fireLast) * m_fireRate);

		// Only create 1 explosion
		if (bulletCount > 0)
		{
			TraceResult tr;

			// TankTrace needs gpGlobals->v_up, etc.
			UTIL_MakeAimVectors(pev->angles);

			TankTrace(barrelEnd, forward, gTankSpread[m_spread], tr);

			ExplosionCreate(tr.vecEndPos, pev->angles, edict(), pev->impulse, TRUE);

			CFuncTank::Fire(barrelEnd, forward, pev);
		}
	}
	else
		CFuncTank::Fire(barrelEnd, forward, pev);
}

/* <8fdcd> ../cstrike/dlls/func_tank.cpp:988 */
LINK_ENTITY_TO_CLASS(func_tankcontrols, CFuncTankControls);

/* <8d71d> ../cstrike/dlls/func_tank.cpp:995 */
IMPLEMENT_SAVERESTORE(CFuncTankControls, CBaseEntity);

/* <8d310> ../cstrike/dlls/func_tank.cpp:1003 */
void CFuncTankControls::__MAKE_VHOOK(Use)(CBaseEntity *pActivator, CBaseEntity *pCaller, USE_TYPE useType, float value)
{
	// pass the Use command onto the controls
	if (m_pTank)
	{
		m_pTank->Use(pActivator, pCaller, useType, value);
	}

	// if this fails,  most likely means save/restore hasn't worked properly
	assert(m_pTank != NULL);
}

/* <8d39a> ../cstrike/dlls/func_tank.cpp:1012 */
void CFuncTankControls::__MAKE_VHOOK(Think)(void)
{
	edict_t *pTarget = NULL;

	do
	{
		pTarget = FIND_ENTITY_BY_TARGETNAME(pTarget, STRING(pev->target));
	}
	while (!FNullEnt(pTarget) && Q_strncmp(STRING(pTarget->v.classname), "func_tank", 9));

	if (FNullEnt(pTarget))
	{
		ALERT(at_console, "No tank %s\n", STRING(pev->target));
		return;
	}

	m_pTank = reinterpret_cast<CFuncTank *>(Instance(pTarget));
}

/* <8d373> ../cstrike/dlls/func_tank.cpp:1030 */
void CFuncTankControls::__MAKE_VHOOK(Spawn)(void)
{
	pev->solid = SOLID_TRIGGER;
	pev->movetype = MOVETYPE_NONE;
	pev->effects |= EF_NODRAW;

	SET_MODEL(ENT(pev), STRING(pev->model));

	UTIL_SetSize(pev, pev->mins, pev->maxs);
	UTIL_SetOrigin(pev, pev->origin);

	// After all the func_tank's have spawned
	pev->nextthink = gpGlobals->time + 0.3;

	CBaseEntity::Spawn();
}

#ifdef HOOK_GAMEDLL

void CFuncTank::Spawn(void)
{
	Spawn_();
}

void CFuncTank::Precache(void)
{
	Precache_();
}

void CFuncTank::KeyValue(KeyValueData *pkvd)
{
	KeyValue_(pkvd);
}

int CFuncTank::Save(CSave &save)
{
	return Save_(save);
}

int CFuncTank::Restore(CRestore &restore)
{
	return Restore_(restore);
}

BOOL CFuncTank::OnControls(entvars_t *pevTest)
{
	OnControls_(pevTest);
}

void CFuncTank::Think(void)
{
	Think_();
}

void CFuncTank::Use(CBaseEntity *pActivator, CBaseEntity *pCaller, USE_TYPE useType, float value)
{
	Use_(pActivator, pCaller, useType, value);
}

void CFuncTank::Fire(const Vector &barrelEnd, const Vector &forward, entvars_t *pevAttacker)
{
	Fire_(barrelEnd, forward, pevAttacker);
}

void CFuncTankGun::Fire(const Vector &barrelEnd, const Vector &forward, entvars_t *pevAttacker)
{
	Fire_(barrelEnd, forward, pevAttacker);
}

void CFuncTankLaser::KeyValue(KeyValueData *pkvd)
{
	KeyValue_(pkvd);
}

int CFuncTankLaser::Save(CSave &save)
{
	return Save_(save);
}

int CFuncTankLaser::Restore(CRestore &restore)
{
	return Restore_(restore);
}

void CFuncTankLaser::Activate(void)
{
	Activate_();
}

void CFuncTankLaser::Think(void)
{
	Think_();
}

void CFuncTankLaser::Fire(const Vector &barrelEnd, const Vector &forward, entvars_t *pevAttacker)
{
	Fire_(barrelEnd, forward, pevAttacker);
}

void CFuncTankRocket::Precache(void)
{
	Precache_();
}

void CFuncTankRocket::Fire(const Vector &barrelEnd, const Vector &forward, entvars_t *pevAttacker)
{
	Fire_(barrelEnd, forward, pevAttacker);
}

void CFuncTankMortar::KeyValue(KeyValueData *pkvd)
{
	KeyValue_(pkvd);
}

void CFuncTankMortar::Fire(const Vector &barrelEnd, const Vector &forward, entvars_t *pevAttacker)
{
	Fire_(barrelEnd, forward, pevAttacker);
}

void CFuncTankControls::Spawn(void)
{
	Spawn_();
}

int CFuncTankControls::Save(CSave &save)
{
	return Save_(save);
}

int CFuncTankControls::Restore(CRestore &restore)
{
	return Restore_(restore);
}

void CFuncTankControls::Think(void)
{
	Think_();
}

void CFuncTankControls::Use(CBaseEntity *pActivator, CBaseEntity *pCaller, USE_TYPE useType, float value)
{
	Use_(pActivator, pCaller, useType, value);
}

#endif // HOOK_GAMEDLL

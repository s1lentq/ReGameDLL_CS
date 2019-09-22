#include "precompiled.h"

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

Vector CFuncTank::m_TankSpread[] =
{
	Vector(0, 0, 0),             // perfect
	Vector(0.025, 0.025, 0.025), // small cone
	Vector(0.05, 0.05, 0.05),    // medium cone
	Vector(0.1, 0.1, 0.1),       // large cone
	Vector(0.25, 0.25, 0.25),    // extra-large cone
};

constexpr int MAX_FIRING_SPREADS = ARRAYSIZE(CFuncTank::m_TankSpread);

IMPLEMENT_SAVERESTORE(CFuncTank, CBaseEntity)

void CFuncTank::Spawn()
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
		pev->nextthink = pev->ltime + 1.0f;
	}

	// Point at the end of the barrel
	m_sightOrigin = BarrelPosition();

	if (m_fireRate <= 0.0f)
		m_fireRate = 1.0f;

	if (m_spread > MAX_FIRING_SPREADS)
		m_spread = 0;

	pev->oldorigin = pev->origin;
}

void CFuncTank::Precache()
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

void CFuncTank::KeyValue(KeyValueData *pkvd)
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
	{
		CBaseEntity::KeyValue(pkvd);
	}
}

BOOL CFuncTank::OnControls(entvars_t *pevTest)
{
	if (!(pev->spawnflags & SF_TANK_CANCONTROL))
		return FALSE;

	Vector offset = pevTest->origin - pev->origin;
	if ((m_vecControllerUsePos - pevTest->origin).Length() < 30.0f)
	{
		return TRUE;
	}

	return FALSE;
}

BOOL CFuncTank::StartControl(CBasePlayer *pController)
{
	if (m_pController)
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

	if (m_pController->m_pActiveItem)
	{
		m_pController->m_pActiveItem->Holster();
		m_pController->pev->weaponmodel = 0;

#ifdef BUILD_LATEST_FIXES
		m_pController->pev->viewmodel = 0;
#endif

#ifdef REGAMEDLL_FIXES
		m_pController->m_iFOV = DEFAULT_FOV;
#endif
	}

	m_pController->m_iHideHUD |= HIDEHUD_WEAPONS;
	m_vecControllerUsePos = m_pController->pev->origin;

	pev->nextthink = pev->ltime + 0.1f;

	return TRUE;
}

void CFuncTank::StopControl()
{
	// TODO: bring back the controllers current weapon
	if (!m_pController)
		return;

	if (m_pController->m_pActiveItem)
	{
		m_pController->m_pActiveItem->Deploy();

		if (m_pController->IsPlayer())
		{
			m_pController->ResetMaxSpeed();
		}
	}

	ALERT(at_console, "stopped using TANK\n");

#ifdef REGAMEDLL_FIXES
	if (m_pController->m_pActiveItem)
#endif
	{
		m_pController->m_iHideHUD &= ~HIDEHUD_WEAPONS;
	}

	pev->nextthink = 0;
	m_pController = nullptr;

	if (IsActive())
	{
		pev->nextthink = pev->ltime + 1.0f;
	}
}

void CFuncTank::ControllerPostFrame()
{
	assert(m_pController != nullptr);

	if (gpGlobals->time < m_flNextAttack)
		return;

	if (m_pController->pev->button & IN_ATTACK)
	{
		Vector vecForward;
		UTIL_MakeVectorsPrivate(pev->angles, vecForward, nullptr, nullptr);

		m_fireLast = gpGlobals->time - (1.0f / m_fireRate) - 0.01f;
		Fire(BarrelPosition(), vecForward, m_pController->pev);

		if (m_pController && m_pController->IsPlayer())
		{
			m_pController->m_iWeaponVolume = LOUD_GUN_VOLUME;
		}

		m_flNextAttack = gpGlobals->time + (1.0f / m_fireRate);
	}
}

void CFuncTank::Use(CBaseEntity *pActivator, CBaseEntity *pCaller, USE_TYPE useType, float value)
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
			((CBasePlayer *)pActivator)->m_pTank = this;
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

edict_t *CFuncTank::FindTarget(edict_t *pPlayer)
{
	return pPlayer;
}

BOOL CFuncTank::InRange(float range)
{
	if (range < m_minRange)
		return FALSE;

	if (m_maxRange > 0 && range > m_maxRange)
		return FALSE;

	return TRUE;
}

void CFuncTank::Think()
{
	pev->avelocity = g_vecZero;
	TrackTarget();

	if (Q_fabs(real_t(pev->avelocity.x)) > 1 || Q_fabs(real_t(pev->avelocity.y)) > 1)
		StartRotSound();
	else
		StopRotSound();
}

void CFuncTank::TrackTarget()
{
	TraceResult tr;
	edict_t *pPlayer = FIND_CLIENT_IN_PVS(edict());
	bool updateTime = false, lineOfSight = false;
	Vector angles, direction, targetPosition, barrelEnd;
	edict_t *pTarget = nullptr;

	// Get a position to aim for
	if (m_pController)
	{
		// Tanks attempt to mirror the player's angles
		angles = m_pController->pev->v_angle;
		angles.x = 0 - angles.x;
		pev->nextthink = pev->ltime + 0.05f;
	}
	else
	{
		if (IsActive())
			pev->nextthink = pev->ltime + 0.1f;
		else
			return;

		if (FNullEnt(pPlayer))
		{
			if (IsActive())
			{
				// Wait 2 secs
				pev->nextthink = pev->ltime + 2.0f;
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

		// No line of sight, don't track
		if (tr.flFraction == 1.0f || tr.pHit == pTarget)
		{
			lineOfSight = true;

			CBaseEntity *pInstance = CBaseEntity::Instance(pTarget);
			if (InRange(range) && pInstance && pInstance->IsAlive())
			{
				updateTime = true;
				m_sightOrigin = UpdateTargetPosition(pInstance);
			}
		}

		// Track sight origin
		// TODO: I'm not sure what i changed
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
		updateTime = false;
	}
	else if (angles.y < (m_yawCenter - m_yawRange))
	{
		angles.y = (m_yawCenter - m_yawRange);

		// Don't update if you saw the player, but out of range
		updateTime = false;
	}

	if (updateTime)
	{
		m_lastSightTime = gpGlobals->time;
	}

	// Move toward target at rate or less
	real_t distY = UTIL_AngleDistance(angles.y, pev->angles.y);
	pev->avelocity.y = distY * 10.0f;

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
	real_t distX = UTIL_AngleDistance(angles.x, pev->angles.x);
	pev->avelocity.x = distX  * 10.0f;

	if (pev->avelocity.x > m_pitchRate)
	{
		pev->avelocity.x = m_pitchRate;
	}
	else if (pev->avelocity.x < -m_pitchRate)
	{
		pev->avelocity.x = -m_pitchRate;
	}

	if (m_pController)
	{
		return;
	}

	if (CanFire() && ((Q_fabs(distX) < m_pitchTolerance && Q_fabs(distY) < m_yawTolerance) || (pev->spawnflags & SF_TANK_LINEOFSIGHT)))
	{
		bool fire = false;
		Vector forward;
		UTIL_MakeVectorsPrivate(pev->angles, forward, nullptr, nullptr);

		if (pev->spawnflags & SF_TANK_LINEOFSIGHT)
		{
			float length = direction.Length();
			UTIL_TraceLine(barrelEnd, barrelEnd + forward * length, dont_ignore_monsters, edict(), &tr);

			if (tr.pHit == pTarget)
			{
				fire = true;
			}
		}
		else
			fire = true;

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
void CFuncTank::AdjustAnglesForBarrel(Vector &angles, float distance)
{
	real_t r2, d2;

	if (m_barrelPos.y != 0.0f || m_barrelPos.z != 0.0f)
	{
		distance -= m_barrelPos.z;
		d2 = distance * distance;

		if (m_barrelPos.y)
		{
			r2 = m_barrelPos.y * m_barrelPos.y;
			angles.y += (180.0f / M_PI) * atan2(m_barrelPos.y, Q_sqrt(d2 - r2));
		}

		if (m_barrelPos.z)
		{
			r2 = m_barrelPos.z * m_barrelPos.z;
			angles.x += (180.0f / M_PI) * atan2(-m_barrelPos.z, Q_sqrt(d2 - r2));
		}
	}
}

// Fire targets and spawn sprites
void CFuncTank::Fire(const Vector &barrelEnd, const Vector &forward, entvars_t *pevAttacker)
{
	if (m_fireLast != 0.0f)
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
			pSprite->pev->nextthink += 0.1f;
		}

		SUB_UseTargets(this, USE_TOGGLE, 0);
	}

	m_fireLast = gpGlobals->time;
}

void CFuncTank::TankTrace(const Vector &vecStart, const Vector &vecForward, const Vector &vecSpread, TraceResult &tr)
{
	// get circular gaussian spread
	float x, z;
	real_t y;

	do
	{
		x = RANDOM_FLOAT(-0.5, 0.5) + RANDOM_FLOAT(-0.5, 0.5);
		y = RANDOM_FLOAT(-0.5, 0.5) + RANDOM_FLOAT(-0.5, 0.5);
		z = x * x + y * y;
	}
	while (z > 1);

	Vector vecDir = vecForward + x * vecSpread.x * gpGlobals->v_right + y * vecSpread.y * gpGlobals->v_up;
	Vector vecEnd;

	vecEnd = vecStart + vecDir * 4096.0f;
	UTIL_TraceLine(vecStart, vecEnd, dont_ignore_monsters, edict(), &tr);
}

void CFuncTank::StartRotSound()
{
	if (!pev->noise || (pev->spawnflags & SF_TANK_SOUNDON))
	{
		return;
	}

	pev->spawnflags |= SF_TANK_SOUNDON;
	EMIT_SOUND(edict(), CHAN_STATIC, (char *)STRING(pev->noise), 0.85, ATTN_NORM);
}

void CFuncTank::StopRotSound()
{
	if (pev->spawnflags & SF_TANK_SOUNDON)
	{
		STOP_SOUND(edict(), CHAN_STATIC, (char *)STRING(pev->noise));
	}

	pev->spawnflags &= ~SF_TANK_SOUNDON;
}

LINK_ENTITY_TO_CLASS(func_tank, CFuncTankGun, CCSFuncTankGun)

void CFuncTankGun::Fire(const Vector &barrelEnd, const Vector &forward, entvars_t *pevAttacker)
{
	if (m_fireLast != 0.0f)
	{
		// FireBullets needs gpGlobals->v_up, etc.
		UTIL_MakeAimVectors(pev->angles);

		int bulletCount = int((gpGlobals->time - m_fireLast) * m_fireRate);
		if (bulletCount > 0)
		{
			for (int i = 0; i < bulletCount; i++)
			{
				switch (m_bulletType)
				{
				case TANK_BULLET_9MM:
					FireBullets(1, barrelEnd, forward, m_TankSpread[m_spread], 4096, BULLET_MONSTER_9MM, 1, m_iBulletDamage, pevAttacker);
					break;
				case TANK_BULLET_MP5:
					FireBullets(1, barrelEnd, forward, m_TankSpread[m_spread], 4096, BULLET_MONSTER_MP5, 1, m_iBulletDamage, pevAttacker);
					break;
				case TANK_BULLET_12MM:
					FireBullets(1, barrelEnd, forward, m_TankSpread[m_spread], 4096, BULLET_MONSTER_12MM, 1, m_iBulletDamage, pevAttacker);
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
	{
		CFuncTank::Fire(barrelEnd, forward, pevAttacker);
	}
}

TYPEDESCRIPTION CFuncTankLaser::m_SaveData[] =
{
	DEFINE_FIELD(CFuncTankLaser, m_pLaser, FIELD_CLASSPTR),
	DEFINE_FIELD(CFuncTankLaser, m_laserTime, FIELD_TIME),
};

LINK_ENTITY_TO_CLASS(func_tanklaser, CFuncTankLaser, CCSFuncTankLaser)
IMPLEMENT_SAVERESTORE(CFuncTankLaser, CFuncTank)

void CFuncTankLaser::Activate()
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

void CFuncTankLaser::KeyValue(KeyValueData *pkvd)
{
	if (FStrEq(pkvd->szKeyName, "laserentity"))
	{
		pev->message = ALLOC_STRING(pkvd->szValue);
		pkvd->fHandled = TRUE;
	}
	else
	{
		CFuncTank::KeyValue(pkvd);
	}
}

CLaser *CFuncTankLaser::GetLaser()
{
	if (m_pLaser)
	{
		return m_pLaser;
	}

	edict_t *pentLaser = FIND_ENTITY_BY_TARGETNAME(nullptr, STRING(pev->message));

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

void CFuncTankLaser::Think()
{
	if (m_pLaser && gpGlobals->time > m_laserTime)
	{
		m_pLaser->TurnOff();
	}

	CFuncTank::Think();
}

void CFuncTankLaser::Fire(const Vector &barrelEnd, const Vector &forward, entvars_t *pevAttacker)
{
	if (m_fireLast != 0.0f && GetLaser())
	{
		// TankTrace needs gpGlobals->v_up, etc.
		UTIL_MakeAimVectors(pev->angles);

		int bulletCount = int((gpGlobals->time - m_fireLast) * m_fireRate);
		if (bulletCount)
		{
			TraceResult tr;
			for (int i = 0; i < bulletCount; i++)
			{
				m_pLaser->pev->origin = barrelEnd;
				TankTrace(barrelEnd, forward, m_TankSpread[m_spread], tr);

				m_laserTime = gpGlobals->time;
				m_pLaser->TurnOn();
				m_pLaser->pev->dmgtime = gpGlobals->time - 1.0f;
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

LINK_ENTITY_TO_CLASS(func_tankrocket, CFuncTankRocket, CCSFuncTankRocket)

void CFuncTankRocket::Precache()
{
	UTIL_PrecacheOther("rpg_rocket");
	CFuncTank::Precache();
}

void CFuncTankRocket::Fire(const Vector &barrelEnd, const Vector &forward, entvars_t *pevAttacker)
{
	if (m_fireLast != 0.0f)
	{
		int bulletCount = int((gpGlobals->time - m_fireLast) * m_fireRate);
		if (bulletCount > 0)
		{
			for (int i = 0; i < bulletCount; i++)
			{
				CBaseEntity *pRocket = CBaseEntity::Create("rpg_rocket", barrelEnd, pev->angles, edict());
			}

			CFuncTank::Fire(barrelEnd, forward, pev);
		}
	}
	else
	{
		CFuncTank::Fire(barrelEnd, forward, pev);
	}
}

LINK_ENTITY_TO_CLASS(func_tankmortar, CFuncTankMortar, CCSFuncTankMortar)

void CFuncTankMortar::KeyValue(KeyValueData *pkvd)
{
	if (FStrEq(pkvd->szKeyName, "iMagnitude"))
	{
		pev->impulse = Q_atoi(pkvd->szValue);
		pkvd->fHandled = TRUE;
	}
	else
	{
		CFuncTank::KeyValue(pkvd);
	}
}

void CFuncTankMortar::Fire(const Vector &barrelEnd, const Vector &forward, entvars_t *pevAttacker)
{
	if (m_fireLast != 0.0f)
	{
		int bulletCount = int((gpGlobals->time - m_fireLast) * m_fireRate);

		// Only create 1 explosion
		if (bulletCount > 0)
		{
			TraceResult tr;

			// TankTrace needs gpGlobals->v_up, etc.
			UTIL_MakeAimVectors(pev->angles);

			TankTrace(barrelEnd, forward, m_TankSpread[m_spread], tr);
			ExplosionCreate(tr.vecEndPos, pev->angles, edict(), pev->impulse, TRUE);
			CFuncTank::Fire(barrelEnd, forward, pev);
		}
	}
	else
	{
		CFuncTank::Fire(barrelEnd, forward, pev);
	}
}

TYPEDESCRIPTION CFuncTankControls::m_SaveData[] =
{
	DEFINE_FIELD(CFuncTankControls, m_pTank, FIELD_CLASSPTR),
};

LINK_ENTITY_TO_CLASS(func_tankcontrols, CFuncTankControls, CCSFuncTankControls)
IMPLEMENT_SAVERESTORE(CFuncTankControls, CBaseEntity)

void CFuncTankControls::Use(CBaseEntity *pActivator, CBaseEntity *pCaller, USE_TYPE useType, float value)
{
	// pass the Use command onto the controls
	if (m_pTank)
	{
		m_pTank->Use(pActivator, pCaller, useType, value);
	}

	// if this fails,  most likely means save/restore hasn't worked properly
	assert(m_pTank != nullptr);
}

void CFuncTankControls::Think()
{
	edict_t *pTarget = nullptr;

	do
	{
		pTarget = FIND_ENTITY_BY_TARGETNAME(pTarget, STRING(pev->target));
	}
	while (!FNullEnt(pTarget) && Q_strncmp(STRING(pTarget->v.classname), "func_tank", 9) != 0);

	if (FNullEnt(pTarget))
	{
		ALERT(at_console, "No tank %s\n", STRING(pev->target));
		return;
	}

	m_pTank = static_cast<CFuncTank *>(Instance(pTarget));
}

void CFuncTankControls::Spawn()
{
	pev->solid = SOLID_TRIGGER;
	pev->movetype = MOVETYPE_NONE;
	pev->effects |= EF_NODRAW;

	SET_MODEL(ENT(pev), STRING(pev->model));

	UTIL_SetSize(pev, pev->mins, pev->maxs);
	UTIL_SetOrigin(pev, pev->origin);

	// After all the func_tank's have spawned
	pev->nextthink = gpGlobals->time + 0.3f;

	CBaseEntity::Spawn();
}

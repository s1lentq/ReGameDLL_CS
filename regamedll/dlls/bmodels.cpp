#include "precompiled.h"

// Calculates origin of a bmodel from absmin/size because all bmodel origins are 0 0 0
Vector VecBModelOrigin(entvars_t *pevBModel)
{
	return pevBModel->absmin + (pevBModel->size * 0.5f);
}

LINK_ENTITY_TO_CLASS(func_wall, CFuncWall, CCSFuncWall)

void CFuncWall::Spawn()
{
	pev->angles = g_vecZero;

	// so it doesn't get pushed by anything
	pev->movetype = MOVETYPE_PUSH;
	pev->solid = SOLID_BSP;

	SET_MODEL(ENT(pev), STRING(pev->model));

	// If it can't move/go away, it's really part of the world
	pev->flags |= FL_WORLDBRUSH;
}

void CFuncWall::Use(CBaseEntity *pActivator, CBaseEntity *pCaller, USE_TYPE useType, float value)
{
	if (ShouldToggle(useType, int(pev->frame)))
	{
		pev->frame = 1.0 - pev->frame;
	}
}

LINK_ENTITY_TO_CLASS(func_wall_toggle, CFuncWallToggle, CCSFuncWallToggle)

void CFuncWallToggle::Spawn()
{
	CFuncWall::Spawn();

	if (pev->spawnflags & SF_WALL_TOOGLE_START_OFF)
	{
		TurnOff();
	}

#ifdef REGAMEDLL_ADD
	if (pev->spawnflags & SF_WALL_TOOGLE_NOTSOLID)
	{
		pev->solid = SOLID_NOT;
	}
#endif

}

#ifdef REGAMEDLL_FIXES
void CFuncWallToggle::Restart()
{
	CFuncWall::Spawn();

	if (pev->spawnflags & SF_WALL_TOOGLE_START_OFF)
	{
		TurnOff();
		return;
	}

	TurnOn();
}
#endif

void CFuncWallToggle::TurnOff()
{
	pev->solid = SOLID_NOT;
	pev->effects |= EF_NODRAW;
	UTIL_SetOrigin(pev, pev->origin);
}

void CFuncWallToggle::TurnOn()
{
	pev->solid = SOLID_BSP;
	pev->effects &= ~EF_NODRAW;
	UTIL_SetOrigin(pev, pev->origin);
}

BOOL CFuncWallToggle::IsOn()
{
	if (pev->solid == SOLID_NOT)
	{
		return FALSE;
	}

	return TRUE;
}

void CFuncWallToggle::Use(CBaseEntity *pActivator, CBaseEntity *pCaller, USE_TYPE useType, float value)
{
	int status = IsOn();

	if (ShouldToggle(useType, status))
	{
		if (status)
			TurnOff();
		else
			TurnOn();
	}
}

LINK_ENTITY_TO_CLASS(func_conveyor, CFuncConveyor, CCSFuncConveyor)

void CFuncConveyor::Spawn()
{
	SetMovedir(pev);
	CFuncWall::Spawn();

	if (!(pev->spawnflags & SF_CONVEYOR_VISUAL))
	{
		pev->flags |= FL_CONVEYOR;
	}

	// HACKHACK - This is to allow for some special effects
	if (pev->spawnflags & SF_CONVEYOR_NOTSOLID)
	{
		// Don't want the engine thinking we've got special contents on this brush
		pev->solid = SOLID_NOT;
		pev->skin = 0;
	}

	if (pev->speed == 0)
		pev->speed = 100;

	UpdateSpeed(pev->speed);
}

// HACKHACK -- This is ugly, but encode the speed in the rendercolor to avoid adding more data to the network stream
void CFuncConveyor::UpdateSpeed(float speed)
{
	// Encode it as an integer with 4 fractional bits
	int speedCode = int(Q_fabs(real_t(speed)) * 16.0);

	if (speed < 0)
		pev->rendercolor.x = 1;
	else
		pev->rendercolor.x = 0;

	pev->rendercolor.y = (speedCode >> 8);
	pev->rendercolor.z = (speedCode & 0xFF);
}

void CFuncConveyor::Use(CBaseEntity *pActivator, CBaseEntity *pCaller, USE_TYPE useType, float value)
{
	pev->speed = -pev->speed;
	UpdateSpeed(pev->speed);
}

LINK_ENTITY_TO_CLASS(func_illusionary, CFuncIllusionary, CCSFuncIllusionary)

void CFuncIllusionary::KeyValue(KeyValueData *pkvd)
{
	// skin is used for content type
	if (FStrEq(pkvd->szKeyName, "skin"))
	{
		pev->skin = Q_atoi(pkvd->szValue);
		pkvd->fHandled = TRUE;
	}
	else
	{
		CBaseToggle::KeyValue(pkvd);
	}
}

void CFuncIllusionary::Spawn()
{
	pev->angles = g_vecZero;
	pev->movetype = MOVETYPE_NONE;

	// always solid_not
	pev->solid = SOLID_NOT;

	SET_MODEL(ENT(pev), STRING(pev->model));

	// I'd rather eat the network bandwidth of this than figure out how to save/restore
	// these entities after they have been moved to the client, or respawn them ala Quake
	// Perhaps we can do this in deathmatch only.
	// MAKE_STATIC(ENT(pev));
}

LINK_ENTITY_TO_CLASS(func_monsterclip, CFuncMonsterClip, CCSFuncMonsterClip)

void CFuncMonsterClip::Spawn()
{
	CFuncWall::Spawn();

	if (CVAR_GET_FLOAT("showtriggers") == 0)
	{
		pev->effects = EF_NODRAW;
	}

	pev->flags |= FL_MONSTERCLIP;
}

TYPEDESCRIPTION CFuncRotating::m_SaveData[] =
{
	DEFINE_FIELD(CFuncRotating, m_flFanFriction, FIELD_FLOAT),
	DEFINE_FIELD(CFuncRotating, m_flAttenuation, FIELD_FLOAT),
	DEFINE_FIELD(CFuncRotating, m_flVolume, FIELD_FLOAT),
	DEFINE_FIELD(CFuncRotating, m_pitch, FIELD_FLOAT),
	DEFINE_FIELD(CFuncRotating, m_sounds, FIELD_INTEGER)
};

LINK_ENTITY_TO_CLASS(func_rotating, CFuncRotating, CCSFuncRotating)
IMPLEMENT_SAVERESTORE(CFuncRotating, CBaseEntity)

void CFuncRotating::KeyValue(KeyValueData *pkvd)
{
	if (FStrEq(pkvd->szKeyName, "fanfriction"))
	{
		m_flFanFriction = Q_atof(pkvd->szValue) / 100;
		pkvd->fHandled = TRUE;
	}
#ifdef REGAMEDLL_FIXES
	else if (FStrEq(pkvd->szKeyName, "volume"))
#else
	else if (FStrEq(pkvd->szKeyName, "Volume"))
#endif
	{
		m_flVolume = Q_atof(pkvd->szValue) / 10.0;

		if (m_flVolume > 1.0)
			m_flVolume = 1.0;

		if (m_flVolume < 0.0)
			m_flVolume = 0.0;

		pkvd->fHandled = TRUE;
	}
	else if (FStrEq(pkvd->szKeyName, "spawnorigin"))
	{
		Vector tmp;
		UTIL_StringToVector((float *)tmp, pkvd->szValue);

		if (tmp != g_vecZero)
		{
			pev->origin = tmp;
		}
	}
	else if (FStrEq(pkvd->szKeyName, "sounds"))
	{
		m_sounds = Q_atoi(pkvd->szValue);
		pkvd->fHandled = TRUE;
	}
	else
	{
		CBaseEntity::KeyValue(pkvd);
	}
}

// QUAKED func_rotating (0 .5 .8) ? START_ON REVERSE X_AXIS Y_AXIS
// You need to have an origin brush as part of this entity.  The
// center of that brush will be
// the point around which it is rotated. It will rotate around the Z
// axis by default.  You can
// check either the X_AXIS or Y_AXIS box to change that.

// "speed" determines how fast it moves; default value is 100.
// "dmg"	damage to inflict when blocked (2 default)

// REVERSE will cause the it to rotate in the opposite direction.
void CFuncRotating::Spawn()
{
#ifdef REGAMEDLL_FIXES
	m_angles = pev->angles;
#endif

	// set final pitch.  Must not be PITCH_NORM, since we
	// plan on pitch shifting later.
	m_pitch = PITCH_NORM - 1;

	// maintain compatibility with previous maps
	if (m_flVolume == 0.0)
		m_flVolume = 1.0;

	// if the designer didn't set a sound attenuation, default to one.
	m_flAttenuation = ATTN_NORM;

	if (pev->spawnflags & SF_BRUSH_ROTATE_SMALLRADIUS)
	{
		m_flAttenuation = ATTN_IDLE;
	}
	else if (pev->spawnflags & SF_BRUSH_ROTATE_MEDIUMRADIUS)
	{
		m_flAttenuation = ATTN_STATIC;
	}
	else if (pev->spawnflags & SF_BRUSH_ROTATE_LARGERADIUS)
	{
		m_flAttenuation = ATTN_NORM;
	}

	// prevent divide by zero if level designer forgets friction!
	if (m_flFanFriction == 0)
	{
		m_flFanFriction = 1;
	}

	if (pev->spawnflags & SF_BRUSH_ROTATE_Z_AXIS)
	{
		pev->movedir = Vector(0, 0, 1);
	}
	else if (pev->spawnflags & SF_BRUSH_ROTATE_X_AXIS)
	{
		pev->movedir = Vector(1, 0, 0);
	}
	else
	{
		// y-axis
		pev->movedir = Vector(0, 1, 0);
	}

	// check for reverse rotation
	if (pev->spawnflags & SF_BRUSH_ROTATE_BACKWARDS)
	{
		pev->movedir = pev->movedir * -1;
	}

	// some rotating objects like fake volumetric lights will not be solid.
	if (pev->spawnflags & SF_BRUSH_ROTATE_NOT_SOLID)
	{
		pev->solid = SOLID_NOT;
		pev->skin = CONTENTS_EMPTY;
		pev->movetype = MOVETYPE_PUSH;
	}
	else
	{
		pev->solid = SOLID_BSP;
		pev->movetype = MOVETYPE_PUSH;
	}

	UTIL_SetOrigin(pev, pev->origin);
	SET_MODEL(ENT(pev), STRING(pev->model));

	SetUse(&CFuncRotating::RotatingUse);

	// did level designer forget to assign speed?
	if (pev->speed <= 0)
	{
		pev->speed = 0;
	}

	// Removed this per level designers request.  -- JAY
	//	if (pev->dmg == 0)
	//		pev->dmg = 2;

	// instant-use brush?
	if (pev->spawnflags & SF_BRUSH_ROTATE_START_ON)
	{
		SetThink(&CFuncRotating::SUB_CallUseToggle);

		// leave a magic delay for client to start up
		pev->nextthink = pev->ltime + 1.5f;
	}

	// can this brush inflict pain?
	if (pev->spawnflags & SF_BRUSH_HURT)
	{
		SetTouch(&CFuncRotating::HurtTouch);
	}

	Precache();
}

#ifdef REGAMEDLL_FIXES
void CFuncRotating::Restart()
{
	// stop sound, we're done
	EMIT_SOUND_DYN(ENT(pev), CHAN_STATIC, (char *)STRING(pev->noiseRunning), 0, ATTN_NONE, SND_STOP, m_pitch);

	// restore angles
	pev->angles = m_angles;
	pev->avelocity = g_vecZero;

	// some rotating objects like fake volumetric lights will not be solid.
	if (pev->spawnflags & SF_BRUSH_ROTATE_NOT_SOLID)
	{
		pev->solid = SOLID_NOT;
		pev->skin = CONTENTS_EMPTY;
		pev->movetype = MOVETYPE_PUSH;
	}
	else
	{
		pev->solid = SOLID_BSP;
		pev->movetype = MOVETYPE_PUSH;
	}

	UTIL_SetOrigin(pev, pev->origin);
	SET_MODEL(ENT(pev), STRING(pev->model));

	SetUse(&CFuncRotating::RotatingUse);

	// did level designer forget to assign speed?
	if (pev->speed <= 0)
	{
		pev->speed = 0;
	}

	// instant-use brush?
	if (pev->spawnflags & SF_BRUSH_ROTATE_START_ON)
	{
		SetThink(&CFuncRotating::SUB_CallUseToggle);

		// leave a magic delay for client to start up
		pev->nextthink = pev->ltime + 0.1f;
	}

	// can this brush inflict pain?
	if (pev->spawnflags & SF_BRUSH_HURT)
	{
		SetTouch(&CFuncRotating::HurtTouch);
	}
}
#endif

void CFuncRotating::Precache()
{
	char *szSoundFile = (char *)STRING(pev->message);

	// set up fan sounds
	if (!FStringNull(pev->message) && Q_strlen(szSoundFile) > 0)
	{
		// if a path is set for a wave, use it
		PRECACHE_SOUND(szSoundFile);
		pev->noiseRunning = ALLOC_STRING(szSoundFile);
	}
	else
	{
		// otherwise use preset sound
		switch (m_sounds)
		{
		case 1:
			PRECACHE_SOUND("fans/fan1.wav");
			pev->noiseRunning = ALLOC_STRING("fans/fan1.wav");
			break;
		case 2:
			PRECACHE_SOUND("fans/fan2.wav");
			pev->noiseRunning = ALLOC_STRING("fans/fan2.wav");
			break;
		case 3:
			PRECACHE_SOUND("fans/fan3.wav");
			pev->noiseRunning = ALLOC_STRING("fans/fan3.wav");
			break;
		case 4:
			PRECACHE_SOUND("fans/fan4.wav");
			pev->noiseRunning = ALLOC_STRING("fans/fan4.wav");
			break;
		case 5:
			PRECACHE_SOUND("fans/fan5.wav");
			pev->noiseRunning = ALLOC_STRING("fans/fan5.wav");
			break;

		case 0:
		default:
			if (!FStringNull(pev->message) && Q_strlen(szSoundFile) > 0)
			{
				PRECACHE_SOUND(szSoundFile);
				pev->noiseRunning = ALLOC_STRING(szSoundFile);
				break;
			}
			else
			{
				pev->noiseRunning = ALLOC_STRING("common/null.wav");
				break;
			}
		}
	}

	if (pev->avelocity != g_vecZero)
	{
		// if fan was spinning, and we went through transition or save/restore,
		// make sure we restart the sound.  1.5 sec delay is magic number. KDB
		SetThink(&CFuncRotating::SpinUp);
		pev->nextthink = pev->ltime + 1.5f;
	}
}

// Will hurt others based on how fast the brush is spinning
void CFuncRotating::HurtTouch(CBaseEntity *pOther)
{
	entvars_t *pevOther = pOther->pev;

	// we can't hurt this thing, so we're not concerned with it
	if (pevOther->takedamage == DAMAGE_NO)
	{
		return;
	}

	// calculate damage based on rotation speed
	pev->dmg = pev->avelocity.Length() / 10;
	pOther->TakeDamage(pev, pev, pev->dmg, DMG_CRUSH);
	pevOther->velocity = (pevOther->origin - VecBModelOrigin(pev)).Normalize() * pev->dmg;
}

// Ramp pitch and volume up to final values, based on difference
// between how fast we're going vs how fast we plan to go
void CFuncRotating::RampPitchVol(BOOL fUp)
{
	Vector vecAVel = pev->avelocity;
	real_t vecCur;
	real_t vecFinal;
	real_t fpct;
	float fvol;
	float fpitch;
	int pitch;

	// get current angular velocity
#ifdef REGAMEDLL_FIXES
	vecCur = Q_abs(vecAVel.x != 0 ? vecAVel.x : (vecAVel.y != 0 ? vecAVel.y : vecAVel.z));
#else
	vecCur = Q_abs(int(vecAVel.x != 0 ? vecAVel.x : (vecAVel.y != 0 ? vecAVel.y : vecAVel.z)));
#endif

	// get target angular velocity
	vecFinal = (pev->movedir.x != 0 ? pev->movedir.x : (pev->movedir.y != 0 ? pev->movedir.y : pev->movedir.z));
	vecFinal *= pev->speed;
#ifdef REGAMEDLL_FIXES
	vecFinal = Q_abs(vecFinal);
#else
	vecFinal = Q_abs(int(vecFinal));
#endif

	// calc volume and pitch as % of final vol and pitch
	fpct = vecCur / vecFinal;

	//if (fUp)
	//{
	//	// spinup volume ramps up from 50% max vol
	//	fvol = m_flVolume * (0.5 + fpct / 2.0);
	//}
	//else
	{
		// slowdown volume ramps down to 0
		fvol = m_flVolume * fpct;
	}

	fpitch = MIN_FANPITCH + (MAX_FANPITCH - MIN_FANPITCH) * fpct;

	pitch = int(fpitch);
	if (pitch == PITCH_NORM)
	{
		pitch = PITCH_NORM - 1;
	}

	// change the fan's vol and pitch
	EMIT_SOUND_DYN(ENT(pev), CHAN_STATIC, (char *)STRING(pev->noiseRunning), fvol, m_flAttenuation, (SND_CHANGE_PITCH | SND_CHANGE_VOL), pitch);
}

// Accelerates a non-moving func_rotating up to it's speed
void CFuncRotating::SpinUp()
{
	pev->nextthink = pev->ltime + 0.1;
	pev->avelocity = pev->avelocity + (pev->movedir * (pev->speed * m_flFanFriction));

	// cache entity's rotational velocity
	Vector vecAVel = pev->avelocity;

	// if we've met or exceeded target speed, set target speed and stop thinking
#ifdef REGAMEDLL_FIXES
	if (Q_abs(vecAVel.x) >= Q_abs(pev->movedir.x * pev->speed)
		&& Q_abs(vecAVel.y) >= Q_abs(pev->movedir.y * pev->speed)
		&& Q_abs(vecAVel.z) >= Q_abs(pev->movedir.z * pev->speed))
#else
	if (Q_abs(int(vecAVel.x)) >= Q_abs(int(pev->movedir.x * pev->speed))	
		&& Q_abs(int(vecAVel.y)) >= Q_abs(int(pev->movedir.y * pev->speed))
		&& Q_abs(int(vecAVel.z)) >= Q_abs(int(pev->movedir.z * pev->speed)))
#endif
	{
		// set speed in case we overshot
		pev->avelocity = pev->movedir * pev->speed;
		EMIT_SOUND_DYN(ENT(pev), CHAN_STATIC, (char *)STRING(pev->noiseRunning), m_flVolume, m_flAttenuation, (SND_CHANGE_PITCH | SND_CHANGE_VOL), MAX_FANPITCH);

		SetThink(&CFuncRotating::Rotate);
		Rotate();
	}
	else
	{
		RampPitchVol(TRUE);
	}
}

void CFuncRotating::SpinDown()
{
	// rotational velocity
	Vector vecAVel;
	vec_t vecdir;

	pev->nextthink = pev->ltime + 0.1f;

	// spin down slower than spinup
	pev->avelocity = pev->avelocity - (pev->movedir * (pev->speed * m_flFanFriction));

	// cache entity's rotational velocity
	vecAVel = pev->avelocity;

	if (pev->movedir.x != 0)
		vecdir = pev->movedir.x;
	else if (pev->movedir.y != 0)
		vecdir = pev->movedir.y;
	else
		vecdir = pev->movedir.z;

	// if we've met or exceeded target speed, set target speed and stop thinking
	// (note: must check for movedir > 0 or < 0)
	if (((vecdir > 0) && (vecAVel.x <= 0 && vecAVel.y <= 0 && vecAVel.z <= 0))
		|| ((vecdir < 0) && (vecAVel.x >= 0 && vecAVel.y >= 0 && vecAVel.z >= 0)))
	{
		// set speed in case we overshot
		pev->avelocity = g_vecZero;

		// stop sound, we're done
		EMIT_SOUND_DYN(ENT(pev), CHAN_STATIC, (char *)STRING(pev->noiseRunning), 0, ATTN_NONE, SND_STOP, m_pitch);

		SetThink(&CFuncRotating::Rotate);
		Rotate();
	}
	else
	{
		RampPitchVol(FALSE);
	}
}

void CFuncRotating::Rotate()
{
	pev->nextthink = pev->ltime + 10;
}

// When a rotating brush is triggered
void CFuncRotating::RotatingUse(CBaseEntity *pActivator, CBaseEntity *pCaller, USE_TYPE useType, float value)
{
	// is this a brush that should accelerate and decelerate when turned on/off (fan)?
	if (pev->spawnflags & SF_BRUSH_ACCDCC)
	{
		// fan is spinning, so stop it.
		if (pev->avelocity != g_vecZero)
		{
			SetThink(&CFuncRotating::SpinDown);

			//EMIT_SOUND_DYN(ENT(pev), CHAN_WEAPON, (char *)STRING(pev->noiseStop), m_flVolume, m_flAttenuation, 0, m_pitch);
			pev->nextthink = pev->ltime + 0.1f;
		}
		// fan is not moving, so start it
		else
		{
			SetThink(&CFuncRotating::SpinUp);
			EMIT_SOUND_DYN(ENT(pev), CHAN_STATIC, (char *)STRING(pev->noiseRunning), 0.01, m_flAttenuation, 0, MIN_FANPITCH);

			pev->nextthink = pev->ltime + 0.1;
		}
	}
	else if (!(pev->spawnflags & SF_BRUSH_ACCDCC)) // this is a normal start/stop brush.
	{
		if (pev->avelocity != g_vecZero)
		{
			// play stopping sound here
			SetThink(&CFuncRotating::SpinDown);

			// EMIT_SOUND_DYN(ENT(pev), CHAN_WEAPON, (char *)STRING(pev->noiseStop), m_flVolume, m_flAttenuation, 0, m_pitch);

			pev->nextthink = pev->ltime + 0.1f;
			// pev->avelocity = g_vecZero;
		}
		else
		{
			EMIT_SOUND_DYN(ENT(pev), CHAN_STATIC, (char *)STRING(pev->noiseRunning), m_flVolume, m_flAttenuation, 0, MAX_FANPITCH);
			pev->avelocity = pev->movedir * pev->speed;

			SetThink(&CFuncRotating::Rotate);
			Rotate();
		}
	}
}

// An entity has blocked the brush
void CFuncRotating::Blocked(CBaseEntity *pOther)
{
	pOther->TakeDamage(pev, pev, pev->dmg, DMG_CRUSH);
}

TYPEDESCRIPTION CPendulum::m_SaveData[] =
{
	DEFINE_FIELD(CPendulum, m_accel, FIELD_FLOAT),
	DEFINE_FIELD(CPendulum, m_distance, FIELD_FLOAT),
	DEFINE_FIELD(CPendulum, m_time, FIELD_TIME),
	DEFINE_FIELD(CPendulum, m_damp, FIELD_FLOAT),
	DEFINE_FIELD(CPendulum, m_maxSpeed, FIELD_FLOAT),
	DEFINE_FIELD(CPendulum, m_dampSpeed, FIELD_FLOAT),
	DEFINE_FIELD(CPendulum, m_center, FIELD_VECTOR),
	DEFINE_FIELD(CPendulum, m_start, FIELD_VECTOR),
};

LINK_ENTITY_TO_CLASS(func_pendulum, CPendulum, CCSPendulum)
IMPLEMENT_SAVERESTORE(CPendulum, CBaseEntity)

void CPendulum::KeyValue(KeyValueData *pkvd)
{
	if (FStrEq(pkvd->szKeyName, "distance"))
	{
		m_distance = Q_atof(pkvd->szValue);
		pkvd->fHandled = TRUE;
	}
	else if (FStrEq(pkvd->szKeyName, "damp"))
	{
		m_damp = Q_atof(pkvd->szValue) * 0.001;
		pkvd->fHandled = TRUE;
	}
	else
	{
		CBaseEntity::KeyValue(pkvd);
	}
}

void CPendulum::Spawn()
{
	// set the axis of rotation
	CBaseToggle::AxisDir(pev);

	if (pev->spawnflags & SF_PENDULUM_PASSABLE)
		pev->solid = SOLID_NOT;
	else
		pev->solid = SOLID_BSP;

	pev->movetype = MOVETYPE_PUSH;
	UTIL_SetOrigin(pev, pev->origin);
	SET_MODEL(ENT(pev), STRING(pev->model));

	if (m_distance == 0)
		return;

	if (pev->speed == 0)
		pev->speed = 100;

	// Calculate constant acceleration from speed and distance
	m_accel = (pev->speed * pev->speed) / (2 * Q_fabs(real_t(m_distance)));
	m_maxSpeed = pev->speed;
	m_start = pev->angles;
	m_center = pev->angles + (m_distance * 0.5) * pev->movedir;

	// instant-use brush?
	if (pev->spawnflags & SF_PENDULUM_START_ON)
	{
		SetThink(&CPendulum::SUB_CallUseToggle);

		// leave a magic delay for client to start up
		pev->nextthink = gpGlobals->time + 0.1f;
	}

	pev->speed = 0;
	SetUse(&CPendulum::PendulumUse);

	// this brush makes a pendulum a rope swing
	if (pev->spawnflags & SF_PENDULUM_SWING)
	{
		SetTouch(&CPendulum::RopeTouch);
	}
}

void CPendulum::PendulumUse(CBaseEntity *pActivator, CBaseEntity *pCaller, USE_TYPE useType, float value)
{
	// Pendulum is moving, stop it and auto-return if necessary
	if (pev->speed)
	{
		if (pev->spawnflags & SF_PENDULUM_AUTO_RETURN)
		{
			real_t delta;

			delta = CBaseToggle::AxisDelta(pev->spawnflags, pev->angles, m_start);

			pev->avelocity = m_maxSpeed * pev->movedir;
			pev->nextthink = pev->ltime + (delta / m_maxSpeed);
			SetThink(&CPendulum::Stop);
		}
		else
		{
			// Dead stop
			pev->speed = 0;
			SetThink(nullptr);
			pev->avelocity = g_vecZero;
		}
	}
	else
	{
		// Start the pendulum moving
		pev->nextthink = pev->ltime + 0.1f;

		// Save time to calculate dt
		m_time = gpGlobals->time;
		SetThink(&CPendulum::Swing);
		m_dampSpeed = m_maxSpeed;
	}
}

void CPendulum::Stop()
{
	pev->angles = m_start;
	pev->speed = 0;
	SetThink(nullptr);
	pev->avelocity = g_vecZero;
}

void CPendulum::Blocked(CBaseEntity *pOther)
{
	m_time = gpGlobals->time;
}

void CPendulum::Swing()
{
	float delta, dt;

	delta = CBaseToggle::AxisDelta(pev->spawnflags, pev->angles, m_center);

	// How much time has passed?
	dt = gpGlobals->time - m_time;

	// Remember the last time called
	m_time = gpGlobals->time;

	if (delta > 0 && m_accel > 0)
	{
		// Integrate velocity
		pev->speed -= m_accel * dt;
	}
	else
		pev->speed += m_accel * dt;

	if (pev->speed > m_maxSpeed)
		pev->speed = m_maxSpeed;

	else if (pev->speed < -m_maxSpeed)
		pev->speed = -m_maxSpeed;

	// scale the destdelta vector by the time spent traveling to get velocity
	pev->avelocity = pev->speed * pev->movedir;

	// Call this again
	pev->nextthink = pev->ltime + 0.1f;

	if (m_damp)
	{
		m_dampSpeed -= m_damp * m_dampSpeed * dt;

		if (m_dampSpeed < 30.0)
		{
			pev->angles = m_center;
			pev->speed = 0;
			SetThink(nullptr);
			pev->avelocity = g_vecZero;
		}
		else if (pev->speed > m_dampSpeed)
			pev->speed = m_dampSpeed;

		else if (pev->speed < -m_dampSpeed)
			pev->speed = -m_dampSpeed;
	}
}

void CPendulum::Touch(CBaseEntity *pOther)
{
	entvars_t *pevOther = pOther->pev;

	if (pev->dmg <= 0)
		return;

	// we can't hurt this thing, so we're not concerned with it
	if (pevOther->takedamage == DAMAGE_NO)
		return;

	// calculate damage based on rotation speed
	float damage = pev->dmg * pev->speed * 0.01;

	if (damage < 0)
	{
		damage = -damage;
	}

	pOther->TakeDamage(pev, pev, damage, DMG_CRUSH);
	pevOther->velocity = (pevOther->origin - VecBModelOrigin(pev)).Normalize() * damage;
}

void CPendulum::RopeTouch(CBaseEntity *pOther)
{
	entvars_t *pevOther = pOther->pev;

	// not a player!
	if (!pOther->IsPlayer())
	{
		ALERT(at_console, "Not a client\n");
		return;
	}

	// this player already on the rope.
	if (ENT(pevOther) == pev->enemy)
	{
		return;
	}

	pev->enemy = pOther->edict();
	pevOther->velocity = g_vecZero;
	pevOther->movetype = MOVETYPE_NONE;
}

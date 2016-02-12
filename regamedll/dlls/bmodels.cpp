#include "precompiled.h"

/*
* Globals initialization
*/
#ifndef HOOK_GAMEDLL

TYPEDESCRIPTION CFuncRotating::m_SaveData[] =
{
	DEFINE_FIELD(CFuncRotating, m_flFanFriction, FIELD_FLOAT),
	DEFINE_FIELD(CFuncRotating, m_flAttenuation, FIELD_FLOAT),
	DEFINE_FIELD(CFuncRotating, m_flVolume, FIELD_FLOAT),
	DEFINE_FIELD(CFuncRotating, m_pitch, FIELD_FLOAT),
	DEFINE_FIELD(CFuncRotating, m_sounds, FIELD_INTEGER)
};

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

#endif // HOOK_GAMEDLL

// BModelOrigin - calculates origin of a bmodel from absmin/size because all bmodel origins are 0 0 0

/* <1c36f> ../cstrike/dlls/bmodels.cpp:43 */
Vector VecBModelOrigin(entvars_t *pevBModel)
{
	return pevBModel->absmin + (pevBModel->size * 0.5);
}

/* <1e384> ../cstrike/dlls/bmodels.cpp:63 */
LINK_ENTITY_TO_CLASS(func_wall, CFuncWall);

/* <1d193> ../cstrike/dlls/bmodels.cpp:65 */
void CFuncWall::__MAKE_VHOOK(Spawn)()
{
	pev->angles = g_vecZero;

	// so it doesn't get pushed by anything
	pev->movetype = MOVETYPE_PUSH;
	pev->solid = SOLID_BSP;

	SET_MODEL(ENT(pev), STRING(pev->model));

	// If it can't move/go away, it's really part of the world
	pev->flags |= FL_WORLDBRUSH;
}

/* <1d873> ../cstrike/dlls/bmodels.cpp:77 */
void CFuncWall::__MAKE_VHOOK(Use)(CBaseEntity *pActivator, CBaseEntity *pCaller, USE_TYPE useType, float value)
{
	if (ShouldToggle(useType, (int)(pev->frame)))
	{
		pev->frame = 1.0 - pev->frame;
	}
}

/* <1e44e> ../cstrike/dlls/bmodels.cpp:96 */
LINK_ENTITY_TO_CLASS(func_wall_toggle, CFuncWallToggle);

/* <1e28f> ../cstrike/dlls/bmodels.cpp:98 */
void CFuncWallToggle::__MAKE_VHOOK(Spawn)()
{
	CFuncWall::Spawn();

	if (pev->spawnflags & SF_WALL_START_OFF)
	{
		TurnOff();
	}
}

/* <1e518> ../cstrike/dlls/bmodels.cpp:106 */
void CFuncWallToggle::TurnOff()
{
	pev->solid = SOLID_NOT;
	pev->effects |= EF_NODRAW;
	UTIL_SetOrigin(pev, pev->origin);
}

/* <1e53a> ../cstrike/dlls/bmodels.cpp:114 */
void CFuncWallToggle::TurnOn()
{
	pev->solid = SOLID_BSP;
	pev->effects &= ~EF_NODRAW;
	UTIL_SetOrigin(pev, pev->origin);
}

/* <1e55c> ../cstrike/dlls/bmodels.cpp:122 */
BOOL CFuncWallToggle::IsOn()
{
	if (pev->solid == SOLID_NOT)
	{
		return FALSE;
	}

	return TRUE;
}

/* <1e101> ../cstrike/dlls/bmodels.cpp:130 */
void CFuncWallToggle::__MAKE_VHOOK(Use)(CBaseEntity *pActivator, CBaseEntity *pCaller, USE_TYPE useType, float value)
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

/* <1e57d> ../cstrike/dlls/bmodels.cpp:155 */
LINK_ENTITY_TO_CLASS(func_conveyor, CFuncConveyor);

/* <1e1c3> ../cstrike/dlls/bmodels.cpp:156 */
void CFuncConveyor::__MAKE_VHOOK(Spawn)()
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

/* <1e647> ../cstrike/dlls/bmodels.cpp:179 */
void CFuncConveyor::UpdateSpeed(float speed)
{
	// Encode it as an integer with 4 fractional bits
	int speedCode = (int)(fabs((float_precision)speed) * 16.0);

	if (speed < 0)
		pev->rendercolor.x = 1;
	else
		pev->rendercolor.x = 0;

	pev->rendercolor.y = (speedCode >> 8);
	pev->rendercolor.z = (speedCode & 0xFF);
}

/* <1e021> ../cstrike/dlls/bmodels.cpp:194 */
void CFuncConveyor::__MAKE_VHOOK(Use)(CBaseEntity *pActivator, CBaseEntity *pCaller, USE_TYPE useType, float value)
{
	pev->speed = -pev->speed;
	UpdateSpeed(pev->speed);
}

/* <1e695> ../cstrike/dlls/bmodels.cpp:217 */
LINK_ENTITY_TO_CLASS(func_illusionary, CFuncIllusionary);

/* <1ddc9> ../cstrike/dlls/bmodels.cpp:219 */
void CFuncIllusionary::__MAKE_VHOOK(KeyValue)(KeyValueData *pkvd)
{
	//skin is used for content type
	if (FStrEq(pkvd->szKeyName, "skin"))
	{
		pev->skin = (int)Q_atof(pkvd->szValue);
		pkvd->fHandled = TRUE;
	}
	else
		CBaseToggle::KeyValue(pkvd);
}

/* <1d1db> ../cstrike/dlls/bmodels.cpp:230 */
void CFuncIllusionary::__MAKE_VHOOK(Spawn)()
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

/* <1e75f> ../cstrike/dlls/bmodels.cpp:262 */
LINK_ENTITY_TO_CLASS(func_monsterclip, CFuncMonsterClip);

/* <1e24f> ../cstrike/dlls/bmodels.cpp:264 */
void CFuncMonsterClip::__MAKE_VHOOK(Spawn)()
{
	CFuncWall::Spawn();

	if (CVAR_GET_FLOAT("showtriggers") == 0)
	{
		pev->effects = EF_NODRAW;
	}

	pev->flags |= FL_MONSTERCLIP;
}

/* <1e82c> ../cstrike/dlls/bmodels.cpp:313 */
LINK_ENTITY_TO_CLASS(func_rotating, CFuncRotating);

/* <1d826> ../cstrike/dlls/bmodels.cpp:310 */
IMPLEMENT_SAVERESTORE(CFuncRotating, CBaseEntity);

/* <1dc21> ../cstrike/dlls/bmodels.cpp:315 */
void CFuncRotating::__MAKE_VHOOK(KeyValue)(KeyValueData *pkvd)
{
	if (FStrEq(pkvd->szKeyName, "fanfriction"))
	{
		m_flFanFriction = Q_atof(pkvd->szValue) / 100;
		pkvd->fHandled = TRUE;
	}
	else if (FStrEq(pkvd->szKeyName, "Volume"))
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
		CBaseEntity::KeyValue(pkvd);
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

/* <1d5c4> ../cstrike/dlls/bmodels.cpp:362 */
void CFuncRotating::__MAKE_VHOOK(Spawn)()
{
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
	if (pev->spawnflags & SF_ROTATING_NOT_SOLID)
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
	if (pev->spawnflags & SF_BRUSH_ROTATE_INSTANT)
	{
		SetThink(&CFuncRotating::SUB_CallUseToggle);

		// leave a magic delay for client to start up
		pev->nextthink = pev->ltime + 1.5;
	}

	// can this brush inflict pain?
	if (pev->spawnflags & SF_BRUSH_HURT)
	{
		SetTouch(&CFuncRotating::HurtTouch);
	}

	Precache();
}

/* <1d28a> ../cstrike/dlls/bmodels.cpp:447 */
void CFuncRotating::__MAKE_VHOOK(Precache)()
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
		pev->nextthink = pev->ltime + 1.5;
	}
}

// Touch - will hurt others based on how fast the brush is spinning

/* <1dea4> ../cstrike/dlls/bmodels.cpp:517 */
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

// RampPitchVol - ramp pitch and volume up to final values, based on difference
// between how fast we're going vs how fast we plan to go

/* <1e8f9> ../cstrike/dlls/bmodels.cpp:540 */
void CFuncRotating::RampPitchVol(int fUp)
{
	Vector vecAVel = pev->avelocity;
	float_precision vecCur;
	float_precision vecFinal;
	float_precision fpct;
	float fvol;
	float fpitch;
	int pitch;

	// get current angular velocity
	vecCur = abs((int)(vecAVel.x != 0 ? vecAVel.x : (vecAVel.y != 0 ? vecAVel.y : vecAVel.z)));

	// get target angular velocity
	vecFinal = (pev->movedir.x != 0 ? pev->movedir.x : (pev->movedir.y != 0 ? pev->movedir.y : pev->movedir.z));
	vecFinal *= pev->speed;
	vecFinal = abs((int)vecFinal);

	// calc volume and pitch as % of final vol and pitch
	fpct = vecCur / vecFinal;

	//if (fUp)
	//{
	//	// spinup volume ramps up from 50% max vol
	//	fvol = m_flVolume * (0.5 + fpct/2.0);
	//}
	//else
	{
		// slowdown volume ramps down to 0
		fvol = m_flVolume * fpct;
	}

	fpitch = FANPITCHMIN + (FANPITCHMAX - FANPITCHMIN) * fpct;

	pitch = (int)fpitch;
	if (pitch == PITCH_NORM)
	{
		pitch = PITCH_NORM - 1;
	}

	// change the fan's vol and pitch
	EMIT_SOUND_DYN(ENT(pev), CHAN_STATIC, (char *)STRING(pev->noiseRunning), fvol, m_flAttenuation, (SND_CHANGE_PITCH | SND_CHANGE_VOL), pitch);
}

// SpinUp - accelerates a non-moving func_rotating up to it's speed

/* <1ea74> ../cstrike/dlls/bmodels.cpp:585 */
void CFuncRotating::SpinUp()
{
	//rotational velocity
	Vector vecAVel;

	pev->nextthink = pev->ltime + 0.1;
	pev->avelocity = pev->avelocity + (pev->movedir * (pev->speed * m_flFanFriction));

	// cache entity's rotational velocity
	vecAVel = pev->avelocity;

	// if we've met or exceeded target speed, set target speed and stop thinking
	if (abs((int)vecAVel.x) >= abs((int)(pev->movedir.x * pev->speed))
		&& abs((int)vecAVel.y) >= abs((int)(pev->movedir.y * pev->speed))
		&& abs((int)vecAVel.z) >= abs((int)(pev->movedir.z * pev->speed)))
	{
		// set speed in case we overshot
		pev->avelocity = pev->movedir * pev->speed;
		EMIT_SOUND_DYN(ENT(pev), CHAN_STATIC, (char *)STRING(pev->noiseRunning), m_flVolume, m_flAttenuation, (SND_CHANGE_PITCH | SND_CHANGE_VOL), FANPITCHMAX);

		SetThink(&CFuncRotating::Rotate);
		Rotate();
	}
	else
	{
		RampPitchVol(TRUE);
	}
}

/* <1e9c3> ../cstrike/dlls/bmodels.cpp:615 */
void CFuncRotating::SpinDown()
{
	//rotational velocity
	Vector vecAVel;
	vec_t vecdir;

	pev->nextthink = pev->ltime + 0.1;

	//spin down slower than spinup
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

/* <1d304> ../cstrike/dlls/bmodels.cpp:653 */
void CFuncRotating::Rotate()
{
	pev->nextthink = pev->ltime + 10;
}

// Rotating Use - when a rotating brush is triggered

/* <1d60e> ../cstrike/dlls/bmodels.cpp:661 */
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
			pev->nextthink = pev->ltime + 0.1;
		}
		else // fan is not moving, so start it
		{
			SetThink(&CFuncRotating::SpinUp);
			EMIT_SOUND_DYN(ENT(pev), CHAN_STATIC, (char *)STRING(pev->noiseRunning), 0.01, m_flAttenuation, 0, FANPITCHMIN);

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

			pev->nextthink = pev->ltime + 0.1;
			// pev->avelocity = g_vecZero;
		}
		else
		{
			EMIT_SOUND_DYN(ENT(pev), CHAN_STATIC, (char *)STRING(pev->noiseRunning), m_flVolume, m_flAttenuation, 0, FANPITCHMAX);
			pev->avelocity = pev->movedir * pev->speed;

			SetThink(&CFuncRotating::Rotate);
			Rotate();
		}
	}
}

// RotatingBlocked - An entity has blocked the brush

/* <1d325> ../cstrike/dlls/bmodels.cpp:706 */
void CFuncRotating::__MAKE_VHOOK(Blocked)(CBaseEntity *pOther)
{
	pOther->TakeDamage(pev, pev, pev->dmg, DMG_CRUSH);
}

/* <1eb14> ../cstrike/dlls/bmodels.cpp:747 */
LINK_ENTITY_TO_CLASS(func_pendulum, CPendulum);

/* <1d7d9> ../cstrike/dlls/bmodels.cpp:761 */
IMPLEMENT_SAVERESTORE(CPendulum, CBaseEntity);

/* <1db2a> ../cstrike/dlls/bmodels.cpp:765 */
void CPendulum::__MAKE_VHOOK(KeyValue)(KeyValueData *pkvd)
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
		CBaseEntity::KeyValue(pkvd);
}

/* <1d9c7> ../cstrike/dlls/bmodels.cpp:782 */
void CPendulum::__MAKE_VHOOK(Spawn)()
{
	// set the axis of rotation
	CBaseToggle::AxisDir(pev);

	if (pev->spawnflags & SF_DOOR_PASSABLE)
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
	m_accel = (pev->speed * pev->speed) / (2 * fabs((float_precision)m_distance));
	m_maxSpeed = pev->speed;
	m_start = pev->angles;
	m_center = pev->angles + (m_distance * 0.5) * pev->movedir;

	if (pev->spawnflags & SF_BRUSH_ROTATE_INSTANT)
	{
		SetThink(&CPendulum::SUB_CallUseToggle);
		pev->nextthink = gpGlobals->time + 0.1f;
	}

	pev->speed = 0;
	SetUse(&CPendulum::PendulumUse);

	if (pev->spawnflags & SF_PENDULUM_SWING)
	{
		SetTouch (&CPendulum::RopeTouch);
	}
}

/* <1d8ec> ../cstrike/dlls/bmodels.cpp:821 */
void CPendulum::PendulumUse(CBaseEntity *pActivator, CBaseEntity *pCaller, USE_TYPE useType, float value)
{
	// Pendulum is moving, stop it and auto-return if necessary
	if (pev->speed)
	{
		if (pev->spawnflags & SF_PENDULUM_AUTO_RETURN)
		{
			float_precision delta;

			delta = CBaseToggle::AxisDelta(pev->spawnflags, pev->angles, m_start);

			pev->avelocity = m_maxSpeed * pev->movedir;
			pev->nextthink = pev->ltime + (delta / m_maxSpeed);
			SetThink(&CPendulum::Stop);
		}
		else
		{
			// Dead stop
			pev->speed = 0;
			SetThink(NULL);
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

/* <1d381> ../cstrike/dlls/bmodels.cpp:852 */
void CPendulum::Stop()
{
	pev->angles = m_start;
	pev->speed = 0;
	SetThink(NULL);
	pev->avelocity = g_vecZero;
}

/* <1d3a7> ../cstrike/dlls/bmodels.cpp:861 */
void CPendulum::__MAKE_VHOOK(Blocked)(CBaseEntity *pOther)
{
	m_time = gpGlobals->time;
}

/* <1d533> ../cstrike/dlls/bmodels.cpp:867 */
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
	pev->nextthink = pev->ltime + 0.1;

	if (m_damp)
	{
		m_dampSpeed -= m_damp * m_dampSpeed * dt;

		if (m_dampSpeed < 30.0)
		{
			pev->angles = m_center;
			pev->speed = 0;
			SetThink(NULL);
			pev->avelocity = g_vecZero;
		}
		else if (pev->speed > m_dampSpeed)
			pev->speed = m_dampSpeed;

		else if (pev->speed < -m_dampSpeed)
			pev->speed = -m_dampSpeed;
	}
}

/* <1d3f5> ../cstrike/dlls/bmodels.cpp:909 */
void CPendulum::__MAKE_VHOOK(Touch)(CBaseEntity *pOther)
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

/* <1da85> ../cstrike/dlls/bmodels.cpp:931 */
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

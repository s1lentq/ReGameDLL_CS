/*
*
*   This program is free software; you can redistribute it and/or modify it
*   under the terms of the GNU General Public License as published by the
*   Free Software Foundation; either version 2 of the License, or (at
*   your option) any later version.
*
*   This program is distributed in the hope that it will be useful, but
*   WITHOUT ANY WARRANTY; without even the implied warranty of
*   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
*   General Public License for more details.
*
*   You should have received a copy of the GNU General Public License
*   along with this program; if not, write to the Free Software Foundation,
*   Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
*
*   In addition, as a special exception, the author gives permission to
*   link the code of this program with the Half-Life Game Engine ("HL
*   Engine") and Modified Game Libraries ("MODs") developed by Valve,
*   L.L.C ("Valve").  You must obey the GNU General Public License in all
*   respects for all of the code used other than the HL Engine and MODs
*   from Valve.  If you modify this file, you may extend this exception
*   to your version of the file, but you are not obligated to do so.  If
*   you do not wish to do so, delete this exception statement from your
*   version.
*
*/

#ifndef BMODELS_H
#define BMODELS_H
#ifdef _WIN32
#pragma once
#endif

#define SF_PENDULUM_SWING	2		// spawnflag that makes a pendulum a rope swing.

#define SF_BRUSH_ACCDCC		16		// brush should accelerate and decelerate when toggled
#define SF_BRUSH_HURT		32		// rotating brush that inflicts pain based on rotation speed
#define SF_ROTATING_NOT_SOLID	64		// some special rotating objects are not solid.

#define SF_WALL_START_OFF	0x0001

#define SF_CONVEYOR_VISUAL	0x0001
#define SF_CONVEYOR_NOTSOLID	0x0002

#define SF_WORLD_DARK		0x0001		// Fade from black at startup
#define SF_WORLD_TITLE		0x0002		// Display game title at startup
#define SF_WORLD_FORCETEAM	0x0004		// Force teams

#define FANPITCHMIN		30
#define FANPITCHMAX		100

// covering cheesy noise1, noise2, & noise3 fields so they make more sense (for rotating fans)
#define noiseStart		noise1
#define noiseStop		noise2
#define noiseRunning		noise3

// This is just a solid wall if not inhibited
class CFuncWall: public CBaseEntity
{
public:
	virtual void Spawn();

	// Bmodels don't go across transitions
	virtual int ObjectCaps() { return CBaseEntity::ObjectCaps() & ~FCAP_ACROSS_TRANSITION; }
	virtual void Use(CBaseEntity *pActivator, CBaseEntity *pCaller, USE_TYPE useType, float value);

#ifdef HOOK_GAMEDLL

	void Spawn_();
	void Use_(CBaseEntity *pActivator, CBaseEntity *pCaller, USE_TYPE useType, float value);

#endif

};

class CFuncWallToggle: public CFuncWall
{
public:
	virtual void Spawn();
	virtual void Use(CBaseEntity *pActivator, CBaseEntity *pCaller, USE_TYPE useType, float value);

#ifdef HOOK_GAMEDLL

	void Spawn_();
	void Use_(CBaseEntity *pActivator, CBaseEntity *pCaller, USE_TYPE useType, float value);

#endif

public:
	void TurnOff();
	void TurnOn();
	BOOL IsOn();
};

class CFuncConveyor: public CFuncWall
{
public:
	virtual void Spawn();
	virtual void Use(CBaseEntity *pActivator, CBaseEntity *pCaller, USE_TYPE useType, float value);

#ifdef HOOK_GAMEDLL

	void Spawn_();
	void Use_(CBaseEntity *pActivator, CBaseEntity *pCaller, USE_TYPE useType, float value);

#endif

public:
	void UpdateSpeed(float speed);
};

// A simple entity that looks solid but lets you walk through it.
class CFuncIllusionary: public CBaseToggle
{
public:
	virtual void Spawn();
	virtual void KeyValue(KeyValueData *pkvd);
	virtual int ObjectCaps() { return CBaseEntity::ObjectCaps() & ~FCAP_ACROSS_TRANSITION; }

#ifdef HOOK_GAMEDLL

	void Spawn_();
	void KeyValue_(KeyValueData *pkvd);

#endif

public:
	void EXPORT SloshTouch(CBaseEntity *pOther);
};

// Monster only clip brush
//
// This brush will be solid for any entity who has the FL_MONSTERCLIP flag set
// in pev->flags
//
// otherwise it will be invisible and not solid.  This can be used to keep
// specific monsters out of certain areas
class CFuncMonsterClip: public CFuncWall
{
public:
	virtual void Spawn();

	// Clear out func_wall's use function
	virtual void Use(CBaseEntity *pActivator, CBaseEntity *pCaller, USE_TYPE useType, float value) {}

#ifdef HOOK_GAMEDLL

	void Spawn_();
	void Use_(CBaseEntity *pActivator, CBaseEntity *pCaller, USE_TYPE useType, float value);

#endif

};

class CFuncRotating: public CBaseEntity
{
public:
	// basic functions
	virtual void Spawn();
	virtual void Precache();
	virtual void KeyValue(KeyValueData *pkvd);
	virtual int Save(CSave &save);
	virtual int Restore(CRestore &restore);
	virtual int ObjectCaps() { return (CBaseEntity::ObjectCaps() & ~FCAP_ACROSS_TRANSITION) | FCAP_MUST_RESET; }
	virtual void Blocked(CBaseEntity *pOther);

#ifdef REGAMEDLL_FIXES
	virtual void Restart();
#endif

#ifdef HOOK_GAMEDLL

	void Spawn_();
	void Precache_();
	void KeyValue_(KeyValueData *pkvd);
	int Save_(CSave &save);
	int Restore_(CRestore &restore);
	void Blocked_(CBaseEntity *pOther);

#endif

public:
	void EXPORT SpinUp();
	void EXPORT SpinDown();
	void EXPORT HurtTouch(CBaseEntity *pOther);
	void EXPORT RotatingUse(CBaseEntity *pActivator, CBaseEntity *pCaller, USE_TYPE useType, float value);
	void EXPORT Rotate();
	void RampPitchVol(int fUp);

public:
	static TYPEDESCRIPTION IMPL(m_SaveData)[5];

	float m_flFanFriction;
	float m_flAttenuation;
	float m_flVolume;
	float m_pitch;
	int m_sounds;

#ifdef REGAMEDLL_FIXES
	Vector m_angles;
#endif

};

class CPendulum: public CBaseEntity
{
public:
	virtual void Spawn();
	virtual void KeyValue(KeyValueData *pkvd);
	virtual int Save(CSave &save);
	virtual int Restore(CRestore &restore);
	virtual int ObjectCaps() { return CBaseEntity::ObjectCaps() & ~FCAP_ACROSS_TRANSITION; }
	virtual void Touch(CBaseEntity *pOther);
	virtual void Blocked(CBaseEntity *pOther);

#ifdef HOOK_GAMEDLL

	void Spawn_();
	void KeyValue_(KeyValueData *pkvd);
	int Save_(CSave &save);
	int Restore_(CRestore &restore);
	void Touch_(CBaseEntity *pOther);
	void Blocked_(CBaseEntity *pOther);

#endif

public:
	void EXPORT Swing();
	void EXPORT PendulumUse(CBaseEntity *pActivator, CBaseEntity *pCaller, USE_TYPE useType, float value);
	void EXPORT Stop();

	// this touch func makes the pendulum a rope
	void EXPORT RopeTouch(CBaseEntity *pOther);

public:
	static TYPEDESCRIPTION IMPL(m_SaveData)[8];

	float m_accel;		// Acceleration
	float m_distance;
	float m_time;
	float m_damp;
	float m_maxSpeed;
	float m_dampSpeed;

	Vector m_center;
	Vector m_start;
};

Vector VecBModelOrigin(entvars_t *pevBModel);

#endif // BMODELS_H

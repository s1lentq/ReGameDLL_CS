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

/* <1c494> ../cstrike/dlls/bmodels.cpp:53 */
class CFuncWall: public CBaseEntity
{
public:
	virtual void Spawn(void);

	// Bmodels don't go across transitions
	virtual int ObjectCaps(void)
	{
		return CBaseEntity::ObjectCaps() & ~FCAP_ACROSS_TRANSITION;
	}
	virtual void Use(CBaseEntity *pActivator, CBaseEntity *pCaller, USE_TYPE useType, float value);

#ifdef HOOK_GAMEDLL

	void Spawn_(void);
	void Use_(CBaseEntity *pActivator, CBaseEntity *pCaller, USE_TYPE useType, float value);

#endif // HOOK_GAMEDLL

};/* size: 152, cachelines: 3, members: 1 */

/* <1c4e1> ../cstrike/dlls/bmodels.cpp:86 */
class CFuncWallToggle: public CFuncWall
{
public:
	virtual void Spawn(void);
	virtual void Use(CBaseEntity *pActivator, CBaseEntity *pCaller, USE_TYPE useType, float value);

#ifdef HOOK_GAMEDLL

	void Spawn_(void);
	void Use_(CBaseEntity *pActivator, CBaseEntity *pCaller, USE_TYPE useType, float value);

#endif // HOOK_GAMEDLL

public:
	void TurnOff(void);
	void TurnOn(void);
	BOOL IsOn(void);

};/* size: 152, cachelines: 3, members: 1 */

/* <1c52e> ../cstrike/dlls/bmodels.cpp:147 */
class CFuncConveyor: public CFuncWall
{
public:
	virtual void Spawn(void);
	virtual void Use(CBaseEntity *pActivator, CBaseEntity *pCaller, USE_TYPE useType, float value);

#ifdef HOOK_GAMEDLL

	void Spawn_(void);
	void Use_(CBaseEntity *pActivator, CBaseEntity *pCaller, USE_TYPE useType, float value);

#endif // HOOK_GAMEDLL

public:
	void UpdateSpeed(float speed);

};/* size: 152, cachelines: 3, members: 1 */

// A simple entity that looks solid but lets you walk through it.

/* <1c65b> ../cstrike/dlls/bmodels.cpp:208 */
class CFuncIllusionary: public CBaseToggle
{
public:
	virtual void Spawn(void);
	virtual void KeyValue(KeyValueData *pkvd);
	virtual int ObjectCaps(void)
	{
		return CBaseEntity::ObjectCaps() & ~FCAP_ACROSS_TRANSITION;
	}

#ifdef HOOK_GAMEDLL

	void Spawn_(void);
	void KeyValue_(KeyValueData *pkvd);

#endif // HOOK_GAMEDLL

public:
	void EXPORT SloshTouch(CBaseEntity *pOther);

};/* size: 312, cachelines: 5, members: 1 */

// Monster only clip brush
//
// This brush will be solid for any entity who has the FL_MONSTERCLIP flag set
// in pev->flags
//
// otherwise it will be invisible and not solid.  This can be used to keep
// specific monsters out of certain areas

/* <1c6a8> ../cstrike/dlls/bmodels.cpp:255 */
class CFuncMonsterClip: public CFuncWall
{
public:
	virtual void Spawn(void);

	// Clear out func_wall's use function
	virtual void Use(CBaseEntity *pActivator, CBaseEntity *pCaller, USE_TYPE useType, float value)
	{
		;
	}

#ifdef HOOK_GAMEDLL

	void Spawn_(void);
	void Use_(CBaseEntity *pActivator, CBaseEntity *pCaller, USE_TYPE useType, float value);

#endif // HOOK_GAMEDLL

};/* size: 152, cachelines: 3, members: 1 */

/* <1c6fa> ../cstrike/dlls/bmodels.cpp:274 */
class CFuncRotating: public CBaseEntity
{
public:
	// basic functions
	virtual void Spawn(void);
	virtual void Precache(void);
	virtual void KeyValue(KeyValueData *pkvd);
	virtual int Save(CSave &save);
	virtual int Restore(CRestore &restore);
	virtual int ObjectCaps(void)
	{
		return CBaseEntity::ObjectCaps() & ~FCAP_ACROSS_TRANSITION;
	}
	virtual void Blocked(CBaseEntity *pOther);

#ifdef HOOK_GAMEDLL

	void Spawn_(void);
	void Precache_(void);
	void KeyValue_(KeyValueData *pkvd);
	int Save_(CSave &save);
	int Restore_(CRestore &restore);
	void Blocked_(CBaseEntity *pOther);

#endif // HOOK_GAMEDLL

public:
	void EXPORT SpinUp(void);
	void EXPORT SpinDown(void);
	void EXPORT HurtTouch(CBaseEntity *pOther);
	void EXPORT RotatingUse(CBaseEntity *pActivator, CBaseEntity *pCaller, USE_TYPE useType, float value);
	void EXPORT Rotate(void);
	void RampPitchVol(int fUp);

public:
	static TYPEDESCRIPTION IMPL(m_SaveData)[5];

public:
	float m_flFanFriction;
	float m_flAttenuation;
	float m_flVolume;
	float m_pitch;
	int m_sounds;

};/* size: 172, cachelines: 3, members: 7 */

/* <1c748> ../cstrike/dlls/bmodels.cpp:720 */
class CPendulum: public CBaseEntity
{
public:
	virtual void Spawn(void);
	virtual void KeyValue(KeyValueData *pkvd);
	virtual int Save(CSave &save);
	virtual int Restore(CRestore &restore);
	virtual int ObjectCaps(void)
	{
		return CBaseEntity::ObjectCaps() & ~FCAP_ACROSS_TRANSITION;
	}
	virtual void Touch(CBaseEntity *pOther);
	virtual void Blocked(CBaseEntity *pOther);

#ifdef HOOK_GAMEDLL

	void Spawn_(void);
	void KeyValue_(KeyValueData *pkvd);
	int Save_(CSave &save);
	int Restore_(CRestore &restore);
	void Touch_(CBaseEntity *pOther);
	void Blocked_(CBaseEntity *pOther);

#endif // HOOK_GAMEDLL

public:
	void EXPORT Swing(void);
	void EXPORT PendulumUse(CBaseEntity *pActivator, CBaseEntity *pCaller, USE_TYPE useType, float value);
	void EXPORT Stop(void);

	// this touch func makes the pendulum a rope
	void EXPORT RopeTouch(CBaseEntity *pOther);

	static TYPEDESCRIPTION IMPL(m_SaveData)[8];

public:
	float m_accel;		// Acceleration
	float m_distance;
	float m_time;
	float m_damp;
	float m_maxSpeed;
	float m_dampSpeed;

	Vector m_center;
	Vector m_start;

};/* size: 200, cachelines: 4, members: 10 */

Vector VecBModelOrigin(entvars_t *pevBModel);

#ifdef HOOK_GAMEDLL

// linked objects
C_DLLEXPORT void func_wall(entvars_t *pev);
C_DLLEXPORT void func_wall_toggle(entvars_t *pev);
C_DLLEXPORT void func_conveyor(entvars_t *pev);
C_DLLEXPORT void func_illusionary(entvars_t *pev);
C_DLLEXPORT void func_monsterclip(entvars_t *pev);
C_DLLEXPORT void func_rotating(entvars_t *pev);
C_DLLEXPORT void func_pendulum(entvars_t *pev);

#endif // HOOK_GAMEDLL

#endif // BMODELS_H

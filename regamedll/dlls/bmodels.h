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

#define SF_PENDULUM_SWING	2
#define SF_BRUSH_ACCDCC		16
#define SF_BRUSH_HURT		32
#define SF_ROTATING_NOT_SOLID	64

#define SF_WALL_START_OFF	0x0001

#define SF_CONVEYOR_VISUAL	0x0001
#define SF_CONVEYOR_NOTSOLID	0x0002

#define FANPITCHMIN		30
#define FANPITCHMAX		100

#define noiseStart		noise1
#define noiseStop		noise2
#define noiseRunning		noise3

/* <1c494> ../cstrike/dlls/bmodels.cpp:53 */
class CFuncWall: public CBaseEntity
{
public:
	NOBODY virtual void Spawn(void);
	NOBODY virtual int ObjectCaps(void)
	{
		return ObjectCaps_();
	}
	NOBODY virtual void Use(CBaseEntity *pActivator, CBaseEntity *pCaller, USE_TYPE useType, float value);

#ifdef HOOK_GAMEDLL

	void Spawn_(void);
	int ObjectCaps_(void)
	{
		return CBaseEntity::ObjectCaps() & ~FCAP_ACROSS_TRANSITION;
	}
	void Use_(CBaseEntity *pActivator, CBaseEntity *pCaller, USE_TYPE useType, float value);

#endif // HOOK_GAMEDLL

};/* size: 152, cachelines: 3, members: 1 */

/* <1c4e1> ../cstrike/dlls/bmodels.cpp:86 */
class CFuncWallToggle: public CFuncWall
{
public:
	NOBODY virtual void Spawn(void);
	NOBODY virtual void Use(CBaseEntity *pActivator, CBaseEntity *pCaller, USE_TYPE useType, float value);

#ifdef HOOK_GAMEDLL

	void Spawn_(void);
	void Use_(CBaseEntity *pActivator, CBaseEntity *pCaller, USE_TYPE useType, float value);

#endif // HOOK_GAMEDLL

public:
	NOBODY void TurnOff(void);
	NOBODY void TurnOn(void);
	NOBODY BOOL IsOn(void);

};/* size: 152, cachelines: 3, members: 1 */

/* <1c52e> ../cstrike/dlls/bmodels.cpp:147 */
class CFuncConveyor: public CFuncWall
{
public:
	NOBODY virtual void Spawn(void);
	NOBODY virtual void Use(CBaseEntity *pActivator, CBaseEntity *pCaller, USE_TYPE useType, float value);

#ifdef HOOK_GAMEDLL

	void Spawn_(void);
	void Use_(CBaseEntity *pActivator, CBaseEntity *pCaller, USE_TYPE useType, float value);

#endif // HOOK_GAMEDLL

public:
	NOBODY void UpdateSpeed(float speed);

};/* size: 152, cachelines: 3, members: 1 */

/* <1c65b> ../cstrike/dlls/bmodels.cpp:208 */
class CFuncIllusionary: public CBaseToggle
{
public:
	NOBODY virtual void Spawn(void);
	NOBODY virtual void KeyValue(KeyValueData *pkvd);
	NOBODY virtual int ObjectCaps(void)
	{
		return ObjectCaps_();
	}

#ifdef HOOK_GAMEDLL

	void Spawn_(void);
	void KeyValue_(KeyValueData *pkvd);
	int ObjectCaps_(void)
	{
		return CBaseEntity::ObjectCaps() & ~FCAP_ACROSS_TRANSITION;
	}

#endif // HOOK_GAMEDLL

public:
	NOBODY void EXPORT SloshTouch(CBaseEntity *pOther);

};/* size: 312, cachelines: 5, members: 1 */

/* <1c6a8> ../cstrike/dlls/bmodels.cpp:255 */
class CFuncMonsterClip: public CFuncWall
{
public:
	NOBODY virtual void Spawn(void);
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
	NOBODY virtual void Spawn(void);
	NOBODY virtual void Precache(void);
	NOBODY virtual void KeyValue(KeyValueData *pkvd);
	NOBODY virtual int Save(CSave &save);
	NOBODY virtual int Restore(CRestore &restore);
	NOBODY virtual int ObjectCaps(void)
	{
		return ObjectCaps_();
	}
	NOBODY virtual void Blocked(CBaseEntity *pOther);

#ifdef HOOK_GAMEDLL

	void Spawn_(void);
	void Precache_(void);
	void KeyValue_(KeyValueData *pkvd);
	int Save_(CSave &save);
	int Restore_(CRestore &restore);
	int ObjectCaps_(void)
	{
		return CBaseEntity::ObjectCaps() & ~FCAP_ACROSS_TRANSITION;
	}
	void Blocked_(CBaseEntity *pOther);

#endif // HOOK_GAMEDLL

public:
	NOBODY void EXPORT SpinUp(void);
	NOBODY void EXPORT SpinDown(void);
	NOBODY void EXPORT HurtTouch(CBaseEntity *pOther);
	NOBODY void EXPORT RotatingUse(CBaseEntity *pActivator, CBaseEntity *pCaller, USE_TYPE useType, float value);
	NOBODY void EXPORT Rotate(void);
	NOBODY void RampPitchVol(int fUp);
public:

#ifndef HOOK_GAMEDLL
	static TYPEDESCRIPTION m_SaveData[5];
#else
	static TYPEDESCRIPTION (*m_SaveData)[5];
#endif // HOOK_GAMEDLL

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
	NOBODY virtual void Spawn(void);
	NOBODY virtual void KeyValue(KeyValueData *pkvd);
	NOBODY virtual int Save(CSave &save);
	NOBODY virtual int Restore(CRestore &restore);
	NOBODY virtual int ObjectCaps(void)
	{
		return ObjectCaps_();
	}
	NOBODY virtual void Touch(CBaseEntity *pOther);
	NOBODY virtual void Blocked(CBaseEntity *pOther);

#ifdef HOOK_GAMEDLL

	void Spawn_(void);
	void KeyValue_(KeyValueData *pkvd);
	int Save_(CSave &save);
	int Restore_(CRestore &restore);
	int ObjectCaps_(void)
	{
		return CBaseEntity::ObjectCaps() & ~FCAP_ACROSS_TRANSITION;
	}
	void Touch_(CBaseEntity *pOther);
	void Blocked_(CBaseEntity *pOther);

#endif // HOOK_GAMEDLL

public:
	NOBODY void EXPORT Swing(void);
	NOBODY void EXPORT PendulumUse(CBaseEntity *pActivator, CBaseEntity *pCaller, USE_TYPE useType, float value);
	NOBODY void EXPORT Stop(void);
	NOBODY void EXPORT RopeTouch(CBaseEntity *pOther);

#ifndef HOOK_GAMEDLL
	static TYPEDESCRIPTION m_SaveData[8];
#else
	static TYPEDESCRIPTION (*m_SaveData)[8];
#endif // HOOK_GAMEDLL

public:
	float m_accel;
	float m_distance;
	float m_time;
	float m_damp;
	float m_maxSpeed;
	float m_dampSpeed;
	Vector m_center;
	Vector m_start;

};/* size: 200, cachelines: 4, members: 10 */

NOBODY Vector VecBModelOrigin(entvars_t *pevBModel);

#endif // BMODELS_H

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
#pragma once

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

// This is just a solid wall if not inhibited
class CFuncWall: public CBaseEntity {
public:
	virtual void Spawn() = 0;

	// Bmodels don't go across transitions
	virtual int ObjectCaps() = 0;
	virtual void Use(CBaseEntity *pActivator, CBaseEntity *pCaller, USE_TYPE useType, float value) = 0;
};

class CFuncWallToggle: public CFuncWall {
public:
	virtual void Spawn() = 0;
	virtual void Use(CBaseEntity *pActivator, CBaseEntity *pCaller, USE_TYPE useType, float value) = 0;
};

class CFuncConveyor: public CFuncWall {
public:
	virtual void Spawn() = 0;
	virtual void Use(CBaseEntity *pActivator, CBaseEntity *pCaller, USE_TYPE useType, float value) = 0;
};

// A simple entity that looks solid but lets you walk through it.
class CFuncIllusionary: public CBaseToggle {
public:
	virtual void Spawn() = 0;
	virtual void KeyValue(KeyValueData *pkvd) = 0;
	virtual int ObjectCaps() = 0;
};

// Monster only clip brush
//
// This brush will be solid for any entity who has the FL_MONSTERCLIP flag set
// in pev->flags
//
// otherwise it will be invisible and not solid.  This can be used to keep
// specific monsters out of certain areas
class CFuncMonsterClip: public CFuncWall {
public:
	virtual void Spawn() = 0;

	// Clear out func_wall's use function
	virtual void Use(CBaseEntity *pActivator, CBaseEntity *pCaller, USE_TYPE useType, float value) = 0;
};

class CFuncRotating: public CBaseEntity {
public:
	// basic functions
	virtual void Spawn() = 0;
	virtual void Precache() = 0;
	virtual void KeyValue(KeyValueData *pkvd) = 0;
	virtual int Save(CSave &save) = 0;
	virtual int Restore(CRestore &restore) = 0;
	virtual int ObjectCaps() = 0;
	virtual void Blocked(CBaseEntity *pOther) = 0;
public:

	float m_flFanFriction;
	float m_flAttenuation;
	float m_flVolume;
	float m_pitch;
	int m_sounds;
};

class CPendulum: public CBaseEntity {
public:
	virtual void Spawn() = 0;
	virtual void KeyValue(KeyValueData *pkvd) = 0;
	virtual int Save(CSave &save) = 0;
	virtual int Restore(CRestore &restore) = 0;
	virtual int ObjectCaps() = 0;
	virtual void Touch(CBaseEntity *pOther) = 0;
	virtual void Blocked(CBaseEntity *pOther) = 0;
public:
	float m_accel;		// Acceleration
	float m_distance;
	float m_time;
	float m_damp;
	float m_maxSpeed;
	float m_dampSpeed;

	Vector m_center;
	Vector m_start;
};

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

#ifndef FUNC_TANK_H
#define FUNC_TANK_H
#ifdef _WIN32
#pragma once
#endif

#define SF_TANK_ACTIVE			0x0001
#define SF_TANK_PLAYER			0x0002
#define SF_TANK_HUMANS			0x0004
#define SF_TANK_ALIENS			0x0008
#define SF_TANK_LINEOFSIGHT		0x0010
#define SF_TANK_CANCONTROL		0x0020
#define SF_TANK_SOUNDON			0x8000

enum TANKBULLET
{
	TANK_BULLET_NONE = 0,	// Custom damage
	TANK_BULLET_9MM,	// env_laser (duration is 0.5 rate of fire)
	TANK_BULLET_MP5,	// rockets
	TANK_BULLET_12MM,	// explosion?
};

/* <8c75e> ../cstrike/dlls/func_tank.cpp:46 */
class CFuncTank: public CBaseEntity
{
public:
	virtual void Spawn(void);
	virtual void Precache(void);
	virtual void KeyValue(KeyValueData *pkvd);
	virtual int Save(CSave &save);
	virtual int Restore(CRestore &restore);

	// Bmodels don't go across transitions
	virtual int ObjectCaps(void)
	{
		return CBaseEntity::ObjectCaps() & ~FCAP_ACROSS_TRANSITION;
	}
	virtual BOOL OnControls(entvars_t *pevTest);
	virtual void Think(void);
	virtual void Use(CBaseEntity *pActivator, CBaseEntity *pCaller, USE_TYPE useType, float value);
	virtual void Fire(const Vector &barrelEnd, const Vector &forward, entvars_t *pevAttacker);
	virtual Vector UpdateTargetPosition(CBaseEntity *pTarget)
	{
		return pTarget->BodyTarget(pev->origin);
	}

#ifdef HOOK_GAMEDLL

	void Spawn_(void);
	void Precache_(void);
	void KeyValue_(KeyValueData *pkvd);
	int Save_(CSave &save);
	int Restore_(CRestore &restore);
	BOOL OnControls_(entvars_t *pevTest);
	void Think_(void);
	void Use_(CBaseEntity *pActivator, CBaseEntity *pCaller, USE_TYPE useType, float value);
	void Fire_(const Vector &barrelEnd, const Vector &forward, entvars_t *pevAttacker);

#endif // HOOK_GAMEDLL

public:
	void TrackTarget(void);
	void StartRotSound(void);
	void StopRotSound(void);

	BOOL IsActive(void)
	{
		return (pev->spawnflags & SF_TANK_ACTIVE) == SF_TANK_ACTIVE;
	}
	void TankActivate(void)
	{
		pev->spawnflags |= SF_TANK_ACTIVE;
		pev->nextthink = pev->ltime + 0.1f;
		m_fireLast = 0.0f;
	}
	void TankDeactivate(void)
	{
		pev->spawnflags &= ~SF_TANK_ACTIVE;
		m_fireLast = 0.0f;
		StopRotSound();
	}
	BOOL CanFire(void)
	{
		return (gpGlobals->time - m_lastSightTime) < m_persist;
	}

	BOOL InRange(float range);

	// Acquire a target.  pPlayer is a player in the PVS
	edict_t *FindTarget(edict_t *pPlayer);
	void TankTrace(const Vector &vecStart, const Vector &vecForward, const Vector &vecSpread, TraceResult &tr);

	Vector BarrelPosition(void)
	{
		Vector forward, right, up;
		UTIL_MakeVectorsPrivate(pev->angles, forward, right, up);
		return pev->origin + (forward * m_barrelPos.x) + (right * m_barrelPos.y) + (up * m_barrelPos.z);
	}

	void AdjustAnglesForBarrel(Vector &angles, float distance);
	BOOL StartControl(CBasePlayer *pController);
	void StopControl(void);
	void ControllerPostFrame(void);

public:
	static TYPEDESCRIPTION IMPL(m_SaveData)[26];

protected:
	CBasePlayer *m_pController;
	float m_flNextAttack;
	Vector m_vecControllerUsePos;

	float m_yawCenter;		// "Center" yaw
	float m_yawRate;		// Max turn rate to track targets
	float m_yawRange;		// Range of turning motion (one-sided: 30 is +/- 30 degress from center)
					// Zero is full rotation

	float m_yawTolerance;		// Tolerance angle

	float m_pitchCenter;		// "Center" pitch
	float m_pitchRate;		// Max turn rate on pitch
	float m_pitchRange;		// Range of pitch motion as above
	float m_pitchTolerance;		// Tolerance angle

	float m_fireLast;		// Last time I fired
	float m_fireRate;		// How many rounds/second
	float m_lastSightTime;		// Last time I saw target
	float m_persist;		// Persistence of firing (how long do I shoot when I can't see)
	float m_minRange;		// Minimum range to aim/track
	float m_maxRange;		// Max range to aim/track

	Vector m_barrelPos;		// Length of the freakin barrel
	float m_spriteScale;		// Scale of any sprites we shoot
	int m_iszSpriteSmoke;
	int m_iszSpriteFlash;
	TANKBULLET m_bulletType;	// Bullet type
	int m_iBulletDamage;		// 0 means use Bullet type's default damage

	Vector m_sightOrigin;		// Last sight of target
	int m_spread;			// firing spread
	int m_iszMaster;		// Master entity (game_team_master or multisource)

};/* size: 280, cachelines: 5, members: 28 */

/* <8c79a> ../cstrike/dlls/func_tank.cpp:719 */
class CFuncTankGun: public CFuncTank
{
public:
	virtual void Fire(const Vector &barrelEnd, const Vector &forward, entvars_t *pevAttacker);

#ifdef HOOK_GAMEDLL

	void Fire_(const Vector &barrelEnd, const Vector &forward, entvars_t *pevAttacker);

#endif // HOOK_GAMEDLL

};/* size: 280, cachelines: 5, members: 1 */

/* <8c7e8> ../cstrike/dlls/func_tank.cpp:768 */
class CFuncTankLaser: public CFuncTank
{
public:
	virtual void KeyValue(KeyValueData *pkvd);
	virtual int Save(CSave &save);
	virtual int Restore(CRestore &restore);
	virtual void Activate(void);
	virtual void Think(void);
	virtual void Fire(const Vector &barrelEnd, const Vector &forward, entvars_t *pevAttacker);

#ifdef HOOK_GAMEDLL

	void KeyValue_(KeyValueData *pkvd);
	int Save_(CSave &save);
	int Restore_(CRestore &restore);
	void Activate_(void);
	void Think_(void);
	void Fire_(const Vector &barrelEnd, const Vector &forward, entvars_t *pevAttacker);

#endif // HOOK_GAMEDLL

	CLaser *GetLaser(void);

public:
	static TYPEDESCRIPTION IMPL(m_SaveData)[2];

private:
	CLaser *m_pLaser;
	float m_laserTime;

};/* size: 288, cachelines: 5, members: 4 */

/* <8c836> ../cstrike/dlls/func_tank.cpp:887 */
class CFuncTankRocket: public CFuncTank
{
public:
	virtual void Precache(void);
	virtual void Fire(const Vector &barrelEnd, const Vector &forward, entvars_t *pevAttacker);

#ifdef HOOK_GAMEDLL

	void Precache_(void);
	void Fire_(const Vector &barrelEnd, const Vector &forward, entvars_t *pevAttacker);

#endif // HOOK_GAMEDLL

};/* size: 280, cachelines: 5, members: 1 */

/* <8c884> ../cstrike/dlls/func_tank.cpp:924 */
class CFuncTankMortar: public CFuncTank
{
public:
	virtual void KeyValue(KeyValueData *pkvd);
	virtual void Fire(const Vector &barrelEnd, const Vector &forward, entvars_t *pevAttacker);

#ifdef HOOK_GAMEDLL

	void KeyValue_(KeyValueData *pkvd);
	void Fire_(const Vector &barrelEnd, const Vector &forward, entvars_t *pevAttacker);

#endif // HOOK_GAMEDLL

};/* size: 280, cachelines: 5, members: 1 */

/* <8c8d2> ../cstrike/dlls/func_tank.cpp:974 */
class CFuncTankControls: public CBaseEntity
{
public:
	virtual void Spawn(void);
	virtual int Save(CSave &save);
	virtual int Restore(CRestore &restore);
	virtual int ObjectCaps(void)
	{
		return (CBaseEntity::ObjectCaps() & ~FCAP_ACROSS_TRANSITION) | FCAP_IMPULSE_USE;
	}
	virtual void Think(void);
	virtual void Use(CBaseEntity *pActivator, CBaseEntity *pCaller, USE_TYPE useType, float value);

#ifdef HOOK_GAMEDLL

	void Spawn_(void);
	int Save_(CSave &save);
	int Restore_(CRestore &restore);
	void Think_(void);
	void Use_(CBaseEntity *pActivator, CBaseEntity *pCaller, USE_TYPE useType, float value);

#endif // HOOK_GAMEDLL

public:
	static TYPEDESCRIPTION IMPL(m_SaveData)[1];

public:
	CFuncTank *m_pTank;

};/* size: 156, cachelines: 3, members: 3 */

#ifdef HOOK_GAMEDLL

#define gTankSpread (*pgTankSpread)
extern Vector gTankSpread[5];

#endif // HOOK_GAMEDLL

#ifdef HOOK_GAMEDLL

// linked objects
C_DLLEXPORT void func_tank(entvars_t *pev);
C_DLLEXPORT void func_tanklaser(entvars_t *pev);
C_DLLEXPORT void func_tankrocket(entvars_t *pev);
C_DLLEXPORT void func_tankmortar(entvars_t *pev);
C_DLLEXPORT void func_tankcontrols(entvars_t *pev);

#endif // HOOK_GAMEDLL

#endif // FUNC_TANK_H

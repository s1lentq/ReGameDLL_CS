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
	TANK_BULLET_NONE = 0,
	TANK_BULLET_9MM,
	TANK_BULLET_MP5,
	TANK_BULLET_12MM,
};

/* <8c75e> ../cstrike/dlls/func_tank.cpp:46 */
class CFuncTank: public CBaseEntity
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
	NOBODY virtual BOOL OnControls(entvars_t *pevTest);
	NOBODY virtual void Think(void);
	NOBODY virtual void Use(CBaseEntity *pActivator, CBaseEntity *pCaller, USE_TYPE useType, float value);
	NOBODY virtual void Fire(const Vector &barrelEnd, const Vector &forward, entvars_t *pevAttacker);
	NOBODY virtual Vector UpdateTargetPosition(CBaseEntity *pTarget)
	{
		return UpdateTargetPosition_(pTarget);
	}
	
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
	BOOL OnControls_(entvars_t *pevTest);
	void Think_(void);
	void Use_(CBaseEntity *pActivator, CBaseEntity *pCaller, USE_TYPE useType, float value);
	void Fire_(const Vector &barrelEnd, const Vector &forward, entvars_t *pevAttacker);
	Vector UpdateTargetPosition_(CBaseEntity *pTarget)
	{
		return pTarget->BodyTarget(pev->origin);
	}

#endif // HOOK_GAMEDLL

public:
	NOBODY void TrackTarget(void);
	NOBODY void StartRotSound(void);
	NOBODY void StopRotSound(void);

	inline BOOL IsActive(void)
	{
		return (pev->spawnflags & SF_TANK_ACTIVE) == SF_TANK_ACTIVE;
	}
	inline void TankActivate(void)
	{
		pev->spawnflags |= SF_TANK_ACTIVE;
		pev->nextthink = pev->ltime + 0.1f;
		m_fireLast = 0.0f;
	}
	inline void TankDeactivate(void)
	{
		pev->spawnflags &= ~SF_TANK_ACTIVE;
		m_fireLast = 0.0f;
		StopRotSound();
	}
	inline BOOL CanFire(void)
	{
		return (gpGlobals->time - m_lastSightTime) < m_persist;
	}

	NOBODY BOOL InRange(float range);
	NOBODY edict_t *FindTarget(edict_t *pPlayer);
	NOBODY void TankTrace(const Vector &vecStart, const Vector &vecForward, const Vector &vecSpread, TraceResult &tr);

	Vector BarrelPosition(void)
	{
		Vector forward, right, up;
		UTIL_MakeVectorsPrivate(pev->angles, forward, right, up);
		return pev->origin + (forward * m_barrelPos.x) + (right * m_barrelPos.y) + (up * m_barrelPos.z);
	}

	NOBODY void AdjustAnglesForBarrel(Vector &angles, float distance);
	NOBODY BOOL StartControl(CBasePlayer *pController);
	NOBODY void StopControl(void);
	NOBODY void ControllerPostFrame(void);

public:
#ifndef HOOK_GAMEDLL
	static TYPEDESCRIPTION m_SaveData[26];
#else // HOOK_GAMEDLL
	static TYPEDESCRIPTION (*m_SaveData)[26];
#endif // HOOK_GAMEDLL

protected:
	CBasePlayer *m_pController;
	float m_flNextAttack;
	Vector m_vecControllerUsePos;
	float m_yawCenter;
	float m_yawRate;
	float m_yawRange;
	float m_yawTolerance;
	float m_pitchCenter;
	float m_pitchRate;
	float m_pitchRange;
	float m_pitchTolerance;
	float m_fireLast;
	float m_fireRate;
	float m_lastSightTime;
	float m_persist;
	float m_minRange;
	float m_maxRange;
	Vector m_barrelPos;
	float m_spriteScale;
	int m_iszSpriteSmoke;
	int m_iszSpriteFlash;
	TANKBULLET m_bulletType;
	int m_iBulletDamage;
	Vector m_sightOrigin;
	int m_spread;
	int m_iszMaster;

};/* size: 280, cachelines: 5, members: 28 */

/* <8c79a> ../cstrike/dlls/func_tank.cpp:719 */
class CFuncTankGun: public CFuncTank
{
public:
	NOBODY virtual void Fire(const Vector &barrelEnd, const Vector &forward, entvars_t *pevAttacker);

#ifdef HOOK_GAMEDLL
	void Fire_(const Vector &barrelEnd, const Vector &forward, entvars_t *pevAttacker);
#endif // HOOK_GAMEDLL

};/* size: 280, cachelines: 5, members: 1 */

/* <8c7e8> ../cstrike/dlls/func_tank.cpp:768 */
class CFuncTankLaser: public CFuncTank
{
public:
	NOBODY virtual void KeyValue(KeyValueData *pkvd);
	NOBODY virtual int Save(CSave &save);
	NOBODY virtual int Restore(CRestore &restore);
	NOBODY virtual void Activate(void);
	NOBODY virtual void Think(void);
	NOBODY virtual void Fire(const Vector &barrelEnd, const Vector &forward, entvars_t *pevAttacker);
	
#ifdef HOOK_GAMEDLL

	void KeyValue_(KeyValueData *pkvd);
	int Save_(CSave &save);
	int Restore_(CRestore &restore);
	void Activate_(void);
	void Think_(void);
	void Fire_(const Vector &barrelEnd, const Vector &forward, entvars_t *pevAttacker);

#endif // HOOK_GAMEDLL

	NOBODY CLaser *GetLaser(void);

public:

#ifndef HOOK_GAMEDLL
	static TYPEDESCRIPTION m_SaveData[2];
#else // HOOK_GAMEDLL
	static TYPEDESCRIPTION (*m_SaveData)[2];
#endif // HOOK_GAMEDLL

private:
	CLaser *m_pLaser;
	float m_laserTime;

};/* size: 288, cachelines: 5, members: 4 */

/* <8c836> ../cstrike/dlls/func_tank.cpp:887 */
class CFuncTankRocket: public CFuncTank
{
public:
	NOBODY virtual void Precache(void);
	NOBODY virtual void Fire(const Vector &barrelEnd, const Vector &forward, entvars_t *pevAttacker);

#ifdef HOOK_GAMEDLL

	void Precache_(void);
	void Fire_(const Vector &barrelEnd, const Vector &forward, entvars_t *pevAttacker);

#endif // HOOK_GAMEDLL

};/* size: 280, cachelines: 5, members: 1 */

/* <8c884> ../cstrike/dlls/func_tank.cpp:924 */
class CFuncTankMortar: public CFuncTank
{
public:
	NOBODY virtual void KeyValue(KeyValueData *pkvd);
	NOBODY virtual void Fire(const Vector &barrelEnd, const Vector &forward, entvars_t *pevAttacker);

#ifdef HOOK_GAMEDLL

	void KeyValue_(KeyValueData *pkvd);
	void Fire_(const Vector &barrelEnd, const Vector &forward, entvars_t *pevAttacker);

#endif // HOOK_GAMEDLL

};/* size: 280, cachelines: 5, members: 1 */

/* <8c8d2> ../cstrike/dlls/func_tank.cpp:974 */
class CFuncTankControls: public CBaseEntity
{
public:
	NOBODY virtual void Spawn(void);
	NOBODY virtual int Save(CSave &save);
	NOBODY virtual int Restore(CRestore &restore);
	NOBODY virtual int ObjectCaps(void);
	NOBODY virtual void Think(void);
	NOBODY virtual void Use(CBaseEntity *pActivator, CBaseEntity *pCaller, USE_TYPE useType, float value);
	
#ifdef HOOK_GAMEDLL

	void Spawn_(void);
	int Save_(CSave &save);
	int Restore_(CRestore &restore);
	int ObjectCaps_(void);
	void Think_(void);
	void Use_(CBaseEntity *pActivator, CBaseEntity *pCaller, USE_TYPE useType, float value);

#endif // HOOK_GAMEDLL

public:
#ifndef HOOK_GAMEDLL
	static TYPEDESCRIPTION m_SaveData[1];
#else // HOOK_GAMEDLL
	static TYPEDESCRIPTION (*m_SaveData)[1];
#endif // HOOK_GAMEDLL

public:
	CFuncTank *m_pTank;

};/* size: 156, cachelines: 3, members: 3 */

#endif // FUNC_TANK_H

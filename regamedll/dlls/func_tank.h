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

enum TANKBULLET
{
	TANK_BULLET_NONE = 0,	// Custom damage
	TANK_BULLET_9MM,		// env_laser (duration is 0.5 rate of fire)
	TANK_BULLET_MP5,		// rockets
	TANK_BULLET_12MM,		// explosion?
};

#define SF_TANK_ACTIVE      BIT(0)
#define SF_TANK_PLAYER      BIT(1)
#define SF_TANK_HUMANS      BIT(2)
#define SF_TANK_ALIENS      BIT(3)
#define SF_TANK_LINEOFSIGHT BIT(4)
#define SF_TANK_CANCONTROL  BIT(5)

#define SF_TANK_SOUNDON     BIT(15)

class CFuncTank: public CBaseEntity
{
public:
	virtual void Spawn();
	virtual void Precache();
	virtual void KeyValue(KeyValueData *pkvd);
	virtual int Save(CSave &save);
	virtual int Restore(CRestore &restore);

	// Bmodels don't go across transitions
	virtual int ObjectCaps() { return CBaseEntity::ObjectCaps() & ~FCAP_ACROSS_TRANSITION; }
	virtual BOOL OnControls(entvars_t *pevTest);
	virtual void Think();
	virtual void Use(CBaseEntity *pActivator, CBaseEntity *pCaller, USE_TYPE useType, float value);
	virtual void Fire(const Vector &barrelEnd, const Vector &forward, entvars_t *pevAttacker);
	virtual Vector UpdateTargetPosition(CBaseEntity *pTarget) { return pTarget->BodyTarget(pev->origin); }

public:
	void TrackTarget();
	void StartRotSound();
	void StopRotSound();

	BOOL IsActive() const { return (pev->spawnflags & SF_TANK_ACTIVE) == SF_TANK_ACTIVE; }
	void TankActivate()
	{
		pev->spawnflags |= SF_TANK_ACTIVE;
		pev->nextthink = pev->ltime + 0.1f;
		m_fireLast = 0.0f;
	}
	void TankDeactivate()
	{
		pev->spawnflags &= ~SF_TANK_ACTIVE;
		m_fireLast = 0.0f;
		StopRotSound();
	}

	BOOL CanFire() const { return (gpGlobals->time - m_lastSightTime) < m_persist; }
	BOOL InRange(float range);

	// Acquire a target.  pPlayer is a player in the PVS
	edict_t *FindTarget(edict_t *pPlayer);
	void TankTrace(const Vector &vecStart, const Vector &vecForward, const Vector &vecSpread, TraceResult &tr);

	Vector BarrelPosition()
	{
		Vector forward, right, up;
		UTIL_MakeVectorsPrivate(pev->angles, forward, right, up);
		return pev->origin + (forward * m_barrelPos.x) + (right * m_barrelPos.y) + (up * m_barrelPos.z);
	}

	void AdjustAnglesForBarrel(Vector &angles, float distance);
	BOOL StartControl(CBasePlayer *pController);
	void StopControl();
	void ControllerPostFrame();

public:
	static TYPEDESCRIPTION m_SaveData[];
	static Vector m_TankSpread[];

protected:
	CBasePlayer *m_pController;
	float m_flNextAttack;
	Vector m_vecControllerUsePos;

	float m_yawCenter;		// "Center" yaw
	float m_yawRate;		// Max turn rate to track targets
	float m_yawRange;		// Range of turning motion (one-sided: 30 is +/- 30 degress from center)
							// Zero is full rotation

	float m_yawTolerance;	// Tolerance angle

	float m_pitchCenter;	// "Center" pitch
	float m_pitchRate;		// Max turn rate on pitch
	float m_pitchRange;		// Range of pitch motion as above
	float m_pitchTolerance;	// Tolerance angle

	float m_fireLast;		// Last time I fired
	float m_fireRate;		// How many rounds/second
	float m_lastSightTime;	// Last time I saw target
	float m_persist;		// Persistence of firing (how long do I shoot when I can't see)
	float m_minRange;		// Minimum range to aim/track
	float m_maxRange;		// Max range to aim/track

	Vector m_barrelPos;		// Length of the freakin barrel
	float m_spriteScale;	// Scale of any sprites we shoot
	int m_iszSpriteSmoke;
	int m_iszSpriteFlash;
	TANKBULLET m_bulletType;// Bullet type
	int m_iBulletDamage;	// 0 means use Bullet type's default damage

	Vector m_sightOrigin;	// Last sight of target
	int m_spread;			// firing spread
	int m_iszMaster;		// Master entity (game_team_master or multisource)
};

class CFuncTankGun: public CFuncTank
{
public:
	virtual void Fire(const Vector &barrelEnd, const Vector &forward, entvars_t *pevAttacker);
};

class CFuncTankLaser: public CFuncTank
{
public:
	virtual void KeyValue(KeyValueData *pkvd);
	virtual int Save(CSave &save);
	virtual int Restore(CRestore &restore);
	virtual void Activate();
	virtual void Think();
	virtual void Fire(const Vector &barrelEnd, const Vector &forward, entvars_t *pevAttacker);

	CLaser *GetLaser();

public:
	static TYPEDESCRIPTION m_SaveData[];

private:
	CLaser *m_pLaser;
	float m_laserTime;
};

class CFuncTankRocket: public CFuncTank
{
public:
	virtual void Precache();
	virtual void Fire(const Vector &barrelEnd, const Vector &forward, entvars_t *pevAttacker);
};

class CFuncTankMortar: public CFuncTank
{
public:
	virtual void KeyValue(KeyValueData *pkvd);
	virtual void Fire(const Vector &barrelEnd, const Vector &forward, entvars_t *pevAttacker);
};

class CFuncTankControls: public CBaseEntity
{
public:
	virtual void Spawn();
	virtual int Save(CSave &save);
	virtual int Restore(CRestore &restore);
	virtual int ObjectCaps() { return (CBaseEntity::ObjectCaps() & ~FCAP_ACROSS_TRANSITION) | FCAP_IMPULSE_USE; }
	virtual void Think();
	virtual void Use(CBaseEntity *pActivator, CBaseEntity *pCaller, USE_TYPE useType, float value);

public:
	static TYPEDESCRIPTION m_SaveData[];
	CFuncTank *m_pTank;
};

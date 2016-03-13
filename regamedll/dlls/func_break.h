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

#ifndef FUNC_BREAK_H
#define FUNC_BREAK_H
#ifdef _WIN32
#pragma once
#endif

// this many shards spawned when breakable objects break;
#define NUM_SHARDS 6

// func breakable
#define SF_BREAK_TRIGGER_ONLY		1	// may only be broken by trigger
#define SF_BREAK_TOUCH			2	// can be 'crashed through' by running player (plate glass)
#define SF_BREAK_PRESSURE		4	// can be broken by a player standing on it
#define SF_BREAK_CROWBAR		256	// instant break if hit with crowbar

// func_pushable (it's also func_breakable, so don't collide with those flags)
#define SF_PUSH_BREAKABLE		128

typedef enum
{
	expRandom = 0,
	expDirected,

} Explosions;

typedef enum
{
	matGlass = 0,
	matWood,
	matMetal,
	matFlesh,
	matCinderBlock,
	matCeilingTile,
	matComputer,
	matUnbreakableGlass,
	matRocks,
	matNone,
	matLastMaterial,

} Materials;

class CBreakable: public CBaseDelay
{
public:
	CBreakable();
	// basic functions
	virtual void Spawn();
	virtual void Precache();
	virtual void Restart();
	virtual void KeyValue(KeyValueData *pkvd);
	virtual int Save(CSave &save);
	virtual int Restore(CRestore &restore);
	virtual int ObjectCaps() { return (CBaseEntity::ObjectCaps() & ~FCAP_ACROSS_TRANSITION); }

	// To spark when hit
	virtual void TraceAttack(entvars_t *pevAttacker, float flDamage, Vector vecDir, TraceResult *ptr, int bitsDamageType);

	// breakables use an overridden takedamage
	virtual int TakeDamage(entvars_t *pevInflictor, entvars_t *pevAttacker, float flDamage, int bitsDamageType);

	virtual int DamageDecal(int bitsDamageType);
	virtual void Use(CBaseEntity *pActivator, CBaseEntity *pCaller, USE_TYPE useType, float value);

#ifdef HOOK_GAMEDLL

	void Spawn_();
	void Precache_();
	void Restart_();
	void KeyValue_(KeyValueData *pkvd);
	int Save_(CSave &save);
	int Restore_(CRestore &restore);
	void TraceAttack_(entvars_t *pevAttacker, float flDamage, Vector vecDir, TraceResult *ptr, int bitsDamageType);
	int TakeDamage_(entvars_t *pevInflictor, entvars_t *pevAttacker, float flDamage, int bitsDamageType);
	int DamageDecal_(int bitsDamageType);
	void Use_(CBaseEntity *pActivator, CBaseEntity *pCaller, USE_TYPE useType, float value);

#endif

public:
	void EXPORT BreakTouch(CBaseEntity *pOther);
	void DamageSound();

	BOOL IsBreakable();
	BOOL SparkWhenHit();

	void EXPORT Die();

	BOOL Explodable() const { return ExplosionMagnitude() > 0; }
	int ExplosionMagnitude() const { return pev->impulse; }

	void ExplosionSetMagnitude(int magnitude) { pev->impulse = magnitude; }

	static void MaterialSoundPrecache(Materials precacheMaterial);
	static void MaterialSoundRandom(edict_t *pEdict, Materials soundMaterial, float volume);
	static const char **MaterialSoundList(Materials precacheMaterial, int &soundCount);

	static const char *pSoundsWood[3];
	static const char *pSoundsFlesh[6];
	static const char *pSoundsGlass[3];
	static const char *pSoundsMetal[3];
	static const char *pSoundsConcrete[3];
	static const char *pSpawnObjects[32];

	static TYPEDESCRIPTION IMPL(m_SaveData)[5];

public:
	Materials m_Material;
	Explosions m_Explosion;
	int m_idShard;
	float m_angle;
	int m_iszGibModel;
	int m_iszSpawnObject;
	float m_flHealth;
};

class CPushable: public CBreakable
{
public:
	CPushable();
	virtual void Spawn();
	virtual void Precache();
	virtual void KeyValue(KeyValueData *pkvd);
	virtual int Save(CSave &save);
	virtual int Restore(CRestore &restore);
	virtual int ObjectCaps() { return (CBaseEntity::ObjectCaps() & ~FCAP_ACROSS_TRANSITION) | FCAP_CONTINUOUS_USE; }
	virtual int TakeDamage(entvars_t *pevInflictor, entvars_t *pevAttacker, float flDamage, int bitsDamageType);
	virtual void Touch(CBaseEntity *pOther);
	virtual void Use(CBaseEntity *pActivator, CBaseEntity *pCaller, USE_TYPE useType, float value);

#ifdef HOOK_GAMEDLL

	void Spawn_();
	void Precache_();
	void KeyValue_(KeyValueData *pkvd);
	int Save_(CSave &save);
	int Restore_(CRestore &restore);
	int TakeDamage_(entvars_t *pevInflictor, entvars_t *pevAttacker, float flDamage, int bitsDamageType);
	void Touch_(CBaseEntity *pOther);
	void Use_(CBaseEntity *pActivator, CBaseEntity *pCaller, USE_TYPE useType, float value);

#endif

public:
	void Move(CBaseEntity *pMover, int push);
	void EXPORT StopSound()
	{
#if 0
		Vector dist = pev->oldorigin - pev->origin;
		if (dist.Length() <= 0)
		{
			STOP_SOUND(ENT(pev), CHAN_WEAPON, m_soundNames[m_lastSound]);
		}
#endif
	}
	float MaxSpeed() const { return m_maxSpeed; }

public:
	static TYPEDESCRIPTION IMPL(m_SaveData)[2];
	static char *m_soundNames[3];

	int m_lastSound;
	float m_maxSpeed;
	float m_soundTime;
};

#endif // FUNC_BREAK_H

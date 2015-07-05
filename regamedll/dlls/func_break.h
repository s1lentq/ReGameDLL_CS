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
#define	NUM_SHARDS 6

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

#ifdef HOOK_GAMEDLL

#define pSoundsWood (*ppSoundsWood)
#define pSoundsFlesh (*ppSoundsFlesh)
#define pSoundsGlass (*ppSoundsGlass)
#define pSoundsMetal (*ppSoundsMetal)
#define pSoundsConcrete (*ppSoundsConcrete)
#define pSpawnObjects (*ppSpawnObjects)
#define m_soundNames (*pm_soundNames)

#endif // HOOK_GAMEDLL

/* <84d53> ../cstrike/dlls/func_break.h:23 */
class CBreakable: public CBaseDelay
{
public:
	// basic functions
	NOBODY virtual void Spawn(void);
	NOBODY virtual void Precache(void);
	NOBODY virtual void Restart(void);
	NOBODY virtual void KeyValue(KeyValueData *pkvd);
	NOBODY virtual int Save(CSave &save);
	NOBODY virtual int Restore(CRestore &restore);
	NOBODY virtual int ObjectCaps(void)
	{
		return ObjectCaps_();
	}

	// To spark when hit
	NOBODY virtual void TraceAttack(entvars_t *pevAttacker, float flDamage, Vector vecDir, TraceResult *ptr, int bitsDamageType);

	// breakables use an overridden takedamage
	NOBODY virtual int TakeDamage(entvars_t *pevInflictor, entvars_t *pevAttacker, float flDamage, int bitsDamageType);

	NOBODY virtual int DamageDecal(int bitsDamageType);
	NOBODY virtual void Use(CBaseEntity *pActivator, CBaseEntity *pCaller, USE_TYPE useType, float value);

#ifdef HOOK_GAMEDLL

	void Spawn_(void);
	void Precache_(void);
	void Restart_(void);
	void KeyValue_(KeyValueData *pkvd);
	int Save_(CSave &save);
	int Restore_(CRestore &restore);
	int ObjectCaps_(void)
	{
		return (CBaseEntity::ObjectCaps() & ~FCAP_ACROSS_TRANSITION);
	}
	void TraceAttack_(entvars_t *pevAttacker, float flDamage, Vector vecDir, TraceResult *ptr, int bitsDamageType);
	int TakeDamage_(entvars_t *pevInflictor, entvars_t *pevAttacker, float flDamage, int bitsDamageType);
	int DamageDecal_(int bitsDamageType);
	void Use_(CBaseEntity *pActivator, CBaseEntity *pCaller, USE_TYPE useType, float value);

#endif // HOOK_GAMEDLL

public:
	NOBODY void EXPORT BreakTouch(CBaseEntity *pOther);
	NOBODY void DamageSound(void);

	NOBODY BOOL IsBreakable(void);
	NOBODY BOOL SparkWhenHit(void);

	NOBODY void EXPORT Die(void);
	
	inline BOOL Explodable(void)
	{
		return ExplosionMagnitude() > 0;
	}
	inline int ExplosionMagnitude(void)
	{
		return pev->impulse;
	}
	inline void ExplosionSetMagnitude(int magnitude)
	{
		pev->impulse = magnitude;
	}

	NOBODY static void MaterialSoundPrecache(Materials precacheMaterial);
	NOBODY static void MaterialSoundRandom(edict_t *pEdict, Materials soundMaterial, float volume);
	NOBODY static const char **MaterialSoundList(Materials precacheMaterial, int &soundCount);

	static const char *pSoundsWood[3];
	static const char *pSoundsFlesh[6];
	static const char *pSoundsGlass[3];
	static const char *pSoundsMetal[3];
	static const char *pSoundsConcrete[3];
	static const char *pSpawnObjects[32];

	static TYPEDESCRIPTION IMPLEMENT_ARRAY(m_SaveData)[5];

public:
	Materials m_Material;
	Explosions m_Explosion;
	int m_idShard;
	float m_angle;
	int m_iszGibModel;
	int m_iszSpawnObject;
	float m_flHealth;

};/* size: 188, cachelines: 3, members: 15 */

/* <84da0> ../cstrike/dlls/func_break.cpp:851 */
class CPushable: public CBreakable
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
	NOBODY virtual int TakeDamage(entvars_t *pevInflictor, entvars_t *pevAttacker, float flDamage, int bitsDamageType);
	NOBODY virtual void Touch(CBaseEntity *pOther);
	NOBODY virtual void Use(CBaseEntity *pActivator, CBaseEntity *pCaller, USE_TYPE useType, float value);
	
#ifdef HOOK_GAMEDLL

	void Spawn_(void);
	void Precache_(void);
	void KeyValue_(KeyValueData *pkvd);
	int Save_(CSave &save);
	int Restore_(CRestore &restore);
	int ObjectCaps_(void)
	{
		return (CBaseEntity::ObjectCaps() & ~FCAP_ACROSS_TRANSITION) | FCAP_CONTINUOUS_USE;
	}
	int TakeDamage_(entvars_t *pevInflictor, entvars_t *pevAttacker, float flDamage, int bitsDamageType);
	void Touch_(CBaseEntity *pOther);
	void Use_(CBaseEntity *pActivator, CBaseEntity *pCaller, USE_TYPE useType, float value);

#endif // HOOK_GAMEDLL

public:
	NOBODY void Move(CBaseEntity *pMover, int push);
	NOBODY void EXPORT StopSound(void);
	inline float MaxSpeed(void)
	{
		return m_maxSpeed;
	}

public:
	static TYPEDESCRIPTION IMPLEMENT_ARRAY(m_SaveData)[2];

public:
	static char *m_soundNames[3];

	int m_lastSound;
	float m_maxSpeed;
	float m_soundTime;

};/* size: 200, cachelines: 4, members: 6 */

#endif // FUNC_BREAK_H

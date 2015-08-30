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

#ifndef BASEMONSTER_H
#define BASEMONSTER_H
#ifdef _WIN32
#pragma once
#endif

void RadiusFlash(Vector vecSrc, entvars_t *pevInflictor, entvars_t *pevAttacker, float flDamage, int iClassIgnore = 0, int bitsDamageType = 0);
float GetAmountOfPlayerVisible(Vector vecSrc, CBaseEntity *entity);
void RadiusDamage(Vector vecSrc, entvars_t *pevInflictor, entvars_t *pevAttacker, float flDamage, float flRadius, int iClassIgnore, int bitsDamageType);
void RadiusDamage2(Vector vecSrc, entvars_t *pevInflictor, entvars_t *pevAttacker, float flDamage, float flRadius, int iClassIgnore, int bitsDamageType);
NOXREF char *vstr(float *v);

/* <48ecff> ../cstrike/dlls/basemonster.h:18 */
class CBaseMonster: public CBaseToggle
{
public:
	NOBODY virtual void KeyValue(KeyValueData *pkvd);
	virtual void TraceAttack(entvars_t *pevAttacker, float flDamage, Vector vecDir, TraceResult *ptr, int bitsDamageType);
	NOBODY virtual int TakeDamage(entvars_t *pevInflictor, entvars_t *pevAttacker, float flDamage, int bitsDamageType);
	NOBODY virtual int TakeHealth(float flHealth, int bitsDamageType);
	virtual void Killed(entvars_t *pevAttacker, int iGib);
	virtual int BloodColor(void)
	{
		return BloodColor_();
	}
	virtual BOOL IsAlive(void)
	{
		return IsAlive_();
	}
	virtual float ChangeYaw(int speed);
	virtual BOOL HasHumanGibs(void);
	virtual BOOL HasAlienGibs(void);
	NOBODY virtual void FadeMonster(void);
	virtual void GibMonster(void);
	NOBODY virtual Activity GetDeathActivity(void);
	virtual void BecomeDead(void);
	virtual BOOL ShouldFadeOnDeath(void);
	NOBODY virtual int IRelationship(CBaseEntity *pTarget);
	virtual void PainSound(void) {}
	NOBODY virtual void ResetMaxSpeed(void) {}
	NOBODY virtual void ReportAIState(void) {}
	virtual void MonsterInitDead(void);
	NOBODY virtual void Look(int iDistance);
	NOBODY virtual CBaseEntity *BestVisibleEnemy(void);
	NOBODY virtual BOOL FInViewCone(CBaseEntity *pEntity);
	NOBODY virtual BOOL FInViewCone(Vector *pOrigin);

#ifdef HOOK_GAMEDLL

	void KeyValue_(KeyValueData *pkvd);
	void TraceAttack_(entvars_t *pevAttacker, float flDamage, Vector vecDir, TraceResult *ptr, int bitsDamageType);
	int TakeDamage_(entvars_t *pevInflictor, entvars_t *pevAttacker, float flDamage, int bitsDamageType);
	int TakeHealth_(float flHealth, int bitsDamageType);
	void Killed_(entvars_t *pevAttacker, int iGib);
	int BloodColor_(void)
	{
		return m_bloodColor;
	}
	BOOL IsAlive_(void)
	{
		return (pev->deadflag != DEAD_DEAD);
	}
	float ChangeYaw_(int speed);
	BOOL HasHumanGibs_(void);
	BOOL HasAlienGibs_(void);
	void FadeMonster_(void);
	void GibMonster_(void);
	Activity GetDeathActivity_(void);
	void BecomeDead_(void);
	BOOL ShouldFadeOnDeath_(void);
	int IRelationship_(CBaseEntity *pTarget);
	void MonsterInitDead_(void);
	void Look_(int iDistance);
	CBaseEntity *BestVisibleEnemy_(void);
	BOOL FInViewCone_(CBaseEntity *pEntity);
	BOOL FInViewCone_(Vector *pOrigin);

#endif // HOOK_GAMEDLL

public:
	void MakeIdealYaw(Vector vecTarget);
	NOBODY Activity GetSmallFlinchActivity(void);
	BOOL ShouldGibMonster(int iGib);
	void CallGibMonster(void);
	BOOL FCheckAITrigger(void);
	int DeadTakeDamage(entvars_t *pevInflictor, entvars_t *pevAttacker, float flDamage, int bitsDamageType);
	float DamageForce(float damage);
	void RadiusDamage(entvars_t *pevInflictor, entvars_t *pevAttacker, float flDamage, int iClassIgnore, int bitsDamageType);
	NOXREF void RadiusDamage(Vector vecSrc, entvars_t *pevInflictor, entvars_t *pevAttacker, float flDamage, int iClassIgnore, int bitsDamageType);
	void RadiusDamage2(Vector vecSrc, entvars_t *pevInflictor, entvars_t *pevAttacker, float flDamage, int iClassIgnore, int bitsDamageType)
	{
		::RadiusDamage2(vecSrc, pevInflictor, pevAttacker, flDamage, flDamage * (RANDOM_FLOAT(0.5, 1.5) + 3), iClassIgnore, bitsDamageType);
	}
	void SetConditions(int iConditions)
	{
		m_afConditions |= iConditions;
	}
	void ClearConditions(int iConditions)
	{
		m_afConditions &= ~iConditions;
	}
	BOOL HasConditions(int iConditions)
	{
		if (m_afConditions & iConditions)
		{
			return TRUE;
		}
		return FALSE;
	}
	BOOL HasAllConditions(int iConditions)
	{
		if ((m_afConditions & iConditions) == iConditions)
		{
			return TRUE;
		}
		return FALSE;
	}
	void Remember(int iMemory)
	{
		m_afMemory |= iMemory;
	}
	void Forget(int iMemory)
	{
		m_afMemory &= ~iMemory;
	}
	BOOL HasMemory(int iMemory)
	{
		if (m_afMemory & iMemory)
		{
			return TRUE;
		}
		return FALSE;
	}
	BOOL HasAllMemories(int iMemory)
	{
		if ((m_afMemory & iMemory) == iMemory)
		{
			return TRUE;
		}
		return FALSE;
	}
	void StopAnimation(void)
	{
		pev->framerate = 0.0;
	}
	NOBODY void CorpseFallThink(void);
	NOBODY CBaseEntity *CheckTraceHullAttack(float flDist, int iDamage, int iDmgType);
	NOXREF void MakeDamageBloodDecal(int cCount, float flNoise, TraceResult *ptr, Vector &vecDir);
	void MonsterUse(CBaseEntity *pActivator, CBaseEntity *pCaller, USE_TYPE useType, float value)
	{
		m_IdealMonsterState = MONSTERSTATE_ALERT;
	}
	void BloodSplat(const Vector &vecSrc, const Vector &vecDir, int HitLocation, int iVelocity);

public:
	Activity m_Activity;			// what the monster is doing (animation)
	Activity m_IdealActivity;		// monster should switch to this activity
	int m_LastHitGroup;			// the last body region that took damage
	int m_bitsDamageType;			// what types of damage has monster (player) taken
	BYTE m_rgbTimeBasedDamage[8];
	MONSTERSTATE m_MonsterState;		// monster's current state
	MONSTERSTATE m_IdealMonsterState;	// monster should change to this state
	int m_afConditions;
	int m_afMemory;
	float m_flNextAttack;			// cannot attack again until this time
	EHANDLE m_hEnemy;			// the entity that the monster is fighting.
	EHANDLE m_hTargetEnt;			// the entity that the monster is trying to reach
	float m_flFieldOfView;			// width of monster's field of view ( dot product )
	int m_bloodColor;			// color of blood particless
	Vector m_HackedGunPos;			// HACK until we can query end of gun
	Vector m_vecEnemyLKP;			// last known position of enemy. (enemy's origin)

};/* size: 404, cachelines: 7, members: 17 */

#ifdef HOOK_GAMEDLL

typedef void (CBaseMonster::*RADIUSDAMAGE_ENTVARS)(entvars_t *, entvars_t *, float, int, int);
typedef void (CBaseMonster::*RADIUSDAMAGE_VECTOR)(Vector, entvars_t *, entvars_t *, float, int, int);

typedef BOOL (CBaseMonster::*FINVIEWCONE_ENTITY)(CBaseEntity *);
typedef BOOL (CBaseMonster::*FINVIEWCONE_VECTOR)(Vector *);

#endif // HOOK_GAMEDLL

#endif // BASEMONSTER_H

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

#include "activity.h"

class EHANDLE;

enum MONSTERSTATE
{
	MONSTERSTATE_NONE = 0,
	MONSTERSTATE_IDLE,
	MONSTERSTATE_COMBAT,
	MONSTERSTATE_ALERT,
	MONSTERSTATE_HUNT,
	MONSTERSTATE_PRONE,
	MONSTERSTATE_SCRIPT,
	MONSTERSTATE_PLAYDEAD,
	MONSTERSTATE_DEAD
};

class CBaseToggle;
class CBaseMonster: public CBaseToggle {
public:
	virtual void KeyValue(KeyValueData *pkvd) = 0;
	virtual void TraceAttack(entvars_t *pevAttacker, float flDamage, Vector vecDir, TraceResult *ptr, int bitsDamageType) = 0;
	virtual BOOL TakeDamage(entvars_t *pevInflictor, entvars_t *pevAttacker, float flDamage, int bitsDamageType) = 0;
	virtual BOOL TakeHealth(float flHealth, int bitsDamageType) = 0;
	virtual void Killed(entvars_t *pevAttacker, int iGib) = 0;
	virtual int BloodColor() = 0;
	virtual BOOL IsAlive() = 0;
	virtual float ChangeYaw(int speed) = 0;
	virtual BOOL HasHumanGibs() = 0;
	virtual BOOL HasAlienGibs() = 0;
	virtual void FadeMonster() = 0;
	virtual void GibMonster() = 0;
	virtual Activity GetDeathActivity() = 0;
	virtual void BecomeDead() = 0;
	virtual BOOL ShouldFadeOnDeath() = 0;
	virtual int IRelationship(CBaseEntity *pTarget) = 0;
	virtual void PainSound() = 0;
	virtual void ResetMaxSpeed() = 0;
	virtual void ReportAIState() = 0;
	virtual void MonsterInitDead() = 0;
	virtual void Look(int iDistance) = 0;
	virtual CBaseEntity *BestVisibleEnemy() = 0;
	virtual BOOL FInViewCone(CBaseEntity *pEntity) = 0;
	virtual BOOL FInViewCone(const Vector *pOrigin) = 0;
public:
	void SetConditions(int iConditions) { m_afConditions |= iConditions; }
	void ClearConditions(int iConditions) { m_afConditions &= ~iConditions; }
	BOOL HasConditions(int iConditions) { return (m_afConditions & iConditions) ? TRUE : FALSE; }
	BOOL HasAllConditions(int iConditions) { return ((m_afConditions & iConditions) == iConditions) ? TRUE : FALSE; }

	void Remember(int iMemory) { m_afMemory |= iMemory; }
	void Forget(int iMemory) { m_afMemory &= ~iMemory; }
	BOOL HasMemory(int iMemory) { return (m_afMemory & iMemory) ? TRUE : FALSE; }
	BOOL HasAllMemories(int iMemory) { return ((m_afMemory & iMemory) == iMemory) ? TRUE : FALSE; }

	void StopAnimation() { pev->framerate = 0.0f; }
public:
	Activity m_Activity;			// what the monster is doing (animation)
	Activity m_IdealActivity;		// monster should switch to this activity
	int m_LastHitGroup;			// the last body region that took damage
	int m_bitsDamageType;			// what types of damage has monster (player) taken
	byte m_rgbTimeBasedDamage[8];

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
};

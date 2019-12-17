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

const int MAX_NODES                    = 100;
const int MAX_HOSTAGES                 = 12;
const int MAX_HOSTAGES_NAV             = 20;

const float HOSTAGE_STEPSIZE           = 26.0f;
const float MAX_HOSTAGES_RESCUE_RADIUS = 256.0f; // rescue zones from legacy info_*

#define VEC_HOSTAGE_VIEW               Vector(0, 0, 12)
#define VEC_HOSTAGE_HULL_MIN           Vector(-10, -10, 0)
#define VEC_HOSTAGE_HULL_MAX           Vector(10, 10, 62)
#define VEC_HOSTAGE_CROUCH             Vector(10, 10, 30)

class CHostage;
class CLocalNav;
class CHostageImprov;
class CHostageManager;

enum HostageChatterType
{
	HOSTAGE_CHATTER_START_FOLLOW = 0,
	HOSTAGE_CHATTER_STOP_FOLLOW,
	HOSTAGE_CHATTER_INTIMIDATED,
	HOSTAGE_CHATTER_PAIN,
	HOSTAGE_CHATTER_SCARED_OF_GUNFIRE,
	HOSTAGE_CHATTER_SCARED_OF_MURDER,
	HOSTAGE_CHATTER_LOOK_OUT,
	HOSTAGE_CHATTER_PLEASE_RESCUE_ME,
	HOSTAGE_CHATTER_SEE_RESCUE_ZONE,
	HOSTAGE_CHATTER_IMPATIENT_FOR_RESCUE,
	HOSTAGE_CHATTER_CTS_WIN,
	HOSTAGE_CHATTER_TERRORISTS_WIN,
	HOSTAGE_CHATTER_RESCUED,
	HOSTAGE_CHATTER_WARN_NEARBY,
	HOSTAGE_CHATTER_WARN_SPOTTED,
	HOSTAGE_CHATTER_CALL_TO_RESCUER,
	HOSTAGE_CHATTER_RETREAT,
	HOSTAGE_CHATTER_COUGH,
	HOSTAGE_CHATTER_BLINDED,
	HOSTAGE_CHATTER_SAW_HE_GRENADE,
	HOSTAGE_CHATTER_DEATH_CRY,
	NUM_HOSTAGE_CHATTER_TYPES,
};

// Improved the hostages from CZero
#include "hostage/hostage_improv.h"

extern CHostageManager *g_pHostages;
extern int g_iHostageNumber;

extern cvar_t cv_hostage_debug;
extern cvar_t cv_hostage_stop;

// A Counter-Strike Hostage Simple
class CHostage: public CBaseMonster
{
public:
	virtual void Spawn();
	virtual void Precache();
	virtual int ObjectCaps();		// make hostage "useable"
	virtual int Classify() { return CLASS_HUMAN_PASSIVE; }
	virtual void TraceAttack(entvars_t *pevAttacker, float flDamage, Vector vecDir, TraceResult *ptr, int bitsDamageType);
	virtual BOOL TakeDamage(entvars_t *pevInflictor, entvars_t *pevAttacker, float flDamage, int bitsDamageType);
	virtual int BloodColor() { return BLOOD_COLOR_RED; }

#ifndef REGAMEDLL_FIXES
	virtual BOOL IsAlive() { return (pev->takedamage == DAMAGE_YES); }
#endif

	virtual void Touch(CBaseEntity *pOther);
	virtual void Use(CBaseEntity *pActivator, CBaseEntity *pCaller, USE_TYPE useType, float value);

public:
	void EXPORT IdleThink();
	void EXPORT Remove();
	void RePosition();
	void SetActivity(Activity act);
	Activity GetActivity() { return m_Activity; }
	float GetModifiedDamage(float flDamage, int nHitGroup);
	void SetFlinchActivity();
	void SetDeathActivity();
	void PlayPainSound();
	void PlayFollowRescueSound();
	void AnnounceDeath(CBasePlayer *pAttacker);
	void ApplyHostagePenalty(CBasePlayer *pAttacker);
	void GiveCTTouchBonus(CBasePlayer *pPlayer);
	void SendHostagePositionMsg();
	void SendHostageEventMsg();
	void DoFollow();
	BOOL IsOnLadder();
	void PointAt(const Vector &vecLoc);
	void MoveToward(const Vector &vecLoc);
	void NavReady();
	void Wiggle();
	void PreThink();
	bool CanTakeDamage(entvars_t *pevAttacker);

	// queries
	bool IsFollowingSomeone() { return IsFollowing(); }
	CBaseEntity *GetLeader()				// return our leader, or NULL
	{
		if (m_improv) {
			return m_improv->GetFollowLeader();
		}

		return m_hTargetEnt;
	}
	bool IsFollowing(const CBaseEntity *pEntity = nullptr)
	{
		if (m_improv) {
			return m_improv->IsFollowing(pEntity);
		}

		if ((!pEntity && !m_hTargetEnt) || (pEntity && m_hTargetEnt != pEntity))
			return false;

		if (m_State != FOLLOW)
			return false;

		return true;
	}

	bool IsValid()  const { return (pev->takedamage == DAMAGE_YES); }
	bool IsDead()   const { return (pev->deadflag == DEAD_DEAD); }
	bool IsAtHome() const { return !(pev->origin - m_vStart).IsLengthGreaterThan(20); }
	const Vector *GetHomePosition() const { return &m_vStart; }

public:
	BOOL m_bTouched;
	BOOL m_bRescueMe;
	float m_flFlinchTime;
	float m_flNextChange;
	float m_flMarkPosition;
	int m_iModel;
	int m_iSkin;
	float m_flNextRadarTime;
	enum state { FOLLOW, STAND, DUCK, SCARED, IDLE, FOLLOWPATH };
	state m_State;
	Vector m_vStart;
	Vector m_vStartAngles;
	Vector m_vPathToFollow[MAX_HOSTAGES_NAV];
	int m_iWaypoint;
	CBasePlayer *m_target;
	CLocalNav *m_LocalNav;
	int m_nTargetNode;
	Vector vecNodes[MAX_NODES];
	EntityHandle<CBasePlayer> m_hStoppedTargetEnt;
	float m_flNextFullThink;
	float m_flPathCheckInterval;
	float m_flLastPathCheck;
	int m_nPathNodes;
	BOOL m_fHasPath;
	float m_flPathAcquired;
	Vector m_vOldPos;
	int m_iHostageIndex;
	BOOL m_bStuck;
	float m_flStuckTime;
	CHostageImprov *m_improv;

	enum ModelType { REGULAR_GUY, OLD_GUY, BLACK_GUY, GOOFY_GUY };
	ModelType m_whichModel;
};

class SimpleChatter
{
public:
	SimpleChatter();
	~SimpleChatter();

	struct SoundFile
	{
		char *filename;
		float duration;
	};

	struct ChatterSet
	{
		SoundFile file[32];
		int count;
		int index;
		bool needsShuffle;
	};

	void AddSound(HostageChatterType type, char *filename);
	float PlaySound(CBaseEntity *pEntity, HostageChatterType type);
	char *GetSound(HostageChatterType type, float *duration);
	void Shuffle(ChatterSet *chatter);

private:
	ChatterSet m_chatter[NUM_HOSTAGE_CHATTER_TYPES];
};

class CHostageManager
{
public:
	CHostageManager();

	void ServerActivate();
	void ServerDeactivate();

	void RestartRound();
	void AddHostage(CHostage *hostage);
	SimpleChatter *GetChatter()
	{
		return &m_chatter;
	}
	bool IsNearbyHostageTalking(CHostageImprov *improv);
	bool IsNearbyHostageJumping(CHostageImprov *improv);
	void OnEvent(GameEventType event, CBaseEntity *pEntity, CBaseEntity *pOther);

	// Iterate over all active hostages in the game, invoking functor on each.
	// If functor returns false, stop iteration and return false.
	template<typename Functor>
	inline bool ForEachHostage(Functor &func) const
	{
		for (int i = 0; i < m_hostageCount; i++)
		{
			CHostage *pHostage = m_hostage[i];

			if (!pHostage || pHostage->pev->deadflag == DEAD_DEAD)
				continue;

			if (!func(pHostage))
				return false;
		}

		return true;
	}
	inline CHostage *GetClosestHostage(const Vector &pos, float *resultRange = nullptr)
	{
		float range;
		float closeRange = 1e8f;
		CHostage *close = nullptr;

		for (int i = 0; i < m_hostageCount; i++)
		{
			range = (m_hostage[i]->pev->origin - pos).Length();

			if (range < closeRange)
			{
				closeRange = range;
				close = m_hostage[i];
			}
		}

		if (resultRange)
			*resultRange = closeRange;

		return close;
	}

private:
	CHostage *m_hostage[MAX_HOSTAGES];
	int m_hostageCount;
	SimpleChatter m_chatter;
};

// Determine whether hostage improv can be used or not
inline bool AreImprovAllowed()
{
	return g_bHostageImprov;
}

void Hostage_RegisterCVars();
void InstallHostageManager();

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

#define MAX_NODES			100
#define MAX_HOSTAGES			12
#define MAX_HOSTAGES_NAV		20

#define HOSTAGE_STEPSIZE		26.0f
#define HOSTAGE_STEPSIZE_DEFAULT	18.0f

#define VEC_HOSTAGE_VIEW		Vector(0, 0, 12)
#define VEC_HOSTAGE_HULL_MIN		Vector(-10, -10, 0)
#define VEC_HOSTAGE_HULL_MAX		Vector(10, 10, 62)

#define VEC_HOSTAGE_CROUCH		Vector(10, 10, 30)
#define RESCUE_HOSTAGES_RADIUS		256.0f				// rescue zones from legacy info_*

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
	HOSTAGE_CHATTER_CTS_WIN ,
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

// A Counter-Strike Hostage Simple
class CHostage: public CBaseMonster {
public:
	virtual void Spawn() = 0;
	virtual void Precache() = 0;
	virtual int ObjectCaps() = 0;		// make hostage "useable"
	virtual int Classify() = 0;
	virtual void TraceAttack(entvars_t *pevAttacker, float flDamage, Vector vecDir, TraceResult *ptr, int bitsDamageType) = 0;
	virtual BOOL TakeDamage(entvars_t *pevInflictor, entvars_t *pevAttacker, float flDamage, int bitsDamageType) = 0;
	virtual int BloodColor() = 0;
	virtual void Touch(CBaseEntity *pOther) = 0;
	virtual void Use(CBaseEntity *pActivator, CBaseEntity *pCaller, USE_TYPE useType, float value) = 0;
public:
	int GetActivity() { return m_Activity; }

	// queries
	bool IsFollowingSomeone() { return IsFollowing(); }
	CBaseEntity *GetLeader()				// return our leader, or NULL
	{
		if (m_improv != NULL)
		{
			return m_improv->GetFollowLeader();
		}

		return m_hTargetEnt;
	}
	bool IsFollowing(const CBaseEntity *entity = NULL)
	{
		if (m_improv != NULL)
		{
			return m_improv->IsFollowing();
		}

		if (entity == NULL && m_hTargetEnt == NULL || (entity != NULL && m_hTargetEnt != entity))
			return false;

		if (m_State != FOLLOW)
			return false;

		return true;
	}
	bool IsValid() const { return (pev->takedamage == DAMAGE_YES); }
	bool IsDead() const { return (pev->deadflag == DEAD_DEAD); }
	bool IsAtHome() const { return (pev->origin - m_vStart).IsLengthGreaterThan(20) != true; }
	const Vector *GetHomePosition() const { return &m_vStart; }
public:
	int m_Activity;
	BOOL m_bTouched;
	BOOL m_bRescueMe;
	float m_flFlinchTime;
	float m_flNextChange;
	float m_flMarkPosition;
	int m_iModel;
	int m_iSkin;
	float m_flNextRadarTime;
	enum state { FOLLOW, STAND, DUCK, SCARED, IDLE, FOLLOWPATH }
	m_State;
	Vector m_vStart;
	Vector m_vStartAngles;
	Vector m_vPathToFollow[20];
	int m_iWaypoint;
	CBasePlayer *m_target;
	CLocalNav *m_LocalNav;
	int nTargetNode;
	Vector vecNodes[MAX_NODES];
	EHANDLE m_hStoppedTargetEnt;
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

	enum ModelType { REGULAR_GUY, OLD_GUY, BLACK_GUY, GOOFY_GUY }
	m_whichModel;
};

class SimpleChatter {
public:
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
private:
	ChatterSet m_chatter[21];
};

class CHostageManager {
public:
	SimpleChatter *GetChatter()
	{
		return &m_chatter;
	}
	// Iterate over all active hostages in the game, invoking functor on each.
	// If functor returns false, stop iteration and return false.
	template<typename Functor>
	inline bool ForEachHostage(Functor &func) const
	{
		for (int i = 0; i < m_hostageCount; i++)
		{
			CHostage *hostage = m_hostage[i];

			if (hostage == NULL || hostage->pev->deadflag == DEAD_DEAD)
				continue;

			if (func(hostage) == false)
				return false;
		}

		return true;
	}
	inline CHostage *GetClosestHostage(const Vector &pos, float *resultRange = NULL)
	{
		float range;
		float closeRange = 1e8f;
		CHostage *close = NULL;

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

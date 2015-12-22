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

#ifndef HOSTAGE_H
#define HOSTAGE_H
#ifdef _WIN32
#pragma once
#endif

// Improved the hostages from CZero
#include "hostage/hostage_improv.h"

#define MAX_NODES			100
#define MAX_HOSTAGES			12
#define MAX_HOSTAGES_NAV		20

#define HOSTAGE_STEPSIZE		26.0
#define HOSTAGE_STEPSIZE_DEFAULT	18.0

#define VEC_HOSTAGE_VIEW		Vector(0, 0, 12)
#define VEC_HOSTAGE_HULL_MIN		Vector(-10, -10, 0)
#define VEC_HOSTAGE_HULL_MAX		Vector(10, 10, 62)

#define VEC_HOSTAGE_CROUCH		Vector(10, 10, 30)

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

#ifdef HOOK_GAMEDLL

#define g_pHostages (*pg_pHostages)
#define g_iHostageNumber (*pg_iHostageNumber)

#define cv_hostage_debug (*pcv_hostage_debug)
#define cv_hostage_stop (*pcv_hostage_stop)

#endif // HOOK_GAMEDLL

extern CHostageManager *g_pHostages;
extern int g_iHostageNumber;

extern cvar_t cv_hostage_debug;
extern cvar_t cv_hostage_stop;

/* <4858e5> ../cstrike/dlls/hostage/hostage.h:32 */
class CHostage: public CBaseMonster
{
public:
	virtual void Spawn(void);
	virtual void Precache(void);
	virtual int ObjectCaps(void);
	virtual int Classify(void)
	{
		return CLASS_HUMAN_PASSIVE;
	}
	virtual int TakeDamage(entvars_t *pevInflictor, entvars_t *pevAttacker, float flDamage, int bitsDamageType);
	virtual int BloodColor(void)
	{
		return BLOOD_COLOR_RED;
	}
	virtual void Touch(CBaseEntity *pOther);
	virtual void Use(CBaseEntity *pActivator, CBaseEntity *pCaller, USE_TYPE useType, float value);

#ifdef HOOK_GAMEDLL

	void Spawn_(void);
	void Precache_(void);
	int ObjectCaps_(void);
	int TakeDamage_(entvars_t *pevInflictor, entvars_t *pevAttacker, float flDamage, int bitsDamageType);
	void Touch_(CBaseEntity *pOther);
	void Use_(CBaseEntity *pActivator, CBaseEntity *pCaller, USE_TYPE useType, float value);

#endif // HOOK_GAMEDLL

public:
	void EXPORT IdleThink(void);
	void EXPORT Remove(void);
	void RePosition(void);
	void SetActivity(int act);
	int GetActivity(void)
	{
		return m_Activity;
	}
	float GetModifiedDamage(float flDamage, int nHitGroup);
	void SetFlinchActivity(void);
	void SetDeathActivity(void);
	void PlayPainSound(void);
	void PlayFollowRescueSound(void);
	void AnnounceDeath(CBasePlayer *pAttacker);
	void ApplyHostagePenalty(CBasePlayer *pAttacker);
	void GiveCTTouchBonus(CBasePlayer *pPlayer);
	void SendHostagePositionMsg(void);
	void SendHostageEventMsg(void);
	void DoFollow(void);
	BOOL IsOnLadder(void);
	void PointAt(const Vector &vecLoc);
	void MoveToward(const Vector &vecLoc);
	void NavReady(void);
	void Wiggle(void);
	void PreThink(void);

	bool IsFollowingSomeone(void)
	{
		return m_improv->IsFollowing();
	}
	CBaseEntity *GetLeader(void)
	{
		if (m_improv != NULL)
		{
			return m_improv->GetFollowLeader();
		}

		return NULL;
	}
	bool IsFollowing(const CBaseEntity *entity)
	{
		return (entity == m_hTargetEnt && m_State == FOLLOW);
	}
	bool IsValid(void)
	{
		return (pev->takedamage == DAMAGE_YES);
	}
	bool IsDead(void)
	{
		return (pev->deadflag == DEAD_DEAD);
	}
	bool IsAtHome(void)
	{
		return (pev->origin - m_vStart).IsLengthGreaterThan(20) != true;
	}
	const Vector *GetHomePosition(void)
	{
		return &m_vStart;
	}

public:
	enum state
	{
		FOLLOW = 0,
		STAND,
		DUCK,
		SCARED,
		IDLE,
		FOLLOWPATH,
	};

	enum ModelType
	{
		REGULAR_GUY = 0,
		OLD_GUY,
		BLACK_GUY,
		GOOFY_GUY,
	};

	int m_Activity;
	BOOL m_bTouched;
	BOOL m_bRescueMe;
	float m_flFlinchTime;
	float m_flNextChange;
	float m_flMarkPosition;
	int m_iModel;
	int m_iSkin;
	float m_flNextRadarTime;
	state m_State;
	Vector m_vStart;
	Vector m_vStartAngles;
	Vector m_vPathToFollow[20];
	int m_iWaypoint;
	CBasePlayer *m_target;
	CLocalNav *m_LocalNav;
	int nTargetNode;
	Vector vecNodes[ MAX_NODES ];
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
	ModelType m_whichModel;

};/* size: 1988, cachelines: 32, members: 32 */

class SimpleChatter
{
public:
	SimpleChatter(void);
	~SimpleChatter(void);

	struct SoundFile
	{
		char *filename;
		float duration;

	};/* size: 8, cachelines: 1, members: 2 */

	struct ChatterSet
	{
		SoundFile file[32];
		int count;
		int index;
		bool needsShuffle;

	};/* size: 268, cachelines: 5, members: 4 */

	void AddSound(HostageChatterType type, char *filename);

#ifdef _WIN32
	#undef PlaySound
#endif // _WIN32

	float PlaySound(CBaseEntity *entity, HostageChatterType type);
	char *GetSound(HostageChatterType type, float *duration);
	void Shuffle(ChatterSet *chatter);

private:
	ChatterSet m_chatter[21];

};/* size: 5628, cachelines: 88, members: 1 */

/* <45b018> ../cstrike/dlls/hostage/hostage.h:247 */
class CHostageManager
{
public:
	CHostageManager(void);

	void ServerActivate(void);
	void ServerDeactivate(void);

	void RestartRound(void);
	void AddHostage(CHostage *hostage);
	SimpleChatter *GetChatter(void)
	{
		return &m_chatter;
	}
	bool IsNearbyHostageTalking(CHostageImprov *improv);
	bool IsNearbyHostageJumping(CHostageImprov *improv);
	void OnEvent(GameEventType event, CBaseEntity *entity, CBaseEntity *other);
	inline CHostage *GetClosestHostage(const Vector &pos, float *resultRange = NULL)
	{
		float range;
		float closeRange = 1e8f;
		CHostage *close = NULL;

		for (int i = 0; i < m_hostageCount; i++)
		{
			range = (m_hostage[ i ]->pev->origin - pos).Length();

			if (range < closeRange)
			{
				closeRange = range;
				close = m_hostage[ i ];
			}
		}

		if (resultRange)
			*resultRange = closeRange;

		return close;
	}

	template<typename T>
	bool ForEachHostage(T &func) const
	{
		for (int i = 0; i < m_hostageCount; i++)
		{
			CHostage *pHostage = m_hostage[ i ];

			if (pHostage->pev->deadflag == DEAD_DEAD)
				continue;

			if (func(pHostage) == false)
				return false;
		}

		return true;
	}

private:
	CHostage *m_hostage[ MAX_HOSTAGES ];
	int m_hostageCount;
	SimpleChatter m_chatter;

};/* size: 5680, cachelines: 89, members: 3 */


///* <470134> ../cstrike/dlls/hostage/hostage.h:293 */
//inline void CHostageManager::ForEachHostage<KeepPersonalSpace>(KeepPersonalSpace &func)
//{
////	{
////		int i;                                                //   295
////	}
//}
//
///* <46fbe8> ../cstrike/dlls/hostage/hostage.h:293 */
//inline void CHostageManager::ForEachHostage<CheckAhead>(CheckAhead &func)
//{
////	{
////		int i;                                                //   295
////	}
//}
//
///* <46fb04> ../cstrike/dlls/hostage/hostage.h:293 */
//inline void CHostageManager::ForEachHostage<CheckWayFunctor>(CheckWayFunctor &func)
//{
////	{
////		int i;                                                //   295
////	}
//}

#ifdef HOOK_GAMEDLL

// linked object
C_DLLEXPORT void hostage_entity(entvars_t *pev);
C_DLLEXPORT void monster_scientist(entvars_t *pev);

#endif // HOOK_GAMEDLL

void Hostage_RegisterCVars(void);
void InstallHostageManager(void);

// refs
extern void (CBaseEntity::*pCHostage__IdleThink)(void);

#endif // HOSTAGE_H

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

#define MAX_NODES 100
#define MAX_HOSTAGES 20

#define HOSTAGE_STEPSIZE 26.0

class CHostage;
class CLocalNav;
class CHostageImprov;

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

/* <4858e5> ../cstrike/dlls/hostage/hostage.h:32 */
class CHostage: public CBaseMonster
{
public:
	NOBODY virtual void Spawn(void);
	NOBODY virtual void Precache(void);
	NOBODY virtual int ObjectCaps(void);
	virtual int Classify(void)
	{
		return CLASS_HUMAN_PASSIVE;
	}
	NOBODY virtual int TakeDamage(entvars_t *pevInflictor, entvars_t *pevAttacker, float flDamage, int bitsDamageType);
	virtual int BloodColor(void)
	{
		return BLOOD_COLOR_RED;
	}
	NOBODY virtual void Touch(CBaseEntity *pOther);
	NOBODY virtual void Use(CBaseEntity *pActivator, CBaseEntity *pCaller, USE_TYPE useType, float value);

	NOBODY void EXPORT IdleThink(void);
	NOBODY void Remove(void);
	NOBODY void RePosition(void);
	NOBODY void SetActivity(int act);
	NOBODY int GetActivity(void);
	NOBODY float GetModifiedDamage(float flDamage, int nHitGroup);
	NOBODY void SetFlinchActivity(void);
	NOBODY void SetDeathActivity(void);
	NOBODY void PlayPainSound(void);
	NOBODY void PlayFollowRescueSound(void);
	NOBODY void AnnounceDeath(CBasePlayer *pAttacker);
	NOBODY void ApplyHostagePenalty(CBasePlayer *pAttacker);
	NOBODY void GiveCTTouchBonus(CBasePlayer *pPlayer);
	NOBODY void SendHostagePositionMsg(void);
	NOBODY void SendHostageEventMsg(void);
	NOBODY void DoFollow(void);
	NOBODY BOOL IsOnLadder(void);
	NOBODY void PointAt(const Vector &vecLoc);
	NOBODY void MoveToward(const Vector &vecLoc);
	void NavReady(void);
	NOBODY void Wiggle(void);
	void PreThink(void);

	NOBODY bool IsFollowingSomeone(void);//
	NOBODY CBaseEntity *GetLeader(void);//
	NOBODY bool IsFollowing(const CBaseEntity *entity)
	{
		return (entity == m_hTargetEnt && m_State == FOLLOW);
	}
	NOBODY bool IsValid(void);//
	NOBODY bool IsDead(void);//
	NOBODY bool IsAtHome(void);//
	NOBODY const Vector *GetHomePosition(void);//
	
#ifdef HOOK_GAMEDLL

	void Spawn_(void);
	void Precache_(void);
	int ObjectCaps_(void);
	int TakeDamage_(entvars_t *pevInflictor, entvars_t *pevAttacker, float flDamage, int bitsDamageType);
	void Touch_(CBaseEntity *pOther);
	void Use_(CBaseEntity *pActivator, CBaseEntity *pCaller, USE_TYPE useType, float value);

#endif // HOOK_GAMEDLL

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
	Vector m_vPathToFollow[ MAX_HOSTAGES ];
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
		struct SoundFile file[32];
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

class CHostageManager
{
public:
	CHostageManager(void);

	NOBODY void ServerActivate(void);
	void ServerDeactivate(void) { };

	NOBODY void RestartRound(void);
	NOBODY void AddHostage(CHostage *hostage);
	SimpleChatter *GetChatter(void)
	{
		return &m_chatter;
	}
	NOBODY bool IsNearbyHostageTalking(CHostageImprov *improv);
	NOBODY bool IsNearbyHostageJumping(CHostageImprov *improv);
	NOBODY void OnEvent(GameEventType event, CBaseEntity *entity, CBaseEntity *other);
	UNTESTED inline CHostage *GetClosestHostage(const Vector &pos, float *resultRange = NULL)
	{
		float closeRange = 100000000.0f;
		CHostage *close = NULL;

		for (int i = 0; i < m_hostageCount; i++)
		{
			float range = (m_hostage[ i ]->pev->origin - pos).Length();

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

private:
	CHostage *m_hostage[12];
	int m_hostageCount;
	SimpleChatter m_chatter;

};/* size: 5680, cachelines: 89, members: 3 */

#ifdef HOOK_GAMEDLL

#define g_pHostages (*pg_pHostages)
#define g_iHostageNumber (*pg_iHostageNumber)

#endif // HOOK_GAMEDLL

extern CHostageManager *g_pHostages;
extern int g_iHostageNumber;

NOBODY void Hostage_RegisterCVars(void);
NOBODY void InstallHostageManager(void);

#endif // HOSTAGE_H

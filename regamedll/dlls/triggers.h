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

#include "utlmap.h"

class CFrictionModifier: public CBaseEntity
{
public:
	virtual void Spawn();
	virtual void KeyValue(KeyValueData *pkvd);
	virtual int Save(CSave &save);
	virtual int Restore(CRestore &restore);
	virtual int ObjectCaps() { return (CBaseEntity::ObjectCaps() & ~FCAP_ACROSS_TRANSITION); }

public:
	void EXPORT ChangeFriction(CBaseEntity *pOther);
	static TYPEDESCRIPTION m_SaveData[];

	float m_frictionFraction;
};

#define SF_AUTO_FIREONCE BIT(0)
#define SF_AUTO_NORESET  BIT(1)

// This trigger will fire when the level spawns (or respawns if not fire once)
// It will check a global state before firing. It supports delay and killtargets
class CAutoTrigger: public CBaseDelay
{
public:
	virtual void Spawn();
	virtual void Precache();
	virtual void KeyValue(KeyValueData *pkvd);
	virtual int Save(CSave &save);
	virtual int Restore(CRestore &restore);
	virtual int ObjectCaps() { return (CBaseDelay::ObjectCaps() & ~FCAP_ACROSS_TRANSITION); }
	virtual void Think();

#ifdef REGAMEDLL_FIXES
	virtual void Restart();
#endif

public:
	static TYPEDESCRIPTION m_SaveData[];

	int m_globalstate;
	USE_TYPE m_triggerType;
};

#define SF_RELAY_FIREONCE BIT(0)

class CTriggerRelay: public CBaseDelay
{
public:
	virtual void Spawn();
	virtual void KeyValue(KeyValueData *pkvd);
	virtual int Save(CSave &save);
	virtual int Restore(CRestore &restore);
	virtual int ObjectCaps() { return (CBaseDelay::ObjectCaps() & ~FCAP_ACROSS_TRANSITION); }
	virtual void Use(CBaseEntity *pActivator, CBaseEntity *pCaller, USE_TYPE useType, float value);

public:
	static TYPEDESCRIPTION m_SaveData[];

	USE_TYPE m_triggerType;
};

const int MAX_MM_TARGETS = 16; // maximum number of targets a single multi_manager entity may be assigned.

#define SF_MULTIMAN_THREAD BIT(0)
#define SF_MULTIMAN_CLONE  BIT(31)

// This entity when fire, will fire up to 16 targets at specified times.
// at specified times.
// FLAG:		THREAD (create clones when triggered)
// FLAG:		CLONE (this is a clone for a threaded execution)
class CMultiManager: public CBaseToggle
{
public:
	virtual void Spawn();
	virtual void Restart();
	virtual void KeyValue(KeyValueData *pkvd);
	virtual int Save(CSave &save);
	virtual int Restore(CRestore &restore);
	virtual int ObjectCaps() { return (CBaseToggle::ObjectCaps() & ~FCAP_ACROSS_TRANSITION); }
	virtual BOOL HasTarget(string_t targetname);

public:
	void EXPORT ManagerThink();
	void EXPORT ManagerUse(CBaseEntity *pActivator, CBaseEntity *pCaller, USE_TYPE useType, float value);

private:
	BOOL IsClone()
	{
		if (pev->spawnflags & SF_MULTIMAN_CLONE)
		{
			return TRUE;
		}

		return FALSE;
	}
	BOOL ShouldClone()
	{
		if (IsClone())
		{
			return FALSE;
		}

		if (pev->spawnflags & SF_MULTIMAN_THREAD)
		{
			return TRUE;
		}

		return FALSE;
	}
	CMultiManager *Clone();

public:
	static TYPEDESCRIPTION m_SaveData[];

	int m_cTargets;
	int m_index;
	float m_startTime;
	int m_iTargetName[MAX_MM_TARGETS];
	float m_flTargetDelay[MAX_MM_TARGETS];
};

// Flags to indicate masking off various render parameters that are normally copied to the targets
#define SF_RENDER_MASKFX    BIT(0)
#define SF_RENDER_MASKAMT   BIT(1)
#define SF_RENDER_MASKMODE  BIT(2)
#define SF_RENDER_MASKCOLOR BIT(3)

// Render parameters trigger
// This entity will copy its render parameters (renderfx, rendermode, rendercolor, renderamt)
// to its targets when triggered.
class CRenderFxManager: public CBaseEntity
{
public:
	virtual void Spawn();
	virtual void Use(CBaseEntity *pActivator, CBaseEntity *pCaller, USE_TYPE useType, float value);

#ifdef REGAMEDLL_FIXES
	virtual void Restart();
	virtual void OnDestroy();

public:
	struct RenderGroup_t
	{
		int rendermode;
		float renderamt;
		Vector rendercolor;
		int renderfx;
	};
	CUtlMap<int, RenderGroup_t> m_RenderGroups;
#endif

};

#define SF_TRIGGER_ALLOWMONSTERS BIT(0) // monsters allowed to fire this trigger
#define SF_TRIGGER_NOCLIENTS     BIT(1) // players not allowed to fire this trigger
#define SF_TRIGGER_PUSHABLES     BIT(2) // only pushables can fire this trigger
#define SF_TRIGGER_NORESET       BIT(6) // it is not allowed to be resetting on a new round

class CBaseTrigger: public CBaseToggle
{
public:
	virtual void KeyValue(KeyValueData *pkvd);
	virtual int ObjectCaps() { return (CBaseToggle::ObjectCaps() & ~FCAP_ACROSS_TRANSITION); }

public:
	void EXPORT TeleportTouch(CBaseEntity *pOther);
	void EXPORT MultiTouch(CBaseEntity *pOther);
	void EXPORT HurtTouch(CBaseEntity *pOther);
	void EXPORT CDAudioTouch(CBaseEntity *pOther);
	void ActivateMultiTrigger(CBaseEntity *pActivator);
	void EXPORT MultiWaitOver();
	void EXPORT CounterUse(CBaseEntity *pActivator, CBaseEntity *pCaller, USE_TYPE useType, float value);
	void EXPORT ToggleUse(CBaseEntity *pActivator, CBaseEntity *pCaller, USE_TYPE useType, float value);
	void InitTrigger();
};

#define SF_TRIGGER_HURT_TARGETONCE      BIT(0) // Only fire hurt target once
#define SF_TRIGGER_HURT_START_OFF       BIT(1) // spawnflag that makes trigger_push spawn turned OFF
#define SF_TRIGGER_HURT_NO_CLIENTS      BIT(3) // spawnflag that makes trigger_push spawn turned OFF
#define SF_TRIGGER_HURT_CLIENTONLYFIRE  BIT(4) // trigger hurt will only fire its target if it is hurting a client
#define SF_TRIGGER_HURT_CLIENTONLYTOUCH BIT(5) // only clients may touch this trigger.

// Hurts anything that touches it.
// If the trigger has a targetname, firing it will toggle state
class CTriggerHurt: public CBaseTrigger
{
public:
	virtual void Spawn();

#ifdef REGAMEDLL_FIXES
	virtual void Restart();
#endif

	void EXPORT RadiationThink();
};

class CTriggerMonsterJump: public CBaseTrigger
{
public:
	virtual void Spawn();
	virtual void Think();
	virtual void Touch(CBaseEntity *pOther);
};

// Starts/stops cd audio tracks
class CTriggerCDAudio: public CBaseTrigger
{
public:
	virtual void Spawn();
	virtual void Touch(CBaseEntity *pOther);
	virtual void Use(CBaseEntity *pActivator, CBaseEntity *pCaller, USE_TYPE useType, float value);

public:
	void PlayTrack(edict_t *pEdict);
};

// This plays a CD track when fired or when the player enters it's radius
class CTargetCDAudio: public CPointEntity
{
public:
	virtual void Spawn();
	virtual void KeyValue(KeyValueData *pkvd);
	virtual void Think();
	virtual void Use(CBaseEntity *pActivator, CBaseEntity *pCaller, USE_TYPE useType, float value);

public:
	void Play(edict_t *pEdict);
};

#define SF_TRIGGER_MULTIPLE_NOTOUCH BIT(0)

// Variable sized repeatable trigger. Must be targeted at one or more entities.
// If "health" is set, the trigger must be killed to activate each time.
// If "delay" is set, the trigger waits some time after activating before firing.
// "wait" : Seconds between triggerings. (.2 default)
// If notouch is set, the trigger is only fired by other entities, not by touching.
// NOTOUCH has been obsoleted by trigger_relay!
// sounds
// 1)	secret
// 2)	beep beep
// 3)	large switch
// 4)
// NEW
// if a trigger has a NETNAME, that NETNAME will become the TARGET of the triggered object.
class CTriggerMultiple: public CBaseTrigger
{
public:
	virtual void Spawn();
};

// Variable sized trigger. Triggers once, then removes itself. You must set the key "target" to the name of another object in the level that has a matching
// "targetname". If "health" is set, the trigger must be killed to activate.
// If notouch is set, the trigger is only fired by other entities, not by touching.
// if "killtarget" is set, any objects that have a matching "target" will be removed when the trigger is fired.
// if "angle" is set, the trigger will only fire when someone is facing the direction of the angle. Use "360" for an angle of 0.
// sounds
// 1)	secret
// 2)	beep beep
// 3)	large switch
// 4)
class CTriggerOnce: public CTriggerMultiple
{
public:
	virtual void Spawn();

#ifdef REGAMEDLL_FIXES
	virtual void Restart();
#endif
};

#define SF_TRIGGER_COUNTER_NOMESSAGE BIT(0)

// Acts as an intermediary for an action that takes multiple inputs.
// If nomessage is not set, it will print "1 more.. " etc when triggered and
// "sequence complete" when finished. After the counter has been triggered "cTriggersLeft"
// times (default 2), it will fire all of it's targets and remove itself.
class CTriggerCounter: public CBaseTrigger
{
public:
	virtual void Spawn();
};

// Derive from point entity so this doesn't move across levels
class CTriggerVolume: public CPointEntity
{
public:
	virtual void Spawn();
};

// Fires a target after level transition and then dies
class CFireAndDie: public CBaseDelay
{
public:
	virtual void Spawn();
	virtual void Precache();
	virtual int ObjectCaps() { return (CBaseDelay::ObjectCaps() | FCAP_FORCE_TRANSITION); }		// Always go across transitions
	virtual void Think();
};

#define SF_CHANGELEVEL_USEONLY BIT(1)

// When the player touches this, he gets sent to the map listed in the "map" variable.
// Unless the NO_INTERMISSION flag is set, the view will go to the info_intermission spot and display stats.
class CChangeLevel: public CBaseTrigger
{
public:
	virtual void Spawn();
	virtual void KeyValue(KeyValueData *pkvd);
	virtual int Save(CSave &save);
	virtual int Restore(CRestore &restore);

public:
	void EXPORT UseChangeLevel(CBaseEntity *pActivator, CBaseEntity *pCaller, USE_TYPE useType, float value);
	void EXPORT TriggerChangeLevel();
	void EXPORT ExecuteChangeLevel();
	void EXPORT TouchChangeLevel(CBaseEntity *pOther);
	void ChangeLevelNow(CBaseEntity *pActivator);

	static edict_t *FindLandmark(const char *pLandmarkName);
	static int ChangeList(LEVELLIST *pLevelList, int maxList);
	static int AddTransitionToList(LEVELLIST *pLevelList, int listCount, const char *pMapName, const char *pLandmarkName, edict_t *pentLandmark);
	static int InTransitionVolume(CBaseEntity *pEntity, char *pVolumeName);

public:
	static TYPEDESCRIPTION m_SaveData[];

	char m_szMapName[MAX_MAPNAME_LENGHT];		// next map
	char m_szLandmarkName[MAX_MAPNAME_LENGHT];	// landmark on next map
	int m_changeTarget;
	float m_changeTargetDelay;

#ifdef REGAMEDLL_FIXES
	float m_flPercentOfPlayers;
#endif
};

class CLadder: public CBaseTrigger
{
public:
	virtual void Spawn();
	virtual void Precache();
	virtual void KeyValue(KeyValueData *pkvd);
};

#define SF_TRIGGER_PUSH_ONCE      BIT(0)
#define SF_TRIGGER_PUSH_START_OFF BIT(1) // spawnflag that makes trigger_push spawn turned OFF

class CTriggerPush: public CBaseTrigger
{
public:
	virtual void Spawn();
	virtual void KeyValue(KeyValueData *pkvd);
	virtual void Touch(CBaseEntity *pOther);

#ifdef REGAMEDLL_FIXES
	virtual void Restart();
#endif
};

class CTriggerTeleport: public CBaseTrigger
{
public:
	virtual void Spawn();
};

class CBuyZone: public CBaseTrigger
{
public:
	virtual void Spawn();

	void EXPORT BuyTouch(CBaseEntity *pOther);
};

class CBombTarget: public CBaseTrigger
{
private:
	bool IsPlayerInBombSite(CBasePlayer *pPlayer);
public:
	virtual void Spawn();
	void EXPORT BombTargetTouch(CBaseEntity *pOther);
	void EXPORT BombTargetUse(CBaseEntity *pActivator, CBaseEntity *pCaller, USE_TYPE useType, float value);
};

class CHostageRescue: public CBaseTrigger
{
public:
	virtual void Spawn();

public:
	void EXPORT HostageRescueTouch(CBaseEntity *pOther);
};

class CEscapeZone: public CBaseTrigger
{
public:
	virtual void Spawn();

	void EXPORT EscapeTouch(CBaseEntity *pOther);
};

class CVIP_SafetyZone: public CBaseTrigger
{
public:
	virtual void Spawn();

	void EXPORT VIP_SafetyTouch(CBaseEntity *pOther);
};

class CTriggerSave: public CBaseTrigger
{
public:
	virtual void Spawn();

	void EXPORT SaveTouch(CBaseEntity *pOther);
};

#define SF_ENDSECTION_USEONLY BIT(0)

class CTriggerEndSection: public CBaseTrigger
{
public:
	virtual void Spawn();
	virtual void KeyValue(KeyValueData *pkvd);

public:
	void EXPORT EndSectionTouch(CBaseEntity *pOther);
	void EXPORT EndSectionUse(CBaseEntity *pActivator, CBaseEntity *pCaller, USE_TYPE useType, float value);
};

class CTriggerGravity: public CBaseTrigger
{
public:
	virtual void Spawn();

	void EXPORT GravityTouch(CBaseEntity *pOther);
};

// this is a really bad idea.
class CTriggerChangeTarget: public CBaseDelay
{
public:
	virtual void Spawn();
	virtual void KeyValue(KeyValueData *pkvd);
	virtual int Save(CSave &save);
	virtual int Restore(CRestore &restore);
	virtual int ObjectCaps() { return (CBaseEntity::ObjectCaps() & ~FCAP_ACROSS_TRANSITION); }
	virtual void Use(CBaseEntity *pActivator, CBaseEntity *pCaller, USE_TYPE useType, float value);

public:
	static TYPEDESCRIPTION m_SaveData[];

private:
	int m_iszNewTarget;
};

#define SF_CAMERA_PLAYER_POSITION    BIT(0)
#define SF_CAMERA_PLAYER_TARGET      BIT(1)
#define SF_CAMERA_PLAYER_TAKECONTROL BIT(2)

class CTriggerCamera: public CBaseDelay
{
public:
	virtual void Spawn();
	virtual void KeyValue(KeyValueData *pkvd);
	virtual int Save(CSave &save);
	virtual int Restore(CRestore &restore);
	virtual int ObjectCaps() { return (CBaseEntity::ObjectCaps() & ~FCAP_ACROSS_TRANSITION); }
	virtual void Use(CBaseEntity *pActivator, CBaseEntity *pCaller, USE_TYPE useType, float value);

public:
	void EXPORT FollowTarget();
	void Move();

	static TYPEDESCRIPTION m_SaveData[];

	EntityHandle<CBasePlayer> m_hPlayer;
	EntityHandle<CBaseEntity> m_hTarget;
	CBaseEntity *m_pentPath;
	int m_sPath;
	float m_flWait;
	float m_flReturnTime;
	float m_flStopTime;
	float m_moveDistance;
	float m_targetSpeed;
	float m_initialSpeed;
	float m_acceleration;
	float m_deceleration;
	int m_state;
};

class CWeather: public CBaseTrigger
{
public:
	virtual void Spawn();
};

class CClientFog: public CBaseEntity
{
public:
	virtual void Spawn();
	virtual void KeyValue(KeyValueData *pkvd);

public:
	int m_iStartDist;
	int m_iEndDist;
	float m_fDensity;
};

void PlayCDTrack(edict_t *pClient, int iTrack);
int BuildChangeList(LEVELLIST *pLevelList, int maxList);
void NextLevel();

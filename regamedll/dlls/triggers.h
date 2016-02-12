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

#ifndef TRIGGERS_H
#define TRIGGERS_H
#ifdef _WIN32
#pragma once
#endif

#define GRENADETYPE_SMOKE			1
#define GRENADETYPE_FLASH			2

#define MAX_ITEM_COUNTS				32
#define MAX_ENTITY				512	// We can only ever move 512 entities across a transition

// triggers
#define	SF_TRIGGER_ALLOWMONSTERS		1	// monsters allowed to fire this trigger
#define	SF_TRIGGER_NOCLIENTS			2	// players not allowed to fire this trigger
#define SF_TRIGGER_PUSHABLES			4	// only pushables can fire this trigger

#define	SF_TRIGGER_PUSH_START_OFF		2	// spawnflag that makes trigger_push spawn turned OFF
#define SF_TRIGGER_HURT_TARGETONCE		1	// Only fire hurt target once
#define	SF_TRIGGER_HURT_START_OFF		2	// spawnflag that makes trigger_push spawn turned OFF
#define	SF_TRIGGER_HURT_NO_CLIENTS		8	// spawnflag that makes trigger_push spawn turned OFF
#define SF_TRIGGER_HURT_CLIENTONLYFIRE		16	// trigger hurt will only fire its target if it is hurting a client
#define SF_TRIGGER_HURT_CLIENTONLYTOUCH		32	// only clients may touch this trigger.

#define SF_AUTO_FIREONCE			0x0001
#define SF_RELAY_FIREONCE			0x0001
#define SF_ENDSECTION_USEONLY			0x0001

#define SF_MULTIMAN_CLONE			0x80000000
#define SF_MULTIMAN_THREAD			0x00000001

#define SF_CHANGELEVEL_USEONLY			0x0002
#define SF_CAMERA_PLAYER_POSITION		1
#define SF_CAMERA_PLAYER_TARGET			2
#define SF_CAMERA_PLAYER_TAKECONTROL		4

// Flags to indicate masking off various render parameters that are normally copied to the targets
#define SF_RENDER_MASKFX	(1 << 0)
#define SF_RENDER_MASKAMT	(1 << 1)
#define SF_RENDER_MASKMODE	(1 << 2)
#define SF_RENDER_MASKCOLOR	(1 << 3)

class CFrictionModifier: public CBaseEntity
{
public:
	virtual void Spawn();
	virtual void KeyValue(KeyValueData *pkvd);
	virtual int Save(CSave &save);
	virtual int Restore(CRestore &restore);
	virtual int ObjectCaps() { return (CBaseEntity::ObjectCaps() & ~FCAP_ACROSS_TRANSITION); }

#ifdef HOOK_GAMEDLL

	void Spawn_();
	void KeyValue_(KeyValueData *pkvd);
	int Save_(CSave &save);
	int Restore_(CRestore &restore);

#endif // HOOK_GAMEDLL

public:
	void EXPORT ChangeFriction(CBaseEntity *pOther);
	static TYPEDESCRIPTION IMPL(m_SaveData)[1];

	float m_frictionFraction;
};

// This trigger will fire when the level spawns (or respawns if not fire once)
// It will check a global state before firing.  It supports delay and killtargets

/* <19e39c> ../cstrike/dlls/triggers.cpp:108 */
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

#ifdef HOOK_GAMEDLL

	void Spawn_();
	void Precache_();
	void KeyValue_(KeyValueData *pkvd);
	int Save_(CSave &save);
	int Restore_(CRestore &restore);
	void Think_();

#endif // HOOK_GAMEDLL

public:
	static TYPEDESCRIPTION IMPL(m_SaveData)[2];

	int m_globalstate;
	USE_TYPE triggerType;
};

/* <19e3ed> ../cstrike/dlls/triggers.cpp:191 */
class CTriggerRelay: public CBaseDelay
{
public:
	virtual void Spawn();
	virtual void KeyValue(KeyValueData *pkvd);
	virtual int Save(CSave &save);
	virtual int Restore(CRestore &restore);
	virtual int ObjectCaps() { return (CBaseDelay::ObjectCaps() & ~FCAP_ACROSS_TRANSITION); }
	virtual void Use(CBaseEntity *pActivator, CBaseEntity *pCaller, USE_TYPE useType, float value);

#ifdef HOOK_GAMEDLL

	void Spawn_();
	void KeyValue_(KeyValueData *pkvd);
	int Save_(CSave &save);
	int Restore_(CRestore &restore);
	void Use_(CBaseEntity *pActivator, CBaseEntity *pCaller, USE_TYPE useType, float value);

#endif // HOOK_GAMEDLL

public:
	static TYPEDESCRIPTION IMPL(m_SaveData)[1];

	USE_TYPE triggerType;
};

// The Multimanager Entity - when fired, will fire up to 16 targets
// at specified times.
// FLAG:		THREAD (create clones when triggered)
// FLAG:		CLONE (this is a clone for a threaded execution)

/* <19e4d6> ../cstrike/dlls/triggers.cpp:264 */
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

#ifdef HOOK_GAMEDLL

	void Spawn_();
	void Restart_();
	void KeyValue_(KeyValueData *pkvd);
	int Save_(CSave &save);
	int Restore_(CRestore &restore);
	BOOL HasTarget_(string_t targetname);

#endif // HOOK_GAMEDLL

public:
	void EXPORT ManagerThink();
	void EXPORT ManagerUse(CBaseEntity *pActivator, CBaseEntity *pCaller, USE_TYPE useType, float value);

private:
	/* <19dfe1> ../cstrike/dlls/triggers.cpp:293 */
	BOOL IsClone()
	{
		if (pev->spawnflags & SF_MULTIMAN_CLONE)
		{
			return TRUE;
		}

		return FALSE;
	}
	/* <19e4f3> ../cstrike/dlls/triggers.cpp:294 */
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
	static TYPEDESCRIPTION IMPL(m_SaveData)[5];

	int m_cTargets;
	int m_index;
	float m_startTime;
	int m_iTargetName[ MAX_MULTI_TARGETS ];
	float m_flTargetDelay[ MAX_MULTI_TARGETS ];
};

// Render parameters trigger
//
// This entity will copy its render parameters (renderfx, rendermode, rendercolor, renderamt)
// to its targets when triggered.

/* <19e50c> ../cstrike/dlls/triggers.cpp:525 */
class CRenderFxManager: public CBaseEntity
{
public:
	virtual void Spawn();
	virtual void Use(CBaseEntity *pActivator, CBaseEntity *pCaller, USE_TYPE useType, float value);

#ifdef HOOK_GAMEDLL

	void Spawn_();
	void Use_(CBaseEntity *pActivator, CBaseEntity *pCaller, USE_TYPE useType, float value);

#endif // HOOK_GAMEDLL

};

/* <19e55f> ../cstrike/dlls/triggers.cpp:566 */
class CBaseTrigger: public CBaseToggle
{
public:
	virtual void KeyValue(KeyValueData *pkvd);
	virtual int ObjectCaps() { return (CBaseToggle::ObjectCaps() & ~FCAP_ACROSS_TRANSITION); }

#ifdef HOOK_GAMEDLL

	void KeyValue_(KeyValueData *pkvd);

#endif // HOOK_GAMEDLL

public:
	void EXPORT TeleportTouch(CBaseEntity *pOther);
	void EXPORT MultiTouch(CBaseEntity *pOther);
	void EXPORT HurtTouch(CBaseEntity *pOther);
	NOXREF void EXPORT CDAudioTouch(CBaseEntity *pOther);
	void ActivateMultiTrigger(CBaseEntity *pActivator);
	void EXPORT MultiWaitOver();
	void EXPORT CounterUse(CBaseEntity *pActivator, CBaseEntity *pCaller, USE_TYPE useType, float value);
	void EXPORT ToggleUse(CBaseEntity *pActivator, CBaseEntity *pCaller, USE_TYPE useType, float value);
	void InitTrigger();
};

// trigger_hurt - hurts anything that touches it. if the trigger has a targetname, firing it will toggle state
// int gfToggleState = 0; // used to determine when all radiation trigger hurts have called 'RadiationThink'

/* <19e5b2> ../cstrike/dlls/triggers.cpp:629 */
class CTriggerHurt: public CBaseTrigger
{
public:
	virtual void Spawn();

#ifdef HOOK_GAMEDLL

	void Spawn_();

#endif // HOOK_GAMEDLL

	void EXPORT RadiationThink();
};

/* <19e60a> ../cstrike/dlls/triggers.cpp:641 */
class CTriggerMonsterJump: public CBaseTrigger
{
public:
	virtual void Spawn();
	virtual void Think();
	virtual void Touch(CBaseEntity *pOther);

#ifdef HOOK_GAMEDLL

	void Spawn_();
	void Think_();
	void Touch_(CBaseEntity *pOther);

#endif // HOOK_GAMEDLL

};

// trigger_cdaudio - starts/stops cd audio tracks

/* <19e65d> ../cstrike/dlls/triggers.cpp:705 */
class CTriggerCDAudio: public CBaseTrigger
{
public:
	virtual void Spawn();
	virtual void Touch(CBaseEntity *pOther);
	virtual void Use(CBaseEntity *pActivator, CBaseEntity *pCaller, USE_TYPE useType, float value);

#ifdef HOOK_GAMEDLL

	void Spawn_();
	void Touch_(CBaseEntity *pOther);
	void Use_(CBaseEntity *pActivator, CBaseEntity *pCaller, USE_TYPE useType, float value);

#endif // HOOK_GAMEDLL

public:
	void PlayTrack();
};

// This plays a CD track when fired or when the player enters it's radius

/* <19e6d2> ../cstrike/dlls/triggers.cpp:783 */
class CTargetCDAudio: public CPointEntity
{
public:
	virtual void Spawn();
	virtual void KeyValue(KeyValueData *pkvd);
	virtual void Think();
	virtual void Use(CBaseEntity *pActivator, CBaseEntity *pCaller, USE_TYPE useType, float value);

#ifdef HOOK_GAMEDLL

	void Spawn_();
	void KeyValue_(KeyValueData *pkvd);
	void Think_();
	void Use_(CBaseEntity *pActivator, CBaseEntity *pCaller, USE_TYPE useType, float value);

#endif // HOOK_GAMEDLL

public:
	void Play();
};

// QUAKED trigger_multiple (.5 .5 .5) ? notouch
// Variable sized repeatable trigger.  Must be targeted at one or more entities.
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

/* <19e725> ../cstrike/dlls/triggers.cpp:1080 */
class CTriggerMultiple: public CBaseTrigger
{
public:
	virtual void Spawn();

#ifdef HOOK_GAMEDLL

	void Spawn_();

#endif // HOOK_GAMEDLL

};

// QUAKED trigger_once (.5 .5 .5) ? notouch
// Variable sized trigger. Triggers once, then removes itself.  You must set the key "target" to the name of another object in the level that has a matching
// "targetname".  If "health" is set, the trigger must be killed to activate.
// If notouch is set, the trigger is only fired by other entities, not by touching.
// if "killtarget" is set, any objects that have a matching "target" will be removed when the trigger is fired.
// if "angle" is set, the trigger will only fire when someone is facing the direction of the angle.  Use "360" for an angle of 0.
// sounds
// 1)	secret
// 2)	beep beep
// 3)	large switch
// 4)

/* <19e77d> ../cstrike/dlls/triggers.cpp:1129 */
class CTriggerOnce: public CTriggerMultiple
{
public:
	virtual void Spawn();

#ifdef HOOK_GAMEDLL

	void Spawn_();

#endif // HOOK_GAMEDLL

};

// QUAKED trigger_counter (.5 .5 .5) ? nomessage
// Acts as an intermediary for an action that takes multiple inputs.
// If nomessage is not set, it will print "1 more.. " etc when triggered and
// "sequence complete" when finished.  After the counter has been triggered "cTriggersLeft"
// times (default 2), it will fire all of it's targets and remove itself.

/* <19e7d5> ../cstrike/dlls/triggers.cpp:1273 */
class CTriggerCounter: public CBaseTrigger
{
public:
	virtual void Spawn();

#ifdef HOOK_GAMEDLL

	void Spawn_();

#endif // HOOK_GAMEDLL

};

// Derive from point entity so this doesn't move across levels

/* <19e82d> ../cstrike/dlls/triggers.cpp:1293 */
class CTriggerVolume: public CPointEntity
{
public:
	virtual void Spawn();

#ifdef HOOK_GAMEDLL

	void Spawn_();

#endif // HOOK_GAMEDLL

};

// Fires a target after level transition and then dies

/* <19e885> ../cstrike/dlls/triggers.cpp:1313 */
class CFireAndDie: public CBaseDelay
{
public:
	virtual void Spawn();
	virtual void Precache();
	virtual int ObjectCaps() { return (CBaseDelay::ObjectCaps() | FCAP_FORCE_TRANSITION); }		// Always go across transitions
	virtual void Think();

#ifdef HOOK_GAMEDLL

	void Spawn_();
	void Precache_();
	void Think_();

#endif // HOOK_GAMEDLL

};

// QUAKED trigger_changelevel (0.5 0.5 0.5) ? NO_INTERMISSION
// When the player touches this, he gets sent to the map listed in the "map" variable.  Unless the NO_INTERMISSION flag is set, the view will go to the info_intermission spot and display stats.

/* <19e906> ../cstrike/dlls/triggers.cpp:1345 */
class CChangeLevel: public CBaseTrigger
{
public:
	virtual void Spawn();
	virtual void KeyValue(KeyValueData *pkvd);
	virtual int Save(CSave &save);
	virtual int Restore(CRestore &restore);

#ifdef HOOK_GAMEDLL

	void Spawn_();
	void KeyValue_(KeyValueData *pkvd);
	int Save_(CSave &save);
	int Restore_(CRestore &restore);

#endif // HOOK_GAMEDLL

public:
	void EXPORT UseChangeLevel(CBaseEntity *pActivator, CBaseEntity *pCaller, USE_TYPE useType, float value);
	NOXREF void EXPORT TriggerChangeLevel();
	void EXPORT ExecuteChangeLevel();
	void EXPORT TouchChangeLevel(CBaseEntity *pOther);
	void ChangeLevelNow(CBaseEntity *pActivator);

	static edict_t *FindLandmark(const char *pLandmarkName);
	static int ChangeList(LEVELLIST *pLevelList, int maxList);
	static int AddTransitionToList(LEVELLIST *pLevelList, int listCount, const char *pMapName, const char *pLandmarkName, edict_t *pentLandmark);
	static int InTransitionVolume(CBaseEntity *pEntity, char *pVolumeName);

public:
	static TYPEDESCRIPTION IMPL(m_SaveData)[4];

	char m_szMapName[ cchMapNameMost ];		// trigger_changelevel only:  next map
	char m_szLandmarkName[ cchMapNameMost ];	// trigger_changelevel only:  landmark on next map
	int m_changeTarget;
	float m_changeTargetDelay;
};

/* <19e99d> ../cstrike/dlls/triggers.cpp:1753 */
class CLadder: public CBaseTrigger
{
public:
	virtual void Spawn();
	virtual void Precache();
	virtual void KeyValue(KeyValueData *pkvd);

#ifdef HOOK_GAMEDLL

	void Spawn_();
	void Precache_();
	void KeyValue_(KeyValueData *pkvd);

#endif // HOOK_GAMEDLL

};

/* <19e9f5> ../cstrike/dlls/triggers.cpp:1797 */
class CTriggerPush: public CBaseTrigger
{
public:
	virtual void Spawn();
	virtual void KeyValue(KeyValueData *pkvd);
	virtual void Touch(CBaseEntity *pOther);

#ifdef HOOK_GAMEDLL

	void Spawn_();
	void KeyValue_(KeyValueData *pkvd);
	void Touch_(CBaseEntity *pOther);

#endif // HOOK_GAMEDLL

};

/* <19ea4d> ../cstrike/dlls/triggers.cpp:1935 */
class CTriggerTeleport: public CBaseTrigger
{
public:
	virtual void Spawn();

#ifdef HOOK_GAMEDLL

	void Spawn_();

#endif // HOOK_GAMEDLL

};

/* <19eadb> ../cstrike/dlls/triggers.cpp:1962 */
class CBuyZone: public CBaseTrigger
{
public:
	virtual void Spawn();

#ifdef HOOK_GAMEDLL

	void Spawn_();

#endif // HOOK_GAMEDLL

	void EXPORT BuyTouch(CBaseEntity *pOther);
};

/* <19eb2e> ../cstrike/dlls/triggers.cpp:2007 */
class CBombTarget: public CBaseTrigger
{
public:
	virtual void Spawn();

#ifdef HOOK_GAMEDLL

	void Spawn_();

#endif // HOOK_GAMEDLL

public:
	void EXPORT BombTargetTouch(CBaseEntity *pOther);
	void EXPORT BombTargetUse(CBaseEntity *pActivator, CBaseEntity *pCaller, USE_TYPE useType, float value);
};

/* <19eb81> ../cstrike/dlls/triggers.cpp:2056 */
class CHostageRescue: public CBaseTrigger
{
public:
	virtual void Spawn();

#ifdef HOOK_GAMEDLL

	void Spawn_();

#endif // HOOK_GAMEDLL

public:
	void EXPORT HostageRescueTouch(CBaseEntity *pOther);
};

/* <19ebd9> ../cstrike/dlls/triggers.cpp:2098 */
class CEscapeZone: public CBaseTrigger
{
public:
	virtual void Spawn();

#ifdef HOOK_GAMEDLL

	void Spawn_();

#endif // HOOK_GAMEDLL

	void EXPORT EscapeTouch(CBaseEntity *pOther);
};

/* <19ec2c> ../cstrike/dlls/triggers.cpp:2155 */
class CVIP_SafetyZone: public CBaseTrigger
{
public:
	virtual void Spawn();

#ifdef HOOK_GAMEDLL

	void Spawn_();

#endif // HOOK_GAMEDLL

	void EXPORT VIP_SafetyTouch(CBaseEntity *pOther);
};

/* <19ec7f> ../cstrike/dlls/triggers.cpp:2198 */
class CTriggerSave: public CBaseTrigger
{
public:
	virtual void Spawn();

#ifdef HOOK_GAMEDLL

	void Spawn_();

#endif // HOOK_GAMEDLL

	void EXPORT SaveTouch(CBaseEntity *pOther);
};

/* <19ecd2> ../cstrike/dlls/triggers.cpp:2234 */
class CTriggerEndSection: public CBaseTrigger
{
public:
	virtual void Spawn();
	virtual void KeyValue(KeyValueData *pkvd);

#ifdef HOOK_GAMEDLL

	void Spawn_();
	void KeyValue_(KeyValueData *pkvd);

#endif // HOOK_GAMEDLL

public:
	void EXPORT EndSectionTouch(CBaseEntity *pOther);
	void EXPORT EndSectionUse(CBaseEntity *pActivator, CBaseEntity *pCaller, USE_TYPE useType, float value);
};

/* <19ed25> ../cstrike/dlls/triggers.cpp:2305 */
class CTriggerGravity: public CBaseTrigger
{
public:
	virtual void Spawn();

#ifdef HOOK_GAMEDLL

	void Spawn_();

#endif // HOOK_GAMEDLL

	void EXPORT GravityTouch(CBaseEntity *pOther);
};

// this is a really bad idea.

/* <19ed7d> ../cstrike/dlls/triggers.cpp:2335 */
class CTriggerChangeTarget: public CBaseDelay
{
public:
	virtual void Spawn();
	virtual void KeyValue(KeyValueData *pkvd);
	virtual int Save(CSave &save);
	virtual int Restore(CRestore &restore);
	virtual int ObjectCaps() { return (CBaseEntity::ObjectCaps() & ~FCAP_ACROSS_TRANSITION); }
	virtual void Use(CBaseEntity *pActivator, CBaseEntity *pCaller, USE_TYPE useType, float value);

#ifdef HOOK_GAMEDLL

	void Spawn_();
	void KeyValue_(KeyValueData *pkvd);
	int Save_(CSave &save);
	int Restore_(CRestore &restore);
	void Use_(CBaseEntity *pActivator, CBaseEntity *pCaller, USE_TYPE useType, float value);

#endif // HOOK_GAMEDLL

public:
	static TYPEDESCRIPTION IMPL(m_SaveData)[1];

private:
	int m_iszNewTarget;
};

/* <19edd0> ../cstrike/dlls/triggers.cpp:2391 */
class CTriggerCamera: public CBaseDelay
{
public:
	virtual void Spawn();
	virtual void KeyValue(KeyValueData *pkvd);
	virtual int Save(CSave &save);
	virtual int Restore(CRestore &restore);
	virtual int ObjectCaps() { return (CBaseEntity::ObjectCaps() & ~FCAP_ACROSS_TRANSITION); }
	virtual void Use(CBaseEntity *pActivator, CBaseEntity *pCaller, USE_TYPE useType, float value);

#ifdef HOOK_GAMEDLL

	void Spawn_();
	void KeyValue_(KeyValueData *pkvd);
	int Save_(CSave &save);
	int Restore_(CRestore &restore);
	void Use_(CBaseEntity *pActivator, CBaseEntity *pCaller, USE_TYPE useType, float value);

#endif // HOOK_GAMEDLL

public:
	void EXPORT FollowTarget();
	void Move();

	static TYPEDESCRIPTION IMPL(m_SaveData)[13];

	EHANDLE m_hPlayer;
	EHANDLE m_hTarget;
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

/* <19ee23> ../cstrike/dlls/triggers.cpp:2693 */
class CWeather: public CBaseTrigger
{
public:
	virtual void Spawn();

#ifdef HOOK_GAMEDLL

	void Spawn_();

#endif // HOOK_GAMEDLL

};

/* <1a5b85> ../cstrike/dlls/triggers.cpp:2710 */
class CClientFog: public CBaseEntity
{
public:
	virtual void Spawn();
	virtual void KeyValue(KeyValueData *pkvd);

#ifdef HOOK_GAMEDLL

	void Spawn_();
	void KeyValue_(KeyValueData *pkvd);

#endif // HOOK_GAMEDLL

public:
	int m_iStartDist;
	int m_iEndDist;
	float m_fDensity;
};

void PlayCDTrack(int iTrack);
int BuildChangeList(LEVELLIST * pLevelList, int maxList);
NOXREF void NextLevel();

#endif // TRIGGERS_H

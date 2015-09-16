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
#define SF_RENDER_MASKFX	(1<<0)
#define SF_RENDER_MASKAMT	(1<<1)
#define SF_RENDER_MASKMODE	(1<<2)
#define SF_RENDER_MASKCOLOR	(1<<3)

class CFrictionModifier: public CBaseEntity
{
public:
	virtual void Spawn(void);
	virtual void KeyValue(KeyValueData *pkvd);
	virtual int Save(CSave &save);
	virtual int Restore(CRestore &restore);
	virtual int ObjectCaps(void)
	{
		return ObjectCaps_();
	}

#ifdef HOOK_GAMEDLL

	void Spawn_(void);
	void KeyValue_(KeyValueData *pkvd);
	int Save_(CSave &save);
	int Restore_(CRestore &restore);
	int ObjectCaps_(void)
	{
		return (CBaseEntity::ObjectCaps() & ~FCAP_ACROSS_TRANSITION);
	}

#endif // HOOK_GAMEDLL

public:
	void EXPORT ChangeFriction(CBaseEntity *pOther);

public:
	static TYPEDESCRIPTION IMPLEMENT_ARRAY(m_SaveData)[1];

	float m_frictionFraction;

};/* size: 156, cachelines: 3, members: 3 */

// This trigger will fire when the level spawns (or respawns if not fire once)
// It will check a global state before firing.  It supports delay and killtargets

/* <19e39c> ../cstrike/dlls/triggers.cpp:108 */
class CAutoTrigger: public CBaseDelay
{
public:
	virtual void Spawn(void);
	virtual void Precache(void);
	virtual void KeyValue(KeyValueData *pkvd);
	virtual int Save(CSave &save);
	virtual int Restore(CRestore &restore);
	virtual int ObjectCaps(void)
	{
		return ObjectCaps_();
	}
	virtual void Think(void);

#ifdef HOOK_GAMEDLL

	void Spawn_(void);
	void Precache_(void);
	void KeyValue_(KeyValueData *pkvd);
	int Save_(CSave &save);
	int Restore_(CRestore &restore);
	int ObjectCaps_(void)
	{
		return (CBaseDelay::ObjectCaps() & ~FCAP_ACROSS_TRANSITION);
	}
	void Think_(void);

#endif // HOOK_GAMEDLL

public:
	static TYPEDESCRIPTION IMPLEMENT_ARRAY(m_SaveData)[2];

	int m_globalstate;
	USE_TYPE triggerType;

};/* size: 168, cachelines: 3, members: 4 */

/* <19e3ed> ../cstrike/dlls/triggers.cpp:191 */
class CTriggerRelay: public CBaseDelay
{
public:
	virtual void Spawn(void);
	virtual void KeyValue(KeyValueData *pkvd);
	virtual int Save(CSave &save);
	virtual int Restore(CRestore &restore);
	virtual int ObjectCaps(void)
	{
		return ObjectCaps_();
	}
	virtual void Use(CBaseEntity *pActivator, CBaseEntity *pCaller, USE_TYPE useType, float value);

#ifdef HOOK_GAMEDLL

	void Spawn_(void);
	void KeyValue_(KeyValueData *pkvd);
	int Save_(CSave &save);
	int Restore_(CRestore &restore);
	int ObjectCaps_(void)
	{
		return (CBaseDelay::ObjectCaps() & ~FCAP_ACROSS_TRANSITION);
	}
	void Use_(CBaseEntity *pActivator, CBaseEntity *pCaller, USE_TYPE useType, float value);

#endif // HOOK_GAMEDLL

public:
	static TYPEDESCRIPTION IMPLEMENT_ARRAY(m_SaveData)[1];

	USE_TYPE triggerType;

};/* size: 164, cachelines: 3, members: 3 */

// The Multimanager Entity - when fired, will fire up to 16 targets
// at specified times.
// FLAG:		THREAD (create clones when triggered)
// FLAG:		CLONE (this is a clone for a threaded execution)

/* <19e4d6> ../cstrike/dlls/triggers.cpp:264 */
class CMultiManager: public CBaseToggle
{
public:
	virtual void Spawn(void);
	virtual void Restart(void);
	virtual void KeyValue(KeyValueData *pkvd);
	virtual int Save(CSave &save);
	virtual int Restore(CRestore &restore);
	virtual int ObjectCaps(void)
	{
		return ObjectCaps_();
	}
	virtual BOOL HasTarget(string_t targetname);

#ifdef HOOK_GAMEDLL

	void Spawn_(void);
	void Restart_(void);
	void KeyValue_(KeyValueData *pkvd);
	int Save_(CSave &save);
	int Restore_(CRestore &restore);
	int ObjectCaps_(void)
	{
		return (CBaseToggle::ObjectCaps() & ~FCAP_ACROSS_TRANSITION);
	}
	BOOL HasTarget_(string_t targetname);

#endif // HOOK_GAMEDLL

public:
	void EXPORT ManagerThink(void);
	void EXPORT ManagerUse(CBaseEntity *pActivator, CBaseEntity *pCaller, USE_TYPE useType, float value);

private:
	/* <19dfe1> ../cstrike/dlls/triggers.cpp:293 */
	inline BOOL IsClone(void)
	{
		if (pev->spawnflags & SF_MULTIMAN_CLONE)
		{
			return TRUE;
		}

		return FALSE;
	}
	/* <19e4f3> ../cstrike/dlls/triggers.cpp:294 */
	inline BOOL ShouldClone(void)
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
	CMultiManager *Clone(void);

public:
	static TYPEDESCRIPTION IMPLEMENT_ARRAY(m_SaveData)[5];

	int m_cTargets;//312
	int m_index;
	float m_startTime;
	int m_iTargetName[ MAX_MULTI_TARGETS ];
	float m_flTargetDelay[ MAX_MULTI_TARGETS ];

};/* size: 452, cachelines: 8, members: 7 */
/* Linux - 452 | Windows - 432 */

// Render parameters trigger
//
// This entity will copy its render parameters (renderfx, rendermode, rendercolor, renderamt)
// to its targets when triggered.

/* <19e50c> ../cstrike/dlls/triggers.cpp:525 */
class CRenderFxManager: public CBaseEntity
{
public:
	virtual void Spawn(void);
	virtual void Use(CBaseEntity *pActivator, CBaseEntity *pCaller, USE_TYPE useType, float value);

#ifdef HOOK_GAMEDLL

	void Spawn_(void);
	void Use_(CBaseEntity *pActivator, CBaseEntity *pCaller, USE_TYPE useType, float value);

#endif // HOOK_GAMEDLL

};/* size: 152, cachelines: 3, members: 1 */

/* <19e55f> ../cstrike/dlls/triggers.cpp:566 */
class CBaseTrigger: public CBaseToggle
{
public:
	virtual void KeyValue(KeyValueData *pkvd);
	virtual int ObjectCaps(void)
	{
		return ObjectCaps_();
	}

#ifdef HOOK_GAMEDLL

	void KeyValue_(KeyValueData *pkvd);
	int ObjectCaps_(void)
	{
		return (CBaseToggle::ObjectCaps() & ~FCAP_ACROSS_TRANSITION);
	}

#endif // HOOK_GAMEDLL

public:
	void EXPORT TeleportTouch(CBaseEntity *pOther);
	void EXPORT MultiTouch(CBaseEntity *pOther);
	void EXPORT HurtTouch(CBaseEntity *pOther);
	NOXREF void EXPORT CDAudioTouch(CBaseEntity *pOther);
	void ActivateMultiTrigger(CBaseEntity *pActivator);
	void EXPORT MultiWaitOver(void);
	void EXPORT CounterUse(CBaseEntity *pActivator, CBaseEntity *pCaller, USE_TYPE useType, float value);
	void EXPORT ToggleUse(CBaseEntity *pActivator, CBaseEntity *pCaller, USE_TYPE useType, float value);
	void InitTrigger(void);

};/* size: 312, cachelines: 5, members: 1 */

// trigger_hurt - hurts anything that touches it. if the trigger has a targetname, firing it will toggle state
// int gfToggleState = 0; // used to determine when all radiation trigger hurts have called 'RadiationThink'

/* <19e5b2> ../cstrike/dlls/triggers.cpp:629 */
class CTriggerHurt: public CBaseTrigger
{
public:
	virtual void Spawn(void);

#ifdef HOOK_GAMEDLL

	void Spawn_(void);

#endif // HOOK_GAMEDLL

	void EXPORT RadiationThink(void);

};/* size: 312, cachelines: 5, members: 1 */

/* <19e60a> ../cstrike/dlls/triggers.cpp:641 */
class CTriggerMonsterJump: public CBaseTrigger
{
public:
	virtual void Spawn(void);
	virtual void Think(void);
	virtual void Touch(CBaseEntity *pOther);

#ifdef HOOK_GAMEDLL

	void Spawn_(void);
	void Think_(void);
	void Touch_(CBaseEntity *pOther);

#endif // HOOK_GAMEDLL

};/* size: 312, cachelines: 5, members: 1 */

// trigger_cdaudio - starts/stops cd audio tracks

/* <19e65d> ../cstrike/dlls/triggers.cpp:705 */
class CTriggerCDAudio: public CBaseTrigger
{
public:
	virtual void Spawn(void);
	virtual void Touch(CBaseEntity *pOther);
	virtual void Use(CBaseEntity *pActivator, CBaseEntity *pCaller, USE_TYPE useType, float value);

#ifdef HOOK_GAMEDLL

	void Spawn_(void);
	void Touch_(CBaseEntity *pOther);
	void Use_(CBaseEntity *pActivator, CBaseEntity *pCaller, USE_TYPE useType, float value);

#endif // HOOK_GAMEDLL

public:
	virtual void PlayTrack(void);

};/* size: 312, cachelines: 5, members: 1 */

// This plays a CD track when fired or when the player enters it's radius

/* <19e6d2> ../cstrike/dlls/triggers.cpp:783 */
class CTargetCDAudio: public CPointEntity
{
public:
	virtual void Spawn(void);
	virtual void KeyValue(KeyValueData *pkvd);
	virtual void Think(void);
	virtual void Use(CBaseEntity *pActivator, CBaseEntity *pCaller, USE_TYPE useType, float value);

#ifdef HOOK_GAMEDLL

	void Spawn_(void);
	void KeyValue_(KeyValueData *pkvd);
	void Think_(void);
	void Use_(CBaseEntity *pActivator, CBaseEntity *pCaller, USE_TYPE useType, float value);

#endif // HOOK_GAMEDLL

public:
	void Play(void);

};/* size: 152, cachelines: 3, members: 1 */

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
	virtual void Spawn(void);

#ifdef HOOK_GAMEDLL

	void Spawn_(void);

#endif // HOOK_GAMEDLL

};/* size: 312, cachelines: 5, members: 1 */

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
	virtual void Spawn(void);

#ifdef HOOK_GAMEDLL

	void Spawn_(void);

#endif // HOOK_GAMEDLL

};/* size: 312, cachelines: 5, members: 1 */

// QUAKED trigger_counter (.5 .5 .5) ? nomessage
// Acts as an intermediary for an action that takes multiple inputs.
// If nomessage is not set, it will print "1 more.. " etc when triggered and
// "sequence complete" when finished.  After the counter has been triggered "cTriggersLeft"
// times (default 2), it will fire all of it's targets and remove itself.

/* <19e7d5> ../cstrike/dlls/triggers.cpp:1273 */
class CTriggerCounter: public CBaseTrigger
{
public:
	virtual void Spawn(void);

#ifdef HOOK_GAMEDLL

	void Spawn_(void);

#endif // HOOK_GAMEDLL

};/* size: 312, cachelines: 5, members: 1 */

// Derive from point entity so this doesn't move across levels

/* <19e82d> ../cstrike/dlls/triggers.cpp:1293 */
class CTriggerVolume: public CPointEntity
{
public:
	virtual void Spawn(void);

#ifdef HOOK_GAMEDLL

	void Spawn_(void);

#endif // HOOK_GAMEDLL

};/* size: 152, cachelines: 3, members: 1 */

// Fires a target after level transition and then dies

/* <19e885> ../cstrike/dlls/triggers.cpp:1313 */
class CFireAndDie: public CBaseDelay
{
public:
	virtual void Spawn(void);
	virtual void Precache(void);
	virtual int ObjectCaps(void)	// Always go across transitions
	{
		return ObjectCaps_();
	}
	virtual void Think(void);

#ifdef HOOK_GAMEDLL

	void Spawn_(void);
	void Precache_(void);
	int ObjectCaps_(void)
	{
		return (CBaseDelay::ObjectCaps() | FCAP_FORCE_TRANSITION);
	}
	void Think_(void);

#endif // HOOK_GAMEDLL

};/* size: 160, cachelines: 3, members: 1 */

// QUAKED trigger_changelevel (0.5 0.5 0.5) ? NO_INTERMISSION
// When the player touches this, he gets sent to the map listed in the "map" variable.  Unless the NO_INTERMISSION flag is set, the view will go to the info_intermission spot and display stats.

/* <19e906> ../cstrike/dlls/triggers.cpp:1345 */
class CChangeLevel: public CBaseTrigger
{
public:
	virtual void Spawn(void);
	virtual void KeyValue(KeyValueData *pkvd);
	virtual int Save(CSave &save);
	virtual int Restore(CRestore &restore);

#ifdef HOOK_GAMEDLL

	void Spawn_(void);
	void KeyValue_(KeyValueData *pkvd);
	int Save_(CSave &save);
	int Restore_(CRestore &restore);

#endif // HOOK_GAMEDLL

public:
	void EXPORT UseChangeLevel(CBaseEntity *pActivator, CBaseEntity *pCaller, USE_TYPE useType, float value);
	NOXREF void EXPORT TriggerChangeLevel(void);
	void EXPORT ExecuteChangeLevel(void);
	void EXPORT TouchChangeLevel(CBaseEntity *pOther);
	void ChangeLevelNow(CBaseEntity *pActivator);

	static edict_t *FindLandmark(const char *pLandmarkName);
	static int ChangeList(LEVELLIST *pLevelList, int maxList);
	static int AddTransitionToList(LEVELLIST *pLevelList, int listCount, const char *pMapName, const char *pLandmarkName, edict_t *pentLandmark);
	static int InTransitionVolume(CBaseEntity *pEntity, char *pVolumeName);

public:
	static TYPEDESCRIPTION IMPLEMENT_ARRAY(m_SaveData)[4];

	char m_szMapName[ cchMapNameMost ];		// trigger_changelevel only:  next map
	char m_szLandmarkName[ cchMapNameMost ];	// trigger_changelevel only:  landmark on next map
	int m_changeTarget;
	float m_changeTargetDelay;

};/* size: 384, cachelines: 6, members: 6 */

/* <19e99d> ../cstrike/dlls/triggers.cpp:1753 */
class CLadder: public CBaseTrigger
{
public:
	virtual void Spawn(void);
	virtual void Precache(void);
	virtual void KeyValue(KeyValueData *pkvd);

#ifdef HOOK_GAMEDLL

	void Spawn_(void);
	void Precache_(void);
	void KeyValue_(KeyValueData *pkvd);

#endif // HOOK_GAMEDLL

};/* size: 312, cachelines: 5, members: 1 */

/* <19e9f5> ../cstrike/dlls/triggers.cpp:1797 */
class CTriggerPush: public CBaseTrigger
{
public:
	virtual void Spawn(void);
	virtual void KeyValue(KeyValueData *pkvd);
	virtual void Touch(CBaseEntity *pOther);

#ifdef HOOK_GAMEDLL

	void Spawn_(void);
	void KeyValue_(KeyValueData *pkvd);
	void Touch_(CBaseEntity *pOther);

#endif // HOOK_GAMEDLL

};/* size: 312, cachelines: 5, members: 1 */

/* <19ea4d> ../cstrike/dlls/triggers.cpp:1935 */
class CTriggerTeleport: public CBaseTrigger
{
public:
	virtual void Spawn(void);

#ifdef HOOK_GAMEDLL

	void Spawn_(void);

#endif // HOOK_GAMEDLL

};/* size: 312, cachelines: 5, members: 1 */

/* <19eadb> ../cstrike/dlls/triggers.cpp:1962 */
class CBuyZone: public CBaseTrigger
{
public:
	virtual void Spawn(void);

#ifdef HOOK_GAMEDLL

	void Spawn_(void);

#endif // HOOK_GAMEDLL

	void EXPORT BuyTouch(CBaseEntity *pOther);

};/* size: 312, cachelines: 5, members: 1 */

/* <19eb2e> ../cstrike/dlls/triggers.cpp:2007 */
class CBombTarget: public CBaseTrigger
{
public:
	virtual void Spawn(void);

#ifdef HOOK_GAMEDLL

	void Spawn_(void);

#endif // HOOK_GAMEDLL

public:
	void EXPORT BombTargetTouch(CBaseEntity *pOther);
	void EXPORT BombTargetUse(CBaseEntity *pActivator, CBaseEntity *pCaller, USE_TYPE useType, float value);

};/* size: 312, cachelines: 5, members: 1 */

/* <19eb81> ../cstrike/dlls/triggers.cpp:2056 */
class CHostageRescue: public CBaseTrigger
{
public:
	virtual void Spawn(void);

#ifdef HOOK_GAMEDLL

	void Spawn_(void);

#endif // HOOK_GAMEDLL

public:
	void EXPORT HostageRescueTouch(CBaseEntity *pOther);

};/* size: 312, cachelines: 5, members: 1 */

/* <19ebd9> ../cstrike/dlls/triggers.cpp:2098 */
class CEscapeZone: public CBaseTrigger
{
public:
	virtual void Spawn(void);

#ifdef HOOK_GAMEDLL

	void Spawn_(void);

#endif // HOOK_GAMEDLL

	void EXPORT EscapeTouch(CBaseEntity *pOther);

};/* size: 312, cachelines: 5, members: 1 */

/* <19ec2c> ../cstrike/dlls/triggers.cpp:2155 */
class CVIP_SafetyZone: public CBaseTrigger
{
public:
	virtual void Spawn(void);

#ifdef HOOK_GAMEDLL

	void Spawn_(void);

#endif // HOOK_GAMEDLL

	void EXPORT VIP_SafetyTouch(CBaseEntity *pOther);

};/* size: 312, cachelines: 5, members: 1 */

/* <19ec7f> ../cstrike/dlls/triggers.cpp:2198 */
class CTriggerSave: public CBaseTrigger
{
public:
	virtual void Spawn(void);

#ifdef HOOK_GAMEDLL

	void Spawn_(void);

#endif // HOOK_GAMEDLL

	void EXPORT SaveTouch(CBaseEntity *pOther);

};/* size: 312, cachelines: 5, members: 1 */

/* <19ecd2> ../cstrike/dlls/triggers.cpp:2234 */
class CTriggerEndSection: public CBaseTrigger
{
public:
	virtual void Spawn(void);
	virtual void KeyValue(KeyValueData *pkvd);

#ifdef HOOK_GAMEDLL

	void Spawn_(void);
	void KeyValue_(KeyValueData *pkvd);

#endif // HOOK_GAMEDLL

public:
	void EXPORT EndSectionTouch(CBaseEntity *pOther);
	void EXPORT EndSectionUse(CBaseEntity *pActivator, CBaseEntity *pCaller, USE_TYPE useType, float value);

};/* size: 312, cachelines: 5, members: 1 */

/* <19ed25> ../cstrike/dlls/triggers.cpp:2305 */
class CTriggerGravity: public CBaseTrigger
{
public:
	virtual void Spawn(void);

#ifdef HOOK_GAMEDLL

	void Spawn_(void);

#endif // HOOK_GAMEDLL

	void EXPORT GravityTouch(CBaseEntity *pOther);

};/* size: 312, cachelines: 5, members: 1 */

// this is a really bad idea.

/* <19ed7d> ../cstrike/dlls/triggers.cpp:2335 */
class CTriggerChangeTarget: public CBaseDelay
{
public:
	virtual void Spawn(void);
	virtual void KeyValue(KeyValueData *pkvd);
	virtual int Save(CSave &save);
	virtual int Restore(CRestore &restore);
	virtual int ObjectCaps(void)
	{
		return ObjectCaps_();
	}
	virtual void Use(CBaseEntity *pActivator, CBaseEntity *pCaller, USE_TYPE useType, float value);

#ifdef HOOK_GAMEDLL

	void Spawn_(void);
	void KeyValue_(KeyValueData *pkvd);
	int Save_(CSave &save);
	int Restore_(CRestore &restore);
	int ObjectCaps_(void)
	{
		return (CBaseEntity::ObjectCaps() & ~FCAP_ACROSS_TRANSITION);
	}
	void Use_(CBaseEntity *pActivator, CBaseEntity *pCaller, USE_TYPE useType, float value);

#endif // HOOK_GAMEDLL

public:
	static TYPEDESCRIPTION IMPLEMENT_ARRAY(m_SaveData)[1];

private:
	int m_iszNewTarget;

};/* size: 164, cachelines: 3, members: 3 */

/* <19edd0> ../cstrike/dlls/triggers.cpp:2391 */
class CTriggerCamera: public CBaseDelay
{
public:
	virtual void Spawn(void);
	virtual void KeyValue(KeyValueData *pkvd);
	virtual int Save(CSave &save);
	virtual int Restore(CRestore &restore);
	virtual int ObjectCaps(void)
	{
		return ObjectCaps_();
	}
	virtual void Use(CBaseEntity *pActivator, CBaseEntity *pCaller, USE_TYPE useType, float value);

#ifdef HOOK_GAMEDLL

	void Spawn_(void);
	void KeyValue_(KeyValueData *pkvd);
	int Save_(CSave &save);
	int Restore_(CRestore &restore);
	int ObjectCaps_(void)
	{
		return (CBaseEntity::ObjectCaps() & ~FCAP_ACROSS_TRANSITION);
	}
	void Use_(CBaseEntity *pActivator, CBaseEntity *pCaller, USE_TYPE useType, float value);

#endif // HOOK_GAMEDLL

public:
	void EXPORT FollowTarget(void);
	void Move(void);

public:
	static TYPEDESCRIPTION IMPLEMENT_ARRAY(m_SaveData)[13];

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

};/* size: 220, cachelines: 4, members: 15 */

/* <19ee23> ../cstrike/dlls/triggers.cpp:2693 */
class CWeather: public CBaseTrigger
{
public:
	virtual void Spawn(void);

#ifdef HOOK_GAMEDLL

	void Spawn_(void);

#endif // HOOK_GAMEDLL

};/* size: 312, cachelines: 5, members: 1 */

/* <1a5b85> ../cstrike/dlls/triggers.cpp:2710 */
class CClientFog: public CBaseEntity
{
public:
	virtual void Spawn(void);
	virtual void KeyValue(KeyValueData *pkvd);

#ifdef HOOK_GAMEDLL

	void Spawn_(void);
	void KeyValue_(KeyValueData *pkvd);

#endif // HOOK_GAMEDLL

public:
	int m_iStartDist;
	int m_iEndDist;
	float m_fDensity;

};/* size: 164, cachelines: 3, members: 4 */

#ifdef HOOK_GAMEDLL

#define st_szNextMap (*pst_szNextMap)
#define st_szNextSpot (*pst_szNextSpot)

#endif // HOOK_GAMEDLL

extern char st_szNextMap[cchMapNameMost];
extern char st_szNextSpot[cchMapNameMost];

void PlayCDTrack(int iTrack);
int BuildChangeList(LEVELLIST * pLevelList, int maxList);
NOXREF void NextLevel(void);

#ifdef HOOK_GAMEDLL

// linked objects
C_DLLEXPORT void func_friction(entvars_t *pev);
C_DLLEXPORT void trigger_auto(entvars_t *pev);
C_DLLEXPORT void trigger_relay(entvars_t *pev);
C_DLLEXPORT void multi_manager(entvars_t *pev);
C_DLLEXPORT void env_render(entvars_t *pev);
C_DLLEXPORT void trigger(entvars_t *pev);
C_DLLEXPORT void trigger_hurt(entvars_t *pev);
C_DLLEXPORT void trigger_monsterjump(entvars_t *pev);
C_DLLEXPORT void trigger_cdaudio(entvars_t *pev);
C_DLLEXPORT void target_cdaudio(entvars_t *pev);
C_DLLEXPORT void trigger_multiple(entvars_t *pev);
C_DLLEXPORT void trigger_once(entvars_t *pev);
C_DLLEXPORT void trigger_counter(entvars_t *pev);
C_DLLEXPORT void trigger_transition(entvars_t *pev);
C_DLLEXPORT void fireanddie(entvars_t *pev);
C_DLLEXPORT void trigger_changelevel(entvars_t *pev);
C_DLLEXPORT void func_ladder(entvars_t *pev);
C_DLLEXPORT void trigger_push(entvars_t *pev);
C_DLLEXPORT void trigger_teleport(entvars_t *pev);
C_DLLEXPORT void info_teleport_destination(entvars_t *pev);
C_DLLEXPORT void func_buyzone(entvars_t *pev);
C_DLLEXPORT void func_bomb_target(entvars_t *pev);
C_DLLEXPORT void func_hostage_rescue(entvars_t *pev);
C_DLLEXPORT void func_escapezone(entvars_t *pev);
C_DLLEXPORT void func_vip_safetyzone(entvars_t *pev);
C_DLLEXPORT void trigger_autosave(entvars_t *pev);
C_DLLEXPORT void trigger_endsection(entvars_t *pev);
C_DLLEXPORT void trigger_gravity(entvars_t *pev);
C_DLLEXPORT void trigger_changetarget(entvars_t *pev);
C_DLLEXPORT void trigger_camera(entvars_t *pev);
C_DLLEXPORT void env_snow(entvars_t *pev);
C_DLLEXPORT void func_snow(entvars_t *pev);
C_DLLEXPORT void env_rain(entvars_t *pev);
C_DLLEXPORT void func_rain(entvars_t *pev);
C_DLLEXPORT void env_fog(entvars_t *pev);

#endif // HOOK_GAMEDLL

#endif // TRIGGERS_H

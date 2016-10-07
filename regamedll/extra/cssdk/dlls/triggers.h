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

#define GRENADETYPE_SMOKE			1
#define GRENADETYPE_FLASH			2

#define MAX_ITEM_COUNTS				32
#define MAX_ENTITY				512	// We can only ever move 512 entities across a transition

// triggers
#define SF_TRIGGER_ALLOWMONSTERS		1	// monsters allowed to fire this trigger
#define SF_TRIGGER_NOCLIENTS			2	// players not allowed to fire this trigger
#define SF_TRIGGER_PUSHABLES			4	// only pushables can fire this trigger
#define SF_TRIGGER_NO_RESET			64	// it is not allowed to be restarted on a new round

#define SF_TRIGGER_PUSH_ONCE			1
#define SF_TRIGGER_PUSH_START_OFF		2	// spawnflag that makes trigger_push spawn turned OFF

#define SF_TRIGGER_HURT_TARGETONCE		1	// Only fire hurt target once
#define SF_TRIGGER_HURT_START_OFF		2	// spawnflag that makes trigger_push spawn turned OFF
#define SF_TRIGGER_HURT_NO_CLIENTS		8	// spawnflag that makes trigger_push spawn turned OFF
#define SF_TRIGGER_HURT_CLIENTONLYFIRE		16	// trigger hurt will only fire its target if it is hurting a client
#define SF_TRIGGER_HURT_CLIENTONLYTOUCH		32	// only clients may touch this trigger.

#define SF_AUTO_FIREONCE			0x0001
#define SF_AUTO_NO_RESET			0x0002

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

class CFrictionModifier: public CBaseEntity {
public:
	virtual void Spawn() = 0;
	virtual void KeyValue(KeyValueData *pkvd) = 0;
	virtual int Save(CSave &save) = 0;
	virtual int Restore(CRestore &restore) = 0;
	virtual int ObjectCaps() = 0;
public:
	float m_frictionFraction;
};

// This trigger will fire when the level spawns (or respawns if not fire once)
// It will check a global state before firing.  It supports delay and killtargets
class CAutoTrigger: public CBaseDelay {
public:
	virtual void Spawn() = 0;
	virtual void Precache() = 0;
	virtual void Restart() = 0;
	virtual void KeyValue(KeyValueData *pkvd) = 0;
	virtual int Save(CSave &save) = 0;
	virtual int Restore(CRestore &restore) = 0;
	virtual int ObjectCaps() = 0;
	virtual void Think() = 0;
public:
	int m_globalstate;
	USE_TYPE triggerType;
};

class CTriggerRelay: public CBaseDelay {
public:
	virtual void Spawn() = 0;
	virtual void KeyValue(KeyValueData *pkvd) = 0;
	virtual int Save(CSave &save) = 0;
	virtual int Restore(CRestore &restore) = 0;
	virtual int ObjectCaps() = 0;
	virtual void Use(CBaseEntity *pActivator, CBaseEntity *pCaller, USE_TYPE useType, float value) = 0;
public:
	USE_TYPE triggerType;
};

// The Multimanager Entity - when fired, will fire up to 16 targets
// at specified times.
// FLAG:		THREAD (create clones when triggered)
// FLAG:		CLONE (this is a clone for a threaded execution)
class CMultiManager: public CBaseToggle {
public:
	virtual void Spawn() = 0;
	virtual void Restart() = 0;
	virtual void KeyValue(KeyValueData *pkvd) = 0;
	virtual int Save(CSave &save) = 0;
	virtual int Restore(CRestore &restore) = 0;
	virtual int ObjectCaps() = 0;
	virtual BOOL HasTarget(string_t targetname) = 0;
public:
	int m_cTargets;
	int m_index;
	float m_startTime;
	int m_iTargetName[MAX_MULTI_TARGETS];
	float m_flTargetDelay[MAX_MULTI_TARGETS];
};

// Render parameters trigger
//
// This entity will copy its render parameters (renderfx, rendermode, rendercolor, renderamt)
// to its targets when triggered.
class CRenderFxManager: public CBaseEntity {
public:
	virtual void Spawn() = 0;
	virtual void Use(CBaseEntity *pActivator, CBaseEntity *pCaller, USE_TYPE useType, float value) = 0;
};

class CBaseTrigger: public CBaseToggle {
public:
	virtual void KeyValue(KeyValueData *pkvd) = 0;
	virtual int ObjectCaps() = 0;
};

// trigger_hurt - hurts anything that touches it. if the trigger has a targetname, firing it will toggle state
// int gfToggleState = 0; // used to determine when all radiation trigger hurts have called 'RadiationThink'
class CTriggerHurt: public CBaseTrigger {
public:
	virtual void Spawn() = 0;
	virtual void Restart() = 0;
	virtual int ObjectCaps() = 0;
};

class CTriggerMonsterJump: public CBaseTrigger {
public:
	virtual void Spawn() = 0;
	virtual void Think() = 0;
	virtual void Touch(CBaseEntity *pOther) = 0;
};

// trigger_cdaudio - starts/stops cd audio tracks
class CTriggerCDAudio: public CBaseTrigger {
public:
	virtual void Spawn() = 0;
	virtual void Touch(CBaseEntity *pOther) = 0;
	virtual void Use(CBaseEntity *pActivator, CBaseEntity *pCaller, USE_TYPE useType, float value) = 0;
};

// This plays a CD track when fired or when the player enters it's radius
class CTargetCDAudio: public CPointEntity {
public:
	virtual void Spawn() = 0;
	virtual void KeyValue(KeyValueData *pkvd) = 0;
	virtual void Think() = 0;
	virtual void Use(CBaseEntity *pActivator, CBaseEntity *pCaller, USE_TYPE useType, float value) = 0;
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
class CTriggerMultiple: public CBaseTrigger {
public:
	virtual void Spawn() = 0;
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
class CTriggerOnce: public CTriggerMultiple {
public:
	virtual void Spawn() = 0;
	virtual void Restart() = 0;
};

// QUAKED trigger_counter (.5 .5 .5) ? nomessage
// Acts as an intermediary for an action that takes multiple inputs.
// If nomessage is not set, it will print "1 more.. " etc when triggered and
// "sequence complete" when finished.  After the counter has been triggered "cTriggersLeft"
// times (default 2), it will fire all of it's targets and remove itself.
class CTriggerCounter: public CBaseTrigger {
public:
	virtual void Spawn() = 0;
};

// Derive from point entity so this doesn't move across levels
class CTriggerVolume: public CPointEntity {
public:
	virtual void Spawn() = 0;
};

// Fires a target after level transition and then dies
class CFireAndDie: public CBaseDelay {
public:
	virtual void Spawn() = 0;
	virtual void Precache() = 0;
	virtual int ObjectCaps() = 0;		// Always go across transitions
	virtual void Think() = 0;
};

// QUAKED trigger_changelevel (0.5 0.5 0.5) ? NO_INTERMISSION
// When the player touches this, he gets sent to the map listed in the "map" variable.  Unless the NO_INTERMISSION flag is set, the view will go to the info_intermission spot and display stats.
class CChangeLevel: public CBaseTrigger {
public:
	virtual void Spawn() = 0;
	virtual void KeyValue(KeyValueData *pkvd) = 0;
	virtual int Save(CSave &save) = 0;
	virtual int Restore(CRestore &restore) = 0;
public:
	char m_szMapName[cchMapNameMost];		// trigger_changelevel only:  next map
	char m_szLandmarkName[cchMapNameMost];		// trigger_changelevel only:  landmark on next map
	int m_changeTarget;
	float m_changeTargetDelay;
};

class CLadder: public CBaseTrigger {
public:
	virtual void Spawn() = 0;
	virtual void Precache() = 0;
	virtual void KeyValue(KeyValueData *pkvd) = 0;
};

class CTriggerPush: public CBaseTrigger {
public:
	virtual void Spawn() = 0;
	virtual void KeyValue(KeyValueData *pkvd) = 0;
	virtual void Touch(CBaseEntity *pOther) = 0;
};

class CTriggerTeleport: public CBaseTrigger {
public:
	virtual void Spawn() = 0;
};

class CBuyZone: public CBaseTrigger {
public:
	virtual void Spawn() = 0;
};

class CBombTarget: public CBaseTrigger {
public:
	virtual void Spawn() = 0;
};

class CHostageRescue: public CBaseTrigger {
public:
	virtual void Spawn() = 0;
};

class CEscapeZone: public CBaseTrigger {
public:
	virtual void Spawn() = 0;
};

class CVIP_SafetyZone: public CBaseTrigger {
public:
	virtual void Spawn() = 0;
};

class CTriggerSave: public CBaseTrigger {
public:
	virtual void Spawn() = 0;
};

class CTriggerEndSection: public CBaseTrigger {
public:
	virtual void Spawn() = 0;
	virtual void KeyValue(KeyValueData *pkvd) = 0;
};

class CTriggerGravity: public CBaseTrigger {
public:
	virtual void Spawn() = 0;
};

// this is a really bad idea.
class CTriggerChangeTarget: public CBaseDelay {
public:
	virtual void Spawn() = 0;
	virtual void KeyValue(KeyValueData *pkvd) = 0;
	virtual int Save(CSave &save) = 0;
	virtual int Restore(CRestore &restore) = 0;
	virtual int ObjectCaps() = 0;
	virtual void Use(CBaseEntity *pActivator, CBaseEntity *pCaller, USE_TYPE useType, float value) = 0;
private:
	int m_iszNewTarget;
};

class CTriggerCamera: public CBaseDelay {
public:
	virtual void Spawn() = 0;
	virtual void KeyValue(KeyValueData *pkvd) = 0;
	virtual int Save(CSave &save) = 0;
	virtual int Restore(CRestore &restore) = 0;
	virtual int ObjectCaps() = 0;
	virtual void Use(CBaseEntity *pActivator, CBaseEntity *pCaller, USE_TYPE useType, float value) = 0;
public:
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

class CWeather: public CBaseTrigger {
public:
	virtual void Spawn() = 0;
};

class CClientFog: public CBaseEntity {
public:
	virtual void Spawn() = 0;
	virtual void KeyValue(KeyValueData *pkvd) = 0;
public:
	int m_iStartDist;
	int m_iEndDist;
	float m_fDensity;
};

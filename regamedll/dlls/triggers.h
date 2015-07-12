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

#define savesolid team

#define GRENADETYPE_SMOKE 1
#define GRENADETYPE_FLASH 2

#define MAX_ITEM_COUNTS 32

#define SF_TRIGGER_PUSH_START_OFF 2
#define SF_TRIGGER_HURT_TARGETONCE 1
#define SF_TRIGGER_HURT_START_OFF 2
#define SF_TRIGGER_HURT_NO_CLIENTS 8
#define SF_TRIGGER_HURT_CLIENTONLYFIRE 16
#define SF_TRIGGER_HURT_CLIENTONLYTOUCH 32

#define SF_AUTO_FIREONCE 0x0001
#define SF_RELAY_FIREONCE 0x0001

#define SF_MULTIMAN_CLONE 0x80000000
#define SF_MULTIMAN_THREAD 0x00000001

#define SF_CHANGELEVEL_USEONLY 0x0002

#define MAX_ENTITY 512

#define SF_CAMERA_PLAYER_POSITION 1
#define SF_CAMERA_PLAYER_TARGET 2
#define SF_CAMERA_PLAYER_TAKECONTROL 4

class CFrictionModifier: public CBaseEntity
{
public:
	NOBODY virtual void Spawn(void);
	NOBODY virtual void KeyValue(KeyValueData *pkvd);
	NOBODY virtual int Save(CSave &save);
	NOBODY virtual int Restore(CRestore &restore);
	NOBODY virtual int ObjectCaps(void)
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
	NOBODY void EXPORT ChangeFriction(CBaseEntity *pOther);

public:
	static TYPEDESCRIPTION IMPLEMENT_ARRAY(m_SaveData)[1];

	float m_frictionFraction;

};/* size: 156, cachelines: 3, members: 3 */

/* <19e39c> ../cstrike/dlls/triggers.cpp:108 */
class CAutoTrigger: public CBaseDelay
{
public:
	NOBODY virtual void Spawn(void);
	NOBODY virtual void Precache(void);
	NOBODY virtual void KeyValue(KeyValueData *pkvd);
	NOBODY virtual int Save(CSave &save);
	NOBODY virtual int Restore(CRestore &restore);
	NOBODY virtual int ObjectCaps(void)
	{
		return ObjectCaps_();
	}
	NOBODY virtual void Think(void);

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

	int m_globalstate; // 160
	USE_TYPE triggerType; // 164

};/* size: 168, cachelines: 3, members: 4 */

/* <19e3ed> ../cstrike/dlls/triggers.cpp:191 */
class CTriggerRelay: public CBaseDelay
{
public:
	NOBODY virtual void Spawn(void);
	NOBODY virtual void KeyValue(KeyValueData *pkvd);
	NOBODY virtual int Save(CSave &save);
	NOBODY virtual int Restore(CRestore &restore);
	NOBODY virtual int ObjectCaps(void)
	{
		return ObjectCaps_();
	}
	NOBODY virtual void Use(CBaseEntity *pActivator, CBaseEntity *pCaller, USE_TYPE useType, float value);
public:

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

/* <19e4d6> ../cstrike/dlls/triggers.cpp:264 */
class CMultiManager: public CBaseToggle
{
public:
	NOBODY virtual void Spawn(void);
	NOBODY virtual void Restart(void);
	NOBODY virtual void KeyValue(KeyValueData *pkvd);
	NOBODY virtual int Save(CSave &save);
	NOBODY virtual int Restore(CRestore &restore);
	NOBODY virtual int ObjectCaps(void)
	{
		return ObjectCaps_();
	}
	NOBODY virtual BOOL HasTarget(string_t targetname);
public:

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

	NOBODY void EXPORT ManagerThink(void);
	NOBODY void EXPORT ManagerUse(CBaseEntity *pActivator, CBaseEntity *pCaller, USE_TYPE useType, float value);

private:
	/* <19dfe1> ../cstrike/dlls/triggers.cpp:293 */
	inline BOOL IsClone(void)
	{
		if (pev->spawnflags & SF_MULTIMAN_CLONE)
			return TRUE;
		return FALSE;
	}
	/* <19e4f3> ../cstrike/dlls/triggers.cpp:294 */
	inline BOOL ShouldClone(void)
	{
		if (IsClone())
			return FALSE;
		if (pev->spawnflags & SF_MULTIMAN_THREAD)
			return TRUE;
		return FALSE;
	}
	NOBODY CMultiManager *Clone(void);

public:
	static TYPEDESCRIPTION IMPLEMENT_ARRAY(m_SaveData)[5];

	int m_cTargets;//312
	int m_index;
	float m_startTime;
	int m_iTargetName[ MAX_MULTI_TARGETS ];
	float m_flTargetDelay[ MAX_MULTI_TARGETS ];

};/* size: 452, cachelines: 8, members: 7 */
/* Linux - 452 | Windows - 432 */

/* <19e50c> ../cstrike/dlls/triggers.cpp:525 */
class CRenderFxManager: public CBaseEntity
{
public:
	NOBODY virtual void Spawn(void);
	NOBODY virtual void Use(CBaseEntity *pActivator, CBaseEntity *pCaller, USE_TYPE useType, float value);

#ifdef HOOK_GAMEDLL

	void Spawn_(void);
	void Use_(CBaseEntity *pActivator, CBaseEntity *pCaller, USE_TYPE useType, float value);

#endif // HOOK_GAMEDLL

};/* size: 152, cachelines: 3, members: 1 */

/* <19e55f> ../cstrike/dlls/triggers.cpp:566 */
class CBaseTrigger: public CBaseToggle
{
public:
	NOBODY virtual void KeyValue(KeyValueData *pkvd);
	NOBODY virtual int ObjectCaps(void)
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
	NOBODY void EXPORT TeleportTouch(CBaseEntity *pOther);
	NOBODY void EXPORT MultiTouch(CBaseEntity *pOther);
	NOBODY void EXPORT HurtTouch(CBaseEntity *pOther);
	NOXREF NOBODY void EXPORT CDAudioTouch(CBaseEntity *pOther);
	NOBODY void ActivateMultiTrigger(CBaseEntity *pActivator);
	NOBODY void EXPORT MultiWaitOver(void);
	NOBODY void EXPORT CounterUse(CBaseEntity *pActivator, CBaseEntity *pCaller, USE_TYPE useType, float value);
	NOBODY void EXPORT ToggleUse(CBaseEntity *pActivator, CBaseEntity *pCaller, USE_TYPE useType, float value);
	NOBODY void InitTrigger(void);

};/* size: 312, cachelines: 5, members: 1 */

/* <19e5b2> ../cstrike/dlls/triggers.cpp:629 */
class CTriggerHurt: public CBaseTrigger
{
public:
	NOBODY virtual void Spawn(void);

#ifdef HOOK_GAMEDLL

	void Spawn_(void);

#endif // HOOK_GAMEDLL

	NOBODY void EXPORT RadiationThink(void);

};/* size: 312, cachelines: 5, members: 1 */

/* <19e60a> ../cstrike/dlls/triggers.cpp:641 */
class CTriggerMonsterJump: public CBaseTrigger
{
public:
	NOBODY virtual void Spawn(void);
	NOBODY virtual void Think(void);
	NOBODY virtual void Touch(CBaseEntity *pOther);

#ifdef HOOK_GAMEDLL

	void Spawn_(void);
	void Think_(void);
	void Touch_(CBaseEntity *pOther);

#endif // HOOK_GAMEDLL

};/* size: 312, cachelines: 5, members: 1 */

/* <19e65d> ../cstrike/dlls/triggers.cpp:705 */
class CTriggerCDAudio: public CBaseTrigger
{
public:
	NOBODY virtual void Spawn(void);
	NOBODY virtual void Touch(CBaseEntity *pOther);
	NOBODY virtual void Use(CBaseEntity *pActivator, CBaseEntity *pCaller, USE_TYPE useType, float value);

#ifdef HOOK_GAMEDLL

	void Spawn_(void);
	void Touch_(CBaseEntity *pOther);
	void Use_(CBaseEntity *pActivator, CBaseEntity *pCaller, USE_TYPE useType, float value);

#endif // HOOK_GAMEDLL

public:
	NOBODY virtual void PlayTrack(void);

};/* size: 312, cachelines: 5, members: 1 */

/* <19e6d2> ../cstrike/dlls/triggers.cpp:783 */
class CTargetCDAudio: public CPointEntity
{
public:
	NOBODY virtual void Spawn(void);
	NOBODY virtual void KeyValue(KeyValueData *pkvd);
	NOBODY virtual void Think(void);
	NOBODY virtual void Use(CBaseEntity *pActivator, CBaseEntity *pCaller, USE_TYPE useType, float value);

#ifdef HOOK_GAMEDLL

	void Spawn_(void);
	void KeyValue_(KeyValueData *pkvd);
	void Think_(void);
	void Use_(CBaseEntity *pActivator, CBaseEntity *pCaller, USE_TYPE useType, float value);

#endif // HOOK_GAMEDLL

public:
	NOBODY void Play(void);

};/* size: 152, cachelines: 3, members: 1 */

/* <19e725> ../cstrike/dlls/triggers.cpp:1080 */
class CTriggerMultiple: public CBaseTrigger
{
public:
	NOBODY virtual void Spawn(void);

#ifdef HOOK_GAMEDLL

	void Spawn_(void);

#endif // HOOK_GAMEDLL

};/* size: 312, cachelines: 5, members: 1 */

/* <19e77d> ../cstrike/dlls/triggers.cpp:1129 */
class CTriggerOnce: public CTriggerMultiple
{
public:
	NOBODY virtual void Spawn(void);

#ifdef HOOK_GAMEDLL

	void Spawn_(void);

#endif // HOOK_GAMEDLL

};/* size: 312, cachelines: 5, members: 1 */

/* <19e7d5> ../cstrike/dlls/triggers.cpp:1273 */
class CTriggerCounter: public CBaseTrigger
{
public:
	NOBODY virtual void Spawn(void);

#ifdef HOOK_GAMEDLL

	void Spawn_(void);

#endif // HOOK_GAMEDLL

};/* size: 312, cachelines: 5, members: 1 */

/* <19e82d> ../cstrike/dlls/triggers.cpp:1293 */
class CTriggerVolume: public CPointEntity
{
public:
	NOBODY virtual void Spawn(void);

#ifdef HOOK_GAMEDLL

	void Spawn_(void);

#endif // HOOK_GAMEDLL

};/* size: 152, cachelines: 3, members: 1 */

/* <19e885> ../cstrike/dlls/triggers.cpp:1313 */
class CFireAndDie: public CBaseDelay
{
public:
	NOBODY virtual void Spawn(void);
	NOBODY virtual void Precache(void);
	NOBODY virtual int ObjectCaps(void)
	{
		return ObjectCaps_();
	}
	NOBODY virtual void Think(void);

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

/* <19e906> ../cstrike/dlls/triggers.cpp:1345 */
class CChangeLevel: public CBaseTrigger
{
public:
	NOBODY virtual void Spawn(void);
	NOBODY virtual void KeyValue(KeyValueData *pkvd);
	NOBODY virtual int Save(CSave &save);
	NOBODY virtual int Restore(CRestore &restore);

#ifdef HOOK_GAMEDLL

	void Spawn_(void);
	void KeyValue_(KeyValueData *pkvd);
	int Save_(CSave &save);
	int Restore_(CRestore &restore);

#endif // HOOK_GAMEDLL

public:
	NOBODY void EXPORT UseChangeLevel(CBaseEntity *pActivator, CBaseEntity *pCaller, USE_TYPE useType, float value);
	NOXREF NOBODY void EXPORT TriggerChangeLevel(void);
	NOBODY void EXPORT ExecuteChangeLevel(void);
	NOBODY void EXPORT TouchChangeLevel(CBaseEntity *pOther);

	NOBODY void ChangeLevelNow(CBaseEntity *pActivator);

	NOXREF static edict_t *FindLandmark(const char *pLandmarkName);
	NOBODY static int ChangeList(LEVELLIST *pLevelList, int maxList);
	NOBODY static int AddTransitionToList(LEVELLIST *pLevelList, int listCount, const char *pMapName, const char *pLandmarkName, edict_t *pentLandmark);
	NOBODY static int InTransitionVolume(CBaseEntity *pEntity, char *pVolumeName);

public:
	static TYPEDESCRIPTION IMPLEMENT_ARRAY(m_SaveData)[4];

	char m_szMapName[ cchMapNameMost ];
	char m_szLandmarkName[ cchMapNameMost ];
	int m_changeTarget;
	float m_changeTargetDelay;

};/* size: 384, cachelines: 6, members: 6 */

/* <19e99d> ../cstrike/dlls/triggers.cpp:1753 */
class CLadder: public CBaseTrigger
{
public:
	NOBODY virtual void Spawn(void);
	NOBODY virtual void Precache(void);
	NOBODY virtual void KeyValue(KeyValueData *pkvd);

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
	NOBODY virtual void Spawn(void);
	NOBODY virtual void KeyValue(KeyValueData *pkvd);
	NOBODY virtual void Touch(CBaseEntity *pOther);

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
	NOBODY virtual void Spawn(void);

#ifdef HOOK_GAMEDLL

	void Spawn_(void);

#endif // HOOK_GAMEDLL

};/* size: 312, cachelines: 5, members: 1 */

/* <19eadb> ../cstrike/dlls/triggers.cpp:1962 */
class CBuyZone: public CBaseTrigger
{
public:
	NOBODY virtual void Spawn(void);

#ifdef HOOK_GAMEDLL

	void Spawn_(void);

#endif // HOOK_GAMEDLL

	NOBODY void EXPORT BuyTouch(CBaseEntity *pOther);

};/* size: 312, cachelines: 5, members: 1 */

/* <19eb2e> ../cstrike/dlls/triggers.cpp:2007 */
class CBombTarget: public CBaseTrigger
{
public:
	NOBODY virtual void Spawn(void);

#ifdef HOOK_GAMEDLL

	void Spawn_(void);

#endif // HOOK_GAMEDLL

public:
	NOBODY void EXPORT BombTargetTouch(CBaseEntity *pOther);
	NOBODY void EXPORT BombTargetUse(CBaseEntity *pActivator, CBaseEntity *pCaller, USE_TYPE useType, float value);

};/* size: 312, cachelines: 5, members: 1 */

/* <19eb81> ../cstrike/dlls/triggers.cpp:2056 */
class CHostageRescue: public CBaseTrigger
{
public:
	NOBODY virtual void Spawn(void);

#ifdef HOOK_GAMEDLL

	void Spawn_(void);

#endif // HOOK_GAMEDLL

public:
	NOBODY void EXPORT HostageRescueTouch(CBaseEntity *pOther);

};/* size: 312, cachelines: 5, members: 1 */

/* <19ebd9> ../cstrike/dlls/triggers.cpp:2098 */
class CEscapeZone: public CBaseTrigger
{
public:
	NOBODY virtual void Spawn(void);

#ifdef HOOK_GAMEDLL

	void Spawn_(void);

#endif // HOOK_GAMEDLL

	NOBODY void EXPORT EscapeTouch(CBaseEntity *pOther);

};/* size: 312, cachelines: 5, members: 1 */

/* <19ec2c> ../cstrike/dlls/triggers.cpp:2155 */
class CVIP_SafetyZone: public CBaseTrigger
{
public:
	NOBODY virtual void Spawn(void);

#ifdef HOOK_GAMEDLL

	void Spawn_(void);

#endif // HOOK_GAMEDLL

	NOBODY void EXPORT VIP_SafetyTouch(CBaseEntity *pOther);

};/* size: 312, cachelines: 5, members: 1 */

/* <19ec7f> ../cstrike/dlls/triggers.cpp:2198 */
class CTriggerSave: public CBaseTrigger
{
public:
	NOBODY virtual void Spawn(void);

#ifdef HOOK_GAMEDLL

	void Spawn_(void);

#endif // HOOK_GAMEDLL

	NOBODY void EXPORT SaveTouch(CBaseEntity *pOther);

};/* size: 312, cachelines: 5, members: 1 */

/* <19ecd2> ../cstrike/dlls/triggers.cpp:2234 */
class CTriggerEndSection: public CBaseTrigger
{
public:
	NOBODY virtual void Spawn(void);
	NOBODY virtual void KeyValue(KeyValueData *pkvd);

#ifdef HOOK_GAMEDLL

	void Spawn_(void);
	void KeyValue_(KeyValueData *pkvd);

#endif // HOOK_GAMEDLL

public:
	NOBODY void EXPORT EndSectionTouch(CBaseEntity *pOther);
	NOBODY void EXPORT EndSectionUse(CBaseEntity *pActivator, CBaseEntity *pCaller, USE_TYPE useType, float value);
};/* size: 312, cachelines: 5, members: 1 */


/* <19ed25> ../cstrike/dlls/triggers.cpp:2305 */
class CTriggerGravity: public CBaseTrigger
{
public:
	NOBODY virtual void Spawn(void);

#ifdef HOOK_GAMEDLL

	void Spawn_(void);

#endif // HOOK_GAMEDLL

	NOBODY void EXPORT GravityTouch(CBaseEntity *pOther);

};/* size: 312, cachelines: 5, members: 1 */

/* <19ed7d> ../cstrike/dlls/triggers.cpp:2335 */
class CTriggerChangeTarget: public CBaseDelay
{
public:
	NOBODY virtual void Spawn(void);
	NOBODY virtual void KeyValue(KeyValueData *pkvd);
	NOBODY virtual int Save(CSave &save);
	NOBODY virtual int Restore(CRestore &restore);
	virtual int ObjectCaps(void)
	{
		return (CBaseDelay::ObjectCaps() & ~FCAP_ACROSS_TRANSITION);
	}
	NOBODY virtual void Use(CBaseEntity *pActivator, CBaseEntity *pCaller, USE_TYPE useType, float value);

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
	NOBODY virtual void Spawn(void);
	NOBODY virtual void KeyValue(KeyValueData *pkvd);
	NOBODY virtual int Save(CSave &save);
	NOBODY virtual int Restore(CRestore &restore);
	NOBODY virtual int ObjectCaps(void)
	{
		return ObjectCaps_();
	}
	NOBODY virtual void Use(CBaseEntity *pActivator, CBaseEntity *pCaller, USE_TYPE useType, float value);

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
	NOBODY void EXPORT FollowTarget(void);
	NOBODY void Move(void);

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
	NOBODY virtual void Spawn(void)
	{
		Spawn_();
	}

#ifdef HOOK_GAMEDLL
	void Spawn_(void)
	{
		InitTrigger();
	}
#endif // HOOK_GAMEDLL

};/* size: 312, cachelines: 5, members: 1 */

/* <1a5b85> ../cstrike/dlls/triggers.cpp:2710 */
class CClientFog: public CBaseEntity
{
public:
	NOBODY virtual void Spawn(void);
	NOBODY virtual void KeyValue(KeyValueData *pkvd);

#ifdef HOOK_GAMEDLL

	void Spawn_(void);
	void KeyValue_(KeyValueData *pkvd);

#endif // HOOK_GAMEDLL

public:
	int m_iStartDist;
	int m_iEndDist;
	float m_fDensity;

};/* size: 164, cachelines: 3, members: 4 */

NOBODY void PlayCDTrack(int iTrack);
NOBODY int BuildChangeList(LEVELLIST * pLevelList, int maxList);
NOBODY void NextLevel(void);

#endif // TRIGGERS_H

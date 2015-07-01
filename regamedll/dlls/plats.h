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

#ifndef PLATS_H
#define PLATS_H
#ifdef _WIN32
#pragma once
#endif

#define SF_PLAT_TOGGLE		0x0001

#define TRAIN_STARTPITCH	60
#define TRAIN_MAXPITCH		200
#define TRAIN_MAXSPEED		1000

#define SF_TRACK_ACTIVATETRAIN	0x00000001
#define SF_TRACK_RELINK		0x00000002
#define SF_TRACK_ROTMOVE	0x00000004
#define SF_TRACK_STARTBOTTOM	0x00000008
#define SF_TRACK_DONT_MOVE	0x00000010

#define FGUNTARGET_START_ON	0x0001

/* <12c817> ../cstrike/dlls/plats.cpp:33 */
class CBasePlatTrain: public CBaseToggle
{
public:
	NOBODY virtual void Precache(void);
	NOBODY virtual void KeyValue(KeyValueData *pkvd);
	NOBODY virtual int Save(CSave &save);
	NOBODY virtual int Restore(CRestore &restore);
	NOBODY virtual int ObjectCaps(void)
	{
		return ObjectCaps_();
	}

	// This is done to fix spawn flag collisions between this class and a derived class
	NOBODY virtual BOOL IsTogglePlat(void)
	{
		return IsTogglePlat_();
	}

#ifdef HOOK_GAMEDLL

	void Precache_(void);
	void KeyValue_(KeyValueData *pkvd);
	int Save_(CSave &save);
	int Restore_(CRestore &restore);
	int ObjectCaps_(void)
	{
		return CBaseEntity::ObjectCaps() & ~FCAP_ACROSS_TRANSITION;
	}
	BOOL IsTogglePlat_(void)
	{
		return (pev->spawnflags & SF_PLAT_TOGGLE) != 0;
	}

#endif // HOOK_GAMEDLL

public:
#ifndef HOOK_GAMEDLL
	static TYPEDESCRIPTION m_SaveData[3];
#else // HOOK_GAMEDLL
	static TYPEDESCRIPTION (*m_SaveData)[3];
#endif // HOOK_GAMEDLL

public:
	BYTE m_bMoveSnd;
	BYTE m_bStopSnd;
	float m_volume;

};/* size: 320, cachelines: 5, members: 5 */

/* <12c853> ../cstrike/dlls/plats.cpp:223 */
class CFuncPlat: public CBasePlatTrain
{
public:
	NOBODY virtual void Spawn(void);
	NOBODY virtual void Precache(void);
	NOBODY virtual void Blocked(CBaseEntity *pOther);
	NOBODY virtual void GoUp(void);
	NOBODY virtual void GoDown(void);
	NOBODY virtual void HitTop(void);
	NOBODY virtual void HitBottom(void);

#ifdef HOOK_GAMEDLL

	void Spawn_(void);
	void Precache_(void);
	void Blocked_(CBaseEntity *pOther);
	void GoUp_(void);
	void GoDown_(void);
	void HitTop_(void);
	void HitBottom_(void);

#endif // HOOK_GAMEDLL

public:
	void Setup(void);

public:
	void EXPORT PlatUse(CBaseEntity *pActivator, CBaseEntity *pCaller, USE_TYPE useType, float value);
	void EXPORT CallGoDown(void);
	void EXPORT CallHitTop(void);
	void EXPORT CallHitBottom(void);

};/* size: 320, cachelines: 5, members: 1 */

/* <12c86e> ../cstrike/dlls/plats.cpp:248 */
class CPlatTrigger: public CBaseEntity
{
public:
	NOBODY virtual int ObjectCaps(void)
	{
		return ObjectCaps_();
	}
	NOBODY virtual void Touch(CBaseEntity *pOther);

#ifdef HOOK_GAMEDLL

	int ObjectCaps_(void)
	{
		return (CBaseEntity::ObjectCaps() & ~FCAP_ACROSS_TRANSITION) | FCAP_DONT_SAVE;
	}
	void Touch_(CBaseEntity *pOther);

#endif // HOOK_GAMEDLL

public:
	NOBODY void SpawnInsideTrigger(CFuncPlat *pPlatform);

public:
	CFuncPlat *m_pPlatform;

};/* size: 156, cachelines: 3, members: 2 */

/* <12c8ee> ../cstrike/dlls/plats.cpp:515 */
class CFuncPlatRot: public CFuncPlat
{
public:
	NOBODY virtual void Spawn(void);
	NOBODY virtual int Save(CSave &save);
	NOBODY virtual int Restore(CRestore &restore);

	NOBODY virtual void GoUp(void);
	NOBODY virtual void GoDown(void);
	NOBODY virtual void HitTop(void);
	NOBODY virtual void HitBottom(void);

#ifdef HOOK_GAMEDLL

	void Spawn_(void);
	int Save_(CSave &save);
	int Restore_(CRestore &restore);
	void GoUp_(void);
	void GoDown_(void);
	void HitTop_(void);
	void HitBottom_(void);

#endif // HOOK_GAMEDLL

public:
	NOBODY void SetupRotation(void);
	NOBODY void RotMove(Vector &destAngle, float time);
	
public:
#ifndef HOOK_GAMEDLL
	static TYPEDESCRIPTION m_SaveData[2];
#else // HOOK_GAMEDLL
	static TYPEDESCRIPTION (*m_SaveData)[2];
#endif // HOOK_GAMEDLL

public:
	Vector m_end;
	Vector m_start;

};/* size: 344, cachelines: 6, members: 4 */

/* <12c93c> ../cstrike/dlls/plats.cpp:628 */
class CFuncTrain: public CBasePlatTrain
{
public:
	NOBODY virtual void Spawn(void);
	NOBODY virtual void Precache(void);
	NOBODY virtual void Restart(void);
	NOBODY virtual void KeyValue(KeyValueData *pkvd);
	NOBODY virtual int Save(CSave &save);
	NOBODY virtual int Restore(CRestore &restore);
	NOBODY virtual void Activate(void);
	NOBODY virtual void OverrideReset(void);
	NOBODY virtual void Use(CBaseEntity *pActivator, CBaseEntity *pCaller, USE_TYPE useType, float value);
	NOBODY virtual void Blocked(CBaseEntity *pOther);

#ifdef HOOK_GAMEDLL

	void Spawn_(void);
	void Precache_(void);
	void Restart_(void);
	void KeyValue_(KeyValueData *pkvd);
	int Save_(CSave &save);
	int Restore_(CRestore &restore);
	void Activate_(void);
	void OverrideReset_(void);
	void Use_(CBaseEntity *pActivator, CBaseEntity *pCaller, USE_TYPE useType, float value);
	void Blocked_(CBaseEntity *pOther);

#endif // HOOK_GAMEDLL

public:
	void EXPORT Wait(void);
	void EXPORT Next(void);

public:
#ifndef HOOK_GAMEDLL
	static TYPEDESCRIPTION m_SaveData[3];
#else // HOOK_GAMEDLL
	static TYPEDESCRIPTION (*m_SaveData)[3];
#endif // HOOK_GAMEDLL

public:
	Vector m_vStartPosition;
	entvars_t *m_pevFirstTarget;
	entvars_t *m_pevCurrentTarget;
	int m_sounds;
	BOOL m_activated;

};/* size: 348, cachelines: 6, members: 7 */

/* <12c9d7> ../cstrike/dlls/plats.cpp:1588 */
class CFuncTrainControls: public CBaseEntity
{
public:
	NOBODY virtual void Spawn(void);
	NOBODY virtual int ObjectCaps(void)
	{
		return ObjectCaps_();
	}

#ifdef HOOK_GAMEDLL

	void Spawn_(void);
	int ObjectCaps_(void)
	{
		return CBaseEntity::ObjectCaps() & ~FCAP_ACROSS_TRANSITION;
	}

#endif // HOOK_GAMEDLL

public:
	void EXPORT Find(void);

};/* size: 152, cachelines: 3, members: 1 */

/* <12ca2a> ../cstrike/dlls/plats.cpp:1654 */
class CFuncTrackChange: public CFuncPlatRot
{
public:
	NOBODY virtual void Spawn(void);
	NOBODY virtual void Precache(void);
	NOBODY virtual void KeyValue(KeyValueData *pkvd);
	NOBODY virtual int Save(CSave &save);
	NOBODY virtual int Restore(CRestore &restore);
	NOBODY virtual void OverrideReset(void);
	NOBODY virtual void Touch(CBaseEntity *pOther);
	NOBODY virtual void Use(CBaseEntity *pActivator, CBaseEntity *pCaller, USE_TYPE useType, float value);
	NOBODY virtual BOOL IsTogglePlat(void);

	NOBODY virtual void EXPORT GoUp(void);
	NOBODY virtual void EXPORT GoDown(void);
	
	NOBODY virtual void HitBottom(void);
	NOBODY virtual void HitTop(void);
	NOBODY virtual void UpdateAutoTargets(int toggleState);

#ifdef HOOK_GAMEDLL

	void Spawn_(void);
	void Precache_(void);
	void KeyValue_(KeyValueData *pkvd);
	int Save_(CSave &save);
	int Restore_(CRestore &restore);
	void OverrideReset_(void);
	void Touch_(CBaseEntity *pOther);
	void Use_(CBaseEntity *pActivator, CBaseEntity *pCaller, USE_TYPE useType, float value);
	BOOL IsTogglePlat_(void);
	void GoUp_(void);
	void GoDown_(void);
	void HitBottom_(void);
	void HitTop_(void);
	void UpdateAutoTargets_(int toggleState);

#endif // HOOK_GAMEDLL
	
public:
	NOBODY void EXPORT Find(void);
	NOBODY TRAIN_CODE EvaluateTrain(CPathTrack *pcurrent);
	NOBODY void UpdateTrain(Vector &dest);

	/* <12c515> ../cstrike/dlls/plats.cpp:1675 */
	NOBODY void DisableUse(void)
	{
		m_use = 0;
	}
	/* <12c52e> ../cstrike/dlls/plats.cpp:1676 */
	NOBODY void EnableUse(void)
	{
		m_use = 1;
	}
	/* <12c547> ../cstrike/dlls/plats.cpp:1677 */
	NOBODY int UseEnabled(void)
	{
		return m_use;
	}

public:
#ifndef HOOK_GAMEDLL
	static TYPEDESCRIPTION m_SaveData[9];
#else // HOOK_GAMEDLL
	static TYPEDESCRIPTION (*m_SaveData)[9];
#endif // HOOK_GAMEDLL

public:
	CPathTrack *m_trackTop;
	CPathTrack *m_trackBottom;
	CFuncTrackTrain *m_train;

	int m_trackTopName;
	int m_trackBottomName;
	int m_trainName;

	TRAIN_CODE m_code;
	int m_targetState;
	int m_use;

};/* size: 380, cachelines: 6, members: 11 */

/* <12ca78> ../cstrike/dlls/plats.cpp:2043 */
class CFuncTrackAuto: public CFuncTrackChange
{
public:
	NOBODY virtual void Use(CBaseEntity *pActivator, CBaseEntity *pCaller, USE_TYPE useType, float value);
	NOBODY virtual void UpdateAutoTargets(int toggleState);

#ifdef HOOK_GAMEDLL

	void Use_(CBaseEntity *pActivator, CBaseEntity *pCaller, USE_TYPE useType, float value);
	void UpdateAutoTargets_(int toggleState);

#endif // HOOK_GAMEDLL


};/* size: 380, cachelines: 6, members: 1 */

/* <12caec> ../cstrike/dlls/plats.cpp:2136 */
class CGunTarget: public CBaseMonster
{
public:
	NOBODY virtual void Spawn(void);
	NOBODY virtual int Save(CSave &save);
	NOBODY virtual int Restore(CRestore &restore);
	NOBODY virtual int ObjectCaps(void)
	{
		return ObjectCaps_();
	}
	NOBODY virtual void Activate(void);
	NOBODY virtual int Classify(void)
	{
		return Classify_();
	}
	NOBODY virtual int TakeDamage(entvars_t *pevInflictor, entvars_t *pevAttacker, float flDamage, int bitsDamageType);
	NOBODY virtual int BloodColor(void)
	{
		return BloodColor_();
	}
	NOBODY virtual void Use(CBaseEntity *pActivator, CBaseEntity *pCaller, USE_TYPE useType, float value);
	NOBODY virtual Vector BodyTarget(const Vector &posSrc)
	{
		return BodyTarget_(posSrc);
	}

#ifdef HOOK_GAMEDLL

	void Spawn_(void);
	int Save_(CSave &save);
	int Restore_(CRestore &restore);
	int ObjectCaps_(void)
	{
		return CBaseEntity::ObjectCaps() & ~FCAP_ACROSS_TRANSITION;
	}
	void Activate_(void);
	int Classify_(void)
	{
		return CLASS_MACHINE;
	}
	int TakeDamage_(entvars_t *pevInflictor, entvars_t *pevAttacker, float flDamage, int bitsDamageType);
	int BloodColor_(void)
	{
		return DONT_BLEED;
	}
	void Use_(CBaseEntity *pActivator, CBaseEntity *pCaller, USE_TYPE useType, float value);
	Vector BodyTarget_(const Vector &posSrc)
	{
		return pev->origin;
	}

#endif // HOOK_GAMEDLL

public:

	NOBODY void EXPORT Next(void);
	NOBODY void EXPORT Start(void);
	NOBODY void EXPORT Wait(void);
	NOBODY void Stop(void);

public:
#ifndef HOOK_GAMEDLL
	static TYPEDESCRIPTION m_SaveData[1];
#else // HOOK_GAMEDLL
	static TYPEDESCRIPTION (*m_SaveData)[1];
#endif // HOOK_GAMEDLL

private:
	BOOL m_on;

};/* size: 408, cachelines: 7, members: 3 */

NOBODY void PlatSpawnInsideTrigger(entvars_t *pevPlatform);
NOBODY float Fix(float angle);
NOBODY void FixupAngles(Vector &v);

#endif // PLATS_H

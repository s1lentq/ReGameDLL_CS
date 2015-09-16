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
	virtual void Precache(void);
	virtual void KeyValue(KeyValueData *pkvd);
	virtual int Save(CSave &save);
	virtual int Restore(CRestore &restore);
	virtual int ObjectCaps(void)
	{
		return ObjectCaps_();
	}

	// This is done to fix spawn flag collisions between this class and a derived class
	virtual BOOL IsTogglePlat(void)
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
	static TYPEDESCRIPTION IMPLEMENT_ARRAY(m_SaveData)[3];

public:
	BYTE m_bMoveSnd;
	BYTE m_bStopSnd;
	float m_volume;

};/* size: 320, cachelines: 5, members: 5 */

/* <12c853> ../cstrike/dlls/plats.cpp:223 */
class CFuncPlat: public CBasePlatTrain
{
public:
	virtual void Spawn(void);
	virtual void Precache(void);
	virtual void Blocked(CBaseEntity *pOther);
	virtual void GoUp(void);
	virtual void GoDown(void);
	virtual void HitTop(void);
	virtual void HitBottom(void);

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
	void EXPORT PlatUse(CBaseEntity *pActivator, CBaseEntity *pCaller, USE_TYPE useType, float value);
	void EXPORT CallGoDown(void);
	void EXPORT CallHitTop(void);
	void EXPORT CallHitBottom(void);

};/* size: 320, cachelines: 5, members: 1 */

/* <12c86e> ../cstrike/dlls/plats.cpp:248 */
class CPlatTrigger: public CBaseEntity
{
public:
	virtual int ObjectCaps(void)
	{
		return ObjectCaps_();
	}
	virtual void Touch(CBaseEntity *pOther);

#ifdef HOOK_GAMEDLL

	int ObjectCaps_(void)
	{
		return (CBaseEntity::ObjectCaps() & ~FCAP_ACROSS_TRANSITION) | FCAP_DONT_SAVE;
	}
	void Touch_(CBaseEntity *pOther);

#endif // HOOK_GAMEDLL

public:
	void SpawnInsideTrigger(CFuncPlat *pPlatform);

public:
	CFuncPlat *m_pPlatform;

};/* size: 156, cachelines: 3, members: 2 */

/* <12c8ee> ../cstrike/dlls/plats.cpp:515 */
class CFuncPlatRot: public CFuncPlat
{
public:
	virtual void Spawn(void);
	virtual int Save(CSave &save);
	virtual int Restore(CRestore &restore);

	virtual void GoUp(void);
	virtual void GoDown(void);
	virtual void HitTop(void);
	virtual void HitBottom(void);

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
	void SetupRotation(void);
	void RotMove(Vector &destAngle, float time);

public:
	static TYPEDESCRIPTION IMPLEMENT_ARRAY(m_SaveData)[2];

public:
	Vector m_end;
	Vector m_start;

};/* size: 344, cachelines: 6, members: 4 */

/* <12c93c> ../cstrike/dlls/plats.cpp:628 */
class CFuncTrain: public CBasePlatTrain
{
public:
	virtual void Spawn(void);
	virtual void Precache(void);
	virtual void Restart(void);
	virtual void KeyValue(KeyValueData *pkvd);
	virtual int Save(CSave &save);
	virtual int Restore(CRestore &restore);
	virtual void Activate(void);
	virtual void OverrideReset(void);
	virtual void Use(CBaseEntity *pActivator, CBaseEntity *pCaller, USE_TYPE useType, float value);
	virtual void Blocked(CBaseEntity *pOther);

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
	static TYPEDESCRIPTION IMPLEMENT_ARRAY(m_SaveData)[3];

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
	virtual void Spawn(void);
	virtual int ObjectCaps(void)
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
	virtual void Spawn(void);
	virtual void Precache(void);
	virtual void KeyValue(KeyValueData *pkvd);
	virtual int Save(CSave &save);
	virtual int Restore(CRestore &restore);
	virtual void OverrideReset(void);
	virtual void Touch(CBaseEntity *pOther);
	virtual void Use(CBaseEntity *pActivator, CBaseEntity *pCaller, USE_TYPE useType, float value);
	virtual BOOL IsTogglePlat(void);

	virtual void EXPORT GoUp(void);
	virtual void EXPORT GoDown(void);

	virtual void HitBottom(void);
	virtual void HitTop(void);
	virtual void UpdateAutoTargets(int toggleState);

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
	void EXPORT Find(void);
	TRAIN_CODE EvaluateTrain(CPathTrack *pcurrent);
	void UpdateTrain(Vector &dest);

	/* <12c515> ../cstrike/dlls/plats.cpp:1675 */
	void DisableUse(void)
	{
		m_use = 0;
	}
	/* <12c52e> ../cstrike/dlls/plats.cpp:1676 */
	void EnableUse(void)
	{
		m_use = 1;
	}
	/* <12c547> ../cstrike/dlls/plats.cpp:1677 */
	int UseEnabled(void)
	{
		return m_use;
	}

public:
	static TYPEDESCRIPTION IMPLEMENT_ARRAY(m_SaveData)[9];

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
	virtual void Use(CBaseEntity *pActivator, CBaseEntity *pCaller, USE_TYPE useType, float value);
	virtual void UpdateAutoTargets(int toggleState);

#ifdef HOOK_GAMEDLL

	void Use_(CBaseEntity *pActivator, CBaseEntity *pCaller, USE_TYPE useType, float value);
	void UpdateAutoTargets_(int toggleState);

#endif // HOOK_GAMEDLL


};/* size: 380, cachelines: 6, members: 1 */

/* <12caec> ../cstrike/dlls/plats.cpp:2136 */
class CGunTarget: public CBaseMonster
{
public:
	virtual void Spawn(void);
	virtual int Save(CSave &save);
	virtual int Restore(CRestore &restore);
	virtual int ObjectCaps(void)
	{
		return ObjectCaps_();
	}
	virtual void Activate(void);
	virtual int Classify(void)
	{
		return Classify_();
	}
	virtual int TakeDamage(entvars_t *pevInflictor, entvars_t *pevAttacker, float flDamage, int bitsDamageType);
	virtual int BloodColor(void)
	{
		return BloodColor_();
	}
	virtual void Use(CBaseEntity *pActivator, CBaseEntity *pCaller, USE_TYPE useType, float value);
	virtual Vector BodyTarget(const Vector &posSrc)
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
	void EXPORT Next(void);
	void EXPORT Start(void);
	void EXPORT Wait(void);
	void Stop(void);

public:
	static TYPEDESCRIPTION IMPLEMENT_ARRAY(m_SaveData)[1];

private:
	BOOL m_on;

};/* size: 408, cachelines: 7, members: 3 */

void PlatSpawnInsideTrigger(entvars_t *pevPlatform);
//float Fix(float angle);
void FixupAngles(Vector &v);

// linked objects
C_DLLEXPORT void func_plat(entvars_t *pev);
C_DLLEXPORT void func_platrot(entvars_t *pev);
C_DLLEXPORT void func_train(entvars_t *pev);
C_DLLEXPORT void func_tracktrain(entvars_t *pev);
C_DLLEXPORT void func_traincontrols(entvars_t *pev);
C_DLLEXPORT void func_trackchange(entvars_t *pev);
C_DLLEXPORT void func_trackautochange(entvars_t *pev);
C_DLLEXPORT void func_guntarget(entvars_t *pev);

#endif // PLATS_H

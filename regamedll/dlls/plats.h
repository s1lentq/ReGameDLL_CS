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

class CBasePlatTrain: public CBaseToggle
{
public:
	virtual void Precache();
	virtual void KeyValue(KeyValueData *pkvd);
	virtual int Save(CSave &save);
	virtual int Restore(CRestore &restore);
	virtual int ObjectCaps() { return CBaseEntity::ObjectCaps() & ~FCAP_ACROSS_TRANSITION; }

	// This is done to fix spawn flag collisions between this class and a derived class
	virtual BOOL IsTogglePlat() { return (pev->spawnflags & SF_PLAT_TOGGLE) != 0; }

#ifdef HOOK_GAMEDLL

	void Precache_();
	void KeyValue_(KeyValueData *pkvd);
	int Save_(CSave &save);
	int Restore_(CRestore &restore);

#endif

public:
	static TYPEDESCRIPTION IMPL(m_SaveData)[3];

	BYTE m_bMoveSnd;
	BYTE m_bStopSnd;
	float m_volume;
};

class CFuncPlat: public CBasePlatTrain
{
public:
	virtual void Spawn();
	virtual void Precache();
	virtual void Blocked(CBaseEntity *pOther);
	virtual void GoUp();
	virtual void GoDown();
	virtual void HitTop();
	virtual void HitBottom();

#ifdef HOOK_GAMEDLL

	void Spawn_();
	void Precache_();
	void Blocked_(CBaseEntity *pOther);
	void GoUp_();
	void GoDown_();
	void HitTop_();
	void HitBottom_();

#endif

public:
	void Setup();
	void EXPORT PlatUse(CBaseEntity *pActivator, CBaseEntity *pCaller, USE_TYPE useType, float value);
	void EXPORT CallGoDown();
	void EXPORT CallHitTop();
	void EXPORT CallHitBottom();
};

class CPlatTrigger: public CBaseEntity
{
public:
	virtual int ObjectCaps() { return (CBaseEntity::ObjectCaps() & ~FCAP_ACROSS_TRANSITION) | FCAP_DONT_SAVE; }
	virtual void Touch(CBaseEntity *pOther);

#ifdef HOOK_GAMEDLL

	void Touch_(CBaseEntity *pOther);

#endif

public:
	void SpawnInsideTrigger(CFuncPlat *pPlatform);

	CFuncPlat *m_pPlatform;
};

class CFuncPlatRot: public CFuncPlat
{
public:
	virtual void Spawn();
	virtual int Save(CSave &save);
	virtual int Restore(CRestore &restore);

	virtual void GoUp();
	virtual void GoDown();
	virtual void HitTop();
	virtual void HitBottom();

#ifdef HOOK_GAMEDLL

	void Spawn_();
	int Save_(CSave &save);
	int Restore_(CRestore &restore);
	void GoUp_();
	void GoDown_();
	void HitTop_();
	void HitBottom_();

#endif

public:
	void SetupRotation();
	void RotMove(Vector &destAngle, float time);

public:
	static TYPEDESCRIPTION IMPL(m_SaveData)[2];

	Vector m_end;
	Vector m_start;
};

class CFuncTrain: public CBasePlatTrain
{
public:
	virtual void Spawn();
	virtual void Precache();
	virtual void Restart();
	virtual void KeyValue(KeyValueData *pkvd);
	virtual int Save(CSave &save);
	virtual int Restore(CRestore &restore);
	virtual void Activate();
	virtual void OverrideReset();
	virtual void Use(CBaseEntity *pActivator, CBaseEntity *pCaller, USE_TYPE useType, float value);
	virtual void Blocked(CBaseEntity *pOther);

#ifdef HOOK_GAMEDLL

	void Spawn_();
	void Precache_();
	void Restart_();
	void KeyValue_(KeyValueData *pkvd);
	int Save_(CSave &save);
	int Restore_(CRestore &restore);
	void Activate_();
	void OverrideReset_();
	void Use_(CBaseEntity *pActivator, CBaseEntity *pCaller, USE_TYPE useType, float value);
	void Blocked_(CBaseEntity *pOther);

#endif

public:
	void EXPORT Wait();
	void EXPORT Next();

public:
	static TYPEDESCRIPTION IMPL(m_SaveData)[3];

	Vector m_vStartPosition;
	entvars_t *m_pevFirstTarget;
	entvars_t *m_pevCurrentTarget;
	int m_sounds;
	BOOL m_activated;
};

class CFuncTrainControls: public CBaseEntity
{
public:
	virtual void Spawn();
	virtual int ObjectCaps() { return CBaseEntity::ObjectCaps() & ~FCAP_ACROSS_TRANSITION; }

#ifdef HOOK_GAMEDLL

	void Spawn_();

#endif

public:
	void EXPORT Find();
};

class CFuncTrackChange: public CFuncPlatRot
{
public:
	virtual void Spawn();
	virtual void Precache();
	virtual void KeyValue(KeyValueData *pkvd);
	virtual int Save(CSave &save);
	virtual int Restore(CRestore &restore);
	virtual void OverrideReset();
	virtual void Touch(CBaseEntity *pOther);
	virtual void Use(CBaseEntity *pActivator, CBaseEntity *pCaller, USE_TYPE useType, float value);
	virtual BOOL IsTogglePlat();

	virtual void EXPORT GoUp();
	virtual void EXPORT GoDown();

	virtual void HitBottom();
	virtual void HitTop();
	virtual void UpdateAutoTargets(int toggleState);

#ifdef HOOK_GAMEDLL

	void Spawn_();
	void Precache_();
	void KeyValue_(KeyValueData *pkvd);
	int Save_(CSave &save);
	int Restore_(CRestore &restore);
	void OverrideReset_();
	void Touch_(CBaseEntity *pOther);
	void Use_(CBaseEntity *pActivator, CBaseEntity *pCaller, USE_TYPE useType, float value);
	BOOL IsTogglePlat_();
	void GoUp_();
	void GoDown_();
	void HitBottom_();
	void HitTop_();
	void UpdateAutoTargets_(int toggleState);

#endif

public:
	void EXPORT Find();
	TRAIN_CODE EvaluateTrain(CPathTrack *pcurrent);
	void UpdateTrain(Vector &dest);

	void DisableUse() { m_use = 0; }
	void EnableUse() { m_use = 1; }

	int UseEnabled() const { return m_use; }

public:
	static TYPEDESCRIPTION IMPL(m_SaveData)[9];

	CPathTrack *m_trackTop;
	CPathTrack *m_trackBottom;
	CFuncTrackTrain *m_train;

	int m_trackTopName;
	int m_trackBottomName;
	int m_trainName;

	TRAIN_CODE m_code;
	int m_targetState;
	int m_use;
};

class CFuncTrackAuto: public CFuncTrackChange
{
public:
	virtual void Use(CBaseEntity *pActivator, CBaseEntity *pCaller, USE_TYPE useType, float value);
	virtual void UpdateAutoTargets(int toggleState);

#ifdef HOOK_GAMEDLL

	void Use_(CBaseEntity *pActivator, CBaseEntity *pCaller, USE_TYPE useType, float value);
	void UpdateAutoTargets_(int toggleState);

#endif

};

class CGunTarget: public CBaseMonster
{
public:
	virtual void Spawn();
	virtual int Save(CSave &save);
	virtual int Restore(CRestore &restore);
	virtual int ObjectCaps() { return (CBaseEntity::ObjectCaps() & ~FCAP_ACROSS_TRANSITION); }
	virtual void Activate();
	virtual int Classify() { return CLASS_MACHINE; }
	virtual int TakeDamage(entvars_t *pevInflictor, entvars_t *pevAttacker, float flDamage, int bitsDamageType);
	virtual int BloodColor() { return DONT_BLEED; }
	virtual void Use(CBaseEntity *pActivator, CBaseEntity *pCaller, USE_TYPE useType, float value);
	virtual Vector BodyTarget(const Vector &posSrc) { return pev->origin; }

#ifdef HOOK_GAMEDLL

	void Spawn_();
	int Save_(CSave &save);
	int Restore_(CRestore &restore);
	void Activate_();
	int TakeDamage_(entvars_t *pevInflictor, entvars_t *pevAttacker, float flDamage, int bitsDamageType);
	void Use_(CBaseEntity *pActivator, CBaseEntity *pCaller, USE_TYPE useType, float value);

#endif

public:
	void EXPORT Next();
	void EXPORT Start();
	void EXPORT Wait();
	void Stop();

public:
	static TYPEDESCRIPTION IMPL(m_SaveData)[1];

private:
	BOOL m_on;
};

void PlatSpawnInsideTrigger(entvars_t *pevPlatform);
void FixupAngles(Vector &v);

#endif // PLATS_H

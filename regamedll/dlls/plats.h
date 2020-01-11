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

#define SF_PLAT_TOGGLE BIT(0) // The lift is no more automatically called from top and activated by stepping on it.
                              // It required trigger to do so.

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

public:
	static TYPEDESCRIPTION m_SaveData[];

	byte m_bMoveSnd;
	byte m_bStopSnd;
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

public:
	void SetupRotation();
	void RotMove(Vector &destAngle, float time);

public:
	static TYPEDESCRIPTION m_SaveData[];

	Vector m_end;
	Vector m_start;
};

#define SF_TRAIN_WAIT_RETRIGGER BIT(0)
#define SF_TRAIN_START_ON       BIT(2) // Train is initially moving
#define SF_TRAIN_PASSABLE       BIT(3) // Train is not solid -- used to make water trains

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

public:
	void EXPORT Wait();
	void EXPORT Next();

public:
	static TYPEDESCRIPTION m_SaveData[];

	Vector m_vStartPosition;
	entvars_t *m_pevFirstTarget;
	entvars_t *m_pevCurrentTarget;
	int m_sounds;
	BOOL m_activated;
};

// This class defines the volume of space that the player must stand in to control the train
class CFuncTrainControls: public CBaseEntity
{
public:
	virtual void Spawn();
	virtual int ObjectCaps() { return CBaseEntity::ObjectCaps() & ~FCAP_ACROSS_TRANSITION; }

public:
	void EXPORT Find();
};

#define SF_TRACK_ACTIVATETRAIN BIT(0)
#define SF_TRACK_RELINK        BIT(1)
#define SF_TRACK_ROTMOVE       BIT(2)
#define SF_TRACK_STARTBOTTOM   BIT(3)
#define SF_TRACK_DONT_MOVE     BIT(4)

enum TRAIN_CODE { TRAIN_SAFE, TRAIN_BLOCKING, TRAIN_FOLLOWING };

// This entity is a rotating/moving platform that will carry a train to a new track.
// It must be larger in X-Y planar area than the train, since it must contain the
// train within these dimensions in order to operate when the train is near it.
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
	virtual BOOL IsTogglePlat() { return TRUE; };

	virtual void EXPORT GoUp();
	virtual void EXPORT GoDown();

	virtual void HitTop();
	virtual void HitBottom();
	virtual void UpdateAutoTargets(int toggleState);

public:
	void EXPORT Find();
	TRAIN_CODE EvaluateTrain(CPathTrack *pcurrent);
	void UpdateTrain(Vector &dest);

	void DisableUse() { m_use = 0; }
	void EnableUse() { m_use = 1; }

	int UseEnabled() const { return m_use; }

public:
	static TYPEDESCRIPTION m_SaveData[];

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
};

// pev->speed is the travel speed
// pev->health is current health
// pev->max_health is the amount to reset to each time it starts

#define SF_GUNTARGET_START_ON BIT(0)

class CGunTarget: public CBaseMonster
{
public:
	virtual void Spawn();
	virtual int Save(CSave &save);
	virtual int Restore(CRestore &restore);
	virtual int ObjectCaps() { return (CBaseEntity::ObjectCaps() & ~FCAP_ACROSS_TRANSITION); }
	virtual void Activate();
	virtual int Classify() { return CLASS_MACHINE; }
	virtual BOOL TakeDamage(entvars_t *pevInflictor, entvars_t *pevAttacker, float flDamage, int bitsDamageType);
	virtual int BloodColor() { return DONT_BLEED; }
	virtual void Use(CBaseEntity *pActivator, CBaseEntity *pCaller, USE_TYPE useType, float value);
	virtual Vector BodyTarget(const Vector &posSrc) { return pev->origin; }

public:
	void EXPORT Next();
	void EXPORT Start();
	void EXPORT Wait();
	void Stop();

public:
	static TYPEDESCRIPTION m_SaveData[];

private:
	BOOL m_on;
};

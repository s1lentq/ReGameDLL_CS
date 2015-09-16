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

#ifndef TRAINS_H
#define TRAINS_H
#ifdef _WIN32
#pragma once
#endif

// Tracktrain spawn flags
#define SF_TRACKTRAIN_NOPITCH		0x0001
#define SF_TRACKTRAIN_NOCONTROL		0x0002
#define SF_TRACKTRAIN_FORWARDONLY	0x0004
#define SF_TRACKTRAIN_PASSABLE		0x0008

// Spawnflag for CPathTrack
#define SF_PATH_DISABLED		0x00000001
#define SF_PATH_FIREONCE		0x00000002
#define SF_PATH_ALTREVERSE		0x00000004
#define SF_PATH_DISABLE_TRAIN		0x00000008
#define SF_PATH_ALTERNATE		0x00008000

// Spawnflags of CPathCorner
#define SF_CORNER_WAITFORTRIG		0x001
#define SF_CORNER_TELEPORT		0x002
#define SF_CORNER_FIREONCE		0x004

/* <121991> ../cstrike/dlls/trains.h:37 */
class CPathTrack: public CPointEntity
{
public:
	virtual void Spawn(void);
	virtual void KeyValue(KeyValueData* pkvd);
	virtual int Save(CSave &save);
	virtual int Restore(CRestore &restore);
	virtual void Activate(void);
	virtual void Use(CBaseEntity *pActivator, CBaseEntity *pCaller, USE_TYPE useType, float value);

#ifdef HOOK_GAMEDLL

	void Spawn_(void);
	void KeyValue_(KeyValueData* pkvd);
	int Save_(CSave &save);
	int Restore_(CRestore &restore);
	void Activate_(void);
	void Use_(CBaseEntity *pActivator, CBaseEntity *pCaller, USE_TYPE useType, float value);

#endif // HOOK_GAMEDLL

	void SetPrevious(CPathTrack *pprevious);
	void Link(void);

	// Returns ppath if enabled, NULL otherwise
	CPathTrack *ValidPath(CPathTrack *ppath, int testFlag);
	void Project(CPathTrack *pstart, CPathTrack *pend, Vector *origin, float dist);

	static CPathTrack *Instance(edict_t *pent);

	CPathTrack *LookAhead(Vector *origin, float dist, int move);
	CPathTrack *Nearest(Vector origin);

	CPathTrack *GetNext(void);
	CPathTrack *GetPrevious(void);

public:
	static TYPEDESCRIPTION IMPLEMENT_ARRAY(m_SaveData)[5];

	float m_length;
	string_t m_altName;
	CPathTrack *m_pnext;
	CPathTrack *m_pprevious;
	CPathTrack *m_paltpath;

};/* size: 172, cachelines: 3, members: 7 */

/* <12c98a> ../cstrike/dlls/trains.h:75 */
class CFuncTrackTrain: public CBaseEntity
{
public:
	virtual void Spawn(void);
	virtual void Precache(void);
	virtual void Restart(void);
	virtual void KeyValue(KeyValueData* pkvd);
	virtual int Save(CSave &save);
	virtual int Restore(CRestore &restore);
	virtual int ObjectCaps(void)
	{
		return ObjectCaps_();
	}
	virtual void OverrideReset(void);
	virtual BOOL OnControls(entvars_t *pev);
	virtual void Use(CBaseEntity *pActivator, CBaseEntity *pCaller, USE_TYPE useType, float value);
	virtual void Blocked(CBaseEntity *pOther);

#ifdef HOOK_GAMEDLL

	void Spawn_(void);
	void Precache_(void);
	void Restart_(void);
	void KeyValue_(KeyValueData* pkvd);
	int Save_(CSave &save);
	int Restore_(CRestore &restore);
	int ObjectCaps_(void)
	{
		return (CBaseEntity::ObjectCaps() & ~FCAP_ACROSS_TRANSITION) | FCAP_DIRECTIONAL_USE;
	}
	void OverrideReset_(void);
	BOOL OnControls_(entvars_t *pev);
	void Use_(CBaseEntity *pActivator, CBaseEntity *pCaller, USE_TYPE useType, float value);
	void Blocked_(CBaseEntity *pOther);

#endif // HOOK_GAMEDLL

public:
	void EXPORT Next(void);
	void EXPORT Find(void);
	void EXPORT NearestPath(void);
	void EXPORT DeadEnd(void);

	void NextThink(float thinkTime, BOOL alwaysThink);
	void SetTrack(CPathTrack *track)
	{
		m_ppath = track->Nearest(pev->origin);
	}
	void SetControls(entvars_t *pevControls);
	void StopSound(void);
	void UpdateSound(void);

	static CFuncTrackTrain *Instance(edict_t *pent);

public:
	static TYPEDESCRIPTION IMPLEMENT_ARRAY(m_SaveData)[12];

	CPathTrack *m_ppath;
	float m_length;
	float m_height;
	float m_speed;
	float m_dir;
	float m_startSpeed;
	Vector m_controlMins;
	Vector m_controlMaxs;
	int m_soundPlaying;
	int m_sounds;
	float m_flVolume;
	float m_flBank;
	float m_oldSpeed;
	float m_fTurnAngle;
	float m_flSteeringWheelDecay;
	float m_flAcceleratorDecay;

private:
	unsigned short m_usAdjustPitch;

};/* size: 236, cachelines: 4, members: 19 */

/* <1ba5f9> ../cstrike/dlls/trains.h:134 */
class CFuncVehicle: public CBaseEntity
{
public:
	virtual void Spawn(void);
	virtual void Precache(void);
	virtual void Restart(void);
	virtual void KeyValue(KeyValueData *pkvd);
	virtual int Save(CSave &save);
	virtual int Restore(CRestore &restore);
	virtual int ObjectCaps(void)
	{
		return ObjectCaps_();
	}
	virtual int Classify(void);
	virtual void OverrideReset(void);
	virtual BOOL OnControls(entvars_t *pev);
	virtual void Use(CBaseEntity *pActivator, CBaseEntity *pCaller, USE_TYPE useType, float value);
	virtual void Blocked(CBaseEntity *pOther);

#ifdef HOOK_GAMEDLL

	void Spawn_(void);
	void Precache_(void);
	void Restart_(void);
	void KeyValue_(KeyValueData *pkvd);
	int Save_(CSave &save);
	int Restore_(CRestore &restore);
	int ObjectCaps_(void)
	{
		return (CBaseEntity::ObjectCaps() & ~FCAP_ACROSS_TRANSITION) | FCAP_DIRECTIONAL_USE;
	}
	int Classify_(void);
	void OverrideReset_(void);
	BOOL OnControls_(entvars_t *pev);
	void Use_(CBaseEntity *pActivator, CBaseEntity *pCaller, USE_TYPE useType, float value);
	void Blocked_(CBaseEntity *pOther);

#endif // HOOK_GAMEDLL

public:
	void EXPORT Next(void);
	void EXPORT Find(void);
	void EXPORT NearestPath(void);
	void EXPORT DeadEnd(void);

	void NextThink(float thinkTime, BOOL alwaysThink);
	void CollisionDetection(void);
	void TerrainFollowing(void);
	void CheckTurning(void);

	void SetTrack(CPathTrack *track)
	{
		m_ppath = track->Nearest(pev->origin);
	}
	void SetControls(entvars_t *pevControls);

	void StopSound(void);
	void UpdateSound(void);

public:
	static CFuncVehicle *Instance(edict_t *pent);

public:
	static TYPEDESCRIPTION IMPLEMENT_ARRAY(m_SaveData)[12];

	CPathTrack *m_ppath;
	float m_length;
	float m_width;
	float m_height;
	float m_speed;
	float m_dir;
	float m_startSpeed;
	Vector m_controlMins;
	Vector m_controlMaxs;
	int m_soundPlaying;
	int m_sounds;
	int m_acceleration;
	float m_flVolume;
	float m_flBank;
	float m_oldSpeed;
	int m_iTurnAngle;
	float m_flSteeringWheelDecay;
	float m_flAcceleratorDecay;
	float m_flTurnStartTime;
	float m_flLaunchTime;
	float m_flLastNormalZ;
	float m_flCanTurnNow;
	float m_flUpdateSound;
	Vector m_vFrontLeft;
	Vector m_vFront;
	Vector m_vFrontRight;
	Vector m_vBackLeft;
	Vector m_vBack;
	Vector m_vBackRight;
	Vector m_vSurfaceNormal;
	Vector m_vVehicleDirection;
	CBaseEntity *m_pDriver;

private:
	unsigned short m_usAdjustPitch;

};/* size: 364, cachelines: 6, members: 35 */

// linked objects
C_DLLEXPORT void path_track(entvars_t *pev);

#endif // TRAINS_H

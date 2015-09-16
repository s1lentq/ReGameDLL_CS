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

#ifndef DOORS_H
#define DOORS_H
#ifdef _WIN32
#pragma once
#endif

#define DOOR_SENTENCEWAIT		6
#define DOOR_SOUNDWAIT			3
#define BUTTON_SOUNDWAIT		0.5

#define SF_DOOR_ROTATE_Y		0
#define SF_DOOR_START_OPEN		1
#define SF_DOOR_ROTATE_BACKWARDS	2
#define SF_DOOR_PASSABLE		8
#define SF_DOOR_ONEWAY			16
#define SF_DOOR_NO_AUTO_RETURN		32
#define SF_DOOR_ROTATE_Z		64
#define SF_DOOR_ROTATE_X		128
#define SF_DOOR_USE_ONLY		256		// door must be opened by player's use button.
#define SF_DOOR_NOMONSTERS		512		// Monster can't open
#define SF_DOOR_SILENT			0x80000000

/* <6840f> ../cstrike/dlls/doors.cpp:34 */
class CBaseDoor: public CBaseToggle
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
	virtual void SetToggleState(int state);
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
		if (pev->spawnflags & SF_ITEM_USE_ONLY)
			return (CBaseToggle::ObjectCaps() & ~FCAP_ACROSS_TRANSITION) | FCAP_IMPULSE_USE;
		else
			return (CBaseToggle::ObjectCaps() & ~FCAP_ACROSS_TRANSITION);
	}
	void SetToggleState_(int state);
	void Use_(CBaseEntity *pActivator, CBaseEntity *pCaller, USE_TYPE useType, float value);
	void Blocked_(CBaseEntity *pOther);

#endif // HOOK_GAMEDLL

public:
	static TYPEDESCRIPTION IMPLEMENT_ARRAY(m_SaveData)[7];

public:
	// used to selectivly override defaults
	void EXPORT DoorTouch(CBaseEntity *pOther);
	int DoorActivate(void);
	void EXPORT DoorGoUp(void);
	void EXPORT DoorGoDown(void);
	void EXPORT DoorHitTop(void);
	void EXPORT DoorHitBottom(void);

public:
	BYTE m_bHealthValue;		// some doors are medi-kit doors, they give players health

	BYTE m_bMoveSnd;		// sound a door makes while moving
	BYTE m_bStopSnd;		// sound a door makes when it stops

	locksound_t m_ls;		// door lock sounds

	BYTE m_bLockedSound;		// ordinals from entity selection
	BYTE m_bLockedSentence;
	BYTE m_bUnlockedSound;
	BYTE m_bUnlockedSentence;

	float m_lastBlockedTimestamp;

};/* size: 360, cachelines: 6, members: 11 */

/* <684c0> ../cstrike/dlls/doors.cpp:935 */
class CRotDoor: public CBaseDoor
{
public:
	virtual void Spawn(void);
	virtual void Restart(void);
	virtual void SetToggleState(int state);

#ifdef HOOK_GAMEDLL

	void Spawn_(void);
	void Restart_(void);
	void SetToggleState_(int state);

#endif // HOOK_GAMEDLL

};/* size: 360, cachelines: 6, members: 1 */

/* <68513> ../cstrike/dlls/doors.cpp:1039 */
class CMomentaryDoor: public CBaseToggle
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
	virtual void Use(CBaseEntity *pActivator, CBaseEntity *pCaller, USE_TYPE useType, float value);

#ifdef HOOK_GAMEDLL

	void Spawn_(void);
	void Precache_(void);
	void KeyValue_(KeyValueData *pkvd);
	int Save_(CSave &save);
	int Restore_(CRestore &restore);
	int ObjectCaps_(void)
	{
		return CBaseToggle::ObjectCaps() & ~FCAP_ACROSS_TRANSITION;
	}
	void Use_(CBaseEntity *pActivator, CBaseEntity *pCaller, USE_TYPE useType, float value);

#endif // HOOK_GAMEDLL

public:
	static TYPEDESCRIPTION IMPLEMENT_ARRAY(m_SaveData)[1];

public:
	BYTE m_bMoveSnd;	// sound a door makes while moving

};/* size: 316, cachelines: 5, members: 3 */

void PlayLockSounds(entvars_t *pev, locksound_t *pls, int flocked, int fbutton);

// linked objects
C_DLLEXPORT void func_door(entvars_t *pev);
C_DLLEXPORT void func_water(entvars_t *pev);
C_DLLEXPORT void func_door_rotating(entvars_t *pev);
C_DLLEXPORT void momentary_door(entvars_t *pev);

#endif // DOORS_H

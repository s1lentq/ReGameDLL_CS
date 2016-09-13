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
#define SF_DOOR_TOUCH_ONLY_CLIENTS	1024		// Only clients can touch
#define SF_DOOR_SILENT			0x80000000

class CBaseDoor: public CBaseToggle {
public:
	virtual void Spawn() = 0;
	virtual void Precache() = 0;
	virtual void Restart() = 0;
	virtual void KeyValue(KeyValueData *pkvd) = 0;
	virtual int Save(CSave &save) = 0;
	virtual int Restore(CRestore &restore) = 0;
	virtual int ObjectCaps() = 0;
	virtual void SetToggleState(int state) = 0;
	virtual void Use(CBaseEntity *pActivator, CBaseEntity *pCaller, USE_TYPE useType, float value) = 0;
	virtual void Blocked(CBaseEntity *pOther) = 0;
public:
	byte m_bHealthValue;		// some doors are medi-kit doors, they give players health

	byte m_bMoveSnd;		// sound a door makes while moving
	byte m_bStopSnd;		// sound a door makes when it stops

	locksound_t m_ls;		// door lock sounds

	byte m_bLockedSound;		// ordinals from entity selection
	byte m_bLockedSentence;
	byte m_bUnlockedSound;
	byte m_bUnlockedSentence;

	float m_lastBlockedTimestamp;
};

class CRotDoor: public CBaseDoor {
public:
	virtual void Spawn() = 0;
	virtual void Restart() = 0;
	virtual void SetToggleState(int state) = 0;
};

class CMomentaryDoor: public CBaseToggle {
public:
	virtual void Spawn() = 0;
	virtual void Precache() = 0;
	virtual void KeyValue(KeyValueData *pkvd) = 0;
	virtual int Save(CSave &save) = 0;
	virtual int Restore(CRestore &restore) = 0;
	virtual int ObjectCaps() = 0;
	virtual void Use(CBaseEntity *pActivator, CBaseEntity *pCaller, USE_TYPE useType, float value) = 0;
public:
	byte m_bMoveSnd;	// sound a door makes while moving
};

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

const float DOOR_SENTENCEWAIT   = 6.0f;
const float DOOR_SOUNDWAIT      = 3.0f;
const float BUTTON_SOUNDWAIT    = 0.5f;

#define SF_DOOR_START_OPEN          BIT(0)
#define SF_DOOR_PASSABLE            BIT(3)
#define SF_DOOR_NO_AUTO_RETURN      BIT(5)
#define SF_DOOR_USE_ONLY            BIT(8)  // Door must be opened by player's use button.
#define SF_DOOR_TOUCH_ONLY_CLIENTS  BIT(10) // Only clients can touch
#define SF_DOOR_ACTUALLY_WATER      BIT(31) // This bit marks that func_door are actually func_water

class CBaseDoor: public CBaseToggle
{
public:
	virtual void Spawn();
	virtual void Precache();
	virtual void Restart();
	virtual void KeyValue(KeyValueData *pkvd);
	virtual int Save(CSave &save);
	virtual int Restore(CRestore &restore);
	virtual int ObjectCaps()
	{
		if (pev->spawnflags & SF_DOOR_USE_ONLY)
			return (CBaseToggle::ObjectCaps() & ~FCAP_ACROSS_TRANSITION) | FCAP_IMPULSE_USE;
		else
			return (CBaseToggle::ObjectCaps() & ~FCAP_ACROSS_TRANSITION);
	}
	virtual void SetToggleState(int state);
	virtual void Use(CBaseEntity *pActivator, CBaseEntity *pCaller, USE_TYPE useType, float value);
	virtual void Blocked(CBaseEntity *pOther);

public:
	static TYPEDESCRIPTION m_SaveData[];

	// used to selectivly override defaults
	void EXPORT DoorTouch(CBaseEntity *pOther);
	int DoorActivate();
	void EXPORT DoorGoUp();
	void EXPORT DoorGoDown();
	void EXPORT DoorHitTop();
	void EXPORT DoorHitBottom();

public:
	byte m_bHealthValue;		// some doors are medi-kit doors, they give players health
	byte m_bMoveSnd;			// sound a door makes while moving
	byte m_bStopSnd;			// sound a door makes when it stops

	locksound_t m_ls;			// door lock sounds

	byte m_bLockedSound;		// ordinals from entity selection
	byte m_bLockedSentence;
	byte m_bUnlockedSound;
	byte m_bUnlockedSentence;

	float m_lastBlockedTimestamp;
};

#define SF_DOOR_ROTATE_BACKWARDS BIT(1)
#define SF_DOOR_ROTATE_ONEWAY    BIT(4)
#define SF_DOOR_ROTATE_Z         BIT(6)
#define SF_DOOR_ROTATE_X         BIT(7)

class CRotDoor: public CBaseDoor
{
public:
	virtual void Spawn();
	virtual void Restart();
	virtual void SetToggleState(int state);
};

class CMomentaryDoor: public CBaseToggle
{
public:
	virtual void Spawn();
	virtual void Precache();
	virtual void KeyValue(KeyValueData *pkvd);
	virtual int Save(CSave &save);
	virtual int Restore(CRestore &restore);
	virtual int ObjectCaps() { return (CBaseToggle::ObjectCaps() & ~FCAP_ACROSS_TRANSITION); }
	virtual void Use(CBaseEntity *pActivator, CBaseEntity *pCaller, USE_TYPE useType, float value);

public:
	static TYPEDESCRIPTION m_SaveData[];

	byte m_bMoveSnd; // sound a door makes while moving
};

void PlayLockSounds(entvars_t *pev, locksound_t *pls, int flocked, int fbutton);

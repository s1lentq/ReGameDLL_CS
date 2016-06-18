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

#define SF_BUTTON_DONTMOVE		1
#define SF_ROTBUTTON_NOTSOLID		1
#define SF_BUTTON_TOGGLE		32	// button stays pushed until reactivated
#define SF_BUTTON_SPARK_IF_OFF		64	// button sparks in OFF state
#define SF_BUTTON_TOUCH_ONLY		256	// button only fires as a result of USE key.

#define SF_GLOBAL_SET			1	// Set global state to initial state on spawn

#define SF_MULTI_INIT			1

// Make this button behave like a door (HACKHACK)
// This will disable use and make the button solid
// rotating buttons were made SOLID_NOT by default since their were some
// collision problems with them...
#define SF_MOMENTARY_DOOR		0x0001

#define SF_SPARK_TOOGLE			32
#define SF_SPARK_IF_OFF			64

#define SF_BTARGET_USE			0x0001
#define SF_BTARGET_ON			0x0002

class CEnvGlobal: public CPointEntity {
public:
	virtual void Spawn() = 0;
	virtual void KeyValue(KeyValueData *pkvd) = 0;
	virtual int Save(CSave &save) = 0;
	virtual int Restore(CRestore &restore) = 0;
	virtual void Use(CBaseEntity *pActivator, CBaseEntity *pCaller, USE_TYPE useType, float value) = 0;
public:
	string_t m_globalstate;
	int m_triggermode;
	int m_initialstate;
};

class CRotButton: public CBaseButton {
public:
	virtual void Spawn() = 0;
};

class CMomentaryRotButton: public CBaseToggle {
public:
	virtual void Spawn() = 0;
	virtual void KeyValue(KeyValueData *pkvd) = 0;
	virtual int Save(CSave &save) = 0;
	virtual int Restore(CRestore &restore) = 0;
	virtual int ObjectCaps() = 0;
	virtual void Use(CBaseEntity *pActivator, CBaseEntity *pCaller, USE_TYPE useType, float value) = 0;
public:
	int m_lastUsed;
	int m_direction;
	float m_returnSpeed;
	Vector m_start;
	Vector m_end;
	int m_sounds;
};

class CEnvSpark: public CBaseEntity {
public:
	virtual void Spawn() = 0;
	virtual void Precache() = 0;
	virtual void KeyValue(KeyValueData *pkvd) = 0;
	virtual int Save(CSave &save) = 0;
	virtual int Restore(CRestore &restore) = 0;
public:
	float m_flDelay;
};

class CButtonTarget: public CBaseEntity {
public:
	virtual void Spawn() = 0;
	virtual int ObjectCaps() = 0;
	virtual BOOL TakeDamage(entvars_t *pevInflictor, entvars_t *pevAttacker, float flDamage, int bitsDamageType) = 0;
	virtual void Use(CBaseEntity *pActivator, CBaseEntity *pCaller, USE_TYPE useType, float value) = 0;
};

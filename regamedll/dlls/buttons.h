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

#ifndef BUTTON_H
#define BUTTON_H
#ifdef _WIN32
#pragma once
#endif

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

class CEnvGlobal: public CPointEntity
{
public:
	virtual void Spawn();
	virtual void KeyValue(KeyValueData *pkvd);
	virtual int Save(CSave &save);
	virtual int Restore(CRestore &restore);
	virtual void Use(CBaseEntity *pActivator, CBaseEntity *pCaller, USE_TYPE useType, float value);

public:
	static TYPEDESCRIPTION IMPL(m_SaveData)[3];

	string_t m_globalstate;
	int m_triggermode;
	int m_initialstate;
};

class CRotButton: public CBaseButton
{
public:
	virtual void Spawn();

#ifdef REGAMEDLL_FIXES
	virtual void Restart();
	virtual int Save(CSave &save);
	virtual int Restore(CRestore &restore);
public:
	static TYPEDESCRIPTION m_SaveData[1];
	Vector m_vecSpawn;
#endif

};

class CMomentaryRotButton: public CBaseToggle
{
public:
	virtual void Spawn();
	virtual void KeyValue(KeyValueData *pkvd);
	virtual int Save(CSave &save);
	virtual int Restore(CRestore &restore);
	virtual int ObjectCaps()
	{
		int flags = CBaseToggle::ObjectCaps() & (~FCAP_ACROSS_TRANSITION);

		if (pev->spawnflags & SF_MOMENTARY_DOOR)
		{
			return flags;
		}

		return (flags | FCAP_CONTINUOUS_USE);
	}
	virtual void Use(CBaseEntity *pActivator, CBaseEntity *pCaller, USE_TYPE useType, float value);

public:
	void EXPORT Off();
	void EXPORT Return();
	void UpdateSelf(float value);
	void UpdateSelfReturn(float value);
	void UpdateAllButtons(float value, int start);
	void PlaySound();
	void UpdateTarget(float value);

public:
	static CMomentaryRotButton *Instance(edict_t *pent) { return (CMomentaryRotButton *)GET_PRIVATE(pent); }
	static TYPEDESCRIPTION IMPL(m_SaveData)[6];

	int m_lastUsed;
	int m_direction;
	float m_returnSpeed;
	Vector m_start;
	Vector m_end;
	int m_sounds;
};

class CEnvSpark: public CBaseEntity
{
public:
	virtual void Spawn();
	virtual void Precache();
	virtual void KeyValue(KeyValueData *pkvd);
	virtual int Save(CSave &save);
	virtual int Restore(CRestore &restore);

public:
	void EXPORT SparkThink();
	void EXPORT SparkStart(CBaseEntity *pActivator, CBaseEntity *pCaller, USE_TYPE useType, float value);
	void EXPORT SparkStop(CBaseEntity *pActivator, CBaseEntity *pCaller, USE_TYPE useType, float value);

public:
	static TYPEDESCRIPTION IMPL(m_SaveData)[1];
	float m_flDelay;
};

class CButtonTarget: public CBaseEntity
{
public:
	virtual void Spawn();
	virtual int ObjectCaps();
	virtual BOOL TakeDamage(entvars_t *pevInflictor, entvars_t *pevAttacker, float flDamage, int bitsDamageType);
	virtual void Use(CBaseEntity *pActivator, CBaseEntity *pCaller, USE_TYPE useType, float value);
};

char *ButtonSound(int sound);
void DoSpark(entvars_t *pev, const Vector &location);

#endif // BUTTON_H

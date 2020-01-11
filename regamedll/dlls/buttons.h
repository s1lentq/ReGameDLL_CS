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

#define SF_GLOBAL_SET BIT(0) // Set global state to initial state on spawn

class CEnvGlobal: public CPointEntity
{
public:
	virtual void Spawn();
	virtual void KeyValue(KeyValueData *pkvd);
	virtual int Save(CSave &save);
	virtual int Restore(CRestore &restore);
	virtual void Use(CBaseEntity *pActivator, CBaseEntity *pCaller, USE_TYPE useType, float value);

public:
	static TYPEDESCRIPTION m_SaveData[];

	string_t m_globalstate;
	int m_triggermode;
	int m_initialstate;
};

#define SF_ROTBUTTON_NOTSOLID  BIT(0)
#define SF_ROTBUTTON_BACKWARDS BIT(1)

class CRotButton: public CBaseButton
{
public:
	virtual void Spawn();

#ifdef REGAMEDLL_FIXES
	virtual void Restart();
	virtual int Save(CSave &save);
	virtual int Restore(CRestore &restore);

public:
	static TYPEDESCRIPTION m_SaveData[];
	Vector m_vecSpawn;
#endif

};

// Make this button behave like a door (HACKHACK)
// This will disable use and make the button solid
// rotating buttons were made SOLID_NOT by default since their were some
// collision problems with them...
#define SF_MOMENTARY_DOOR BIT(0)

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
	static TYPEDESCRIPTION m_SaveData[];

	int m_lastUsed;
	int m_direction;
	float m_returnSpeed;
	Vector m_start;
	Vector m_end;
	int m_sounds;
};

#define SF_SPARK_TOOGLE BIT(5)
#define SF_SPARK_IF_OFF BIT(6)

class CEnvSpark: public CBaseEntity
{
public:
	virtual void Spawn();
	virtual void Precache();
	virtual void KeyValue(KeyValueData *pkvd);
	virtual int Save(CSave &save);
	virtual int Restore(CRestore &restore);

#ifdef REGAMEDLL_FIXES
	virtual void Restart();
#endif

public:
	void EXPORT SparkThink();
	void EXPORT SparkStart(CBaseEntity *pActivator, CBaseEntity *pCaller, USE_TYPE useType, float value);
	void EXPORT SparkStop(CBaseEntity *pActivator, CBaseEntity *pCaller, USE_TYPE useType, float value);

public:
	static TYPEDESCRIPTION m_SaveData[];

	float m_flDelay;
};

#define SF_BTARGET_USE BIT(0)
#define SF_BTARGET_ON  BIT(1)

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

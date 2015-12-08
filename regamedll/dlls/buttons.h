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
#define	SF_BUTTON_TOGGLE		32	// button stays pushed until reactivated
#define	SF_BUTTON_SPARK_IF_OFF		64	// button sparks in OFF state
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

/* <249a3> ../cstrike/dlls/buttons.cpp:38 */
class CEnvGlobal: public CPointEntity
{
public:
	virtual void Spawn(void);
	virtual void KeyValue(KeyValueData *pkvd);
	virtual int Save(CSave &save);
	virtual int Restore(CRestore &restore);
	virtual void Use(CBaseEntity *pActivator, CBaseEntity *pCaller, USE_TYPE useType, float value);

#ifdef HOOK_GAMEDLL

	void Spawn_(void);
	void KeyValue_(KeyValueData *pkvd);
	int Save_(CSave &save);
	int Restore_(CRestore &restore);
	void Use_(CBaseEntity *pActivator, CBaseEntity *pCaller, USE_TYPE useType, float value);

#endif // HOOK_GAMEDLL

public:
	static TYPEDESCRIPTION IMPL(m_SaveData)[3];

public:
	string_t m_globalstate;
	int m_triggermode;
	int m_initialstate;

};/* size: 164, cachelines: 3, members: 5 */

/* <24b67> ../cstrike/dlls/buttons.cpp:800 */
class CRotButton: public CBaseButton
{
public:
	virtual void Spawn(void);

#ifdef HOOK_GAMEDLL

	void Spawn_(void);

#endif // HOOK_GAMEDLL

};/* size: 368, cachelines: 6, members: 1 */

/* <24bba> ../cstrike/dlls/buttons.cpp:873 */
class CMomentaryRotButton: public CBaseToggle
{
public:
	virtual void Spawn(void);
	virtual void KeyValue(KeyValueData *pkvd);
	virtual int Save(CSave &save);
	virtual int Restore(CRestore &restore);
	virtual int ObjectCaps(void)
	{
		int flags = CBaseToggle::ObjectCaps() & (~FCAP_ACROSS_TRANSITION);

		if (pev->spawnflags & SF_MOMENTARY_DOOR)
		{
			return flags;
		}

		return (flags | FCAP_CONTINUOUS_USE);
	}
	virtual void Use(CBaseEntity *pActivator, CBaseEntity *pCaller, USE_TYPE useType, float value);

#ifdef HOOK_GAMEDLL

	void Spawn_(void);
	void KeyValue_(KeyValueData *pkvd);
	int Save_(CSave &save);
	int Restore_(CRestore &restore);
	void Use_(CBaseEntity *pActivator, CBaseEntity *pCaller, USE_TYPE useType, float value);

#endif // HOOK_GAMEDLL

public:
	void EXPORT Off(void);
	void EXPORT Return(void);
	void UpdateSelf(float value);
	void UpdateSelfReturn(float value);
	void UpdateAllButtons(float value, int start);
	void PlaySound(void);
	void UpdateTarget(float value);
public:
	static CMomentaryRotButton *Instance(edict_t *pent)
	{
		return (CMomentaryRotButton *)GET_PRIVATE(pent);
	}

public:
	static TYPEDESCRIPTION IMPL(m_SaveData)[6];

public:
	int m_lastUsed;
	int m_direction;
	float m_returnSpeed;
	Vector m_start;
	Vector m_end;
	int m_sounds;

};/* size: 352, cachelines: 6, members: 8 */

/* <24c08> ../cstrike/dlls/buttons.cpp:1117 */
class CEnvSpark: public CBaseEntity
{
public:
	virtual void Spawn(void);
	virtual void Precache(void);
	virtual void KeyValue(KeyValueData *pkvd);
	virtual int Save(CSave &save);
	virtual int Restore(CRestore &restore);

#ifdef HOOK_GAMEDLL

	void Spawn_(void);
	void Precache_(void);
	void KeyValue_(KeyValueData *pkvd);
	int Save_(CSave &save);
	int Restore_(CRestore &restore);

#endif // HOOK_GAMEDLL

public:
	void EXPORT SparkThink(void);
	void EXPORT SparkStart(CBaseEntity *pActivator, CBaseEntity *pCaller, USE_TYPE useType, float value);
	void EXPORT SparkStop(CBaseEntity *pActivator, CBaseEntity *pCaller, USE_TYPE useType, float value);

public:
	static TYPEDESCRIPTION IMPL(m_SaveData)[1];

public:
	float m_flDelay;

};/* size: 156, cachelines: 3, members: 3 */

/* <24c24> ../cstrike/dlls/buttons.cpp:1223 */
class CButtonTarget: public CBaseEntity
{
public:
	virtual void Spawn(void);
	virtual int ObjectCaps(void);
	virtual int TakeDamage(entvars_t *pevInflictor, entvars_t *pevAttacker, float flDamage, int bitsDamageType);
	virtual void Use(CBaseEntity *pActivator, CBaseEntity *pCaller, USE_TYPE useType, float value);

#ifdef HOOK_GAMEDLL

	void Spawn_(void);
	int ObjectCaps_(void);
	int TakeDamage_(entvars_t *pevInflictor, entvars_t *pevAttacker, float flDamage, int bitsDamageType);
	void Use_(CBaseEntity *pActivator, CBaseEntity *pCaller, USE_TYPE useType, float value);

#endif // HOOK_GAMEDLL

};/* size: 152, cachelines: 3, members: 1 */

char *ButtonSound(int sound);
void DoSpark(entvars_t *pev, const Vector &location);

#ifdef HOOK_GAMEDLL

// linked objects
C_DLLEXPORT void env_global(entvars_t *pev);
C_DLLEXPORT void multisource(entvars_t *pev);
C_DLLEXPORT void func_button(entvars_t *pev);
C_DLLEXPORT void func_rot_button(entvars_t *pev);
C_DLLEXPORT void momentary_rot_button(entvars_t *pev);
C_DLLEXPORT void env_spark(entvars_t *pev);
C_DLLEXPORT void env_debris(entvars_t *pev);
C_DLLEXPORT void button_target(entvars_t *pev);

#endif // HOOK_GAMEDLL

#endif // BUTTON_H

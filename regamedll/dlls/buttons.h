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

/* <249a3> ../cstrike/dlls/buttons.cpp:38 */
class CEnvGlobal: public CPointEntity
{
public:
	NOBODY virtual void Spawn(void);
	NOBODY virtual void KeyValue(KeyValueData *pkvd);
	NOBODY virtual int Save(CSave &save);
	NOBODY virtual int Restore(CRestore &restore);
	NOBODY virtual void Use(CBaseEntity *pActivator, CBaseEntity *pCaller, USE_TYPE useType, float value);

#ifdef HOOK_GAMEDLL

	void Spawn_(void);
	void KeyValue_(KeyValueData *pkvd);
	int Save_(CSave &save);
	int Restore_(CRestore &restore);
	void Use_(CBaseEntity *pActivator, CBaseEntity *pCaller, USE_TYPE useType, float value);

#endif // HOOK_GAMEDLL

public:
	static TYPEDESCRIPTION IMPLEMENT_ARRAY(m_SaveData)[3];

public:
	string_t m_globalstate;
	int m_triggermode;
	int m_initialstate;

};/* size: 164, cachelines: 3, members: 5 */

/* <24b67> ../cstrike/dlls/buttons.cpp:800 */
class CRotButton: public CBaseButton
{
public:
	NOBODY virtual void Spawn(void);

#ifdef HOOK_GAMEDLL
	void Spawn_(void);
#endif // HOOK_GAMEDLL

};/* size: 368, cachelines: 6, members: 1 */

/* <24bba> ../cstrike/dlls/buttons.cpp:873 */
class CMomentaryRotButton: public CBaseToggle
{
public:
	NOBODY virtual void Spawn(void);
	NOBODY virtual void KeyValue(KeyValueData *pkvd);
	NOBODY virtual int Save(CSave &save);
	NOBODY virtual int Restore(CRestore &restore);
	NOBODY virtual int ObjectCaps(void);
	NOBODY virtual void Use(CBaseEntity *pActivator, CBaseEntity *pCaller, USE_TYPE useType, float value);

#ifdef HOOK_GAMEDLL

	void Spawn_(void);
	void KeyValue_(KeyValueData *pkvd);
	int Save_(CSave &save);
	int Restore_(CRestore &restore);
	int ObjectCaps_(void);
	void Use_(CBaseEntity *pActivator, CBaseEntity *pCaller, USE_TYPE useType, float value);

#endif // HOOK_GAMEDLL

public:
	NOBODY void EXPORT Off(void);
	NOBODY void EXPORT Return(void);
	NOBODY void UpdateSelf(float value);
	NOBODY void UpdateSelfReturn(float value);
	NOBODY void UpdateAllButtons(float value, int start);
	NOBODY void PlaySound(void);
	NOBODY void UpdateTarget(float value);
public:
	static CMomentaryRotButton *Instance(edict_t *pent)
	{
		return (CMomentaryRotButton *)GET_PRIVATE(pent);
	}

public:
	static TYPEDESCRIPTION IMPLEMENT_ARRAY(m_SaveData)[6];

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
	NOBODY virtual void Spawn(void);
	NOBODY virtual void Precache(void);
	NOBODY virtual void KeyValue(KeyValueData *pkvd);
	NOBODY virtual int Save(CSave &save);
	NOBODY virtual int Restore(CRestore &restore);

#ifdef HOOK_GAMEDLL

	void Spawn_(void);
	void Precache_(void);
	void KeyValue_(KeyValueData *pkvd);
	int Save_(CSave &save);
	int Restore_(CRestore &restore);

#endif // HOOK_GAMEDLL

public:
	NOBODY void EXPORT SparkThink(void);
	NOBODY void EXPORT SparkStart(CBaseEntity *pActivator, CBaseEntity *pCaller, USE_TYPE useType, float value);
	NOBODY void EXPORT SparkStop(CBaseEntity *pActivator, CBaseEntity *pCaller, USE_TYPE useType, float value);

public:
	static TYPEDESCRIPTION IMPLEMENT_ARRAY(m_SaveData)[1];

public:
	float m_flDelay;

};/* size: 156, cachelines: 3, members: 3 */

/* <24c24> ../cstrike/dlls/buttons.cpp:1223 */
class CButtonTarget: public CBaseEntity
{
public:
	NOBODY virtual void Spawn(void);
	NOBODY virtual int ObjectCaps(void);
	NOBODY virtual int TakeDamage(entvars_t *pevInflictor, entvars_t *pevAttacker, float flDamage, int bitsDamageType);
	NOBODY virtual void Use(CBaseEntity *pActivator, CBaseEntity *pCaller, USE_TYPE useType, float value);

#ifdef HOOK_GAMEDLL

	void Spawn_(void);
	int ObjectCaps_(void);
	int TakeDamage_(entvars_t *pevInflictor, entvars_t *pevAttacker, float flDamage, int bitsDamageType);
	void Use_(CBaseEntity *pActivator, CBaseEntity *pCaller, USE_TYPE useType, float value);

#endif // HOOK_GAMEDLL

};/* size: 152, cachelines: 3, members: 1 */

NOBODY char *ButtonSound(int sound);
NOBODY void DoSpark(entvars_t *pev, const Vector &location);

#endif // BUTTON_H

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

#ifndef H_CYCLER_H
#define H_CYCLER_H
#ifdef _WIN32
#pragma once
#endif

class CCyclerSprite: public CBaseEntity
{
public:
	NOBODY virtual void Spawn(void);
	NOBODY virtual void Restart(void);
	NOBODY virtual int Save(CSave &save);
	NOBODY virtual int Restore(CRestore &restore);
	virtual int ObjectCaps(void)
	{
		return ((CBaseEntity::ObjectCaps()|FCAP_DONT_SAVE|FCAP_IMPULSE_USE));
	}
	NOBODY virtual int TakeDamage(entvars_t *pevInflictor, entvars_t *pevAttacker, float flDamage, int bitsDamageType);
	NOBODY virtual void Think(void);
	NOBODY virtual void Use(CBaseEntity *pActivator, CBaseEntity *pCaller, USE_TYPE useType, float value);
public:
	NOBODY void Animate(float frames);
	inline int ShouldAnimate(void)
	{
		return m_animate && m_maxFrame > 1.0;
	}
public:

#ifndef HOOK_GAMEDLL

	static TYPEDESCRIPTION m_SaveData[3];
#else
	static TYPEDESCRIPTION (*m_SaveData)[3];

#endif // HOOK_GAMEDLL

	int m_animate;
	float m_lastTime;
	float m_maxFrame;
	int m_renderfx;
	int m_rendermode;
	float m_renderamt;
	vec3_t m_rendercolor;

#ifdef HOOK_GAMEDLL

public:
	NOBODY void Spawn_(void);
	NOBODY void Restart_(void);
	NOBODY int Save_(CSave &save);
	NOBODY int Restore_(CRestore &restore);
	NOBODY int TakeDamage_(entvars_t *pevInflictor, entvars_t *pevAttacker, float flDamage, int bitsDamageType);
	NOBODY void Think_(void);
	NOBODY void Use_(CBaseEntity *pActivator, CBaseEntity *pCaller, USE_TYPE useType, float value);

#endif // HOOK_GAMEDLL

};/* size: 188, cachelines: 3, members: 9 */

class CCycler: public CBaseMonster
{
public:
	NOBODY virtual void Spawn(void);
	NOBODY virtual int Save(CSave &save);
	NOBODY virtual int Restore(CRestore &restore);
	virtual int ObjectCaps(void)
	{
		return ((CBaseEntity::ObjectCaps()|FCAP_IMPULSE_USE));
	}
	NOBODY virtual int TakeDamage(entvars_t *pevInflictor, entvars_t *pevAttacker, float flDamage, int bitsDamageType);
	virtual BOOL IsAlive(void)
	{
		return FALSE;
	}
	NOBODY virtual void Think(void);
	NOBODY virtual void Use(CBaseEntity *pActivator, CBaseEntity *pCaller, USE_TYPE useType, float value);
public:
	void GenericCyclerSpawn(char *szModel, Vector vecMin, Vector vecMax);
public:
#ifndef HOOK_GAMEDLL

	static TYPEDESCRIPTION m_SaveData[1];
#else
	static TYPEDESCRIPTION (*m_SaveData)[1];

#endif // HOOK_GAMEDLL

	int m_animate;

#ifdef HOOK_GAMEDLL

	NOBODY void Spawn_(void);
	NOBODY int Save_(CSave &save);
	NOBODY int Restore_(CRestore &restore);
	NOBODY int TakeDamage_(entvars_t *pevInflictor, entvars_t *pevAttacker, float flDamage, int bitsDamageType);
	NOBODY void Think_(void);
	NOBODY void Use_(CBaseEntity *pActivator, CBaseEntity *pCaller, USE_TYPE useType, float value);

#endif // HOOK_GAMEDLL

};/* size: 408, cachelines: 7, members: 3 */

class CGenericCycler: public CCycler
{
public:
	NOBODY virtual void Spawn(void);

#ifdef HOOK_GAMEDLL

	NOBODY void Spawn_(void);

#endif // HOOK_GAMEDLL

};/* size: 408, cachelines: 7, members: 1 */

class CCyclerProbe: public CCycler
{
public:
	NOBODY virtual void Spawn(void);

#ifdef HOOK_GAMEDLL

	NOBODY void Spawn_(void);

#endif // HOOK_GAMEDLL

};/* size: 408, cachelines: 7, members: 1 */

//#include "weapons.h"

class CWeaponCycler: public CBasePlayerWeapon
{
public:
	NOBODY virtual void Spawn(void);
	virtual int GetItemInfo(ItemInfo *p)
	{
		return 0;
	}
	NOBODY virtual BOOL Deploy(void);
	NOBODY virtual void Holster(int skiplocal = 0);
	virtual int iItemSlot(void)
	{
		return 1;
	}
	NOBODY virtual void PrimaryAttack(void);
	NOBODY virtual void SecondaryAttack(void);
public:
	int m_iszModel;
	int m_iModel;

#ifdef HOOK_GAMEDLL

	NOBODY void Spawn_(void);
	NOBODY BOOL Deploy_(void);
	NOBODY void Holster_(int skiplocal = 0);
	NOBODY void PrimaryAttack_(void);
	NOBODY void SecondaryAttack_(void);

#endif // HOOK_GAMEDLL

};/* size: 344, cachelines: 6, members: 3 */

class CWreckage: public CBaseMonster
{
	NOBODY virtual void Spawn(void);
	NOBODY virtual void Precache(void);
	NOBODY virtual int Save(CSave &save);
	NOBODY virtual int Restore(CRestore &restore);
	NOBODY virtual void Think(void);
public:
#ifndef HOOK_GAMEDLL

	static TYPEDESCRIPTION m_SaveData[1];
#else
	static TYPEDESCRIPTION (*m_SaveData)[1];

#endif // HOOK_GAMEDLL

	int m_flStartTime;

#ifdef HOOK_GAMEDLL

	NOBODY void Spawn_(void);
	NOBODY void Precache_(void);
	NOBODY int Save_(CSave &save);
	NOBODY int Restore_(CRestore &restore);
	NOBODY void Think_(void);

#endif // HOOK_GAMEDLL

};/* size: 408, cachelines: 7, members: 3 */

#endif // H_CYCLER_H

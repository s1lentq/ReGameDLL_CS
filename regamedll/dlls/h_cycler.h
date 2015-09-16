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

/* <cb93c> ../cstrike/dlls/h_cycler.cpp:35 */
class CCycler: public CBaseMonster
{
public:
	virtual void Spawn(void);
	virtual int Save(CSave &save);
	virtual int Restore(CRestore &restore);
	virtual int ObjectCaps(void)
	{
		return ObjectCaps_();
	}
	virtual int TakeDamage(entvars_t *pevInflictor, entvars_t *pevAttacker, float flDamage, int bitsDamageType);

	// Don't treat as a live target
	virtual BOOL IsAlive(void)
	{
		return FALSE;
	}
	virtual void Think(void);
	virtual void Use(CBaseEntity *pActivator, CBaseEntity *pCaller, USE_TYPE useType, float value);

#ifdef HOOK_GAMEDLL

	void Spawn_(void);
	int Save_(CSave &save);
	int Restore_(CRestore &restore);
	int ObjectCaps_(void)
	{
		return (CBaseEntity::ObjectCaps() | FCAP_IMPULSE_USE);
	}
	int TakeDamage_(entvars_t *pevInflictor, entvars_t *pevAttacker, float flDamage, int bitsDamageType);
	void Think_(void);
	void Use_(CBaseEntity *pActivator, CBaseEntity *pCaller, USE_TYPE useType, float value);

#endif // HOOK_GAMEDLL

public:
	void GenericCyclerSpawn(char *szModel, Vector vecMin, Vector vecMax);

public:
	static TYPEDESCRIPTION IMPLEMENT_ARRAY(m_SaveData)[1];

	int m_animate;

};/* size: 408, cachelines: 7, members: 3 */

// we should get rid of all the other cyclers and replace them with this.

/* <cb9b2> ../cstrike/dlls/h_cycler.cpp:67 */
class CGenericCycler: public CCycler
{
public:
	virtual void Spawn(void);

#ifdef HOOK_GAMEDLL

	void Spawn_(void);

#endif // HOOK_GAMEDLL

};/* size: 408, cachelines: 7, members: 1 */

// Probe droid imported for tech demo compatibility

/* <cba04> ../cstrike/dlls/h_cycler.cpp:80 */
class CCyclerProbe: public CCycler
{
public:
	virtual void Spawn(void);

#ifdef HOOK_GAMEDLL

	void Spawn_(void);

#endif // HOOK_GAMEDLL

};/* size: 408, cachelines: 7, members: 1 */

/* <cba56> ../cstrike/dlls/h_cycler.cpp:218 */
class CCyclerSprite: public CBaseEntity
{
public:
	virtual void Spawn(void);
	virtual void Restart(void);
	virtual int Save(CSave &save);
	virtual int Restore(CRestore &restore);
	virtual int ObjectCaps(void)
	{
		return ObjectCaps_();
	}
	virtual int TakeDamage(entvars_t *pevInflictor, entvars_t *pevAttacker, float flDamage, int bitsDamageType);
	virtual void Think(void);
	virtual void Use(CBaseEntity *pActivator, CBaseEntity *pCaller, USE_TYPE useType, float value);

#ifdef HOOK_GAMEDLL

	void Spawn_(void);
	void Restart_(void);
	int Save_(CSave &save);
	int Restore_(CRestore &restore);
	int ObjectCaps_(void)
	{
		return (CBaseEntity::ObjectCaps() | FCAP_DONT_SAVE | FCAP_IMPULSE_USE);
	}
	int TakeDamage_(entvars_t *pevInflictor, entvars_t *pevAttacker, float flDamage, int bitsDamageType);
	void Think_(void);
	void Use_(CBaseEntity *pActivator, CBaseEntity *pCaller, USE_TYPE useType, float value);

#endif // HOOK_GAMEDLL

public:
	void Animate(float frames);
	inline int ShouldAnimate(void)
	{
		return (m_animate && m_maxFrame > 1.0);
	}

public:
	static TYPEDESCRIPTION IMPLEMENT_ARRAY(m_SaveData)[3];

	int m_animate;
	float m_lastTime;
	float m_maxFrame;
	int m_renderfx;
	int m_rendermode;
	float m_renderamt;
	vec3_t m_rendercolor;

};/* size: 188, cachelines: 3, members: 9 */


/* <cbbc0> ../cstrike/dlls/h_cycler.cpp:344 */
class CWeaponCycler: public CBasePlayerWeapon
{
public:
	virtual void Spawn(void);
	virtual int GetItemInfo(ItemInfo *p)
	{
		return 0;
	}
	virtual BOOL Deploy(void);
	virtual void Holster(int skiplocal = 0);
	virtual int iItemSlot(void)
	{
		return 1;
	}
	virtual void PrimaryAttack(void);
	virtual void SecondaryAttack(void);

#ifdef HOOK_GAMEDLL

	void Spawn_(void);
	BOOL Deploy_(void);
	void Holster_(int skiplocal = 0);
	void PrimaryAttack_(void);
	void SecondaryAttack_(void);

#endif // HOOK_GAMEDLL

public:
	int m_iszModel;
	int m_iModel;

};/* size: 344, cachelines: 6, members: 3 */

// Flaming Wreakage

/* <cbc13> ../cstrike/dlls/h_cycler.cpp:427 */
class CWreckage: public CBaseMonster
{
public:
	virtual void Spawn(void);
	virtual void Precache(void);
	virtual int Save(CSave &save);
	virtual int Restore(CRestore &restore);
	virtual void Think(void);

#ifdef HOOK_GAMEDLL

	void Spawn_(void);
	void Precache_(void);
	int Save_(CSave &save);
	int Restore_(CRestore &restore);
	void Think_(void);

#endif // HOOK_GAMEDLL

public:
	static TYPEDESCRIPTION IMPLEMENT_ARRAY(m_SaveData)[1];

	int m_flStartTime;

};/* size: 408, cachelines: 7, members: 3 */

// linked objects
C_DLLEXPORT void cycler(entvars_t *pev);
C_DLLEXPORT void cycler_prdroid(entvars_t *pev);
C_DLLEXPORT void cycler_sprite(entvars_t *pev);
C_DLLEXPORT void cycler_weapon(entvars_t *pev);
C_DLLEXPORT void cycler_wreckage(entvars_t *pev);

#endif // H_CYCLER_H

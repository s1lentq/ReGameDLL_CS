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

class CCycler: public CBaseMonster
{
public:
	virtual void Spawn();
	virtual int Save(CSave &save);
	virtual int Restore(CRestore &restore);
	virtual int ObjectCaps() { return (CBaseEntity::ObjectCaps() | FCAP_IMPULSE_USE); }
	virtual int TakeDamage(entvars_t *pevInflictor, entvars_t *pevAttacker, float flDamage, int bitsDamageType);

	// Don't treat as a live target
	virtual BOOL IsAlive() { return FALSE; }
	virtual void Think();
	virtual void Use(CBaseEntity *pActivator, CBaseEntity *pCaller, USE_TYPE useType, float value);

#ifdef HOOK_GAMEDLL

	void Spawn_();
	int Save_(CSave &save);
	int Restore_(CRestore &restore);
	int TakeDamage_(entvars_t *pevInflictor, entvars_t *pevAttacker, float flDamage, int bitsDamageType);
	void Think_();
	void Use_(CBaseEntity *pActivator, CBaseEntity *pCaller, USE_TYPE useType, float value);

#endif

public:
	void GenericCyclerSpawn(char *szModel, Vector vecMin, Vector vecMax);

public:
	static TYPEDESCRIPTION IMPL(m_SaveData)[1];

	int m_animate;
};

// we should get rid of all the other cyclers and replace them with this.
class CGenericCycler: public CCycler
{
public:
	virtual void Spawn();

#ifdef HOOK_GAMEDLL

	void Spawn_();

#endif

};

// Probe droid imported for tech demo compatibility
class CCyclerProbe: public CCycler
{
public:
	virtual void Spawn();

#ifdef HOOK_GAMEDLL

	void Spawn_();

#endif

};

class CCyclerSprite: public CBaseEntity
{
public:
	virtual void Spawn();
	virtual void Restart();
	virtual int Save(CSave &save);
	virtual int Restore(CRestore &restore);
	virtual int ObjectCaps() { return (CBaseEntity::ObjectCaps() | FCAP_DONT_SAVE | FCAP_IMPULSE_USE); }
	virtual int TakeDamage(entvars_t *pevInflictor, entvars_t *pevAttacker, float flDamage, int bitsDamageType);
	virtual void Think();
	virtual void Use(CBaseEntity *pActivator, CBaseEntity *pCaller, USE_TYPE useType, float value);

#ifdef HOOK_GAMEDLL

	void Spawn_();
	void Restart_();
	int Save_(CSave &save);
	int Restore_(CRestore &restore);
	int TakeDamage_(entvars_t *pevInflictor, entvars_t *pevAttacker, float flDamage, int bitsDamageType);
	void Think_();
	void Use_(CBaseEntity *pActivator, CBaseEntity *pCaller, USE_TYPE useType, float value);

#endif

public:
	void Animate(float frames);
	inline int ShouldAnimate() { return (m_animate && m_maxFrame > 1.0f); }

public:
	static TYPEDESCRIPTION IMPL(m_SaveData)[3];

	int m_animate;
	float m_lastTime;
	float m_maxFrame;
	int m_renderfx;
	int m_rendermode;
	float m_renderamt;
	vec3_t m_rendercolor;
};

class CWeaponCycler: public CBasePlayerWeapon
{
public:
	virtual void Spawn();
	virtual int GetItemInfo(ItemInfo *p) { return 0; }
	virtual BOOL Deploy();
	virtual void Holster(int skiplocal = 0);
	virtual int iItemSlot() { return 1; }
	virtual void PrimaryAttack();
	virtual void SecondaryAttack();

#ifdef HOOK_GAMEDLL

	void Spawn_();
	BOOL Deploy_();
	void Holster_(int skiplocal = 0);
	void PrimaryAttack_();
	void SecondaryAttack_();

#endif

public:
	int m_iszModel;
	int m_iModel;
};

// Flaming Wreakage
class CWreckage: public CBaseMonster
{
public:
	virtual void Spawn();
	virtual void Precache();
	virtual int Save(CSave &save);
	virtual int Restore(CRestore &restore);
	virtual void Think();

#ifdef HOOK_GAMEDLL

	void Spawn_();
	void Precache_();
	int Save_(CSave &save);
	int Restore_(CRestore &restore);
	void Think_();

#endif

public:
	static TYPEDESCRIPTION IMPL(m_SaveData)[1];

	int m_flStartTime;
};

#endif // H_CYCLER_H

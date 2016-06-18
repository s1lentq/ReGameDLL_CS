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

class CCycler: public CBaseMonster {
public:
	virtual void Spawn() = 0;
	virtual int Save(CSave &save) = 0;
	virtual int Restore(CRestore &restore) = 0;
	virtual int ObjectCaps() = 0;
	virtual BOOL TakeDamage(entvars_t *pevInflictor, entvars_t *pevAttacker, float flDamage, int bitsDamageType) = 0;

	// Don't treat as a live target
	virtual BOOL IsAlive() = 0;
	virtual void Think() = 0;
	virtual void Use(CBaseEntity *pActivator, CBaseEntity *pCaller, USE_TYPE useType, float value) = 0;
public:
	int m_animate;
};

// we should get rid of all the other cyclers and replace them with this.
class CGenericCycler: public CCycler {
public:
	virtual void Spawn() = 0;
};

// Probe droid imported for tech demo compatibility
class CCyclerProbe: public CCycler {
public:
	virtual void Spawn() = 0;
};

class CCyclerSprite: public CBaseEntity {
public:
	virtual void Spawn() = 0;
	virtual void Restart() = 0;
	virtual int Save(CSave &save) = 0;
	virtual int Restore(CRestore &restore) = 0;
	virtual int ObjectCaps() = 0;
	virtual BOOL TakeDamage(entvars_t *pevInflictor, entvars_t *pevAttacker, float flDamage, int bitsDamageType) = 0;
	virtual void Think() = 0;
	virtual void Use(CBaseEntity *pActivator, CBaseEntity *pCaller, USE_TYPE useType, float value) = 0;
public:
	inline int ShouldAnimate() { return (m_animate && m_maxFrame > 1.0f); }
public:
	int m_animate;
	float m_lastTime;
	float m_maxFrame;
	int m_renderfx;
	int m_rendermode;
	float m_renderamt;
	vec3_t m_rendercolor;
};

class CWeaponCycler: public CBasePlayerWeapon {
public:
	virtual void Spawn() = 0;
	virtual int GetItemInfo(ItemInfo *p) = 0;
	virtual BOOL Deploy() = 0;
	virtual void Holster(int skiplocal = 0) = 0;
	virtual int iItemSlot() = 0;
	virtual void PrimaryAttack() = 0;
	virtual void SecondaryAttack() = 0;
public:
	int m_iszModel;
	int m_iModel;
};

// Flaming Wreakage
class CWreckage: public CBaseMonster {
public:
	virtual void Spawn() = 0;
	virtual void Precache() = 0;
	virtual int Save(CSave &save) = 0;
	virtual int Restore(CRestore &restore) = 0;
	virtual void Think() = 0;
public:
	int m_flStartTime;
};

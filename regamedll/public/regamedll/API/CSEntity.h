/*
*
*    This program is free software; you can redistribute it and/or modify it
*    under the terms of the GNU General Public License as published by the
*    Free Software Foundation; either version 2 of the License, or (at
*    your option) any later version.
*
*    This program is distributed in the hope that it will be useful, but
*    WITHOUT ANY WARRANTY; without even the implied warranty of
*    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
*    General Public License for more details.
*
*    You should have received a copy of the GNU General Public License
*    along with this program; if not, write to the Free Software Foundation,
*    Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
*
*    In addition, as a special exception, the author gives permission to
*    link the code of this program with the Half-Life Game Engine ("HL
*    Engine") and Modified Game Libraries ("MODs") developed by Valve,
*    L.L.C ("Valve").  You must obey the GNU General Public License in all
*    respects for all of the code used other than the HL Engine and MODs
*    from Valve.  If you modify this file, you may extend this exception
*    to your version of the file, but you are not obligated to do so.  If
*    you do not wish to do so, delete this exception statement from your
*    version.
*
*/

#pragma once

class CBaseEntity;
class CCSEntity
{
public:
	CCSEntity() :
		m_pContainingEntity(nullptr),
		m_pevLastInflictor(nullptr)
	{
		m_ucDmgPenetrationLevel = 0;
	}

	virtual ~CCSEntity() {}
	virtual void FireBullets(int iShots, Vector &vecSrc, Vector &vecDirShooting, Vector &vecSpread, float flDistance, int iBulletType, int iTracerFreq, int iDamage, entvars_t *pevAttacker);
	virtual void FireBuckshots(ULONG cShots, Vector &vecSrc, Vector &vecDirShooting, Vector &vecSpread, float flDistance, int iTracerFreq, int iDamage, entvars_t *pevAttacker);
	virtual Vector FireBullets3(Vector &vecSrc, Vector &vecDirShooting, float vecSpread, float flDistance, int iPenetration, int iBulletType, int iDamage, float flRangeModifier, entvars_t *pevAttacker, bool bPistol, int shared_rand);

	CBaseEntity *BaseEntity() const;

public:
	CBaseEntity *m_pContainingEntity;
	unsigned char m_ucDmgPenetrationLevel; // penetration level of the damage caused by the inflictor
	entvars_t *m_pevLastInflictor;

private:
#if defined(_MSC_VER)
#pragma region reserve_data_Region
#endif
	char CCSEntity_Reserve[0x3FF7];

	virtual void func_reserve1() {};
	virtual void func_reserve2() {};
	virtual void func_reserve3() {};
	virtual void func_reserve4() {};
	virtual void func_reserve5() {};
	virtual void func_reserve6() {};
	virtual void func_reserve7() {};
	virtual void func_reserve8() {};
	virtual void func_reserve9() {};
	virtual void func_reserve10() {};
	virtual void func_reserve11() {};
	virtual void func_reserve12() {};
	virtual void func_reserve13() {};
	virtual void func_reserve14() {};
	virtual void func_reserve15() {};
	virtual void func_reserve16() {};
	virtual void func_reserve17() {};
	virtual void func_reserve18() {};
	virtual void func_reserve19() {};
	virtual void func_reserve20() {};
	virtual void func_reserve21() {};
	virtual void func_reserve22() {};
	virtual void func_reserve23() {};
	virtual void func_reserve24() {};
	virtual void func_reserve25() {};
	virtual void func_reserve26() {};
	virtual void func_reserve27() {};
	virtual void func_reserve28() {};
	virtual void func_reserve29() {};
	virtual void func_reserve30() {};
#if defined(_MSC_VER)
#pragma endregion
#endif
};

// Inlines
inline CBaseEntity *CCSEntity::BaseEntity() const
{
	return this->m_pContainingEntity;
}

inline void CBaseEntity::SetDmgPenetrationLevel(int iPenetrationLevel)
{
#ifdef REGAMEDLL_API
	CSEntity()->m_ucDmgPenetrationLevel = iPenetrationLevel;
#endif
}

inline void CBaseEntity::ResetDmgPenetrationLevel()
{
#ifdef REGAMEDLL_API
	CSEntity()->m_ucDmgPenetrationLevel = 0;
#endif
}

inline int CBaseEntity::GetDmgPenetrationLevel() const
{
#ifdef REGAMEDLL_API
	return CSEntity()->m_ucDmgPenetrationLevel;
#else
	return 0;
#endif
}

inline void CBaseEntity::KilledInflicted(entvars_t* pevInflictor, entvars_t *pevAttacker, int iGib)
{
#ifdef REGAMEDLL_API
	CSEntity()->m_pevLastInflictor = pevInflictor;
#else
	g_pevLastInflictor = pevInflictor;
#endif

	Killed(pevAttacker, iGib);

#ifdef REGAMEDLL_API
	CSEntity()->m_pevLastInflictor = nullptr;
#else
	g_pevLastInflictor = nullptr;
#endif
}

inline entvars_t* CBaseEntity::GetLastInflictor()
{
#ifdef REGAMEDLL_API
	return CSEntity()->m_pevLastInflictor;
#else
	return g_pevLastInflictor;
#endif
}

class CCSDelay: public CCSEntity
{
public:

private:
	int CCSDelay_Reserve[0x100];
};

class CCSAnimating: public CCSDelay
{
public:

private:
	int CCSAnimating_Reserve[0x100];
};

class CCSToggle: public CCSAnimating
{
public:

private:
	int CCSToggle_Reserve[0x100];
};

class CCSMonster: public CCSToggle
{
public:

private:
	int CCSMonster_Reserve[0x100];
};

#define CSENTITY_API_INTERFACE_VERSION "CSENTITY_API_INTERFACE_VERSION003"

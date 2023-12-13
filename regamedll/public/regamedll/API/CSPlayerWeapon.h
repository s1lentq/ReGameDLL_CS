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

enum SecondaryAtkState : uint8_t 
{
	WEAPON_SECONDARY_ATTACK_NONE = 0,
	WEAPON_SECONDARY_ATTACK_SET,
	WEAPON_SECONDARY_ATTACK_BLOCK
};

class CBasePlayerWeapon;
class CCSPlayerWeapon: public CCSPlayerItem
{
public:
	CCSPlayerWeapon() :
		m_iStateSecondaryAttack(WEAPON_SECONDARY_ATTACK_NONE)
	{
	}

	virtual BOOL DefaultDeploy(char *szViewModel, char *szWeaponModel, int iAnim, char *szAnimExt, int skiplocal = 0);
	virtual int DefaultReload(int iClipSize, int iAnim, float fDelay);
	virtual bool DefaultShotgunReload(int iAnim, int iStartAnim, float fDelay, float fStartDelay, const char *pszReloadSound1 = nullptr, const char *pszReloadSound2 = nullptr);
	virtual void KickBack(float up_base, float lateral_base, float up_modifier, float lateral_modifier, float up_max, float lateral_max, int direction_change);
	virtual void SendWeaponAnim(int iAnim, int skiplocal = 0);

	CBasePlayerWeapon *BasePlayerWeapon() const;

public:
	SecondaryAtkState m_iStateSecondaryAttack;
	float m_flBaseDamage;
};

// Inlines
inline CBasePlayerWeapon *CCSPlayerWeapon::BasePlayerWeapon() const
{
	return reinterpret_cast<CBasePlayerWeapon *>(this->m_pContainingEntity);
}


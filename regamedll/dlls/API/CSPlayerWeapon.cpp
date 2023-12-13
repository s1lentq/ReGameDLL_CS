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

#include "precompiled.h"

EXT_FUNC BOOL CCSPlayerWeapon::DefaultDeploy(char *szViewModel, char *szWeaponModel, int iAnim, char *szAnimExt, int skiplocal)
{
	return BasePlayerWeapon()->DefaultDeploy(szViewModel, szWeaponModel, iAnim, szAnimExt, skiplocal);
}

EXT_FUNC int CCSPlayerWeapon::DefaultReload(int iClipSize, int iAnim, float fDelay)
{
	return BasePlayerWeapon()->DefaultReload(iClipSize, iAnim, fDelay);
}

EXT_FUNC bool CCSPlayerWeapon::DefaultShotgunReload(int iAnim, int iStartAnim, float fDelay, float fStartDelay, const char *pszReloadSound1, const char *pszReloadSound2)
{
	return BasePlayerWeapon()->DefaultShotgunReload(iAnim, iStartAnim, fDelay, fStartDelay, pszReloadSound1, pszReloadSound2);
}

EXT_FUNC void CCSPlayerWeapon::KickBack(float up_base, float lateral_base, float up_modifier, float lateral_modifier, float up_max, float lateral_max, int direction_change)
{
	BasePlayerWeapon()->KickBack(up_base, lateral_base, up_modifier, lateral_modifier, up_max, lateral_max, direction_change);
}

EXT_FUNC void CCSPlayerWeapon::SendWeaponAnim(int iAnim, int skiplocal)
{
	BasePlayerWeapon()->SendWeaponAnim(iAnim, skiplocal);
}

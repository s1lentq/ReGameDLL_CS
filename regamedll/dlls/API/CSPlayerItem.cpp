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

EXT_FUNC void CCSPlayerItem::SetItemInfo(ItemInfo *pInfo)
{
	Q_memcpy(&m_ItemInfo, pInfo, sizeof(m_ItemInfo));
}

#ifdef REGAMEDLL_API
int CBasePlayerItem::iPosition()        const { return CSPlayerItem()->m_ItemInfo.iPosition; }
const char *CBasePlayerItem::pszAmmo1() const { return CSPlayerItem()->m_ItemInfo.pszAmmo1; }
int CBasePlayerItem::iMaxAmmo1()        const { return CSPlayerItem()->m_ItemInfo.iMaxAmmo1; }
const char *CBasePlayerItem::pszAmmo2() const { return CSPlayerItem()->m_ItemInfo.pszAmmo2; }
int CBasePlayerItem::iMaxAmmo2()        const { return CSPlayerItem()->m_ItemInfo.iMaxAmmo2; }
const char *CBasePlayerItem::pszName()  const { return CSPlayerItem()->m_ItemInfo.pszName; }
int CBasePlayerItem::iMaxClip()         const { return CSPlayerItem()->m_ItemInfo.iMaxClip; }
int CBasePlayerItem::iWeight()          const { return CSPlayerItem()->m_ItemInfo.iWeight; }
int CBasePlayerItem::iFlags()           const { return CSPlayerItem()->m_ItemInfo.iFlags; }
#endif

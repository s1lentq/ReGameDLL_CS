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

#include "archtypes.h"
#include "regamedll_api.h"
#include "regamedll_interfaces_impl.h"

// Observer_IsValidTarget
typedef IHookChainImpl<class CBasePlayer *, class CBasePlayer *, class CBasePlayer *, int, bool> CReGameHook_Observer_IsValidTarget;
typedef IHookChainRegistryImpl<class CBasePlayer *, class CBasePlayer *, class CBasePlayer *, int, bool> CReGameHookRegistry_Observer_IsValidTarget;

// GetForceCamera
typedef IHookChainImpl<int, class CBasePlayer *> CReGameHook_GetForceCamera;
typedef IHookChainRegistryImpl<int, class CBasePlayer *> CReGameHookRegistry_GetForceCamera;

class CReGameHookchains : public IReGameHookchains {
public:
	CReGameHookRegistry_Observer_IsValidTarget m_Observer_IsValidTarget;
	CReGameHookRegistry_GetForceCamera m_GetForceCamera;

public:
	virtual IReGameHookRegistry_Observer_IsValidTarget* Observer_IsValidTarget();
	virtual IReGameHookRegistry_GetForceCamera* GetForceCamera();
};

extern CReGameHookchains g_ReGameHookchains;
extern ReGameFuncs_t g_ReGameApiFuncs;

class CReGameApi : public IReGameApi {
public:
	virtual int GetMajorVersion();
	virtual int GetMinorVersion();

	virtual const ReGameFuncs_t *GetFuncs();
	virtual IReGameHookchains *GetHookchains();
};

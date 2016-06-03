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

#include "maintypes.h"
#include "regamedll_interfaces.h"

#define __API_VHOOK(fname)\
	fname##_

#ifndef HOOK_GAMEDLL

#define __API_HOOK __API_VHOOK
#define __MAKE_VHOOK(fname)\
	fname

#define LINK_HOOK_CLASS_VOID_CHAIN(className, functionName, args, ...)\
	void className::functionName args {\
		g_ReGameHookchains.m_##className##_##functionName.callChain(&className::functionName##_, this, __VA_ARGS__);\
	}
#define LINK_HOOK_CLASS_VOID_CHAIN2(className, functionName)\
	void className::functionName() {\
		g_ReGameHookchains.m_##className##_##functionName.callChain(&className::functionName##_, this);\
	}

#define LINK_HOOK_CLASS_CHAIN(ret, className, functionName, args, ...)\
	ret className::functionName args {\
		return g_ReGameHookchains.m_##className##_##functionName.callChain(&className::functionName##_, this, __VA_ARGS__);\
	}
#define LINK_HOOK_CLASS_CHAIN2(ret, className, functionName)\
	ret className::functionName() {\
		return g_ReGameHookchains.m_##className##_##functionName.callChain(&className::functionName##_, this);\
	}

#define LINK_HOOK_CLASS_VOID_CUSTOM_CHAIN(className, customPrefix, functionName, args, ...)\
	void className::functionName args {\
		g_ReGameHookchains.m_##customPrefix##_##functionName.callChain(&className::functionName##_, this, __VA_ARGS__);\
	}
#define LINK_HOOK_CLASS_VOID_CUSTOM_CHAIN2(className, customPrefix, functionName)\
	void className::functionName() {\
		g_ReGameHookchains.m_##customPrefix##_##functionName.callChain(&className::functionName##_, this);\
	}

#define LINK_HOOK_CLASS_CUSTOM_CHAIN(ret, className, customPrefix, functionName, args, ...)\
	ret className::functionName args {\
		return g_ReGameHookchains.m_##customPrefix##_##functionName.callChain(&className::functionName##_, this, __VA_ARGS__);\
	}
#define LINK_HOOK_CLASS_CUSTOM_CHAIN2(ret, className, customPrefix, functionName)\
	ret className::functionName() {\
		return g_ReGameHookchains.m_##customPrefix##_##functionName.callChain(&className::functionName##_, this);\
	}

#define LINK_HOOK_VOID_CHAIN(functionName, args, ...)\
	void functionName args {\
		g_ReGameHookchains.m_##functionName.callChain(functionName##_, __VA_ARGS__);\
	}

#define LINK_HOOK_CHAIN(ret, functionName, args, ...)\
	ret functionName args {\
		return g_ReGameHookchains.m_##functionName.callChain(functionName##_, __VA_ARGS__);\
	}

#define LINK_HOOK_VOID_CHAIN2(functionName)\
	void functionName() {\
		g_ReGameHookchains.m_##functionName.callChain(functionName##_);\
	}

#define LINK_HOOK_CHAIN2(ret, functionName)\
	ret functionName() {\
		return g_ReGameHookchains.m_##functionName.callChain(functionName##_);\
	}

#endif

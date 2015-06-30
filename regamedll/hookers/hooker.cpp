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

HIDDEN Module g_GameDLLModule = { NULL, NULL, NULL, NULL };
HIDDEN Module g_EngineModule = { NULL, NULL, NULL, NULL };

extern const size_t g_BaseOffset;
extern FunctionHook g_FunctionHooks[];
extern AddressRef g_FunctionRefs[];
extern AddressRef g_DataRefs[];

void printAddrRebase(size_t addr,const char *funcName)
{
	static int inum = 0;
	addr += g_BaseOffset - g_GameDLLModule.base;
	printf("#%d. %s - 0x%p\n", ++inum, funcName, (void *)addr);
}

void *GetOriginalFuncAddrOrDie(const char *funcName)
{
	for (FunctionHook *cfh = &g_FunctionHooks[0]; cfh->symbolName; cfh++)
	{
		if (!strcmp(cfh->symbolName, funcName))
			return (void*) cfh->originalAddress;
	}

	regamedll_syserror(__FUNCTION__": Could not find function '%s'", funcName);
	return NULL;
}

void *GetOriginalFuncAddrOrDefault(const char *funcName, void *def)
{
	for (FunctionHook *cfh = &g_FunctionHooks[0]; cfh->symbolName; cfh++)
	{
		if (!strcmp(cfh->symbolName, funcName))
			return (void*)cfh->originalAddress;
	}

	return def;
}

void *GetFuncRefAddrOrDie(const char *funcName)
{
	for (AddressRef *cfh = &g_FunctionRefs[0]; cfh->symbolName; cfh++)
	{
		if (!strcmp(cfh->symbolName, funcName))
			return (void*)cfh->originalAddress;
	}

	regamedll_syserror(__FUNCTION__": Could not find function '%s'", funcName);
	return NULL;
}

void *GetFuncRefAddrOrDefault(const char *funcName, void *def)
{
	for (AddressRef *cfh = &g_FunctionRefs[0]; cfh->symbolName; cfh++)
	{
		if (!strcmp(cfh->symbolName, funcName))
			return (void*)cfh->originalAddress;
	}

	return def;
}

int HookGameDLL(size_t gameAddr, size_t engAddr)
{
	if (gameAddr == NULL
		|| !FindModuleByAddress(gameAddr, &g_GameDLLModule)
		|| !FindModuleByAddress(engAddr, &g_EngineModule))
	{
		return (FALSE);
	}

	// Find all addresses
	bool success = true;

	AddressRef *refData = g_DataRefs;
	while (refData->symbolName != NULL)
	{
		if (!GetAddress(&g_GameDLLModule, (Address *)refData, g_BaseOffset))
		{
#if _DEBUG
			printf(__FUNCTION__ ": symbol not found \"%s\", symbol index: %i\n", refData->symbolName, refData->symbolIndex);
			success = false;
#endif // _DEBUG
		}
		refData++;
	}

	AddressRef *refFunc = g_FunctionRefs;
	while (refFunc->symbolName != NULL)
	{
		if (!GetAddress(&g_GameDLLModule, (Address *)refFunc, g_BaseOffset))
		{
#if _DEBUG
			printf(__FUNCTION__ ": symbol not found \"%s\", symbol index: %i\n", refData->symbolName, refData->symbolIndex);
			success = false;
#endif // _DEBUG
		}
		refFunc++;
	}

	FunctionHook *hookFunc = g_FunctionHooks;
	while (hookFunc->handlerFunc != NULL)
	{
		if (!GetAddress(&g_GameDLLModule, (Address*)hookFunc, g_BaseOffset))
		{
#if _DEBUG
			printf(__FUNCTION__ ": symbol not found \"%s\", symbol index: %i\n", refData->symbolName, refData->symbolIndex);
			success = false;
#endif // _DEBUG
		}
		hookFunc++;
	}

	if (!success)
	{
#if _DEBUG
		printf(__FUNCTION__ ": failed to hook gamedll!\n");
#endif // _DEBUG
		return (FALSE);
	}

#ifdef _WIN32
	Module hlds_exe;
	if (!FindModuleByName("hlds.exe", &hlds_exe) && !FindModuleByName("hl.exe", &hlds_exe))
		return (FALSE);

	TestSuite_Init(&g_EngineModule, &hlds_exe, g_FunctionRefs);

#endif // _WIN32

	refData = g_DataRefs;
	while (refData->addressRef != NULL)
	{
		if (!FindDataRef(&g_GameDLLModule, refData))
			return (FALSE);
		refData++;
	}

	refFunc = g_FunctionRefs;
	while (refFunc->addressRef != NULL)
	{
		if (!FindDataRef(&g_GameDLLModule, refFunc))
			return (FALSE);
		refFunc++;
	}

	// Actually hook all things
	if (!g_ReGameDLLRuntimeConfig.disableAllHooks)
	{
		hookFunc = g_FunctionHooks;
		while (hookFunc->handlerFunc != NULL)
		{
			if (!HookFunction(&g_GameDLLModule, hookFunc))
				return (FALSE);

			hookFunc++;
		}
	}

#ifdef _WIN32
	Regamedll_Debug_Init();
#endif // _WIN32

	return (TRUE);
}

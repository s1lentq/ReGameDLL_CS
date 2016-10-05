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
#include "FileSystem.h"

#ifdef _WIN32
	#include <direct.h>
#else
	#include <unistd.h>
#endif

#define GIVEFNPTRS_TO_DLL_PROCNAME "GiveFnptrsToDll"

#ifdef _WIN32
	#define ORIGINAL_ENGINE_DLL_NAME "swds.dll"
	#define ORIGINAL_GAME_DLL_NAME "mp.dll"
	#define ORIGINAL_FILESYSTEM_DLL_NAME "filesystem_stdio2.dll"
#else
	#define ORIGINAL_ENGINE_DLL_NAME "engine_i486.so"
	#define ORIGINAL_GAME_DLL_NAME "cs.so"
	#define ORIGINAL_FILESYSTEM_DLL_NAME "filesystem_stdio2.so"
#endif

IBaseInterface *CreateFileSystemInterface();
InterfaceReg iface = InterfaceReg(CreateFileSystemInterface, "VFileSystem009");

int HookGameDLL(size_t gameAddr, size_t engAddr);

CSysModule *g_pOriginalFileSystemModule = NULL;
CSysModule *g_pOriginalGameDLLModule = NULL;

CreateInterfaceFn g_OriginalFileSystemFactory = NULL;
IFileSystem *g_pOriginalFileSystem = NULL;

IBaseInterface *CreateFileSystemInterface()
{
	if (g_pOriginalFileSystem)
		return g_pOriginalFileSystem;

	if (g_pOriginalFileSystemModule)
	{
		g_OriginalFileSystemFactory = Sys_GetFactory(g_pOriginalFileSystemModule);
		if (g_OriginalFileSystemFactory)
		{
			int returnCode = 0;
			g_pOriginalFileSystem = reinterpret_cast<IBaseFileSystem *>(g_OriginalFileSystemFactory(FILESYSTEM_INTERFACE_VERSION, &returnCode));
			return g_pOriginalFileSystem;
		}
	}

	return NULL;
}

const char *shrPathGameDLL()
{
	static char szDllFilename[ MAX_PATH ];

#ifdef _WIN32
	_getcwd(szDllFilename, MAX_PATH);
#else
	getcwd(szDllFilename, MAX_PATH);
#endif

	if (g_ReGameDLLRuntimeConfig.IsCzero())
		Q_strcat(szDllFilename, "\\czero\\dlls\\"ORIGINAL_GAME_DLL_NAME);
	else
		Q_strcat(szDllFilename, "\\cstrike\\dlls\\"ORIGINAL_GAME_DLL_NAME);

	return (const char *)szDllFilename;
}

#ifdef _WIN32
BOOL WINAPI DllMain(HINSTANCE hinstDLL, DWORD fdwReason, LPVOID lpvReserved)
{
	if (fdwReason == DLL_PROCESS_ATTACH)
	{
#ifdef HOOK_GAMEDLL
		g_ReGameDLLRuntimeConfig.parseFromCommandLine(GetCommandLineA());

		g_pOriginalGameDLLModule = Sys_LoadModule(shrPathGameDLL());
		g_pOriginalFileSystemModule = Sys_LoadModule(ORIGINAL_FILESYSTEM_DLL_NAME);

		size_t gameAddr = (size_t)Sys_GetProcAddress((void *)g_pOriginalGameDLLModule, GIVEFNPTRS_TO_DLL_PROCNAME);
		size_t engAddr = (size_t)Sys_GetProcAddress(ORIGINAL_ENGINE_DLL_NAME, CREATEINTERFACE_PROCNAME);

		HookGameDLL(gameAddr, engAddr);
#endif
	}
	else if (fdwReason == DLL_PROCESS_DETACH)
	{
		if (g_pOriginalFileSystemModule)
		{
			Sys_UnloadModule(g_pOriginalFileSystemModule);
			g_pOriginalFileSystemModule = NULL;
			g_OriginalFileSystemFactory = NULL;
			g_pOriginalFileSystem = NULL;
		}
		if (g_pOriginalGameDLLModule)
		{
			Sys_UnloadModule(g_pOriginalGameDLLModule);
			g_pOriginalGameDLLModule = NULL;
		}
	}

	return TRUE;
}
#else // _WIN32
void __attribute__((constructor)) DllMainLoad()
{
	g_pOriginalGameDLLModule = Sys_LoadModule(shrPathGameDLL());
	g_pOriginalFileSystemModule = Sys_LoadModule(ORIGINAL_FILESYSTEM_DLL_NAME);

	size_t gameAddr = (size_t)Sys_GetProcAddress((void *)g_pOriginalGameDLLModule, GIVEFNPTRS_TO_DLL_PROCNAME);
	size_t engAddr = (size_t)Sys_GetProcAddress(ORIGINAL_ENGINE_DLL_NAME, CREATEINTERFACE_PROCNAME);

	HookGameDLL(gameAddr, engAddr);
}
void __attribute__((destructor)) DllMainUnload()
{
	if (g_pOriginalFileSystemModule)
	{
		Sys_UnloadModule(g_pOriginalFileSystemModule);
		g_pOriginalFileSystemModule = NULL;
		g_OriginalFileSystemFactory = NULL;
		g_pOriginalFileSystem = NULL;
	}
	if (g_pOriginalGameDLLModule)
	{
		Sys_UnloadModule(g_pOriginalGameDLLModule);
		g_pOriginalGameDLLModule = NULL;
	}
}
#endif // _WIN32

#include "precompiled.h"

// Holds engine functionality callbacks
enginefuncs_t g_engfuncs;
globalvars_t *gpGlobals;

// Receive engine function table from engine.
// This appears to be the _first_ DLL routine called by the engine, so we
// do some setup operations here.
C_DLLEXPORT void WINAPI GiveFnptrsToDll(enginefuncs_t *pEnginefuncsTable, globalvars_t *pGlobals)
{
	Q_memcpy(&g_engfuncs, pEnginefuncsTable, sizeof(enginefuncs_t));
	gpGlobals = pGlobals;

	FileSystem_Init();
	Regamedll_Game_Init();
}

#ifdef _WIN32

// DLL entry point
BOOL WINAPI DllMain(HINSTANCE hinstDLL, DWORD fdwReason, LPVOID lpvReserved)
{
	if (fdwReason == DLL_PROCESS_ATTACH)
	{
	}
	else if (fdwReason == DLL_PROCESS_DETACH)
	{
	}

	return TRUE;
}

#else // _WIN32

void __attribute__((constructor)) DllMainLoad()
{
}

void __attribute__((destructor)) DllMainUnload()
{
}

#endif // _WIN32

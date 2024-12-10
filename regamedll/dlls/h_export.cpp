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
}

#if defined(_LINUX)

void __attribute__((constructor)) DllMainLoad()
{
}

void __attribute__((destructor)) DllMainUnload()
{
}

#endif // _LINUX

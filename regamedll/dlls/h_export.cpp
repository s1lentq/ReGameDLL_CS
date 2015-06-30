#include "precompiled.h"

enginefuncs_t g_engfuncs;
globalvars_t *gpGlobals;

/* <d0737> ../cstrike/dlls/h_export.cpp:58 */
C_DLLEXPORT void WINAPI GiveFnptrsToDll(enginefuncs_t *pEnginefuncsTable,globalvars_t *pGlobals)
{
	memcpy(&g_engfuncs, pEnginefuncsTable, sizeof(enginefuncs_t));
	gpGlobals = pGlobals;
}

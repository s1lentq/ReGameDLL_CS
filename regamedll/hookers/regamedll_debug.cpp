#include "precompiled.h"

std::ofstream g_ReGameDLLDebugLog;

void Regamedll_Debug_logAlloc(size_t sz, void *ptr)
{
	g_ReGameDLLDebugLog << "malloc(" << sz << ") => " << std::hex << (size_t)ptr << "\n";
	g_ReGameDLLDebugLog.flush();
}

void Regamedll_Debug_logRealloc(size_t sz, void *oldPtr, void *newPtr)
{
	g_ReGameDLLDebugLog << "realloc(" << std::hex << (size_t)oldPtr << ", " << sz << ") => " << std::hex << (size_t)newPtr << "\n";
	g_ReGameDLLDebugLog.flush();
}

void Regamedll_Debug_logFree(void *ptr)
{
	g_ReGameDLLDebugLog << "free(" << std::hex << (size_t)ptr << ")\n";
	g_ReGameDLLDebugLog.flush();
}

void Regamedll_Debug_logStrDup(const char *s, void *ptr)
{
	g_ReGameDLLDebugLog << "strdup(" << std::hex << (size_t)ptr << ") => " << s << "\n";
	g_ReGameDLLDebugLog.flush();
}

void Regamedll_Debug_Init(void)
{
	//g_ReGameDLLDebugLog.exceptions(std::ios::badbit | std::ios::failbit);
	//g_ReGameDLLDebugLog.open("d:\\REGAME_SERVER\\regamedll_debug.log", std::ios::out | std::ios::binary);
}

void _print_chat(class CBasePlayer *pPlayer, const char *fmt, ...)
{
	static char Dest[4096];

	va_list ap;
	va_start(ap, fmt);
	vsnprintf(Dest, sizeof(Dest), fmt, ap);
	va_end(ap);

	if (Q_strlen(Dest) < sizeof(Dest) - 2)
		Q_strcat(Dest, "\n");

	else Dest[Q_strlen(Dest) - 1] = '\n';
	
	UTIL_SayText(Dest, (class CBaseEntity *)pPlayer);
}

void _printf2(const char *fmt, ...)
{
	/*
	* check is null, test the demo started before than searches pointer to refs
	*/
	if (&g_engfuncs == NULL || g_engfuncs.pfnServerPrint == NULL)
		return;

	static char Dest[4096];
	va_list ap;
	va_start(ap, fmt);
	vsnprintf(Dest, sizeof(Dest), fmt, ap);
	va_end(ap);

	if (Q_strlen(Dest) < sizeof(Dest) - 2)
		Q_strcat(Dest, "\n");

	else Dest[Q_strlen(Dest) - 1] = '\n';
	
	SERVER_PRINT(Dest);
}

#if defined(HOOK_GAMEDLL) && !defined(REGAMEDLL_UNIT_TESTS)
extern int nCountHook;

void Regamedll_Game_Init(void)
{
#ifdef _WIN32
	if (g_ReGameDLLRuntimeConfig.disableAllHooks)
		return;
#endif // _WIN32

	printf2("[Hooker]: The total number hooks of functions is - %d", nCountHook);
}

#endif // HOOK_GAMEDLL


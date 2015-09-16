#pragma once

#include "osconfig.h"
#include "maintypes.h"
#include "memory.h"

#ifdef _WIN32

extern void Regamedll_Debug_logAlloc(size_t sz, void *ptr);
extern void Regamedll_Debug_logRealloc(size_t sz, void *oldPtr, void *newPtr);
extern void Regamedll_Debug_logFree(void *ptr);
extern void Regamedll_Debug_logStrDup(const char *s, void *ptr);
extern void Regamedll_Debug_Init(void);

#endif // _WIN32

#if defined(HOOK_GAMEDLL) && !defined(REGAMEDLL_UNIT_TESTS)
extern void Regamedll_Game_Init(void);
#endif // HOOK_GAMEDLL

extern void _printf2(const char *fmt, ...);
extern void _print_chat(class CBasePlayer *pPlayer, const char *fmt, ...);

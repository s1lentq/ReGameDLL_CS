#pragma once

#include "osconfig.h"

extern size_t OffsetToRebase(size_t addr);
extern bool GetAddressUsingHook(size_t addr);
extern VirtualTableRef *GetVirtualTableRefAddr(const char *szClassName);
extern void *GetFunctionEntity(const char *szClassName);
extern void printAddrRebase(size_t addr,const char *funcName);
extern FunctionHook *GetFunctionPtrByName(const char *funcName);
extern void *GetOriginalFuncAddrOrDie(const char *funcName);
extern void *GetOriginalFuncAddrOrDefault(const char *funcName, void *def);
extern void *GetFuncRefAddrOrDie(const char *funcName);
extern void *GetFuncRefAddrOrDefault(const char *funcName, void *def);

#if defined(HOOK_GAMEDLL) && !defined(REGAMEDLL_UNIT_TESTS)

extern void Regamedll_Game_Init(void);
extern void _printf2(const char *fmt, ...);
extern void _print_chat(class CBasePlayer *pPlayer, const char *fmt, ...);

#endif // HOOK_GAMEDLL

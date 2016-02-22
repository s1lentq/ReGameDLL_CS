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

#ifdef _WIN32

void *_malloc_mhook_(size_t n);
void *_realloc_mhook_(void *memblock, size_t size);
void _free_mhook_(void *p);
void *_calloc_mhook_(size_t n, size_t s);
void *__nh_malloc_mhook_(size_t n);
char *_strdup_mhook_(const char *s);

#endif // _WIN32

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

extern FunctionHook g_FunctionHooks[];
extern VirtualTableRef g_TableRefs[];
extern AddressRef g_FunctionRefs[];
extern AddressRef g_DataRefs[];

#ifdef _WIN32

void *malloc_wrapper(size_t size);
void *_nh_malloc_wrapper(size_t n);
void *realloc_wrapper(void *orig, size_t newSize);
void free_wrapper(void *mem);
void *calloc_wrapper(size_t count, size_t size);
char *strdup_wrapper(const char *s);
int rand_wrapper();

#endif // _WIN32

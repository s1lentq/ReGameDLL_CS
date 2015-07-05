#pragma once

#include "osconfig.h"

extern void printAddrRebase(size_t addr,const char *funcName);
extern FunctionHook *GetFunctionPtrByName(const char *funcName);
extern void *GetOriginalFuncAddrOrDie(const char *funcName);
extern void *GetOriginalFuncAddrOrDefault(const char *funcName, void *def);
extern void *GetFuncRefAddrOrDie(const char *funcName);
extern void *GetFuncRefAddrOrDefault(const char *funcName, void *def);

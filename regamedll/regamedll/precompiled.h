#ifndef PRECOMPILED_H
#define PRECOMPILED_H
#ifdef _WIN32
#pragma once
#endif

#include "version/appversion.h"

#include "mem.h"
#include "platform.h"
#include "osconfig.h"
#include "sse_mathfun.h"

#include "memory.h"
#include "RegameDLLRuntimeConfig.h"
#include "regamedll_debug.h"

#include "MemPool.h"
#include "engine.h"

#include "dlls.h"
#include "basetypes.h"

#ifdef HOOK_GAMEDLL
#include "hooker.h"
#endif // HOOK_GAMEDLL

//valve libs stuff
#include "tier0/platform.h"
#include "tier0/dbg.h"

#include "interface.h"
#include "utlbuffer.h"
#include "utlrbtree.h"
#include "utlsymbol.h"

//testsuite

#include "testsuite/testsuite.h"
#include "testsuite/funccalls.h"
#include "testsuite/recorder.h"
#include "testsuite/demoplayer.h"

#include "bzip2/bzlib.h"

#endif // PRECOMPILED_H

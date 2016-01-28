#pragma once

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

#ifdef HOOK_GAMEDLL
#include "hooker.h"

// STL containers Visual Studio 6.0
#include "stl/vector"
#include "stl/list"

#endif // HOOK_GAMEDLL

//valve libs stuff
#include "tier0/platform.h"
#include "tier0/dbg.h"

#include "dlls.h"
#include "basetypes.h"

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

#include "hookchains_impl.h"
#include "regamedll_interfaces.h"
#include "regamedll_interfaces_impl.h"
#include "regamedll_api.h"
#include "regamedll_api_impl.h"

#ifdef REGAMEDLL_ADD
#include "regamedll_add.h"
#endif // REGAMEDLL_ADD

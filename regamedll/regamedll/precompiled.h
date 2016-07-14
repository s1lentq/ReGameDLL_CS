#pragma once

#include "version/appversion.h"

#include "osconfig.h"
#include "asmlib.h"
#include "sse_mathfun.h"

#include "MemPool.h"
#include "engine.h"
#include "platform.h"
#include "regamedll_debug.h"

#ifdef HOOK_GAMEDLL
#include "memory.h"
#include "hooker.h"
#include "RegameDLLRuntimeConfig.h"

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

#include "hookchains_impl.h"

#include "regamedll.h"

#include "regamedll_interfaces.h"
#include "regamedll_api.h"

#include "regamedll_interfaces_impl.h"
#include "regamedll_api_impl.h"

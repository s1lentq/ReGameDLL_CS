#include "precompiled.h"

/*
* Globals initialization
*/
#ifndef HOOK_GAMEDLL

DebugOutputLevel outputLevel[NUM_LEVELS] =
{
	{ "bot", DEBUG_BOT },
	{ "career", DEBUG_CAREER },
	{ "tutor", DEBUG_TUTOR },
	{ "stats", DEBUG_STATS },
	{ "hostage", DEBUG_HOSTAGE },
	{ "all", DEBUG_ALL }
};

unsigned int theDebugOutputTypes;
static char theDebugBuffer[DebugBufferSize];

#else // HOOK_GAMEDLL

DebugOutputLevel outputLevel[ NUM_LEVELS ];
unsigned int theDebugOutputTypes;
char theDebugBuffer[ DebugBufferSize ];

#endif // HOOK_GAMEDLL

/* <22fe8b> ../cstrike/dlls/debug.cpp:39 */
NOXREF bool IsDeveloper(void)
{
	return (CVAR_GET_FLOAT("developer") > 0.0);
}

/* <22ff69> ../cstrike/dlls/debug.cpp:45 */
NOXREF void UTIL_DPrintf(DebugOutputType outputType, char *pszMsg, ...)
{
	va_list argptr;
	va_start(argptr, pszMsg);

	if (IsDeveloper())
	{
		if (theDebugOutputTypes & outputType)
		{
#ifdef REGAMEDLL_FIXES
			Q_vsnprintf(theDebugBuffer, DebugBufferSize, pszMsg, argptr);
#else
			vsprintf(theDebugBuffer, pszMsg, argptr);
#endif // REGAMEDLL_FIXES
			SERVER_PRINT(theDebugBuffer);
		}
	}
}

// OVERLOAD
void UTIL_DPrintf(char *pszMsg, ...)
{
	va_list argptr;
	va_start(argptr, pszMsg);

	if (IsDeveloper())
	{
#ifdef REGAMEDLL_FIXES
		Q_vsnprintf(theDebugBuffer, DebugBufferSize, pszMsg, argptr);
#else
		vsprintf(theDebugBuffer, pszMsg, argptr);
#endif // REGAMEDLL_FIXES
		SERVER_PRINT(theDebugBuffer);
	}
}

/* <22fe97> ../cstrike/dlls/debug.cpp:78 */
NOXREF void PrintDebugFlags(void)
{
	char *tmp;
	char *state;
	int remainder = DebugBufferSize;

	theDebugBuffer[0] = 0;
	tmp = BufPrintf(theDebugBuffer, remainder, "mp_debug:\n");

	for (int i = 0; i < NUM_LEVELS - 1; i++)
	{
		DebugOutputLevel *level = &outputLevel[i];
		if (theDebugOutputTypes & level->value)
			state = "on";
		else 
			state = "off";

		tmp = BufPrintf(tmp, remainder, "  %s: %s\n", level->name, state);
	}
	SERVER_PRINT(theDebugBuffer);
}

/* <22fed4> ../cstrike/dlls/debug.cpp:94 */
NOBODY void SetDebugFlag(const char *flagStr, bool state)
{
//	{
//		enum DebugOutputType flag;                            //    96
//		{
//			int i;                                        //    97
//			{
//				class DebugOutputLevel level;         //    99
//				FStrEq(const char *sz1,
//					const char *sz2);  //   100
//			}
//		}
//	}
}

/* <23001f> ../cstrike/dlls/debug.cpp:126 */
NOBODY void PrintDebugFlag(const char *flagStr)
{
//	{
//		enum DebugOutputType flag;                            //   128
//		{
//			int i;                                        //   129
//			{
//				class DebugOutputLevel level;         //   131
//				FStrEq(const char *sz1,
//					const char *sz2);  //   132
//			}
//		}
//	}
}

/* <2300a9> ../cstrike/dlls/debug.cpp:149 */
NOBODY void UTIL_SetDprintfFlags(const char *flagStr)
{
//	IsDeveloper(void);  //   151
//	PrintDebugFlags(void);  //   156
}

/* <23012d> ../cstrike/dlls/debug.cpp:175 */
NOBODY void UTIL_BotDPrintf(char *pszMsg, ...)
{
//	IsDeveloper(void);  //   177
//	{
//		va_list argptr;                                       //   182
//	}
}

/* <230181> ../cstrike/dlls/debug.cpp:193 */
NOBODY void UTIL_CareerDPrintf(char *pszMsg, ...)
{
//	IsDeveloper(void);  //   195
//	{
//		va_list argptr;                                       //   200
//	}
}

/* <2301d5> ../cstrike/dlls/debug.cpp:211 */
NOBODY void UTIL_TutorDPrintf(char *pszMsg, ...)
{
//	IsDeveloper(void);  //   213
//	{
//		va_list argptr;                                       //   218
//	}
}

/* <230229> ../cstrike/dlls/debug.cpp:229 */
NOBODY void UTIL_StatsDPrintf(char *pszMsg, ...)
{
//	IsDeveloper(void);  //   231
//	{
//		va_list argptr;                                       //   236
//	}
}

/* <23027d> ../cstrike/dlls/debug.cpp:247 */
NOBODY void UTIL_HostageDPrintf(char *pszMsg, ...)
{
//	IsDeveloper(void);  //   249
//	{
//		va_list argptr;                                       //   254
//	}
}

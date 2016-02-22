#include "precompiled.h"

/*
* Globals initialization
*/
#ifndef HOOK_GAMEDLL

DebugOutputLevel outputLevel[ NUM_LEVELS ] =
{
	{ "bot",	DEBUG_BOT },
	{ "career",	DEBUG_CAREER },
	{ "tutor",	DEBUG_TUTOR },
	{ "stats",	DEBUG_STATS },
	{ "hostage",	DEBUG_HOSTAGE },
	{ "all",	DEBUG_ALL }
};

unsigned int theDebugOutputTypes;
static char theDebugBuffer[ DebugBufferSize ];

#endif

bool IsDeveloper()
{
	return (CVAR_GET_FLOAT("developer") > 0.0);
}

NOXREF void UTIL_DPrintf(DebugOutputType outputType, char *pszMsg, ...)
{
	if (!IsDeveloper())
		return;

	if (theDebugOutputTypes & outputType)
	{
		va_list argptr;
		va_start(argptr, pszMsg);
		vsprintf(theDebugBuffer, pszMsg, argptr);
		va_end(argptr);

		SERVER_PRINT(theDebugBuffer);
	}
}

void UTIL_DPrintf(char *pszMsg, ...)
{
	if (!IsDeveloper())
		return;

	va_list argptr;
	va_start(argptr, pszMsg);
	vsprintf(theDebugBuffer, pszMsg, argptr);
	va_end(argptr);

	SERVER_PRINT(theDebugBuffer);
}

void PrintDebugFlags()
{
	char *tmp;
	int remainder = DebugBufferSize;

	theDebugBuffer[0] = '\0';
	tmp = BufPrintf(theDebugBuffer, remainder, "mp_debug:\n");

	for (int i = 0; i < NUM_LEVELS - 1; ++i)
	{
		DebugOutputLevel level = outputLevel[i];

		tmp = BufPrintf(tmp, remainder, "  %s: %s\n", level.name, (theDebugOutputTypes & level.value) ? "on" : "off");
	}
	SERVER_PRINT(theDebugBuffer);
}

void SetDebugFlag(const char *flagStr, bool state)
{
	if (flagStr != NULL)
	{
		DebugOutputType flag;
		for (int i = 0; i < ARRAYSIZE(outputLevel); ++i)
		{
			DebugOutputLevel level = outputLevel[ i ];

			if (FStrEq(level.name, flagStr))
			{
				flag = level.value;

				if (state)
					theDebugOutputTypes |= flag;
				else
					theDebugOutputTypes &= ~flag;

				SERVER_PRINT(SharedVarArgs("mp_debug: %s is now %s\n", flagStr, state ? "on" : "off"));
				return;
			}
		}
	}

	SERVER_PRINT(SharedVarArgs("mp_debug: unknown variable '%s'\n", flagStr));
}

void PrintDebugFlag(const char *flagStr)
{
	if (flagStr != NULL)
	{
		DebugOutputType flag;
		for (int i = 0; i < ARRAYSIZE(outputLevel); ++i)
		{
			DebugOutputLevel level = outputLevel[ i ];

			if (FStrEq(level.name, flagStr))
			{
				flag = level.value;
				SERVER_PRINT(SharedVarArgs("mp_debug: %s is %s\n", flagStr, (flag & theDebugOutputTypes) ? "on" : "off"));
				return;
			}
		}
	}

	SERVER_PRINT(SharedVarArgs("mp_debug: unknown variable '%s'\n", flagStr));
}

void UTIL_SetDprintfFlags(const char *flagStr)
{
	if (!IsDeveloper())
		return;

	if (flagStr != NULL && flagStr[0] != '\0')
	{
		if (flagStr[0] == '+')
			SetDebugFlag(&flagStr[1], true);

		else if (flagStr[0] == '-')
			SetDebugFlag(&flagStr[1], false);
		else
			PrintDebugFlag(flagStr);
	}
	else
		PrintDebugFlags();
}

NOXREF void UTIL_BotDPrintf(char *pszMsg, ...)
{
	if (!IsDeveloper())
		return;

	if (theDebugOutputTypes & DEBUG_BOT)
	{
		va_list argptr;
		va_start(argptr, pszMsg);
		vsprintf(theDebugBuffer, pszMsg, argptr);
		va_end(argptr);

		SERVER_PRINT(theDebugBuffer);
	}
}

void UTIL_CareerDPrintf(char *pszMsg, ...)
{
	if (!IsDeveloper())
		return;

	if (theDebugOutputTypes & DEBUG_CAREER)
	{
		va_list argptr;
		va_start(argptr, pszMsg);
		vsprintf(theDebugBuffer, pszMsg, argptr);
		va_end(argptr);

		SERVER_PRINT(theDebugBuffer);
	}
}

NOXREF void UTIL_TutorDPrintf(char *pszMsg, ...)
{
	if (!IsDeveloper())
		return;

	if (theDebugOutputTypes & DEBUG_TUTOR)
	{
		va_list argptr;
		va_start(argptr, pszMsg);
		vsprintf(theDebugBuffer, pszMsg, argptr);
		va_end(argptr);

		SERVER_PRINT(theDebugBuffer);
	}
}

NOXREF void UTIL_StatsDPrintf(char *pszMsg, ...)
{
	if (!IsDeveloper())
		return;

	if (theDebugOutputTypes & DEBUG_STATS)
	{
		va_list argptr;
		va_start(argptr, pszMsg);
		vsprintf(theDebugBuffer, pszMsg, argptr);
		va_end(argptr);

		SERVER_PRINT(theDebugBuffer);
	}
}

NOXREF void UTIL_HostageDPrintf(char *pszMsg, ...)
{
	if (!IsDeveloper())
		return;

	if (theDebugOutputTypes & DEBUG_HOSTAGE)
	{
		va_list argptr;
		va_start(argptr, pszMsg);
		vsprintf(theDebugBuffer, pszMsg, argptr);
		va_end(argptr);

		SERVER_PRINT(theDebugBuffer);
	}
}

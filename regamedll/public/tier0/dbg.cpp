//========= Copyright Valve Corporation, All rights reserved. ============//
//
// Purpose:
//
// $NoKeywords: $
//
//===========================================================================//

#include "precompiled.h"

// Templates to assist in validating pointers:
void _AssertValidReadPtr(void *ptr, int count)
{
#if defined(_WIN32)
	Assert(!IsBadReadPtr(ptr, count));
#else
	Assert(ptr);
#endif

}

void _AssertValidWritePtr(void *ptr, int count)
{
#if defined(_WIN32)
	Assert(!IsBadWritePtr(ptr, count));
#else
	Assert(ptr);
#endif
}

void _AssertValidReadWritePtr(void *ptr, int count)
{
#if defined(_WIN32)
	Assert(!(IsBadWritePtr(ptr, count) || IsBadReadPtr(ptr, count)));
#else
	Assert(ptr);
#endif
}

#if defined(DBGFLAG_ASSERT)
void AssertValidStringPtr(const char *ptr, int maxchar)
{
#if defined(_WIN32)
	Assert(!IsBadStringPtr(ptr, maxchar));
#else
	Assert(ptr);
#endif
}
#endif // DBGFLAG_ASSERT

// Globals
SpewRetval_t DefaultSpewFunc(SpewType_t type, int level, const char *pMsg)
{
	printf("%s", pMsg);

	if (type == SPEW_ASSERT)
		return SPEW_DEBUGGER;
	else if (type == SPEW_ERROR)
		return SPEW_ABORT;
	else
		return SPEW_CONTINUE;
}

static SpewOutputFunc_t s_SpewOutputFunc = DefaultSpewFunc;

static const char *s_pMessage  = nullptr;
static const char *s_pFileName = nullptr;
static int         s_Line      = 0;
static SpewType_t  s_SpewType  = SPEW_MESSAGE;

// Spew output management.
void SpewOutputFunc(SpewOutputFunc_t func)
{
	s_SpewOutputFunc = func ? func : DefaultSpewFunc;
}

SpewOutputFunc_t GetSpewOutputFunc()
{
	if (s_SpewOutputFunc)
	{
		return s_SpewOutputFunc;
	}
	else
	{
		return DefaultSpewFunc;
	}
}

void _ExitOnFatalAssert()
{
	Msg("Fatal assert failed: %s, file %s line %d.  Application exiting.\n", s_pMessage, s_pFileName, s_Line);

#if defined(WIN32)
	TerminateProcess(GetCurrentProcess(), EXIT_FAILURE); // die, die RIGHT NOW! (don't call exit() so destructors will not get run)
#else
	exit(EXIT_FAILURE); // forcefully shutdown of the process without destructors running
#endif
}

// Spew functions
void _SpewInfo(SpewType_t type, const char *pFile, int line)
{
	// Only grab the file name. Ignore the path
	const char *pSlash  = Q_strrchr(pFile, '\\');
	const char *pSlash2 = Q_strrchr(pFile, '/');

	if (pSlash < pSlash2) pSlash = pSlash2;

	s_pFileName = pSlash ? pSlash + 1 : pFile;
	s_Line      = line;
	s_SpewType  = type;
}

SpewRetval_t _SpewMessageV(SpewType_t spewType, int level, const char *pMsgFormat, va_list args)
{
	if (level < 0) level = DBG_DEFAULT_LEVEL;

	static char szTempBuffer[4096]{};
	szTempBuffer[0] = '\0';
	s_pMessage = szTempBuffer;

	// check that we won't artifically truncate the string
	assert(Q_strlen(pMsgFormat) < sizeof(szTempBuffer));

	// Printf the file and line for warning + assert only...
	int len = 0;
	if (spewType == SPEW_ASSERT)
	{
		len = Q_snprintf(szTempBuffer, sizeof(szTempBuffer), "%s (%d) : ", s_pFileName, s_Line);
	}

	if (len == -1)
	{
		return SPEW_ABORT;
	}

	// Create the message....
	len += Q_vsnprintf(&szTempBuffer[len], sizeof(szTempBuffer) - len, pMsgFormat, args);

	// Use normal assert here; to avoid recursion
	assert(len < sizeof(szTempBuffer));

	// Add \n for warning and assert
	if ((spewType == SPEW_ASSERT))
	{
		len += Q_snprintf(&szTempBuffer[len], sizeof(szTempBuffer) - len, "\n");
		Plat_OutputDebugString(szTempBuffer);
	}

	// use normal assert here; to avoid recursion
	assert((size_t)len < (sizeof(szTempBuffer) / sizeof(szTempBuffer[0]) - 1));
	assert(s_SpewOutputFunc);

	// direct it to the appropriate target(s)
	SpewRetval_t ret = s_SpewOutputFunc(spewType, level, szTempBuffer);
	switch (ret)
	{
	// Put the break into the macro so it would occur in the right place
	case SPEW_DEBUGGER:
	{
		if (spewType != SPEW_ASSERT)
			DebuggerBreakIfDebugging();

		break;
	}
	case SPEW_ABORT:
	{
#if defined(WIN32)
		TerminateProcess(GetCurrentProcess(), EXIT_FAILURE); // die, die RIGHT NOW! (don't call exit() so destructors will not get run)
#else
		exit(EXIT_FAILURE); // forcefully shutdown of the process without destructors running
#endif
		break;
	}
	default:
		break;
	}

	return ret;
}

#if defined(_WIN32)
// Returns true if they want to break in the debugger
bool DoNewAssertDialog(const char *pFile, int line, const char *pExpression);
#endif

bool _SpewAssertDialog()
{
#if defined(_WIN32)
	return DoNewAssertDialog(s_pFileName, s_Line, s_pMessage);
#else
	return false;
#endif
}

SpewRetval_t _SpewAssert(const char *pFile, int line, int level, const char *pMsgFormat, ...)
{
	_SpewInfo(SPEW_ASSERT, pFile, line);

	va_list args;
	va_start(args, pMsgFormat);
	SpewRetval_t ret = _SpewMessageV(s_SpewType, level, pMsgFormat, args);
	va_end(args);
	return ret;
}

void _Msg(int level, const char *pMsgFormat, ...)
{
	va_list args;
	va_start(args, pMsgFormat);
	_SpewMessageV(SPEW_MESSAGE, level, pMsgFormat, args);
	va_end(args);
}

void _Warning(int level, const char *pMsgFormat, ...)
{
	va_list args;
	va_start(args, pMsgFormat);
	_SpewMessageV(SPEW_WARNING, level, pMsgFormat, args);
	va_end(args);
}

void _Log(int level, const char *pMsgFormat, ...)
{
	va_list args;
	va_start(args, pMsgFormat);
	_SpewMessageV(SPEW_LOG, level, pMsgFormat, args);
	va_end(args);
}

void Error(const char *pMsgFormat, ...)
{
	va_list args;
	va_start(args, pMsgFormat);
	_SpewMessageV(SPEW_ERROR, DBG_DEFAULT_LEVEL, pMsgFormat, args);
	va_end(args);
}

//========= Copyright Valve Corporation, All rights reserved. ============//
//
// Purpose:
//
// $NoKeywords: $
//
//===========================================================================//

#pragma once

#include "basetypes.h"

#include <math.h>
#include <stdio.h>
#include <stdarg.h>

#define DBG_DEFAULT_LEVEL 0

// Usage model for the Dbg library
//
// 1. Spew.
//
//   Spew can be used in a static and a dynamic mode. The static
//   mode allows us to display assertions and other messages either only
//   in debug builds, or in non-release builds. The dynamic mode allows us to
//   turn on and off certain spew messages while the application is running.
//
//   Static Spew messages:
//
//     Assertions are used to detect and warn about invalid states
//     Spews are used to display a particular status/warning message.
//
//     To use an assertion, use
//
//     Assert((f == 5));
//     AssertMsg((f == 5), ("F needs to be %d here!\n", 5));
//     AssertFunc((f == 5), BadFunc());
//     AssertEquals(f, 5);
//     AssertFloatEquals(f, 5.0f, 1e-3);
//
//     The first will simply report that an assertion failed on a particular
//     code file and line. The second version will display a print-f formatted message
//	   along with the file and line, the third will display a generic message and
//     will also cause the function BadFunc to be executed, and the last two
//	   will report an error if f is not equal to 5 (the last one asserts within
//	   a particular tolerance).
//
//     To use a warning, use
//
//     Warning("Oh I feel so %s all over\n", "yummy");
//
//     Warning will do its magic in only Debug builds. To perform spew in *all*
//     builds, use RelWarning.
//
//	   Three other spew types, Msg, Log, and Error, are compiled into all builds.
//	   These error types do *not* need two sets of parenthesis.
//
//	   Msg("Isn't this exciting %d?", 5);
//	   Error("I'm just thrilled");
//
//   Spew output
//
//     The output of the spew system can be redirected to an externally-supplied
//     function which is responsible for outputting the spew. By default, the
//     spew is simply printed using printf.
//
//     To redirect spew output, call SpewOutput.
//
//     SpewOutputFunc(OutputFunc);
//
//     This will cause OutputFunc to be called every time a spew message is
//     generated. OutputFunc will be passed a spew type and a message to print.
//     It must return a value indicating whether the debugger should be invoked,
//     whether the program should continue running, or whether the program
//     should abort.
//
// 2. Code activation
//
//   To cause code to be run only in debug builds, use DBG_CODE:
//   An example is below.
//
//   DBG_CODE(
//				{
//					int x = 5;
//					++x;
//				}
//          );
//
// 3. Breaking into the debugger.
//
//   To cause an unconditional break into the debugger in debug builds only, use DBG_BREAK
//
//   DBG_BREAK();
//
//	 You can force a break in any build (release or debug) using
//
//	 DebuggerBreak();

// Various types of spew messages
// I'm sure you're asking yourself why SPEW_ instead of DBG_ ?
// It's because DBG_ is used all over the place in windows.h
// For example, DBG_CONTINUE is defined. Feh.
enum SpewType_t
{
	SPEW_MESSAGE = 0,
	SPEW_WARNING,
	SPEW_ASSERT,
	SPEW_ERROR,
	SPEW_LOG,

	SPEW_TYPE_COUNT
};

enum SpewRetval_t
{
	SPEW_DEBUGGER = 0,
	SPEW_CONTINUE,
	SPEW_ABORT
};

// Type of externally defined function used to display debug spew
typedef SpewRetval_t (*SpewOutputFunc_t)(SpewType_t spewType, int level, const char *pMsg);

// Used to redirect spew output
void SpewOutputFunc(SpewOutputFunc_t func);

// Used ot get the current spew output function
SpewOutputFunc_t GetSpewOutputFunc();

// Used to display messages, should never be called directly.
SpewRetval_t	_SpewAssert(const char *pFile, int line, int level, const char *pMsg, ...);
void			_ExitOnFatalAssert();
bool			_SpewAssertDialog();

inline bool ShouldUseNewAssertDialog()
{
#if defined(DBGFLAG_ASSERTDLG)
	return true;		// always show an assert dialog
#else
	return Plat_IsInDebugSession();		// only show an assert dialog if the process is being debugged
#endif // DBGFLAG_ASSERTDLG
}

#define _AssertMsg(_exp, _msg, _executeExp, _bFatal)                                                                 \
	do {                                                                                                             \
		if (!(_exp))                                                                                                 \
		{                                                                                                            \
			SpewRetval_t ret = _SpewAssert(__FILE__, __LINE__, DBG_DEFAULT_LEVEL, _msg);                             \
			if (ret == SPEW_DEBUGGER)                                                                                \
			{                                                                                                        \
				if (!ShouldUseNewAssertDialog() || _SpewAssertDialog())                                              \
					DebuggerBreakIfDebugging();                                                                      \
			}                                                                                                        \
			_executeExp;                                                                                             \
			if (_bFatal)                                                                                             \
				_ExitOnFatalAssert();                                                                                \
		}                                                                                                            \
	} while (0)

#define _AssertMsgWarn(_exp, _msg)                                                                                   \
	if (!(_exp))                                                                                                     \
	{                                                                                                                \
		Warning("%s (%d) : " _msg, __FILE__, __LINE__);                                                              \
	}                                                                                                                \

#define _AssertMsgOnce(_exp, _msg, _bFatal)                                                                          \
	do {                                                                                                             \
		static bool fAsserted = false;                                                                               \
		if (!fAsserted && !(_exp))                                                                                   \
		{                                                                                                            \
			fAsserted = true;                                                                                        \
			_AssertMsg(_exp, _msg, (fAsserted = true), _bFatal);                                                     \
		}                                                                                                            \
	} while (0)

// Spew macros...
// AssertFatal macros
// AssertFatal is used to detect an unrecoverable error condition.
// If enabled, it may display an assert dialog (if DBGFLAG_ASSERTDLG is turned on or running under the debugger),
// and always terminates the application

#if defined(DBGFLAG_ASSERTFATAL)

#define AssertWarn(_exp)												_AssertMsgWarn(_exp, "Assertion Failed: " #_exp)
#define AssertFatal(_exp)												_AssertMsg(_exp, "Assertion Failed: " #_exp, ((void)0), true)
#define AssertFatalOnce(_exp)                                           _AssertMsgOnce(_exp, "Assertion Failed: " #_exp, true)
#define AssertFatalMsg(_exp, _msg)                                      _AssertMsg(_exp, _msg, ((void)0), true)
#define AssertFatalMsgOnce(_exp, _msg)                                  _AssertMsgOnce(_exp, _msg, true)
#define AssertFatalFunc(_exp, _f)                                       _AssertMsg(_exp, "Assertion Failed: " #_exp, _f, true)
#define AssertFatalEquals(_exp, _expectedValue)                         AssertFatalMsg2((_exp) == (_expectedValue), "Expected %d but got %d!", (_expectedValue), (_exp))
#define AssertFatalFloatEquals(_exp, _expectedValue, _tol)              AssertFatalMsg2(fabs((_exp) - (_expectedValue)) <= (_tol), "Expected %f but got %f!", (_expectedValue), (_exp))
#define VerifyFatal(_exp)                                               AssertFatal(_exp)
#define VerifyEqualsFatal(_exp, _expectedValue)                         AssertFatalEquals(_exp, _expectedValue)

#if defined(_DEBUG)
	#define DbgVerifyFatal(_exp)                                        AssertFatal(_exp)
#else
	#define DbgVerifyFatal(_exp)                                        ((void)0)
#endif

#define AssertFatalMsg1(_exp, _msg, a1)                                 AssertFatalMsg(_exp, CDbgFmtMsg(_msg, a1).ToString())
#define AssertFatalMsg2(_exp, _msg, a1, a2)                             AssertFatalMsg(_exp, CDbgFmtMsg(_msg, a1, a2).ToString())
#define AssertFatalMsg3(_exp, _msg, a1, a2, a3)                         AssertFatalMsg(_exp, CDbgFmtMsg(_msg, a1, a2, a3).ToString())
#define AssertFatalMsg4(_exp, _msg, a1, a2, a3, a4)                     AssertFatalMsg(_exp, CDbgFmtMsg(_msg, a1, a2, a3, a4).ToString())
#define AssertFatalMsg5(_exp, _msg, a1, a2, a3, a4, a5)                 AssertFatalMsg(_exp, CDbgFmtMsg(_msg, a1, a2, a3, a4, a5).ToString())
#define AssertFatalMsg6(_exp, _msg, a1, a2, a3, a4, a5, a6)             AssertFatalMsg(_exp, CDbgFmtMsg(_msg, a1, a2, a3, a4, a5, a6).ToString())
#define AssertFatalMsg7(_exp, _msg, a1, a2, a3, a4, a5, a6, a7)         AssertFatalMsg(_exp, CDbgFmtMsg(_msg, a1, a2, a3, a4, a5, a6, a7).ToString())
#define AssertFatalMsg8(_exp, _msg, a1, a2, a3, a4, a5, a6, a7, a8)     AssertFatalMsg(_exp, CDbgFmtMsg(_msg, a1, a2, a3, a4, a5, a6, a7, a8).ToString())
#define AssertFatalMsg9(_exp, _msg, a1, a2, a3, a4, a5, a6, a7, a8, a9) AssertFatalMsg(_exp, CDbgFmtMsg(_msg, a1, a2, a3, a4, a5, a6, a7, a8, a9).ToString())

#else // DBGFLAG_ASSERTFATAL

#define AssertWarn(_exp)                                                ((void)0)
#define AssertFatal(_exp)                                               ((void)0)
#define AssertFatalOnce(_exp)                                           ((void)0)
#define AssertFatalMsg(_exp, _msg)                                      ((void)0)
#define AssertFatalMsgOnce(_exp, _msg)                                  ((void)0)
#define AssertFatalFunc(_exp, _f)                                       ((void)0)
#define AssertFatalEquals(_exp, _expectedValue)                         ((void)0)
#define AssertFatalFloatEquals(_exp, _expectedValue, _tol)              ((void)0)
#define VerifyFatal(_exp)                                               (_exp)
#define VerifyEqualsFatal(_exp, _expectedValue)                         (_exp)

#define DbgVerifyFatal(_exp)                                            (_exp)

#define AssertFatalMsg1(_exp, _msg, a1)                                 ((void)0)
#define AssertFatalMsg2(_exp, _msg, a1, a2)                             ((void)0)
#define AssertFatalMsg3(_exp, _msg, a1, a2, a3)                         ((void)0)
#define AssertFatalMsg4(_exp, _msg, a1, a2, a3, a4)                     ((void)0)
#define AssertFatalMsg5(_exp, _msg, a1, a2, a3, a4, a5)                 ((void)0)
#define AssertFatalMsg6(_exp, _msg, a1, a2, a3, a4, a5, a6)             ((void)0)
#define AssertFatalMsg7(_exp, _msg, a1, a2, a3, a4, a5, a6, a7)         ((void)0)
#define AssertFatalMsg8(_exp, _msg, a1, a2, a3, a4, a5, a6, a7, a8)     ((void)0)
#define AssertFatalMsg9(_exp, _msg, a1, a2, a3, a4, a5, a6, a7, a8, a9) ((void)0)

#endif // DBGFLAG_ASSERTFATAL

#if defined(DBGFLAG_ASSERT)

#define Assert(_exp)                                                    _AssertMsg(_exp, "Assertion Failed: " #_exp, ((void)0), false)
#define AssertMsg_(_exp, _msg)                                          _AssertMsg(_exp, _msg, ((void)0), false)
#define AssertOnce(_exp)                                                _AssertMsgOnce(_exp, "Assertion Failed: " #_exp, false)
#define AssertMsgOnce(_exp, _msg)                                       _AssertMsgOnce(_exp, _msg, false)
#define AssertFunc(_exp, _f)                                            _AssertMsg(_exp, "Assertion Failed: " #_exp, _f, false)
#define AssertEquals(_exp, _expectedValue)                              AssertMsg2((_exp) == (_expectedValue), "Expected %d but got %d!", (_expectedValue), (_exp))
#define AssertFloatEquals(_exp, _expectedValue, _tol)                   AssertMsg2(fabs((_exp) - (_expectedValue)) <= (_tol), "Expected %f but got %f!", (_expectedValue), (_exp))
#define Verify(_exp)                                                    (_exp)
#define VerifyEquals(_exp, _expectedValue)                              AssertEquals(_exp, _expectedValue)

#if defined(_DEBUG)
	#define DbgVerify(_exp)                                             (_exp)
	#define DbgAssert(_exp)                                             Assert(_exp)
	#define DbgAssertMsg(_exp, _msg)                                    AssertMsg(_exp, _msg)
	#define DbgAssertMsg1(_exp, _msg, a1)                               AssertMsg1(_exp, _msg, a1)
	#define DbgAssertMsg2(_exp, _msg, a1, a2)                           AssertMsg2(_exp, _msg, a1, a2)
	#define DbgAssertMsg3(_exp, _msg, a1, a2, a3)                       AssertMsg3(_exp, _msg, a1, a2, a3)
	#define DbgAssertMsg4(_exp, _msg, a1, a2, a3)                       AssertMsg4(_exp, _msg, a1, a2, a3, a4)
	#define DbgAssertMsg5(_exp, _msg, a1, a2, a3)                       AssertMsg5(_exp, _msg, a1, a2, a3, a4, a5)
	#define DbgAssertMsg6(_exp, _msg, a1, a2, a3)                       AssertMsg6(_exp, _msg, a1, a2, a3, a4, a5, a6)
	#define DbgAssertMsg7(_exp, _msg, a1, a2, a3)                       AssertMsg7(_exp, _msg, a1, a2, a3, a4, a5, a6, a7)
	#define DbgAssertMsg8(_exp, _msg, a1, a2, a3)                       AssertMsg8(_exp, _msg, a1, a2, a3, a4, a5, a6, a7, a8)
	#define DbgAssertMsg9(_exp, _msg, a1, a2, a3)                       AssertMsg9(_exp, _msg, a1, a2, a3, a4, a5, a6, a7, a8, a9)
#else
	#define DbgVerify(_exp)                                             ((void)0)
	#define DbgAssert(_exp)                                             ((void)0)
	#define DbgAssertMsg(_exp, _msg)                                    ((void)0)
	#define DbgAssertMsg1(_exp, _msg, a1)                               ((void)0)
	#define DbgAssertMsg2(_exp, _msg, a1, a2)                           ((void)0)
	#define DbgAssertMsg3(_exp, _msg, a1, a2, a3)                       ((void)0)
	#define DbgAssertMsg4(_exp, _msg, a1, a2, a3)                       ((void)0)
	#define DbgAssertMsg5(_exp, _msg, a1, a2, a3)                       ((void)0)
	#define DbgAssertMsg6(_exp, _msg, a1, a2, a3)                       ((void)0)
	#define DbgAssertMsg7(_exp, _msg, a1, a2, a3)                       ((void)0)
	#define DbgAssertMsg8(_exp, _msg, a1, a2, a3)                       ((void)0)
	#define DbgAssertMsg9(_exp, _msg, a1, a2, a3)                       ((void)0)
#endif

#define AssertMsg(_exp, _msg)                                           AssertMsg_(_exp, _msg)
#define AssertMsg1(_exp, _msg, a1)                                      AssertMsg_(_exp, CDbgFmtMsg(_msg, a1).ToString())
#define AssertMsg2(_exp, _msg, a1, a2)                                  AssertMsg_(_exp, CDbgFmtMsg(_msg, a1, a2).ToString())
#define AssertMsg3(_exp, _msg, a1, a2, a3)                              AssertMsg_(_exp, CDbgFmtMsg(_msg, a1, a2, a3).ToString())
#define AssertMsg4(_exp, _msg, a1, a2, a3, a4)                          AssertMsg_(_exp, CDbgFmtMsg(_msg, a1, a2, a3, a4).ToString())
#define AssertMsg5(_exp, _msg, a1, a2, a3, a4, a5)                      AssertMsg_(_exp, CDbgFmtMsg(_msg, a1, a2, a3, a4, a5).ToString())
#define AssertMsg6(_exp, _msg, a1, a2, a3, a4, a5, a6)                  AssertMsg_(_exp, CDbgFmtMsg(_msg, a1, a2, a3, a4, a5, a6).ToString())
#define AssertMsg6(_exp, _msg, a1, a2, a3, a4, a5, a6)                  AssertMsg_(_exp, CDbgFmtMsg(_msg, a1, a2, a3, a4, a5, a6).ToString())
#define AssertMsg7(_exp, _msg, a1, a2, a3, a4, a5, a6, a7)              AssertMsg_(_exp, CDbgFmtMsg(_msg, a1, a2, a3, a4, a5, a6, a7).ToString())
#define AssertMsg8(_exp, _msg, a1, a2, a3, a4, a5, a6, a7, a8)          AssertMsg_(_exp, CDbgFmtMsg(_msg, a1, a2, a3, a4, a5, a6, a7, a8).ToString())
#define AssertMsg9(_exp, _msg, a1, a2, a3, a4, a5, a6, a7, a8, a9)      AssertMsg_(_exp, CDbgFmtMsg(_msg, a1, a2, a3, a4, a5, a6, a7, a8, a9).ToString())

#else // DBGFLAG_ASSERT

#define Assert(_exp)                                                    ((void)0)
#define AssertMsg(_exp, _msg)                                           ((void)0)
#define AssertOnce(_exp)                                                ((void)0)
#define AssertMsgOnce(_exp, _msg)                                       ((void)0)
#define AssertFunc(_exp, _f)                                            ((void)0)
#define AssertEquals(_exp, _expectedValue)                              ((void)0)
#define AssertFloatEquals(_exp, _expectedValue, _tol)                   ((void)0)

#define Verify(_exp)                                                    ((void)0)
#define VerifyEquals(_exp, _expectedValue)                              ((void)0)

#define DbgVerify(_exp)                                                 ((void)0)
#define DbgAssert(_exp)                                                 ((void)0)
#define DbgAssertMsg(_exp, _msg)                                        ((void)0)
#define DbgAssertMsg1(_exp, _msg, a1)                                   ((void)0)
#define DbgAssertMsg2(_exp, _msg, a1, a2)                               ((void)0)
#define DbgAssertMsg3(_exp, _msg, a1, a2, a3)                           ((void)0)
#define DbgAssertMsg4(_exp, _msg, a1, a2, a3)                           ((void)0)
#define DbgAssertMsg5(_exp, _msg, a1, a2, a3)                           ((void)0)
#define DbgAssertMsg6(_exp, _msg, a1, a2, a3)                           ((void)0)
#define DbgAssertMsg7(_exp, _msg, a1, a2, a3)                           ((void)0)
#define DbgAssertMsg8(_exp, _msg, a1, a2, a3)                           ((void)0)
#define DbgAssertMsg9(_exp, _msg, a1, a2, a3)                           ((void)0)

#define AssertMsg1(_exp, _msg, a1)                                      ((void)0)
#define AssertMsg2(_exp, _msg, a1, a2)                                  ((void)0)
#define AssertMsg3(_exp, _msg, a1, a2, a3)                              ((void)0)
#define AssertMsg4(_exp, _msg, a1, a2, a3, a4)                          ((void)0)
#define AssertMsg5(_exp, _msg, a1, a2, a3, a4, a5)                      ((void)0)
#define AssertMsg6(_exp, _msg, a1, a2, a3, a4, a5, a6)                  ((void)0)
#define AssertMsg6(_exp, _msg, a1, a2, a3, a4, a5, a6)                  ((void)0)
#define AssertMsg7(_exp, _msg, a1, a2, a3, a4, a5, a6, a7)              ((void)0)
#define AssertMsg8(_exp, _msg, a1, a2, a3, a4, a5, a6, a7, a8)          ((void)0)
#define AssertMsg9(_exp, _msg, a1, a2, a3, a4, a5, a6, a7, a8, a9)      ((void)0)

#endif // DBGFLAG_ASSERT

// default level versions (level 0)
#define Msg(...)        _Msg    (0, __VA_ARGS__)
#define Warning(...)    _Warning(0, __VA_ARGS__)
#define Log(...)        _Log    (0, __VA_ARGS__)

// These looked at the "developer" functions
#define DevMsg(...)     _Msg    (1, __VA_ARGS__)
#define DevWarning(...) _Warning(1, __VA_ARGS__)
#define DevLog(...)     _Log    (1, __VA_ARGS__)

// These are always compiled in
void _Msg    (int level, const char *pMsg, ...);
void _Warning(int level, const char *pMsg, ...);
void _Log    (int level, const char *pMsg, ...);
void Error   (const char *pMsg, ...);

// You can use this macro like a runtime assert macro.
// If the condition fails, then Error is called with the message. This macro is called
// like AssertMsg, where msg must be enclosed in parenthesis:
//
// ErrorIfNot(bCondition, ("a b c %d %d %d", 1, 2, 3));
#define ErrorIfNot(condition, msg) \
	if ((condition))               \
		;                          \
				else               \
	{                              \
		Error msg;                 \
	}

// Code macros, debugger interface
#if defined(_DEBUG)
	#define DBG_CODE(_code)          if (0) ; else { _code }
	#define DBG_DCODE(_g, _l, _code) if (IsSpewActive(_g, _l)) { _code } else {}
	#define DBG_BREAK()              DebuggerBreakIfDebugging()
#else // _DEBUG
	#define DBG_CODE(_code)          ((void)0)
	#define DBG_DCODE(_g, _l, _code) ((void)0)
	#define DBG_BREAK()              ((void)0)
#endif // _DEBUG

// Templates to assist in validating pointers:
// Have to use these stubs so we don't have to include windows.h here.
void _AssertValidReadPtr(void *ptr, int count = 1);
void _AssertValidWritePtr(void *ptr, int count = 1);
void _AssertValidReadWritePtr(void *ptr, int count = 1);

#if defined(DBGFLAG_ASSERT)
	void AssertValidStringPtr(const char *ptr, int maxchar = 0xFFFFFF);
	template <class T> inline void AssertValidReadPtr(T *ptr, int count = 1)      { _AssertValidReadPtr((void *)ptr, count); }
	template <class T> inline void AssertValidWritePtr(T *ptr, int count = 1)     { _AssertValidWritePtr((void *)ptr, count); }
	template <class T> inline void AssertValidReadWritePtr(T *ptr, int count = 1) { _AssertValidReadWritePtr((void *)ptr, count); }
	#define AssertValidThis() AssertValidReadWritePtr(this, sizeof(*this))
#else
	#define AssertValidStringPtr(...)    ((void)0)
	#define AssertValidReadPtr(...)      ((void)0)
	#define AssertValidWritePtr(...)     ((void)0)
	#define AssertValidReadWritePtr(...) ((void)0)
	#define AssertValidThis()            ((void)0)
#endif // #if defined(DBGFLAG_ASSERT)

// Macro to protect functions that are not reentrant
#if defined(_DEBUG)
class CReentryGuard
{
public:
	CReentryGuard(int *pSemaphore)
		: m_pSemaphore(pSemaphore)
	{
		++(*m_pSemaphore);
	}
	~CReentryGuard()
	{
		--(*m_pSemaphore);
	}

private:
	int *m_pSemaphore;
};

#define ASSERT_NO_REENTRY()          \
	static int fSemaphore##__LINE__; \
	Assert(!fSemaphore##__LINE__);   \
	CReentryGuard ReentryGuard##__LINE__(&fSemaphore##__LINE__)
#else // _DEBUG
#define ASSERT_NO_REENTRY()
#endif // _DEBUG

// Inline string formatter
class CDbgFmtMsg
{
public:
	CDbgFmtMsg(const char *pszFormat, ...)
	{
		va_list arg_ptr;
		va_start(arg_ptr, pszFormat);
		_vsnprintf(m_szBuf, sizeof(m_szBuf) - 1, pszFormat, arg_ptr);
		va_end(arg_ptr);

		m_szBuf[sizeof(m_szBuf) - 1] = '\0';
	}

	operator const char *() const
	{
		return m_szBuf;
	}

	const char *ToString() const
	{
		return m_szBuf;
	}

private:
	char m_szBuf[256];
};

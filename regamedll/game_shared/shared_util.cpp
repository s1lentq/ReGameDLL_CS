#include "precompiled.h"

/*
* Globals initialization
*/
#ifndef HOOK_GAMEDLL

static char s_shared_token[ 1500 ];
static char s_shared_quote = '\"';

#else

char s_shared_token[ 1500 ];
char s_shared_quote;

#endif // HOOK_GAMEDLL

/* <2d4a66> ../game_shared/shared_util.cpp:50 */
NOBODY uchar32 *SharedWVarArgs(uchar32 *format, ...)
{
//	{
//		va_list argptr;                                       //    52
//		intconst BufLen;                                      //    53
//		intconst NumBuffers;                                  //    54
//		wchar_t string;                                       //    55
//		int curstring;                                        //    56
//	}
}

/* <2d4b0a> ../game_shared/shared_util.cpp:68 */
char *SharedVarArgs(char *format, ...)
{
	va_list argptr;
	const int BufLen = 1024;
	const int NumBuffers = 4;

	static char string[ NumBuffers ][ BufLen ];
	static int curstring = 0;

	curstring = (curstring + 1) % NumBuffers;

	va_start(argptr, format);
	Q_vsnprintf(string[ curstring ], BufLen, format, argptr);
	va_end(argptr);

	return string[ curstring ];
}

/* <2d4ba1> ../game_shared/shared_util.cpp:90 */
char *BufPrintf(char *buf, int &len, const char *fmt, ...)
{
	va_list argptr;
	if (len > 0)
	{
		va_start(argptr, fmt);
		Q_vsnprintf(buf, len, fmt, argptr);
		va_end(argptr);

		len -= Q_strlen(buf);
		return buf + Q_strlen(buf);
	}
	return NULL;
}

/* <2d4c0d> ../game_shared/shared_util.cpp:106 */
NOBODY uchar32 *BufWPrintf(uchar32 *buf, int &len, const uchar32 *fmt, ...)
{
//	{
//		va_list argptr;                                       //   111
//	}
}

/* <2d4c7e> ../game_shared/shared_util.cpp:122 */
NOBODY const uchar32 *NumAsWString(int val)
{
//	{
//		intconst BufLen;                                      //   124
//		intconst NumBuffers;                                  //   125
//		wchar_t string;                                       //   126
//		int curstring;                                        //   127
//		int len;                                              //   131
//	}
}

/* <2d4d11> ../game_shared/shared_util.cpp:137 */
const char *NumAsString(int val)
{
	const int BufLen = 16;
	const int NumBuffers = 4;

	static char string[ NumBuffers ][ BufLen ];
	static int curstring = 0;

	int len = 16;

	curstring = (curstring + 1) % 4;
	BufPrintf(string[curstring], len, "%d", val);

	return string[curstring];
}

// Returns the token parsed by SharedParse()

/* <2d4da4> ../game_shared/shared_util.cpp:155 */
char *SharedGetToken(void)
{
	return s_shared_token;
}

// Returns the token parsed by SharedParse()

/* <2d4dbf> ../game_shared/shared_util.cpp:164 */
NOXREF void SharedSetQuoteChar(char c)
{
	s_shared_quote = c;
}

// Parse a token out of a string

/* <2d4de7> ../game_shared/shared_util.cpp:173 */
NOBODY const char *SharedParse(const char *data)
{
//	
//skipwhite:                                                            //   185
//	{
//		int c;                                                //   175
//		int len;                                              //   176
//	}
}

// Returns true if additional data is waiting to be processed on this line

/* <2d4e40> ../game_shared/shared_util.cpp:247 */
NOBODY bool SharedTokenWaiting(const char *buffer)
{
//	{
//		const char *p;                                      //   249
//	}
}

#include "precompiled.h"

char s_shared_token[1500];
char s_shared_quote = '\"';

NOXREF wchar_t *SharedWVarArgs(wchar_t *format, ...)
{
	va_list argptr;
	const int BufLen = 1024;
	const int NumBuffers = 4;
	static wchar_t string[NumBuffers][BufLen];
	static int curstring = 0;

	curstring = (curstring + 1) % NumBuffers;

	va_start(argptr, format);
	Q_vsnwprintf(string[curstring], BufLen, format, argptr);
	va_end(argptr);

	return string[curstring];
}

char *SharedVarArgs(char *format, ...)
{
	va_list argptr;
	const int BufLen = 1024;
	const int NumBuffers = 4;

	static char string[NumBuffers][BufLen];
	static int curstring = 0;

	curstring = (curstring + 1) % NumBuffers;

	va_start(argptr, format);
	Q_vsnprintf(string[curstring], BufLen, format, argptr);
	va_end(argptr);

	return string[curstring];
}

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

	return nullptr;
}

wchar_t *BufWPrintf(wchar_t *buf, int &len, const wchar_t *fmt, ...)
{
	if (len <= 0)
		return nullptr;

	va_list argptr;

	va_start(argptr, fmt);
	Q_vsnwprintf(buf, len, fmt, argptr);
	va_end(argptr);

	len -= wcslen(buf);
	return buf + wcslen(buf);
}

NOXREF const wchar_t *NumAsWString(int val)
{
	const int BufLen = 16;
	const int NumBuffers = 4;
	static wchar_t string[NumBuffers][BufLen];
	static int curstring = 0;

	curstring = (curstring + 1) % NumBuffers;

	int len = BufLen;
	BufWPrintf(string[curstring], len, L"%d", val);
	return string[curstring];
}

const char *NumAsString(int val)
{
	const int BufLen = 16;
	const int NumBuffers = 4;

	static char string[NumBuffers][BufLen];
	static int curstring = 0;

	int len = 16;

	curstring = (curstring + 1) % NumBuffers;
	BufPrintf(string[curstring], len, "%d", val);

	return string[curstring];
}

// Returns the token parsed by SharedParse()
char *SharedGetToken()
{
	return s_shared_token;
}

// Returns the token parsed by SharedParse()
NOXREF void SharedSetQuoteChar(char c)
{
	s_shared_quote = c;
}

// Parse a token out of a string
char *SharedParse(char *data)
{
	int c;
	int len;

	len = 0;
	s_shared_token[0] = '\0';

	if (!data)
		return nullptr;

// skip whitespace
skipwhite:
	while ((c = *data) <= ' ')
	{
		if (c == 0)
		{
			// end of file;
			return nullptr;
		}

		data++;
	}

	// skip // comments till the next line
	if (c == '/' && data[1] == '/')
	{
		while (*data && *data != '\n')
			data++;

		// start over new line
		goto skipwhite;
	}

	// handle quoted strings specially: copy till the end or another quote
	if (c == s_shared_quote)
	{
		// skip starting quote
		data++;

		while (true)
		{
			// get char and advance
			c = *data++;
			if (c == s_shared_quote || !c)
			{
				s_shared_token[len] = '\0';
				return data;
			}

			s_shared_token[len++] = c;
		}
	}

	// parse single characters
	if (c == '{' || c == '}'|| c == ')'|| c == '(' || c == '\'' || c == ',')
	{
		s_shared_token[len++] = c;
		s_shared_token[len] = '\0';
		return data + 1;
	}

	// parse a regular word
	do
	{
		s_shared_token[len] = c;
		data++;
		len++;
		c = *data;

		if (c == '{' || c == '}'|| c == ')'|| c == '(' || c == '\'' || c == ',')
			break;

	}
	while (c > 32);

	s_shared_token[len] = '\0';
	return data;
}

// Returns true if additional data is waiting to be processed on this line
bool SharedTokenWaiting(const char *buffer)
{
	const char *p;

	p = buffer;
	while (*p && *p != '\n')
	{
		if (!isspace(*p) || isalnum(*p))
			return true;

		p++;
	}

	return false;
}

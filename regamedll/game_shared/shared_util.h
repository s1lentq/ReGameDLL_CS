/*
*
*   This program is free software; you can redistribute it and/or modify it
*   under the terms of the GNU General Public License as published by the
*   Free Software Foundation; either version 2 of the License, or (at
*   your option) any later version.
*
*   This program is distributed in the hope that it will be useful, but
*   WITHOUT ANY WARRANTY; without even the implied warranty of
*   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
*   General Public License for more details.
*
*   You should have received a copy of the GNU General Public License
*   along with this program; if not, write to the Free Software Foundation,
*   Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
*
*   In addition, as a special exception, the author gives permission to
*   link the code of this program with the Half-Life Game Engine ("HL
*   Engine") and Modified Game Libraries ("MODs") developed by Valve,
*   L.L.C ("Valve").  You must obey the GNU General Public License in all
*   respects for all of the code used other than the HL Engine and MODs
*   from Valve.  If you modify this file, you may extend this exception
*   to your version of the file, but you are not obligated to do so.  If
*   you do not wish to do so, delete this exception statement from your
*   version.
*
*/

#ifndef SHARED_UTIL
#define SHARED_UTIL
#ifdef _WIN32
#pragma once
#endif

#ifdef HOOK_GAMEDLL

#define s_shared_token (*ps_shared_token)
#define s_shared_quote (*ps_shared_quote)

#endif // HOOK_GAMEDLL

extern char s_shared_token[ 1500 ];
extern char s_shared_quote;

NOBODY uchar32 *SharedWVarArgs(uchar32 *format, ...);
char *SharedVarArgs(char *format, ...);
char *BufPrintf(char *buf, int &len, const char *fmt, ...);
NOBODY uchar32 *BufWPrintf(uchar32 *buf, int &len, const uchar32 *fmt, ...);
NOBODY const uchar32 *NumAsWString(int val);
const char *NumAsString(int val);
char *SharedGetToken(void);
NOXREF void SharedSetQuoteChar(char c);
NOBODY const char *SharedParse(const char *data);
NOBODY bool SharedTokenWaiting(const char *buffer);

/* <db469> ../game_shared/shared_util.h:46 */
inline char *CloneString(const char *str)
{
	if (!str)
	{
		char *cloneStr = new char[1];
		cloneStr[0] = '\0';
		return cloneStr;
	}
	char *cloneStr = new char [Q_strlen(str) + 1];
	Q_strcpy(cloneStr, str);
	return cloneStr;
}

#ifdef _WIN32

inline wchar_t *CloneWString(const wchar_t *str)
{
	wchar_t *cloneStr = new wchar_t [wcslen(str) + 1];
	wcscpy(cloneStr, str);
	return cloneStr;
}

#endif // _WIN32

#endif // SHARED_UTIL

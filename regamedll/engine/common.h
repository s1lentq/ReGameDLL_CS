/*
*
*    This program is free software; you can redistribute it and/or modify it
*    under the terms of the GNU General Public License as published by the
*    Free Software Foundation; either version 2 of the License, or (at
*    your option) any later version.
*
*    This program is distributed in the hope that it will be useful, but
*    WITHOUT ANY WARRANTY; without even the implied warranty of
*    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
*    General Public License for more details.
*
*    You should have received a copy of the GNU General Public License
*    along with this program; if not, write to the Free Software Foundation,
*    Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
*
*    In addition, as a special exception, the author gives permission to
*    link the code of this program with the Half-Life Game Engine ("HL
*    Engine") and Modified Game Libraries ("MODs") developed by Valve,
*    L.L.C ("Valve").  You must obey the GNU General Public License in all
*    respects for all of the code used other than the HL Engine and MODs
*    from Valve.  If you modify this file, you may extend this exception
*    to your version of the file, but you are not obligated to do so.  If
*    you do not wish to do so, delete this exception statement from your
*    version.
*
*/

#ifndef COMMON_H
#define COMMON_H
#ifdef _WIN32
#pragma once
#endif

#include "maintypes.h"
#include "bspfile.h"
#include "FileSystem.h"
#include "info.h"

// Don't allow overflow
#define SIZEBUF_CHECK_OVERFLOW		0
#define SIZEBUF_ALLOW_OVERFLOW		BIT(0)
#define SIZEBUF_OVERFLOWED		BIT(1)

/* <6ae> ../common/common.h:82 */
typedef struct sizebuf_s
{
	const char *buffername;
	uint16_t flags;
	byte *data;
	int maxsize;
	int cursize;
} sizebuf_t;

/* <270aa> ../common/common.h:297 */
typedef struct downloadtime_s
{
	qboolean bUsed;
	float fTime;
	int nBytesRemaining;
} downloadtime_t;

/* <19fa2> ../common/common.h:303 */
typedef struct incomingtransfer_s
{
	qboolean doneregistering;
	int percent;
	qboolean downloadrequested;
	downloadtime_t rgStats[8];
	int nCurStat;
	int nTotalSize;
	int nTotalToTransfer;
	int nRemainingToTransfer;
	float fLastStatusUpdate;
	qboolean custom;
} incomingtransfer_t;

//#define Q_functions
#ifndef Q_functions

#ifndef _WIN32
#define _strlwr(p) for (int i = 0; p[i] != 0; i++) p[i] = tolower(p[i]);
#endif

#ifdef _WIN32
#define printf2 _printf2
#define chatf _print_chat
#endif // _WIN32

#define Q_close _close
#define Q_write _write
#define Q_memset memset
#define Q_memcpy memcpy
#define Q_strlen strlen
#define Q_memcmp memcmp
#define Q_strcpy strcpy
#define Q_strncpy strncpy
#define Q_strrchr strrchr
#define Q_strcat strcat
#define Q_strncat strncat
#define Q_strcmp strcmp
#define Q_strncmp strncmp
//#define Q_strcasecmp _stricmp		// Use Q_stricmp
//#define Q_strncasecmp _strnicmp	// Use Q_strnicmp
#define Q_strdup _strdup
#define Q_stricmp _stricmp
#define Q_strnicmp _strnicmp
#define Q_strstr strstr
#define Q_strchr strchr
#define Q_strrchr strrchr
#define Q_strlwr _strlwr
#define Q_sprintf sprintf
#define Q_snprintf _snprintf
#define Q_atoi atoi
#define Q_atof atof
//#define Q_strtoull strtoull
//#define Q_FileNameCmp FileNameCmp
#define Q_vsnprintf _vsnprintf
#else // Q_functions
void Q_strcpy(char *dest, const char *src);
int Q_strlen(const char *str);
NOBODY void Q_memset(void *dest, int fill, int count);
NOBODY void Q_memcpy(void *dest, const void *src, int count);
NOBODY int Q_memcmp(void *m1, void *m2, int count);
NOBODY void Q_strncpy(char *dest, const char *src, int count);
NOBODY char *Q_strrchr(char *s, char c);
NOBODY void Q_strcat(char *dest, char *src);
NOBODY int Q_strcmp(const char *s1, const char *s2);
NOBODY int Q_strncmp(const char *s1, const char *s2, int count);
NOBODY int Q_strncasecmp(const char *s1, const char *s2, int n);
NOBODY int Q_strcasecmp(const char *s1, const char *s2);
NOBODY int Q_stricmp(const char *s1, const char *s2);
NOBODY int Q_strnicmp(const char *s1, const char *s2, int n);
NOBODY int Q_atoi(const char *str);
NOBODY float Q_atof(const char *str);
NOBODY char *Q_strlwr(char *src);
NOBODY int Q_FileNameCmp(char *file1, char *file2);
NOBODY char *Q_strstr(const char *s1, const char *search);
NOBODY uint64 Q_strtoull(char *str);

#endif // Q_functions

#endif // COMMON_H

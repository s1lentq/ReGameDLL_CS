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

#pragma once

#ifdef _WIN32
const char CORRECT_PATH_SEPARATOR = '\\';
const char INCORRECT_PATH_SEPARATOR = '/';
#else
const char CORRECT_PATH_SEPARATOR = '/';
const char INCORRECT_PATH_SEPARATOR = '\\';
#endif

#if !defined(_WIN32)
inline char *_strupr(char *start)
{
      char *str = start;
      while (str && *str)
      {
              *str = (char)toupper(*str);
              str++;
      }

      return start;
}

inline char *_strlwr(char *start)
{
      char *str = start;
      while (str && *str)
      {
              *str = (char)tolower(*str);
              str++;
      }

      return start;
}
#endif

#if defined(ASMLIB_H) && defined(HAVE_OPT_STRTOOLS)
	#define Q_memset A_memset
	#define Q_memcpy A_memcpy
	#define Q_memcmp A_memcmp
	#define Q_memmove A_memmove
	#define Q_strlen A_strlen
	#define Q_strcpy A_strcpy
	#define Q_strncpy strncpy
	#define Q_strcat A_strcat
	#define Q_strncat strncat
	#define Q_strcmp A_strcmp
	#define Q_strncmp strncmp
	#define Q_strdup _strdup
	#define Q_stricmp A_stricmp
	#define Q_strnicmp _strnicmp
	#define Q_strstr A_strstr
	#define Q_strchr strchr
	#define Q_strrchr strrchr
	#define Q_strtok strtok
	#define Q_strlwr A_strtolower
	#define Q_strupr A_strtoupper
	#define Q_sprintf sprintf
	#define Q_snprintf _snprintf
	#define Q_vsnprintf _vsnprintf
	#define Q_vsnwprintf _vsnwprintf
	#define Q_atoi atoi
	#define Q_atof atof
	#define Q_sqrt M_sqrt
	#define Q_min M_min
	#define Q_max M_max
	#define Q_clamp M_clamp
	#define Q_abs abs
	#define Q_fabs fabs
	#define Q_tan tan
	#define Q_atan atan
	#define Q_atan2 atan2
	#define Q_acos acos
	#define Q_cos cos
	#define Q_sin sin
	#define Q_pow pow
	#define Q_fmod fmod
#else
	#define Q_memset memset
	#define Q_memcpy memcpy
	#define Q_memcmp memcmp
	#define Q_memmove memmove
	#define Q_strlen strlen
	#define Q_strcpy strcpy
	#define Q_strncpy strncpy
	#define Q_strcat strcat
	#define Q_strncat strncat
	#define Q_strcmp strcmp
	#define Q_strncmp strncmp
	#define Q_strdup _strdup
	#define Q_stricmp _stricmp
	#define Q_strnicmp _strnicmp
	#define Q_strstr strstr
	#define Q_strchr strchr
	#define Q_strrchr strrchr
	#define Q_strtok strtok
	#define Q_strlwr _strlwr
	#define Q_strupr _strupr
	#define Q_sprintf sprintf
	#define Q_snprintf _snprintf
	#define Q_vsnprintf _vsnprintf
	#define Q_vsnwprintf _vsnwprintf
	#define Q_atoi atoi
	#define Q_atof atof
	#define Q_sqrt sqrt
	#define Q_min min
	#define Q_max max
	#define Q_clamp clamp
	#define Q_abs abs
	#define Q_fabs fabs
	#define Q_tan tan
	#define Q_atan atan
	#define Q_atan2 atan2
	#define Q_acos acos
	#define Q_cos cos
	#define Q_sin sin
	#define Q_pow pow
	#define Q_fmod fmod
#endif // #if defined(ASMLIB_H) && defined(HAVE_OPT_STRTOOLS)

// size - sizeof(buffer)
inline char *Q_strlcpy(char *dest, const char *src, size_t size) {
	Q_strncpy(dest, src, size - 1);
	dest[size - 1] = '\0';
	return dest;
}

// a safe variant of strcpy that truncates the result to fit in the destination buffer
template <size_t size>
char *Q_strlcpy(char (&dest)[size], const char *src) {
	return Q_strlcpy(static_cast<char *>(dest), src, size);
}

// safely concatenate two strings.
// a variant of strcat that truncates the result to fit in the destination buffer
inline size_t Q_strlcat(char *dest, const char *src, size_t maxDestSize)
{
	size_t srclen; // Length of source string
	size_t dstlen; // Length of destination string

	// Figure out how much room is left
	dstlen = strlen(dest);
	size_t unRemainingSize = maxDestSize - dstlen - 1;

	// Sanity check in case dest doesn't contain a null termination
	if (dstlen > (maxDestSize - 1))
		dstlen = maxDestSize - 1;

	if (unRemainingSize <= 0 || unRemainingSize > maxDestSize)
	{
		dest[dstlen] = '\0';
		return dstlen; // No room, return immediately
	}

	// Figure out how much room is needed
	srclen = strlen(src);

	// Copy the appropriate amount
	if (srclen > unRemainingSize)
		srclen = unRemainingSize;

	Q_memcpy(dest + dstlen, src, srclen);
	dest[dstlen + srclen] = '\0';
	return dstlen + srclen;
}

template <size_t size>
inline size_t Q_strlcat(char (&dest)[size], const char *src)
{
	return Q_strlcat(static_cast<char *>(dest), src, size);
}

// Force slashes of either type to be = separator character
inline void Q_FixSlashes(char *pname, char separator = CORRECT_PATH_SEPARATOR)
{
	while (*pname)
	{
		if (*pname == INCORRECT_PATH_SEPARATOR || *pname == CORRECT_PATH_SEPARATOR)
		{
			*pname = separator;
		}

		pname++;
	}
}

// strcpy that works correctly with overlapping src and dst buffers
inline char *Q_strcpy_s(char *dst, char *src) {
	int len = Q_strlen(src);
	Q_memmove(dst, src, len + 1);
	return dst;
}

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
#pragma once

#include "regamedll_const.h"

#undef DLLEXPORT
#ifdef _WIN32
	// Attributes to specify an "exported" function, visible from outside the
	// DLL.
	#define DLLEXPORT	__declspec(dllexport)
	// WINAPI should be provided in the windows compiler headers.
	// It's usually defined to something like "__stdcall".

	#define NOINLINE __declspec(noinline)
#else
	#define DLLEXPORT	__attribute__((visibility("default")))
	#define WINAPI		/* */
	#define NOINLINE	__attribute__((noinline))
#endif // _WIN32

// Manual branch optimization for GCC 3.0.0 and newer
#if !defined(__GNUC__) || __GNUC__ < 3
	#define likely(x) (x)
	#define unlikely(x) (x)
#else
	#define likely(x) __builtin_expect(!!(x), 1)
	#define unlikely(x) __builtin_expect(!!(x), 0)
#endif

// Simplified macro for declaring/defining exported DLL functions.  They
// need to be 'extern "C"' so that the C++ compiler enforces parameter
// type-matching, rather than considering routines with mis-matched
// arguments/types to be overloaded functions...
//
// AFAIK, this is os-independent, but it's included here in osdep.h where
// DLLEXPORT is defined, for convenience.
#define C_DLLEXPORT extern "C" DLLEXPORT

enum hash_types_e { CLASSNAME };

// Things that toggle (buttons/triggers/doors) need this
enum TOGGLE_STATE { TS_AT_TOP, TS_AT_BOTTOM, TS_GOING_UP, TS_GOING_DOWN };

typedef struct hash_item_s
{
	entvars_t *pev;
	struct hash_item_s *next;
	struct hash_item_s *lastHash;
	int pevIndex;

} hash_item_t;

typedef struct locksounds
{
	string_t sLockedSound;
	string_t sLockedSentence;
	string_t sUnlockedSound;
	string_t sUnlockedSentence;
	int iLockedSentence;
	int iUnlockedSentence;
	float flwaitSound;
	float flwaitSentence;
	byte bEOFLocked;
	byte bEOFUnlocked;

} locksound_t;

typedef struct hudtextparms_s
{
	float x;
	float y;
	int effect;
	byte r1,g1,b1,a1;
	byte r2,g2,b2,a2;
	float fadeinTime;
	float fadeoutTime;
	float holdTime;
	float fxTime;
	int channel;

} hudtextparms_t;

enum USE_TYPE { USE_OFF, USE_ON, USE_SET, USE_TOGGLE };
enum TRAIN_CODE { TRAIN_SAFE, TRAIN_BLOCKING, TRAIN_FOLLOWING };
enum IGNORE_MONSTERS { ignore_monsters = 1, dont_ignore_monsters = 0, missile = 2 };
enum IGNORE_GLASS { ignore_glass = 1, dont_ignore_glass = 0 };
enum { point_hull = 0, human_hull = 1, large_hull = 2, head_hull = 3 };

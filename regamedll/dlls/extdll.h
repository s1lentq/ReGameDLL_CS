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

#pragma warning(disable:4244)		// int or float down-conversion
#pragma warning(disable:4305)		// int or float data truncation
#pragma warning(disable:4201)		// nameless struct/union
#pragma warning(disable:4514)		// unreferenced inline function removed
#pragma warning(disable:4100)		// unreferenced formal parameter

#include "archtypes.h"
#include "maintypes.h"
#include "strtools.h"

#ifdef _WIN32
	#define WIN32_LEAN_AND_MEAN // Exclude rarely-used stuff from Windows headers
	#define NOWINRES
	#define NOSERVICE
	#define NOMCX
	#define NOIME
	#include "winsani_in.h"
	#include "windows.h"
	#include "winsani_out.h"
	#undef PlaySound
#else
	#include <limits.h>
	#include <stdarg.h>
	#include <string.h>
#endif // _WIN32

// Misc C-runtime library headers
#include "stdio.h"
#include "stdlib.h"
#include "math.h"

// Header file containing definition of globalvars_t and entvars_t
typedef int EOFFSET;					// More explicit than "int"
typedef unsigned int func_t;
typedef float vec_t;					// needed before including progdefs.h

// Vector class
#include "vector.h"

// Defining it as a (bogus) struct helps enforce type-checking
#define vec3_t Vector

// QString class
#include "qstring.h"

// Shared engine/DLL constants
#include "const.h"
#include "edict.h"

// Shared header describing protocol between engine and DLLs
#include "eiface.h"

// Shared header between the client DLL and the game DLLs
#include "cdll_dll.h"
#include "extdef.h"

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

#ifdef _WIN32 // WINDOWS
	#pragma warning(disable : 4005)
#endif // _WIN32

// disable must return a value
#pragma warning(disable : 4716)

#ifndef _WIN32

// disable missing return statement at end of non-void function
#pragma warning(disable : 1011)

// disable offsetof applied to non-POD (Plain Old Data) types is nonstandard
#pragma warning(disable : 1875)

#endif // _WIN32

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <stddef.h>
#include <string.h>
#include <time.h>
#include <math.h>
//#include <setjmp.h>
#include <assert.h>

#ifdef _WIN32 // WINDOWS
	#include <windows.h>
	//#include <winsock.h>
	//#include <wsipx.h> // for support IPX
	#define PSAPI_VERSION 1
	#include <psapi.h>
	#include <nmmintrin.h>
	#include <fcntl.h>
	//#include <sys/types.h>
	#include <sys/stat.h>
	#include <io.h>
#else // _WIN32
	//#include <arpa/inet.h>
	#include <ctype.h>
	//#include <dirent.h>
	#include <dlfcn.h>
	#include <elf.h>
	#include <errno.h>
	#include <fcntl.h>
	#include <limits.h>
	#include <link.h>
	#include <netdb.h>
	#include <netinet/in.h>
	#include <pthread.h>
	#include <sys/ioctl.h>
	#include <sys/mman.h>
	#include <sys/stat.h>
	#include <sys/time.h>
	//#include <sys/types.h>
	//#include <sys/sysinfo.h>
	#include <unistd.h>

	// Deail with stupid macro in kernel.h
	#undef __FUNCTION__
#endif // _WIN32

#include <string>
//#include <sstream>
//#include <fstream>
#include <iomanip>

#ifdef _WIN32 // WINDOWS
#ifndef _STDINT
	typedef unsigned __int64 uint64_t;
	typedef unsigned __int32 uint32_t;
	typedef unsigned __int16 uint16_t;
	typedef unsigned __int8 uint8_t;

	typedef __int64 int64_t;
	typedef __int32 int32_t;
	typedef __int16 int16_t;
	typedef __int8 int8_t;

	typedef wchar_t uchar16;
	typedef unsigned int uchar32;
#endif
#else // _WIN32
	typedef unsigned long long uint64_t;
	typedef unsigned int uint32_t;
	typedef unsigned short uint16_t;
	typedef unsigned char uint8_t;

	#ifndef __int8_t_defined
		typedef long long int64_t;
		typedef int int32_t;
		typedef short int16_t;
		typedef char int8_t;
	#endif

	typedef unsigned char byte;
	typedef unsigned char BYTE;
	typedef unsigned short uchar16;
	typedef wchar_t uchar32;
#endif // _WIN32

#ifdef _WIN32 // WINDOWS
	#define _CRT_SECURE_NO_WARNINGS
	#define WIN32_LEAN_AND_MEAN

	#ifndef CDECL
		#define CDECL __cdecl
	#endif

	#define STDCALL __stdcall
	#define HIDDEN
	#define NOINLINE __declspec(noinline)
	#define ALIGN16 __declspec(align(16))
	#define FORCE_STACK_ALIGN

	// Attributes to specify an "exported" function, visible from outside the
	// DLL.
	#undef DLLEXPORT
	#define DLLEXPORT	__declspec(dllexport)
	// WINAPI should be provided in the windows compiler headers.
	// It's usually defined to something like "__stdcall".

#else // _WIN32
	#ifndef PAGESIZE
		#define PAGESIZE 4096
	#endif
	#define ALIGN(addr) (size_t)((size_t)addr & ~(PAGESIZE-1))
	#define ARRAYSIZE(p) (sizeof(p)/sizeof(p[0]))

	#define _MAX_FNAME NAME_MAX
	#define MAX_PATH 260

	typedef void *HWND;

	typedef unsigned long DWORD;
	typedef unsigned short WORD;
	typedef unsigned int UNINT32;

	#define CDECL __attribute__ ((cdecl))
	#define STDCALL __attribute__ ((stdcall))
	#define HIDDEN __attribute__((visibility("hidden")))
	#define NOINLINE __attribute__((noinline))
	#define ALIGN16 __attribute__((aligned(16)))
	#define FORCE_STACK_ALIGN __attribute__((force_align_arg_pointer))

	#undef DLLEXPORT
	#define DLLEXPORT	__attribute__((visibility("default")))
	#define WINAPI		/* */

	#ifndef FALSE
	#define FALSE	0
	#endif
	#ifndef TRUE
	#define TRUE	1
	#endif
#endif // _WIN32

// Simplified macro for declaring/defining exported DLL functions.  They
// need to be 'extern "C"' so that the C++ compiler enforces parameter
// type-matching, rather than considering routines with mis-matched
// arguments/types to be overloaded functions...
//
// AFAIK, this is os-independent, but it's included here in osdep.h where
// DLLEXPORT is defined, for convenience.
#define C_DLLEXPORT extern "C" DLLEXPORT

#define EXT_FUNC /*FORCE_STACK_ALIGN*/

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

#include "osconfig.h"

template <typename T, size_t N>
char(&ArraySizeHelper(T(&array)[N]))[N];

#undef ARRAYSIZE
#define ARRAYSIZE(array)             (sizeof(ArraySizeHelper(array)))

// Makes a 4-byte "packed ID" int out of 4 characters
#define MAKEID(d, c, b, a)           (((int)(a)<<24) | ((int)(b)<<16) | ((int)(c)<<8) | ((int)(d)))

// Compares a string with a 4-byte packed ID constant
#define STRING_MATCHES_ID(p, id)     ((*((int *)(p)) == (id)) ? true : false)
#define ID_TO_STRING(id, p)          ((p)[3] = (((id)>>24) & 0xFF), (p)[2] = (((id)>>16) & 0xFF), (p)[1] = (((id)>>8) & 0xFF), (p)[0] = (((id)>>0) & 0xFF))

// Keeps clutter down a bit, when using a float as a bit-vector
#define SetBits  (flBitVector, bits) ((flBitVector) = (int)(flBitVector) | (bits))
#define ClearBits(flBitVector, bits) ((flBitVector) = (int)(flBitVector) & ~(bits))
#define FBitSet  (flBitVector, bit)  ((int)(flBitVector) & (bit))

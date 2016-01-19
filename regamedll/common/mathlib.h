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

#ifndef MATHLIB_H
#define MATHLIB_H
#ifdef _WIN32
#pragma once
#endif

#ifdef PLAY_GAMEDLL

// probably gamedll compiled with flag /fpmath:fasted,
// so we need to use type double, otherwise will be the test failed

typedef double float_precision;

#else // PLAY_GAMEDLL

typedef float float_precision;

#endif // PLAY_GAMEDLL

/* <42b7f> ../common/mathlib.h:3 */
typedef float vec_t;

/* <42b91> ../common/mathlib.h:6 */
typedef vec_t vec3_t[3];

/* <80013> ../common/mathlib.h:8 */
typedef vec_t vec4_t[4];

/* <42bac> ../common/mathlib.h:18 */
typedef int fixed16_t; /* size: 4 */

/* <42bb7> ../common/mathlib.h:60 */
typedef union DLONG_u
{
	int i[2];
	double d;
	float f;
} DLONG;

#define M_PI			3.14159265358979323846

template <typename T>
T Q_min(T a, T b)		{ return (a < b) ? a : b; }

template <typename T>
T Q_max(T a, T b)		{ return (a > b) ? a : b; }

template <typename T>
T clamp(T a, T min, T max)	{ return (a > max) ? max : (a < min) ? min : a; }

// bitwise operators templates
template<class T, class type=typename std::underlying_type<T>::type>
inline T operator~ (T a)	{ return (T)~(type)a; }
template<class T, class type=typename std::underlying_type<T>::type>
inline T operator| (T a, T b)	{ return (T)((type)a | (type)b); }
template<class T, class type=typename std::underlying_type<T>::type>
inline T operator& (T a, T b)	{ return (T)((type)a & (type)b); }
template<class T, class type=typename std::underlying_type<T>::type>
inline T operator^ (T a, T b)	{ return (T)((type)a ^ (type)b); }
template<class T, class type=typename std::underlying_type<T>::type>
inline T& operator|= (T& a, T b){ return (T&)((type&)a |= (type)b); }
template<class T, class type=typename std::underlying_type<T>::type>
inline T& operator&= (T& a, T b){ return (T&)((type&)a &= (type)b); }
template<class T, class type=typename std::underlying_type<T>::type>
inline T& operator^= (T& a, T b){ return (T&)((type&)a ^= (type)b); }

#define VectorSubtract(a,b,c) {(c)[0]=(a)[0]-(b)[0];(c)[1]=(a)[1]-(b)[1];(c)[2]=(a)[2]-(b)[2];}
#define VectorAdd(a,b,c) {(c)[0]=(a)[0]+(b)[0];(c)[1]=(a)[1]+(b)[1];(c)[2]=(a)[2]+(b)[2];}
#define VectorCopy(a,b) {(b)[0]=(a)[0];(b)[1]=(a)[1];(b)[2]=(a)[2];}
#define VectorClear(a) {(a)[0]=0.0;(a)[1]=0.0;(a)[2]=0.0;}

#endif // MATHLIB_H

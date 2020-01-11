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

#ifdef PLAY_GAMEDLL
// NOTE: In some cases we need high precision of floating-point,
// so use double instead of float, otherwise unittest will fail
typedef double real_t;
#else
typedef float real_t;
#endif

typedef float vec_t;
typedef vec_t vec3_t[3];
typedef vec_t vec4_t[4];
typedef int fixed16_t;

typedef union DLONG_u
{
	int i[2];
	double d;
	float f;
} DLONG;

#define M_PI			3.14159265358979323846

#ifdef __cplusplus
#ifdef min
#undef min
#endif

#ifdef max
#undef max
#endif

#ifdef clamp
#undef clamp
#endif

template <typename T>
const T& min(const T& a, const T& b) { return (a < b) ? a : b; }

template <typename T>
const T& max(const T& a, const T& b) { return (a > b) ? a : b; }

template <typename T>
const T& clamp(const T& a, const T& min, const T& max) { return (a > max) ? max : (a < min) ? min : a; }

#else // __cplusplus

#ifndef max
#define max(a,b) (((a) > (b)) ? (a) : (b))
#endif

#ifndef min
#define min(a,b) (((a) < (b)) ? (a) : (b))
#endif

#define clamp(val, min, max) (((val) > (max)) ? (max) : (((val) < (min)) ? (min) : (val)))
#endif // __cplusplus

#ifdef HAVE_SSE
inline float M_sqrt(float value) {
	return _mm_cvtss_f32(_mm_sqrt_ss(_mm_load_ss(&value)));
}

inline double M_sqrt(double value) {
	auto v = _mm_load_sd(&value);
	return _mm_cvtsd_f64(_mm_sqrt_sd(v, v));
}
#endif

template<typename T>
inline double M_sqrt(T value) {
	return sqrt(value);
}

#ifdef HAVE_SSE
inline float M_min(float a, float b) {
	return _mm_cvtss_f32(_mm_min_ss(_mm_load_ss(&a), _mm_load_ss(&b)));
}

inline double M_min(double a, double b) {
	return _mm_cvtsd_f64(_mm_min_sd(_mm_load_sd(&a), _mm_load_sd(&b)));
}
#endif

template<typename T>
inline T M_min(T a, T b) {
	return min(a, b);
}

#ifdef HAVE_SSE
inline float M_max(float a, float b) {
	return _mm_cvtss_f32(_mm_max_ss(_mm_load_ss(&a), _mm_load_ss(&b)));
}

inline double M_max(double a, double b) {
	return _mm_cvtsd_f64(_mm_max_sd(_mm_load_sd(&a), _mm_load_sd(&b)));
}
#endif

template<typename T>
inline T M_max(T a, T b) {
	return max(a, b);
}

#ifdef HAVE_SSE
inline float M_clamp(float a, float min, float max) {
	return _mm_cvtss_f32(_mm_min_ss(_mm_max_ss(_mm_load_ss(&a), _mm_load_ss(&min)), _mm_load_ss(&max)));
}

inline double M_clamp(double a, double min, double max) {
	return _mm_cvtsd_f64(_mm_min_sd(_mm_max_sd(_mm_load_sd(&a), _mm_load_sd(&min)), _mm_load_sd(&max)));
}
#endif

template<typename T>
inline T M_clamp(T a, T min, T max) {
	return clamp(a, min, max);
}

template<class T>
inline void SWAP(T &first, T &second) {
	T temp = first;
	first = second;
	second = temp;
}

#define VectorSubtract(a,b,c) {(c)[0]=(a)[0]-(b)[0];(c)[1]=(a)[1]-(b)[1];(c)[2]=(a)[2]-(b)[2];}
#define VectorAdd(a,b,c) {(c)[0]=(a)[0]+(b)[0];(c)[1]=(a)[1]+(b)[1];(c)[2]=(a)[2]+(b)[2];}
#define VectorCopy(a,b) {(b)[0]=(a)[0];(b)[1]=(a)[1];(b)[2]=(a)[2];}
#define VectorClear(a) {(a)[0]=0.0;(a)[1]=0.0;(a)[2]=0.0;}

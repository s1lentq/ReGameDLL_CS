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

#ifndef VECTOR_H
#define VECTOR_H
#ifdef _WIN32
#pragma once
#endif

#ifdef HOOK_GAMEDLL

// probably gamedll compiled with flag /fpmath:fasted,
// so you need to use double, otherwise the demo will fail

typedef double float_precision;

#else // HOOK_GAMEDLL

typedef float float_precision;

#endif // HOOK_GAMEDLL

/* <5d3ffa> ../cstrike/dlls/vector.h:26 */
class Vector2D
{
public:
	vec_t x, y;

	inline Vector2D(void) : x(0.0), y(0.0)
	{
	}
	inline Vector2D(float X, float Y) : x(0.0), y(0.0)
	{
		x = X;
		y = Y;
	}
	inline Vector2D operator+(const Vector2D &v) const
	{
		return Vector2D(x + v.x, y + v.y);
	}
	inline Vector2D operator-(const Vector2D &v) const
	{
		return Vector2D(x - v.x, y - v.y);
	}
	inline Vector2D operator*(float fl) const
	{
		return Vector2D(x * fl, y * fl);
	}
	inline Vector2D operator/(float fl) const
	{
		return Vector2D(x / fl, y / fl);
	}
	inline Vector2D operator/=(float fl) const
	{
		return Vector2D(x / fl, y / fl);
	}
#ifdef HOOK_GAMEDLL
	inline double Length(void) const
	{
		return sqrt((double)(x * x + y * y));
	}
#else
	inline float Length(void) const
	{
		return sqrt(x * x + y * y);
	}
#endif // HOOK_GAMEDLL
	inline float LengthSquared(void) const
	{
		return (x * x + y * y);
	}
	inline Vector2D Normalize(void) const
	{
#ifdef HOOK_GAMEDLL
		double flLength = Length();
		if (!flLength)
			return Vector2D(0, 0);

		flLength = 1 / flLength;
		return Vector2D((float)(x * flLength), (float)(y * flLength));
#else
		float flLength = Length();
		if (!flLength)
			return Vector2D(0, 0);

		flLength = 1 / flLength;
		return Vector2D(x * flLength, y * flLength);
#endif // HOOK_GAMEDLL
	}
	inline bool IsLengthLessThan(float length) const
	{
		return (LengthSquared() < length * length);
	}
	inline bool IsLengthGreaterThan(float length) const
	{
		return (LengthSquared() > length * length);
	}
	inline float_precision NormalizeInPlace(void)
	{
		float_precision flLength = Length();
		if (flLength > 0.0)
		{
			x /= (vec_t)flLength;
			y /= (vec_t)flLength;
		}
		else
		{
			x = 1.0;
			y = 0.0;
		}
		return flLength;
	}
	inline bool IsZero(float tolerance = 0.01f) const
	{
		return (x > -tolerance && x < tolerance &&
			y > -tolerance && y < tolerance);
	}
};/* size: 8, cachelines: 1, members: 2 */

inline float DotProduct(const Vector2D &a, const Vector2D &b)
{
	return (a.x * b.x + a.y * b.y);
}
inline Vector2D operator*(float fl, const Vector2D &v)
{
	return v * fl;
}

/* <5e2e91> ../cstrike/dlls/vector.h:104 */
class Vector
{
public:
	vec_t x, y, z;
	inline Vector(void) : x(0.0), y(0.0), z(0.0)
	{
	}
	inline Vector(float X, float Y, float Z) : x(0.0), y(0.0), z(0.0)
	{
		x = X;
		y = Y;
		z = Z;
	}
	inline Vector(const Vector &v) : x(0.0), y(0.0), z(0.0)
	{
		x = v.x;
		y = v.y;
		z = v.z;
	}
	inline Vector(const float rgfl[3]) : x(0.0), y(0.0), z(0.0)
	{
		x = rgfl[0];
		y = rgfl[1];
		z = rgfl[2];
	}
	inline Vector operator-(void) const
	{
		return Vector(-x, -y, -z);
	}
	inline int operator==(const Vector &v) const
	{
		return x == v.x && y == v.y && z == v.z;
	}
	inline int operator!=(const Vector &v) const
	{
		return !(*this == v);
	}
	inline Vector operator+(const Vector &v) const
	{
		return Vector(x + v.x, y + v.y, z + v.z);
	}
	inline Vector operator-(const Vector &v) const
	{
		return Vector(x - v.x, y - v.y, z - v.z);
	}
	inline Vector operator*(float fl) const
	{
		return Vector(x * fl, y * fl, z * fl);
	}
	inline Vector operator/(float fl) const
	{
		return Vector(x / fl, y / fl, z / fl);
	}
	inline Vector operator/=(float fl) const
	{
		return Vector(x / fl, y / fl, z / fl);
	}
	inline void CopyToArray(float *rgfl) const
	{
		rgfl[0] = x;
		rgfl[1] = y;
		rgfl[2] = z;
	}
#ifdef HOOK_GAMEDLL
	inline double Length(void) const
	{
		return sqrt((double)(x * x + y * y + z * z));
	}
#else
	inline float Length(void) const
	{
		return sqrt(x * x + y * y + z * z);
	}
#endif // HOOK_GAMEDLL
	inline float LengthSquared(void) const
	{
		return (x * x + y * y + z * z);
	}
	operator float*()
	{
		return &x;
	}
	operator const float*() const
	{
		return &x;
	}
	inline Vector Normalize(void) const
	{
#ifdef HOOK_GAMEDLL
		double flLength = Length();
#else
		float flLength = Length();
#endif // HOOK_GAMEDLL

		if (!flLength)
			return Vector(0, 0, 1);

		flLength = 1 / flLength;
		return Vector((float)(x * flLength), (float)(y * flLength), (float)(z * flLength));
	}
	inline Vector2D Make2D(void) const
	{
		Vector2D Vec2;
		Vec2.x = x;
		Vec2.y = y;
		return Vec2;
	}
#ifdef HOOK_GAMEDLL
	inline double Length2D(void) const
	{
		return sqrt((double)(x * x + y * y));
	}
#else
	inline double Length2D(void) const
	{
		return sqrt(x * x + y * y);
	}
#endif // HOOK_GAMEDLL
	inline bool IsLengthLessThan(float length) const
	{
		return (LengthSquared() < length * length);
	}
	inline bool IsLengthGreaterThan(float length) const
	{
		UNTESTED
		return (LengthSquared() > length * length);
	}
	inline float_precision NormalizeInPlace(void)
	{
		float_precision flLength = Length();
		if (flLength > 0.0)
		{
			x /= (vec_t)flLength;
			y /= (vec_t)flLength;
			z /= (vec_t)flLength;
		}
		else
		{
			x = 0.0;
			y = 0.0;
			z = 1.0;
		}
		return flLength;
	}
	inline bool IsZero(float tolerance = 0.01f) const
	{
		return (x > -tolerance && x < tolerance &&
			y > -tolerance && y < tolerance &&
			z > -tolerance && z < tolerance);
	}
};/* size: 12, cachelines: 1, members: 3 */

/* <1c0d1> ../cstrike/dlls/vector.h:184 */
inline Vector operator*(float fl, const Vector &v)
{
	return v * fl;
}

/* <5d9a4> ../cstrike/dlls/vector.h:185 */
inline float DotProduct(const Vector &a, const Vector &b)
{
	return (a.x * b.x + a.y * b.y + a.z * b.z);
}

/* <1ba548> ../cstrike/dlls/vector.h:186 */
inline Vector CrossProduct(const Vector &a, const Vector &b)
{
	return Vector(a.y * b.z - a.z * b.y, a.z * b.x - a.x * b.z, a.x * b.y - a.y * b.x);
}

template<class T>
inline void SWAP(T &first, T &second)
{
	T temp = first;
	first = second;
	second = temp;
}

#endif // VECTOR_H

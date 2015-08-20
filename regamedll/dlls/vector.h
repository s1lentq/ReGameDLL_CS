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
#ifdef HOOK_GAMEDLL
	inline Vector2D operator*(float_precision fl) const
	{
		return Vector2D((vec_t)(x * fl), (vec_t)(y * fl));
	}
	inline Vector2D operator/(float_precision fl) const
	{
		return Vector2D((vec_t)(x / fl), (vec_t)(y / fl));
	}
	inline Vector2D operator/=(float_precision fl) const
	{
		return Vector2D((vec_t)(x / fl), (vec_t)(y / fl));
	}
#else
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
#endif // HOOK_GAMEDLL
	inline double Length(void) const
	{
		return sqrt((float_precision)(x * x + y * y));
	}
	inline float LengthSquared(void) const
	{
		return (x * x + y * y);
	}
	inline Vector2D Normalize(void) const
	{
		float_precision flLen = Length();
		if (!flLen)
			return Vector2D(0, 0);

		flLen = 1 / flLen;
	
#ifdef HOOK_GAMEDLL
		return Vector2D((vec_t)(x * flLen), (vec_t)(y * flLen));
#else
		return Vector2D(x * flLen, y * flLen);
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
		float_precision flLen = Length();
		if (flLen > 0.0)
		{
			x /= (vec_t)flLen;
			y /= (vec_t)flLen;
		}
		else
		{
			x = 1.0;
			y = 0.0;
		}
		return flLen;
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
#ifdef HOOK_GAMEDLL
	inline Vector operator*(float_precision fl) const
	{
		return Vector((vec_t)(x * fl), (vec_t)(y * fl), (vec_t)(z * fl));
	}
	inline Vector operator/(float_precision fl) const
	{
		return Vector((vec_t)(x / fl), (vec_t)(y / fl), (vec_t)(z / fl));
	}
	inline Vector operator/=(float_precision fl) const
	{
		return Vector((vec_t)(x / fl), (vec_t)(y / fl), (vec_t)(z / fl));
	}
#else
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
#endif // HOOK_GAMEDLL

	inline void CopyToArray(float *rgfl) const
	{
		rgfl[0] = x;
		rgfl[1] = y;
		rgfl[2] = z;
	}
	inline float_precision Length(void) const
	{
		float_precision x1 = (float_precision)x;
		float_precision y1 = (float_precision)y;
		float_precision z1 = (float_precision)z;


		return sqrt(x1 * x1 + y1 * y1 + z1 * z1);

		//return sqrt((float_precision)(x * x + y * y + z * z));
	}
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
#ifndef HOOK_GAMEDLL
	inline Vector Normalize(void)
	{
		float flLen = Length();
		if (flLen == 0)
			return Vector(0, 0, 1);

		flLen = 1 / flLen;
		return Vector(x * flLen, y * flLen, z * flLen);
	}
#else
	inline Vector Normalize(void)
	{
		float_precision flLen = Length();
		if (flLen == 0)
			return Vector(0, 0, 1);

		vec_t fTemp = (vec_t)(1 / flLen);
		return Vector(x * fTemp, y * fTemp, z * fTemp);
	}
	// for out precision normalize
	inline Vector NormalizePrecision(void)
	{
#ifndef HOOK_GAMEDLL
		return Normalize();
#else
		float_precision flLen = Length();
		if (flLen == 0)
			return Vector(0, 0, 1);

		flLen = 1 / flLen;
		return Vector((vec_t)(x * flLen), (vec_t)(y * flLen), (vec_t)(z * flLen));
#endif // HOOK_GAMEDLL
	}
#endif // HOOK_GAMEDLL
	inline Vector2D Make2D(void) const
	{
		Vector2D Vec2;
		Vec2.x = x;
		Vec2.y = y;
		return Vec2;
	}
	inline double Length2D(void) const
	{
		return sqrt((float_precision)(x * x + y * y));
	}
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
		float_precision flLen = Length();
		if (flLen > 0.0)
		{
			x /= (vec_t)flLen;
			y /= (vec_t)flLen;
			z /= (vec_t)flLen;
		}
		else
		{
			x = 0.0;
			y = 0.0;
			z = 1.0;
		}
		return flLen;
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
inline float_precision DotProduct(const Vector &a, const Vector &b)
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

template<
	typename X,
	typename Y,
	typename Z,
	typename LenType
>
inline LenType LenghtSubtract(Vector vecStart, Vector vecDest)
{
	X floatX = (vecDest.x - vecStart.x);
	Y floatY = (vecDest.y - vecStart.y);
	Z floatZ = (vecDest.z - vecStart.z);

	return sqrt((float_precision)(floatX * floatX + floatY * floatY + floatZ * floatZ));
}

template<
	typename X,
	typename Y,
	typename Z,
	typename LenType
>
inline Vector NormalizeSubtract(Vector vecStart, Vector vecDest)
{
	Vector dir;

#ifdef HOOK_GAMEDLL

	X floatX = (vecDest.x - vecStart.x);
	Y floatY = (vecDest.y - vecStart.y);
	Z floatZ = (vecDest.z - vecStart.z);

	LenType flLen = sqrt((float_precision)(floatX * floatX + floatY * floatY + floatZ * floatZ));

	if (flLen == 0.0)
	{
		dir = Vector(0, 0, 1);
	}
	else
	{
		flLen = 1.0 / flLen;

		dir.x = (vec_t)(floatX * flLen);
		dir.y = (vec_t)(floatY * flLen);
		dir.z = (vec_t)(floatZ * flLen);
	}
#else
	dir = (vecDest - vecStart).Normalize();
#endif // HOOK_GAMEDLL

	return dir;
}

#endif // VECTOR_H

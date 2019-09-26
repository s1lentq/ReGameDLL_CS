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

// Used for many pathfinding and many other operations that are treated as planar rather than 3D.
class Vector2D
{
public:
	// Construction/destruction
	Vector2D() : x(), y() {}
	Vector2D(float X, float Y) : x(X), y(Y) {}
	Vector2D(const Vector2D &v) { *(int *)&x = *(int *)&v.x; *(int *)&y = *(int *)&v.y; }

	// Operators
	decltype(auto) operator-()         const { return Vector2D(-x, -y); }
	bool operator==(const Vector2D &v) const { return x == v.x && y == v.y; }
	bool operator!=(const Vector2D &v) const { return !(*this == v); }

	decltype(auto) operator+(const Vector2D &v)  const { return Vector2D(x + v.x, y + v.y); }
	decltype(auto) operator-(const Vector2D &v)  const { return Vector2D(x - v.x, y - v.y); }
	decltype(auto) operator*(const Vector2D &v)  const { return Vector2D(x * v.x, y * v.y); }
	decltype(auto) operator/(const Vector2D &v)  const { return Vector2D(x / v.x, y / v.y); }

	decltype(auto) operator+=(const Vector2D &v) { return (*this = *this + v); }
	decltype(auto) operator-=(const Vector2D &v) { return (*this = *this - v); }
	decltype(auto) operator*=(const Vector2D &v) { return (*this = *this * v); }
	decltype(auto) operator/=(const Vector2D &v) { return (*this = *this / v); }

	decltype(auto) operator+(float fl) const { return Vector2D(x + fl, y + fl); }
	decltype(auto) operator-(float fl) const { return Vector2D(x - fl, y - fl); }

	// TODO: FIX ME!!
#ifdef PLAY_GAMEDLL
	decltype(auto) operator*(float fl) const { return Vector2D(vec_t(x * fl), vec_t(y * fl)); }
	decltype(auto) operator/(float fl) const { return Vector2D(vec_t(x / fl), vec_t(y / fl)); }
#else
	decltype(auto) operator*(float fl) const { return Vector2D(x * fl, y * fl); }
	decltype(auto) operator/(float fl) const { return Vector2D(x / fl, y / fl); }
#endif

	decltype(auto) operator=(std::nullptr_t) { return Vector2D(0, 0); }
	decltype(auto) operator+=(float fl) { return (*this = *this + fl); }
	decltype(auto) operator-=(float fl) { return (*this = *this - fl); }
	decltype(auto) operator*=(float fl) { return (*this = *this * fl); }
	decltype(auto) operator/=(float fl) { return (*this = *this / fl); }

	// Methods
	inline void Clear() { x = 0; y = 0; }
	inline void CopyToArray(float *rgfl) const { *(int *)&rgfl[0] = *(int *)&x; *(int *)&rgfl[1] = *(int *)&y; }
	inline real_t Length() const { return Q_sqrt(real_t(x * x + y * y)); }		// Get the vector's magnitude
	inline float LengthSquared() const { return (x * x + y * y); }				// Get the vector's magnitude squared

	operator float*()             { return &x; } // Vectors will now automatically convert to float * when needed
	operator const float*() const { return &x; } // Vectors will now automatically convert to float * when needed

	Vector2D Normalize() const
	{
		real_t flLen = Length();
		if (!flLen)
			return Vector2D(0, 0);

		flLen = 1 / flLen;

#ifdef PLAY_GAMEDLL
		return Vector2D(vec_t(x * flLen), vec_t(y * flLen));
#else
		return Vector2D(x * flLen, y * flLen);
#endif // PLAY_GAMEDLL
	}
	inline bool IsLengthLessThan   (float length) const { return (LengthSquared() < length * length); }
	inline bool IsLengthGreaterThan(float length) const { return (LengthSquared() > length * length); }
	real_t NormalizeInPlace()
	{
		real_t flLen = Length();
		if (flLen > 0.0)
		{
			x = vec_t(1 / flLen * x);
			y = vec_t(1 / flLen * y);
		}
		else
		{
			x = 1.0;
			y = 0.0;
		}
		return flLen;
	}
	bool IsZero(float tolerance = 0.01f) const
	{
		return (x > -tolerance && x < tolerance &&
			y > -tolerance && y < tolerance);
	}

	// Members
	vec_t x, y;
};

inline real_t DotProduct(const Vector2D &a, const Vector2D &b)
{
	return (a.x * b.x + a.y * b.y);
}

inline Vector2D operator*(float fl, const Vector2D &v)
{
	return v * fl;
}

// 3D Vector
// Same data-layout as engine's vec3_t, which is a vec_t[3]
class Vector
{
public:
	// Construction/destruction
	Vector() : x(), y(), z() {}
	Vector(float X, float Y, float Z) : x(X), y(Y), z(Z) {}
	Vector(const Vector &v) { *(int *)&x = *(int *)&v.x; *(int *)&y = *(int *)&v.y; *(int *)&z = *(int *)&v.z; }
	Vector(const float rgfl[3]) { *(int *)&x = *(int *)&rgfl[0]; *(int *)&y = *(int *)&rgfl[1]; *(int *)&z = *(int *)&rgfl[2]; }

	// Operators
	decltype(auto) operator-()       const { return Vector(-x, -y, -z); }
	bool operator==(const Vector &v) const { return x == v.x && y == v.y && z == v.z; }
	bool operator!=(const Vector &v) const { return !(*this == v); }

	decltype(auto) operator+(const Vector &v) const { return Vector(x + v.x, y + v.y, z + v.z); }
	decltype(auto) operator-(const Vector &v) const { return Vector(x - v.x, y - v.y, z - v.z); }
	decltype(auto) operator*(const Vector &v) const { return Vector(x * v.x, y * v.y, z * v.z); }
	decltype(auto) operator/(const Vector &v) const { return Vector(x / v.x, y / v.y, z / v.z); }

	decltype(auto) operator+=(const Vector &v) { return (*this = *this + v); }
	decltype(auto) operator-=(const Vector &v) { return (*this = *this - v); }
	decltype(auto) operator*=(const Vector &v) { return (*this = *this * v); }
	decltype(auto) operator/=(const Vector &v) { return (*this = *this / v); }

	decltype(auto) operator+(float fl) const { return Vector(x + fl, y + fl, z + fl); }
	decltype(auto) operator-(float fl) const { return Vector(x - fl, y - fl, z - fl); }

	// TODO: FIX ME!!
#ifdef PLAY_GAMEDLL
	decltype(auto) operator*(float fl) const { return Vector(vec_t(x * fl), vec_t(y * fl), vec_t(z * fl)); }
	decltype(auto) operator/(float fl) const { return Vector(vec_t(x / fl), vec_t(y / fl), vec_t(z / fl)); }
#else
	decltype(auto) operator*(float fl) const { return Vector(x * fl, y * fl, z * fl); }
	decltype(auto) operator/(float fl) const { return Vector(x / fl, y / fl, z / fl); }
#endif

	decltype(auto) operator=(std::nullptr_t) { return Vector(0, 0, 0); }
	decltype(auto) operator+=(float fl) { return (*this = *this + fl); }
	decltype(auto) operator-=(float fl) { return (*this = *this - fl); }
	decltype(auto) operator*=(float fl) { return (*this = *this * fl); }
	decltype(auto) operator/=(float fl) { return (*this = *this / fl); }

	// Methods
	void Clear()
	{
		x = 0;
		y = 0;
		z = 0;
	}

	void CopyToArray(float *rgfl) const
	{
		*(int *)&rgfl[0] = *(int *)&x;
		*(int *)&rgfl[1] = *(int *)&y;
		*(int *)&rgfl[2] = *(int *)&z;
	}

	// Get the vector's magnitude
	real_t Length() const
	{
		real_t x1 = real_t(x);
		real_t y1 = real_t(y);
		real_t z1 = real_t(z);

		return Q_sqrt(x1 * x1 + y1 * y1 + z1 * z1);
	}

	// Get the vector's magnitude squared
	real_t LengthSquared() const { return (x * x + y * y + z * z); }

	operator float*()             { return &x; } // Vectors will now automatically convert to float * when needed
	operator const float*() const { return &x; } // Vectors will now automatically convert to float * when needed

#ifndef PLAY_GAMEDLL
	Vector Normalize() const
	{
		float flLen = Length();
		if (flLen == 0)
			return Vector(0, 0, 1);

		flLen = 1 / flLen;
		return Vector(x * flLen, y * flLen, z * flLen);
	}
#else
	Vector Normalize()
	{
		real_t flLen = Length();
		if (flLen == 0)
			return Vector(0, 0, 1);

		vec_t fTemp = vec_t(1 / flLen);
		return Vector(x * fTemp, y * fTemp, z * fTemp);
	}
#endif // PLAY_GAMEDLL
	// for out precision normalize
	Vector NormalizePrecision() const
	{
#ifndef PLAY_GAMEDLL
		return Normalize();
#else
		real_t flLen = Length();
		if (flLen == 0)
			return Vector(0, 0, 1);

		flLen = 1 / flLen;
		return Vector(vec_t(x * flLen), vec_t(y * flLen), vec_t(z * flLen));
#endif // PLAY_GAMEDLL
	}
	Vector2D Make2D() const
	{
		Vector2D Vec2;
		*(int *)&Vec2.x = *(int *)&x;
		*(int *)&Vec2.y = *(int *)&y;
		return Vec2;
	}

	real_t Length2D() const { return Q_sqrt(real_t(x * x + y * y)); }

	inline bool IsLengthLessThan   (float length) const { return (LengthSquared() < length * length); }
	inline bool IsLengthGreaterThan(float length) const { return (LengthSquared() > length * length); }

#ifdef PLAY_GAMEDLL
	template<typename T = real_t>
	real_t NormalizeInPlace()
	{
		T flLen = Length();

		if (flLen > 0)
		{
			x = vec_t(1 / flLen * x);
			y = vec_t(1 / flLen * y);
			z = vec_t(1 / flLen * z);
		}
		else
		{
			x = 0;
			y = 0;
			z = 1;
		}

		return flLen;
	}
#else // PLAY_GAMEDLL
	float NormalizeInPlace()
	{
		float flLen = Length();
		if (flLen > 0)
		{
			x /= flLen;
			y /= flLen;
			z /= flLen;
		}
		else
		{
			x = 0;
			y = 0;
			z = 1;
		}
		return flLen;
	}
#endif // PLAY_GAMEDLL
	bool IsZero(float tolerance = 0.01f) const
	{
		return (x > -tolerance && x < tolerance &&
			y > -tolerance && y < tolerance &&
			z > -tolerance && z < tolerance);
	}

	// Members
	vec_t x, y, z;
};

inline Vector operator*(float fl, const Vector &v)
{
	return v * fl;
}

inline real_t DotProduct(const Vector &a, const Vector &b)
{
	return (a.x * b.x + a.y * b.y + a.z * b.z);
}

inline real_t DotProduct2D(const Vector &a, const Vector &b)
{
	return (a.x * b.x + a.y * b.y);
}

inline Vector CrossProduct(const Vector &a, const Vector &b)
{
	return Vector(a.y * b.z - a.z * b.y, a.z * b.x - a.x * b.z, a.x * b.y - a.y * b.x);
}

template<
	typename X,
	typename Y,
	typename Z,
	typename LenType
>
inline LenType LengthSubtract(Vector vecStart, Vector vecDest)
{
	X floatX = (vecDest.x - vecStart.x);
	Y floatY = (vecDest.y - vecStart.y);
	Z floatZ = (vecDest.z - vecStart.z);

	return Q_sqrt(real_t(floatX * floatX + floatY * floatY + floatZ * floatZ));
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

#ifdef PLAY_GAMEDLL

	X floatX = (vecDest.x - vecStart.x);
	Y floatY = (vecDest.y - vecStart.y);
	Z floatZ = (vecDest.z - vecStart.z);

	LenType flLen = Q_sqrt(real_t(floatX * floatX + floatY * floatY + floatZ * floatZ));

	if (flLen == 0.0)
	{
		dir = Vector(0, 0, 1);
	}
	else
	{
		flLen = 1.0 / flLen;

		dir.x = vec_t(floatX * flLen);
		dir.y = vec_t(floatY * flLen);
		dir.z = vec_t(floatZ * flLen);
	}
#else
	dir = (vecDest - vecStart).Normalize();
#endif // PLAY_GAMEDLL

	return dir;
}

#ifdef PLAY_GAMEDLL
template<typename X, typename Y, typename LenType>
inline Vector NormalizeMulScalar(Vector2D vec, float scalar)
{
	LenType flLen;
	X floatX;
	Y floatY;

	flLen = (LenType)vec.Length();

	if (flLen <= 0.0)
	{
		floatX = 1;
		floatY = 0;
	}
	else
	{
		flLen = 1 / flLen;

		floatX = vec.x * flLen;
		floatY = vec.y * flLen;
	}

	return Vector(vec_t(floatX * scalar), vec_t(floatY * scalar), 0);
}
template<typename X, typename Y, typename LenType, typename LenCast>
inline Vector NormalizeMulScalar(Vector vec, float scalar)
{
	LenType flLen;
	X floatX = vec.x;
	Y floatY = vec.y;

	flLen = (LenType)vec.Length();

	if (flLen <= 0.0)
	{
		floatX = 1;
		floatY = 0;
	}
	else
	{
		floatX = floatX * LenCast(1 / flLen);
		floatY = floatY * LenCast(1 / flLen);
	}

	return Vector(vec_t(floatX * scalar), vec_t(floatY * scalar), 0);
}
#endif // PLAY_GAMEDLL

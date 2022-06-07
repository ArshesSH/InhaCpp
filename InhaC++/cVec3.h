#pragma once

#include "MathSH.h"
#include <iostream>

template<typename T>
class cVec3
{
public:
	cVec3() {}
	cVec3(T x, T y, T z = (T)0)
		:
		x(x),
		y(y),
		z(z)
	{
	}
	
	T GetX() const
	{
		return x;
	}
	T GetY() const
	{
		return y;
	}
	T GetZ() const
	{
		return z;
	}
	bool operator==( const cVec3& rhs )
	{
		return MathSH::Compare( x, rhs.x ) && MathSH::Compare( y, rhs.y ) && MathSH::Compare( z, rhs.z );
	}
	bool operator!=( const cVec3& rhs )
	{
		return (x != rhs.x) || (y != rhs.y) || (z != rhs.z);
	}
	cVec3 operator+( const cVec3& rhs ) const
	{
		return cVec3( x + rhs.x, y + rhs.y, z + rhs.z );
	}
	cVec3& operator+=( const cVec3& rhs )
	{
		return *this = *this + rhs;
	}
	cVec3 operator-( const cVec3& rhs ) const
	{
		return cVec3( x - rhs.x, y - rhs.y, z - rhs.z );
	}
	cVec3& operator-=( const cVec3& rhs )
	{
		return *this = *this - rhs;
	}
	cVec3 operator*(T rhs) const
	{
		return cVec3( x * rhs, y * rhs, z * rhs );
	}
	cVec3 operator/ (T rhs) const
	{
		return cVec3( x / rhs, y / rhs, z / rhs );
	}

	T LengthSq() const
	{
		return x * x + y * y + z * z;
	}
	T Length() const
	{
		return sqrt( LengthSq() );
	}
	cVec3& Normalize()
	{
		const T length = Length();
		x /= length;
		y /= length;
		z /= length;
		return *this;
	}
	cVec3 GetNormalized() const
	{
		cVec3 vecNormal = *this;
		vecNormal.Normalize();
		return vecNormal;
	}
	static T Dot( const cVec3& lhs, const cVec3& rhs ) 
	{
		return lhs.x * rhs.x + lhs.y * rhs.y + lhs.z * rhs.z;
	}
	static cVec3 Cross( const cVec3& lhs, const cVec3& rhs ) 
	{
		return
		{
			cVec3(
				lhs.y * rhs.z - lhs.z * rhs.y,
				lhs.z * rhs.x - lhs.x * rhs.z,
				lhs.x * rhs.y - lhs.y * rhs.x
			)
		};
	}
	static T Radian( const cVec3& lhs, const cVec3& rhs ) 
	{
		return (T)acos( Dot( lhs, rhs ) / sqrt( lhs.LengthSq() * rhs.LengthSq() ) );
	}
	static T Angle( const cVec3& lhs, const cVec3& rhs ) 
	{
		return Radian( lhs, rhs )* (180 / MathSH::pi);
	}

	friend cVec3 operator*( T n, const cVec3& rhs )
	{
		return rhs * n;
	}
	friend std::ostream& operator<<( std::ostream& os, const cVec3& v )
	{
		std::cout << "(" << v.GetX() << ", " << v.GetY() << ", " << v.GetZ() << ")";
		return os;
	}

private:
	T x;
	T y;
	T z;
};
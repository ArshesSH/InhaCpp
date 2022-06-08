#pragma once

#include <cmath>

template<typename T>
class Rect2D;
template<typename T>
class Circle2D;

template<typename T>
class MyPoint
{
public:
	MyPoint()
		:
		x(T(0)),
		y(T(0))
	{}
	MyPoint(T x, T y)
		:
		x(x),
		y(y)
	{}

	MyPoint<T> operator+( const MyPoint<T>& rhs ) const
	{
		return { x + rhs.x , y + rhs.y };
	}
	MyPoint<T>& operator+=( const MyPoint<T>& rhs ) const
	{
		return *this = *this + rhs;
	}
	MyPoint<T> operator-( const MyPoint<T>& rhs ) const
	{
		return { x - rhs.x , y - rhs.y };
	}
	MyPoint<T>& operator-=( const MyPoint<T>& rhs ) const
	{
		return *this = *this - rhs;
	}
	T GetLength() const
	{
		return std::sqrt( GetLengthSq() );
	}
	T GetLengthSq() const
	{
		return x * x + y * y;
	}
	double GetDistanceWith( const MyPoint<T>& other ) const
	{
		const MyPoint<T> vDist = other - *this;
		return vDist.GetLength();
	}
	T GetX() const
	{
		return x;
	}
	T GetY() const
	{
		return y;
	}
	friend bool IsContains( const Rect2D<T>& rect, const MyPoint<T>& p )
	{
		return rect.IsContains(p.GetX(), p.GetY() );
	}
	friend bool IsContains( const Circle2D<T>& c, const MyPoint<T>& p )
	{
		return c.IsContains( p.GetX(), p.GetY() );
	}
private:
	T x;
	T y;
};
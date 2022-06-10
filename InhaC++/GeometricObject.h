#pragma once

#include "Vec2.h"

template<typename T>
class GeometricObject
{
public:
	GeometricObject()
		:
		x((T)0),
		y((T)0)
	{}
	GeometricObject( T x, T y )
		:
		x(x),
		y(y)
	{}
	virtual ~GeometricObject() = default;

	Vec2<T> GetPos() const
	{
		return pos;
	}
	T GetX() const
	{
		return x;
	}
	T GetY() const
	{
		return y;
	}

protected:
	T x;
	T y;
};

template<typename T>
class Point : public GeometricObject<T>
{
public:
	Point() {};
	Point(T x, T y)
		:
		GeometricObject(x, y)
	{}
	~Point() {} = default;

	Point<T> operator+( const Point<T>& rhs ) const
	{
		return { x + rhs.x , y + rhs.y };
	}
	Point<T>& operator+=( const Point<T>& rhs ) const
	{
		return *this = *this + rhs;
	}
	Point<T> operator-( const Point<T>& rhs ) const
	{
		return { x - rhs.x , y - rhs.y };
	}
	Point<T>& operator-=( const Point<T>& rhs ) const
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
	double GetDistanceWith( const Point<T>& other ) const
	{
		const Point<T> vDist = other - *this;
		return vDist.GetLength();
	}

	friend bool IsContains( const Rect2D<T>& rect, const Point<T>& p )
	{
		return rect.IsContains( p.GetX(), p.GetY() );
	}
	friend bool IsContains( const Circle2D<T>& c, const Point<T>& p )
	{
		return c.IsContains( p.GetX(), p.GetY() );
	}
private:
};

template<typename T>
class PlaneFigure : public GeometricObject<T>
{
public:
	PlaneFigure()
		:
		center((T)0, (T)0)
	{}
	PlaneFigure( T x, T y )
		:
		center( x, y )
	{}
	bool IsOverlapWith(const PlaneFigure<T>&)
	virtual ~PlaneFigure() = default;

private:
	Vec2<T> center;
};
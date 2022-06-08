#pragma once

#include "Vec2.h"

template<typename T>
class Rect2D
{
public:
	Rect2D()
		:
		center( { (T)0, (T)0 } ),
		width( (T)1 ),
		height( (T)1 )
	{
		SetVertices();
	}
	Rect2D(const Vec2<T>& center, T width, T height)
		:
		center(center),
		width(width),
		height( height )
	{
		SetVertices();
	}
	Rect2D( T x, T y, T width, T height )
		:
		center( x, y ),
		width( width ),
		height( height )
	{
		SetVertices();
	}
	
	bool IsOverlapWith( const Rect2D<T>& other ) const
	{
		return right > other.left && left < other.right && top > other.bottom && bottom < other.top;
	}
	template<typename T2>
	bool IsContainedBy( const Rect2D<T2>& other ) const
	{
		return other.top >= top && other.bottom <= bottom && other.left <= left && other.right >= right;
	}
	template<typename T2>
	bool IsContains( const Rect2D<T2>& other ) const
	{
		return (other.top <= top && other.bottom >= bottom && other.left >= left && other.right <= right);
	}
	template<typename T2>
	bool IsContains( const Vec2<T2>& point ) const
	{
		return point.y <= top && point.y >= bottom && point.x >= left && point.x <= right;
	}
	template<typename T2>
	bool IsContains( T2 x, T2 y ) const
	{
		return IsContains( Vec2<T2>{ x,y } );
	}
	T GetArea() const
	{
		return width * height;
	}
	T GetPerimeter() const
	{
		return width * 2 + height * 2;
	}
	Vec2<T> GetCenter() const
	{
		return center;
	}
	T GetWidth() const
	{
		return width;
	}
	T GetHeight() const
	{
		return height;
	}
	void SetWidth(T width_in)
	{
		width = width_in;
		SetVertices();
	}
	void SetHeight( T height_in )
	{
		height = height_in;
		SetVertices();
	}
	void SetCenter( const Vec2<T>& center_in )
	{
		center = center_in;
		SetVertices();
	}
	void SetCenter( T x, T y )
	{
		SetCenter( { x, y } );
		SetVertices();
	}

private:
	void SetVertices()
	{
		const T halfWidth = T( width / 2.0 );
		const T halfHeight = T( height / 2.0 );
		left = center.x - halfWidth;
		right = center.x + halfWidth;
		top = center.y + halfHeight;
		bottom = center.y - halfHeight;
	}

private:
	Vec2<T> center;
	T width;
	T height;

	T left;
	T right;
	T top;
	T bottom;
};
#pragma once

#include "Vec2.h"

template<typename T>
class Rect
{
public:
	Rect()
		:
		left(T(0)),
		right(T(0)),
		top(T(0)),
		bottom(T(0))
	{}
	Rect(T left, T right, T top, T bottom)
		:
		left(left),
		right(right),
		top(top),
		bottom(bottom)
	{}
	Rect(const Vec2<T>& leftTop, const Vec2<T>& rightBottom)
		:
		left(leftTop.x),
		right(rightBottom.x ),
		top(leftTop.y),
		bottom(rightBottom.y)
	{}
	Rect(const Vec2<T>& leftTop, T width, T height)
	{
		Rect( leftTop, leftTop + Vec2<T>{width, height} );
	}
	
	bool IsOverlapWith( const Rect<T>& other ) const
	{
		return right > other.left && left < other.right && bottom > other.bottom && top < other.bottom;
	}
	
	template<typename T2>
	bool IsContainedBy( const Rect<T2>& other ) const
	{
		return other.top >= top && other.bottom <= bottom && other.left >= left && other.right <= right;
	}
	template<typename T2>
	bool IsContains( const Vec2<T2> point ) const
	{
		return  point.y >= top && point.y <= bottom && point.x >= left && point.x <= right;
	}
	Vec2<T> GetCenter()
	{
		const Vec2<T> half( GetWidth() / (T)2, GetHeight() / (T)2 );
		const Vec2<T> leftTop( left, top );
		return leftTop + half;
	}
	static Rect<T> GetRectByCenter( const Vec2<T>& center, T width, T height )
	{
		const Vec2<T> half( width / (T)2, height / (T)2 );
		const Vec2<T> leftTop( center - half );
		const Vec2<T> rightBottom( center + half );
		return Rect<T>( leftTop, rightBottom );
	}
	T GetWidth() const
	{
		return right - left;
	}
	T GetHeight() const
	{
		return bottom - top;
	}
private:
	T left;
	T right;
	T top;
	T bottom;
};
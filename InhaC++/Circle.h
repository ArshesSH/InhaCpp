#pragma once

#include "Vec2.h"

template<typename T>
class Circle
{
public:
	Circle()
		:
		center( 0, 0 ),
		radius( 0 )
	{}
	Circle(const Vec2<T>& center, T radius)
		:
		center(center),
		radius(radius)
	{}
	

	bool IsOverlapWidth( const Circle<T> other ) const
	{
		const Vec2<T> distanceSq = center - other.center;
		const T sumOfRadius = radius + other.radius;
		return distanceSq.GetLengthSq() < sumOfRadius * sumOfRadius;
	}
	bool IsContainedBy( const Circle<T> other ) const
	{
		const Vec2<T> distanceSq = center - other.center;
		const T difference = other.radius - radius;
		return distanceSq.GetLengthSq() < difference * difference;
	}

	Vec2<T> GetCenter() const
	{
		return center;
	}
	T GetRadius() const
	{
		return radius;
	}

private:
	Vec2<T> center;
	T radius;
};
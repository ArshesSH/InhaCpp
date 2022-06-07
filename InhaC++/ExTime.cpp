#include "ExTime.h"

#include <iostream>

ExTime::ExTime()
	:
	hours(0),
	minutes(0)
{
}

ExTime::ExTime( int h, int m )
	:
	hours(h),
	minutes(m)
{
}

void ExTime::AddMin( int m )
{
	minutes += m;
	hours += minutes / 60;
	minutes %= 60;
}

void ExTime::AddHr( int h )
{
	hours += h;
}

void ExTime::Reset( int h, int m )
{
	hours = h;
	minutes = m;
}

ExTime ExTime::Sum( const ExTime& t ) const
{
	ExTime sum;
	sum.minutes = minutes + t.minutes;
	sum.hours = hours + t.hours + sum.minutes / 60;
	sum.minutes %= 60;
	return sum;
}

void ExTime::Show() const
{
	std::cout << hours << "½Ã°£, " << minutes << "ºÐ";
}


ExTime ExTime::operator+( const ExTime& t ) const
{
	ExTime sum;
	sum.minutes = minutes + t.minutes;
	sum.hours = hours + t.hours + sum.minutes / 60;
	sum.minutes %= 60;
	return sum;
}

ExTime& ExTime::operator+=( const ExTime& t )
{
	return *this = *this + t;
}

#pragma once

class ExTime
{
public:
	ExTime();
	ExTime( int h, int m = 0 );
	void AddMin( int m );
	void AddHr( int h );
	void Reset( int h = 0, int m = 0 );
	ExTime Sum( const ExTime& t ) const;
	void Show() const;

	ExTime operator+( const ExTime& t ) const;
	ExTime& operator+= ( const ExTime& t );

private:
	int hours;
	int minutes;
};


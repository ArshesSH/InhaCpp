#include "Chapter8.h"

#include <iostream>
#include <string>
#include "Vec2.h"

/*
* Q1.
* 선1의 두 점(x1,y1), (x2,y2)와
* 선2의 두 점(x3,y3), (x4,y4)가 있을 때
* 두 선의 교차점을 구하는 프로그램
* 
* 크래머 공식 이용
* 
* Input > 점 4개 입력: x1, y1, x2, y2, x3, y3, x4,y4
*		> 2 2 5 -1.0 4.0 2.0 -1.0 -2.0
* output > 교차점은 (2.88889, 1.11111)
* 두 선 평행 시 평행 출력
*/

struct Line
{
	Line() = default;
	
	// ax + by = c
	Line( const Vec2<float>& p1, const Vec2<float>& p2 )
	{
		a = -(p2.y - p1.y);
		b = (p2.x - p1.x);
		c = a * p1.x + b * p1.y;
	}

	bool IsSameWith( const Line& rhs )
	{
		if ( b == 0 )
		{
			return c == rhs.c;
		}
		else
		{
			return (-a / b == -rhs.a / rhs.b) && (c == rhs.c);
		}
	}

	bool IsParellelWith( const Line& rhs )
	{
		return (a * rhs.b - b * rhs.a) == 0;
	}

	Vec2<float> GetCrossPointWith( const Line& rhs )
	{
		const float d = (a * rhs.b - b * rhs.a);
		const float x = (c * rhs.b - b * rhs.c) / d;
		const float y = (a * rhs.c - c * rhs.a) / d;
		return { x, y };
	}
	
	float a;
	float b;
	float c;
};

void Chapter8::Question1()
{
	Vec2<float> p1, p2, p3, p4;

	std::cout << "두 점을 아는 두 선의 교차점을 구한다\n"
		<< "직선1 점1 입력 : ";
	std::cin >> p1.x >> p1.y;
	std::cout << "직선1 점2 입력 : ";
	std::cin >> p2.x >> p2.y;
	std::cout << "직선2 점1 입력 : ";
	std::cin >> p3.x >> p3.y;
	std::cout << "직선2 점2 입력 : ";
	std::cin >> p4.x >> p4.y;

	Line line1( p1, p2 );
	Line line2( p3, p4 );
	
	if ( line1.IsSameWith( line2 ) )
	{
		std::cout << "두 직선이 같습니다.\n\n";
	}
	else if ( line1.IsParellelWith( line2 ) )
	{
		std::cout << "두 직선이 평행합니다.\n\n";
	}
	else
	{
		const Vec2<float> crossPoint = line1.GetCrossPointWith( line2 );
		std::cout << "교차점은 (" << crossPoint.x << ", " << crossPoint.y << ") 입니다.\n\n";
	}
}

void Chapter8::Swaps()
{
	int wallet1 = 3000;
	int wallet2 = 3500;

	std::cout << "기존  = " << wallet1 << ", " << wallet2 << std::endl;

	auto swapp = []( int* lhs, int* rhs ) {
		int tmp = *lhs;
		*lhs = *rhs;
		*rhs = tmp;
	};
	auto swapr = []( int& lhs, int& rhs ) {
		int tmp = lhs;
		lhs = rhs;
		rhs = tmp;
	};
	auto swapv = []( int lhs, int rhs ) {
		int tmp = lhs;
		lhs = rhs;
		rhs = tmp;
	};

	swapp( &wallet1, &wallet2 );
	std::cout << "Pointer  = " << wallet1 << ", " << wallet2 << std::endl;
	swapr( wallet1, wallet2 );
	std::cout << "Reference  = " << wallet1 << ", " << wallet2 << std::endl;
	swapv( wallet1, wallet2 );
	std::cout << "Value  = " << wallet1 << ", " << wallet2 << std::endl;
}


struct job
{
	char name[60];
	double salary;
	int floor;
};

template<typename T>
T Max5( const T* list )
{
	T max = list[0];
	for ( int i = 0; i < 5; i++ )
	{
		max = std::max( list[i], max );
	}
	return max;
}

template<typename T>
T MaxN( T* list, int size )
{
	T max = list[0];
	for ( int i = 0; i < size; i++ )
	{
		max = std::max( list[i], max );
	}
	return max;
}

template<>
const char* MaxN( const char** str, int size )
{
	//char* strAddr = str[0];
	size_t maxSize = std::strlen( str[0] );
	size_t pos = 0;
	for ( int i = 0; i < size; i++ )
	{
		if ( maxSize < std::strlen( str[i] ) )
		{
			maxSize = std::strlen( str[i] );
			pos = i;
		}
	}
	return str[pos];
}

void Chapter8::Exercise5n6()
{
	std::cout << "문제 5번: 5개의 배열에서 가장 큰 값 찾기\n";

	std::cout << "int형 값 5개 입력 : ";
	int listI[5];
	for ( int i = 0; i < 5; i++ )
	{
		std::cin >> listI[i];
	}
	std::cout << "가장 큰 값은 " << Max5( listI ) << "입니다.\n\n";

	std::cout << "double형 값 5개 입력 : ";
	double listD[5];
	for ( int i = 0; i < 5; i++ )
	{
		std::cin >> listD[i];
	}
	std::cout << "가장 큰 값은 " << Max5( listD ) << "입니다.\n\n";

	std::cout << "문제 6번 템플릿 \n";
	std::cout << "int형 값 6개 입력 : ";
	int tListI[6];
	for ( int i = 0; i < 6; i++ )
	{
		std::cin >> tListI[i];
	}
	std::cout << "가장 큰 값은 " << MaxN( tListI, 6 ) << "입니다.\n\n";

	std::cout << "double형 값 4개 입력 : ";
	int tListD[4];
	for ( int i = 0; i < 4; i++ )
	{
		std::cin >> tListD[i];
	}
	std::cout << "가장 큰 값은 " << MaxN( tListD, 4 ) << "입니다.\n\n";


	const char* tListStr[4] = {"hello", "asdf", "asfsadfsa", "asdfasf"};
	for ( int i = 0; i < 4; i++ )
	{
		std::cout << "문자" << i << " = " << tListStr[i] << std::endl;
	}
	std::cout << "가장 길이가 큰 str : " << MaxN( tListStr, 4 ) << std::endl;
}

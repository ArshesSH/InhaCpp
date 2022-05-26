#include "Chapter8.h"

#include <iostream>
#include <string>
#include "Vec2.h"

/*
* Q1.
* ��1�� �� ��(x1,y1), (x2,y2)��
* ��2�� �� ��(x3,y3), (x4,y4)�� ���� ��
* �� ���� �������� ���ϴ� ���α׷�
* 
* ũ���� ���� �̿�
* 
* Input > �� 4�� �Է�: x1, y1, x2, y2, x3, y3, x4,y4
*		> 2 2 5 -1.0 4.0 2.0 -1.0 -2.0
* output > �������� (2.88889, 1.11111)
* �� �� ���� �� ���� ���
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

	std::cout << "�� ���� �ƴ� �� ���� �������� ���Ѵ�\n"
		<< "����1 ��1 �Է� : ";
	std::cin >> p1.x >> p1.y;
	std::cout << "����1 ��2 �Է� : ";
	std::cin >> p2.x >> p2.y;
	std::cout << "����2 ��1 �Է� : ";
	std::cin >> p3.x >> p3.y;
	std::cout << "����2 ��2 �Է� : ";
	std::cin >> p4.x >> p4.y;

	Line line1( p1, p2 );
	Line line2( p3, p4 );
	
	if ( line1.IsSameWith( line2 ) )
	{
		std::cout << "�� ������ �����ϴ�.\n\n";
	}
	else if ( line1.IsParellelWith( line2 ) )
	{
		std::cout << "�� ������ �����մϴ�.\n\n";
	}
	else
	{
		const Vec2<float> crossPoint = line1.GetCrossPointWith( line2 );
		std::cout << "�������� (" << crossPoint.x << ", " << crossPoint.y << ") �Դϴ�.\n\n";
	}
}

void Chapter8::Swaps()
{
	int wallet1 = 3000;
	int wallet2 = 3500;

	std::cout << "����  = " << wallet1 << ", " << wallet2 << std::endl;

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
	std::cout << "���� 5��: 5���� �迭���� ���� ū �� ã��\n";

	std::cout << "int�� �� 5�� �Է� : ";
	int listI[5];
	for ( int i = 0; i < 5; i++ )
	{
		std::cin >> listI[i];
	}
	std::cout << "���� ū ���� " << Max5( listI ) << "�Դϴ�.\n\n";

	std::cout << "double�� �� 5�� �Է� : ";
	double listD[5];
	for ( int i = 0; i < 5; i++ )
	{
		std::cin >> listD[i];
	}
	std::cout << "���� ū ���� " << Max5( listD ) << "�Դϴ�.\n\n";

	std::cout << "���� 6�� ���ø� \n";
	std::cout << "int�� �� 6�� �Է� : ";
	int tListI[6];
	for ( int i = 0; i < 6; i++ )
	{
		std::cin >> tListI[i];
	}
	std::cout << "���� ū ���� " << MaxN( tListI, 6 ) << "�Դϴ�.\n\n";

	std::cout << "double�� �� 4�� �Է� : ";
	int tListD[4];
	for ( int i = 0; i < 4; i++ )
	{
		std::cin >> tListD[i];
	}
	std::cout << "���� ū ���� " << MaxN( tListD, 4 ) << "�Դϴ�.\n\n";


	const char* tListStr[4] = {"hello", "asdf", "asfsadfsa", "asdfasf"};
	for ( int i = 0; i < 4; i++ )
	{
		std::cout << "����" << i << " = " << tListStr[i] << std::endl;
	}
	std::cout << "���� ���̰� ū str : " << MaxN( tListStr, 4 ) << std::endl;
}

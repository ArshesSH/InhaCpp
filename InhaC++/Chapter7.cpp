#include "Chapter7.h"

#include <iostream>
#include <string>
#include <array>
#include <cctype>
#include "Vec2.h"
#include <cstdio>
/*
* �ﰢ�� 3���� ���� �˰� ���� �� �ﰢ���� ������ ���ϴ� ���α׷�
* Input : 1.5 -3.4 4.6 5 9.5 -3.4
* ���� : 33.6
*/


void Chapter7::Question1()
{

	struct Vec2
	{
		float x;
		float y;
	};


	struct Triangle
	{
		Vec2 p1;
		Vec2 p2;
		Vec2 p3;

		float GetTriangleArea()
		{
			return std::abs(
				((p1.x * p2.y) + (p2.x * p3.y) + (p3.x * p1.y))
				- ((p2.x * p1.y) + (p3.x * p2.y) + (p1.x * p3.y))
			) / 2.0f;
		}
	};

	Triangle tri;

	std::cout << "�ﰢ���� ���� ��� \n"
		<< "Input P1(x1, y1) : ";
	std::cin >> tri.p1.x >> tri.p1.y;
	std::cout << "Input P2(x2, y2) : ";
	std::cin >> tri.p2.x >> tri.p2.y;
	std::cout << "Input P3(x3, y3) : ";
	std::cin >> tri.p3.x >> tri.p3.y;

	std::cout << tri.GetTriangleArea() << std::endl;
}


/*
* ��й�ȣ ��Ģ
* 1. ��й�ȣ�� ��� 8���� ����
* 2. ��й�ȣ�� ���ڿ� ���ڷθ� �����Ǿ���Ѵ�
* 3. ��й�ȣ�� ��� �ΰ��� ���ڰ� ���ԵǾ���Ѵ�
* ��й�ȣ�� �Է����� �� ��Ģ�� ������ valid password �ƴϸ� Invalid password ���
*/

struct Password
{
	std::string words;
	const int minNumCnt = 2;

	bool IsValid()
	{
		// If password is less than 8 chars
		if ( words.size() < 8 )
		{
			return false;
		}

		int numCnt = 0;
		int alphaCnt = 0;
		for ( auto c : words )
		{
			if ( std::isdigit( c ) )
			{
				// Increase numCnt if find digit
				numCnt++;
			}
			else if( std::isalpha( c ) )
			{
				// Increase charCnt if find alpha
				alphaCnt++;
			}
			else
			{
				// Return false when char not num and alpha
				return false;
			}
		}

		// Return false when numCnt or alphaCnt less than 2
		if ( numCnt < 2 || alphaCnt < 2)
		{
			return false;
		}

		return true;
	}
};

void Chapter7::Question2()
{
	Password pw;

	std::cout << "��й�ȣ 8���� ����, ���� �� ���ڷ� ����, �ּ� �� �� ���� ���� \n"
		<< "Input Password : ";
	std::cin >> pw.words;

	if ( pw.IsValid() )
	{
		std::cout << "Valid password\n\n";
	}
	else
	{
		std::cout << "Invalid password\n\n";
	}
}

void Subdivide( char* ar, int low, int high, int level )
{
	if ( level == 0 )
	{
		return;
	}
	int mid = (high + low) / 2;
	ar[mid] = '|';
	Subdivide( ar, low, mid, level - 1 );
	Subdivide( ar, mid, high, level - 1 );
}

const int Len = 66;
const int Divs = 6;

void Chapter7::Ruler()
{
	char ruler[Len];
	
	int i;
	for ( i = 1; i < Len - 2; i++ )
	{
		ruler[i] = ' ';
	}
	ruler[Len - 1] = '\0';
	int max = Len - 2;
	int min = 0;
	ruler[min] = ruler[max] = '|';
	std::cout << ruler << std::endl;
	for ( i = 1; i < Divs; i++ )
	{
		Subdivide( ruler, min, max, i );
		std::cout << ruler << std::endl;
		for ( int j = 1; j < Len - 2; j++ )
		{
			ruler[j] = ' ';
		}
	}
}

const double* f1( const double ar[], int n ) { return ar; }
const double* f2( const double[], int );
const double* f3( const double*, int );

void Chapter7::Arfupt()
{
	double av[3] = { 1112.3, 1542.6, 2227.9 };
	
	const double* (*p1)(const double*, int) = f1;
	auto p2 = f2;

	std::cout << "�Լ������� :\n�ּҰ�\n" << (*p1)(av, 3) << " : " << *(*p1)(av, 3) << std::endl;
	std::cout << "�Լ������� :\n�ּҰ�\n" << p2(av, 3) << " : " << *p2(av, 3) << std::endl;

	const double* (*pa[3])(const double*, int) = { f1, f2, f3 };
	auto pb = pa;
	std::cout << "\n�Լ� �����͸� ���ҷ� ������ �迭 :\n �ּ� ��\n";
	for ( int i = 0; i < 3; i++ )
	{
		std::cout << pa[i]( av, 3 ) << " : " << *pa[i]( av, 3 ) << std::endl;
	}
	
	std::cout << "\n�����͸� ���ҷ� ������ �迭�� ����Ű�� ������ :\n�ּҰ�\n";
	auto pc = &pa;
	std::cout << (*pc)[0]( av, 3 ) << " : " << *(*pc)[0](av, 3) << std::endl;
	const double* (*(*pd)[3])(const double*, int) = &pa;
	const double* pdb = (*pd)[1]( av, 3 );
	std::cout << pdb << ": " << *pdb << std::endl;
	std::cout << (*(*pd)[2])(av, 3) << " : " << *(*(*pd)[2])(av, 3) << std::endl;
}

const double* f2( const double ar[], int n )
{
	return ar + 1;
}
const double* f3( const double* ar, int n )
{
	return ar + 2;
}

/*
* ��(x,y)�� �Է¹޾� �� ���� (x0,y0)�� �߽����� �ϰ� �������� r�� �� ���ο� �����ϴ��� �˻��ϴ� ���α׷�
* input > r = 10, x0 = 0, y0 = 0, x = 5, y = 5
* output > �� 4,5�� ������ (0,0)�̰� �������� 10�� �� �ȿ� �ֽ��ϴ�.
* 
* ���� ���ο� �����ϴ��� �˻��ϴ� �Լ��� �����,
* ������ ���� ���ڷ� �Ѱ� �� �� ������ ����ü�� �̿��ؼ� ����
*/

struct Circle
{
	float r;
	Vec2<float> center;
};

bool IsDotInCircle( const Circle* const circle, const Vec2<float>* const dot )
{
	const float distance = (*dot - circle->center).GetLengthSq();
	
	if ( distance <= std::powf(circle->r, 2) )
	{
		return true;
	}
	return false;
}

void Chapter7::Question3()
{
	Circle circle;
	float x, y;
	std::cout << "���� �������Է� : ";
	std::cin >> circle.r;
	std::cout << "���� ���� �Է�(x, y) : ";
	std::cin >> x >> y;
	circle.center = { x, y };
	std::cout << "�� �Է�(x, y) : ";
	std::cin >> x >> y;
	const Vec2<float> dot = { x, y };

	if ( IsDotInCircle( &circle, &dot ) )
	{
		printf( "��(%.1f, %.1f)�� ������ (%.1f, %.1f)�̰� �������� %.1f�� �� �ȿ� �ֽ��ϴ�.",
			dot.x, dot.y, circle.center.x, circle.center.y, circle.r );
	}
	else
	{
		printf( "��(%.1f, %.1f)�� ������ (%.1f, %.1f)�̰� �������� %.1f�� �� �ȿ� �����ϴ�.",
			dot.x, dot.y, circle.center.x, circle.center.y, circle.r );
	}
}
#include "Chapter11.h"

#include <iostream>
#include "ExTime.h"
#include "cVec3.h"
#include "Circle2D.h"
#include "Rect2D.h"
#include "MyPoint.h"

/*
* Q1.
* n을 입력받아 2^n 형태의 값
* ex n = 3
*						1
*					  1 2 1
*					1 2 4 2 1
*				  1 2 4 8 4 2 1
*/
void Chapter11::Question1()
{
	int n;
	std::cout << "\nn입력 : ";
	std::cin >> n;

	for ( int line = 1; line <= n + 1; ++line )
	{
		for ( int space = n - line; space >= 0; --space )
		{
			std::cout << "     ";
		}
		for ( int i = 0; i < line * 2 - 1; ++i )
		{
			if ( i < line )
			{
				printf( "%5d", (int)std::pow( 2, i ) );
			}
			else
			{
				const int flipI = line * 2 - 2 - i;
				printf( "%5d", (int)std::pow( 2, flipI ) );
			}
		}
		std::cout << std::endl;
	}
}

void Chapter11::ExOperatorOverloading()
{
	ExTime planning;
	ExTime coding( 2, 40 );
	ExTime fixing( 5, 55 );
	ExTime total;

	std::cout << "Planning time = ";
	planning.Show();
	std::cout << std::endl;

	std::cout << "Coding time = ";
	coding.Show();
	std::cout << std::endl;

	std::cout << "Fixing time = ";
	fixing.Show();
	std::cout << std::endl;

	total = coding + fixing;
	std::cout << "coding + fixing = ";
	total.Show();
	std::cout << std::endl;

	ExTime morefixing( 3, 28 );
	std::cout << "more fixing time = ";
	morefixing.Show();
	std::cout << std::endl;

	total = morefixing.operator+( total );
	std::cout << "morefixing.operator+( total ) = ";
	total.Show();
	std::cout << std::endl;
}

void Chapter11::ExVector()
{
	const cVec3<double> u( -1, 3, 2 );
	const cVec3<double> v( 3, -4, 1 );
	std::cout << "문제1 operator\n";
	std::cout << "u + v = " << u + v << std::endl;
	std::cout << "u - v = " << u - v << std::endl;
	std::cout << "3u + 2v = " << (3 * u) + (2 *v) << std::endl;
	std::cout << "-2u + v = " << (u * -2) + v << std::endl;

	std::cout << "\n문제2 normal\n";
	std::cout << "Normal(u) = " << u.GetNormalized() << "Normal(v) = " << v.GetNormalized() << std::endl;

	std::cout << "\n문제3 angle\n";
	std::cout << "u = (1,1,1), v = (2,3,4), Angle = "
		<< cVec3<double>::Angle( cVec3<double>( 1, 1, 1 ), cVec3<double>( 2, 3, 4 ) ) << std::endl;
	std::cout << "u = (1,1,0), v = (-2,2,0), Angle = "
		<< cVec3<double>::Angle( cVec3<double>( 1, 1, 0 ), cVec3<double>( -2, 2, 0 ) ) << std::endl;
	std::cout << "u = (-1,-1,-1), v = (3,1,0), Angle = "
		<< cVec3<double>::Angle( cVec3<double>( -1, -1, -1 ), cVec3<double>( 3, 1, 0 ) ) << std::endl;

	const cVec3<double> vA( 0, 0, 0 );
	const cVec3<double> vB( 0, 1, 3 );
	const cVec3<double> vC( 5, 1, 0 );
	
	const cVec3<double> vAB = vB - vA;
	const cVec3<double> vAC = vC - vA;
	const cVec3<double> vNormalTriangle = cVec3<double>::Cross( vAB, vAC );
	std::cout << "\n문제4\nA = (0,0,0), B = (0,1,3), C = (5,1,0)으로 구성된 삼각형의 법선벡터\n"
		<< "Vector AB = " << vAB << ", Vector AC = " << vAC
		<< "\nNormal Vec = " << vNormalTriangle
		<< "\nNormalized Normal Vec = " << vNormalTriangle.GetNormalized() << std::endl;
}

class Stonewt
{
public:
	Stonewt( double lbs )
	{
		stone = int( lbs ) / Lbs_per_stn;
		pds_left = int( lbs ) % Lbs_per_stn + lbs - int( lbs );
		pounds = lbs;
	}
	Stonewt( int stn, double lbs )
	{
		stone = stn;
		pds_left = lbs;
		pounds = stn * Lbs_per_stn + lbs;
	}
	Stonewt()
	{
		stone = 0;
		pds_left = pounds = 0.0;
	}
	void show_lbs() const
	{
		std::cout << stone << "스톤, " << pds_left << "파운드\n";
	}
	void show_stn() const
	{
		std::cout << pounds << "파운드\n";
	}

	// 변환 함수
	operator int() const
	{
		return int( pounds + 0.5 );
	}
	operator double() const
	{
		return pounds;
	}

private:
	static constexpr int Lbs_per_stn = 14;
	int stone;
	double pds_left;
	double pounds;
};

void Chapter11::ExDataTypeChange()
{
	Stonewt poppins( 9, 2.8 );
	// 암시적 변환
	double p_wt = poppins;
	
	std::cout << "double형으로 변환 => Poppins: " << p_wt << "파운드\n";
	std::cout << "int형으로 변환 => Poppins: " << int( poppins ) << "파운드\n";
}


/*
* 다음을 포함하는 Circle2D클래스를 정의하라
* - 원의 중심을 나타내는 x,y라는 두 개의 double 데이터 필드와 get 상수함수
* - double 데이터 필드 radius와 get 상수 함수
* - (x,y)가 (0,0), radius가 1인 기본 원을 생성하는 기본생성자
* - 지정된 x,y 와 radius로 원을 생성하는 생성자
* - 원의 면적을 반환하는 getArea() 상수함수
* - 원의 둘레를 반환하는 getPerimeter() 상수함수
* - 지정된 점(x,y)가 생성된 원 내부에 있을 경우, true 를 반환하는 contains(double x, double y) 상수함수
* - 지정된 원이 생성된 원 내부에 있을 경우, true를 반환하는 contains(const circle2d& circle) 상수함수
* - 지정된 원이 생성된 원과 중첩되는 경우, true를 반환하는 overlaps(const circle2d& circle)상수 함수
* - 클래스에 대한 uml 다이어그램 그리고 클래스를 구현하라
* 
* Circle2D객체 c1(2,2,5.5), c2(2,2,5.5) c3(4,5,10.5)를 생성하고, c1의 면적과 둘레, c1.contains(3,3), c1.contains(c2), c1.overlaps(c3)
* 의 결과를 화면에 출력하는 프로그램
*/
void Chapter11::Question2()
{
	std::cout << "c1(2, 2, 5.5), c2(2, 2, 5.5) c3(4, 5, 10.5) 생성\n";
	Circle2D<double> c1( 2, 2, 5.5 );
	Circle2D<double> c2( 2, 2, 5.5 );
	Circle2D<double> c3( 4, 5, 10.5 );
	Circle2D<double> c4( 3, 2, 10.5 );

	std::cout << "c1의 면적: " << c1.GetArea() << "\nc1의 둘레: " << c1.GetPerimeter() << std::endl;
	std::cout << "c1.contains( 3, 3 ) : " << std::boolalpha << c1.IsContains( 3, 3 ) << std::endl;
	std::cout << "c1.contains( c2 ) : " << std::boolalpha << c1.IsContains( c2 ) << std::endl;
	std::cout << "c1.overlaps( c3 ) : " << std::boolalpha << c1.IsOverlapWith( c3 ) << std::endl;
	std::cout << "c1.contains( c4 ) : " << std::boolalpha << c1.IsContains( c4 ) << std::endl;
	std::cout << "c4.contains( c1 ) : " << std::boolalpha << c4.IsContains( c1 ) << std::endl;
	std::cout << "c1.contains( c3 ) : " << std::boolalpha << c1.IsContains( c4 ) << std::endl;
	std::cout << "c1.IsContainedBy( c3 ) : " << std::boolalpha << c1.IsContainedBy( c3 ) << std::endl;
	std::cout << "c4.IsContainedBy( c1 ) : " << std::boolalpha << c4.IsContainedBy( c1 ) << std::endl;
	std::cout << "c1.IsContainedBy( c4 ) : " << std::boolalpha << c1.IsContainedBy( c4 ) << std::endl;
}

/*
* 다음을 포함하는 Rectangle2D클래스를 정의하라.
* 직사각형의 중심을 나타내는 x,y 두개의 double 데이터 필드.
* get set, 변은 x축과 y축 평행
* double데이터 필드 widht, height, 이에 대한 get set
* x,y는 0,0 width height은 모두 1인 기본생성자
* 지정된 x,y,width, height 으로 직사각형 생성하는 생성자
* 직사각형 면적 반환 getarea()
* 직사각형 둘레를 반환하는 getperimeter()
* 지정된 점이 직사각형 내부에 있을 경우 contains 함수
* 지정된 직사각형이 생성된 직사각형 내부에 있을 경우 contains
* 직사각형이 생성된 직사각형과 중첩 overlap
* uml작성
* 3개의 rect2d r1(2,2,5.5, 4.9), r2(4,5,10.5,3.2), r3(3,5,2.3,5.4) 생성 및
* r1 면적과 둘레 출력
* r1.contains(3,3)
* r1.contains(r2),
* r1.overlaps(r3)의 결과 출력
*/

void Chapter11::Question3()
{
	Rect2D<double> r1( 2, 2, 5.5, 4.9 );
	Rect2D<double> r2( 4, 5, 10.5, 3.2 );
	Rect2D<double> r3( 3, 5, 2.3, 5.4 );
	Rect2D<double> r4( 0,1,2,4 );
	Rect2D<double> r5( 0,4,4,2 );

	std::cout << "r1(2, 2, 5.5, 4.9), r2(4, 5, 10.5, 3.2), r3(3, 5, 2.3, 5.4)" << std::endl;
	std::cout << "r1.GetArea() = " << r1.GetArea() << std::endl;
	std::cout << "r1.GetPerimeter() = " << r1.GetPerimeter() << std::endl;
	std::cout << "r1.IsContains( 3, 3 ) = " << std::boolalpha << r1.IsContains( 3, 3 ) << std::endl;
	std::cout << "r1.IsContains( r2 ) = " << std::boolalpha << r1.IsContains( r2 ) << std::endl;
	std::cout << "r1.IsOverlapWith( r3 ) = " << std::boolalpha << r1.IsOverlapWith( r3 ) << std::endl;

	std::cout << "r1.IsContains( r4 ) = " << std::boolalpha << r1.IsContains( r4 ) << std::endl;
	std::cout << "r4.IsContains( r1 ) = " << std::boolalpha << r4.IsContains( r1 ) << std::endl;
	std::cout << "r1.IsContainedBy( r4 ) = " << std::boolalpha << r1.IsContainedBy( r4 ) << std::endl;
	std::cout << "r4.IsContainedBy( r1 ) = " << std::boolalpha << r4.IsContainedBy( r1 ) << std::endl;
	std::cout << "r1.IsOverlapWith( r4 ) = " << std::boolalpha << r1.IsOverlapWith( r4 ) << std::endl;
	std::cout << "r4.IsOverlapWith( r1 ) = " << std::boolalpha << r4.IsOverlapWith( r1 ) << std::endl;
	std::cout << "r4.IsOverlapWith( r5 ) = " << std::boolalpha << r4.IsOverlapWith( r5 ) << std::endl;
}

/*
*  x와 y축의 점을 표시하는 MyPoint 클래스를 설계하라.
    - 좌표를 나타내는 두개의 x,y 데이터 필드
    - 점(0,0)을 생성하는 인수 없는 생성자
    - 지정 좌표의 점을 생성하는 생성자
    - x, y 데이터 필드를 위한 가각 두개의 get 함수
    - MyPoint 유형의 한 점에서 다른 점까지의 거리를 반환하는 distance 함수
    클래스에 대한 UML 다이어 그램을 그리고, 클래스를 구현하라.
    두개의 점 (0,0)과 (10, 30.5)를 생성하고 두 점 사이의 거리를 표시하는
    테스트 프로그램을 작성하라.

    생성된 좌표의 점이 circle2D 클래스의 객체나 Rectangle2D 객체의 내부에 있는지
    여부를 판단하는 contains() 함수를 MyPoint 객체를 인자로 하는
    프렌드 함수로 구현하라.
*/

void Chapter11::Question4()
{
	MyPoint<double> p1( 0, 0 );
	MyPoint<double> p2( 10, 30.5 );
	Rect2D<double> rect1( 1, 1, 2, 2 );
	Circle2D<double> c1( 1, 1, 1 );
	
	std::cout << "p1: (0, 0), p2: (10, 30.5)\n";
	std::cout << "Distance = " << p1.GetDistanceWith( p2 ) << std::endl;
	std::cout << "IsContains( rect1, p1 )= " << std::boolalpha << IsContains( rect1, p1 ) << std::endl;
	std::cout << "IsContains( c1, p1 )= " << std::boolalpha << IsContains( c1, p1 ) << std::endl;
}

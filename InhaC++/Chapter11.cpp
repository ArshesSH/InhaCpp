#include "Chapter11.h"

#include <iostream>
#include "ExTime.h"
#include "cVec3.h"
#include "Circle2D.h"
#include "Rect2D.h"
#include "MyPoint.h"

/*
* Q1.
* n�� �Է¹޾� 2^n ������ ��
* ex n = 3
*						1
*					  1 2 1
*					1 2 4 2 1
*				  1 2 4 8 4 2 1
*/
void Chapter11::Question1()
{
	int n;
	std::cout << "\nn�Է� : ";
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
	std::cout << "����1 operator\n";
	std::cout << "u + v = " << u + v << std::endl;
	std::cout << "u - v = " << u - v << std::endl;
	std::cout << "3u + 2v = " << (3 * u) + (2 *v) << std::endl;
	std::cout << "-2u + v = " << (u * -2) + v << std::endl;

	std::cout << "\n����2 normal\n";
	std::cout << "Normal(u) = " << u.GetNormalized() << "Normal(v) = " << v.GetNormalized() << std::endl;

	std::cout << "\n����3 angle\n";
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
	std::cout << "\n����4\nA = (0,0,0), B = (0,1,3), C = (5,1,0)���� ������ �ﰢ���� ��������\n"
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
		std::cout << stone << "����, " << pds_left << "�Ŀ��\n";
	}
	void show_stn() const
	{
		std::cout << pounds << "�Ŀ��\n";
	}

	// ��ȯ �Լ�
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
	// �Ͻ��� ��ȯ
	double p_wt = poppins;
	
	std::cout << "double������ ��ȯ => Poppins: " << p_wt << "�Ŀ��\n";
	std::cout << "int������ ��ȯ => Poppins: " << int( poppins ) << "�Ŀ��\n";
}


/*
* ������ �����ϴ� Circle2DŬ������ �����϶�
* - ���� �߽��� ��Ÿ���� x,y��� �� ���� double ������ �ʵ�� get ����Լ�
* - double ������ �ʵ� radius�� get ��� �Լ�
* - (x,y)�� (0,0), radius�� 1�� �⺻ ���� �����ϴ� �⺻������
* - ������ x,y �� radius�� ���� �����ϴ� ������
* - ���� ������ ��ȯ�ϴ� getArea() ����Լ�
* - ���� �ѷ��� ��ȯ�ϴ� getPerimeter() ����Լ�
* - ������ ��(x,y)�� ������ �� ���ο� ���� ���, true �� ��ȯ�ϴ� contains(double x, double y) ����Լ�
* - ������ ���� ������ �� ���ο� ���� ���, true�� ��ȯ�ϴ� contains(const circle2d& circle) ����Լ�
* - ������ ���� ������ ���� ��ø�Ǵ� ���, true�� ��ȯ�ϴ� overlaps(const circle2d& circle)��� �Լ�
* - Ŭ������ ���� uml ���̾�׷� �׸��� Ŭ������ �����϶�
* 
* Circle2D��ü c1(2,2,5.5), c2(2,2,5.5) c3(4,5,10.5)�� �����ϰ�, c1�� ������ �ѷ�, c1.contains(3,3), c1.contains(c2), c1.overlaps(c3)
* �� ����� ȭ�鿡 ����ϴ� ���α׷�
*/
void Chapter11::Question2()
{
	std::cout << "c1(2, 2, 5.5), c2(2, 2, 5.5) c3(4, 5, 10.5) ����\n";
	Circle2D<double> c1( 2, 2, 5.5 );
	Circle2D<double> c2( 2, 2, 5.5 );
	Circle2D<double> c3( 4, 5, 10.5 );
	Circle2D<double> c4( 3, 2, 10.5 );

	std::cout << "c1�� ����: " << c1.GetArea() << "\nc1�� �ѷ�: " << c1.GetPerimeter() << std::endl;
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
* ������ �����ϴ� Rectangle2DŬ������ �����϶�.
* ���簢���� �߽��� ��Ÿ���� x,y �ΰ��� double ������ �ʵ�.
* get set, ���� x��� y�� ����
* double������ �ʵ� widht, height, �̿� ���� get set
* x,y�� 0,0 width height�� ��� 1�� �⺻������
* ������ x,y,width, height ���� ���簢�� �����ϴ� ������
* ���簢�� ���� ��ȯ getarea()
* ���簢�� �ѷ��� ��ȯ�ϴ� getperimeter()
* ������ ���� ���簢�� ���ο� ���� ��� contains �Լ�
* ������ ���簢���� ������ ���簢�� ���ο� ���� ��� contains
* ���簢���� ������ ���簢���� ��ø overlap
* uml�ۼ�
* 3���� rect2d r1(2,2,5.5, 4.9), r2(4,5,10.5,3.2), r3(3,5,2.3,5.4) ���� ��
* r1 ������ �ѷ� ���
* r1.contains(3,3)
* r1.contains(r2),
* r1.overlaps(r3)�� ��� ���
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
*  x�� y���� ���� ǥ���ϴ� MyPoint Ŭ������ �����϶�.
    - ��ǥ�� ��Ÿ���� �ΰ��� x,y ������ �ʵ�
    - ��(0,0)�� �����ϴ� �μ� ���� ������
    - ���� ��ǥ�� ���� �����ϴ� ������
    - x, y ������ �ʵ带 ���� ���� �ΰ��� get �Լ�
    - MyPoint ������ �� ������ �ٸ� �������� �Ÿ��� ��ȯ�ϴ� distance �Լ�
    Ŭ������ ���� UML ���̾� �׷��� �׸���, Ŭ������ �����϶�.
    �ΰ��� �� (0,0)�� (10, 30.5)�� �����ϰ� �� �� ������ �Ÿ��� ǥ���ϴ�
    �׽�Ʈ ���α׷��� �ۼ��϶�.

    ������ ��ǥ�� ���� circle2D Ŭ������ ��ü�� Rectangle2D ��ü�� ���ο� �ִ���
    ���θ� �Ǵ��ϴ� contains() �Լ��� MyPoint ��ü�� ���ڷ� �ϴ�
    ������ �Լ��� �����϶�.
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

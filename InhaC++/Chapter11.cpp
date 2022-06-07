#include "Chapter11.h"

#include <iostream>
#include "ExTime.h"
#include "cVec3.h"

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

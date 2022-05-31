#include "Chapter10.h"

#include <iostream>
#include "Vec2.h"
#include "Vec3.h"
#include "stock00.h"

/*
* Q1
* �б��� 100���� �繰�԰� 100���� �л��� �ִ�.
* ��� �繰���� ù ���� �����ִ�
* �л��� ���Ƿ� ���鼭
*	s1�̶�� ù ��° �л��� ��� �繰���� ����.
*	s2��� �� ��° �л��� �繰�� L2���� �����Ͽ� �ϳ��� �ǳʶٸ鼭 �繰���� �ݴ´�.
*	s3��� �� ��° �л��� �繰�� L3���� �����Ͽ� �� ��° �繰�� ���� ���¸� �����Ѵ�.
*	s4��� �� ��° �л��� �繰�� L4���� �����Ͽ� �� ��° �繰�� ���� ���¸� �����Ѵ�.
*	...
*	s100�̶�� �� ��° �л��� �繰�� L100���� �����Ͽ� 100 ��° �繰�� ���� ���¸� �����Ѵ�.
* 
*	��� �л��� ������ ����ϰ� �� ���� � �繰���� �����ִ���, �����ִ� ��� �繰�� ��ȣ�� ���
*/

void ChangeLockerState( bool& isLockerClose )
{
	isLockerClose = 1 - isLockerClose;
}

void Chapter10::Question1()
{
	// s1
	bool isLockerCloseList[100] = { false };

	for ( int s = 2; s <= 100; s++ )
	{
		for ( int i = 1; i * s < 100; i++ )
		{
			ChangeLockerState( isLockerCloseList[(i * s) - 1] );
		}
	}

	std::cout << "�����ִ� �繰���� :\n";
	for ( int i = 0; i < 100; i++ )
	{
		if ( isLockerCloseList[i] == false )
		{
			std::cout << i + 1 << "��° ";
		}
	}
	std::cout << std::endl;
}


/*
* Q2
* �� p0���� p1������ ������ �־����� ��
* �� p2�� ���� ���� �Ǵ� �����ʿ� �ִ��� �Ǵ��� �� �ִ�.
* �� p0, p1, p2 �Է� �� �� p2�� ��� ��ġ�ϴ��� ����ϴ� ���α׷�
* 
* p0 : 4.4 2
* p1 : 6.5 9.5
* p2 : -5 4
* p2�� ���� ���ʿ� �ִ�.
*/
void Chapter10::Question2()
{
	Vec3<float> point[3];

	for ( int i = 0; i < 3; i++ )
	{
		std::cout << "�� p" << i << "(x" << i << ", y" << i << ") : ";
		std::cin >> point[i].x >> point[i].y;
		point[i].z = 0;
	}
	
	const Vec3<float> line = point[1] - point[0];
	const Vec3<float> lineDir = line.GetNormalized();
	
	const Vec3<float> crossed = Vec3<float>::GetCrossProduct( lineDir, point[2] );
	
	if ( crossed.z > 0 )
	{
		std::cout << "p2�� ���� ���ʿ� �ִ�." << std::endl;
	}
	else if ( crossed.z < 0 )
	{
		std::cout << "p2�� ���� �����ʿ� �ִ�." << std::endl;
	}
	else
	{
		std::cout << "p2�� �� ���� �ִ�." << std::endl;
	}
}

void Chapter10::LearnClass()
{
	Stock fluffy_the_cat;
	fluffy_the_cat.acquire( "NanoSmart", 20, 12.50 );
	fluffy_the_cat.show();
	fluffy_the_cat.buy( 15, 18.125 );
	fluffy_the_cat.show();
	fluffy_the_cat.sell( 400, 20.00 );
	fluffy_the_cat.show();
	fluffy_the_cat.buy( 300000, 40.125 );
	fluffy_the_cat.show();
	fluffy_the_cat.sell( 300000, 0.125 );
	fluffy_the_cat.show();
}


/*
* Q3
* �ﰢ���� �� ���� ���̸� �˸� ������ ������ ���� �� �ִ�.
* �ﰢ���� �� ������ ��ǥ�� �Է¹��� �� �ﰢ���� ������ ���϶�
* 
* ex>
* �� 1 : 1 1
* �� 2 : 6.5 1
* �� 3 : 6.5 2.5
* �� ���� 15.25, 90.00, 74.74 �̴�.
*/
template<typename T>
T GetRadian( const Vec2<T>& lineOne, const Vec2<T>& lineTwo )
{
	return (T)std::acosf( (lineOne * lineTwo) / std::sqrtf(lineOne.GetLengthSq() * lineTwo.GetLengthSq()) );
}

void Chapter10::Question3()
{
	Vec2<float> p[3];
	for ( int i = 0; i < 3; i++ )
	{
		std::cout << "��" << i << " : ";
		std::cin >> p[i].x >> p[i].y;
	}

	const float pi = 3.141592;
	const float radCoef = (180 / pi);

	float angle[3];
	bool isTriangle = true;
	for ( int i = 0; i < 3; i++ )
	{
		int indexLeft = i - 1;
		if ( indexLeft == -1 )
		{
			indexLeft = 2;
		}

		int indexRight = i + 1;
		if ( indexRight == 3 )
		{
			indexRight = 0;
		}

		const Vec2<float> lineOne = p[indexLeft] - p[i];
		const Vec2<float> lineTwo = p[indexRight] - p[i];

		angle[i] = radCoef * GetRadian( lineOne, lineTwo );
		if ( std::isnan( angle[i] ) )
		{
			isTriangle = false;	
		}
	}

	if ( isTriangle )
	{
		const auto origin = std::cout.setf( std::ios_base::fixed, std::ios_base::floatfield );
		const auto prec = std::cout.precision( 2 );

		std::cout << "�� ���� " << angle[0] << " " << angle[1] << " " << angle[2] << "�̴�.\n" << std::endl;

		std::cout.setf( origin, std::ios_base::floatfield );
		std::cout.precision( prec );
	}
	else
	{
		std::cout << "�ﰢ���� �ƴմϴ�!!!\n" << std::endl;
	}

}

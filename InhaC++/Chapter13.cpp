#include "Chapter13.h"

#include <iostream>
#include "TableTennisPlayer.h"

#include <memory>
#include <vector>
#include "GeometricObject.h"


void Chapter13::ExInheritance()
{
	TableTennisPlayer player1( "Tara", "Boomdea", false );
	RatedPlayer rplayer1( 1140, "Mallory", "Duck", true );
	rplayer1.Name();
	if ( rplayer1.HasTable() )
	{
		std::cout << ": 탁구대가 있다.\n";
	}
	else
	{
		std::cout << ": 탁구대가 없다.\n";
	}
	player1.Name();
	if ( player1.HasTable() )
	{
		std::cout << ": 탁구대가 있다.\n";
	}
	else
	{
		std::cout << ": 탁구대가 없다.\n";
	}
	std::cout << "이름: ";
	rplayer1.Name();
	std::cout << "; 랭킹: " << rplayer1.Rating() << std::endl;

	RatedPlayer rplayer2( 1212, player1 );
	std::cout << "이름: ";
	rplayer2.Name();
	std::cout << "; 랭킹: " << rplayer2.Rating() << std::endl;

	RatedPlayer::Show( rplayer1 );
	RatedPlayer::Show( player1 );
}


/*
* Circle2D, Rectangle2D, MyPoint 클래스를 추상 클래스 상속 개념을 적용하여 다시 작성
* BaseClass => GeometricObject
*/
void Chapter13::Question1()
{
	std::vector<std::unique_ptr<GeometricObject<double>>> geoObjects;
	geoObjects.push_back( std::make_unique<Circle<double>>( 2, 2, 5.5 ) );
	geoObjects.push_back( std::make_unique<Circle<double>>( 3, 2, 10.5 ) );
	geoObjects.push_back( std::make_unique<Rect<double>>( 2, 2, 5.5, 4.9 ) );
	geoObjects.push_back( std::make_unique<Rect<double>>( 4, 5, 10.5, 3.2 ) );
	geoObjects.push_back( std::make_unique<Point<double>>( 0, 0 ) );
	geoObjects.push_back( std::make_unique<Point<double>>( 10, 30.5 ) );

	std::cout << "c1( 2, 2, 5.5 ), c2( 3, 2, 10.5 )" << std::endl;

	std::cout << "c1의 면적: " << geoObjects[0]->GetArea() << "\nc1의 둘레: " << geoObjects[0]->GetPerimeter() << std::endl;
	std::cout << "c1.contains( 3, 3 ) : " << std::boolalpha << geoObjects[0]->IsContains( 3, 3 ) << std::endl;
	std::cout << "c1.contains( c2 ) : " << std::boolalpha << geoObjects[0]->IsContains( *geoObjects[1] ) << std::endl;
	std::cout << "c1.overlaps( c2 ) : " << std::boolalpha << geoObjects[0]->IsOverlapWith( *geoObjects[1] ) << std::endl;
	std::cout << "c1.IsContainedBy( c2 ) : " << std::boolalpha << geoObjects[0]->IsContainedBy( *geoObjects[1] ) << std::endl;

	std::cout << "r1(2, 2, 5.5, 4.9), r2(4, 5, 10.5, 3.2)" << std::endl;
	std::cout << "r1.GetArea() = " << geoObjects[2]->GetArea() << std::endl;
	std::cout << "r1.GetPerimeter() = " << geoObjects[2]->GetPerimeter() << std::endl;
	std::cout << "r1.IsContains( 3, 3 ) = " << std::boolalpha << geoObjects[2]->IsContains( 3, 3 ) << std::endl;
	std::cout << "r1.IsContains( r2 ) = " << std::boolalpha << geoObjects[2]->IsContains( *geoObjects[3] ) << std::endl;
	std::cout << "r1.IsOverlapWith( r2 ) = " << std::boolalpha << geoObjects[2]->IsOverlapWith( *geoObjects[3] ) << std::endl;

	std::cout << "p1: (0, 0), p2: (10, 30.5)\n";
	std::cout << "Distance = " << geoObjects[4]->GetDistanceWith( *geoObjects[5] ) << std::endl;
	std::cout << "IsContains( rect1, p1 )= " << std::boolalpha << Point<double>::IsContains( *geoObjects[2], *geoObjects[4] ) << std::endl;
	std::cout << "IsContains( c1, p1 )= " << std::boolalpha << Point<double>::IsContains( *geoObjects[0], *geoObjects[4] ) << std::endl;
}

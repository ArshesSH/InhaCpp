#include "Chapter13.h"

#include <iostream>
#include "TableTennisPlayer.h"

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
}

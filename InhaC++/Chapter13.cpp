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
		std::cout << ": Ź���밡 �ִ�.\n";
	}
	else
	{
		std::cout << ": Ź���밡 ����.\n";
	}
	player1.Name();
	if ( player1.HasTable() )
	{
		std::cout << ": Ź���밡 �ִ�.\n";
	}
	else
	{
		std::cout << ": Ź���밡 ����.\n";
	}
	std::cout << "�̸�: ";
	rplayer1.Name();
	std::cout << "; ��ŷ: " << rplayer1.Rating() << std::endl;

	RatedPlayer rplayer2( 1212, player1 );
	std::cout << "�̸�: ";
	rplayer2.Name();
	std::cout << "; ��ŷ: " << rplayer2.Rating() << std::endl;

	RatedPlayer::Show( rplayer1 );
	RatedPlayer::Show( player1 );
}


/*
* Circle2D, Rectangle2D, MyPoint Ŭ������ �߻� Ŭ���� ��� ������ �����Ͽ� �ٽ� �ۼ�
* BaseClass => GeometricObject
*/
void Chapter13::Question1()
{
}

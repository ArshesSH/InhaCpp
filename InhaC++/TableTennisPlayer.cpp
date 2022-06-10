#include "TableTennisPlayer.h"

#include <iostream>

TableTennisPlayer::TableTennisPlayer( const std::string& fn, const std::string& ln, bool ht )
	:
	firstName(fn),
	lastName(ln),
	hasTable(ht)
{
}

void TableTennisPlayer::Name() const
{
	std::cout << lastName << ", " << firstName;
}

void TableTennisPlayer::Show( const TableTennisPlayer& p )
{
	std::cout << "�̸�: ";
	p.Name();
	std::cout << "\nŹ����: ";
	if ( p.HasTable() )
	{
		std::cout << "�ִ�.\n";
	}
	else
	{
		std::cout << "����.\n";
	}
}

RatedPlayer::RatedPlayer( unsigned int rating, const std::string& fn, const std::string& ln, bool ht )
	:
	rating( rating ),
	TableTennisPlayer( fn, ln, ht )
{
}

RatedPlayer::RatedPlayer( unsigned int rating, const TableTennisPlayer& tp )
	:
	rating( rating ),
	TableTennisPlayer( tp )
{
}

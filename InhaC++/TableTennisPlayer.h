#pragma once

#include <string>

class TableTennisPlayer
{
public:
	TableTennisPlayer( const std::string& fn = "none", const std::string& ln = "none", bool ht = false );
	void Name() const;
	bool HasTable() const
	{
		return hasTable;
	}
	void ResetTable( bool v )
	{
		hasTable = v;
	}
	static void Show( const TableTennisPlayer& p );
private:
	std::string firstName;
	std::string lastName;
	bool hasTable;
};

class RatedPlayer : public TableTennisPlayer
{
public:
	RatedPlayer( unsigned int rating = 0, const std::string& fn = "none", const std::string& ln = "none", bool ht = false );
	RatedPlayer( unsigned int rating, const TableTennisPlayer& tp );
	unsigned int Rating() const
	{
		return rating;
	}
	void ResetRating( unsigned int r )
	{
		rating = r;
	}
private:
	unsigned int rating;
};
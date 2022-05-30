#pragma once

#include <vector>

// Always Start with NoData = -1, Final is Count of List
enum class ItemID
{
	NoData = -1,
	A,
	B,
	C,
	D,
	E,
	F,
	G,
	H,
	I,
	J,
	K,
	Count
};

class ItemTable
{
public:
	// Set ID and Acquisition probability of Item
	class ItemInfo
	{
	public:
		ItemInfo( ItemID id, int percentage );
		ItemID GetID() const;
		int GetPercentage() const;
	private:
		ItemID id;
		int percentage;
	};

public:
	ItemTable( const std::vector<ItemInfo>& itemInfos, int tableSize );
	ItemID GetItem( int pos );
	size_t GetSize() const;
	bool CheckItemIsNoData( int pos ) const;
private:
	std::vector<ItemID> itemDistributionList;
};
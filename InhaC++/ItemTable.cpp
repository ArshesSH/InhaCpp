#include "ItemTable.h"

ItemTable::ItemInfo::ItemInfo( ItemID id, int percentage )
	:
	id( id ),
	percentage( percentage )
{}

ItemID ItemTable::ItemInfo::GetID() const
{
	return id;
}

int ItemTable::ItemInfo::GetPercentage() const
{
	return percentage;
}

ItemTable::ItemTable( const std::vector<ItemInfo>& itemInfos, int tableSize = 10 )
{
	// Reserve itemDistributionList
	itemDistributionList.reserve( 100 );

	// Set itemDistributionList by percentage of itemList
	for (auto e : itemInfos)
	{
		for (int i = 0; i < e.GetPercentage(); i++)
		{
			itemDistributionList.push_back( e.GetID() );
		}
	}
}

ItemID ItemTable::GetItem( int pos )
{
	// Return id and set to NoData
	const ItemID id = itemDistributionList[pos];
	itemDistributionList[pos] = ItemID::NoData;
	return id;
}

size_t ItemTable::GetSize() const
{
	return itemDistributionList.size();
}

bool ItemTable::CheckItemIsNoData( int pos ) const
{
	return itemDistributionList[pos] == ItemID::NoData;
}
#include "ItemTable.h"

ItemTable::ItemInfo::ItemInfo( ItemID id, int percentage )
	:
	id( id ),
	percentage( percentage ),
	count( percentage )
{}

ItemID ItemTable::ItemInfo::GetID() const
{
	return id;
}

int ItemTable::ItemInfo::GetPercentage() const
{
	return percentage;
}

int ItemTable::ItemInfo::GetRemainCount() const
{
	return count;
}

void ItemTable::ItemInfo::ResetCount()
{
	count = percentage;
}

void ItemTable::ItemInfo::ReduceCount()
{
	--count;
}

bool ItemTable::ItemInfo::IsCountZero() const
{
	return count == 0;
}


ItemTable::ItemTable( const std::vector<ItemInfo>& itemInfos )
	:
	itemInfoList(itemInfos)
{
	for (const auto info : itemInfoList)
	{
		totalItemCount += info.GetPercentage();
	}
}

size_t ItemTable::GetSize() const
{
	return itemInfoList.size();
}

size_t ItemTable::GetTotalItemCount() const
{
	return totalItemCount;
}

bool ItemTable::IsItemCountZero( int pos ) const
{
	return itemInfoList[pos].IsCountZero();
}

bool ItemTable::IsItemTableEmpty() const
{
	for (const auto info : itemInfoList)
	{
		if (!info.IsCountZero())
		{
			return false;
		}
	}
	return true;
}

ItemID ItemTable::GetItem( int pos )
{
	// Return id and reduce conut
	const ItemID id = itemInfoList[pos].GetID();
	itemInfoList[pos].ReduceCount();
	return id;
}

void ItemTable::ResetItemTable()
{
	for (auto& info : itemInfoList)
	{
		info.ResetCount();
	}
}

#include "ItemResultTable.h"

void ItemResultTable::PushPos( size_t pos )
{
	count++;
	posList.push_back( pos );
}

size_t ItemResultTable::GetCount() const
{
	return count;
}

const std::vector<size_t>& ItemResultTable::GetPosList() const
{
	return posList;
}
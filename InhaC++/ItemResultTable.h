#pragma once

#include <vector>

class ItemResultTable
{
public:
	void PushPos( size_t pos );
	size_t GetCount() const;
	const std::vector<size_t>& GetPosList() const;
private:
	size_t count = 0;
	std::vector<size_t> posList;
};
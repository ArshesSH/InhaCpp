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
		int GetRemainCount() const;
		void ResetCount();
		void ReduceCount();
		bool IsCountZero() const;

	private:
		ItemID id;
		const int percentage;
		int count;
	};


public:
	ItemTable( const std::vector<ItemInfo>& itemInfos );

	size_t GetSize() const;
	size_t GetTotalItemCount() const;
	bool IsItemCountZero( int pos ) const;
	bool IsItemTableEmpty() const;
	ItemID GetItem( int pos );
	void ResetItemTable();

private:
	std::vector<ItemInfo> itemInfoList;
	size_t totalItemCount = 0;
};
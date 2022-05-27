#include "Chapter9.h"

#include <iostream>
#include "Rect.h"
#include "Circle.h"
#include <random>
#include <vector>
#include <string>

/*
* Q1.
* �� ���簢�� �߽��� x��ǥ y��ǥ ��, ��, ���� �Է¹޾� �ι�° ���簢���� ù��° ���簢�� ���ο� �ִ���
* ù��° ���簢���� ��ġ������ �����ϴ� ���α׷�
* ù��° �簢�� x,y,width,height > 2.5 4 2.5 43
* �ι��� �簢�� > 1.5 5 0.5 3
* �ι�°�� ù��° �簢�� ���ο� �ִ�.
*/
void Chapter9::Question1()
{

	std::cout << "�� ���簢���� ���� �� ��ħ ���� �Ǵ�\n";
	std::cout << "ù ��° �簢�� ������ ũ��x, y, width, height �Է� : ";
	
	Vec2<float> center;
	float width, height;

	// Create rect1
	std::cin >> center.x >> center.y >> width >> height;
	Rect<float> rect1 = Rect<float>::GetRectByCenter( center, width, height );

	// Create rect2
	std::cout << "�� ��° �簢�� ������ ũ��x, y, width, height �Է� : ";
	std::cin >> center.x >> center.y >> width >> height;
	Rect<float> rect2 = Rect<float>::GetRectByCenter( center, width, height );


	// Check Contains
	if ( rect2.IsContainedBy( rect1 ) )
	{	
		std::cout << "�� ��° �簢���� ù ��° �簢���ȿ� �ִ�.\n\n";
	}
	else if ( rect1.IsContainedBy( rect2 ) )
	{
		std::cout << "�� ��° �簢���� ù ��° �簢���� �����Ѵ�.\n\n";
	}
	// Check overlap
	else if ( rect2.IsOverlapWith( rect1 ) || rect2.IsContains( rect1.GetCenter() ) )
	{
		std::cout << "�� ��° �簢���� ù ��° �簢���� ���ƴ�\n\n";
	}
	else
	{
		std::cout << "�� ��° �簢���� ù ��° �簢���� ��ġ�� �ʴ´�\n\n";
	}
}

/*
* �� ���� ���� ���� �߽��� ��ǥ�� �������� �Է¹޾�
* �� ��° ���� ù ��° ���� ���ο� �ִ��� ��ġ������ �����϶�
* ù ���� �� x,y,r > 0.5 5.1 13
* �� ��° �� x,y,r > 1 1.7 4.5
* �� ��° ���� ù ��° �� ���ο� �ִ�
*/
void Chapter9::Question2()
{
	std::cout << "�� ���� �߽����� ���������� ���� ��ħ �� ���� �Ǵ�\n";
	std::cout << "ù ��° �� �Է� (x, y, r) : ";

	Vec2<float> center;
	float radius;
	// Create circle1
	std::cin >> center.x >> center.y >> radius;
	Circle<float> circle1( center, radius );

	std::cout << "�� ��° �� �Է� (x, y, r) : ";
	std::cin >> center.x >> center.y >> radius;
	Circle<float> circle2( center, radius );

	// Check contain
	if ( circle2.IsContainedBy( circle1 ) )
	{
		std::cout << "�� ��° ���� ù ��° ���ȿ� �ִ�.\n\n";
	}
	else if ( circle2.IsOverlapWidth( circle1 ) )
	{
		std::cout << "�� ��° ���� ù ��° ���� ��ģ��.\n\n";
	}
	else
	{
		std::cout << "�� ��° ���� ù ��° ���� ��ġ�� �ʴ´�.\n\n";
	}
}

const int n = 5;
void Chapter9::NewPlace()
{
	char buffer[BUFSIZ];
	double* pd1;
	double* pd2;
	std::cout << "new�� ��ġ���� new�� ù ��° ȣ��:\n";
	pd1 = new double[n];
	pd2 = new (buffer) double[n];

	for ( int i = 0; i < n; i++ )
	{
		pd2[i] = pd1[i] = 1000 + 20.0 * i;
	}
	std::cout << "�޸� �ּ�:\n" << pd1 << " : ��;	" << (void*)buffer << " : ����" << std::endl;
	std::cout << "�޸� ����:\n";
	for ( int i = 0; i < n; i++ )
	{
		std::cout << &pd1[i] << "�� " << pd1[i] << ";	";
		std::cout << &pd2[i] << "�� " << pd2[i] << std::endl;
	}

	std::cout << "\nnew�� ��ġ ���� new�� �� ��° ȣ��:\n";
	double* pd3, * pd4;
	pd3 = new double[n];
	pd4 = new (buffer) double[n];
	for ( int i = 0; i < n; i++ )
	{
		pd4[i] = pd3[i] = 1000 + 40.0 * i;
	}
	std::cout << "�޸� ����:\n";
	for ( int i = 0; i < n; i++ )
	{
		std::cout << &pd3[i] << "�� " << pd3[i] << ";	";
		std::cout << &pd4[i] << "�� " << pd4[i] << std::endl;
	}

	std::cout << "\nnew�� ��ġ ���� new�� �� ��° ȣ��:\n";
	delete[] pd1;
	pd1 = new double[n];
	pd2 = new (buffer + n * sizeof( double )) double[n];
	for ( int i = 0; i < n; i++ )
	{
		pd2[i] = pd1[i] = 1000 + 60.0 * i;
	}
	std::cout << "�޸� ����:\n";
	for ( int i = 0; i < n; i++ )
	{
		std::cout << &pd1[i] << "�� " << pd1[i] << ";	";
		std::cout << &pd2[i] << "�� " << pd2[i] << std::endl;
	}
	delete[] pd1;
	delete[] pd3;
}

/*
* Q3.
* ������ �鸸�� ������ �� �ùķ��̼�
* �ո�� �޸��� ���� ����ϴ� ���α׷�
* �� �ڰ� ��% �������� ����ؼ� ���
* 100��° => �ո� ~% �޸� ~%
* 1000��° => �ո� ~% �޸� ~%
* 10000��° => �ո� ~% �޸� ~%
* ...
* 1000000��° => �ո� ~% �޸� ~%
*/

void Chapter9::Question3()
{
	std::cout << "���� �鸸�� Ȯ�� �׽�Ʈ\n";

	std::random_device rd;
	std::mt19937 rng( rd() );
	std::uniform_int_distribution<int> coin( 0, 1 );

	int frontCnt = 0;
	int backCnt = 0;

	int outNum = 100;
	for ( size_t cnt = 0; cnt < 1000000; cnt++ )
	{
		const int coinResult = coin( rng );
		switch ( coinResult )
		{
		case 0:
			frontCnt++;
			break;
		case 1:
			backCnt++;
			break;
		default:
			break;
		}
		
		if ( cnt == outNum )
		{
			std::cout << cnt << "��° ��� : �ո� " << (frontCnt / (float)cnt) << "% �޸� " << (backCnt / (float)cnt)
				<< "%" << std::endl;
			outNum *= 10;
		}
	}
}

/*
* Q4.
* ������ ����� ������ ���� ��
* 
* ���		������		Ȯ��		������	Ȯ��
* -------------------------------------------
* 5star		A-Item		1%
* -------------------------------------------
* 4star		B-Item		3%		C-Item	3%
* -------------------------------------------
* 3star		D-Item		5%		E-Item	5%
*			F-Item		5%
* -------------------------------------------
* 2star		G-Item		10%		H-Item	10%
*			I-Item		10%		J-Item	10%
* -------------------------------------------
* 1star		K-Item		38%
* -------------------------------------------
* 
* �� �������� ������ Ȯ���� �°� ��Ȯ�� �������� ���α׷���
* 
* ex> Ƚ��? 100
* ��� > A:1, B:3, c:3, D:5
* Ƚ�� 1000
* >A:10, B:30, C:30, D:50
*/

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

struct ItemInform
{
	ItemInform( ItemID id, int percentage )
		:
		id(id),
		percentage(percentage)
	{}

	ItemID id;
	int percentage;
};

class ItemTable
{
public:
	ItemTable( const std::vector<ItemInform>& itemList, int tableSize )
		:
		tableSize(tableSize)
	{
		// Reserve itemDistributionList
		itemDistributionList.reserve( tableSize );

		// Set itemDistributionList by percentage of itemList
		for ( auto e : itemList )
		{
			for ( int i = 0; i < e.percentage; i++ )
			{
				itemDistributionList.push_back( e.id );
			}
		}
	}

	ItemID GetItem(int pos)
	{
		const ItemID id = itemDistributionList[pos];
		itemDistributionList[pos] = ItemID::NoData;
		return id;
	}

	ItemID GetRandomItem( int randNum )
	{
		ItemID id = ItemID::NoData;
		while ( itemDistributionList[randNum] != ItemID::NoData )
		{
			id = GetItem( randNum );
		}
		return id;
	}

private:
	std::vector<ItemID> itemDistributionList;
	int tableSize = 0;
};

void Chapter9::Question4()
{
	// Create ItemList
	const std::vector<ItemInform> itemList = { ItemInform( ItemID::A, 1 ), ItemInform( ItemID::B, 3 ), ItemInform( ItemID::C, 3 ),
		ItemInform( ItemID::D, 5 ),ItemInform( ItemID::E, 5 ),ItemInform( ItemID::F, 5 ),ItemInform( ItemID::G, 10 ),
		ItemInform( ItemID::H, 10 ),ItemInform( ItemID::I, 10 ),ItemInform( ItemID::J, 10 ),ItemInform( ItemID::K, 38 )
	};

	const int itemCnt = 100;

	// Create ItemTable
	const ItemTable originItemTable( itemList, itemCnt );
	ItemTable itemTable( itemList, itemCnt );

	// Print Main script
	std::cout << "������ Ȯ�� �̱�\n";
	std::cout << "Ƚ�� �Է�(100�̻�): ";
	int cnt;
	std::cin >> cnt;

	std::random_device rd;
	std::mt19937 rng( rd() );
	std::uniform_int_distribution<int> itemRand( 0, itemCnt );

	std::vector<ItemID> acquisitionList;
	acquisitionList.reserve( itemCnt );

	// for loop as cnt
	for ( int i = 1; i <= cnt; i++ )
	{
		int randNum = itemRand( rng );
		
		const ItemID curId = itemTable.GetRandomItem( randNum );
		std::cout << i << "��° ȹ�� �� : " << (int)curId << std::endl;

		// Reset Table
		if ( i % 100 == 0 )
		{
			itemTable = originItemTable;
		}
	}

}

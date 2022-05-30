#include "Chapter9.h"

#include <iostream>
#include "Rect.h"
#include "Circle.h"
#include <random>
#include <vector>
#include <string>
#include "ItemTable.h"
#include "ItemResultTable.h"

/*
* Q1.
* 두 직사각형 중심점 x좌표 y좌표 값, 폭, 높이 입력받아 두번째 직사각형이 첫번째 직사각형 내부에 있는지
* 첫번째 직사각형과 겹치는지를 결정하는 프로그램
* 첫번째 사각형 x,y,width,height > 2.5 4 2.5 43
* 두번쨰 사각형 > 1.5 5 0.5 3
* 두번째는 첫번째 사각형 내부에 있다.
*/
void Chapter9::Question1()
{

	std::cout << "두 직사각형의 포함 및 겹침 여부 판단\n";
	std::cout << "첫 번째 사각형 중점과 크기x, y, width, height 입력 : ";
	
	Vec2<float> center;
	float width, height;

	// Create rect1
	std::cin >> center.x >> center.y >> width >> height;
	Rect<float> rect1 = Rect<float>::GetRectByCenter( center, width, height );

	// Create rect2
	std::cout << "두 번째 사각형 중점과 크기x, y, width, height 입력 : ";
	std::cin >> center.x >> center.y >> width >> height;
	Rect<float> rect2 = Rect<float>::GetRectByCenter( center, width, height );


	// Check Contains
	if ( rect2.IsContainedBy( rect1 ) )
	{	
		std::cout << "두 번째 사각형은 첫 번째 사각형안에 있다.\n\n";
	}
	else if ( rect1.IsContainedBy( rect2 ) )
	{
		std::cout << "두 번째 사각형은 첫 번째 사각형을 포함한다.\n\n";
	}
	// Check overlap
	else if ( rect2.IsOverlapWith( rect1 ) || rect2.IsContains( rect1.GetCenter() ) )
	{
		std::cout << "두 번째 사각형은 첫 번째 사각형과 겹쳤다\n\n";
	}
	else
	{
		std::cout << "두 번째 사각형은 첫 번째 사각형과 겹치지 않는다\n\n";
	}
}

/*
* 두 개의 원에 대해 중심점 좌표와 반지름을 입력받아
* 두 번째 원이 첫 번째 원의 내부에 있는지 겹치는지를 결정하라
* 첫 번재 원 x,y,r > 0.5 5.1 13
* 두 번째 원 x,y,r > 1 1.7 4.5
* 두 번째 원은 첫 번째 원 내부에 있다
*/
void Chapter9::Question2()
{
	std::cout << "두 원의 중심점관 반지름으로 원의 겹침 및 내부 판단\n";
	std::cout << "첫 번째 원 입력 (x, y, r) : ";

	Vec2<float> center;
	float radius;
	// Create circle1
	std::cin >> center.x >> center.y >> radius;
	Circle<float> circle1( center, radius );

	std::cout << "두 번째 원 입력 (x, y, r) : ";
	std::cin >> center.x >> center.y >> radius;
	Circle<float> circle2( center, radius );

	// Check contain
	if ( circle2.IsContainedBy( circle1 ) )
	{
		std::cout << "두 번째 원은 첫 번째 원안에 있다.\n\n";
	}
	else if ( circle2.IsOverlapWidth( circle1 ) )
	{
		std::cout << "두 번째 원은 첫 번째 원과 겹친다.\n\n";
	}
	else
	{
		std::cout << "두 번째 원은 첫 번째 원과 겹치지 않는다.\n\n";
	}
}

const int n = 5;
void Chapter9::NewPlace()
{
	char buffer[BUFSIZ];
	double* pd1;
	double* pd2;
	std::cout << "new와 위치지정 new의 첫 번째 호출:\n";
	pd1 = new double[n];
	pd2 = new (buffer) double[n];

	for ( int i = 0; i < n; i++ )
	{
		pd2[i] = pd1[i] = 1000 + 20.0 * i;
	}
	std::cout << "메모리 주소:\n" << pd1 << " : 힙;	" << (void*)buffer << " : 정적" << std::endl;
	std::cout << "메모리 내용:\n";
	for ( int i = 0; i < n; i++ )
	{
		std::cout << &pd1[i] << "에 " << pd1[i] << ";	";
		std::cout << &pd2[i] << "에 " << pd2[i] << std::endl;
	}

	std::cout << "\nnew와 위치 지정 new의 두 번째 호출:\n";
	double* pd3, * pd4;
	pd3 = new double[n];
	pd4 = new (buffer) double[n];
	for ( int i = 0; i < n; i++ )
	{
		pd4[i] = pd3[i] = 1000 + 40.0 * i;
	}
	std::cout << "메모리 내용:\n";
	for ( int i = 0; i < n; i++ )
	{
		std::cout << &pd3[i] << "에 " << pd3[i] << ";	";
		std::cout << &pd4[i] << "에 " << pd4[i] << std::endl;
	}

	std::cout << "\nnew와 위치 지정 new의 세 번째 호출:\n";
	delete[] pd1;
	pd1 = new double[n];
	pd2 = new (buffer + n * sizeof( double )) double[n];
	for ( int i = 0; i < n; i++ )
	{
		pd2[i] = pd1[i] = 1000 + 60.0 * i;
	}
	std::cout << "메모리 내용:\n";
	for ( int i = 0; i < n; i++ )
	{
		std::cout << &pd1[i] << "에 " << pd1[i] << ";	";
		std::cout << &pd2[i] << "에 " << pd2[i] << std::endl;
	}
	delete[] pd1;
	delete[] pd3;
}

/*
* Q3.
* 동전을 백만번 던지는 것 시뮬레이션
* 앞면과 뒷면의 수를 출력하는 프로그램
* 앞 뒤가 몇% 나오는지 계산해서 출력
* 100번째 => 앞면 ~% 뒷면 ~%
* 1000번째 => 앞면 ~% 뒷면 ~%
* 10000번째 => 앞면 ~% 뒷면 ~%
* ...
* 1000000번째 => 앞면 ~% 뒷면 ~%
*/

void Chapter9::Question3()
{
	std::cout << "동전 백만번 확률 테스트\n";

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
			std::cout << cnt << "번째 결과 : 앞면 " << (frontCnt / (float)cnt) << "% 뒷면 " << (backCnt / (float)cnt)
				<< "%" << std::endl;
			outNum *= 10;
		}
	}
}

/*
* Q4.
* 아이템 목록이 다음과 같을 때
* 
* 등급		아이템		확률		아이템	확률
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
* 각 아이템이 지정된 확률에 맞게 정확히 나오도록 프로그래밍
* 
* ex> 횟수? 100
* 결과 > A:1, B:3, c:3, D:5
* 횟수 1000
* >A:10, B:30, C:30, D:50
*/

void Chapter9::Question4()
{
	// Create ItemList
	const std::vector<ItemTable::ItemInfo> itemInfos = { ItemTable::ItemInfo( ItemID::A, 1 ), ItemTable::ItemInfo( ItemID::B, 3 ), ItemTable::ItemInfo( ItemID::C, 3 ),
		ItemTable::ItemInfo( ItemID::D, 5 ),ItemTable::ItemInfo( ItemID::E, 5 ),ItemTable::ItemInfo( ItemID::F, 5 ),ItemTable::ItemInfo( ItemID::G, 10 ),
		ItemTable::ItemInfo( ItemID::H, 10 ),ItemTable::ItemInfo( ItemID::I, 10 ),ItemTable::ItemInfo( ItemID::J, 10 ),ItemTable::ItemInfo( ItemID::K, 38 )
	};

	// Create ItemTable
	ItemTable itemTable( itemInfos );

	// Set MaxCnt
	std::cout << "아이템 확률 뽑기\n";
	std::cout << "횟수 입력(100이상): ";
	int maxCnt;
	std::cin >> maxCnt;

	// Create Random Engine
	std::random_device rd;
	std::mt19937 rng( rd() );
	std::vector<unsigned int> itemProbabilities;
	itemProbabilities.reserve( (int)ItemID::Count );
	for (const auto e : itemInfos)
	{
		itemProbabilities.push_back( e.GetPercentage() );
	}
	std::discrete_distribution<unsigned int> itemDist( itemProbabilities.cbegin(), itemProbabilities.cend() );

	/*
	* Create ResultTable List
	* ResultTable has count of ItemID::Somthing and it's position
	*/ 
	std::vector<ItemResultTable> resultList( (int)ItemID::Count );

	// for loop as tryCnt to Gacha
	for ( int tryCnt = 1; tryCnt <= maxCnt; )
	{
		// Get Random Number
		int randPos = itemDist( rng );

		// If No Data at random	pos, continue and get new random value
		if (itemTable.IsItemCountZero( randPos ))
		{
			continue;
		}

		// Get Data from randomNum
		const ItemID curId = itemTable.GetItem( randPos );
		resultList[(int)curId].PushPos( tryCnt );

		// Log data
		std::cout << tryCnt << "번째 획득 값 : " << (int)curId << std::endl;

		// Reset ItemTable
		if (tryCnt % itemTable.GetTotalItemCount() == 0)
		{
			itemTable.ResetItemTable();
		}

		tryCnt++;
	}

	std::cout << std::endl;

	// Print result of each Item
	for (int i = 0; i < (int)ItemID::Count; i++)
	{
		std::cout << char( i + 'A' ) << "-Item\n획득 개수: " << resultList[i].GetCount() << "\n획득 위치: \n";
		for (auto e : resultList[i].GetPosList())
		{
			std::cout << e << " ";
		}
		std::cout <<"\n" << std::endl;
	}
}

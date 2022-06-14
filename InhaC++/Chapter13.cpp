#include "Chapter13.h"

#include <iostream>
#include "TableTennisPlayer.h"

#include <memory>
#include <vector>
#include "GeometricObject.h"
#include "StopWatch.h"
#include "Worker.h"

#include <Windows.h>
#include <bitset>

void Chapter13::ExInheritance()
{
	TableTennisPlayer player1( "Tara", "Boomdea", false );
	RatedPlayer rplayer1( 1140, "Mallory", "Duck", true );
	rplayer1.Name();
	if ( rplayer1.HasTable() )
	{
		std::cout << ": 탁구대가 있다.\n";
	}
	else
	{
		std::cout << ": 탁구대가 없다.\n";
	}
	player1.Name();
	if ( player1.HasTable() )
	{
		std::cout << ": 탁구대가 있다.\n";
	}
	else
	{
		std::cout << ": 탁구대가 없다.\n";
	}
	std::cout << "이름: ";
	rplayer1.Name();
	std::cout << "; 랭킹: " << rplayer1.Rating() << std::endl;

	RatedPlayer rplayer2( 1212, player1 );
	std::cout << "이름: ";
	rplayer2.Name();
	std::cout << "; 랭킹: " << rplayer2.Rating() << std::endl;

	RatedPlayer::Show( rplayer1 );
	RatedPlayer::Show( player1 );
}


/*
* Circle2D, Rectangle2D, MyPoint 클래스를 추상 클래스 상속 개념을 적용하여 다시 작성
* BaseClass => GeometricObject
*/
void Chapter13::Question1()
{
	std::vector<std::unique_ptr<GeometricObject<double>>> geoObjects;
	geoObjects.push_back( std::make_unique<Circle<double>>( 2, 2, 5.5 ) );
	geoObjects.push_back( std::make_unique<Circle<double>>( 3, 2, 10.5 ) );
	geoObjects.push_back( std::make_unique<Rect<double>>( 2, 2, 5.5, 4.9 ) );
	geoObjects.push_back( std::make_unique<Rect<double>>( 4, 5, 10.5, 3.2 ) );
	geoObjects.push_back( std::make_unique<Point<double>>( 0, 0 ) );
	geoObjects.push_back( std::make_unique<Point<double>>( 10, 30.5 ) );

	std::cout << "c1( 2, 2, 5.5 ), c2( 3, 2, 10.5 )" << std::endl;

	std::cout << "c1의 면적: " << geoObjects[0]->GetArea() << "\nc1의 둘레: " << geoObjects[0]->GetPerimeter() << std::endl;
	std::cout << "c1.contains( 3, 3 ) : " << std::boolalpha << geoObjects[0]->IsContains( 3, 3 ) << std::endl;
	std::cout << "c1.contains( c2 ) : " << std::boolalpha << geoObjects[0]->IsContains( *geoObjects[1] ) << std::endl;
	std::cout << "c1.overlaps( c2 ) : " << std::boolalpha << geoObjects[0]->IsOverlapWith( *geoObjects[1] ) << std::endl;
	std::cout << "c1.IsContainedBy( c2 ) : " << std::boolalpha << geoObjects[0]->IsContainedBy( *geoObjects[1] ) << std::endl;

	std::cout << "r1(2, 2, 5.5, 4.9), r2(4, 5, 10.5, 3.2)" << std::endl;
	std::cout << "r1.GetArea() = " << geoObjects[2]->GetArea() << std::endl;
	std::cout << "r1.GetPerimeter() = " << geoObjects[2]->GetPerimeter() << std::endl;
	std::cout << "r1.IsContains( 3, 3 ) = " << std::boolalpha << geoObjects[2]->IsContains( 3, 3 ) << std::endl;
	std::cout << "r1.IsContains( r2 ) = " << std::boolalpha << geoObjects[2]->IsContains( *geoObjects[3] ) << std::endl;
	std::cout << "r1.IsOverlapWith( r2 ) = " << std::boolalpha << geoObjects[2]->IsOverlapWith( *geoObjects[3] ) << std::endl;

	std::cout << "p1: (0, 0), p2: (10, 30.5)\n";
	std::cout << "Distance = " << geoObjects[4]->GetDistanceWith( *geoObjects[5] ) << std::endl;
	std::cout << "IsContains( rect1, p1 )= " << std::boolalpha << Point<double>::IsContains( *geoObjects[2], *geoObjects[4] ) << std::endl;
	std::cout << "IsContains( c1, p1 )= " << std::boolalpha << Point<double>::IsContains( *geoObjects[0], *geoObjects[4] ) << std::endl;
}


enum class Tower
{
	A,
	B,
	C,
	Count
};


int TowerNumFix( int n )
{
	if ( n < 0 )
	{
		return TowerNumFix( (int)Tower::Count + n );
	}
	else if ( n >= (int)Tower::Count )
	{
		return TowerNumFix( n - (int)Tower::Count );
	}
	else
	{
		return n;
	}
}

int	GetMoveDir( int ringCnt )
{
	// move right when even
	if ( ringCnt % 2 == 0 )
	{
		return 1;
	}
	else
	{
		return -1;
	}
}

bool MoveRing( std::vector<int>& curTower, std::vector<int>& nextTower )
{
	// If curTower is empty skip
	if ( curTower.empty() )
	{
		return false;
	}

	const int curTowerTop = curTower[curTower.size() - 1];

	//Move if Next Tower is Empty or curTop < nextTop
	if ( nextTower.empty() )
	{
		curTower.pop_back();
		nextTower.push_back( curTowerTop );
		return true;
	}
	else if ( curTowerTop < nextTower[nextTower.size() - 1] )
	{
		curTower.pop_back();
		nextTower.push_back( curTowerTop );
		return true;
	}
	else
	{
		return false;
	}
}

void PrintTower( const std::vector<std::vector<int>>& towers, int ringCnt )
{
	printf( " A   B   C\n" );

	for ( int j = ringCnt - 1; j >= 0; --j )
	{
		for ( int i = 0; i < towers.size(); ++i )
		{
			const int towerTopPos = (int)towers[i].size() - 1;
			if ( j > towerTopPos )
			{
				printf( "[ ] " );
			}
			else
			{
				printf( "[%d] ", towers[i][j] );
			}
		}
		printf( "\n" );
	}

	printf( "\n" );
}

void ExTowerOfHanoi()
{
	int ringCntMax = 3;

	constexpr int towerCnt = (int)Tower::Count;
	std::vector<std::vector<int>> towers( towerCnt );

	// Init Tower
	for ( int i = ringCntMax; i > 0; --i )
	{
		towers[(int)Tower::A].push_back( i );
	}
	PrintTower( towers, ringCntMax );

	int moveDir = GetMoveDir( ringCntMax );
	int moveCount;
	int curTowerPos = 0;
	int nextTowerPos = 0;

	// Get Result
	for ( moveCount = 0; towers[towerCnt - 1].size() < ringCntMax; )
	{
		bool isMoved = false;

		// Try Move at CurTower
		for ( int i = 1; (i <= towerCnt - 1) && !isMoved; ++i )
		{
			nextTowerPos = TowerNumFix( curTowerPos + (moveDir * i) );
			isMoved = MoveRing( towers[curTowerPos], towers[nextTowerPos] );
		}

		// Change Tower
		if ( isMoved )
		{
			++moveCount;
			curTowerPos = TowerNumFix( nextTowerPos + moveDir );
			PrintTower( towers, ringCntMax );
		}
		else
		{
			curTowerPos = TowerNumFix( curTowerPos + moveDir );
		}
	}
	std::cout << "움직인 횟수 : " << moveCount << std::endl;
}

/*
* 다음 내용을 포함하는 StopWatch 클래스 설계
* get함수를 갖는 전용 데이터필드 startTime, endTime
* startTime을 현재 시간으로 초기화하는 인수 없는 생성자
* startTime을 현재 시간으로 재설정하는 start()함수
* endTime을 현재시간으로 설정하는 stop()함수
* stopwatch의 경과시간을 밀리초 단위로 반환하는 getElapsedTime()함수
* 클래스에 대한 UML다이어그램을 그리고 클래스 구현
* 앞서만든 확률아이템 또는 하노이 타워 문제 해결에 걸리는 시간 측정
*/
void Chapter13::Question2()
{
	StopWatch timer;
	ExTowerOfHanoi();
	timer.Stop();

	std::cout << "\n걸린 시간 : " << timer.GetElapsedTime<double, (int)StopWatch::TimeUnit::Milli>() << "ms" << std::endl;
}

const int LIM = 4;
void Chapter13::TestWorker()
{
	Waiter bob( "홍길동", 314L, 5 );
	Singer bev( "조수미", 522L, 3 );
	Waiter w_temp;
	Singer s_temp;

	Worker* pw[LIM] = { &bob, &bev, &w_temp, &s_temp };

	for ( int i = 2; i < LIM; i++ )
	{
		pw[i]->Set();
	}
	for ( int i = 0; i < LIM; i++ )
	{
		pw[i]->Show();
		std::cout << std::endl;
	}
}

const int Size = 5;
void Chapter13::TestWorkerVirtual()
{
	using std::cin;
	using std::cout;
	using std::endl;
	using std::strchr;

	Worker* lolas[Size];
	int ct;
	for ( ct = 0; ct < Size; ct++ )
	{
		char choice;
		cout << "직종을 입력하십시오:\n"
			<< "w:웨이터 s:가수 t:가수 겸 웨이터 q:종료\n";
		cin >> choice;
		while ( strchr( "wstq", choice ) == NULL )
		{
			cout << "w, s, t, q 중에서 하나를 선택하십시오: ";
			cin >> choice;
		}
		if ( choice == 'q' )
		{
			break;
		}
		switch ( choice )
		{
		case 'w':
			lolas[ct] = new Waiter;
			break;
		case 's':
			lolas[ct] = new Singer;
			break;
		case 't':
			lolas[ct] = new SingingWaiter;
			break;
		}
		cin.get();
		lolas[ct]->Set();
	}

	cout << "\n 사원 현황은 다음과 같습니다.\n";
	for ( int i = 0; i < ct; i++ )
	{
		cout << endl;
		lolas[i]->Show();
	}
	for ( int i = 0; i < ct; i++ )
	{
		delete lolas[i];
	}
	cout << "프로그램 종료\n";
}

/*
* 8 x 8 상하좌우대각선 퀸 이동
* 8개의 퀸이 서로 충돌하지 않고 위치할 수 있는 경우의 수를 만들고,
* 해당 조합을 □와 ■를 이용해서 퀸의 배치 상황을 출력
* 퀸 있음: ■, 없음: □
* ■ □ □ □ □ □ □ □
* □ □ □ □ □ □ □ □
* □ □ □ □ □ □ □ □
* □ □ □ ■ □ □ □ □
* □ □ □ □ □ □ □ □
* □ □ □ □ □ □ □ □
* □ □ □ □ □ □ □ □
* □ □ □ □ □ □ □ □
*/

void PrintVistiedMap( const std::bitset<64>& visitedMap, const Vec2<int>& queenPos, int boardSize = 8 )
{
	system( "cls" );
	for ( int y = 0; y < boardSize; ++y )
	{
		for ( int x = 0; x < boardSize; ++x )
		{
			const int curPos = y * boardSize + x;
			if ( Vec2<int>{x,y} == queenPos )
			{
				std::cout << "★ ";
			}
			else if ( visitedMap[curPos])
			{
				std::cout << "● ";
			}
			else
			{
				std::cout << "○ ";
			}
		}
		std::cout << "\n" << std::endl;
	}
	std::cout << "\n" << std::endl;
}

void SetMapTrueByDir( std::bitset<64>& visitedMap, const Vec2<int>& curPos, const Vec2<int>& dir, int boardSize = 8 )
{
	// Check cur pos to true
	const int curMapPos = curPos.y * boardSize + curPos.x;
	visitedMap[curMapPos] = true;

	const Vec2<int> nextPos = curPos + dir;
	const int nextMapPos = nextPos.y * boardSize + nextPos.x;

	if ( nextPos.x >= boardSize || nextPos.x < 0 || nextPos.y < 0 || nextPos.y >= boardSize )
	{
		return;
	}
	SetMapTrueByDir( visitedMap, nextPos, dir, boardSize );
}

int SetMapTrueByQueenPos( std::bitset<64>& visitedMap, const Vec2<int>& queenPos, int boardSize = 8 )
{
	const Vec2<int> up = { 0, -1 };
	const Vec2<int> down = { 0, 1 };
	const Vec2<int> left = { -1, 0 };
	const Vec2<int> right = { 1, 0 };

	int count = 0;

	// Set Dir
	SetMapTrueByDir( visitedMap, queenPos, up, boardSize );
	SetMapTrueByDir( visitedMap, queenPos, down, boardSize );
	SetMapTrueByDir( visitedMap,  queenPos, left, boardSize );
	SetMapTrueByDir( visitedMap, queenPos, right, boardSize );
	SetMapTrueByDir( visitedMap, queenPos, up + left, boardSize );
	SetMapTrueByDir( visitedMap, queenPos, up + right, boardSize );
	SetMapTrueByDir( visitedMap, queenPos, down + left, boardSize );
	SetMapTrueByDir( visitedMap, queenPos, down + right, boardSize );


	//std::cout << "Move DownRight\n";
	//PrintVistiedMap( visitedMap, queenPos );
}

std::vector<Vec2<int>> PutEightQueens(std::bitset<64>&visitedMap, int startX, int startY, int queenCnt, int boardSize = 8)
{
	std::vector<Vec2<int>> queens;
	queens.emplace_back( startX, startY );
	SetMapTrueByQueenPos( visitedMap, queens[queens.size() - 1] );

	int nextPos = 0;
	for ( nextPos = 0; nextPos < visitedMap.size(); ++nextPos )
	{
		if ( visitedMap[nextPos] == false )
		{
			 break;
		}
	}

	if ( queenCnt == 8 )
	{
		return queens;
	}
	else
	{
		queens = PutEightQueens( visitedMap, nextPos % boardSize, nextPos / boardSize, boardSize );
	}
}

void PrintQueens( const std::vector<Vec2<int>> queens, int boardSize = 8)
{
	int curQueenCnt = 0;
	for ( int y = 0; y < boardSize; ++y )
	{
		for ( int x = 0; x < boardSize; ++x )
		{
			const Vec2<int> curPos( x, y );

			bool isInList = false;

			for ( const auto e : queens )
			{
				if ( e == curPos )
				{
					isInList = true;
					break;
				}
			}

			if ( isInList )
			{
				std::cout << "■ ";
				curQueenCnt++;
			}
			else
			{
				std::cout << "□ ";
			}
		}
		std::cout << "\n" << std::endl;
	}
}

void Chapter13::Question3()
{
	constexpr static int boardSize = 8;
	
	std::vector<std::vector<Vec2<int>>> eightQueensList;

	std::bitset<64> visitedMap = false;

	for ( int y = 0; y < boardSize; ++y )
	{
		for ( int x = 0; x < boardSize; ++x )
		{
			visitedMap.reset();
			std::vector<Vec2<int>> queens = PutEightQueens( visitedMap, x, y );
			if ( queens.size() == 8 )
			{
				eightQueensList.push_back( queens );
			}
		}
	}

	for ( const auto e : eightQueensList )
	{
		PrintQueens( e );
	}
}




/*
* N명의 이용자를 가진 소셜 네트워크 서비스
* 이용자는 1번부터 n번 번호 
붙어있음
* 각 이용자의 친구 수 분석
* 이용자 A가 B의 친구라면 B도 A의 친구
* 친구의 친구도 친구, A와 B가 친구이고 B와 C가 친구이면 A와 C도 친구
* 
* 소셜 네트워크 전체이용자 수 N,
* 각 이용자의 친구관계를 담고 있는 배열 relation이 매개변수로 주어질 때
* 각 이용자의 친구 수를 1번 이용자 순서대로 담은 배열을 return하도록 함수 작성
* 
* 제한사항
* N은 2이상 100이하 자연수
* relation의 각 원소는 친구관계를 나타내며, relation의 길이는 1이상 N(N-1)/2이하
* 각 친구 관계는 길이가 2인 배열이며, 순서대로 (a,b)로 나타냄. a,b (1<=a, b<=n, a!=b) 는 친구관계인 두 이용자의 번호
* a와 b가 같은 경우는 없으며, 친구 관계는 한 번씩만 주어진다.
* 제한시간:100000ms
*/



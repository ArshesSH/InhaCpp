#include "Chapter13.h"

#include <iostream>
#include "TableTennisPlayer.h"

#include <memory>
#include <vector>
#include <random>
#include "GeometricObject.h"
#include "StopWatch.h"
#include "Worker.h"

#include <bitset>
#include <fstream>
#include <algorithm>
#include <sstream>
#include "InputReader.h"

#define NOMINMAX

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

class QueenMap
{
private:
	class Tile
	{
	public:
		enum class State
		{
			Empty,
			Visited,
			HasQueen
		};
	public:
		Tile() {};
		void SetEmpty()
		{
			state = State::Empty;
		}
		void SetVisited()
		{
			state = State::Visited;
		}
		void SetHasQueen()
		{
			state = State::HasQueen;
		}
		State GetState() const
		{
			return state;
		}
		bool IsEmpty() const
		{
			return state == State::Empty;
		}
		bool IsVisited() const
		{
			return state == State::Visited;
		}
		bool IsHasQueen() const
		{
			return state == State::HasQueen;
		}
	private:
		State state = State::Empty;
	};

public:
	QueenMap( int size )
		:
		width( size ),
		fieldSize( size* size )
	{
		field.reserve( fieldSize );
		field.assign( width * width, Tile() );
	} 
	bool CheckFieldSize(const Vec2<int>& pos) const
	{
		return (pos.x >= 0 && pos.x < width) && (pos.y >= 0 && pos.y < width);
	}
	int FindNextEmpty()
	{
		for ( int i = 0; i < width * width; ++i )
		{
			if ( field[i].IsEmpty())
			{
				return i;
			}
		}
		return -1;
	}
	void SetVisitedLineByDir(const Vec2<int>& lastPos, const Vec2<int>& dir)
	{
		const Vec2<int>& curPos = lastPos + dir;
		if ( CheckFieldSize( curPos ) )
		{
			const int curTilePos = curPos.y * width + curPos.x;
			if ( field[curTilePos].IsEmpty() || field[curTilePos].IsVisited() )
			{
				field[curTilePos].SetVisited();
				SetVisitedLineByDir( curPos, dir );
			}
		}
	}
	void SetMapVisitedFrom( const Vec2<int>& pos )
	{
		SetVisitedLineByDir( pos, Up );
		SetVisitedLineByDir( pos, Down );
		SetVisitedLineByDir( pos, Right );
		SetVisitedLineByDir( pos, Left );
		SetVisitedLineByDir( pos, Up + Right );
		SetVisitedLineByDir( pos, Up + Left );
		SetVisitedLineByDir( pos, Down + Right );
		SetVisitedLineByDir( pos, Down + Left );
	}
	void SetQueen( const Vec2<int>& curPos )
	{
		const int curTilePos = curPos.y * width + curPos.x;
		
		field[curTilePos].SetHasQueen();
		queenCount++;
		SetMapVisitedFrom( curPos );
		PrintField();
		auto savedField = field;
		for (int i = 0; i < fieldSize; ++i )
		{
			if ( savedField[i].IsEmpty() )
			{
				const Vec2<int> nextPos = { i % width, i / width };
				SetQueen( nextPos );
				field = savedField;
				queenCount--;
			}
		}
	}
	void PrintField() const
	{
		for ( int y = 0; y < width; ++y )
		{
			for ( int x = 0; x < width; ++x )
			{
				const int pos = y * width + x;
				if ( field[pos].IsEmpty() )
				{
					std::cout << "○";
				}
				else if ( field[pos].IsHasQueen())
				{
					std::cout << "★";
				}
				else
				{
					std::cout << "◎";
				}
			}
			std::cout << std::endl;
		}
		std::cout << queenCount <<"개" << std::endl;
	}
	void PrintField(const std::vector<Tile>& target) const
	{
		for ( int y = 0; y < width; ++y )
		{
			for ( int x = 0; x < width; ++x )
			{
				const int pos = y * width + x;
				if ( target[pos].IsEmpty() )
				{
					std::cout << "○";
				}
				else if ( target[pos].IsHasQueen() )
				{
					std::cout << "★";
				}
				else
				{
					std::cout << "◎";
				}
			}
			std::cout << std::endl;
		}
		std::cout << queenCount << "개" << std::endl;
	}
	void PrintQueens() const
	{
		for ( int y = 0; y < width; ++y )
		{
			for ( int x = 0; x < width; ++x )
			{
				const int pos = y * width + x;
				if ( field[pos].IsHasQueen() )
				{
					std::cout << "■";
				}
				else
				{
					std::cout << "□";
				}
			}
			std::cout << std::endl;
		}
		std::cout << std::endl;
	}
	std::vector<Tile> GetField() const
	{
		return field;
	}
private:
	const Vec2<int> Up { 0, -1 };
	const Vec2<int> Down{ 0, 1 };
	const Vec2<int> Right{ 1,0 };
	const Vec2<int> Left{ -1,0 };
	const int width;
	const int fieldSize = width * width;
	std::vector<Tile> field;
	int queenCount = 0;
};

void Chapter13::Question3()
{
	std::vector<QueenMap> eightQueenList;

	constexpr int fieldSize = 8;
	for ( int y = 0; y < fieldSize; ++y )
	{
		for ( int x = 0; x < fieldSize; ++x )
		{
			QueenMap queenField( fieldSize );
			queenField.SetQueen( { x,y } );
		}
	}

}

/*
서울시에 일직선 모양의 새로운 도로가 생겼다.새로운 도로의 전체 길이는 l 이고 도로에는 총 n 개의 가로등이 세워졌다.
이 도로의 모든 가로등에 전구를 사서 달려고 한다.전구를 선택하는 기준은 다음과 같다.
1. 전구는 길의 좌측, 우측 방향으로 각각 d길이 만큼 길을 밝힐 수 있다.d 는 자연수
2. 모든 가로등에는 같은 종류( d값이 같은 )의 전구를 달아야 한다.
3. 안전을 위하여 도로위에 어두운 부분이 있어서는 안된다.

이때, d값이 충분히 크다면 전체 도로를 밝게 비출 수 있지만, d값이 작아진다면 도로 위에 빛이 닿지 않는 부분이 생길 수도 있다.
따라서, 도로 위에 어두운 부분이 생기지 않도록 하는 d값 중 최솟값을 구하려고 한다.
전체 도로의 길이 l, 가로등이 새워져 있는 위치가 들어있는 배열 v 가 매개변수로 주어질 때, 위의 모든 조건을 만족하는 d의 최솟값을 return 하도록 solution 함수를 완성하라.


제한사항
- l은 1 이상 1,000,000,000 이하의 자연수
- v 에는 가로등의 위치정보가 들어있다.
- 가로등의 위치는0 이상 l 이하의 정수이며, 같은 위치에 2개 이상의 가로등이 있는 경우는 주어지지 않는다.
- 가로등의 개수는1 이상 1,000 이하의 자연수
*/

inline bool CheckLight( int curRight, int nextLeft )
{
	return nextLeft <= curRight;
}

int GetMinLightLength(int roadLength, std::vector<int> v )
{
	int minDist = 0;
	roadLength++;
	
	std::sort( v.begin(), v.end() );

	for ( ; minDist < roadLength; ++minDist )
	{
		bool isLighted = true;
		int curPos = 0;
		int nextPos = 1;

		int curLeft = (std::max)(0, v[curPos] - minDist);
		int curRight;
		int nextLeft = (std::max)(0, v[nextPos] - minDist);
		int nextRight;
		isLighted &= CheckLight( 0, curLeft );
		for ( ; nextPos < v.size() - 1; ++curPos, ++nextPos )
		{
			curRight = (std::min)(roadLength - 1, v[curPos] + minDist);
			nextLeft = (std::max)(0, v[nextPos] - minDist);
			isLighted &= CheckLight( curRight, nextLeft );
			if ( isLighted == false )
			{
				break;
			}
		}
		nextRight = (std::min)(roadLength - 1, v[nextPos] + minDist);
		isLighted &= CheckLight( nextRight, roadLength-1);

		if ( isLighted )
		{
			return minDist;
		}
	}
	return minDist;
}

void Chapter13::Question4()
{
	InputReader text( L"text\\C13Q4.txt" );
	auto inputLine = text.GetLineVector();

	for ( int i = 0; i < inputLine.size(); i += 2 )
	{
		int l = stoi( inputLine[i] );
		std::stringstream ss( inputLine[i + 1] );
		std::vector<int> v;

		int n;
		while ( ss >> n ) {
			v.push_back( n );
		}

		StopWatch timer;
		const int answer = GetMinLightLength( l, v );
		timer.Stop();

		std::cout << "l = " << l <<std::endl;
		std::cout << "List : ";
		for ( const auto n : v )
		{
			std::cout << n << " ";
		}
		std::cout << std::endl;
		std::cout << "최소길이 = " << answer << ", 걸린시간 : " << timer.GetElapsedTime<double, (int)StopWatch::TimeUnit::Milli>() << "ms" << std::endl;
	}
}

class Grand
{
private:
	int hold;
public:
	Grand( int h = 0 )
		:
		hold( h )
	{}
	virtual void Speak() const
	{
		std::cout << "Grand Class\n";
	}
	virtual int Value() const
	{
		return hold;
	}
};
class Superb : public Grand
{
public:
	Superb( int h = 0 )
		:
		Grand( h )
	{}
	void Speak() const override
	{
		std::cout << "Superb Class\n";
	}
	virtual void Say() const
	{
		std::cout << "Superb value = " << Value() << std::endl;
	}
};
class Magnificent : public Superb
{
private:
	char ch;
public:
	Magnificent( int h = 0, char c = 'A' )
		:
		Superb( h ),
		ch( c )
	{}
	void Speak() const override
	{
		std::cout << "Magnificent class\n";
	}
	void Say() const override
	{
		std::cout << "char = " << ch << "value = " << Value() << std::endl;
	}
};

Grand* GetOne()
{
	Grand* pG = nullptr;
	switch ( std::rand() % 3 )
	{
	case 0:
		pG = new Grand( std::rand() % 100 );
		break;
	case 1:
		pG = new Superb( std::rand() % 100 );
		break;
	case 2:
		pG = new Magnificent( std::rand() % 100, 'A' + std::rand() % 26 );
		break;
	}
	return pG;
}

void Chapter13::ExRTTI()
{
	std::srand( std::time( 0 ) );
	Grand* pG;
	Superb* pS;
	for ( int i = 0; i < 5; i++ )
	{
		pG = GetOne();
		pG->Speak();
		if ( pS = dynamic_cast<Superb*>(pG) )
		{
			pS->Say();
		}
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



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
		std::cout << ": Ź���밡 �ִ�.\n";
	}
	else
	{
		std::cout << ": Ź���밡 ����.\n";
	}
	player1.Name();
	if ( player1.HasTable() )
	{
		std::cout << ": Ź���밡 �ִ�.\n";
	}
	else
	{
		std::cout << ": Ź���밡 ����.\n";
	}
	std::cout << "�̸�: ";
	rplayer1.Name();
	std::cout << "; ��ŷ: " << rplayer1.Rating() << std::endl;

	RatedPlayer rplayer2( 1212, player1 );
	std::cout << "�̸�: ";
	rplayer2.Name();
	std::cout << "; ��ŷ: " << rplayer2.Rating() << std::endl;

	RatedPlayer::Show( rplayer1 );
	RatedPlayer::Show( player1 );
}


/*
* Circle2D, Rectangle2D, MyPoint Ŭ������ �߻� Ŭ���� ��� ������ �����Ͽ� �ٽ� �ۼ�
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

	std::cout << "c1�� ����: " << geoObjects[0]->GetArea() << "\nc1�� �ѷ�: " << geoObjects[0]->GetPerimeter() << std::endl;
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
	std::cout << "������ Ƚ�� : " << moveCount << std::endl;
}

/*
* ���� ������ �����ϴ� StopWatch Ŭ���� ����
* get�Լ��� ���� ���� �������ʵ� startTime, endTime
* startTime�� ���� �ð����� �ʱ�ȭ�ϴ� �μ� ���� ������
* startTime�� ���� �ð����� �缳���ϴ� start()�Լ�
* endTime�� ����ð����� �����ϴ� stop()�Լ�
* stopwatch�� ����ð��� �и��� ������ ��ȯ�ϴ� getElapsedTime()�Լ�
* Ŭ������ ���� UML���̾�׷��� �׸��� Ŭ���� ����
* �ռ����� Ȯ�������� �Ǵ� �ϳ��� Ÿ�� ���� �ذῡ �ɸ��� �ð� ����
*/
void Chapter13::Question2()
{
	StopWatch timer;
	ExTowerOfHanoi();
	timer.Stop();

	std::cout << "\n�ɸ� �ð� : " << timer.GetElapsedTime<double, (int)StopWatch::TimeUnit::Milli>() << "ms" << std::endl;
}

const int LIM = 4;
void Chapter13::TestWorker()
{
	Waiter bob( "ȫ�浿", 314L, 5 );
	Singer bev( "������", 522L, 3 );
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
		cout << "������ �Է��Ͻʽÿ�:\n"
			<< "w:������ s:���� t:���� �� ������ q:����\n";
		cin >> choice;
		while ( strchr( "wstq", choice ) == NULL )
		{
			cout << "w, s, t, q �߿��� �ϳ��� �����Ͻʽÿ�: ";
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

	cout << "\n ��� ��Ȳ�� ������ �����ϴ�.\n";
	for ( int i = 0; i < ct; i++ )
	{
		cout << endl;
		lolas[i]->Show();
	}
	for ( int i = 0; i < ct; i++ )
	{
		delete lolas[i];
	}
	cout << "���α׷� ����\n";
}

/*
* 8 x 8 �����¿�밢�� �� �̵�
* 8���� ���� ���� �浹���� �ʰ� ��ġ�� �� �ִ� ����� ���� �����,
* �ش� ������ ��� �Ḧ �̿��ؼ� ���� ��ġ ��Ȳ�� ���
* �� ����: ��, ����: ��
* �� �� �� �� �� �� �� ��
* �� �� �� �� �� �� �� ��
* �� �� �� �� �� �� �� ��
* �� �� �� �� �� �� �� ��
* �� �� �� �� �� �� �� ��
* �� �� �� �� �� �� �� ��
* �� �� �� �� �� �� �� ��
* �� �� �� �� �� �� �� ��
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
	private:
		State state = State::Empty;
	};

public:
	QueenMap(int size)
		:
		width(size)
	{
		field = std::make_unique<Tile[]>( size * size );
	} 
	bool CheckFieldSize(const Vec2<int>& pos) const
	{
		return (pos.x >= 0 && pos.x < 8) && (pos.y >= 0 && pos.x < 8);
	}
	int FindNextEmpty()
	{
		for ( int i = 0; i < width * width; ++i )
		{
			if ( field[i].GetState() == Tile::State::Empty )
			{
				return i;
			}
		}
		return -1;
	}
	void SetVisitedLineByDir(const Vec2<int>& curPos, const Vec2<int>& dir)
	{
		if ( CheckFieldSize( curPos ) )
		{
			const int curTilePos = curPos.y * width + curPos.x;
			if ( field[curTilePos].GetState() == Tile::State::Empty )
			{
				field[curTilePos].SetVisited();
				SetVisitedLineByDir( curPos + dir, dir );
			}
		}
	}
	void SetMapVisited( const Vec2<int>& pos )
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
		SetMapVisited( curPos );

		const int nextTilePos = FindNextEmpty();
		if ( nextTilePos != -1 )
		{

		}
	}

	void PrintField() const
	{
		for ( int y = 0; y < width; ++y )
		{
			for ( int x = 0; x < width; ++x )
			{
				const int pos = y * width + x;
				const Tile::State state = field[pos].GetState();
				if ( state == Tile::State::Empty )
				{
					std::cout << "��";
				}
				else if ( state == Tile::State::HasQueen )
				{
					std::cout << "��";
				}
				else
				{
					std::cout << "��";
				}
			}
			std::cout << std::endl;
		}
		std::cout << std::endl;
	}

private:
	const Vec2<int> Up { 0, 1 };
	const Vec2<int> Down{ 0, -1 };
	const Vec2<int> Right{ 1,0 };
	const Vec2<int> Left{ -1,0 };
	const int width;
	std::unique_ptr<Tile[]> field;
	int queenCount = 0;
};



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
				std::cout << "�� ";
			}
			else if ( visitedMap[curPos])
			{
				std::cout << "�� ";
			}
			else
			{
				std::cout << "�� ";
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

void SetMapTrueByQueenPos( std::bitset<64>& visitedMap, const Vec2<int>& queenPos, int boardSize = 8 )
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
	PutEightQueens( visitedMap, nextPos % boardSize, nextPos / boardSize, boardSize );
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
				std::cout << "�� ";
				curQueenCnt++;
			}
			else
			{
				std::cout << "�� ";
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
			std::vector<Vec2<int>> queens;
			visitedMap.reset();
			PutEightQueens( visitedMap, x, y, 8 );
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
* N���� �̿��ڸ� ���� �Ҽ� ��Ʈ��ũ ����
* �̿��ڴ� 1������ n�� ��ȣ 
�پ�����
* �� �̿����� ģ�� �� �м�
* �̿��� A�� B�� ģ����� B�� A�� ģ��
* ģ���� ģ���� ģ��, A�� B�� ģ���̰� B�� C�� ģ���̸� A�� C�� ģ��
* 
* �Ҽ� ��Ʈ��ũ ��ü�̿��� �� N,
* �� �̿����� ģ�����踦 ��� �ִ� �迭 relation�� �Ű������� �־��� ��
* �� �̿����� ģ�� ���� 1�� �̿��� ������� ���� �迭�� return�ϵ��� �Լ� �ۼ�
* 
* ���ѻ���
* N�� 2�̻� 100���� �ڿ���
* relation�� �� ���Ҵ� ģ�����踦 ��Ÿ����, relation�� ���̴� 1�̻� N(N-1)/2����
* �� ģ�� ����� ���̰� 2�� �迭�̸�, ������� (a,b)�� ��Ÿ��. a,b (1<=a, b<=n, a!=b) �� ģ�������� �� �̿����� ��ȣ
* a�� b�� ���� ���� ������, ģ�� ����� �� ������ �־�����.
* ���ѽð�:100000ms
*/



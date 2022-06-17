#include "Chapter16.h"

#include <iostream>
#include <vector>
#include <string>
#include "Vec2.h"
#include "StopWatch.h"
#include <memory>
#include <algorithm>
#include <iterator>
#include <fstream>
#include "FileSplitter.h"

/*
* 홀수의 양의 정수 k 가 주어졌을 때
* 가로 세로 크기가 k인 공간에 오른쪽으로 정렬 된 삼각형 출력
* 모서리는 * 내부는 +로 채우기
*  3<= k <= 99
* 잘못된 데이터 입력되는 경우가 없다
* 
* 
* ex)
*		3						5
*		*						*
*	  * *					  * *
*		*					* + *
*							  * *
*								*
*/

class TileMap
{
private:
	class Tile
	{
	public:
		enum class Type
		{
			Empty,
			Border,
			InFill
		};
	public:
		Tile() {};
		void SetTypeEmpty()
		{
			type = Type::Empty;
		}
		void SetTypeBorder()
		{
			type = Type::Border;
		}
		void SetTypeInfill()
		{
			type = Type::InFill;
		}
		Type GetType() const
		{
			return type;
		}
		bool IsTypeEmpty() const
		{
			return type == Type::Empty;
		}
		bool IsTypeBorder() const
		{
			return type == Type::Border;
		}
		bool IsTypeInFill() const
		{
			return type == Type::InFill;
		}
	private:
		Type type = Type::Empty;
	};
public:
	TileMap( int width )
		:
		width( width ),
		size( width * width )
	{
		tiles.reserve( size );
		tiles.assign( size, Tile() );
	}
	inline char GetTileChar(const Tile& t) const
	{
		if ( t.IsTypeEmpty() )
		{
			return ' ';
		}
		else if ( t.IsTypeBorder() )
		{
			return '*';
		}
		return '+';
	}
	void PrintTiles() const
	{
		for ( int y = 0; y < width; ++y )
		{
			for ( int x = 0; x < width; ++x )
			{
				std::cout << GetTileChar( tiles[y * width + x] ) << " ";
			}
			std::cout << std::endl;
		}
		std::cout << std::endl;
	}
	void CreateRightTriangle()
	{
		bool wasLeftBorder = false;
		for ( int y = 0; y < width; ++y )
		{
			for ( int x = 0; x < width; ++x )
			{
				// On Right Side
				if (x >= width / 2)
				{
					const int pos = y * width + x;
					if ( x == y || x + y == width - 1 )
					{
						tiles[pos].SetTypeBorder();
						wasLeftBorder = true;
					}
					else if ( wasLeftBorder )
					{
						tiles[pos].SetTypeInfill();
					}
					if ( x == width - 1 )
					{
						tiles[pos].SetTypeBorder();
						wasLeftBorder = false;
					}
				}
			}
		}
	}
private:
	std::vector<Tile> tiles;
	const int width;
	const int size;
};

void Chapter16::Question1()
{
	int n = 0;
	while ( n % 2 == 0 )
	{
		std::cout << "홀수 숫자 입력 : ";
		std::cin >> n;
	}

	StopWatch timer;

	TileMap tri( n );
	tri.CreateRightTriangle();
	tri.PrintTiles();

	timer.Stop();
	std::cout << "걸린 시간 : " << timer.GetElapsedTime<double, (int)StopWatch::TimeUnit::Milli>() << " ms\n";
}

void Chapter16::ExSmartPtr()
{
	class Report
	{
	private:
		std::string str;
	public:
		Report( const std::string& s )
			:
			str( s )
		{
			std::cout << "객체가 생성되었습니다!\n";
		}
		~Report()
		{
			std::cout << "객체가 삭제되었습니다!\n";
		}
		void Comment() const
		{
			std::cout << str << "\n";
		}
	};

	{
		std::unique_ptr<Report> pU = std::make_unique<Report>( "unique ptr" );
		pU->Comment();
	}
	{
		std::shared_ptr<Report> pS = std::make_shared<Report>( "Shared ptr" );
		pS->Comment();
	}
}

struct Review
{
	std::string title;
	int rating;
};

bool FillReview( Review& rr )
{
	std::cout << "책 제목을 입력하십시오 (끝내려면 quit 입력) : ";
	std::getline( std::cin, rr.title );
	if ( rr.title == "quit" )
	{
		return false;
	}
	std::cout << "책 등급(0-10)을 입력하십시오: ";
	std::cin >> rr.rating;
	if ( !std::cin )
	{
		return false;
	}
	while ( std::cin.get() != '\n' )
	{
		continue;
	}
	return true;
}

void ShowReview( const Review& rr )
{
	std::cout << rr.rating << "\t" << rr.title << std::endl;
}

void Chapter16::ExVectorClass()
{
	using std::cout;
	using std::vector;
	vector<Review> books;
	Review temp;
	while ( FillReview(temp) )
	{
		books.push_back( temp );
	}
	int num = books.size();
	if ( num > 0 )
	{
		cout << "감사합니다. 당신은 다음과 같이 입력했습니다.\n등급\t제목\n";
		for ( int i = 0; i < num; ++i )
		{
			ShowReview( books[i] );
		}
		cout << "한번 더 출력한다:\n등급\t제목\n";
		vector<Review>::iterator it;
		for ( it = books.begin(); it != books.end(); it++ )
		{
			ShowReview( *it );
		}
		vector<Review> oldList( books );
		if ( num > 3 )
		{
			books.erase( books.begin() + 1, books.begin() + 3 );
			cout << "삭제한 후:\n";
			for ( it = books.begin(); it != books.end(); it++ )
			{
				ShowReview( *it );
			}
			books.insert( books.begin(), oldList.begin() + 1, oldList.begin() + 2 );
			cout << "삽입한 후:\n";
			for ( it = books.begin(); it != books.end(); it++ )
			{
				ShowReview( *it );
			}
		}
		books.swap( oldList );
		cout << "oldlist와 books를 교환한 후 :\n";
		for ( it = books.begin(); it != books.end(); it++ )
		{
			ShowReview( *it );
		}
	}
	else
	{
		cout << "입력한 것이 없어 얻은 것이 없습니다\n";
	}
}

void Chapter16::CopyIt()
{
	using namespace std;

	int casts[10] = { 6,7,2,9,4,11,8,7,10,5 };
	vector<int> dice( 10 );

	copy( casts, casts + 10, dice.begin() );
	cout << "주사위를 던져라!\n";
	ostream_iterator<int, char> out_iter( cout, " " );
	copy( dice.begin(), dice.end(), out_iter );
	cout << endl;
	cout << "역방향 이터레이터의 암시적 사용:\n";
	copy( dice.rbegin(), dice.rend(), out_iter );
	cout << endl;
	cout << "역방향 이터레이터의 명시적 사용:\n";
	vector<int>::reverse_iterator ri;
	for ( ri = dice.rbegin(); ri != dice.rend(); ++ri )
	{
		cout << *ri << ' ';
	}
	cout << endl;
}


void Chapter16::Inserts()
{
	using namespace std;
	string s1[4] = { "fine", "fish", "fashion", "fate" };
	string s2[2] = { "busy", "bats" };
	string s3[2] = { "silly", "singers" };
	
	vector<string> words( 4 );
	copy( s1, s1 + 4, words.begin() );
	auto Output = []( const string& s ) {cout << s << " "; };
	for_each( words.begin(), words.end(), Output );
	cout << endl;

	copy( s2, s2 + 2, back_insert_iterator<vector<string>>( words ) );
	for_each( words.begin(), words.end(), Output );
	cout << endl;

	copy( s3, s3 + 2, back_insert_iterator<vector<string>>( words ) );
	for_each( words.begin(), words.end(), Output );
	cout << endl;
}

void Chapter16::EXWrite()
{
	using std::cout;
	using std::endl;
	const char* state1 = "Florida";
	const char* state2 = "kansas";
	const char* state3 = "euphoria";
	int len = std::strlen( state3 );
	cout << "루프 인덱스 증가:\n";
	int i;
	for ( i = 1; i <= len; i++ )
	{
		cout.write( state3, i );
		cout << endl;
	}

	cout << "루프 인덱스 감소:\n";
	for ( i = len; i > 0; i-- )
	{
		cout.write( state3, i ) << endl;
	}
	cout << "문자열 길이 초과:\n";
	cout.write( state3, len + 5 ) << endl;
}

void Chapter16::CheckIt()
{
	using namespace std;
	cout << "수를 입력하십시오: ";
	int sum = 0;
	int input;
	while ( cin >> input )
	{
		sum += input;
		cout << "현재 input = " << input << endl;
	}
	cout << "마지막으로 입력한 값 = " << input << endl;
	cout << "합계 = " << sum << endl;
	
}

void Chapter16::ExFileIO()
{
	using namespace std;
	string filename;
	cout << "새 파일을 위한 이름ㅇ르 입력하십시오: ";
	cin >> filename;

	ofstream fout( filename.c_str() );
	fout << "비밀번호 노출에 주의하십시오.\n";
	cout << "비밀번호를 입력하십시오: ";
	float password;
	cin >> password;
	fout << " 귀하의 비밀번호는 " << password << "입니다.\n";
	fout.close();

	ifstream fin( filename.c_str() );
	cout << filename << " 파일의 내용은 다음과 같습니다:\n";
	char ch;
	while ( fin.get( ch ) )
	{
		cout << ch;
	}
	cout << "프로그램을 종료합니다.\n";
	fin.close();
}

/*
* 용량이 큰 파일을 작은 용량으로 분할하는 유틸리티
* 사용자로부터 소스 파일명을 입력받은 후 각각 분할된 작은 파일의 바이트 값을 입력받음
* ex> Enter file name : test.zip
* Enter file size : 1024
* -> File test.zip.01
* -> File test.zip.02
* -> File test.zip.03
* Split Done.
*/


void Chapter16::Question2()
{
	std::cout << "ENter file name :";
	std::string filename;
	std::cin >> filename;
	FileSplitter fileSplitter( filename );
	fileSplitter.Split( 3 );
}

/*
* 사용자로 부터 소스 파일의 개수, 소스 파일의 이름, 목적 파일의 이름을 입력받아
* 새로운 하나의 파일로 파일을 조합하는 프로그램
* ex >	Enter file number: 3
*		Enter source file name: test.zip.01
*		Enter source file name: test.zip.02
*		Enter source file name: test.zip.03
*		Enter Target file name : test.zip
*		combine done.
*/
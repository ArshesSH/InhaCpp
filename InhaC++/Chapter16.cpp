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
* Ȧ���� ���� ���� k �� �־����� ��
* ���� ���� ũ�Ⱑ k�� ������ ���������� ���� �� �ﰢ�� ���
* �𼭸��� * ���δ� +�� ä���
*  3<= k <= 99
* �߸��� ������ �ԷµǴ� ��찡 ����
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
		std::cout << "Ȧ�� ���� �Է� : ";
		std::cin >> n;
	}

	StopWatch timer;

	TileMap tri( n );
	tri.CreateRightTriangle();
	tri.PrintTiles();

	timer.Stop();
	std::cout << "�ɸ� �ð� : " << timer.GetElapsedTime<double, (int)StopWatch::TimeUnit::Milli>() << " ms\n";
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
			std::cout << "��ü�� �����Ǿ����ϴ�!\n";
		}
		~Report()
		{
			std::cout << "��ü�� �����Ǿ����ϴ�!\n";
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
	std::cout << "å ������ �Է��Ͻʽÿ� (�������� quit �Է�) : ";
	std::getline( std::cin, rr.title );
	if ( rr.title == "quit" )
	{
		return false;
	}
	std::cout << "å ���(0-10)�� �Է��Ͻʽÿ�: ";
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
		cout << "�����մϴ�. ����� ������ ���� �Է��߽��ϴ�.\n���\t����\n";
		for ( int i = 0; i < num; ++i )
		{
			ShowReview( books[i] );
		}
		cout << "�ѹ� �� ����Ѵ�:\n���\t����\n";
		vector<Review>::iterator it;
		for ( it = books.begin(); it != books.end(); it++ )
		{
			ShowReview( *it );
		}
		vector<Review> oldList( books );
		if ( num > 3 )
		{
			books.erase( books.begin() + 1, books.begin() + 3 );
			cout << "������ ��:\n";
			for ( it = books.begin(); it != books.end(); it++ )
			{
				ShowReview( *it );
			}
			books.insert( books.begin(), oldList.begin() + 1, oldList.begin() + 2 );
			cout << "������ ��:\n";
			for ( it = books.begin(); it != books.end(); it++ )
			{
				ShowReview( *it );
			}
		}
		books.swap( oldList );
		cout << "oldlist�� books�� ��ȯ�� �� :\n";
		for ( it = books.begin(); it != books.end(); it++ )
		{
			ShowReview( *it );
		}
	}
	else
	{
		cout << "�Է��� ���� ���� ���� ���� �����ϴ�\n";
	}
}

void Chapter16::CopyIt()
{
	using namespace std;

	int casts[10] = { 6,7,2,9,4,11,8,7,10,5 };
	vector<int> dice( 10 );

	copy( casts, casts + 10, dice.begin() );
	cout << "�ֻ����� ������!\n";
	ostream_iterator<int, char> out_iter( cout, " " );
	copy( dice.begin(), dice.end(), out_iter );
	cout << endl;
	cout << "������ ���ͷ������� �Ͻ��� ���:\n";
	copy( dice.rbegin(), dice.rend(), out_iter );
	cout << endl;
	cout << "������ ���ͷ������� ����� ���:\n";
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
	cout << "���� �ε��� ����:\n";
	int i;
	for ( i = 1; i <= len; i++ )
	{
		cout.write( state3, i );
		cout << endl;
	}

	cout << "���� �ε��� ����:\n";
	for ( i = len; i > 0; i-- )
	{
		cout.write( state3, i ) << endl;
	}
	cout << "���ڿ� ���� �ʰ�:\n";
	cout.write( state3, len + 5 ) << endl;
}

void Chapter16::CheckIt()
{
	using namespace std;
	cout << "���� �Է��Ͻʽÿ�: ";
	int sum = 0;
	int input;
	while ( cin >> input )
	{
		sum += input;
		cout << "���� input = " << input << endl;
	}
	cout << "���������� �Է��� �� = " << input << endl;
	cout << "�հ� = " << sum << endl;
	
}

void Chapter16::ExFileIO()
{
	using namespace std;
	string filename;
	cout << "�� ������ ���� �̸����� �Է��Ͻʽÿ�: ";
	cin >> filename;

	ofstream fout( filename.c_str() );
	fout << "��й�ȣ ���⿡ �����Ͻʽÿ�.\n";
	cout << "��й�ȣ�� �Է��Ͻʽÿ�: ";
	float password;
	cin >> password;
	fout << " ������ ��й�ȣ�� " << password << "�Դϴ�.\n";
	fout.close();

	ifstream fin( filename.c_str() );
	cout << filename << " ������ ������ ������ �����ϴ�:\n";
	char ch;
	while ( fin.get( ch ) )
	{
		cout << ch;
	}
	cout << "���α׷��� �����մϴ�.\n";
	fin.close();
}

/*
* �뷮�� ū ������ ���� �뷮���� �����ϴ� ��ƿ��Ƽ
* ����ڷκ��� �ҽ� ���ϸ��� �Է¹��� �� ���� ���ҵ� ���� ������ ����Ʈ ���� �Է¹���
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
* ����ڷ� ���� �ҽ� ������ ����, �ҽ� ������ �̸�, ���� ������ �̸��� �Է¹޾�
* ���ο� �ϳ��� ���Ϸ� ������ �����ϴ� ���α׷�
* ex >	Enter file number: 3
*		Enter source file name: test.zip.01
*		Enter source file name: test.zip.02
*		Enter source file name: test.zip.03
*		Enter Target file name : test.zip
*		combine done.
*/
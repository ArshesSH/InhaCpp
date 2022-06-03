#include "Chapter10.h"

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <random>
#include "Vec2.h"
#include "Vec3.h"
#include "stock00.h"

/*
* Q1
* 학교에 100개의 사물함과 100명의 학생이 있다.
* 모든 사물함은 첫 날에 닫혀있다
* 학생이 교실로 들어가면서
*	s1이라는 첫 번째 학생은 모든 사물함을 연다.
*	s2라는 두 번째 학생은 사물함 L2부터 시작하여 하나씩 건너뛰면서 사물함을 닫는다.
*	s3라는 세 번째 학생은 사물함 L3부터 시작하여 세 번째 사물함 마다 상태를 변경한다.
*	s4라는 네 번째 학생은 사물함 L4부터 시작하여 네 번째 사물함 마다 상태를 변경한다.
*	...
*	s100이라는 백 번째 학생은 사물함 L100부터 시작하여 100 번째 사물함 마다 상태를 변경한다.
* 
*	모든 학생이 교실을 통과하고 난 다음 어떤 사물함이 열려있는지, 열려있는 모든 사물함 번호를 출력
*/

void ChangeLockerState( bool& isLockerClose )
{
	isLockerClose = 1 - isLockerClose;
}

void Chapter10::Question1()
{
	// s1
	bool isLockerCloseList[100] = { false };

	for ( int s = 2; s <= 100; s++ )
	{
		for ( int i = 1; i * s < 100; i++ )
		{
			ChangeLockerState( isLockerCloseList[(i * s) - 1] );
		}
	}

	std::cout << "열려있는 사물함은 :\n";
	for ( int i = 0; i < 100; i++ )
	{
		if ( isLockerCloseList[i] == false )
		{
			std::cout << i + 1 << "번째 ";
		}
	}
	std::cout << std::endl;
}


/*
* Q2
* 점 p0부터 p1까지의 직선이 주어졌을 때
* 점 p2가 선의 왼쪽 또는 오른쪽에 있는지 판단할 수 있다.
* 점 p0, p1, p2 입력 후 점 p2가 어디에 위치하는지 출력하는 프로그램
* 
* p0 : 4.4 2
* p1 : 6.5 9.5
* p2 : -5 4
* p2는 선의 왼쪽에 있다.
*/
void Chapter10::Question2()
{
	Vec3<float> point[3];

	for ( int i = 0; i < 3; i++ )
	{
		std::cout << "점 p" << i << "(x" << i << ", y" << i << ") : ";
		std::cin >> point[i].x >> point[i].y;
		point[i].z = 0;
	}
	
	const Vec3<float> line = point[1] - point[0];
	const Vec3<float> lineDir = line.GetNormalized();
	
	const Vec3<float> crossed = Vec3<float>::GetCrossProduct( lineDir, point[2] );
	
	if ( crossed.z > 0 )
	{
		std::cout << "p2는 선의 왼쪽에 있다." << std::endl;
	}
	else if ( crossed.z < 0 )
	{
		std::cout << "p2는 선의 오른쪽에 있다." << std::endl;
	}
	else
	{
		std::cout << "p2는 선 위에 있다." << std::endl;
	}
}

void Chapter10::LearnClass()
{
	Stock fluffy_the_cat;
	fluffy_the_cat.acquire( "NanoSmart", 20, 12.50 );
	fluffy_the_cat.show();
	fluffy_the_cat.buy( 15, 18.125 );
	fluffy_the_cat.show();
	fluffy_the_cat.sell( 400, 20.00 );
	fluffy_the_cat.show();
	fluffy_the_cat.buy( 300000, 40.125 );
	fluffy_the_cat.show();
	fluffy_the_cat.sell( 300000, 0.125 );
	fluffy_the_cat.show();
}


/*
* Q3
* 삼각형의 세 변의 길이를 알면 세개의 내각을 구할 수 있다.
* 삼각형의 세 꼭지점 좌표를 입력받은 후 삼각형의 각도를 구하라
* 
* ex>
* 점 1 : 1 1
* 점 2 : 6.5 1
* 점 3 : 6.5 2.5
* 세 각은 15.25, 90.00, 74.74 이다.
*/
template<typename T>
T GetRadian( const Vec2<T>& lineOne, const Vec2<T>& lineTwo )
{
	return (T)std::acosf( (lineOne * lineTwo) / std::sqrtf(lineOne.GetLengthSq() * lineTwo.GetLengthSq()) );
}

void Chapter10::Question3()
{
	Vec2<float> p[3];
	for ( int i = 0; i < 3; i++ )
	{
		std::cout << "점" << i << " : ";
		std::cin >> p[i].x >> p[i].y;
	}

	const float pi = 3.141592;
	const float radCoef = (180 / pi);

	float angle[3];
	bool isTriangle = true;
	for ( int i = 0; i < 3; i++ )
	{
		int indexLeft = i - 1;
		if ( indexLeft == -1 )
		{
			indexLeft = 2;
		}

		int indexRight = i + 1;
		if ( indexRight == 3 )
		{
			indexRight = 0;
		}

		const Vec2<float> lineOne = p[indexLeft] - p[i];
		const Vec2<float> lineTwo = p[indexRight] - p[i];

		angle[i] = radCoef * GetRadian( lineOne, lineTwo );
		if ( std::isnan( angle[i] ) )
		{
			isTriangle = false;	
		}
	}

	if ( isTriangle )
	{
		const auto origin = std::cout.setf( std::ios_base::fixed, std::ios_base::floatfield );
		const auto prec = std::cout.precision( 2 );

		std::cout << "세 각은 " << angle[0] << " " << angle[1] << " " << angle[2] << "이다.\n" << std::endl;

		std::cout.setf( origin, std::ios_base::floatfield );
		std::cout.precision( prec );
	}
	else
	{
		std::cout << "삼각형이 아닙니다!!!\n" << std::endl;
	}
}

/*
* 임의의 한 단어를 생성하고 사용자가 한 번에 한 문자만을 추측하도록 해서 단어를 맞추는 게임 (행맨)
* 단어의 각 문자 '*'로 표시
* 사용자가 올바른 추측하면 실제 문자 화면에 표시
* 사용자가 단어 맞추기를 끝냈을 경우 실수한 횟수 표시, 다른 단어로 계속할 것인지 묻기
* ex>생성된 단어 : apple
* 단어중 한 글자를 입력하시오 : ***** > a
*							  a****
* 단어중 한 글자를 입력하시오 : a**** > r
* r은 단어에 포함되지 않습니다.
* 단어중 한 글자를 입력하시오 : ***** > a
* a는 이미 단어에 포함되어 있습니다.
* 단어중 한 글자를 입력하시오 : app*e > l
* 총 x번 실패 x번 만에 정답!
*/

void GetCharPosList( char c, const std::string& str, std::vector<size_t>& posList )
{
	for ( auto i = 0; i < str.size(); ++i )
	{
		if ( str[i] == c )
		{
			posList.push_back( i );
		}
	}
}

bool IsCharInStr( char c, const std::string& str )
{
	if ( str.find( c ) != std::string::npos )
	{
		return true;
	}
	return false;
}

void Chapter10::Hangman()
{
	// Generate words
	std::vector<std::string> words;
	std::ifstream in( "5words.txt" );
	for ( std::string str; std::getline( in, str ); )
	{
		if ( str.empty() )
		{
			continue;
		}
		words.push_back( str );
	}
	in.close();

	// Set Init variables
	int correctCnt = 0;
	int wrongCnt = 0;

	// Loop Game
	bool isGameFinished = false;
	while ( !isGameFinished )
	{
		// Pick word from random words
		std::random_device rd;
		std::mt19937 rng( rd() );
		std::uniform_int_distribution<> wordDist( 0, words.size() - 1 );
		const std::string targetWord = words[wordDist( rng )];

		// Generate answerStr
		std::string answerStr;
		for ( const auto c : targetWord )
		{
			answerStr.push_back( '*' );
		}

		// Loop Stage
		bool isStageFinished = false;
		while ( !isStageFinished )
		{
			// Print current state
			std::cout << "단어 중 한 글자를 입력하시오. " << answerStr << " > ";
			
			// Get Player Input char
			char playerInput;
			std::cin >> playerInput;
			playerInput = (char)tolower( playerInput );

			// Get Character Pos List
			std::vector<size_t> posList;
			GetCharPosList( playerInput, targetWord, posList );

			// If playerInput in target word
			if ( !posList.empty() )
			{
				// If playerInput not in answerStr
				if ( !IsCharInStr( playerInput, answerStr ) )
				{
					// Change answerStr
					for ( const auto e : posList )
					{
						answerStr[e] = playerInput;
					}
					++correctCnt;
					std::cout << "\t\t\t\t" << answerStr << std::endl;

					// If Find Answer, Finish stage
					if ( answerStr == targetWord )
					{
						std::cout << "총 " << wrongCnt << "번 실패, " << correctCnt << "번 만에 정답!\n\n";
						isStageFinished = true;
					}
				}
				else
				{
					std::cout << playerInput << "은(는) 이미 있습니다.\n\n";
				}
			}
			else
			{
				std::cout << playerInput << "은(는) 단어에 포함되지 않습니다.\n\n";
				++wrongCnt;
			}
		}

		// Continue
		bool inputFlag = true;
		while ( inputFlag )
		{
			char c;
			std::cout << "계속 하시겠습니까? (Y or N) : ";
			std::cin >> c;
			switch ( c )
			{
			case 'y':
			case 'Y':
				inputFlag = false;
				break;

			case 'n':
			case 'N':
				isGameFinished = true;
				inputFlag = false;
				break;
			}
		}
	}
}

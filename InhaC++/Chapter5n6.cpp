#include "Chapter5n6.h"

#include <iostream>
#include <vector>
#include <cstring>


void Chapter5n6::ExPalindrome()
{
    std::string str;
    std::cout << "Input String : ";
    std::cin >> str;

    std::cout << str << "은 회문";
    if ( FindPalindrome(str) )
    {
        std::cout << "입니다." << std::endl;
    }
    else
    {
        std::cout << "이 아닙니다." << std::endl;
    }
}

/*
* Q3
* 1~10까지 정수 입력 피라미드 출력 프로그램
* ex) INput 5  / o == space
* oooo1
* ooo212
* oo32123
* o4321234
* 543212345
*/
void Chapter5n6::PrintPyramid()
{
    int inputNum = 1;
    do
    {
        std::cout << "Input Num(1~10) : ";
        std::cin >> inputNum;
    } while ( inputNum < 1 || inputNum > 10 );


    // for each line
    for ( int line = 1; line <= inputNum; ++line )
    {
        // Print Space at line
        for ( int iSpace = line; iSpace < inputNum; ++iSpace )
        {
            std::cout << " ";
        }

        // Increase or Decrease number
        for ( int num = line, numCnt = 0; numCnt < (line * 2) - 1; ++numCnt)
        {
            std::cout << num;
            if ( numCnt < line - 1 )
            {
                --num;
            }
            else
            {
                ++num;
            }
        }
        std::cout << std::endl; 
    }
}

void Chapter5n6::Exercise7()
{
    // Dynamic array
    struct CarInfo
    {
        std::string companyName;
        int year = 0;
    };

    int carCnt;
    std::cout << "몇 대의 차를 목록으로 관리하시겠습니까? ";
    std::cin >> carCnt;

    CarInfo* pCarList = new CarInfo[carCnt];
    for ( int i = 0; i < carCnt; ++i )
    {
        std::cout << "자동차 #" << i << ":\n";
        std::cout << "제작업체: ";
        std::cin >> pCarList->companyName;
        std::cout << "제작년도: ";
        std::cin >> pCarList->year;
    }

    std::cout << "귀하가 보유하고 있는 자동차 목록은 다음과 같습니다.\n";
    for ( int i = 0; i < carCnt; ++i )
    {
        std::cout << pCarList->year << "년형 " << pCarList->companyName << std::endl;
    }

    delete[] pCarList;

    // Vector
    struct CarInfoForVec
    {
        std::string companyName;
        int year = 0;
    };

    int carCount;
    std::cout << "몇 대의 차를 목록으로 관리하시겠습니까? ";
    std::cin >> carCount;

    std::vector<CarInfoForVec> carList;
    for ( int i = 0; i < carCount; ++i )
    {
        std::string company;
        int year;
        std::cout << "자동차 #" << i << ":\n";
        std::cout << "제작업체: ";
        std::cin >> company;
        std::cout << "제작년도: ";
        std::cin >> year;

        carList.emplace_back( CarInfoForVec{ company, year } );
    }

    std::cout << "귀하가 보유하고 있는 자동차 목록은 다음과 같습니다.\n";

    for ( auto e : carList )
    {
        std::cout << e.year << "년형 " << e.companyName << std::endl;
    }

}

void Chapter5n6::Exercise8()
{
    char tmpStr[BUFSIZ];
    int cnt = 0;
    std::cout << "영어 단어들을 입력하십시오 (끝내려면 done을 입력) : ";
    while ( strcmp( tmpStr, "done" ) != 0 )
    {
        std::cin >> tmpStr;
        cnt++;
    }

    std::cout << cnt - 1 << std::endl;
}

bool Chapter5n6::FindPalindrome( const std::string str )
{
    for ( int startPos = 0, endPos = str.size() - 1; startPos < endPos; startPos++, endPos--  )
    {
        if ( str[startPos] != str[endPos] )
        {
            return false;
        }
    }
    return true;
}

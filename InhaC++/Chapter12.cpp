#include "Chapter12.h"

#include <iostream>
#include "MyString.h"
#include <crtdbg.h>

void CallByRef( MyString& src )
{
	std::cout << "Call By Reference : " << src << std::endl;
}
void CallByVal( MyString src )
{
	std::cout << "Call By Value : " << src << std::endl;
}

void Chapter12::LearnSpecialMemeberFunction()
{
	const int wordsSize = 10;

	MyString name;
	std::cout << "이름 입력 : ";
	std::cin >> name;

	std::cout << name << "님 영어 단어 " << wordsSize << "개 입력해요\n";
	MyString words[wordsSize];
	char tmp[MyString::BufferSize];
	
	int i;
	for ( i = 0; i < wordsSize; ++i )
	{
		std::cout << i + 1 << ": ";
		std::cin.get( tmp, MyString::BufferSize );
		while ( std::cin && std::cin.get() != '\n' )
		{
			continue;
		}
		if ( !std::cin || tmp[0] == '\0' )
		{
			break;
		}
		else
		{
			words[i] = tmp;
		}
	}
	int total = i;

	if ( total > 0 )
	{
		std::cout << "Word List\n";
		for ( int i = 0; i < total; i++ )
		{
			std::cout << words[i][0] << ": " << words[i] << std::endl;
		}
		int shortest = 0;
		int first = 0;
		for ( i = 1; i < total; i++ )
		{
			if ( words[i].Size() < words[shortest].Size() )
			{
				shortest = i;
			}
			if ( words[i] < words[first] )
			{
				first = i;
			}
		}
		std::cout << "가장 짧은 단어 : " << words[shortest] << std::endl;
		std::cout << "사전 순 가장 앞 단어 : " << words[first] << std::endl;
		std::cout << MyString::GetCount() << "개의 Mystring 객체 사용\n";
	}
	else
	{
		std::cout << "입력금지\n";
	}
}

void Chapter12::UpgradeMyString()
{
	MyString s1( " and I am a C++ student." );
	MyString s2 = "영문 이름을 입력하십시오: ";
	MyString s3;
	std::cout << s2;
	std::cin >> s3;
	s2 = "My name is " + s3;
	std::cout << s2 << ".\n";
	s2 = s2 + s1;
	s2.StrToUpper();
	std::cout << "다음 문자열에는\n" << s2 << "\n문자 'A'가 " << s2.GetCountOf( 'A' ) << "개 들어있습니다.\n";

	s1 = "red";
	MyString rgb[3] = { MyString( s1 ), MyString( "green" ), MyString( "blue" ) };
	std::cout << "삼원색 입력 영어 : ";
	MyString answer;
	bool success = false;
	while ( std::cin >> answer )
	{
		answer.StrToLower();
		for ( int i = 0; i < 3; i++ )
		{
			if ( answer == rgb[i] )
			{
				std::cout << "맞았습니다!\n";
				success = true;
				break;
			}
		}
		if ( success )
		{
			break;
		}
		else
		{
			std::cout << "다시 입력하세요 : ";
		}
	}
	std::cout << "프로그램을 종료합니다.\n";
}


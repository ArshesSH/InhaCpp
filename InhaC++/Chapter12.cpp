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
	std::cout << "�̸� �Է� : ";
	std::cin >> name;

	std::cout << name << "�� ���� �ܾ� " << wordsSize << "�� �Է��ؿ�\n";
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
		std::cout << "���� ª�� �ܾ� : " << words[shortest] << std::endl;
		std::cout << "���� �� ���� �� �ܾ� : " << words[first] << std::endl;
		std::cout << MyString::GetCount() << "���� Mystring ��ü ���\n";
	}
	else
	{
		std::cout << "�Է±���\n";
	}
}

void Chapter12::UpgradeMyString()
{
	MyString s1( " and I am a C++ student." );
	MyString s2 = "���� �̸��� �Է��Ͻʽÿ�: ";
	MyString s3;
	std::cout << s2;
	std::cin >> s3;
	s2 = "My name is " + s3;
	std::cout << s2 << ".\n";
	s2 = s2 + s1;
	s2.StrToUpper();
	std::cout << "���� ���ڿ�����\n" << s2 << "\n���� 'A'�� " << s2.GetCountOf( 'A' ) << "�� ����ֽ��ϴ�.\n";

	s1 = "red";
	MyString rgb[3] = { MyString( s1 ), MyString( "green" ), MyString( "blue" ) };
	std::cout << "����� �Է� ���� : ";
	MyString answer;
	bool success = false;
	while ( std::cin >> answer )
	{
		answer.StrToLower();
		for ( int i = 0; i < 3; i++ )
		{
			if ( answer == rgb[i] )
			{
				std::cout << "�¾ҽ��ϴ�!\n";
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
			std::cout << "�ٽ� �Է��ϼ��� : ";
		}
	}
	std::cout << "���α׷��� �����մϴ�.\n";
}


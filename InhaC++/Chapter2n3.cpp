#include "Chapter2n3.h"

#include <iostream>
#include <climits>

// Test First std::cout function
void Chapter2::FirstEx()
{
	std::cout << "hello world!" << std::endl;
}

void Chapter2::SecondEx()
{
	int nInt = INT_MAX;
	short nShort = SHRT_MAX;
	long nLong = LONG_MAX;
	long long nLLong = LLONG_MAX;

	std::cout << "int = " << sizeof( int ) << "bytes\n";
	std::cout << "short = " << sizeof( nShort ) << "bytes\n";
	std::cout << "long = " << sizeof( nLong ) << "bytes\n";
	std::cout << "long long = " << sizeof( nLLong ) << "bytes\n";
	std::cout << std::endl;

	std::cout << "Max int = " << nInt << std::endl;
	std::cout << "Max short = " << nShort << std::endl;
	std::cout << "Max long = " << nLong << std::endl;
	std::cout << "Max long long = " << nLLong << std::endl;
	std::cout << "byte per bit = " << CHAR_BIT << std::endl;
}

void Chapter2::ExMorechar()
{
	char ch = 'M';
	int i = ch;
	std::cout << ch << "�� ASCII = " << i << "�̴�" << std::endl;
	std::cout << ch << " + 1 = ";
	ch++;
	i = ch;
	std::cout << ch << "'s ASCII = " << i << std::endl;
	std::cout.put( ch );
	std::cout.put( '!' );
	std::cout << std::endl;
}

void Chapter2::ExInit()
{
	std::cout.setf( std::ios_base::fixed, std::ios_base::floatfield );

	float tree = 3;
	int guess = 3.9832;
	int debt = 7.2E12;

	std::cout << " tree = " << tree << std::endl;
	std::cout << " guess = " << guess << std::endl;
	std::cout << " debt = " << debt << std::endl;
}

void Chapter2::Exercise1()
{
	std::cout << "Input height(cm) : ___cm\b\b\b\b\b";
	int height;
	std::cin >> height;

	const float heightMeter = (float)height / 100.0f;

	std::cout << "Meter: " << heightMeter << "m, centimeter: " << height << "cm" << std::endl;
}

void Chapter2::Exercise3()
{
	int latitudeDegree;
	int latitudeMinute;
	int latitudeSecond;

	std::cout << "������ ��, ��, �� ������ �Է��Ͻÿ�:" << std::endl;
	std::cout << "����, ������ �Է��Ͻÿ�:";
	std::cin >> latitudeDegree;
	std::cout << "������, �а��� �Է��Ͻÿ�:";
	std::cin >> latitudeMinute;
	std::cout << "������, �ʰ��� �Է��Ͻÿ�:";
	std::cin >> latitudeSecond;
	
	const float dms = latitudeDegree + latitudeMinute / 60.0f + latitudeSecond / 3600.0f;
	std::cout << latitudeDegree << "��, " << latitudeMinute << "��, " << latitudeSecond << "�� = " << dms << "��";
}

void Chapter2::Exercise5()
{
	long long populationWorld;
	long long populationAmerica;

	std::cout << "���� �α����� �Է��Ͻÿ�: ";
	std::cin >> populationWorld;
	std::cout << "�̱��� �α����� �Է��Ͻÿ�: ";
	std::cin >> populationAmerica;

	const float populationAmericaRate = (populationAmerica * 100.0f) / (float)populationWorld;
	std::cout << "���� �α������� �̱��� �����ϴ� ������ " << populationAmericaRate << "% �̴�." << std::endl;
}

void Chapter2::Exercise7()
{
	float gasConsumptionEU;
	std::cout << "������ �ֹ��� �Һ�(L/100Km) �Է� : ";
	std::cin >> gasConsumptionEU;

	const float gasConsumptionUSA = (62.14f / gasConsumptionEU * 3.875f);
	std::cout << "�̱��� �ֹ��� �Һ�(miles per gallon) = " << gasConsumptionUSA << "mpg" << std::endl;
}
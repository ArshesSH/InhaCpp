#include "Chapter4.h"

#include <iostream>
#include <string>
#include <memory>
#include <vector>
#include <array>

void Chapter4::InStr()
{
	constexpr int arrSize = 20;
	char name[arrSize];
	char dessert[arrSize];

	std::cout << "Input name: ";
	std::cin.getline( name, arrSize );
	std::cout << "Input dessert: ";
	std::cin.getline( dessert, arrSize );

	std::cout << "맛있는 " << name << "를 준비했습니다. " << dessert << "님!" << std::endl;
}

void Chapter4::NumStr()
{
	std::cout << "입주년 : ";
	int year;
	std::cin >> year;
	// get 입력으로 \n 제거
	//std::cin.get();
	//std::cin.ignore();
	std::cout << "도시 : ";
	char address[80];
	std::cin.getline( address, 80 );
	std::cout << "입주년 : " << year << std::endl;
	std::cout << "도시 : " << address << std::endl;
}

void Chapter4::StrType1()
{
	char charr1[20];
	char charr2[20] = "jaguar";

	std::string str1;
	std::string str2 = "panther";

	std::cout << "고양이과 동물 한 종 입력 : ";
	std::cin >> charr1;
	std::cout << "다른 고양이과 동물 한 종 입력 : ";
	std::cin >> str1;

	std::cout << "아래 동물들은 모두 고양이과입니다.\n";
	std::cout << charr1 << " " << charr2 << " " << str1 << " " << str2 << " " << std::endl;
}

void Chapter4::StrType2()
{
	std::string s1 = "penguin";
	std::string s2, s3;

	//std::getline( std::cin, s1 );

	std::cout << "string copy constructor\n";
	s2 = s1;
	std::cout << "s1 : " << s1 << ", s2 : " << s2 << std::endl;

	std::cout << "c스타일 문자열 대입 가능\n";
	s2 = "buzzard";
	std::cout << s2 << std::endl;
	std::cout << "+ 연산자\n";
	s3 = s1 + s2;
	std::cout << s3 << std::endl;
	std::cout << "+=연산자\n";
	std::cout << "s1 += s2 = ";
	s1 += s2;
	std::cout << s1 << std::endl;
	std::cout << "+= c string \n";
	s2 += "for a day";
	std::cout << s2 << std::endl;
}

void Chapter4::UseNew()
{
	int nights = 1001;
	int* pt = new int;
	*pt = 1001;

	std::cout << "nights 값 = ";
	std::cout << nights << ": 메모리 위치 " << &nights << std::endl;
	std::cout << "int 형";
	std::cout << "값 = " << *pt << ": 메모리 위치 = " << pt << std::endl;

	delete pt;	
	pt = nullptr;
}

void Chapter4::PtrStr()
{
	char animal[20] = "bear";
	const char* bird = "wren";
	char* ps;

	std::cout << animal << " and " << bird << std::endl;
	std::cout << "Input : ";
	std::cin >> animal;
	ps = animal;
	std::cout << ps << "s!\n";
	std::cout << "strcpy()이전\n";
	std::cout << reinterpret_cast<int*>(animal) << ": " << animal << std::endl;
	std::cout << reinterpret_cast<int*>(ps) << ": " << ps << std::endl;

	auto animalSize = strlen( animal ) + 1;
	ps = new char[animalSize];
	strcpy_s( ps, animalSize, animal );
	std::cout << "strcpy() 사용 후:\n";
	std::cout << reinterpret_cast<int*>(animal) << ": " << animal << std::endl;
	std::cout << reinterpret_cast<int*>(ps) << ": " << ps << std::endl;

	delete[] ps;
}

void Chapter4::DeleteChar()
{
	char* name;

	name = GetName();
	std::cout << reinterpret_cast<int*>(name) << ": " << name << std::endl;
	delete[] name;

	name = GetName();
	std::cout << reinterpret_cast<int*>(name) << ": " << name << std::endl;
	delete[] name;
}

void Chapter4::Choices()
{
	// c-style array
	double a1[4] = { 1.2, 2.4, 3.6, 4.8 };
	std::vector<double> a2(4);

	a2[0] = 1.0 / 3.0;
	a2[1] = 1.0 / 5.0;
	a2[2] = 1.0 / 7.0;
	a2[3] = 1.0 / 9.0;


}

void Chapter4::Exercise569()
{
	struct CandyBar
	{
		std::string name;
		float weight;
		int calorie;
	};

	// 5번
	CandyBar snack = { "Mocha Munch", 2.3, 350 };
	std::cout << "snack " << snack.name << ", " << snack.weight << ", " << snack.calorie << std::endl;

	// 6번
	CandyBar snackArr[3];
	for ( int i = 0; i < 3; i++ )
	{
		std::cout << "\nInput snack's name : ";
		std::cin >> snackArr[i].name;
		std::cout << "Input snack's weight : ";
		std::cin >> snackArr[i].weight;
		std::cout << "Input snack's calorie : ";
		std::cin >> snackArr[i].calorie;
		std::cout << std::endl;
	}

	for ( int i = 0; i < 3; i++ )
	{
		std::cout << "snack[" << i << "]'s name : " << snackArr[i].name << std::endl;
		std::cout << "snack[" << i << "]'s weight : " << snackArr[i].weight << std::endl;
		std::cout << "snack[" << i << "]'s calorie : " << snackArr[i].calorie << std::endl;
	}

	// 9번
	CandyBar* pSnack = new CandyBar[3];
	for ( int i = 0; i < 3; i++ )
	{
		std::cout << "\nInput snack's name : ";
		std::cin >> pSnack[i].name;
		std::cout << "Input snack's weight : ";
		std::cin >> pSnack[i].weight;
		std::cout << "Input snack's calorie : ";
		std::cin >> pSnack[i].calorie;
		std::cout << std::endl;
	}

	for ( int i = 0; i < 3; i++ )
	{
		std::cout << "snack[" << i << "]'s name : " << pSnack[i].name << std::endl;
		std::cout << "snack[" << i << "]'s weight : " << pSnack[i].weight << std::endl;
		std::cout << "snack[" << i << "]'s calorie : " << pSnack[i].calorie << std::endl;
	}

	delete[] pSnack;
}

void Chapter4::Exercise7()
{
	struct PizzaInfo
	{
		char companyName[BUFSIZ];
		float diameter;
		float weight;
	};

	PizzaInfo tmpPizza;
	std::cout << "- Input Pizza Data -\n" << "Input Pizza Company : ";
	std::cin.getline( tmpPizza.companyName, BUFSIZ );
	std::cout << "Input Pizza's diameter : ";
	std::cin >> tmpPizza.diameter;
	std::cout << "Input Pizza's weight : ";
	std::cin >> tmpPizza.weight;

	std::cout << "Pizza Company : " << tmpPizza.companyName << "\nDiameter : " << tmpPizza.diameter <<
		"\nWeight : " << tmpPizza.weight << std::endl;
}

void Chapter4::Exercise8()
{
	struct PizzaInfo
	{
		char companyName[BUFSIZ];
		float diameter;
		float weight;
	};

	PizzaInfo* pTmpPizza = new PizzaInfo;

	std::cout << "- Input Pizza Data -\n" << "Input Pizza's diameter : ";
	std::cin >> pTmpPizza->diameter;
	std::cin.get();
	std::cout << "Input Pizza Company : ";
	std::cin.getline( pTmpPizza->companyName, BUFSIZ );
	std::cout << "Input Pizza's weight : ";
	std::cin >> pTmpPizza->weight;

	std::cout << "Pizza Company : " << pTmpPizza->companyName << "\nDiameter : " << pTmpPizza->diameter <<
		"\nWeight : " << pTmpPizza->weight << std::endl;
}


char* Chapter4::GetName()
{
	char tmp[80];
	std::cout << "이름 입력: ";
	std::cin >> tmp;
	auto size = strlen( tmp ) + 1;
	char* pChArr = new char[size];
	
	strcpy_s( pChArr, 80, tmp );

	return pChArr;
}

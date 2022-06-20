#include "Day0620.h"

#include <iostream>
#include <fstream>
#include <string>

#include "Encoder.h"
#include "Decoder.h"

/*
* Q1.Encoding
* 파일 내 모든 바이트에 임의의 수를 더하도록 부호화 하라
* 사용자가 입력 파일 이름과 출력 파일 이름을 입력하면
* 입력파일의 암호화된 버전을 출력파일로 저장하는 프로그램을 작성하라
* 
* ex Input Source filename : source.txt
*	 Input Encoding filename : encoding.txt
* 더해진 임의 수를 encoding.txt 맨 앞에 기입하도록 한다.
* 
*/

void Day0620::Question1()
{
	std::cout << "Input Source filename :";
	std::string srcName;
	std::cin >> srcName;
	std::cout << "Input Encoding filename : ";
	std::string destName;
	std::cin >> destName;
	
	Encoder encoder( srcName, destName );
	encoder.EncodeFile();
}

/*
* Q2. Decoding
* 암호화된 파일을 복호화 하는 프로그램을 작성하라.
* 사용자가 입력 파일 이름과 출력 파일 이름을 입력하면
* 입력파일의 복호화 버전을 출력파일로 저장하는 프로그램을 작성하라
* 
* ex Input Source filename : source.txt
*	 Input Decoding filename : dest.txt
* 더해진 임의 수를 읽어 decoding 하라.
* 
*/

void Day0620::Question2()
{
	std::cout << "Input Source filename :";
	std::string srcName;
	std::cin >> srcName;
	std::cout << "Input Decoding filename : ";
	std::string destName;
	std::cin >> destName;

	Decoder decoder( srcName, destName );
	decoder.DecodeFile();
}



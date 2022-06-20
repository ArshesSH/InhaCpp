#include "Day0620.h"

#include <iostream>
#include <fstream>
#include <string>

#include "Encoder.h"
#include "Decoder.h"

/*
* Q1.Encoding
* ���� �� ��� ����Ʈ�� ������ ���� ���ϵ��� ��ȣȭ �϶�
* ����ڰ� �Է� ���� �̸��� ��� ���� �̸��� �Է��ϸ�
* �Է������� ��ȣȭ�� ������ ������Ϸ� �����ϴ� ���α׷��� �ۼ��϶�
* 
* ex Input Source filename : source.txt
*	 Input Encoding filename : encoding.txt
* ������ ���� ���� encoding.txt �� �տ� �����ϵ��� �Ѵ�.
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
* ��ȣȭ�� ������ ��ȣȭ �ϴ� ���α׷��� �ۼ��϶�.
* ����ڰ� �Է� ���� �̸��� ��� ���� �̸��� �Է��ϸ�
* �Է������� ��ȣȭ ������ ������Ϸ� �����ϴ� ���α׷��� �ۼ��϶�
* 
* ex Input Source filename : source.txt
*	 Input Decoding filename : dest.txt
* ������ ���� ���� �о� decoding �϶�.
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



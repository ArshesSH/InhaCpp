#include "Encoder.h"

#include <random>
#include <iostream>
#include <fstream>

Encoder::Encoder( const std::string& srcName, const std::string& encodedName )
	:
	srcName( srcName ),
	encodedName( encodedName )
{
	std::random_device rd;
	std::mt19937 rng( rd() );
	std::uniform_int_distribution<int> randNumGen( 1, maxRand );
	
	randNum = randNumGen( rng );
}

void Encoder::EncodeFile()
{
	std::ifstream fileIn( srcName, std::ios_base::binary );
	if ( fileIn )
	{
		// Open file and Set contents Size
		std::string randNumStr = std::to_string(randNum) + "\n";

		std::string contents;
		fileIn.seekg( 0, std::ios_base::end );
		contents.resize( fileIn.tellg() );
		const int fileSize = contents.size();
		fileIn.seekg( 0, std::ios_base::beg );
		fileIn.read( &contents[0], fileSize );
		fileIn.close();

		// Encode
		for ( auto& e : contents )
		{
			e = EncodeBinary(e);
		}

		const std::string encodedStr = randNumStr + contents;
		std::ofstream fileOut( encodedName, std::ios_base::binary );
		fileOut.write( &encodedStr[0], fileSize + (int)randNumStr.size() );
		fileOut.close();

		std::cout << "File Successfully encoded\n";
	}
	else
	{
		std::cout << "File name : " << srcName << "is not exist!\n";
	}
	std::cout << std::endl;
}

unsigned char Encoder::EncodeBinary( unsigned char c)
{
	return c + randNum;
}

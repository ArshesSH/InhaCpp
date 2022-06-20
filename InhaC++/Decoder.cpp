#include "Decoder.h"

#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>

Decoder::Decoder( const std::string& srcName, const std::string& destName )
	:
	srcName( srcName ),
	destName( destName )
{
}

void Decoder::DecodeFile()
{
	std::ifstream fileIn( srcName, std::ios_base::binary );
	if ( fileIn )
	{
		// Get First Line for Encode Num
		std::string encodeNumStr;
		std::getline( fileIn, encodeNumStr );
		encodeNum = std::stoi( encodeNumStr );
		const size_t encodeNumStrSize = encodeNumStr.size();

		// Get Contents
		std::string fileStr;
		fileIn.seekg( 0, std::ios_base::end );
		fileStr.resize( fileIn.tellg() );
		fileIn.seekg( 0, std::ios_base::beg );
		fileIn.read( &fileStr[0], fileStr.size() );
		fileIn.close();

		const size_t contentsSize = fileStr.size() - encodeNumStrSize - 1;
		std::string contents = fileStr.substr( encodeNumStrSize + 1, contentsSize );
		for ( auto& e : contents )
		{
			e = DecodeBinary( e );
		}
		std::ofstream fileOut( destName, std::ios_base::binary );
		fileOut.write( &contents[0], contentsSize );
		fileOut.close();
		
		std::cout << "File sucessfully decoded!\n";
	}
	else
	{
		std::cout << "Src File name : " << srcName << "is not exist!\n";
	}
	std::cout << std::endl;
}

unsigned char Decoder::DecodeBinary( unsigned char c )
{
	return c - encodeNum;
}

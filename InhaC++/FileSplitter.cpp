#include "FileSplitter.h"

#include <fstream>
#include <memory>
#include <iostream>
#include <cassert>


FileSplitter::FileSplitter( const std::string& filename )
	:
	filename(filename)
{
}

void FileSplitter::Split( size_t splitSize )
{
	std::fstream fs( filename, std::ios_base::binary | std::ios_base::in | std::ios_base::out );
	assert( fs );
	if ( !fs.is_open() )
	{
		return;
	}

	// Get File Size
	auto pos = fs.tellg();
	fs.seekg( 0, std::ios_base::end );
	originSize = fs.tellg() - pos;
	fs.seekg( std::ios_base::beg );

	std::unique_ptr<char[]> datas = std::make_unique<char[]>( splitSize );

	const int splitCnt = originSize / splitSize;
	const int remain = originSize % splitSize;

	for ( int i = 0; i < originSize; ++i )
	{

	}

}

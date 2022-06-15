#pragma once

#include <fstream>
#include <string>
#include <vector>
#include <cassert>

class InputReader
{
public:
	InputReader(const std::wstring& filename)
		:
		filename(filename)
	{}

	std::vector<std::string> GetLineVector() const
	{
		std::vector<std::string> list;
		std::ifstream input( filename );

		assert( !input.fail() );

		for ( std::string str; std::getline( input, str ); )
		{
			if ( str.empty() )
			{
				continue;
			}
			list.push_back( str );
		}
		input.close();

		return list;
	}

	std::string GetSingleLine() const
	{
		std::ifstream input( filename );
		assert( !input.fail() );

		std::string str;
		std::getline( input, str );
		return std::move( str );
	}

private:
	std::wstring filename;
};
#pragma once

#include <string>

class FileSplitter
{
public:
	FileSplitter( const std::string& filename );
	
	void Split(size_t splitSize);
private:
	const std::string filename;
	size_t originSize = 0;
};


#pragma once

#include <string>

class Decoder
{
public:
	Decoder( const std::string& srcName, const std::string& destName );
	void DecodeFile();
private:
	inline unsigned char DecodeBinary(unsigned char c);
private:
	const std::string srcName;
	const std::string destName;
	int encodeNum = 0;
};


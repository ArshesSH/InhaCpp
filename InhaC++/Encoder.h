#pragma once

#include <string>

class Encoder
{
public:
	Encoder( const std::string& srcName, const std::string& encodedName );
	void EncodeFile();

private:
	inline unsigned char EncodeBinary( unsigned char c);

private:
	static constexpr int maxRand = 100;
	const std::string srcName;
	const std::string encodedName;
	int randNum;
};


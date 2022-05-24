#pragma once

#include <string>
#include <vector>

class Chapter5n6
{
public:
	static void ExPalindrome();
	static void PrintPyramid();
	static void Exercise7();
	static void Exercise8();
	static void Question1();
	static void Question2();
	static void Excctypes();
	static void ExFileOutStream();
	static void ExFileInStream();
	static void Exercise4();
private:
	struct BopData
	{
		std::string fullname;
		std::string title;
		std::string id;
		int preference = -1;
	};

	static bool FindPalindrome( const std::string str );
	static char Exercise4InputMenu();
	static void Exercise4Register();
	static void Exercise4SearchFullname();
	static void Exercise4SearchTitle();
	static void Exercise4SearchId();
	static void Exercise4SearchPreference();
	static void Exercise4LoadFile( std::vector<BopData>& list );
	static size_t Exercise4FindData( std::string& str, const char* findStr );
};
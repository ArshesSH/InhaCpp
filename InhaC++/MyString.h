#pragma once

#include <iostream>

class MyString
{
public:
	// Default Constructor
	MyString();
	MyString( const char* s );

	// Destructor
	~MyString();

	// Copy Constructor
	MyString( const MyString& src );

	// Copy Assignment
	MyString& operator=( const MyString& src );
	MyString& operator=( const char* s );

	char& operator[]( int i );
	const char& operator[]( int i ) const;
	bool operator<( const MyString& rhs );
	bool operator>( const MyString& rhs );
	bool operator==( const MyString& rhs );
	MyString operator+( const MyString& rhs ) const;

	static int GetCount();
	size_t Size() const;
	void StrToLower();
	void StrToUpper();
	size_t GetCountOf( char c );

	friend MyString operator+( const char* const lhs, const MyString& rhs );
	friend std::ostream& operator<<( std::ostream& os, const MyString& s );
	friend std::istream& operator>>( std::istream& is, MyString& s );
	
public:
	static constexpr size_t BufferSize = 512;
private:
	static int count;
	size_t length;
	char* str;
};


#include "MyString.h"

#include <cctype>

int MyString::count = 0;

MyString::MyString()
{
    length = 1;
    str = new char[1];
    str[0] = '\0';
    count++;
    //std::cout <<"     " << count << ": " << str << " Created by Default Constructor\n";
}

MyString::MyString( const char* s )
{
    length = std::strlen( s );
    str = new char[length + 1];
    strcpy_s( str, length+1, s );
    count++;
    //std::cout << "     " << count << ": " << str << " Created by Constructor\n";
}

MyString::~MyString()
{
    //std::cout << "     " << str << " Destroy by Destructor\n";
    --count;
    //std::cout << "     " << "³²Àº °´Ã¼ ¼ö : " << count << std::endl;
    delete[] str;
    str = nullptr;
}

MyString::MyString( const MyString& src )
{
    length = src.length;
    str = new char[length + 1];
    strcpy_s( str, length + 1, src.str );
    count++;
    //std::cout << "     " << count << ": " << str << " Created by Copy Constructor \n";
}

MyString& MyString::operator=( const MyString& src )
{
    if ( this == &src )
    {
        return *this;
    }
    delete[] str;
    str = nullptr;
    length = src.length;
    str = new char[length + 1];
    strcpy_s( str, length + 1, src.str );
    //std::cout << "     " << count << ": " << str << " Created by Copy Assignment \n";
    return *this;
}

MyString& MyString::operator=( const char* s )
{
    delete[] str;
    str = nullptr;
    length = std::strlen( s );
    str = new char[length + 1];
    strcpy_s( str, length + 1, s );
    //std::cout << "     " << count << ": " << str << " Created by Copy Assignment \n";
    return *this;
}

char& MyString::operator[]( int i )
{
    return str[i];
}

const char& MyString::operator[]( int i ) const
{
    return str[i];
}

bool MyString::operator<( const MyString& rhs )
{
    return strcmp(str, rhs.str) < 0;
}

bool MyString::operator>( const MyString& rhs )
{
    return rhs.str < str;
}

bool MyString::operator==( const MyString& rhs )
{
    return strcmp( str, rhs.str ) == 0;
}


MyString MyString::operator+( const MyString& rhs ) const
{
    const size_t concatSize = length + rhs.length + 1;
    char* s = new char[concatSize];
    strcpy_s( s, concatSize, str );
    strcat_s( s, concatSize, rhs.str );
    MyString addStr( s );
    delete[] s;
    return addStr;
}

int MyString::GetCount()
{
    return count;
}

size_t MyString::Size() const
{
    return length;
}

void MyString::StrToLower()
{
    for ( size_t i = 0; i < length; ++i )
    {
        str[i] = tolower( str[i] );
    }
}

void MyString::StrToUpper()
{
    for ( size_t i = 0; i < length; ++i )
    {
        str[i] = toupper( str[i] );
    }
}

size_t MyString::GetCountOf( char c )
{
    size_t cnt = 0;
    for ( size_t i = 0; i < length; ++i )
    {
        if ( str[i] == c )
        {
            ++cnt;
        }
    }
    return cnt;
}

MyString operator+( const char* const lhs, const MyString& rhs )
{
    const size_t concatSize = strlen( lhs ) + rhs.length + 1;
    char* s = new char[concatSize];
    strcpy_s( s, concatSize, lhs );
    strcat_s( s, concatSize, rhs.str );
    MyString addStr( s );
    delete[] s;
    return addStr;
}

std::ostream& operator<<( std::ostream& os, const MyString& s )
{
    os << s.str;
    return os;
}

std::istream& operator>>( std::istream& is, MyString& s )
{
    char temp[MyString::BufferSize];
    is.get( temp, MyString::BufferSize );
    if ( is )
    {
        s = temp;
    }
    while ( is && is.get() != '\n' )
    {
        continue;
    }
    return is;
}

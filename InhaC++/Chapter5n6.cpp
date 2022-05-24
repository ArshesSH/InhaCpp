#include "Chapter5n6.h"

#include <iostream>
#include <cstring>
#include <cctype>
#include <fstream>
#include <algorithm>


void Chapter5n6::ExPalindrome()
{
    std::string str;
    std::cout << "Input String : ";
    std::cin >> str;

    std::cout << str << "�� ȸ��";
    if ( FindPalindrome(str) )
    {
        std::cout << "�Դϴ�." << std::endl;
    }
    else
    {
        std::cout << "�� �ƴմϴ�." << std::endl;
    }
}

/*
* Q3
* 1~10���� ���� �Է� �Ƕ�̵� ��� ���α׷�
* ex) INput 5  / o == space
* oooo1
* ooo212
* oo32123
* o4321234
* 543212345
*/
void Chapter5n6::PrintPyramid()
{
    int inputNum = 1;
    do
    {
        std::cout << "Input Num(1~10) : ";
        std::cin >> inputNum;
    } while ( inputNum < 1 || inputNum > 10 );


    // for each line
    for ( int line = 1; line <= inputNum; ++line )
    {
        // Print Space at line
        for ( int iSpace = line; iSpace < inputNum; ++iSpace )
        {
            std::cout << " ";
        }

        // Increase or Decrease number
        for ( int num = line, numCnt = 0; numCnt < (line * 2) - 1; ++numCnt)
        {
            std::cout << num;
            if ( numCnt < line - 1 )
            {
                --num;
            }
            else
            {
                ++num;
            }
        }
        std::cout << std::endl; 
    }
}

void Chapter5n6::Exercise7()
{
    // Dynamic array
    struct CarInfo
    {
        std::string companyName;
        int year = 0;
    };

    int carCnt;
    std::cout << "�� ���� ���� ������� �����Ͻðڽ��ϱ�? ";
    std::cin >> carCnt;

    CarInfo* pCarList = new CarInfo[carCnt];
    for ( int i = 0; i < carCnt; ++i )
    {
        std::cout << "�ڵ��� #" << i << ":\n";
        std::cout << "���۾�ü: ";
        std::cin >> pCarList->companyName;
        std::cout << "���۳⵵: ";
        std::cin >> pCarList->year;
    }

    std::cout << "���ϰ� �����ϰ� �ִ� �ڵ��� ����� ������ �����ϴ�.\n";
    for ( int i = 0; i < carCnt; ++i )
    {
        std::cout << pCarList->year << "���� " << pCarList->companyName << std::endl;
    }

    delete[] pCarList;

    // Vector
    struct CarInfoForVec
    {
        std::string companyName;
        int year = 0;
    };

    int carCount;
    std::cout << "�� ���� ���� ������� �����Ͻðڽ��ϱ�? ";
    std::cin >> carCount;

    std::vector<CarInfoForVec> carList;
    for ( int i = 0; i < carCount; ++i )
    {
        std::string company;
        int year;
        std::cout << "�ڵ��� #" << i << ":\n";
        std::cout << "���۾�ü: ";
        std::cin >> company;
        std::cout << "���۳⵵: ";
        std::cin >> year;

        carList.emplace_back( CarInfoForVec{ company, year } );
    }

    std::cout << "���ϰ� �����ϰ� �ִ� �ڵ��� ����� ������ �����ϴ�.\n";

    for ( auto e : carList )
    {
        std::cout << e.year << "���� " << e.companyName << std::endl;
    }

}

void Chapter5n6::Exercise8()
{
    char tmpStr[BUFSIZ];
    int cnt = 0;
    std::cout << "���� �ܾ���� �Է��Ͻʽÿ� (�������� done�� �Է�) : ";
    while ( strcmp( tmpStr, "done" ) != 0 )
    {
        std::cin >> tmpStr;
        cnt++;
    }

    std::cout << cnt - 1 << std::endl;
}

bool Chapter5n6::FindPalindrome( const std::string str )
{
    for ( int startPos = 0, endPos = str.size() - 1; startPos < endPos; startPos++, endPos--  )
    {
        if ( str[startPos] != str[endPos] )
        {
            return false;
        }
    }
    return true;
}


/*
* ������� ���ӵ� a(m/s^2) �̷��ӵ� v(m/s)
* �̷� �ּ� Ȱ�� �Ÿ� ��� ���α׷�
* �Ÿ� = v^2 / 2a
* input 60, 3.5 -> 514.286
*/
void Chapter5n6::Question1()
{
    float speed;
    float accelation;

    std::cout << "Input Speed(m/s) and Accelation(m/s^2) : ";
    std::cin >> speed >> accelation;

    const float minTaxing = powf( speed, 2 ) / (2 * accelation);
    std::cout << "Minimum Taxing distance : " << minTaxing << std::endl;
}

/*
* ���� (x1, y1) , (x2, y2)�� �Է¹޾� ���� ������ �Ÿ��� ����ϴ� ���α׷�
* sqrt((x2 - x1)^2 + (y2 - y1)^2)
* 1.5 -3.4 , 4 5 -> 8,7641
*/



void Chapter5n6::Question2()
{
    struct Vec2
    {
        int x = 0;
        int y = 0;

        Vec2& operator-=( const Vec2& rhs )
        {
            this->x -= rhs.x;
            this->y -= rhs.y;
            return *this;
        }

        Vec2 operator-( const Vec2& rhs )
        {
            return *this -= rhs;
        }

        float  GetLengthSq() const
        {
            return x * x + y * y;
        }

        float GetLength() const
        {
            return std::sqrtf( (float)GetLengthSq() );
        }
    };

    float x1, x2, y1, y2;
    std::cout << "Input Point1(x, y) : ";
    std::cin >> x1 >> y1;
    std::cout << "Input Point2(x, y) : ";
    std::cin >> x2 >> y2;

    const float distance = std::sqrtf( std::powf( (x2 - x1), 2 ) + std::powf( y2 - y1, 2 ) );
    std::cout << "Distance = " << distance << std::endl;
}

void Chapter5n6::Excctypes()
{
    std::cout << "�м��� �ؽ�Ʈ�� �Է��Ͻÿ�. "
        "�Է��� ���� @���� ǥ���Ͻʽÿ�.\n";
    char ch;
    int whitespace = 0;
    int digits = 0;
    int chars = 0;
    int punct = 0;
    int others = 0;

    std::cin.get( ch );
    for ( std::cin.get( ch ); ch != '@'; std::cin.get( ch ) )
    {
        if ( std::isalpha( ch ) )
        {
            chars++;
        }
        else if ( std::isspace( ch ) )
        {
            whitespace++;
        }
        else if ( std::isdigit( ch ) )
        {
            digits++;
        }
        else if ( std::ispunct( ch ) )
        {
            punct++;
        }
        else
        {
            others++;
        }
    }

    std::cout << "���ĺ� ���� " << chars << ", "
        << "���� " << whitespace << ", "
        << "���� " << digits << ", "
        << "������ " << punct << ", "
        << "��Ÿ" << others << std::endl;
}

void Chapter5n6::ExFileOutStream()
{
    char automobile[50];
    int year;
    double a_price;
    double d_price;

    std::ofstream outFile;
    outFile.open( "carinfo.txt" );
    
    std::cout << "�ڵ��� ����Ŀ�� ������ �Է��Ͻÿ�: ";
    std::cin.getline( automobile, 50 );
    std::cout << "������ �Է��Ͻÿ�:  ";
    std::cin >> year;
    std::cout << "���� ������ �Է��Ͻÿ�: ";
    std::cin >> a_price;
    d_price = 0.913 * a_price;

    std::cout << std::fixed;
    std::cout.precision( 2 );
    outFile.setf( std::ios_base::showpoint );
    outFile << "����Ŀ�� ����: " << automobile << std::endl;
    outFile << "���� " << year << std::endl;
    outFile << "���� ���� $" << a_price << std::endl;
    outFile << "���� ���� $" << d_price << std::endl;

    outFile.close();
}

void Chapter5n6::ExFileInStream()
{
    std::string filename;
    std::cout << "Input file name : ";
    std::getline( std::cin, filename );

    std::ifstream inFile( filename );
    if ( !inFile.is_open() )
    {
        std::cout << "Can't open file" << std::endl;
        exit( EXIT_FAILURE );
    }

    double value;
    double sum = 0.0;
    int count = 0;

    for ( inFile >> value; inFile.good(); ++count)
    {
        sum += value;
        inFile >> value;
    }
    if ( inFile.eof() )
    {
        std::cout << "���� ��" << std::endl;
    }
    else if ( inFile.fail() )
    {
        std::cout << "������ ����ġ" << std::endl;
    }
    else
    {
        std::cout << "����" << std::endl;
    }

    if ( count == 0 )
    {
        std::cout << "������ ����" << std::endl;
    }
    else
    {
        std::cout << "���� �׸� ���� : " << count << std::endl;
        std::cout << "�հ� : " << sum << std::endl;
        std::cout << "���: " << sum / count << std::endl;
    }
    inFile.close();
}

void Chapter5n6::Exercise4()
{
    enum class BopMenu
    {
        Register = 'a',
        Fullname,
        Title,
        Id,
        Preference,
        Exit = 'q'
    };

    char menuInput;
    std::vector<BopData> bopList;
    do
    {
        menuInput = Exercise4InputMenu();

        switch ( menuInput )
        {
        case (int)BopMenu::Register:
            Exercise4Register();
            break;
        case (int)BopMenu::Fullname:
            Exercise4SearchFullname();
            break;
        case (int)BopMenu::Title:
            Exercise4SearchTitle();
            break;
        case (int)BopMenu::Id:
            Exercise4SearchId();
            break;
        case (int)BopMenu::Preference:
            Exercise4SearchPreference();
            break;
        case (int)BopMenu::Exit:
            std::cout << "��� �����մϴ�\n";
            break;
        default:
            std::cout << "Please Input valid menu!!!\n";
        }
    } while ( menuInput != (char)BopMenu::Exit );

}

char Chapter5n6::Exercise4InputMenu()
{
    char menuInput;
    std::cout << "\nManagement Benevolent Order of Programmers\n"
        << "---- BOP Menu ----\n"
        << "a. Save BOP Data  b. Search by Fullname  c. Search by Title\n"
        << "d. Search by ID  e. Search by preference  q. Exit" << std::endl;
    std::cin >> menuInput;
    std::cin.get();
    // Check is Input Upper than change to lower
    if ( std::isupper( menuInput ) )
    {
        menuInput = std::tolower( menuInput );
    }

    return menuInput;
}

void Chapter5n6::Exercise4Register()
{
    BopData bop;
    std::cout << "\nInput fullname : ";
    std::getline( std::cin, bop.fullname );
    std::cout << "Input title : ";
    std::getline( std::cin, bop.title );
    std::cout << "Input id : ";
    std::getline( std::cin, bop.id );

    while ( bop.preference < 0 || bop.preference > 2 )
    {
        std::cout << "Input preference(0:Fullname 1:Title 2:ID) : ";
        std::cin >> bop.preference;
    }

    std::ofstream file( "bopdata.txt", std::ofstream::app );
    file << "F:" << bop.fullname << " ";
    file << "T:" << bop.title << " ";
    file << "I:" << bop.id << " ";
    file << "P:" << bop.preference << std::endl;
    file.close();
}

void Chapter5n6::Exercise4SearchFullname()
{
    std::vector<BopData> bopList;
    Exercise4LoadFile( bopList );
    for ( auto e : bopList )
    {
        std::cout << e.fullname << std::endl;
    }
}

void Chapter5n6::Exercise4SearchTitle()
{
    std::vector<BopData> bopList;
    Exercise4LoadFile( bopList );
    for ( auto e : bopList )
    {
        std::cout << e.title << std::endl;
    }
}

void Chapter5n6::Exercise4SearchId()
{
    std::vector<BopData> bopList;
    Exercise4LoadFile( bopList );
    for ( auto e : bopList )
    {
        std::cout << e.id << std::endl;
    }
}

void Chapter5n6::Exercise4SearchPreference()
{
    std::vector<BopData> bopList;
    Exercise4LoadFile( bopList );
    for ( auto e : bopList )
    {
        std::string target;
        switch ( e.preference )
        {
        case 0:
            target = e.fullname;
            break;
        case 1:
            target = e.title;
            break;
        case 2:
            target = e.id;
            break;
        }
        std::cout << target << std::endl;
    }
}

void Chapter5n6::Exercise4LoadFile( std::vector<BopData>& list )
{
    BopData bop;

    std::ifstream file( "bopdata.txt" );
    if ( !file.is_open() )
    {
        std::cout << "Fail to open file!!!\n";
        exit( EXIT_FAILURE );
    }
    std::string strLine;
    
    for ( std::getline( file, strLine ); file.good(); std::getline( file, strLine ))
    {
        const auto posF = Exercise4FindData( strLine, "F:" ) + 2;
        const auto posT = Exercise4FindData( strLine, "T:" ) + 2;
        const auto posI = Exercise4FindData( strLine, "I:" ) + 2;
        const auto posP = Exercise4FindData( strLine, "P:" ) + 2;

        bop.fullname = strLine.substr( posF, posT - posF - 3 );
        bop.title = strLine.substr( posT, posI - posT - 3 );
        bop.id = strLine.substr( posI, posP - posI - 3 );
        bop.preference = std::stoi( strLine.substr( posP, strLine.size() - posP ) );

        list.push_back( bop );
    }
    file.close();
}

size_t Chapter5n6::Exercise4FindData( std::string& str, const char* findStr )
{
    auto pos = str.find( findStr );
    if ( pos == std::string::npos )
    {
        std::cout << "Fail to Find "<< findStr << " data!!!\n";
        exit( EXIT_FAILURE );
    }
    return pos;
}

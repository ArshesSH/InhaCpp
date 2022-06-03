#include "Account.h"

#include <iostream>

Account::Account( const std::string& name, const std::string& number)
	:
	name(name),
	number(number)
{
}

void Account::Print() const
{
	std::cout << "¿¹±ÝÁÖ : " << name
		<< "\n°èÁÂ ¹øÈ£ : " << number
		<< "\nÀÜ¾× : " << balance << "\n" << std::endl;
}

void Account::Deposit( int amount )
{
	balance += amount;
}

void Account::DoWithdraw()
{
	balance = nextBalance;
}

bool Account::CheckWithdraw( int amount )
{
	nextBalance = balance;
	nextBalance -= amount;
	if ( nextBalance >= 0 )
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool Account::IsSameNumber( const std::string& n ) const
{
	return number == n;
}

int Account::GetBalance() const
{
	return balance;
}

#include "Account.h"

#include <iostream>
#include <limits>

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

void Account::DoDeposit( int amount )
{
	balance += amount;
}

void Account::DoWithdraw()
{
	balance = nextBalance;
}

bool Account::CheckInputAmount( int amount )
{
	if ( amount <= 0 || amount + balance >= LLONG_MAX )
	{
		return false;
	}
	return true;
}

bool Account::CheckWithdraw( int amount ) 

{
	nextBalance = balance;
	nextBalance -= amount;
	if ( nextBalance >= 0 )
	{
		return true;
	}
	return false;
}

bool Account::IsSameNumber( const std::string& n ) const
{
	return number == n;
}

long long int Account::GetBalance() const
{
	return balance;
}

#pragma once

#include <string>

class Account
{
public:
	Account( const std::string& name, const std::string& number );
	
	void Print() const;
	void DoDeposit( int amount );
	void DoWithdraw();
	bool CheckInputAmount( int amount );
	bool CheckWithdraw( int amount );
	bool IsSameNumber( const std::string& n ) const;
	long long int GetBalance() const;
private:
	std::string name;
	std::string number;
	long long int balance = 0;
	long long int nextBalance = 0;
};

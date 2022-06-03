#pragma once

#include <string>

class Account
{
public:
	Account( const std::string& name, const std::string& number );
	
	void Print() const;
	void Deposit( int amount );
	void DoWithdraw();
	bool CheckWithdraw( int amount );
	bool IsSameNumber( const std::string& n ) const;
	int GetBalance() const;
private:
	std::string name;
	std::string number;
	int balance = 0;
	int nextBalance = 0;
};

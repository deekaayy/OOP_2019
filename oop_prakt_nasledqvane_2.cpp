#include "pch.h"
#include <iostream>
#include<cassert>
class Account
{
private:
	size_t accountNumber;
	char* accountOwnerName;
	void del()
	{
		delete[] accountOwnerName;
	}
	void copy(const Account& other)
	{
		this->accountBalance = other.accountBalance;
		strcpy(this->accountOwnerName, other.accountOwnerName);
		this->accountBalance = other.accountBalance;
	}
protected:
	double accountBalance;
	void credit(double val)
	{
		accountBalance += val;
	}
	void debit(double val)
	{
		if (accountBalance - val < 0)
		{
			std::cout << "Insufficient balance!"; return;
		}
		else
		{
			accountBalance -= val;
		}
	}
public:
	double getBalance() const
	{
		return accountBalance;
	}
	void setBalance(double bal)
	{
		accountBalance = bal;
	}
	void setOnwerName(const char* name)
	{
		assert(accountOwnerName);
		if (!name)
		{
			name = "";
		}
		delete[] accountOwnerName;
		accountOwnerName = new char[strlen(name) + 1];
		strcpy(accountOwnerName, name);
	}
	const char* getOwnerName() const
	{
		return accountOwnerName;
	}
	void setAccountNumber(size_t num) 
	{
		accountNumber = num;
	}
	size_t getAccountNumber() const
	{
		return accountNumber;
	}
	Account(size_t accountNumb = 00000, const char* ownerName = "", double balance=000) :accountNumber(accountNumb), accountBalance(balance)
	{
		strcpy(accountOwnerName, ownerName);
	}
	~Account()
	{
		del();
	}
	Account(const Account& other)
	{
		if (this != &other)
		{
			del();
			copy(other);
		}
	}
	Account& operator=(const Account& other)
	{
		if (this != &other)
		{
			del();
			copy(other);
		}
		return *this;
	}
};

class SavingsAccount: protected Account
{
private:
	double interestRate;
public:
	SavingsAccount(size_t accountNumb = 00000, const char* ownerName = "", double balance = 000.0, double interest=0.00):Account(accountNumb,ownerName,balance), interestRate(interest) {}
	SavingsAccount(const SavingsAccount& other)
	{
		Account((Account)other); 
		this->interestRate = other.interestRate;
	}
	SavingsAccount& operator=(const SavingsAccount& other)
	{
		Account((Account)other);
		this->interestRate = other.interestRate;
		return *this;
	}
	double calculateInterest()
	{
		return accountBalance*interestRate;
	}
};

class CheckingAccount : protected Account
{
private:
	double fee;
public:
	CheckingAccount(size_t accountNumb = 00000, const char* ownerName = "", size_t balance = 000, double _fee=0.50):Account(accountNumb, ownerName, balance), fee(_fee) {}
	CheckingAccount(const CheckingAccount& other)
	{
		Account((Account)other);
		fee = other.fee;
	}
	CheckingAccount& operator=(const CheckingAccount& other)
	{
		Account((Account)other);
		this->fee = other.fee;
		return *this;
	}
	void credit(size_t val)
	{
		Account::credit(val);
		accountBalance -= fee;
	}
	void debit(size_t val)
	{
		double tempBalance = accountBalance;
		Account::debit(val);

		if (accountBalance - fee < 0)
		{
			std::cout << "insufficient balance! Your transaction will not be completed!" << std::endl;
			accountBalance = tempBalance;
		}
		else
		{
			accountBalance -= fee;
		}
	}
};
int main()
{
	SavingsAccount a(10, "ivan", 10.0, 5);
	SavingsAccount b(a);
	CheckingAccount c(30, "pesho", 20.0, 10);
	

}

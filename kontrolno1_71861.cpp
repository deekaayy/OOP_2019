
#include "pch.h"
#include <iostream>
#include <cstring>

//_CRT_SECURE_NO_WARNINGS

const int MAX_SIZE=50;
const int MAX_WORKER_SIZE = 100;
bool strcompare(const char* name, const char* _name)
{
	bool flag = true;
	if (strlen(name) == strlen(_name))
	{
		for (int i = 0; i < strlen(name); i++)
		{
			if (*(name + i) != *(_name + i))
			{
				flag = false;
				return flag;
			}
		}
	}
	else
	{
		flag = false;
	}
	return flag;
}
void strcopy(char*& name, const char* _name)
{
	int name1len = strlen(_name);
	delete[] name;
	name = new char[name1len + 1];
	for (int i = 0; i <= name1len; i++)
	{
		name[i] = _name[i];
	}
}
class BankAccount
{
private:
	char* name;
	char* accountNumb;
	double balance;
	void copy(const BankAccount& other)
	{
		setName(other.name);
		setAccountNumb(other.accountNumb);
		setBalance(other.balance);
	}
public:
	void del()
	{
		delete[] name;
		delete[] accountNumb;
	}
	BankAccount()
	{
		setName("");
		setAccountNumb("");
		setBalance(0);
	}
	BankAccount(const char* _name, const char* _accountNum, double _balance)
	{
		setName(_name);
		setAccountNumb(_accountNum);
		setBalance(_balance);
	}
	BankAccount& operator=(const BankAccount& other)
	{
		if (this != &other)
		{
			del();
			copy(other);
		}
		return *this;
	}
	~BankAccount()
	{
		del();
	}
	BankAccount(const BankAccount& other)
	{
		copy(other);
	}
	void deposit(double depos)
	{
		balance += depos;
	}
	void withdraw(double withdr)
	{
		if ((balance - withdr) < 0)
		{
			std::cout << "Can't withdraw that amount, money left: " << balance << std::endl;
		}
	}
	void setName(const char* _name)
	{
		if (!_name)
		{
			_name = "";
		}
		delete[] name;
		name = new char[strlen(_name) + 1];
		strcopy(name, _name);
	}
	void setAccountNumb(const char* _numb)
	{
		if (!_numb)
		{
			_numb = "";
		}
		delete[] accountNumb;
		accountNumb = new char[strlen(_numb) + 1];
		strcopy(accountNumb, _numb);
	}
	void setBalance(double bal)
	{
		balance = bal;
	}
	double getBalance() const
	{
		return balance;
	}
	const char* getName() const
	{
		return name;
	}
	const char* getAccountNum() const
	{
		return accountNumb;
	}
	void print()
	{
		std::cout << name << " with account number " << accountNumb << " with balance: " << balance << std::endl;
	}
};
class Bank
{
private:
	BankAccount *accounts;
	size_t capacity;
	size_t size=0;
	void copy(const Bank& other)
	{
		accounts = other.accounts;
		capacity = other.capacity;
	}
	void del()
	{
		delete[] accounts;
	}
public:
	Bank()
	{
		capacity = 100;
		size = 0;
	}
	Bank(size_t _cap)
	{
		capacity = _cap;
		size = 0;
	}
	~Bank()
	{
		del();
	}
	Bank(const Bank& other)
	{
		if (this != &other)
		{
			del();
			copy(other);
		}
	}
	void addAccount(const BankAccount& account)
	{
		accounts[size] = account;
		size++;
	}
	void deleteAccount(const char* _num)
	{
		for (int i = 0; i < size; i++)
		{
			if (strcompare(accounts[i].getAccountNum(), _num) == true)
			{
				for (int j = i; j < size - 1; j++)
				{
					accounts[i] = accounts[j + 1];
				}
			}
		}
	}
	void printBank()
	{
		std::cout << "Bank members: " << std::endl;
		for (int i = 0; i < size; i++)
		{
			accounts[i].print();
		}
	}
};
int main()
{
	BankAccount a("ddddk", "555", 60);
	BankAccount b(a);
	BankAccount c;
	c.setName("Krum");
	a.print();
	b.print();
	c.print();
	Bank d;
	d.addAccount(a);
	d.addAccount(b);
	d.printBank();
}

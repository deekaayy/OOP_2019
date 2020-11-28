#include "pch.h"
#include"strsStuff.h"
#include <iostream>
#include<ostream>
#include<istream>
class myString
{
private:
	char* m_str = nullptr;
	void del()
	{
		delete[] m_str;
	}
	void copy(const char* new_string)
	{
		if (!new_string)
		{
			new_string = "";
		}
		int len = strLen(new_string) + 1;
		m_str = new char[len];
		strcopy(m_str, new_string);
	}
	
public:
	myString()
	{
		m_str = new char[1];
		m_str[0] = '\0';
	}
	myString(const char* new_str)
	{
		copy(new_str);
	}
	~myString()
	{
		del();
	}
	myString& operator=(const myString& other)
	{
		if (this != &other)
		{
			del();
			copy(other.m_str);
		}
		return *this;
	}
	myString(const myString& other)
	{
		copy(other.m_str);
	}
	bool operator==(const myString& other) const
	{
		return strcompare(m_str, other.m_str) == 0;
	}
	bool operator!=(const myString& other) const
	{
		return !(*this == other);
	}
	bool operator<(const myString& other) const
	{
		return strcompare(m_str, other.m_str) < 0;
	}
	void print() const
	{
		std::cout << m_str << std::endl;
	}
	char getCharAt(int a)
	{
		return *(m_str + a - 1);
	}
	friend std::ostream& operator<<(std::ostream& out, const myString& str)
	{
		return out << str.m_str;
	}
	friend std::istream& operator>>(std::istream& in, myString& str)
	{
		in.getline(str.m_str, 50);
		return in;
	}
	myString substring(int pos, int pos2)
	{
		myString a;
		a.m_str = new char[pos2 - pos +2];
		for (int i = pos, j=0; i <= pos2; i++, j++)
		{
			a.m_str[j] = this->m_str[i];
		}
		a.m_str[pos2+1] = '\0';
		return a;
	}
};
int main()
{
	myString a("test1");
	myString b(a);
	std::cout << a.getCharAt(3) << std::endl;
	std::cout<<a.substring(0, 2)<<std::endl;
	a.print();
	b.print();
	std::cout << "INput the new string: ";
	std::cin >> b;
	std::cout << b;
}

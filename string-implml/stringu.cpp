#include"pch.h"
#include"strsStuff.h"
int strLen(const char* a)
{
	int size = 0;
	for (int i = 0; a[i] != '\0'; i++)
	{
		size++;
	}
	return size;
}
bool strcompare(const char* name, const char* _name)
{
	bool flag = true;
	if (strLen(name) == strLen(_name))
	{
		for (int i = 0; i < strLen(name); i++)
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
	int name1len = strLen(_name);
	delete[] name;
	name = new char[name1len + 1];
	for (int i = 0; i <= name1len; i++)
	{
		name[i] = _name[i];
	}
}
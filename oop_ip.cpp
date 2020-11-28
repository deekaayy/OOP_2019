#include "pch.h"
#include <iostream>

class MacAddress
{
//FF:FF:FF:FF:FF:FF
private: 
	char address[18];
public:
	MacAddress()
	{
		strncpy(this->address, "FF:FF:FF:FF:FF:FF", 18);
	}
	MacAddress(const char* address)
	{
		if (strlen(address) != 17)
		{
			std::cout << "Invalid Mac Address, Setting default..."<<std::endl;
			strncpy(this->address, "FF:FF:FF:FF:FF:FF", 18);

		}
		else
		{
			strncpy(this->address, address, 18);
		}
	}
	const char* getAddress() const
	{
		return this->address;
	}
	bool operator>(const MacAddress& other) const
	{
		return strcmp(this->address, other.address) > 0;
	}
	bool operator==(const MacAddress& other) const
	{
		return strcmp(this->address, other.address) == 0;

	}
	bool operator<(const MacAddress& other) const
	{
		return strcmp(this->address, other.address) < 0;

	}
};
class SmartPhone
{
private:
	char model[128];
	char brand[256];
	char owner[256];
	size_t year;
	size_t memory;
	MacAddress macAddress;
public:
	SmartPhone()
	{
		strncpy(this->model, "Default Model", 14);
		strncpy(this->brand, "Default Brand", 14);
		strncpy(this->owner, "Default Owner", 14);
		this->year = 2019;
		this->memory = 32;
		this->macAddress = MacAddress();
	}
	SmartPhone(const char* model, const char* brand, const char* owner, size_t year, size_t memory, MacAddress address)
	{
		strcpy(this->model, model);
		strcpy(this->brand, brand);
		strcpy(this->owner, owner);
		this->year = year;
		this->memory = memory;
		this->macAddress = address;

	}
	void setModel(const char* model)
	{
		strcpy(this->model, model);

	}
	const char* getModel() const
	{
		return this->model;
	}
	void setBrand(const char* brand)
	{
		strcpy(this->brand, brand);

	}
	const char* getBrand() const
	{
		return this->brand;
	}
	void setYear(size_t year)
	{
		this->year = year;
	}
	size_t getYear() const
	{
		return this->year;
	}
	void setMemory(size_t memory)
	{
		this->memory = memory;
	}
	size_t getMemory() const
	{
		return this->memory;
	}
	void setMacAddress(MacAddress address)
	{
		this->macAddress = address;
	}
	const MacAddress& getMacAddress() const
	{
		return this->macAddress;
	}
	void print() const
	{
		std::cout << this->model << std::endl;
		std::cout << this->brand << std::endl;
		std::cout << this->owner << std::endl;
		std::cout << this->year << std::endl;
		std::cout << this->macAddress.getAddress() << std::endl;
	}
};

class Router
{
private:
	SmartPhone* phones;
	size_t size;
	size_t capacity;
	void copy(const Router& other)
	{
		this->capacity = other.capacity;
		this->size = other.size;
		this->phones = new SmartPhone[other.capacity];
		for (size_t i = 0; i < this->size; i++)
		{
			this->phones[i] = other.phones[i];
		}
	}
	void del()
	{
		delete[] phones;
	}
	void resize()
	{
		this->capacity *= 2;
		SmartPhone* newPhones = new SmartPhone[this->capacity];
		for (size_t i = 0; i < this->size; i++)
		{
			newPhones[i] = phones[i];
		}
		delete[] this->phones;
		phones = newPhones;
	}
	void popAt(size_t index)
	{
		for (size_t i = index; i > this->size; i++)
		{
			this->phones[i] = this->phones[i + 1];
		}
		this->size--;
	}
public:
	Router()
	{
		this->capacity = 8;
		this->size = 0;
		this->phones = new SmartPhone[this->capacity];
	}
	Router(const Router& other)
	{
		this->copy(other);
	}
	Router& operator=(const Router& other)
	{
		if (this != &other)
		{
			this->del();
			this->copy(other);
		}
		return *this;
	}
	~Router()
	{
		this->del();
	}
	void addPhone(const SmartPhone& phone)
	{
		if (this->size >= this->capacity)
		{
			resize();
		}
		this->phones[this->size++] = phone;
	}
	void removePhone(MacAddress address)
	{
		int index = -1;
		for (size_t i = 0; i < this->size; i++)
		{
			if (this->phones[i].getMacAddress() == address)
			{
				index = i;
				break;
			}
		}
		if (index != -1)
		{
			this->popAt(index);
		}
	}
	void sort()
	{
		for (size_t i = 0; i < this->size - 1; i++)
		{
			for (size_t j = 0; j < this->size - 1; j++)
			{
				if (this->phones[j].getMacAddress() > this->phones[j + 1].getMacAddress())
				{
					std::swap(this->phones[j], this->phones[j + 1]);
				}
			}
		}
	}
	Router& operator+=(const SmartPhone& other)
	{
		this->addPhone(other);
		return *this;
	}
	Router operator+(const SmartPhone& other) const
	{
		Router returned = *this;
		returned += other;
		return returned;
	}
	void print() const
	{
		for (size_t i = 0; i < this->size; i++)
		{
			this->phones[i].print();
		}
	}
};

int main()
{
	   
    std::cout << "Hello World!\n"; 
	SmartPhone a;
	a.print();
	SmartPhone b = a;
	b.print();
}

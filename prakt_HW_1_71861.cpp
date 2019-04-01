#include "pch.h"
#include <iostream>
#include <cstring>
const int MAX_NAME_SIZE = 50;

class Worker
{
private:
	char *name;
	char *EGN;
	size_t yearsOfService;
	size_t numOfCarsSold;
	bool isBoss, employed;
	void copy(const Worker& other)
	{
		name = EGN = nullptr;
		setName(other.name);
		setEGN(other.EGN);
		setYearsService(other.yearsOfService);
		setCarsSold(other.numOfCarsSold);
	}
public:
	void del()
	{
		delete[] name;
		delete[] EGN;
	}
	Worker() :name(nullptr), EGN(nullptr)
	{
		setName("");
		setEGN("");
		setCarsSold(0);
		setYearsService(0);
		setBoss(0);
		setEmployed(true);
	}
	Worker(const char* _name, const char* _egn, size_t _yearsService, size_t _carsSold, bool _isBoss):name(nullptr), EGN(nullptr), yearsOfService(_yearsService), numOfCarsSold(_carsSold), isBoss(_isBoss), employed(true)
	{
		setName(_name);
		setEGN(_egn);
		setCarsSold(_carsSold);
		setYearsService(_yearsService);
		setBoss(_isBoss);
		setEmployed(true);
	}
	~Worker()
	{
		del();
	}
	Worker(const Worker &other)
	{
		copy(other);
	}
	void setEmployed(bool _employed)
	{
		employed = _employed;
	}
	bool getEmployedStatus()
	{
		return employed;
	}
	void setBoss(bool _boss)
	{
		isBoss = _boss;
	}
	bool getBossStatus()
	{
		return isBoss;
	}
	void setName(const char* _name)
	{
		if (!_name)
		{
			_name = "";
		}
		delete[] name;
		int len = strlen(_name);
		name = new char[len + 1];
		strcpy(name, _name);
	}
	void setEGN(const char* _egn)
	{
		if (!_egn)
		{
			_egn = "";
		}
		delete[] EGN;
		int len = strlen(_egn);
		EGN = new char[len + 1];
		strcpy(EGN, _egn);
	}
	void setYearsService(size_t _years)
	{
		yearsOfService = _years;
	}
	void setCarsSold(size_t _cars)
	{
		numOfCarsSold = _cars;
	}
	const char* getName() const
	{
		return name;
	}
	const char* getEGN() const
	{
		return EGN;
	}
	size_t getYearsOfService() const
	{
		return yearsOfService;
	}
	size_t getNumberOfCarsSold() const
	{
		return numOfCarsSold;
	}
	void print() const
	{
		std::cout <<"Salesman "<< name << " " << EGN << " with " << yearsOfService << " years of experience and " << numOfCarsSold << " sales."<<std::endl;
	}
	Worker& operator=(const Worker& other)
	{
		if (this != &other)
		{
			del();
			copy(other);
		}
		return *this;
	}
};

class Automobile
{
private:
	char* brand;
	char* model;
	size_t yearOfProduction;
	size_t price;
	size_t mileage;
	void del()
	{
		delete[] brand;
		delete[] model;
	}
	void copy(const Automobile& other)
	{
		brand = model = nullptr;
		setBrand(other.brand);
		setModel(other.model);
		setYearOfProduction(other.yearOfProduction);
		setPrice(other.price);
		setMileage(other.mileage);
	}
public:

	Automobile():brand(nullptr), model(nullptr)
	{
		setBrand("Audi");
		setModel("A3");//there's only one truth
		setYearOfProduction(2012);
		setPrice(12000);
		setMileage(160000);
	}
	Automobile(const char* _brand, const char* _model, size_t _year, size_t _price, size_t _mileage)
	{
		setBrand(_brand);
		setModel(_model);
		setYearOfProduction(_year);
		setPrice(_price);
		setMileage(_mileage);
	}
	Automobile(const Automobile &other)
	{
		copy(other);
	}
	~Automobile()
	{
		del();
	}
	void print()
	{
		std::cout << brand << " " << model << " made in " << yearOfProduction << " with mileage " << mileage << ". Price: " << price<<std::endl;
	}
	void setBrand(const char* _brand)
	{
		if (!_brand)
		{
			_brand = "";
		}
		delete[] brand;
		int len = strlen(_brand);
		brand = new char[len + 1];
		strcpy(brand, _brand);
	}
	void setModel(const char* _model)
	{
		if (!_model)
		{
			_model = "";
		}
		delete[] model;
		int len = strlen(_model);
		model = new char[len + 1];
		strcpy(model, _model);
	}
	void setYearOfProduction(size_t _year)
	{
		yearOfProduction = _year;
	}
	void setPrice(size_t _price)
	{
		price = _price;
	}
	void setMileage(size_t _mileage)
	{
		mileage = _mileage;
	}
	const char* getBrand() const
	{
		return brand;
	}
	const char* getModel() const
	{
		return model;
	}
	size_t getYearOfProduction() const
	{
		return yearOfProduction;
	}
	size_t getPrice() const
	{
		return price;
	}
	size_t getMileage() const
	{
		return mileage;
	}
	Automobile& operator=(const Automobile& other)
	{
		if (this != &other)
		{
			del();
			copy(other);
		}
		return *this;
	}
};

class Dealership
{
private:
	Worker boss;
	Worker *employees;
	Automobile *cars;
	size_t numOfEmployees;
	size_t numOfCars;
	size_t capacity;
	size_t carCapacity;
	void extend()
	{
		Worker *tmp = employees;
		capacity *= 2;
		employees = new Worker[capacity];
		for (int i = 0; i < numOfEmployees; ++i)
		{
			employees[i] = tmp[i];
		}
		delete[] tmp;
	}
	void extendCar()
	{
		Automobile *tmp = cars;
		carCapacity *= 2;
		cars = new Automobile[carCapacity];
		for (int i = 0; i < numOfCars; ++i)
		{
			cars[i] = tmp[i];
		}
		delete[] tmp;
	}
public:
	Dealership()
	{
		capacity = 10;
		carCapacity = 20;
		numOfEmployees = 0;
		numOfCars = 0;
		employees = new Worker[capacity];
		cars = new Automobile[carCapacity];
		boss.setBoss(true);
	}
	void setBoss(const char* _name, const char* _egn, size_t _yearsService, size_t _carsSold)
	{
		boss.setBoss(true);
		boss.setName(_name);
		boss.setEGN(_egn);
		boss.setYearsService(_yearsService);
		boss.setCarsSold(_carsSold);
		boss.setEmployed(true);
	}
	void addEmployee(const Worker& newEmployee)
	{
		if (numOfEmployees == capacity)
		{
			extend();
		}
		employees[numOfEmployees++] = newEmployee;
	}
	void addCar(const Automobile& newCar)
	{
		if (numOfCars == carCapacity)
		{
			extendCar();
		}
		cars[numOfCars++] = newCar;
	}
	void removeWorker(const char* _egn)
	{
		if (numOfEmployees != 0)
		{
			bool isThere = false;
			for (int i = 0; i < numOfEmployees; ++i)
			{
				if (employees[i].getEGN() == _egn)
				{
					isThere = true;
					for (int j = i; j < numOfEmployees - 1; ++j)
					{
						employees[j] = employees[j + 1];
					}
				}
			}
			if (isThere == true)
			{
				employees[numOfEmployees].del();
				--numOfEmployees;
			}
			else
				std::cout << "At present there is no such employee" << std::endl;
		}
		else
		{
			std::cout << "No employees left!"<<std::endl;
		}
	}
	void removeCar(const char* _brand, const char* _model)
	{
		for (int i = 0; i < numOfCars; ++i)
		{
			if ((strcmp(cars[i].getBrand(), _brand) == 0) && (strcmp(cars[i].getModel(), _model) == 0))
			{
				for (int j = i; j < numOfCars; ++j)
				{
					cars[i] = cars[j + 1];
				}
				--numOfCars;
				return;
			}
		}
	}
	void carSold(const char* _brand, const char* _model, const char* _name)
	{
		for (int i = 0; i < numOfEmployees; i++)
		{
			if (strcmp(employees[i].getName(), _name) == 0)
			{
				employees[i].setCarsSold(employees[i].getNumberOfCarsSold() + 1);
				std::cout << "Car " << _brand << " " << _model << " sold by " << _name << std::endl;
				removeCar(_brand, _model);
				return;
			}
		}
	}
	void sortWrokersByCarsSold()
	{
		for (int i = 1; i < numOfEmployees - 1; ++i)
		{
			Worker min = employees[i];
			size_t minIndex = i;
			for (int j = i + 1; j < numOfEmployees; ++j)
			{
				if (employees[j].getNumberOfCarsSold() < min.getNumberOfCarsSold())
				{
					min = employees[j];
					minIndex = j;
				}
			}
			std::swap(employees[i], employees[minIndex]);
		}
		std::cout << "\n Sorted by cars sold_____________________________ \n";
		print();
	}
	void sortWorkersByYearsOfService()
	{
		for (int i = 1; i < numOfEmployees - 1; ++i)
		{
			Worker min = employees[i];
			size_t minIndex = i;
			for (int j = i + 1; j < numOfEmployees; ++j)
			{
				if (employees[j].getYearsOfService() < min.getYearsOfService())
				{
					min = employees[j];
					minIndex = j;
				}
			}
			std::swap(employees[i], employees[minIndex]);
		}
		std::cout << "\n Sorted by years of service_____________________________ \n";
		print();
	}
	void sortCarsByPrice()
	{
		for (int i = 0; i < numOfCars - 1; ++i)
		{
			Automobile min = cars[i];
			size_t minIndex = i;
			for (int j = i + 1; j < numOfCars; ++j)
			{
				if (cars[j].getPrice()<min.getPrice())
				{
					min = cars[j];
					minIndex = j;
				}
			}
			std::swap(cars[i], cars[minIndex]);
		}
		std::cout << "\n Sorted by price__________________________________________ \n";
		print();
	}
	void sortCarsByMileage()
	{
		for (int i = 0; i < numOfCars - 1; ++i)
		{
			Automobile min = cars[i];
			size_t minIndex = i;
			for (int j = i + 1; j < numOfCars; ++j)
			{
				if (cars[j].getMileage() < min.getMileage())
				{
					min = cars[j];
					minIndex = j;
				}
			}
			std::swap(cars[i], cars[minIndex]);
		}
		std::cout << "\n Sorted by mileage_____________________________ \n";
		print();
	}
	void print() const
	{
		std::cout << "Boss: "; 
		boss.print();
		if (numOfEmployees == 0)
		{
			std::cout << "No employees present. " << std::endl;
		}
		else
		{
			std::cout << "Workers: ___________________________________________" << std::endl;
			for (int i = 0; i < numOfEmployees; ++i)
			{
				employees[i].print();
			}
		}
		if (numOfCars == 0)
		{
			std::cout << "No more cars left. " << std::endl;
		}
		else
		{
			std::cout << "Cars: ________________________________________________ " << std::endl;
			for (int j = 0; j < numOfCars; ++j)
			{
				cars[j].print();
			}
		}
		std::cout << std::endl;
	}

};
int main()
{

	Worker a;
	Worker b("pesho", "9908073208", 3, 120, 0);
	Worker c("rali<3", "0909090807", 6, 100, 0);
	Worker d("ivan", "9999999999", 1, 140, 0);
	Automobile a1;
	Automobile b1(a1);
	Dealership carfact;
	carfact.setBoss("dekaay", "9908070605", 15, 1000);
	carfact.addCar(a1);
	carfact.addCar(b1);
	carfact.addEmployee(a);
	carfact.addEmployee(b);
	carfact.print();
	carfact.carSold("Audi", "A3","pesho");
	carfact.print();
	return 0;
}
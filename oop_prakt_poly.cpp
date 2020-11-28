#include "pch.h"
#include <iostream>
#include <string>
#include <vector>
class Dish
{
private:
	std::string name;
	std::string description;
	struct NutritionalData {
		int protein=0;
		int carbohydrates=0;
		int fats=0;
	};
	NutritionalData data;
	virtual Dish* doClone() const = 0;
public:
	Dish() : name(" "), description("") {}
	Dish(std::string _name, std::string _description, int _protein, int _carbohydrates, int _fats) : name(_name), description(_description) {
		data.protein = _protein;
		data.carbohydrates = _carbohydrates;
		data.fats = _fats;
	}
	int calculateCal() {
		return data.protein * 4 + data.carbohydrates * 4 + data.fats * 9;
	}
	virtual void printInfo() = 0;
	std::string getName() const
	{
		return name;
	}
	std::string getDescription() const
	{
		return description;
	}
	Dish* clone() const
	{
		return doClone();
	}
};

class Starter : public Dish {
private:
	Starter* doClone() const override
	{
		return new Starter(*this);
	}
public:
	Starter() :Dish() {}
	Starter(std::string _name, std::string _description, int _protein, int _carbohydrates, int _fats):
		Dish(_name, _description, _protein, _carbohydrates, _fats) {}
	void printInfo() override
	{
		std::cout << getName() << " " << getDescription() << " with calories: " << calculateCal() << std::endl;
	}
};

class mainDish : public Dish {
private:
	mainDish* doClone() const override
	{
		return new mainDish(*this);
	}
public:
	mainDish() :Dish() {}
	mainDish(std::string _name, std::string _description, int _protein, int _carbohydrates, int _fats) :
		Dish(_name, _description, _protein, _carbohydrates, _fats) {}
	void printInfo() override
	{
		std::cout << getName() << " " << getDescription() << " with calories: " << calculateCal() << std::endl;
	}
};

class Dessert : public Dish {
private:
	Dessert* doClone() const override
	{
		return new Dessert(*this);
	}
public:
	Dessert() :Dish() {}
	Dessert(std::string _name, std::string _description, int _protein, int _carbohydrates, int _fats) :
		Dish(_name, _description, _protein, _carbohydrates, _fats) {}
	void printInfo() override
	{
		std::cout << getName() << " " << getDescription() << " with calories: " << calculateCal() << std::endl;
	}
};

class CookerBook {
private:
	std::vector<Dish*> menu;
	std::string name;
	std::string author;
	std::string publishing;
public:
	CookerBook() {
		name = "";
		author = "";
		publishing = "";
	}
	CookerBook(std::string _name, std::string _author, std::string _publish) {
		name = _name;
		author = _author;
		publishing = _publish;
	}
	void addDish(Dish& added)
	{
		menu.push_back(added.clone());
	}
	void print()
	{
		std::cout << name << " " << author << " " << publishing << std::endl;
		for (auto x : menu)
		{
			x->printInfo();
		}
	}
};
int main()
{
	Starter a("a", "a", 1, 2, 3);
	mainDish b("b", "b", 2, 3, 4);
	Dessert c("c", "c", 4, 5, 6);
	CookerBook book("kniga", "dd", "izdat");
	book.addDish(a);
	book.addDish(b);
	book.addDish(c);
	book.print();

}
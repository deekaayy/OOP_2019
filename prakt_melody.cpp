#include "pch.h"
#include <iostream>
#include <string>
#include <vector>
class Melody {
private:
	std::string melody;
	virtual Melody* doCopy() const = 0;
public:
	Melody():melody("") {}
	Melody(std::string _melody) : melody(_melody) {}
	virtual void print() const = 0;
	Melody* clone() const {
		return doCopy();
	}
	std::string getName() const {
		return melody;
	}
};

class Song:public Melody {
private:
	float duration;
	std::string author;
	Song* doCopy() const override{
		return new Song(*this);
	}
public:
	Song() :Melody(),duration(0.0),author("") {}
	Song(std::string _melody,std::string _author, float _duration) :
		Melody(_melody),author(_author), duration(_duration) {}
	void print() const override{
		std::cout << getName() << " " << author << " " << duration << std::endl;
	}
};

class Mix : public Melody {
private:
	std::vector<Melody*> tree;
	std::string frontCover;
	void del() const {
		for (auto x : tree) {
			delete x;
		}
	}
	void copy(const Mix& other) {
		for (Melody* mel : other.tree) {
			tree.push_back(mel->clone());
		}
	}
	Mix* doCopy() const override {
		return new Mix(*this);
	}

public:
	Mix() :Melody(), frontCover("") {
		tree.clear();
	}
	Mix(std::string _frontCover, std::string _melody) :
		Melody(_melody), frontCover(_frontCover) {}
	~Mix() {
		del();
	}
	const Mix& operator=(const Mix& other) {
		if (this != &other) {
			del();
			copy(other);
		}
	}
	void print() const override {
		std::cout << " /////////////////" << frontCover << "////////////////////////" << std::endl;
		for (auto x : tree) {
			x->print();
		}
	}
	void add(const Melody& added) {
		tree.push_back(added.clone());
	}
};

int main()
{


    std::cout << "Hello World!\n"; 
}

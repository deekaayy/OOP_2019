#include "pch.h"
#include <iostream>
#include<string>
#include<vector>
#include<cstring>

class File
{	
private:
	std::string fileName;
	virtual File* doClone() const = 0;
public:
	virtual bool isTextFile() const = 0; //after a long brainstorm, a check had to be made
	File() = default;
	virtual ~File() = default;
	File(std::string _fileName)
	{
		fileName = _fileName;
	}
	File& operator=(const File& other)
	{
		if (this != &other) {
			fileName = other.fileName;
		}
		return *this;
	}
	std::string getName() const
	{
		return fileName;
	}
	File* clone() const {
		return doClone();
	}
	void setName(const std::string& _name){
		fileName = _name;
	}
	virtual int size() const = 0;
	virtual void print() const = 0;
};

class TextFile : public File
{
private:
	std::string txtFileData;
	TextFile* doClone() const override { 
		return new TextFile(*this);
	}
public:
	TextFile(std::string fileName = "", std::string _data= "") : File(fileName), txtFileData(_data) {}
	~TextFile() = default;
	int size() const override {
		return txtFileData.size();
	}
	bool isTextFile()const { 
		return true; 
	}
	void addContent(std::string newContent) {
		txtFileData = newContent;
	}
	void print() const override {
		std::cout << getName() << " " << txtFileData << std::endl;
	}
};

class Catalog : public File
{
private:
	std::vector<File*> catalogData;
	Catalog* doClone() const override {
		return new Catalog(*this);
	}
	void copy(const Catalog& other)
	{
		for (File* file : other.catalogData)
		{
			catalogData.push_back(file->clone());
		}
	}

	void del()
	{
		for (File* file : catalogData)
		{
			delete file;
		}
	}
public:
	Catalog() : File("") {};
	Catalog(std::string nameOfCatalog) :File(nameOfCatalog) {}
	~Catalog() {
		std::cout << "del" << std::endl;
		for (auto x : catalogData) {
			delete x;
		}
	}
	Catalog(const Catalog& other) : File(other.getName()), catalogData()
	{
		copy(other);
	}

	Catalog& operator=(const Catalog& other)
	{
		if (this != &other)
		{
			del();
			
			copy(other);
		}

		return *this;
	}
	bool isTextFile()const { 
		return false; 
	}
	int size() const override {
		int count = 0;
		for (auto x : catalogData) {
			count += x->size();
		}
		return count;
	}
	const std::vector<File*>& takePtrToElements()const { //another check 
		return catalogData;
	}

	void addFile(const File& newFile) {
		catalogData.push_back(newFile.clone());
	}
	void print() const override {
		for (auto x : catalogData) {
			x->print();
		}
	}
	std::vector<File*> getCatalogueData() const {
		return catalogData;
	}
};

std::string split(std::string& source, char symb) // had to redefine
{
	int pos = 0;//current position
	std::string result;
	for (; pos < source.size(); pos++)
	{
		if (source[pos] == symb) {
			break;
		}
		result.push_back(source[pos]);//+ length & added char
	}
	source.erase(0, pos + 1);
	return result;
}

void insert(Catalog& destination, const File& source, std::string path) {

	File* trackIt = &destination;
	std::string folder = split(path, '/');
	bool isPath = false; //and again another check
	while (folder != "") {

		isPath = false;

		for (auto elem : ((Catalog*)trackIt)->takePtrToElements()) { // a must do conversion or you get slapped in the face

			if (folder == elem->getName() && elem->isTextFile() == false) {
				trackIt = elem;
				isPath = true;
			}
		}
		if (isPath == false) {
			std::cout << "Invalid path..." << std::endl;
			return;
		}
		folder = split(path, '/');
	}
	((Catalog*)trackIt)->addFile(source);
	//TODO: gotta optimise
}

int main()
{
	Catalog root("oop");

	Catalog sub("hw");

	sub.addFile(TextFile("vector", "#include <vector>"));

	sub.addFile(TextFile("filesystem", "TODO"));

	root.addFile(TextFile("test1", "web server"));

	root.addFile(TextFile("test2", "... as if"));

	root.addFile(sub);

	std::cout << sub.size() << std::endl;

	std::cout << root.size() << std::endl;
	root.print();
	std::cout << std::endl;
    
	insert(root, TextFile("New File", "Content"), "hw");

	insert(root, TextFile("New File2", "Content"), "hw/non-existant");  // Non-existant file in path

	insert(root, TextFile("New File3", "Content"), "hw/vector"); // Non-catalog in path
	std::cout << std::endl;
	std::cout << root.size() << std::endl;
	root.print();
	////end mi lif

	//░░░░░░░░░░░░░░░░░░░░░░░░░░░░░
	//	░░░░░░░░░░░░░▄▄▄▄▄▄▄░░░░░░░░░
	//	░░░░░░░░░▄▀▀▀░░░░░░░▀▄░░░░░░░
	//	░░░░░░░▄▀░░░░░░░░░░░░▀▄░░░░░░
	//	░░░░░░▄▀░░░░░░░░░░▄▀▀▄▀▄░░░░░
	//	░░░░▄▀░░░░░░░░░░▄▀░░██▄▀▄░░░░
	//	░░░▄▀░░▄▀▀▀▄░░░░█░░░▀▀░█▀▄░░░
	//	░░░█░░█▄▄░░░█░░░▀▄░░░░░▐░█░░░
	//	░░▐▌░░█▀▀░░▄▀░░░░░▀▄▄▄▄▀░░█░░
	//	░░▐▌░░█░░░▄▀░░░░░░░░░░░░░░█░░
	//	░░▐▌░░░▀▀▀░░░░░░░░░░░░░░░░▐▌░
	//	░░▐▌░░░░░░░░░░░░░░░▄░░░░░░▐▌░
	//	░░▐▌░░░░░░░░░▄░░░░░█░░░░░░▐▌░
	//	░░░█░░░░░░░░░▀█▄░░▄█░░░░░░▐▌░
	//	░░░▐▌░░░░░░░░░░▀▀▀▀░░░░░░░▐▌░
	//	░░░░█░░░░░░░░░░░░░░░░░░░░░█░░
	//	░░░░▐▌▀▄░░░░░░░░░░░░░░░░░▐▌░░
	//	░░░░░█░░▀░░░░░░░░░░░░░░░░▀░░░
	//	░░░░░░░░░░░░░░░░░░░░░░░░░░░░░
	return 0;
}
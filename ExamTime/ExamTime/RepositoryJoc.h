#pragma once
#include "Joc.h"
#include <vector>
#include <string>

using namespace std;

class RepositoryJoc
{
private:
	vector<Joc> storage;
	string filePath;

	void readFromFile();
	void writeToFile();

public:
	//Constructors
	RepositoryJoc(string filePath): filePath{filePath}{}
	RepositoryJoc(const RepositoryJoc&) = delete;
	
	//Adds games to the repository
	void adaugaJoc(Joc j);

	//Edits games from the repository.
	void editJoc(Joc j);

	//Finds the smallest id that isn't being used.
	int smallestFreeId();

	//Returns all the elements in the repo as a vector.
	vector<Joc> getAll();
};


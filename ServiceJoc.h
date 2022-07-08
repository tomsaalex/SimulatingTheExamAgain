#pragma once
#include "RepositoryJoc.h"
#include "ValidatorJoc.h"

class ServiceJoc
{
private:
	RepositoryJoc& repo;
	ValidatorJoc& valid;
public:
	//Constructors
	ServiceJoc(RepositoryJoc& repo, ValidatorJoc vld) : repo{ repo }, valid{ vld }{}
	ServiceJoc(const ServiceJoc& srv) = delete;

	//Manages the addition of games on a service level.
	void srvAddJoc(int dim, string tabla, string nextPlayer);

	//Manages the editing of games on a service level.
	void srvEditJoc(int id, int dim, string tabla, string nextPlayer, string stare);
	
	//Returns all the elements in the repository as a vector.
	vector<Joc> srvGetAll();

	//Returns all the elements in the repository sorted by their state, as a vector.
	vector<Joc> srvGetAllSortedByState();
	
};


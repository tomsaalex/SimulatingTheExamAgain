#pragma once
#include <string>
#include "CustomException.h"

class Joc
{
private:
	int id;
	int dim;
	string tabla;
	string nextPlayer;
	string stareJoc;
public:
	//Constructors
	Joc(int id, int dim, string tabla, string nextPlayer, string stareJoc):id{id}, dim{dim}, tabla{tabla}, nextPlayer{nextPlayer}, stareJoc{stareJoc}{}
	Joc(int id, int dim, string tabla, string nextPlayer) :id{ id }, dim{ dim }, tabla{ tabla }, nextPlayer{ nextPlayer }{
		stareJoc = "Neinceput";
	}
	//Getters
	int getId() const
	{
		return id;
	}
	int getDim() const
	{
		return dim;
	}
	string getTabla() const
	{
		return tabla;
	}
	string getNextPlayer() const
	{
		return nextPlayer;
	}
	string getStare() const
	{
		return stareJoc;
	}

	//Setters
	void setDim(int newDim)
	{
		dim = newDim;
	}
	void setTabla(string newTabla)
	{
		tabla = newTabla;
	}
	void setNextPlayer(string newNextPlayer)
	{
		nextPlayer = newNextPlayer;
	}
	void setStare(string newStare)
	{
		stareJoc = newStare;
	}

	//Converts the object into a format that can be printed to a file.
	string printToFileFormat() const
	{
		return to_string(id) + " " + to_string(dim) + " " + tabla + " " + nextPlayer + " " + stareJoc;
	}
};


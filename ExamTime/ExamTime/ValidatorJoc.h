#pragma once
#include "Joc.h"

class ValidatorJoc
{
public:
	//Validates any given game.
	bool valideazaJoc(Joc j)
	{
		if (j.getDim() != 3 &&
			j.getDim() != 4 &&
			j.getDim() != 5)
			return false;

		if (j.getTabla().size() != j.getDim() * j.getDim())
			return false;

		for (auto e : j.getTabla())
		{
			if (e != 'X' && e != 'O' && e != '-')
				return false;
		}

		if (j.getNextPlayer() != "X" && j.getNextPlayer() != "O")
			return false;

		if (j.getStare() != "Neinceput" && j.getStare() != "In derulare" && j.getStare() != "Terminat")
			return false;

		return true;
	}
};


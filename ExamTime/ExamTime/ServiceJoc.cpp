#include "ServiceJoc.h"
#include <algorithm>

void ServiceJoc::srvAddJoc(int dim, string tabla, string nextPlayer)
{
    Joc j = Joc(repo.smallestFreeId(), dim, tabla, nextPlayer);

    if (valid.valideazaJoc(j) == false)
        throw CustomException("Joc invalid!\n");

    repo.adaugaJoc(j);
}

void ServiceJoc::srvEditJoc(int id, int dim, string tabla, string nextPlayer, string stare)
{    
    Joc joc = Joc(id, dim, tabla, nextPlayer, stare);
    
    if(valid.valideazaJoc(joc) == false)
        throw CustomException("Joc invalid!\n");
    
    repo.editJoc(joc);
}


vector<Joc> ServiceJoc::srvGetAll()
{
    return repo.getAll();
}

vector<Joc> ServiceJoc::srvGetAllSortedByState()
{
    vector<Joc> unsorted = repo.getAll();

    sort(unsorted.begin(), unsorted.end(), [](Joc a, Joc b) {
        int convertedAState;
        int convertedBState;

        if (a.getStare() == "Neinceput")
            convertedAState = 0;
        else if (a.getStare() == "In derulare")
            convertedAState = 1;
        else if (a.getStare() == "Terminat")
            convertedAState = 2;

        if (b.getStare() == "Neinceput")
            convertedBState = 0;
        else if (b.getStare() == "In derulare")
            convertedBState = 1;
        else if (b.getStare() == "Terminat")
            convertedBState = 2;

        return convertedAState < convertedBState;
    });

    return unsorted;
}

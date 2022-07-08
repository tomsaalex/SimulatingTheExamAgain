#include "RepositoryJoc.h"
#include <fstream>
#include <sstream>
#include <algorithm>

void RepositoryJoc::readFromFile()
{
    storage.clear();
    ifstream fin(filePath);

    if (!fin.is_open())
        throw CustomException("File couldn't open!\n");

    string line;
    while (getline(fin, line))
    {
        if (line.empty())
            continue;

        stringstream str = stringstream(line);

        string strId; getline(str, strId, ' '); int id = stoi(strId);
        string strDim; getline(str, strDim, ' '); int dim = stoi(strDim);
        string tabla; getline(str, tabla, ' ');
        string nextPlayer; getline(str, nextPlayer, ' ');
        string stare; getline(str, stare);

        Joc j(id, dim, tabla, nextPlayer, stare);

        storage.push_back(j);
    }
    
    fin.close();
}

void RepositoryJoc::writeToFile()
{
    ofstream fout(filePath);

    if(!fout.is_open())
        throw CustomException("File couldn't open!\n");

    for (Joc v : storage)
    {
        fout << v.printToFileFormat() << '\n';
    }
}


void RepositoryJoc::adaugaJoc(Joc joc)
{
    for (Joc j : storage)
        if (j.getId() == joc.getId())
            throw CustomException("ID duplicat");
    
    storage.push_back(joc);
    writeToFile();
}

void RepositoryJoc::editJoc(Joc joc)
{
    for (Joc& j : storage)
    {
        if (j.getId() == joc.getId())
        {
            j.setDim(joc.getDim());
            j.setNextPlayer(joc.getNextPlayer());
            j.setStare(joc.getStare());
            j.setTabla(joc.getTabla());
        }
    }

    writeToFile();
}
/*
Joc& RepositoryJoc::getJocReference(int id)
{
    for (Joc& j : storage)
    {
        if (j.getId() == id)
            return j;
    }

    throw CustomException("Jocul cerut nu exista!\n");
}
*/
int RepositoryJoc::smallestFreeId()
{
    readFromFile();

    vector<Joc> elems = storage;
    sort(elems.begin(), elems.end(), [](Joc a, Joc b) {
        return a.getId() < b.getId();
    });

    int currentId = 1;

    for (Joc j : elems)
    {
        if (j.getId() == currentId)
            currentId++;
    }

    return currentId;
}

vector<Joc> RepositoryJoc::getAll()
{
    readFromFile();
    return storage;
}

#include "Tests.h"
#include "ServiceJoc.h"
#include <assert.h>

void Tests::testEverything()
{
	RepositoryJoc repo{"TestFile.txt"};
	ValidatorJoc valid;
	ServiceJoc srv{ repo, valid };

	Joc j(1, 3, "XXXOOOXXX", "X");

	repo.adaugaJoc(j);
	assert(repo.getAll().size() == 1);

	srv.srvAddJoc(4, "OOOOOOOOO", "X");
	assert(srv.srvGetAll().size() == 2);

	//srv.srvEditJoc(1, )

}

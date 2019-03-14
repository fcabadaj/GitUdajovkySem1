#include "CentralnySklad.h"

using namespace structures;

CentralnySklad::CentralnySklad():
	vozovyPark_(new ArrayList<Vozidlo*>)
{
}


CentralnySklad::~CentralnySklad()
{
	for (unsigned int i = 0; i < vozovyPark_->size(); i++)
	{
		delete (*vozovyPark_)[i];
	}
	delete vozovyPark_;
}

void CentralnySklad::vypisVozidla()
{
	for (unsigned int i = 0; i < vozovyPark_->size(); i++)
	{
		(*vozovyPark_)[i]->vypisVozidlo();
	}
}

#include "structures/heap_monitor.h"
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
		(*vozovyPark_)[i]->vypisSa();
	}
}

bool CentralnySklad::skontrolujSPZ(string spz)
{
	for (unsigned int i = 0; i < vozovyPark_->size(); i++)
	{
		if (vozovyPark_->operator[](i)->getSPZ() == spz)
		{
			cout << "Vozidlo s takouto SPZ uz existuje! \n";
			return false;
		}		
	}
	return true;
}

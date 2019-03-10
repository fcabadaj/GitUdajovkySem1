#include "AoESystem.h"


AoESystem::AoESystem():
	regiony_(new ArrayList<Region*>())
{
	regiony_->add(new Region(eRegiony::BA));
}


AoESystem::~AoESystem()
{
}

bool AoESystem::pridajVozidlo(eRegiony::EnumRegion nazovRegionu, string spz, int nosnost, int prevadzkoveNaklady)
{
	Vozidlo *vozidlo = new Vozidlo(spz,nosnost,prevadzkoveNaklady);
	
	if (static_cast<int>(regiony_->size()) == 0)
	{
		(*regiony_)[0]->getVozovyPark().add(vozidlo);
		return true;
	}
	else
	{
		for (unsigned int i = 0; i < static_cast<int>(regiony_->size()); i++)
		{
			if (regiony_->operator[](i)->getNazovRegionu() == nazovRegionu)
			{
				regiony_->operator[](i)->getVozovyPark().add(vozidlo);
				return true;
			}
		}
		return false;
	}
	
}

bool AoESystem::pridajDrona(eRegiony::EnumRegion nazovRegionu, int sCislo, int typ, int nosnost, int rychlost, int dobaLetu, int dobaNabijania)
{
	Dron *dron = new Dron(sCislo, typ, nosnost, rychlost, dobaLetu, dobaNabijania);

	for  (unsigned int i = 0;  i < static_cast<int>(regiony_->size()); i++)
	{
		if (regiony_->operator[](i)->getNazovRegionu() == nazovRegionu)
		{
			regiony_->operator[](i)->getDrony().add(dron);
			return true;
		}		
	}
	return false;

}

#include "AoESystem.h"


AoESystem::AoESystem():
	regiony_(new ArrayList<Region*>())
{
	
}


AoESystem::~AoESystem()
{
	delete regiony_;
}

Region AoESystem::getRegion(eRegiony::EnumRegion nazovRegionu)
{
	for (unsigned int i = 0; i < static_cast<int>(regiony_->size()); i++)
	{
		if (regiony_->operator[](i)->getNazovRegionu() == nazovRegionu)
		{
			return *regiony_->operator[](i);
		}
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

bool AoESystem::pridajVozidlo(eRegiony::EnumRegion nazovRegionu, string spz, int nosnost, int prevadzkoveNaklady)
{
	Vozidlo *vozidlo = new Vozidlo(spz, nosnost, prevadzkoveNaklady);

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

void AoESystem::naplnRegiony()
{
	Region *region = new Region(eRegiony::ZA);
	regiony_->add(region);
	Region *region2 = new Region(eRegiony::BA);
	regiony_->add(region2);
}

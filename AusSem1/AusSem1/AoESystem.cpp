#include "AoESystem.h"

AoESystem::AoESystem():
	regiony_(new Array<Region*>(25))
{
	(*regiony_)[0] = new Region(eRegiony::ZA, new CentralnySklad());
	(*regiony_)[1] = new Region(eRegiony::BA);
	(*regiony_)[2] = new Region(eRegiony::ZA);

}


AoESystem::~AoESystem()
{
	for (unsigned int i = 0; i < regiony_->size(); i++)
	{
		delete (*regiony_)[i];
	}
	delete regiony_;
}

Region AoESystem::getRegion(eRegiony::EnumRegion nazovRegionu)
{
	for (unsigned int i = 0; i < regiony_->size(); i++)
	{
		if ((*regiony_)[i]->getNazovRegionu() == nazovRegionu)
		{
			return *(*regiony_)[i];
		}
	}
}

bool AoESystem::skontrolujSPZ(string spz)
{
	if (spz.length() != 7)
	{
		cout << "Zle zadana SPZ, Musi mat 7 znakov \n";
		return false;
	}
	for (unsigned int i = 0;  i < regiony_->size(); i++)
	{
		if ((*regiony_)[i]->getCentralnySklad().getVozovyPark()->operator[](i)->getSPZ() == spz)
			cout << "Vozidlo s takouto SPZ je uz zaevidovane! \n";
		return false;
	}
	return true;
}

//bool aoesystem::pridajdrona(eregiony::enumregion nazovregionu, int scislo, int typ, int nosnost, int rychlost, int dobaletu, int dobanabijania)
//{
//	dron *dron = new dron(scislo, typ, nosnost, rychlost, dobaletu, dobanabijania);
//
//	for  (unsigned int i = 0;  i < regiony_->size(); i++)
//	{
//		if ((*regiony_)[i]->getnazovregionu() == nazovregionu)
//		{
//			regiony_->operator[](i)->getdrony().add(dron);
//			return true;
//		}		
//	}
//	return false;
//
//}

bool AoESystem::pridajVozidlo(eRegiony::EnumRegion nazovRegionu, string spz, int nosnost, int prevadzkoveNaklady, Datum *datum)
{
	if (skontrolujSPZ(spz))
	{
		Vozidlo *vozidlo = new Vozidlo(spz, nosnost, prevadzkoveNaklady, datum);

		for (unsigned int i = 0; i < regiony_->size(); i++)
		{
			if ((*regiony_)[i]->getNazovRegionu() == nazovRegionu)
			{
				(*regiony_)[i]->getCentralnySklad().getVozovyPark()->add(vozidlo);
				cout << "Vozidlo bolo pridane uspesne" << endl;
				return true;
			}
		}
	}
	return false;
	
}


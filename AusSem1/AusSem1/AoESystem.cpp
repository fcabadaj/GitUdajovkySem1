#include "AoESystem.h"
#include "structures/heap_monitor.h"

using namespace eRegiony;

AoESystem::AoESystem():
	regiony_(new Array<Region*>(25)),
	datum_(new Datum(1))
{	
	initRegiony();
}

AoESystem::~AoESystem()
{
	for (unsigned int i = 0; i < regiony_->size(); i++)
	{
		delete (*regiony_)[i];
	}
	delete regiony_;
	regiony_ = nullptr;

	delete datum_;
	datum_ = nullptr;
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

bool AoESystem::skontrolujSC(int sCislo)
{
	if (sCislo > 10000 || sCislo < 1)
	{
		cout << "Hodnoty serioveho cisla su platne od 1 - 9999! \n";
		return false;
	}
	for (unsigned int i = 0; i < regiony_->size(); i++)
	{
		if (regiony_->operator[](i)->getLokalnySklad()->skontrolujSCislo(sCislo) == false)
			return false;
	}
	return true;
}

bool AoESystem::skontrolujSPZ(string spz)
{
	if (spz.length() != 7)
	{
		cout << "Zle zadana SPZ, Musi mat 7 znakov \n";
		return false;
	}
	return regiony_->operator[](0)->getCentralnySklad()->skontrolujSPZ(spz);
}

bool AoESystem::skontrolujZamietnutieObj(Datum *datum, Objednavka *objednavka)
{
	Sklad *skladVyzdvihnutia = nullptr;

	for (unsigned int i = 0; i < regiony_->size(); i++)
	{
		if (regiony_->operator[](i)->getNazovRegionu() == objednavka->getRegionVyzdvihnutia())
			skladVyzdvihnutia = regiony_->operator[](i)->getLokalnySklad();
	}

	if (skladVyzdvihnutia->skontrolujZamietnutieObj(datum, objednavka)) 
	{	
		return true;
	}

	return false;
}

bool AoESystem::pridajVozidlo(eRegiony::EnumRegion nazovRegionu, string spz, int nosnost, int prevadzkoveNaklady)
{
	if (skontrolujSPZ(spz))
	{
		Datum *datum = new Datum(*datum_);
		Vozidlo *vozidlo = new Vozidlo(spz, nosnost, prevadzkoveNaklady, datum);

		for (unsigned int i = 0; i < regiony_->size(); i++)
		{
			if ((*regiony_)[i]->getNazovRegionu() == nazovRegionu)
			{
				(*regiony_)[i]->getCentralnySklad()->getVozovyPark()->add(vozidlo);
				cout << "Vozidlo bolo pridane uspesne " << endl;
				return true;
			}
		}
	}
	return false;	
}


bool AoESystem::pridajDrona(eRegiony::EnumRegion nazovRegionu, int sCislo, int typ)
{
	if (skontrolujSC(sCislo))
	{
		int nosnost = 0;
		int rychlost = 0;
		int dobaLetu = 0;
		int dobaNabijania = 0;

		if (typ == 1)
		{
			nosnost = 2;
			rychlost = 80;
			dobaLetu = 40;
			dobaNabijania = 3;
			
		}
		else if(typ == 2)
		{
			nosnost = 5;
			rychlost = 40;
			dobaLetu = 60;
			dobaNabijania = 5;
		}
		
		Datum *datum = new Datum(*datum_);
		Dron *dron = new Dron(sCislo, typ, nosnost, rychlost, dobaLetu, dobaNabijania,datum);

		for (unsigned int i = 0; i < regiony_->size(); i++)
		{
			if (regiony_->operator[](i)->getNazovRegionu() == nazovRegionu)
			{
				regiony_->operator[](i)->getLokalnySklad()->getDrony()->add(dron);
				cout << "Dron bol uspesne pridany \n";
				return true;
			}
		}
	}
	return false;
}

bool AoESystem::pridajObjednavku(int id, int hmotnost, eRegiony::EnumRegion regionVyzdvihnutia, eRegiony::EnumRegion regionDorucenia, int vzdOdSkladuVyzdvihnutia, int vzdOdSkladuDorucenia)
{
	bool dorucenie = false;
	Datum *datum = new Datum(*datum_);
	Objednavka *objednavka = new Objednavka(id,hmotnost,regionVyzdvihnutia,regionDorucenia,vzdOdSkladuVyzdvihnutia,vzdOdSkladuDorucenia);

	if (skontrolujZamietnutieObj(datum, objednavka))
	{
		for (unsigned int i = 0; i < regiony_->size(); i++)
		{
			if (regiony_->operator[](i)->getNazovRegionu() == regionVyzdvihnutia)
			{
				regiony_->operator[](i)->getLokalnySklad()->getObjednavky()->add(objednavka);
				delete datum;
				cout << "Objednavka bola prijata \n";

				if (regionVyzdvihnutia == regionDorucenia)
					dorucenie = true;

					objednavka->setNaDorucenie(dorucenie);

				return true;
			}
		}
	}

	// pridanie objednavky do ArrayListu zrusenych objednavok
	for (unsigned int i = 0; i < regiony_->size(); i++)
	{
		if (regiony_->operator[](i)->getNazovRegionu() == regionVyzdvihnutia)
		{
			regiony_->operator[](i)->getLokalnySklad()->getZamietnuteObjednavky()->add(objednavka);
			delete datum;
			cout << "Objednavka bola zamietnuta!! \n";
			return false;
		}
	}
	
	return false;
}

void AoESystem::vypisVozidla()
{
	cout << "Vypis vozidiel v centralnom sklade regionu ZA \n";
	regiony_->operator[](0)->getCentralnySklad()->vypisVozidla();
}

void AoESystem::vypisDrony()
{
	for (unsigned int i = 0; i < regiony_->size(); i++)
	{
		regiony_->operator[](i)->getLokalnySklad()->vypisDrony();
	}
}

void AoESystem::vypisObjednavky()
{
	for (unsigned int i = 0; i < regiony_->size(); i++)
	{
		regiony_->operator[](i)->getLokalnySklad()->vypisObjednavky();
	}
}

void AoESystem::initRegiony()
{
	regiony_->operator[](0) = new Region(eRegiony::ZA, new CentralnySklad());

	for (unsigned int i = 1; i < regiony_->size(); i++)
	{
		EnumRegion nazovRegionu{ static_cast<EnumRegion>(i) };
		regiony_->operator[](i) = new Region(nazovRegionu);
	}
}

void AoESystem::pridajHodinu()
{
	datum_->pridajHodinu();
}

void AoESystem::vypisDatum()
{
	datum_->vypisSa();
}

void AoESystem::vypisZamietnuteObjednavky()
{
	for (unsigned int i = 0; i < regiony_->size(); i++)
	{
		regiony_->operator[](i)->getLokalnySklad()->vypisZamietnuteObjednavky();
	}
}




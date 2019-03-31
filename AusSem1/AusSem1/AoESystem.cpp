#include "AoESystem.h"
#include "structures/heap_monitor.h"
#include <windows.h>
#include <fstream>
#include <cstdlib>
#include <cmath>

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
		delete regiony_->operator[](i);
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
	return eRegiony::ZA;
}

//skontroluje unikatnost serioveho cisla drona
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

//skontroluje unikatnost SPZ auta
bool AoESystem::skontrolujSPZ(string spz)
{
	if (spz.length() != 7)
	{
		cout << "Zle zadana SPZ, Musi mat 7 znakov \n";
		return false;
	}
	return regiony_->operator[](0)->getCentralnySklad()->skontrolujSPZ(spz);
}

//ak by prijatie objednavky porusilo niektore z podmienok, zamietne objednavku
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

//kontrola ID pre objednavku
bool AoESystem::skontrolujId(Objednavka *objednavka)
{
	for (unsigned int i = 0; i < regiony_->size(); i++)
	{

	}
	return false;
}

//pridanie vozidla do centralneho skladu
bool AoESystem::pridajVozidlo(eRegiony::EnumRegion nazovRegionu, string spz, double nosnost)
{
	if (skontrolujSPZ(spz))
	{
		Datum *datum = new Datum(*datum_);
		Vozidlo *vozidlo = new Vozidlo(spz, nosnost, datum);

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

//pridavanie drona do skladu daneho regionu, kde sa tiez podla typu drona urcia atributy
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

bool AoESystem::pridajObjednavku(int id, double hmotnost, eRegiony::EnumRegion regionVyzdvihnutia, eRegiony::EnumRegion regionDorucenia, int vzdOdSkladuVyzdvihnutia, int vzdOdSkladuDorucenia)
{
	bool dorucenie = false;
	Datum *datum = new Datum(*datum_);

	Objednavka *objednavka = new Objednavka(id,hmotnost,regionVyzdvihnutia,regionDorucenia,vzdOdSkladuVyzdvihnutia,vzdOdSkladuDorucenia, datum);

	if (skontrolujZamietnutieObj(datum, objednavka))
	{
		for (unsigned int i = 0; i < regiony_->size(); i++)
		{
			if (regiony_->operator[](i)->getNazovRegionu() == regionVyzdvihnutia)
			{
				regiony_->operator[](i)->getLokalnySklad()->getPrijateObjednavky()->add(objednavka);
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

//Uvedie array regionov do pociatocneho stavu
void AoESystem::initRegiony()
{
	regiony_->operator[](0) = new Region(eRegiony::ZA, new CentralnySklad());

	for (unsigned int i = 1; i < regiony_->size(); i++)
	{
		EnumRegion nazovRegionu{ static_cast<EnumRegion>(i) };
		regiony_->operator[](i) = new Region(nazovRegionu);
	}
}

/*
	pridaj hodinu sluzi na pridanie jednej hodiny do systemoveho casu
	ako aj signalizovanie skladu aby vyslal dronov na vyzdvihnutie alebo dorucenie objednavky
	a o 21 hodine, signal vozidlam aby porozvazali zasielky
*/
void AoESystem::pridajHodinu()
{
	Datum *datum = new Datum(*datum_);
	bool vozidlaDorucili = false;

	datum_->pridajHodinu();

	if (datum_->getHodina() == 21 || datum_->getHodina() == 7)
		cout << "Objednavky sa v tuto hodinu nevybavuju! \n";
	else
		vybavObjednavky(datum);
		

	if (datum_->getHodina() == 21)
		vozidlaDorucili = vysliVozidla();

	if (datum_->getHodina() == 7 && vozidlaDorucili)
		cout << "Objednavky boli prevezene do prislusnych skladov! \n";

	delete datum;
}

void AoESystem::vybavObjednavky(Datum *datum)
{
	for (unsigned int i = 0; i < regiony_->size(); i++)
	{
		regiony_->operator[](i)->getLokalnySklad()->vybavObjednavky(datum);
	}
}

bool AoESystem::vysliVozidla()
{
	if (regiony_->operator[](0)->getCentralnySklad()->getVozovyPark()->size() == 0)
	{
		cout << "Vozidlo nie je k dispozicii, objednavky nebudu prevezene! \n";
		return false;
	}
	
	double celkNaklady = 0;
	ArrayList<Vozidlo*> *vozidla;
	ArrayList<Objednavka*> *objednavkyVSklade;
	Objednavka *objednavka;
	vozidla = regiony_->operator[](0)->getCentralnySklad()->getVozovyPark();

	Vozidlo *vozidlo = nullptr;

	if (vozidla->size() == 1)
	{
		Sleep(100);
		cout << "======================================================= \n";
		cout << "Vozidlo zbiera objednavky z lokalnych skladov \n";
		vozidlo = vozidla->operator[](0);

		// objednavky zo vsetkych skladov ktore nie su na dorucenie v danom regione sa odovzdaju vozidlu
		for (unsigned int i = 0; i < regiony_->size(); i++)
		{
			regiony_->operator[](i)->getLokalnySklad()->odovzdajObjednavkyVozidlu(vozidlo);
		}

		Sleep(100);
		cout << "======================================================= \n";
		cout << "Objednavky boli nalozene \n";
		cout << "======================================================= \n";

		//objednavky sa rozvezu do prislusnych skladov
		for (unsigned int i = 0; i < regiony_->size(); i++)
		{
			regiony_->operator[](i)->getLokalnySklad()->vyberObjZVozidla(vozidlo, regiony_->operator[](i)->getNazovRegionu());
		}

		if (vozidlo->getObjednavky()->size() != 0)
			cout << "Nepodarilo sa vylozit vsetky objednavky! \n";

		//aktualizacia celkovych prevadzkovych nakladov pre vozidlo
		celkNaklady = static_cast<double>(vozidlo->getCelkPrevNaklady());
		double prevNaklady = vozidlo->getPrevNaklady();
		double pocetReg = static_cast<double>(vozidlo->getRegiony()->size());
		double aktNaklady = 2.0 * prevNaklady * pocetReg;
		celkNaklady += aktNaklady;
		vozidlo->setCelkPrevNaklady(celkNaklady);

		int pocetRegionov = static_cast<int>(vozidlo->getRegiony()->size());
		int kilometre = (20 * 2 * pocetRegionov) + vozidlo->getCelkPocetKilometrov();
		vozidlo->setCelkPocetKilometrov(kilometre);

		cout << "======================================================= \n";
		cout << "Celkove prevadzkove naklady vozidla boli aktualizovane! \n";
		cout << "======================================================= \n";
		return true;
	}
	else
	{
		cout << "Not implemented yet \n";
		return false;
	}
	return false;
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

void AoESystem::zapisDoSuboru()
{
	ofstream subor;
	subor.open("output.txt");
	eRegiony::EnumRegion nazovRegionu;
	
	if (regiony_->operator[](0)->getCentralnySklad()->getVozovyPark()->size() != 0)
		subor << regiony_->operator[](0)->getCentralnySklad()->getVozovyPark()->operator[](0)->zapisDoSuboru();

	for (unsigned int i = 0; i < regiony_->size(); i++)
	{
		if (regiony_->operator[](i)->getLokalnySklad()->getDrony()->size() != 0)
		{
			nazovRegionu = regiony_->operator[](i)->getNazovRegionu();
			subor << regiony_->operator[](i)->getLokalnySklad()->zapisDrony(nazovRegionu);
		}
	}

	for (unsigned int i = 0; i < regiony_->size(); i++)
	{
		if (regiony_->operator[](i)->getLokalnySklad()->getPrijateObjednavky()->size() != 0)
		{
			nazovRegionu = regiony_->operator[](i)->getNazovRegionu();
			subor << regiony_->operator[](i)->getLokalnySklad()->zapisObjednavky();
		}
	}

	subor.close();
}

void AoESystem::nacitajZoSuboru()
{
	ifstream subor("input.txt");
	int sCislo;
	int typ;
	int region;
	int objekt;
	string spz;
	double nosnost;
	int id;
	int hmotnost;
	int regV;
	int regD;
	int vzdV;
	int vzdD;

	while (subor >> objekt)
	{
		switch (objekt)
		{
		case 1:
			subor >> region >> sCislo >> typ;
			this->pridajDrona(static_cast<EnumRegion>(region), sCislo, typ);
			break;
		case 2:
			subor >> region >> spz >> nosnost;
			this->pridajVozidlo(static_cast<EnumRegion>(region), spz, nosnost);
			break;
		case 3:
			subor >> id >> hmotnost >> regV >> regD >> vzdV >> vzdD;
			this->pridajObjednavku(id, hmotnost, static_cast<EnumRegion>(regV), static_cast<EnumRegion>(regD), vzdV, vzdD);
			break;
		default:
			break;
		}
	}
}

void AoESystem::prejdiNa21H()
{
	do
	{
		pridajHodinu();
		Sleep(50);
	} while (datum_->getHodina() != 21);
}

void AoESystem::vypisStatistik()
{
	system("CLS");
	int i = 0;
	cout << "======================================================= \n";
	cout << "stlac 0 - region do ktoreho bolo dorucenych najviac zasielok \n";
	cout << "stlac 1 - region z ktoreho bolo odoslanych najviac zasielok \n";
	cout << "stlac 2 - vypis zamietnutych objednavok \n";
	cout << "stlac 3 - vypis zrusenych objednavok \n";
	cout << "stlac 4 - vypis celkoveho poctu dorucenych zasielok\n";
	cout << "stlac 5 - vypis celkoveho poctu najazdenych kilometrov vozidiel\n";
	cout << "stlac 6 - vypis celkoveho poctu nalietanych hodin jednotlivych typov dronov\n";
	cout << "stlac 7 - PRE NAVRAT DO HLAVNEHO MENU \n";
	cout << "======================================================= \n";
	cin >> i;

	int denOd = 0;
	int denDo = 0;
	int reg = 0;
	int pocetZasielok = 0;
	double nalietaneHodiny = 0;
	Region *najlepsi = regiony_->operator[](0);
	int index = 0;

	switch (i)
	{
	case 0:
		for (unsigned int i = 1; i < regiony_->size(); i++)
		{
			if (najlepsi->getLokalnySklad()->getPocetDorucenychZasielok() < regiony_->operator[](i)->getLokalnySklad()->getPocetDorucenychZasielok())
			{
				najlepsi = regiony_->operator[](i);
				index = i;
			}
		}
		cout << "Najviac dorucenych zasielok ma region: " << getMenoRegionu(index) << " " << najlepsi->getLokalnySklad()->getPocetDorucenychZasielok() << endl;

		break;

	case 1:
		for (unsigned int i = 1; i < regiony_->size(); i++)
		{
			if (najlepsi->getLokalnySklad()->getPocetOdoslanychZasielok() < regiony_->operator[](i)->getLokalnySklad()->getPocetOdoslanychZasielok())
			{
				najlepsi = regiony_->operator[](i);
				index = i;
			}
		}
		cout << "Najviac odoslanych zasielok ma region: " << getMenoRegionu(index) << " " << najlepsi->getLokalnySklad()->getPocetOdoslanychZasielok() << endl;

		break;

	case 2:
		cout << "vypis zamietnutych objednavok \n";
		cout << "======================================================= \n";
		cout << "Zadaj den od: \n";
		cin >> denOd;
		cout << "Zadaj den do: \n";
		cin >> denDo;
		cout << "Zadaj region: \n";
		cout << "0 = ZA, 1 = MA, 2 = BA, 3 = TT, 4 = KN, 5 = LV \n 6 = TN, 7 = PD,  8 = MT, 9 = NR, 10 = CA, 11 = NO \n 12 = LM, 13 = BB, 14 = ZV, 15 = KA, 16 = LC, 17 = RA \n 18 = PP, 19 = SL, 20 = SN, 21 = KE, 22 = PO, 23 = HE, 24 = MI \n";
		cin >> reg;
		cout << "V regione " << getMenoRegionu(reg) << " su tieto zamietnute objednavky" << endl;
		for (unsigned int i = 0; i < regiony_->size(); i++)
		{
			if (regiony_->operator[](i)->getNazovRegionu() == static_cast<eRegiony::EnumRegion>(reg))
			{
				if (regiony_->operator[](i)->getLokalnySklad()->getZamietnuteObjednavky()->size() == 0)
					cout << "V zadanom regione nie su ziadne zamietnute objednavky \n";
				else
				regiony_->operator[](i)->getLokalnySklad()->statVypisZamietnuteObjednavky(denOd, denDo);
			}
		}
		break;

	case 3:
		cout << "vypis zrusenych objednavok \n";
		cout << "======================================================= \n";
		cout << "Zadaj den od: \n";
		cin >> denOd;
		cout << "Zadaj den do: \n";
		cin >> denDo;

		for (unsigned int i = 0; i < regiony_->size(); i++)
		{			
			cout << "Region: " << getMenoRegionu(i) << endl;
			regiony_->operator[](i)->getLokalnySklad()->statVypisZruseneObjednavky(denOd, denDo);			
		}
		break;

	case 4:		
		cout << "vypis celkoveho poctu dorucenych zasielok\n";
		cout << "======================================================= \n";
		for (unsigned int i = 0; i < regiony_->size(); i++)
		{
			pocetZasielok += static_cast<int>(regiony_->operator[](i)->getLokalnySklad()->getVybaveneObjednavky()->size());
		}
		cout << "Celkovy pocet dorucenych zasielok je: " << pocetZasielok << endl;
		break;

	case 5:
		cout << "vypis celkoveho poctu najazdenych kilometrov vozidiel\n";
		cout << "======================================================= \n";
		if (regiony_->operator[](0)->getCentralnySklad()->getVozovyPark()->size() != 0)
			cout << "Vozidla spolu najazdili: " << regiony_->operator[](0)->getCentralnySklad()->getVozovyPark()->operator[](0)->getCelkPocetKilometrov() << endl;
		else
			cout << "Ziadne vozidlo nie je v tomto systeme zaregistrovane \n";		
		break;

	case 6:
		cout << "vypis celkoveho poctu nalietanych hodin jednotlivych typov dronov\n";
		cout << "======================================================= \n";
		for (unsigned int i = 0; i < regiony_->size(); i++)
		{
			cout << "Region: " << getMenoRegionu(i) << endl;
			regiony_->operator[](i)->getLokalnySklad()->statVypisDrony();
		}
		break;

	case 7:
		break;
	default:
		break;
	}
}

string AoESystem::getMenoRegionu(int reg)
{
	string mena[25]{ "ZA","MA","BA","TT","KN","LV","TN","PD","MT","NR","CA","NO","LM","BB","ZV","KA","LC","RA","PP","SL","SN","KE","PO","HE","MI" };
	return mena[reg];
}





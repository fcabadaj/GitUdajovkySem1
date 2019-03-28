#include "structures/heap_monitor.h"
#include "Sklad.h"
#include <iostream>

using namespace std;

Sklad::Sklad():
	drony_(new ArrayList<Dron*>),
	prijateObjednavky_(new ArrayList<Objednavka*>),
	zamietnuteObjednavky_(new ArrayList<Objednavka*>),
	prevzateObjednavky_(new ArrayList<Objednavka*>),
	vybaveneObjednavky_(new ArrayList<Objednavka*>)
{
}

Sklad::~Sklad()
{
	for (unsigned int i = 0; i < drony_->size(); i++)
	{
		delete drony_->operator[](i);
	}
	delete drony_;
	drony_ = nullptr;

	for (unsigned int i = 0; i < prijateObjednavky_->size(); i++)
	{
		delete prijateObjednavky_->operator[](i);
	}
	delete prijateObjednavky_;
	prijateObjednavky_ = nullptr;
	
	for (unsigned int i = 0; i < zamietnuteObjednavky_->size(); i++)
	{
		delete zamietnuteObjednavky_->operator[](i);
	}
	delete zamietnuteObjednavky_;
	zamietnuteObjednavky_ = nullptr;

	for (unsigned int i = 0; i < prevzateObjednavky_->size(); i++)
	{
		delete prevzateObjednavky_->operator[](i);
	}
	delete prevzateObjednavky_;
	prevzateObjednavky_ = nullptr;

	for (unsigned int i = 0; i < vybaveneObjednavky_->size(); i++)
	{
		delete vybaveneObjednavky_->operator[](i);
	}
	delete vybaveneObjednavky_;
	vybaveneObjednavky_ = nullptr;
}

//vrati objednavku podla ID
Objednavka * Sklad::getObjednavka(int id)
{
	for (unsigned int i = 0; i < prijateObjednavky_->size(); i++)
	{
		if (prijateObjednavky_->operator[](i)->getId() == id)
			return prijateObjednavky_->operator[](i);
	}
	return nullptr;
}

//vypise drony v danom sklade
void Sklad::vypisDrony()
{
	for (unsigned int i = 0; i < drony_->size(); i++)
	{
		drony_->operator[](i)->vypisSa();
	}
}

//vypise vsetky prijate objednavky
void Sklad::vypisObjednavky()
{
	for (unsigned int i = 0; i < prevzateObjednavky_->size(); i++)
	{
		prevzateObjednavky_->operator[](i)->vypisSa();
	}
}

//vypise zamietnute objednavky
void Sklad::vypisZamietnuteObjednavky()
{
	for (unsigned int i = 0; i < zamietnuteObjednavky_->size(); i++)
	{
		zamietnuteObjednavky_->operator[](i)->vypisSa();
	}
}

void Sklad::vybavObjednavky(Datum *datum)
{	
	Dron *najDron = nullptr;
	Objednavka *objednavka = nullptr;
	int vzdialenost = 0;

	//najskor chcem vybavit vsetky objednavky na dorucenie
	for (unsigned int i = 0; i < prevzateObjednavky_->size(); i++)
	{
		objednavka = prevzateObjednavky_->operator[](i);
		if (objednavka->getNaDorucenie() && objednavka->getPrevzata())
		{
			if (najdiNajlepsiehoDrona(objednavka) == nullptr)
				cout << "Drony nie su k dispozicii \n";
			else
			{
				najDron = najdiNajlepsiehoDrona(objednavka);
				bool dorucil = najDron->vybavDorucenieObjednavky(objednavka);
				if (dorucil)
				{
					cout << "Objednavka s ID " << objednavka->getId() << " bola dorucena! \n";
					vybaveneObjednavky_->add(objednavka);
					prevzateObjednavky_->tryRemove(objednavka);
				}
				else
					cout << "Objednavka s ID " << objednavka->getId() << "nebola uspesne dorucena! \n";
			}
		}
	}

	for (unsigned int i = 0; i < prijateObjednavky_->size(); i++)
	{
		objednavka = prijateObjednavky_->operator[](i);
		if (objednavka->getPrevzata() == false)
		{
			if (najdiNajlepsiehoDrona(objednavka) == nullptr)
				cout << "Drony nie su k dispozicii \n";
			else
			{
				najDron = najdiNajlepsiehoDrona(objednavka);
				bool vyzdvihol = najDron->vybavVyzdvihnutieObjednavky(objednavka);

				if (vyzdvihol)
				{
					objednavka->setPrevzata(true);
					cout << "Objednavka s ID " << objednavka->getId() << " bola prevzata a zaradena do objednavok na dorucenie! \n";
					prevzateObjednavky_->add(objednavka);
					prijateObjednavky_->tryRemove(objednavka);
				}
				else
					cout << "Objednavka s ID " << objednavka->getId() << " nebola prevzata!!! \n";
			}
		}
	}
	/*
	TO DO: bateriu a dolet setovat podla niecoho normalneho
	*/
	//po vybaveni vsetkych moznych objednavok sa drony vratia do skladu a nabiju sa
	for (unsigned int i = 0; i < drony_->size(); i++)
	{
		drony_->operator[](i)->setJeVSklade(true);

		if (drony_->operator[](i)->getTyp() == 1)
		{
			drony_->operator[](i)->setBateriu(100);
			drony_->operator[](i)->setAktDolet(drony_->operator[](i)->getMaxDolet());
		}
	}	
}


void Sklad::presunPrijateObj()
{
	for (unsigned int i = 0; i < prijateObjednavky_->size(); i++)
	{
		if (prijateObjednavky_->operator[](i)->getRegionDorucenia() == prijateObjednavky_->operator[](i)->getRegionVyzdvihnutia())
		{			
			prevzateObjednavky_->add(prijateObjednavky_->operator[](i));
			prijateObjednavky_->removeAt(i);
		}
	}
}

//skontroluje seriove cislo dronov, ci uz ho nejaky nema
bool Sklad::skontrolujSCislo(int cislo)
{
	for (unsigned int i = 0; i < drony_->size(); i++)
	{
		if (drony_->operator[](i)->getSCislo() == cislo)
		{
			cout << "Dron s takymto seriovym cislom uz existuje! \n";
			return false;
		}
	}
	return true;
}

//podmienky zamietnutia objednavky + nastavenie statusu zamietnutia
bool Sklad::skontrolujZamietnutieObj(Datum *datum, Objednavka *objednavka)
{
	std::string status = "";

	if (datum->getHodina() >= 20) 
	{
		status = "Objednavka sa v den " + to_string(datum->getDen()) + " nestihne vybavit!";
		objednavka->setStatus(status);
		return false;
	}	

	if (objednavka->getHmotnost() > 5)
	{
		status = "Objednavka ma vacsiu ako povolenu hmotnost!";
		objednavka->setStatus(status);
		return false;
	}

	if (!skontrolujRadiusDronov(objednavka)) 
	{
		status = "Vzdialenost objednavky je mimo radius dronov!";
		objednavka->setStatus(status);
		return false;
	}

	if (pridajDronaObjednavke(objednavka) == nullptr)
	{
		status = "Dron nie je k dispozicii!";
		objednavka->setStatus(status);
		return false;
	}

	if (!stihneVyzdvihnut(objednavka, datum))
	{
		status = "Spolocnost nedokaze vyzdvihnut objednavky pred 20:00";
		objednavka->setStatus(status);
		return false;
	}
	
	return true;
}

//skontroluje ci nie je objednavka mimo radius dronov podla hmotnosti objednavky a teda typu drona
bool Sklad::skontrolujRadiusDronov(Objednavka *objednavka)
{
	double rychlost = 0.0;
	double dobaLetu = 0.0;
	double radiusDrona = 0.0;

	if (objednavka->getHmotnost() <= 2)
	{		
		rychlost = 80;
		dobaLetu = 40;
	}	
	else if (objednavka->getHmotnost() > 2)
	{		
		rychlost = 40;
		dobaLetu = 60;
	}

	radiusDrona = (rychlost / 60)*dobaLetu;
	radiusDrona /= 2;

	//kontrola radiusu aj pre region vyzdvihnutia aj dorucenia
	if (static_cast<int>(radiusDrona) < objednavka->getvzdOdSkladuDorucenia() || static_cast<int>(radiusDrona) < objednavka->getvzdOdSkladuVyzdvihnutia())
		return false;
	else
		return true;
}

//skontroluje ci sa objednavka stihne vyzdvihnut do 20:00
bool Sklad::stihneVyzdvihnut(Objednavka *objednavka, Datum *datum)
{
	double casVybaveniaObjednavok = 0.0;

	//celkovy cas dorucenia vsetkych objednavok
	for (unsigned int i = 0; i < prijateObjednavky_->size(); i++)
	{
		if (prijateObjednavky_->operator[](i)->getNaDorucenie())
		{
			casVybaveniaObjednavok += prijateObjednavky_->operator[](i)->getDron()->getCasDorucenia();
		}		
	}
	if (datum->getHodina() + static_cast<int>(ceil(casVybaveniaObjednavok)) + static_cast<int>(objednavka->getDron()->getCasVyzdvihnutia()) >= 20)
		return false;
	else
		return true;
}

bool Sklad::odovzdajObjednavkyVozidlu(Vozidlo *vozidlo)
{
	//presunutie objednavok ktore nie su na dorucenie v tomto regione do vozidla
	for (unsigned int i = 0; i < prevzateObjednavky_->size(); i++)
	{
		if (prevzateObjednavky_->operator[](i)->getNaDorucenie() == false)
		{
			vozidlo->getObjednavky()->add(prevzateObjednavky_->operator[](i));			
			cout << "Objednavky boli nalozene \n";
		}
	}

	for (unsigned int i = 0; i < vozidlo->getObjednavky()->size(); i++)
	{
		prevzateObjednavky_->tryRemove(vozidlo->getObjednavky()->operator[](i));
	}

	return true;
}

bool Sklad::vyberObjZVozidla(Vozidlo * vozidlo, eRegiony::EnumRegion nazovReg)
{
	Objednavka *objednavka;

	for (unsigned int i = 0; i < vozidlo->getObjednavky()->size(); i++)
	{
		objednavka = vozidlo->getObjednavky()->operator[](i);

		if (nazovReg == objednavka->getRegionDorucenia())
		{
			objednavka->setNaDorucenie(true);
			prevzateObjednavky_->add(objednavka);
			cout << "Objednavka s ID: " << objednavka->getId() << " bola dovezena do skladu dorucenia! \n";
			vozidlo->getObjednavky()->tryRemove(objednavka);
		}
	}
	return false;
}

// prida drona objednavke pre pristup k jeho atributom 
// a vyhne sa moznemu nullptr
Dron * Sklad::pridajDronaObjednavke(Objednavka * objednavka)
{	
	double casDorucenia = 0; 
	double casVyzdvihnuta = 0;

	if (drony_ == nullptr)
		return nullptr;

	if (drony_->size() == 0)	
		return nullptr;	

	if (objednavka->getHmotnost() <= 2)
	{
		for (unsigned int i = 0; i < drony_->size(); i++)
		{
			if (drony_->operator[](i)->getTyp() == 1 || drony_->operator[](i)->getTyp() == 2)
			{
				objednavka->setDron(drony_->operator[](i));
				casDorucenia = static_cast<double>(objednavka->getvzdOdSkladuDorucenia()) / static_cast<double>(drony_->operator[](i)->getRychlost());
				casVyzdvihnuta =  static_cast<double>(objednavka->getvzdOdSkladuVyzdvihnutia()) / static_cast<double>(drony_->operator[](i)->getRychlost());
				drony_->operator[](i)->setCasDorucenia(casDorucenia);
				drony_->operator[](i)->setCasVyzdvihnutia(casVyzdvihnuta);
				return drony_->operator[](i);
			}
		}
	} 
	else
	{
		for (unsigned int i = 0; i < drony_->size(); i++)
		{
			if (drony_->operator[](i)->getTyp() == 2)
			{
				objednavka->setDron(drony_->operator[](i));
				casDorucenia = static_cast<double>(objednavka->getvzdOdSkladuDorucenia()) / static_cast<double>(drony_->operator[](i)->getRychlost());
				casVyzdvihnuta = static_cast<double>(objednavka->getvzdOdSkladuVyzdvihnutia()) / static_cast<double>(drony_->operator[](i)->getRychlost());
				drony_->operator[](i)->setCasDorucenia(casDorucenia);
				drony_->operator[](i)->setCasVyzdvihnutia(casVyzdvihnuta);
				return drony_->operator[](i);
			}
		}
	}
	return nullptr;
}

//najde najlepsieho drona podla stanovenych podmienok
Dron * Sklad::najdiNajlepsiehoDrona(Objednavka *objednavka)
{
	if (drony_->size() == 0)
		return nullptr;

	bool prehladaneTyp1 = false;
	ArrayList<Dron*> *najlepsieDrony = new ArrayList<Dron*>;
	Dron *najlepsiDron = nullptr;

	//podla hmotnosti objednavky prehladava drony, uprednostnuje drona s najmensou hmotnostou a najlepsim stavom baterie
	for (unsigned int i = 0; i < drony_->size(); i++)
	{
		if (objednavka->getHmotnost() > 2)
		{
			if (drony_->operator[](i)->getTyp() == 2 && drony_->operator[](i)->getJeVSklade() == true)
			{
				najlepsieDrony->add(drony_->operator[](i));
			}
		}
		else
		{
			if (drony_->operator[](i)->getTyp() == 1 && drony_->operator[](i)->getJeVSklade() == true)
			{
				najlepsieDrony->add(drony_->operator[](i));
			}
		}	
	}

	if (objednavka->getHmotnost() < 2 && najlepsieDrony->size() == 0)
		prehladaneTyp1 = true;

	//ak sa nenajde dron pre hmotnost < 2 v dronoch typu 1, prehladam este drony typu 2
	if (prehladaneTyp1)
	{
		for (unsigned int i = 0; i < drony_->size(); i++)
		{
			if (drony_->operator[](i)->getTyp() == 2 && drony_->operator[](i)->getJeVSklade() == true)
			{
				najlepsieDrony->add(drony_->operator[](i));
			}
		}
	}

	//ak nenajde ziadneho volneho drona zavola sa 'najskor skonci'
	if (najlepsieDrony->size() == 0)
		najlepsiDron = najskorSkonci(objednavka);
	else
	{
		//z najlepsich dronov ten co ma najviac baterie
		najlepsiDron = drony_->operator[](0);
		for (unsigned int i = 0; i < najlepsieDrony->size() - 1; i++)
		{
			if (drony_->operator[](i + 1)->getStavBaterie() > najlepsiDron->getStavBaterie())
			{
				najlepsiDron = drony_->operator[](i + 1);
			}
		}
	}

	delete najlepsieDrony;
	return najlepsiDron;
}

//najde drona ktory najskor dokonci svoju objednavku
Dron * Sklad::najskorSkonci(Objednavka *objednavka)
{
	double casDoNavratu = 10000000;
	Dron *najeplsiDron = nullptr;

	for (unsigned int i = 0; i < drony_->size(); i++)
	{
		if (drony_->operator[](i)->getObjednavku()->getPrevzata())
		{
			if (casDoNavratu > drony_->operator[](i)->getCasDorucenia() && objednavka->getvzdOdSkladuDorucenia() <= drony_->operator[](i)->getAktDolet())
			{
				casDoNavratu = drony_->operator[](i)->getCasDorucenia();
				najeplsiDron = drony_->operator[](i);
			}
			
		} 
		else if (!(drony_->operator[](i)->getObjednavku()->getPrevzata()))
		{
			if (casDoNavratu > drony_->operator[](i)->getCasVyzdvihnutia() && objednavka->getvzdOdSkladuVyzdvihnutia() <= drony_->operator[](i)->getAktDolet())
			{
				casDoNavratu = drony_->operator[](i)->getCasDorucenia();
				najeplsiDron = drony_->operator[](i);
			}
		}	
	}

	char input;

	if (najeplsiDron == nullptr)
		return nullptr;

	//ak by sa nenasiel dron co to stine vyzdvihnut do hodiny tak ma moznost zakaznik zrusit objednavku
	if (!najeplsiDron->getObjednavku()->getPrevzata())
	{
		if (casDoNavratu + objednavka->getDron()->getCasDorucenia() > 1 || casDoNavratu + objednavka->getDron()->getCasVyzdvihnutia() > 1)
		{			
			cout << "Vyzdvihnutie objednavky bude trvat viac ako hodinu, chcete objednavku zrusit? \n y(ano)/n(nie)";
			cin >> input;
			if (input == 'y')
				return nullptr;
		}
	}
	return najeplsiDron;
}

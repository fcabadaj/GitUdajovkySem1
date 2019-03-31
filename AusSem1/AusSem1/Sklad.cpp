#include "structures/heap_monitor.h"
#include "Sklad.h"
#include <iostream>
#include <windows.h>

using namespace std;

Sklad::Sklad(int pdz, int poz):
	drony_(new ArrayList<Dron*>),
	prijateObjednavky_(new ArrayList<Objednavka*>),
	zamietnuteObjednavky_(new ArrayList<Objednavka*>),
	prevzateObjednavky_(new ArrayList<Objednavka*>),
	vybaveneObjednavky_(new ArrayList<Objednavka*>),
	zruseneObjednavky_(new ArrayList<Objednavka*>),
	pocetDorucenychZasielok_(pdz),
	pocetOdoslanychZasielok_(poz)
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

	for (unsigned int i = 0; i < zruseneObjednavky_->size(); i++)
	{
		delete zruseneObjednavky_->operator[](i);
	}
	delete zruseneObjednavky_;
	zruseneObjednavky_ = nullptr;
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
	for (unsigned int i = 0; i < prijateObjednavky_->size(); i++)
	{
		prijateObjednavky_->operator[](i)->vypisSa();
	}

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

void Sklad::statVypisZamietnuteObjednavky(int denOd, int denDo)
{
	for (unsigned int i = 0; i < zamietnuteObjednavky_->size(); i++)
	{
		if (zamietnuteObjednavky_->operator[](i)->getDatum()->getDen() >= denOd && zamietnuteObjednavky_->operator[](i)->getDatum()->getDen() <= denDo)
		{
			zamietnuteObjednavky_->operator[](i)->vypisSa();
		}		
	}
}

void Sklad::statVypisZruseneObjednavky(int denOd, int denDo)
{
	for (unsigned int i = 0; i < zruseneObjednavky_->size(); i++)
	{
		if (zruseneObjednavky_->operator[](i)->getDatum()->getDen() >= denOd && zruseneObjednavky_->operator[](i)->getDatum()->getDen() <= denDo)
		{
			zruseneObjednavky_->operator[](i)->vypisSa();
			cout << "======================================================= \n";
		}
	}
}

void Sklad::statVypisDrony()
{
	double nalietaneHodiny1 = 0.0;
	double nalietaneHodiny2 = 0.0;

	for (unsigned int i = 0; i < drony_->size(); i++)
	{
		if (drony_->operator[](i)->getTyp() == 1)
			nalietaneHodiny1 += drony_->operator[](i)->getNalietaneHodiny();
		else
			nalietaneHodiny2 += drony_->operator[](i)->getNalietaneHodiny();
	}
	cout << "Drony typu I. nalietali: " << nalietaneHodiny1 << " hodin \n";
	cout << "Drony typu II. nalietali: " << nalietaneHodiny2 << " hodin \n";
	cout << "======================================================= \n";
}

void Sklad::vybavObjednavky(Datum *datum)
{	
	Dron *najDron = nullptr;
	Objednavka *objednavka = nullptr;
	int size = static_cast<int>(prevzateObjednavky_->size());
	ArrayList<Objednavka*> *objNaVymazanie = new ArrayList<Objednavka*>;

	//najskor chcem vybavit vsetky objednavky na dorucenie
	for (unsigned int i = 0; i < static_cast<int>(prevzateObjednavky_->size()); i++)
	{
		objednavka = prevzateObjednavky_->operator[](i);
		if (objednavka->getNaDorucenie() && objednavka->getPrevzata())
		{
			najDron = najdiNajlepsiehoDrona(objednavka);

			if (najDron == nullptr)
				cout << "Objednavka s ID:" << objednavka->getId() << " nebola dorucena (chybaju drony)\n";
			else
			{				
				bool dorucil = najDron->vybavDorucenieObjednavky(objednavka);
				if (dorucil)
				{
					cout << "Objednavka s ID " << objednavka->getId() << " bola dorucena! \n";
					vybaveneObjednavky_->add(objednavka);
					objNaVymazanie->add(objednavka);
					//prevzateObjednavky_->tryRemove(objednavka);
				}
				else
					cout << "Objednavka s ID " << objednavka->getId() << " nebola uspesne dorucena! \n";
			}
		}
	}

	for (unsigned int i = 0; i < objNaVymazanie->size(); i++)
	{
		prevzateObjednavky_->tryRemove(objNaVymazanie->operator[](i));
	}
	objNaVymazanie->clear();

	size = static_cast<int>(prijateObjednavky_->size());
	//potom chcem vybavit objednavky na vyzdvihnutie 
	for (unsigned int i = 0; i < static_cast<int>(prijateObjednavky_->size()); i++)
	{
		objednavka = prijateObjednavky_->operator[](i);
		if (objednavka->getPrevzata() == false)
		{
			najDron = najdiNajlepsiehoDrona(objednavka);

			if (najDron == nullptr)
				cout << "Objednavka s ID:" << objednavka->getId() << " nebola vyzdvihnuta (chybaju drony)\n";
			else
			{			
				bool vyzdvihol = najDron->vybavVyzdvihnutieObjednavky(objednavka);

				if (vyzdvihol)
				{					
					cout << "Objednavka s ID " << objednavka->getId() << " bola prevzata a zaradena do objednavok na dorucenie! \n";
					prevzateObjednavky_->add(objednavka);
					//prijateObjednavky_->tryRemove(objednavka);
					objNaVymazanie->add(objednavka);
				}
				else
					cout << "Objednavka s ID " << objednavka->getId() << " nebola prevzata!!! \n";
			}
		}
	}

	for (unsigned int i = 0; i < objNaVymazanie->size(); i++)
	{
		prijateObjednavky_->tryRemove(objNaVymazanie->operator[](i));
	}
	objNaVymazanie->clear();


	for (unsigned int i = 0; i < drony_->size(); i++)
	{
		//ak je dron v sklade
		drony_->operator[](i)->setJeVSklade(true);
		double casNabijania = 0.0;
		double nabitieBaterie = 0.0;
		int stavBaterie = 0;
		double dolet = 0;
		double hodina = 0.6;

		//dron musi mat registrovanu objednavku
		if (drony_->operator[](i)->getObjednavku() != nullptr)
		{
			if (drony_->operator[](i)->getTyp() == 1)
			{
				casNabijania = hodina - drony_->operator[](i)->getCelkCasLietania();			

				// cas nabijania v hodinach / 0.05 (0.05 = 3 minuty z hodiny) = + 10%
				nabitieBaterie = (casNabijania / 0.05) * 10;

				stavBaterie = static_cast<int>(nabitieBaterie);
				if (drony_->operator[](i)->getStavBaterie() + stavBaterie > 100)
					stavBaterie = 100;

				drony_->operator[](i)->setBateriu(stavBaterie);

				dolet = ((((static_cast<double>(drony_->operator[](i)->getRychlost()) / 60)*static_cast<double>(drony_->operator[](i)->getDobuLetu())) / 2) * static_cast<double>(stavBaterie)) / 100;

				drony_->operator[](i)->setAktDolet(static_cast<int>(dolet));

			}
			else if (drony_->operator[](i)->getTyp() == 2)
			{
				// 1h - ako dlho dronovi trvalo dorucit objednavku
				casNabijania = hodina - drony_->operator[](i)->getCelkCasLietania();

				// cas nabijania v hodinach / 0.05 (0.05 = 3 minuty z hodiny) = + 10%
				nabitieBaterie = (casNabijania / 0.083) * 10;

				stavBaterie = static_cast<int>(nabitieBaterie);
				if (drony_->operator[](i)->getStavBaterie() + stavBaterie > 100)
					stavBaterie = 100;

				if (drony_->operator[](i)->getStavBaterie() + stavBaterie < 0)
					stavBaterie = 0;

				drony_->operator[](i)->setBateriu(stavBaterie);

				dolet = ((((static_cast<double>(drony_->operator[](i)->getRychlost()) / 60)*static_cast<double>(drony_->operator[](i)->getDobuLetu())) / 2) * static_cast<double>(stavBaterie)) / 100;

				drony_->operator[](i)->setAktDolet(static_cast<int>(dolet));
			}
		}
	}	

	//nastavim prevzatym objednavkam bool prevzata na true
	for (unsigned int i = 0; i < prevzateObjednavky_->size(); i++)
	{
		prevzateObjednavky_->operator[](i)->setPrevzata(true);
	}

	for (unsigned int i = 0; i < drony_->size(); i++)
	{
		drony_->operator[](i)->setCelkCasLietania(0);
	}

	delete objNaVymazanie;
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
	
	if (!skontrolujNosnostVozidla(objednavka))
	{
		status = "Pridanie objednavky by prekrocilo nosnost vozidla! \n";
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
			pocetOdoslanychZasielok_++;
		}
	}

	//vymazanie objednavok zo skladu
	for (unsigned int i = 0; i < vozidlo->getObjednavky()->size(); i++)
	{
		prevzateObjednavky_->tryRemove(vozidlo->getObjednavky()->operator[](i));
	}

	return true;
}

bool Sklad::vyberObjZVozidla(Vozidlo * vozidlo, eRegiony::EnumRegion nazovReg)
{
	Objednavka *objednavka;
	ArrayList<Objednavka*> *objNaVymazanie = new ArrayList<Objednavka*>;

	for (unsigned int i = 0; i < vozidlo->getObjednavky()->size(); i++)
	{
		objednavka = vozidlo->getObjednavky()->operator[](i);

		if (nazovReg == objednavka->getRegionDorucenia())
		{
			objednavka->setNaDorucenie(true);
			prevzateObjednavky_->add(objednavka);
			pocetDorucenychZasielok_++;
			objNaVymazanie->add(objednavka);
			cout << "Objednavka s ID: " << objednavka->getId() << " bola dovezena do skladu dorucenia! \n";
			Sleep(100);

			//vozidlo->getObjednavky()->tryRemove(objednavka);
		}
	}

	for (unsigned int i = 0; i < objNaVymazanie->size(); i++)
	{
		vozidlo->getObjednavky()->tryRemove(objNaVymazanie->operator[](i));
	}

	delete objNaVymazanie;

	return true;
}

bool Sklad::skontrolujNosnostVozidla(Objednavka * objednavka)
{
	double celkVahaObj = 0;
	double nosnost = 2;

	for (unsigned int i = 0; i < prijateObjednavky_->size(); i++)
	{
		if (!prijateObjednavky_->operator[](i)->getNaDorucenie())
		{
			celkVahaObj += prijateObjednavky_->operator[](i)->getHmotnost();
		}		
	}

	for (unsigned int i = 0; i < prevzateObjednavky_->size(); i++)
	{
		if (!prevzateObjednavky_->operator[](i)->getNaDorucenie())
		{
			celkVahaObj += prevzateObjednavky_->operator[](i)->getHmotnost();
		}
	}

	if (celkVahaObj/1000 > nosnost)
	{
		return false;
	}
	return true;
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
		for (unsigned int i = 1; i < drony_->size(); i++)
		{
			if (drony_->operator[](i)->getStavBaterie() > najlepsiDron->getStavBaterie())
			{
				najlepsiDron = drony_->operator[](i);
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
	double hodina = 0.6;

	for (unsigned int i = 0; i < drony_->size(); i++)
	{
		if (!(drony_->operator[](i)->getObjednavku() == nullptr))
		{
			if (drony_->operator[](i)->getObjednavku()->getPrevzata())
			{
				if (casDoNavratu > drony_->operator[](i)->getCasDorucenia() && objednavka->getvzdOdSkladuDorucenia() <= drony_->operator[](i)->getAktDolet())
				{
					casDoNavratu = drony_->operator[](i)->getCelkCasLietania() + drony_->operator[](i)->getCasDorucenia();
					najeplsiDron = drony_->operator[](i);
				}

			}
			else if (!(drony_->operator[](i)->getObjednavku()->getPrevzata()))
			{
				if (casDoNavratu > drony_->operator[](i)->getCasVyzdvihnutia() && objednavka->getvzdOdSkladuVyzdvihnutia() <= drony_->operator[](i)->getAktDolet())
				{
					casDoNavratu = drony_->operator[](i)->getCelkCasLietania() + drony_->operator[](i)->getCasVyzdvihnutia();
					najeplsiDron = drony_->operator[](i);
				}
			}
		}
	}

	char input;

	if (najeplsiDron == nullptr)
		return nullptr;

	string status;
	//ak by sa nenasiel dron co to stine vyzdvihnut do hodiny tak ma moznost zakaznik zrusit objednavku
	if (!najeplsiDron->getObjednavku()->getPrevzata())
	{
		if (casDoNavratu + objednavka->getDron()->getCasDorucenia() > hodina || casDoNavratu + objednavka->getDron()->getCasVyzdvihnutia() > hodina)
		{			
			cout << "Vyzdvihnutie objednavky bude trvat viac ako hodinu, chcete objednavku zrusit? \n y(ano)/n(nie)";
			cin >> input;
			if (input == 'y')
			{
				status = "Objednavka bola zrusena uzivatelom";
				objednavka->setStatus(status);
				zruseneObjednavky_->add(objednavka);
				prijateObjednavky_->tryRemove(objednavka);
				return nullptr;
			}
			
		}
	}
	return najeplsiDron;
}

string Sklad::zapisDrony(eRegiony::EnumRegion nazov)
{
	string s;
	for (unsigned int i = 0; i < drony_->size(); i++)
	{
		s += drony_->operator[](i)->zapisDoSuboru(nazov);
	}
	return s;
}

string Sklad::zapisObjednavky()
{
	string s;
	for (unsigned int i = 0; i < prijateObjednavky_->size(); i++)
	{
		s += prijateObjednavky_->operator[](i)->zapisDoSuboru();
	}
	return s;
}

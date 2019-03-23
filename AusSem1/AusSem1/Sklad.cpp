#include "structures/heap_monitor.h"
#include "Sklad.h"
#include <iostream>

using namespace std;

Sklad::Sklad():
	drony_(new ArrayList<Dron*>),
	objednavky_(new ArrayList<Objednavka*>),
	zamietnuteObjednavky_(new ArrayList<Objednavka*>)
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

	for (unsigned int i = 0; i < objednavky_->size(); i++)
	{
		delete objednavky_->operator[](i);
	}
	delete objednavky_;
	objednavky_ = nullptr;
	
	for (unsigned int i = 0; i < zamietnuteObjednavky_->size(); i++)
	{
		delete zamietnuteObjednavky_->operator[](i);
	}
	delete zamietnuteObjednavky_;
	zamietnuteObjednavky_ = nullptr;
}

Objednavka * Sklad::getObjednavka(int id)
{
	for (unsigned int i = 0; i < objednavky_->size(); i++)
	{
		if (objednavky_->operator[](i)->getId() == id)
			return objednavky_->operator[](i);
	}
	return nullptr;
}

void Sklad::vypisDrony()
{
	for (unsigned int i = 0; i < drony_->size(); i++)
	{
		drony_->operator[](i)->vypisSa();
	}
}

void Sklad::vypisObjednavky()
{
	for (unsigned int i = 0; i < objednavky_->size(); i++)
	{
		objednavky_->operator[](i)->vypisSa();
	}
}

void Sklad::vypisZamietnuteObjednavky()
{
	for (unsigned int i = 0; i < zamietnuteObjednavky_->size(); i++)
	{
		zamietnuteObjednavky_->operator[](i)->vypisSa();
	}
}

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

	if (static_cast<int>(radiusDrona) < objednavka->getvzdOdSkladuDorucenia() || static_cast<int>(radiusDrona) < objednavka->getvzdOdSkladuVyzdvihnutia())
		return false;
	else
		return true;
}

bool Sklad::stihneVyzdvihnut(Objednavka *objednavka, Datum *datum)
{
	double casVybaveniaObjednavok = 0.0;

	//celkovy cas dorucenia vsetkych objednavok
	for (unsigned int i = 0; i < objednavky_->size(); i++)
	{
		if (objednavky_->operator[](i)->getNaDorucenie())
		{
			casVybaveniaObjednavok += objednavky_->operator[](i)->getDron()->getCasDorucenia();
		}		
	}
	if (datum->getHodina() + static_cast<int>(ceil(casVybaveniaObjednavok)) + static_cast<int>(objednavka->getDron()->getCasVyzdvihnutia()) >= 20)
		return false;
	else
		return true;
}

Dron * Sklad::pridajDronaObjednavke(Objednavka * objednavka)
{
	bool jeTyp1 = false;
	double casDorucenia = 0; 
	double casVyzdvihnuta = 0;

	if (drony_->size() == 0)
	{
		return nullptr;
	}

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



Dron * Sklad::najdiNajlepsiehoDrona(Objednavka *objednavka)
{
	return nullptr;	
}

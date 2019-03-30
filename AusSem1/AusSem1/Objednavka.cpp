#include "structures/heap_monitor.h"
#include "Objednavka.h"

Objednavka::Objednavka(int id, double hmotnost, eRegiony::EnumRegion regionVyzdvihnutia, eRegiony::EnumRegion regionDorucenia, int vzdOdSkladuVyzdvihnutia, int vzdOdSkladuDorucenia, std::string status, Dron *dron, bool dor, bool prevzata) :
	id_(id),
	hmotnost_(hmotnost),
	regionDorucenia_(regionDorucenia),
	regionVyzdvihnutia_(regionVyzdvihnutia),
	vzdOdSkladuVyzdvihnutia_(vzdOdSkladuVyzdvihnutia),
	vzdOdSkladuDorucenia_(vzdOdSkladuDorucenia),
	status_(status),
	dron_(dron),
	naDorucenie_(dor),
	prevzata_(prevzata)
{
}

Objednavka::~Objednavka()
{
	//id kvoli getteru
	id_ = 0;
	hmotnost_ = 0;
	vzdOdSkladuDorucenia_ = 0;
	vzdOdSkladuVyzdvihnutia_ = 0;
}

void Objednavka::vypisSa()
{
	std::cout << "Objednavka: Id: " << id_ << " Hmotnost: " << hmotnost_ << " NaDorucenie: " << naDorucenie_ << " Prevzata: " << prevzata_ << " Status: " << status_ << " \n";
}

string Objednavka::zapisDoSuboru()
{
	return  "3 " + to_string(id_) + " " + to_string(static_cast<int>(hmotnost_)) + " " + to_string(static_cast<int>(regionVyzdvihnutia_)) + " " + to_string(static_cast<int>(regionDorucenia_)) + " " + to_string(vzdOdSkladuVyzdvihnutia_) + " " + to_string(vzdOdSkladuDorucenia_) + "\n";
}

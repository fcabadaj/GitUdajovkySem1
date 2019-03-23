#include "structures/heap_monitor.h"
#include "Objednavka.h"

Objednavka::Objednavka(int id, double hmotnost, eRegiony::EnumRegion regionVyzdvihnutia, eRegiony::EnumRegion regionDorucenia, int vzdOdSkladuVyzdvihnutia, int vzdOdSkladuDorucenia, std::string status, Dron *dron, bool dor) :
	id_(id),
	hmotnost_(hmotnost),
	regionDorucenia_(regionDorucenia),
	regionVyzdvihnutia_(regionVyzdvihnutia),
	vzdOdSkladuVyzdvihnutia_(vzdOdSkladuVyzdvihnutia),
	vzdOdSkladuDorucenia_(vzdOdSkladuDorucenia),
	status_(status),
	dron_(dron),
	naDorucenie_(dor)
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
	std::cout << "Objednavka: Id: " << id_ << " Hmotnost: " << hmotnost_ << " Status: " << status_ << " \n";
}

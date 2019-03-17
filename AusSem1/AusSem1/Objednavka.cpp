#include "structures/heap_monitor.h"
#include "Objednavka.h"
#include <iostream>



Objednavka::Objednavka(int id, int hmotnost, eRegiony::EnumRegion regionDorucenia, int vzdialenostOdSkladu) :
	id_(id),
	hmotnost_(hmotnost),
	regionDorucenia_(regionDorucenia),
	vzdialenostOdSkladu_(vzdialenostOdSkladu)
{
}


Objednavka::~Objednavka()
{
	hmotnost_ = 0;
	vzdialenostOdSkladu_ = 0;
}

void Objednavka::vypisSa()
{
	std::cout << "Objednavka: Id: " << id_ << " Hmotnost: " << " Region: " << regionDorucenia_ << " VzdialenostOdSkladu: " << vzdialenostOdSkladu_ << "\n";
}

#pragma once
#include "structures/heap_monitor.h"
#include "EnumReg.h"

class Objednavka
{
private:
	int id_;
	int hmotnost_;
	eRegiony::EnumRegion regionDorucenia_;
	int vzdialenostOdSkladu_;

public:
	Objednavka(int id, int hmotnost, eRegiony::EnumRegion regionDorucenia_, int vzdialenostOdSkladu_);
	~Objednavka();
	void vypisSa();
};

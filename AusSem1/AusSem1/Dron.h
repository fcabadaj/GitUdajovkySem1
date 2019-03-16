#pragma once
#include "structures/heap_monitor.h"
#include "Datum.h"
class Dron
{

private:
	int sCislo_;
	int typ_;
	int nosnost_;
	int rychlost_;
	int dobaLetu_;
	int dobaNabijania_;
	Datum *datum_;

public:
	Dron(int sCislo, int typ, int nosnost, int rychlost, int dobaLetu, int dobaNabijania, Datum *datum);
	~Dron();
	int getSCislo() { return sCislo_; };
	void vypisSa();
};


#pragma once
#include "structures/heap_monitor.h"
class Dron
{

private:
	int sCislo_;
	int typ_;
	int nosnost_;
	int rychlost_;
	int dobaLetu_;
	int dobaNabijania_;

public:
	Dron(int sCislo, int typ, int nosnost, int rychlost, int dobaLetu, int dobaNabijania);
	~Dron();
	int getSCislo() { return sCislo_; };
	void vypisSa();
};


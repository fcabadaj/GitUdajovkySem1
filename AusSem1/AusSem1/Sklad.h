#pragma once
#include "structures/heap_monitor.h"
#include "structures/list/array_list.h"
#include "Dron.h"

using namespace structures;

class Sklad
{
private:
	ArrayList<Dron*> *drony_;

public:
	Sklad();
	~Sklad();
	ArrayList<Dron*>* getDrony() { return drony_; }
	void vypisDrony();
	bool skontrolujSCislo(int cislo);
};


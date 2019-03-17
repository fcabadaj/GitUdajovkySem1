#pragma once
#include "structures/heap_monitor.h"
#include "structures/list/array_list.h"
#include "structures/queue/explicit_queue.h"
#include "Objednavka.h"
#include "Dron.h"

using namespace structures;

class Sklad
{
private:
	ArrayList<Dron*> *drony_;
	ExplicitQueue<Objednavka*> *objednavky_;

public:
	Sklad();
	~Sklad();
	ArrayList<Dron*>* getDrony() { return drony_; }
	ExplicitQueue<Objednavka*>* getObjednavky() { return objednavky_; }
	void vypisDrony();
	void vypisObjednavky();
	bool skontrolujSCislo(int cislo);
	bool skontrolujZamietnutieObj(int id);
};


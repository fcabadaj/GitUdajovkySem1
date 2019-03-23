#pragma once
#include "structures/heap_monitor.h"
#include "structures/list/array_list.h"
#include "structures/queue/explicit_queue.h"
#include "Objednavka.h"
#include "Dron.h"
#include <math.h>

using namespace structures;

class Sklad
{
private:
	ArrayList<Dron*> *drony_;
	ArrayList<Objednavka*> *objednavky_;
	ArrayList<Objednavka*> *zamietnuteObjednavky_;
public:
	Sklad();
	~Sklad();
	ArrayList<Dron*>* getDrony() { return drony_; }
	ArrayList<Objednavka*>* getZamietnuteObjednavky() { return zamietnuteObjednavky_; };
	//Objednavky su v arrayListe pretoze pri mojej logike vypoctu zamietnutia bodu a) potrebujem prejst vsetky objednavky
	ArrayList<Objednavka*>* getObjednavky() { return objednavky_; }
	Objednavka* getObjednavka(int id);
	void vypisDrony();
	void vypisObjednavky();
	void vypisZamietnuteObjednavky();
	bool skontrolujSCislo(int cislo);
	bool skontrolujZamietnutieObj(Datum *datum, Objednavka *objednavka);
	bool skontrolujRadiusDronov(Objednavka *objednavka);
	bool stihneVyzdvihnut(Objednavka *objednavka, Datum *datum);
	Dron* pridajDronaObjednavke(Objednavka *objednavka);
	Dron* najdiNajlepsiehoDrona(Objednavka *objednavka);
};


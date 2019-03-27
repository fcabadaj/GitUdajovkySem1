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
	//objednavky ktore sa prijali
	ArrayList<Objednavka*> *prijateObjednavky_;
	//zamietnute objednavky 
	ArrayList<Objednavka*> *zamietnuteObjednavky_;
	//uz prevzate objednavky od zakaznika
	ArrayList<Objednavka*> *prevzateObjednavky_;
	//vybavene objednavky
	ArrayList<Objednavka*> *vybaveneObjednavky_;
public:
	Sklad();
	~Sklad();
	ArrayList<Dron*>* getDrony() { return drony_; }
	ArrayList<Objednavka*>* getZamietnuteObjednavky() { return zamietnuteObjednavky_; };
	//Objednavky su v arrayListe pretoze pri mojej logike vypoctu zamietnutia bodu a) potrebujem prejst vsetky objednavky
	ArrayList<Objednavka*>* getPrijateObjednavky() { return prijateObjednavky_; }
	ArrayList<Objednavka*>* getVybaveneObjednavky() { return vybaveneObjednavky_; }
	Objednavka* getObjednavka(int id);
	void vypisDrony();
	void vypisObjednavky();
	void vypisZamietnuteObjednavky();
	void vybavObjednavky(Datum *datum);
	void presunPrijateObj();
	bool skontrolujSCislo(int cislo);
	bool skontrolujZamietnutieObj(Datum *datum, Objednavka *objednavka);
	bool skontrolujRadiusDronov(Objednavka *objednavka);
	bool stihneVyzdvihnut(Objednavka *objednavka, Datum *datum);
	Dron* pridajDronaObjednavke(Objednavka *objednavka);
	Dron* najdiNajlepsiehoDrona(Objednavka *objednavka);
	Dron* najskorSkonci(Objednavka *objednavka);
};


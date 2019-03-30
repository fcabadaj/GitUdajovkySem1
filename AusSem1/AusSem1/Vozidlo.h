#pragma once
#include "structures/heap_monitor.h"
#include "structures/list/array_list.h"
#include "EnumReg.h"
#include <string>
#include <iostream>
#include "Datum.h"
#include "Objednavka.h"

using namespace std;
using namespace structures;
using namespace eRegiony;

class Vozidlo
{
private:
	string spz_;
	double nosnost_;
	double prevadzkoveNaklady_;
	double celkPrevNaklady_;
	double aktZataz_;
	Datum *datum_;
	ArrayList<Objednavka*> *objednavky_;
	Array<EnumRegion*> *regiony_;

public:
	Vozidlo(string spz, double nosnost, Datum *datum, double prevadzkoveNaklady = 15.0, double aktZataz = 0.0, double celk = 0.00000);
	~Vozidlo();
	void vypisSa();
	void initRegiony();
	void vypisRegiony();
	Array<EnumRegion*>* getRegiony() { return regiony_; };
	ArrayList<Objednavka*>* getObjednavky() { return objednavky_; };
	string getSPZ() { return spz_; };
	void setCelkPrevNaklady(double d) { this->celkPrevNaklady_ = d; };
	double getCelkPrevNaklady() { return celkPrevNaklady_; };
	double getPrevNaklady() { return prevadzkoveNaklady_; };
	string zapisDoSuboru();
};


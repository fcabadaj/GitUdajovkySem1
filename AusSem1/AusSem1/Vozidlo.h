#pragma once
#include "structures/heap_monitor.h"
#include <string>
#include <iostream>
#include "Datum.h"
#include "Objednavka.h"

using namespace std;

class Vozidlo
{
private:
	string spz_;
	double nosnost_;
	double prevadzkoveNaklady_;
	Datum *datum_;
	ArrayList<Objednavka*> *objednavky_;

public:
	Vozidlo(string spz, double nosnost, double prevadzkoveNaklady, Datum *datum);
	~Vozidlo();
	void vypisSa();
	string getSPZ() { return spz_; };
};


#include <string>
#include <iostream>
#include "Datum.h"
#pragma once

using namespace std;

class Vozidlo
{
private:
	string spz_;
	int nosnost_;
	int prevadzkoveNaklady_;
	Datum *datum_;

public:
	Vozidlo(string spz, int nosnost, int prevadzkoveNaklady, Datum *datum);
	~Vozidlo();
	void vypisVozidlo();
	string getSPZ() { return spz_; };
};


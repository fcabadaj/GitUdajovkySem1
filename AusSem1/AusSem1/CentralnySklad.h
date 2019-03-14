#pragma once

#include "structures/list/array_list.h"
#include "Vozidlo.h"

using namespace structures;

class CentralnySklad
{
private:
	ArrayList<Vozidlo*> *vozovyPark_;

public:
	CentralnySklad();
	~CentralnySklad();
	ArrayList<Vozidlo*>* getVozovyPark() { return vozovyPark_; };
	void vypisVozidla();
};


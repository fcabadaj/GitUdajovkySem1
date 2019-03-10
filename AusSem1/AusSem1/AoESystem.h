#pragma once
#include "Region.h"

class AoESystem
{

private:
	ArrayList<Region*> *regiony_;

public:
	AoESystem();
	~AoESystem();
	Region getRegion(eRegiony::EnumRegion nazovRegionu);
	bool pridajVozidlo(eRegiony::EnumRegion nazovRegionu, string spz, int nosnost, int prevadzkoveNaklady);
	bool pridajDrona(eRegiony::EnumRegion nazovRegionu, int sCislo, int typ, int nosnost, int rychlost, int dobaLetu, int dobaNabijania);
};


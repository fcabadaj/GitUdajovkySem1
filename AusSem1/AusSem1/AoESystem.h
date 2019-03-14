#pragma once
#include "Region.h"
#include "structures/array/array.h"

class AoESystem
{

private:
	Array<Region*> *regiony_;

public:
	AoESystem();
	~AoESystem();
	Region getRegion(eRegiony::EnumRegion nazovRegionu);
	bool skontrolujSPZ(string spz);
	bool pridajVozidlo(eRegiony::EnumRegion nazovRegionu, string spz, int nosnost, int prevadzkoveNaklady,Datum *datum);
	bool pridajDrona(eRegiony::EnumRegion nazovRegionu, int sCislo, int typ, int nosnost, int rychlost, int dobaLetu, int dobaNabijania);
};


#pragma once
#include "structures/heap_monitor.h"
#include "Region.h"
#include "structures/array/array.h"

class AoESystem
{

private:
	Array<Region*> *regiony_;
	Datum *datum_;

public:
	AoESystem();
	~AoESystem();
	Region getRegion(eRegiony::EnumRegion nazovRegionu);
	bool skontrolujSC(int sCislo);
	bool skontrolujSPZ(string spz);	
	bool skontrolujZamietnutieObj(int id, eRegiony::EnumRegion nazovRegionu);
	bool pridajVozidlo(eRegiony::EnumRegion nazovRegionu, string spz, int nosnost, int prevadzkoveNaklady);
	bool pridajDrona(eRegiony::EnumRegion nazovRegionu, int sCislo, int typ);
	bool pridajObjednavku(int id, eRegiony::EnumRegion nazovRegionu, int hmotnost, int vzdialenostOdSkladu );
	void vypisVozidla();
	void vypisDrony();
	void vypisObjednavky();
	void vypisDatum();
	void initRegiony();
	void pridajHodinu();
};


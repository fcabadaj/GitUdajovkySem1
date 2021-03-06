#pragma once
#include "structures/heap_monitor.h"
#include "Region.h"
#include "structures/array/array.h"

class AoESystem
{

private:
	Array<Region*> *regiony_;
	Datum *datum_;
	void vybavObjednavky(Datum *datum);
	bool vysliVozidla();
	void initRegiony();
	bool skontrolujSC(int sCislo);
	bool skontrolujSPZ(string spz);
	bool skontrolujZamietnutieObj(Datum *datum, Objednavka *objednavka);
	bool skontrolujId(Objednavka *objednavka);

public:
	AoESystem();
	~AoESystem();
	Region getRegion(eRegiony::EnumRegion nazovRegionu);
	Datum* getDatum() { return datum_; };	
	bool pridajVozidlo(eRegiony::EnumRegion nazovRegionu, string spz, double nosnost);
	bool pridajDrona(eRegiony::EnumRegion nazovRegionu, int sCislo, int typ);
	bool pridajObjednavku(int id, double hmotnost, eRegiony::EnumRegion regionVyzdvihnutia, eRegiony::EnumRegion regionDorucenia, int vzdOdSkladuVyzdvihnutia, int vzdOdSkladuDorucenia);
	void vypisVozidla();
	void vypisDrony();
	void vypisObjednavky();
	void vypisDatum();
	void vypisZamietnuteObjednavky();	
	void pridajHodinu();	
	void zapisDoSuboru();
	void nacitajZoSuboru();
	void prejdiNa21H();
	void vypisStatistik();	
	string getMenoRegionu(int reg);
};


#pragma once
#include "structures/heap_monitor.h"
#include "Datum.h"
#include "Objednavka.h"

class Objednavka;

class Dron
{

private:
	int sCislo_;
	int typ_;
	int nosnost_;
	int rychlost_;
	int dobaLetu_;
	int dobaNabijania_;
	Datum *datum_;
	bool jeVSklade_;
	Objednavka *objednavka_;
	double casVyzdvihnuta_;
	double casDorucenia_;
	int bateriaPercenta_;

public:
	Dron(int sCislo, int typ, int nosnost, int rychlost, int dobaLetu, int dobaNabijania, Datum *datum, Objednavka *objednavka = nullptr, bool jeVSklade = true, int bateria = 100, double casD = 0, double casV = 0);
	~Dron();
	int getSCislo() { return sCislo_; };
	int getTyp() { return typ_; };
	int getRychlost() { return rychlost_; };
	int getDobuLetu() { return dobaLetu_; };
	double getCasVyzdvihnutia() { return casVyzdvihnuta_; };
	double getCasDorucenia() { return casDorucenia_; };
	bool getJeVSklade() { return jeVSklade_; };
	void vypisSa();
	void setCasVyzdvihnutia(double cas) { this->casVyzdvihnuta_ = cas; };
	void setCasDorucenia(double cas) { this->casDorucenia_ = cas; };
};


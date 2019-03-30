#pragma once
#include "structures/heap_monitor.h"
#include "Datum.h"
#include "EnumReg.h"

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
	//je v sklade alebo vybavuje objednavku
	bool jeVSklade_;
	Objednavka *objednavka_;
	//dlzka trvania vyzdvihnutia objednavky
	double casVyzdvihnuta_;
	//dlzka trvania dorucenia objednavky
	double casDorucenia_;
	int bateriaPercenta_;
	// dolet podla stavu baterie == ((( ( rychlost_/60 )*dobaLetu_) / 2) * bateriaPercenta_) / 100
	int maxDolet_;
	int aktDolet_;
	double nalietaneHodiny_;
	double celkCasLietania_;

public:
	Dron(int sCislo, int typ, int nosnost, int rychlost, int dobaLetu, int dobaNabijania, Datum *datum, Objednavka *objednavka = nullptr, bool jeVSklade = true, int bateria = 100, double casD = 0, double casV = 0, double h = 0, double celkCasLietania_ = 0.0);
	~Dron();
	void initDolet();
	int getSCislo() { return sCislo_; };
	int getTyp() { return typ_; };
	int getRychlost() { return rychlost_; };
	int getDobuLetu() { return dobaLetu_; };
	double getCasVyzdvihnutia() { return casVyzdvihnuta_; };
	double getCasDorucenia() { return casDorucenia_; };
	double getCelkCasLietania() { return celkCasLietania_; };
	bool getJeVSklade() { return jeVSklade_; };
	bool vybavDorucenieObjednavky(Objednavka *objednavka);
	bool vybavVyzdvihnutieObjednavky(Objednavka *objednavka);
	int getAktDolet() { return aktDolet_; };
	int getStavBaterie() { return bateriaPercenta_; };
	int getMaxDolet() { return maxDolet_; };
	Objednavka* getObjednavku() { return objednavka_; };
	void vypisSa();
	void setCasVyzdvihnutia(double cas) { this->casVyzdvihnuta_ = cas; };
	void setCasDorucenia(double cas) { this->casDorucenia_ = cas; };
	void setJeVSklade(bool b) { this->jeVSklade_ = b; };
	void odratajBaterku(int vzdialenost);
	void setObjednavka(Objednavka *obj) { this->objednavka_ = obj; };
	void setBateriu(int c) { this->bateriaPercenta_ = c; };
	void setAktDolet(int d) { this->aktDolet_ = d; };
	void setCelkCasLietania(double d) { this->celkCasLietania_ = d; };
	string zapisDoSuboru(eRegiony::EnumRegion nazov);
};


#pragma once
#include "structures/heap_monitor.h"
#include "EnumReg.h"
#include <iostream>
#include <string>
#include "Dron.h"

class Dron;

class Objednavka
{
private:
	int id_;
	double hmotnost_;
	eRegiony::EnumRegion regionDorucenia_;
	eRegiony::EnumRegion regionVyzdvihnutia_;
	int vzdOdSkladuDorucenia_;
	int vzdOdSkladuVyzdvihnutia_;
	std::string status_;
	Dron *dron_;
	bool naDorucenie_;

public:
	Objednavka(int id, double hmotnost, eRegiony::EnumRegion regionVyzdvihnutia, eRegiony::EnumRegion regionDorucenia, int vzdOdSkladuVyzdvihnutia, int vzdOdSkladuDorucenia, std::string status = "Prijata", Dron *dron = nullptr, bool dor = false);
	~Objednavka();
	eRegiony::EnumRegion getRegionDorucenia() { return regionDorucenia_; };
	eRegiony::EnumRegion getRegionVyzdvihnutia() { return regionVyzdvihnutia_; };
	int getvzdOdSkladuDorucenia() { return vzdOdSkladuDorucenia_; };
	int getvzdOdSkladuVyzdvihnutia() { return vzdOdSkladuVyzdvihnutia_; };
	void setNaDorucenie(bool dor) { this->naDorucenie_ = dor; };
	bool getNaDorucenie() { return naDorucenie_; };
	Dron* getDron() { return dron_; };
	int getId() { return id_; };
	int getHmotnost() { return hmotnost_; };
	void vypisSa();
	void setStatus(std::string status) { this->status_ = status; };
	void setDron(Dron *dron) { this->dron_ = dron; };
};

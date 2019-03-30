#include "structures/heap_monitor.h"
#include <iostream>
#include "Dron.h"
#include "Objednavka.h"
using namespace std;

Dron::Dron(int sCislo, int typ, int nosnost, int rychlost, int dobaLetu, int dobaNabijania, Datum *datum, Objednavka *objednavka, bool jeVSklade, int bateria, double casD, double casV, double h, double cC) :
	sCislo_(sCislo),
	typ_(typ),
	nosnost_(nosnost),
	rychlost_(rychlost),
	dobaLetu_(dobaLetu),
	dobaNabijania_(dobaNabijania),
	datum_(datum),
	jeVSklade_(jeVSklade),
	objednavka_(objednavka),
	bateriaPercenta_(bateria),
	casDorucenia_(casD),
	casVyzdvihnuta_(casV),
	nalietaneHodiny_(h),
	celkCasLietania_(cC)
{
	initDolet();
}

Dron::~Dron()
{
	sCislo_ = 0;
	typ_ = 0;
	nosnost_ = 0;
	rychlost_ = 0;
	dobaLetu_ = 0;
	dobaNabijania_ = 0;
	delete datum_;
	datum_ = nullptr;
}

void Dron::initDolet()
{	
	maxDolet_ = static_cast<int>(((static_cast<double>(rychlost_)/60)*static_cast<double>(dobaLetu_))/2);
	aktDolet_ = maxDolet_;
}

bool Dron::vybavDorucenieObjednavky(Objednavka * objednavka)
{
	if (objednavka->getvzdOdSkladuDorucenia() > this->getAktDolet())
		return false;

	//dron a objednavka o sebe navzajom vedia
	this->setObjednavka(objednavka);
	objednavka->setDron(this);

	double casDorucenia = static_cast<double>(objednavka->getvzdOdSkladuDorucenia()) / static_cast<double>(rychlost_);
	double celkCasLietania = this->celkCasLietania_ + casDorucenia;
	this->setCasDorucenia(casDorucenia);
	this->setCelkCasLietania(celkCasLietania);

	this->setJeVSklade(false);

	cout << "Dron SC: " << this->getSCislo() << " prave dorucuje objednavku " << objednavka->getId() << endl;

	odratajBaterku(objednavka->getvzdOdSkladuDorucenia());	 
	//cas dorucenia je *2 pretoze sa pocita na zaklade vzdialenosti a ta sa dava / 2 kvoli ceste tam a naspat
	nalietaneHodiny_ += this->casDorucenia_*2;

	return true;
}

bool Dron::vybavVyzdvihnutieObjednavky(Objednavka * objednavka)
{
	if (objednavka->getvzdOdSkladuVyzdvihnutia() > this->getAktDolet())
		return false;

	this->setObjednavka(objednavka);
	objednavka->setDron(this);

	double casVyzdvihnuta = static_cast<double>(objednavka->getvzdOdSkladuVyzdvihnutia()) / static_cast<double>(rychlost_);
	this->setCasVyzdvihnutia(casVyzdvihnuta);

	double celkCasLietania = this->celkCasLietania_ + casVyzdvihnuta;
	
	this->setCelkCasLietania(celkCasLietania);

	this->setJeVSklade(false);

	cout << "Dron SC: " << this->getSCislo() << " prave vyzdvihuje objednavku " << objednavka->getId() << endl;
		
	odratajBaterku(objednavka->getvzdOdSkladuVyzdvihnutia());
	//cas dorucenia je *2 pretoze sa pocita na zaklade vzdialenosti a ta sa dava / 2 kvoli ceste tam a naspat
	nalietaneHodiny_ += this->casVyzdvihnuta_*2;

	return true;
	
}

void Dron::vypisSa()
{
	cout << "Dron SC: " << sCislo_ << " Typ: " << typ_ <<  " Datum pridania: Den: " << datum_->getDen() << " Hodina " << datum_->getHodina() << " Stav baterie: " << bateriaPercenta_<< " Aktualny dolet: " << aktDolet_ << " Celk. nalietane hod. " << nalietaneHodiny_/0.6 <<endl;
}

void Dron::odratajBaterku(int vzdialenost)
{
	double percenta = (static_cast<double>(vzdialenost) / static_cast<double>(maxDolet_)) * 100;
	bateriaPercenta_ -= static_cast<int>(percenta);
	aktDolet_ = static_cast<int>(((((static_cast<double>(rychlost_) / 60)*static_cast<double>(dobaLetu_)) / 2) * static_cast<double>(bateriaPercenta_)) / 100);
}

string Dron::zapisDoSuboru(eRegiony::EnumRegion nazov)
{
	return  "1 " + to_string(static_cast<int>(nazov)) + " " + to_string(sCislo_) + " " + to_string(typ_) + "\n";
}

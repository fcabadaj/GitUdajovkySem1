#include "structures/heap_monitor.h"
#include <iostream>
#include "Dron.h"

using namespace std;

Dron::Dron(int sCislo, int typ, int nosnost, int rychlost, int dobaLetu, int dobaNabijania, Datum *datum, Objednavka *objednavka, bool jeVSklade, int bateria, double casD, double casV) :
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
	casVyzdvihnuta_(casV)
{
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

void Dron::vypisSa()
{
	cout << "Dron Seriove Cislo: " << sCislo_ << " Typ: " << typ_ << " Nosnost: " << nosnost_ << " Datum pridania: Den: " << datum_->getDen() << " Hodina " << datum_->getHodina() << endl;
}

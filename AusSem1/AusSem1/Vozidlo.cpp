#include "Vozidlo.h"
#include <string>

Vozidlo::Vozidlo(string spz, int nosnost, int prevadzkoveNaklady, Datum *datum) :
	spz_(spz),
	nosnost_(nosnost),
	prevadzkoveNaklady_(prevadzkoveNaklady),
	datum_(datum)
{
}

Vozidlo::~Vozidlo()
{
	spz_ = "";
	nosnost_ = 0;
	prevadzkoveNaklady_ = 0;
	delete datum_;
}

void Vozidlo::vypisVozidlo()
{
	cout << "SPZ: " << spz_ << " Nosnost: " << nosnost_ << " Prevadzkove Naklady: " << prevadzkoveNaklady_ << endl;
}

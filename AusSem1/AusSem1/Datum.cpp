#include "structures/heap_monitor.h"
#include "Datum.h"
#include <iostream>

using namespace std;

Datum::Datum(int den, int hodina, int minuty) :
	den_(den),
	hodina_(hodina),
	minuty_(minuty)
{
}

Datum::Datum(Datum & datum)
{
	*this = datum;
}

Datum::~Datum()
{
	den_ = 0;
	hodina_ = 0;
	minuty_ = 0;
}

void Datum::pridajHodinu()
{	
	if (hodina_ == 21)
	{
		hodina_ = 6;
		den_++;
	}
	hodina_++;
}

void Datum::vypisSa()
{
	cout << "Aktualny datum a cas: den: " << den_ << " hodina: " << hodina_ << endl;
}

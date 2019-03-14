#include "Datum.h"



Datum::Datum(int den, int mesiac, int rok, int hodina) :
	den_(den),
	mesiac_(mesiac),
	rok_(rok),
	hodina_(hodina)
{
}

Datum::~Datum()
{
	den_ = 0;
	mesiac_ = 0;
	rok_ = 0;
	hodina_ = 0;
}

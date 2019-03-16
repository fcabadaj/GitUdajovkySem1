#include "structures/heap_monitor.h"
#include "Datum.h"



Datum::Datum(int den, int hodina) :
	den_(den),
	hodina_(hodina)
{
}

Datum::~Datum()
{
	den_ = 0;
	hodina_ = 0;
}

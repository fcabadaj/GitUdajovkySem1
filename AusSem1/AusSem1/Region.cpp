#include "structures/heap_monitor.h"
#include "Region.h"

Region::Region(eRegiony::EnumRegion nazovRegionu, CentralnySklad* centralnySklad) :
	nazovRegionu_(nazovRegionu),
	centralnySklad_(centralnySklad),
	sklad_(new Sklad)
{	
}

Region::~Region()
{	
	delete sklad_;
	delete centralnySklad_;
}




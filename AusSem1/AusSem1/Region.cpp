#include "Region.h"

Region::Region(eRegiony::EnumRegion nazovRegionu) :
	nazovRegionu_(nazovRegionu),
	drony_(new ArrayList<Dron*>()),
	sklad_(new Sklad())
{
	
}

Region::~Region()
{
	delete drony_;
	delete sklad_;
}




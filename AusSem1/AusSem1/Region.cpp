#include "Region.h"

Region::Region(eRegiony::EnumRegion nazovRegionu) :
	nazovRegionu_(nazovRegionu),
	vozovyPark_(new ArrayList<Vozidlo*>()),
	drony_(new ArrayList<Dron*>()),
	sklad_(new Sklad())
{
	
}

Region::~Region()
{
	delete vozovyPark_;
	delete drony_;
	delete sklad_;
}

void Region::vypisUdajeOVozidlach()
{
	for (int i = 0; i < vozovyPark_->size(); i++)
	{
		vozovyPark_->operator[](i)->vypisVozidlo();
	}
}



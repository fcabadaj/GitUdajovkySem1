#pragma once
#include "structures/list/array_list.h"
#include "structures/vector/vector.h"
#include "Vozidlo.h"
#include "Dron.h"
#include "Sklad.h"
#include "EnumReg.h"

using namespace structures;

class Region
{
private:
	eRegiony::EnumRegion nazovRegionu_;
	ArrayList<Dron*>	*drony_;
	Sklad *sklad_;
public:
	Region(eRegiony::EnumRegion nazovRegionu);
	~Region();
	ArrayList<Dron*> getDrony() { return *drony_;  }
	eRegiony::EnumRegion getNazovRegionu() { return nazovRegionu_; };
	
};


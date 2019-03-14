#pragma once
#include "structures/list/array_list.h"
#include "structures/vector/vector.h"
#include "Vozidlo.h"
#include "Dron.h"
#include "Sklad.h"
#include "EnumReg.h"
#include "CentralnySklad.h"

using namespace structures;

class Region
{
private:
	eRegiony::EnumRegion nazovRegionu_;
	CentralnySklad *centralnySklad_;
public:
	Region(eRegiony::EnumRegion nazovRegionu, CentralnySklad* centralnySklad = nullptr);
	~Region();	
	eRegiony::EnumRegion getNazovRegionu() { return nazovRegionu_; };
	CentralnySklad& getCentralnySklad() { return *centralnySklad_; };
	
};


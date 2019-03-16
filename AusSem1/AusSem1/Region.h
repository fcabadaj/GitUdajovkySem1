#pragma once
#include "structures/heap_monitor.h"
#include "Sklad.h"
#include "EnumReg.h"
#include "CentralnySklad.h"

using namespace structures;

class Region
{
private:
	Sklad *sklad_;
	eRegiony::EnumRegion nazovRegionu_;
	CentralnySklad *centralnySklad_;
	
public:
	Region(eRegiony::EnumRegion nazovRegionu, CentralnySklad* centralnySklad = nullptr);
	~Region();
	eRegiony::EnumRegion getNazovRegionu() { return nazovRegionu_; };
	CentralnySklad* getCentralnySklad() { return centralnySklad_; };
	Sklad* getLokalnySklad() { return sklad_; };

};


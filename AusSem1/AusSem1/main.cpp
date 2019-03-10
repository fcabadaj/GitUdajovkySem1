#include "structures/vector/vector.h"
#include "structures/list/array_list.h"
#include <iostream>
#include "Dron.h"
#include "AoESystem.h"
#include "EnumReg.h"

using namespace structures;
using namespace std;
using namespace eRegiony;


int main() 
{	
	Region *region = new Region(BA);

	AoESystem *system = new AoESystem();
	system->pridajVozidlo(eRegiony::BA, "ZA894FS", 5, 3);

	region->vypisUdajeOVozidlach();

	int cislo2 = 0;
	cin >> cislo2;

	return 0;
}
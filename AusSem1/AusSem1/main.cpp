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
	
	AoESystem *system = new AoESystem();
	Datum* datum = new Datum(1, 1, 1, 1);
	system->pridajVozidlo(ZA,"ZA654FS",50,15,datum);

	system->getRegion(ZA).getCentralnySklad().vypisVozidla();	

	int cislo2 = 0;
	cin >> cislo2;


	return 0;
}
#include "structures/heap_monitor.h"
#include "structures/vector/vector.h"
#include "structures/list/array_list.h"
#include <iostream>
#include <cstdlib>
#include "Dron.h"
#include "AoESystem.h"
#include "EnumReg.h"

using namespace structures;
using namespace std;
using namespace eRegiony;

void menu(int &c);

int main() 
{
	initHeapMonitor();
	AoESystem *esystem = new AoESystem();
	Datum* datum = new Datum(1);

	int choice = 155;
	menu(choice);

	while (choice != 0)
	{
		esystem->vypisDatum();
		string spz;

		int nosnost;
		int nazovRegionu;
		int sCislo;
		int typ;

		switch (choice)
		{
		case 0: return 0;
			break;
		case 1: 			
			cout << "PRIDANIE VOZIDLA DO VOZOVEHO PARKU\n";
			cout << "============================================== \n";
			cout << "Zadaj 7 znakovu SPZ: \n";
			cin >> spz;
			cout << "Zadaj nosnost vozidla v tonach \n";
			cin >> nosnost;
			esystem->pridajVozidlo(ZA, spz, nosnost, 15);
			break;

		case 2:
			cout << "PRIDANIE DRONA DO FLOTILY DRONOV \n";
			cout << "============================================== \n";
			cout << "Zadaj region do ktoreho chces drona pridat \n";
			cout << "0 = ZA, 1 = MA, 2 = BA, 3 = TT, 4 = KN, 5 = LV \n 6 = TN, 7 = PD,  8 = MT, 9 = NR, 10 = CA, 11 = NO \n 12 = LM, 13 = BB, 14 = ZV, 15 = KA, 16 = LC, 17 = RA \n 18 = PP, 19 = SL, 20 = SN, 21 = KE, 22 = PO, 23 = HE, 24 = MI \n";
			cin >> nazovRegionu;
			cout << "Zadaj seriove cislo drona: \n";
			cin >> sCislo;
			cout << "Zadaj typ drona:  1 = TYP I.  2 = TYP II. ";
			cin >> typ;
			esystem->pridajDrona(static_cast<EnumRegion>(nazovRegionu), sCislo, typ);
			break;

		case 3:
			esystem->vypisVozidla();
			break;

		case 4:
			esystem->vypisDrony();
			break;

		case 5: 
			esystem->pridajHodinu();
			break;

		default:
			break;
		}
		menu(choice);
	}

	delete esystem;
	delete datum;

	return 0;
}


void menu(int &c) 
{	
	cout << "======================================================= \n";
	cout << "stlac 0 - pre ukoncenie programu \n";
	cout << "stlac 1 - pre pridanie vozidla \n";
	cout << "stlac 2 - pre pridanie drona \n";
	cout << "stlac 3 - pre vypis vozidiel \n";
	cout << "stlac 4 - pre vypis dronov \n";
	cout << "stlac 5 - pre pridanie hodiny \n";
	cout << "======================================================= \n";
	cin >> c;
	system("CLS");
}
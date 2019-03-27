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
		cout << "======================================================= \n";

		string spz;
		int nosnost;
		int regVzdvihnutia = -1;
		int regDorucenia = -1;
		int sCislo;
		int typ;
		int id;
		int vzdVyzdvihnutia;
		int vzdDorucenia;
		int hmotnost;

		switch (choice)
		{
		case 0: return 0;
			break;

		case 1:
			esystem->pridajHodinu();
			break;

		case 2: 			
			cout << "PRIDANIE VOZIDLA DO VOZOVEHO PARKU\n";
			cout << "======================================================= \n";
			cout << "Zadaj 7 znakovu SPZ: \n";
			cin >> spz;
			cout << "Zadaj nosnost vozidla v tonach \n";
			cin >> nosnost;
			esystem->pridajVozidlo(ZA, spz, nosnost, 15);
			break;

		case 3:
			cout << "PRIDANIE DRONA DO FLOTILY DRONOV \n";
			cout << "======================================================= \n";
			while (regDorucenia < 0 || regDorucenia > 24)
			{
				cout << "Zadaj region do ktoreho chces drona pridat \n";
				cout << "0 = ZA, 1 = MA, 2 = BA, 3 = TT, 4 = KN, 5 = LV \n 6 = TN, 7 = PD,  8 = MT, 9 = NR, 10 = CA, 11 = NO \n 12 = LM, 13 = BB, 14 = ZV, 15 = KA, 16 = LC, 17 = RA \n 18 = PP, 19 = SL, 20 = SN, 21 = KE, 22 = PO, 23 = HE, 24 = MI \n";
				cin >> regDorucenia;
			}
			cout << "Zadaj seriove cislo drona: \n";
			cin >> sCislo;
			cout << "Zadaj typ drona:  1 = TYP I.  2 = TYP II. ";
			cin >> typ;
			esystem->pridajDrona(static_cast<EnumRegion>(regDorucenia), sCislo, typ);
			break;

		case 4:
			cout << "PRIDANIE OBJEDNAVKY DO SKLADU \n";
			cout << "======================================================= \n";
			cout << "Zadaj id Objednavky (integer) \n";
			cin >> id;
			cout << "Zadaj hmotnost Objednavky \n";
			cin >> hmotnost;
			while (regVzdvihnutia < 0 || regVzdvihnutia > 24)
			{
				cout << "Zadaj region odkial chces objednavku vyzdvihnut \n";
				cout << "0 = ZA, 1 = MA, 2 = BA, 3 = TT, 4 = KN, 5 = LV \n 6 = TN, 7 = PD,  8 = MT, 9 = NR, 10 = CA, 11 = NO \n 12 = LM, 13 = BB, 14 = ZV, 15 = KA, 16 = LC, 17 = RA \n 18 = PP, 19 = SL, 20 = SN, 21 = KE, 22 = PO, 23 = HE, 24 = MI \n";
				cin >> regVzdvihnutia;
			}
			while (regDorucenia < 0 || regDorucenia > 24)
			{
				cout << "Zadaj region kam chces objednavku dorucit \n";
				cout << "0 = ZA, 1 = MA, 2 = BA, 3 = TT, 4 = KN, 5 = LV \n 6 = TN, 7 = PD,  8 = MT, 9 = NR, 10 = CA, 11 = NO \n 12 = LM, 13 = BB, 14 = ZV, 15 = KA, 16 = LC, 17 = RA \n 18 = PP, 19 = SL, 20 = SN, 21 = KE, 22 = PO, 23 = HE, 24 = MI \n";
				cin >> regDorucenia;
			}
			cout << "Zadaj vzdialenost miesta vyzdvihnutia od lokalneho skladu \n";
			cin >> vzdVyzdvihnutia;
			cout << "Zadaj vzdialenost miesta dorucenia od miestneho lokalneho skladu \n";
			cin >> vzdDorucenia;
			esystem->pridajObjednavku(id,hmotnost, static_cast<EnumRegion>(regVzdvihnutia), static_cast<EnumRegion>(regDorucenia), vzdVyzdvihnutia, vzdDorucenia);
			break;

		case 5:
			esystem->vypisVozidla();
			break;

		case 6:
			esystem->vypisDrony();
			break;	

		case 7:
			esystem->vypisZamietnuteObjednavky();
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
	cout << "stlac 1 - pre pridanie hodiny \n";
	cout << "stlac 2 - pre pridanie vozidla \n";
	cout << "stlac 3 - pre pridanie drona \n";
	cout << "stlac 4 - pre pridanie objednavky \n";
	cout << "stlac 5 - pre vypis vozidiel \n";
	cout << "stlac 6 - pre vypis dronov \n";
	cout << "stlac 7 - pre vypis zamietnutych objednavok \n";	
	cout << "======================================================= \n";
	cin >> c;
	system("CLS");
}
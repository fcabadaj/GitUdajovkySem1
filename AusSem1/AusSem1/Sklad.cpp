#include "structures/heap_monitor.h"
#include "Sklad.h"
#include <iostream>

using namespace std;

Sklad::Sklad():
	drony_(new ArrayList<Dron*>)
{
}

Sklad::~Sklad()
{
	for (unsigned int i = 0; i < drony_->size(); i++)
	{
		delete (*drony_)[i];
	}
	delete drony_;
}

void Sklad::vypisDrony()
{
	for (unsigned int i = 0; i < drony_->size(); i++)
	{
		drony_->operator[](i)->vypisSa();
	}
}

bool Sklad::skontrolujSCislo(int cislo)
{
	for (unsigned int i = 0; i < drony_->size(); i++)
	{
		if (drony_->operator[](i)->getSCislo() == cislo)
		{
			cout << "Dron s takymto seriovym cislom uz existuje! \n";
			return false;
		}
	}
	return true;
}

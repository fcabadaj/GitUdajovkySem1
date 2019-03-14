#include <iostream>
#include "Dron.h"


Dron::Dron(int sCislo, int typ, int nosnost, int rychlost, int dobaLetu, int dobaNabijania) :
	sCislo_(sCislo),
	typ_(typ),
	nosnost_(nosnost),
	rychlost_(rychlost),
	dobaLetu_(dobaLetu),
	dobaNabijania_(dobaNabijania)
{
}




Dron::~Dron()
{
	sCislo_ = 0;
	typ_ = 0;
	nosnost_ = 0;
	rychlost_ = 0;
	dobaLetu_ = 0;
	dobaNabijania_ = 0;
}
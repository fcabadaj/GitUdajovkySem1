#pragma once
#include "Dron.h"
#include "Region.h"

using namespace structures;

class Sklad
{

private:
	ArrayList<Dron*> *drony_;

public:
	Sklad();
	~Sklad();
	ArrayList<Dron*> getDrony() { return *drony_; }
};


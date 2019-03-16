#pragma once
#include "structures/heap_monitor.h"

using namespace std;

class Datum
{
private:
	int den_;
	int hodina_;
public:
	Datum(int den, int hodina);
	~Datum();
};


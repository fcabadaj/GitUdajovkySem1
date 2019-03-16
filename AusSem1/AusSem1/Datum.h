#pragma once
#include "structures/heap_monitor.h"

using namespace std;

class Datum
{
private:
	int den_;
	int hodina_;
	int minuty_;
public:
	Datum(int den, int hodina = 7, int minuty = 0);	
	Datum(Datum &datum);
	~Datum();
	int getHodina() { return hodina_;  };
	int getDen() { return den_; };
	void pridajHodinu();
	void vypisSa();
};


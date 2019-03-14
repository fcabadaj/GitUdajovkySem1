#pragma once

using namespace std;

class Datum
{
private:
	int den_;
	int mesiac_;
	int rok_;
	int hodina_;
public:
	Datum(int den, int mesiac, int rok, int hodina);
	~Datum();
};


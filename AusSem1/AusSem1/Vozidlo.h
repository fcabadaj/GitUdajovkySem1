#include <string>
#include <iostream>
#pragma once

using namespace std;

class Vozidlo
{
private:
	string spz_;
	int nosnost_;
	int prevadzkoveNaklady_;

public:
	Vozidlo(string spz, int nosnost, int prevadzkoveNaklady);
	~Vozidlo();
	void vypisVozidlo();
};


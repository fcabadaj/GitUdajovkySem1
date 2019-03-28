#include "structures/heap_monitor.h"
#include "Vozidlo.h"
#include <string>
#include <iomanip>

using namespace structures;
using namespace eRegiony;
using namespace std;

Vozidlo::Vozidlo(string spz, double nosnost, Datum *datum, double prevadzkoveNaklady, double aktZataz, double celk) :
	spz_(spz),
	nosnost_(nosnost),
	prevadzkoveNaklady_(prevadzkoveNaklady),
	datum_(datum),
	regiony_(new Array<EnumRegion*>(25)),
	objednavky_(new ArrayList<Objednavka*>),
	aktZataz_(aktZataz),
	celkPrevNaklady_(celk)
{
	initRegiony();
}

Vozidlo::~Vozidlo()
{
	spz_ = "";
	nosnost_ = 0;
	prevadzkoveNaklady_ = 0;
	delete datum_;

	for (unsigned int i = 0; i < regiony_->size(); i++)
	{
		delete regiony_->operator[](i);
	}
	delete regiony_;
	regiony_ = nullptr;


	for (unsigned int i = 0; i < objednavky_->size(); i++)
	{
		delete objednavky_->operator[](i);
	}
	delete objednavky_;
	objednavky_ = nullptr;
}

void Vozidlo::vypisSa()
{
	cout.precision(4);
	cout.fixed;
	cout << "SPZ: " << spz_ << " Nosnost: " << nosnost_ << " Celkove Prevadzkove Naklady: "<< celkPrevNaklady_ << " Datum pridania: " << " Den: " << datum_->getDen() << " Hodina: " << datum_->getHodina() << endl;
}

void Vozidlo::initRegiony()
{	
	for (unsigned int i = 0; i < regiony_->size(); i++)
	{
		EnumRegion nazovRegionu{ static_cast<EnumRegion>(i) };
		regiony_->operator[](i) = new EnumRegion(nazovRegionu);
	}
}

void Vozidlo::vypisRegiony()
{
	for (unsigned int i = 0; i < regiony_->size(); i++)
	{
		cout << regiony_->operator[](i) << endl;
	}
}

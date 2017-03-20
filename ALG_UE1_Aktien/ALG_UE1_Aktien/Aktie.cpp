#include "stdafx.h"
#include "Aktie.h"
#include "Datum.h"
#include <string>


Aktie::Aktie(std::string name, std::string kuerzel, std::string wertpapiernummer)
{
	Name = name;
	Kuerzel = kuerzel;
	Wertpapiernummer = wertpapiernummer;
}

Aktie::Aktie(const Aktie& other) { //Copy constructor fertig schreiben!!!
	Name = other.Name;
	Kuerzel = other.Kuerzel;
	Wertpapiernummer = other.Wertpapiernummer;
}

Aktie::~Aktie()
{
}

void Aktie::FuegeKurseintragHinzu(std::string datum, float open, float high, float low, float close, float adjclose, int volume) {
	int test;

}
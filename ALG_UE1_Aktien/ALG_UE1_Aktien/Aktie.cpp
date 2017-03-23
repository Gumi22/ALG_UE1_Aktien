#include "stdafx.h"
#include "Aktie.h"
#include "Datum.h"
#include <string>

#include <iostream>

Aktie::Aktie(std::string name, std::string kuerzel, std::string wertpapiernummer)
{
	std::cout << "Constructing aktie" << std::endl;

	Name = name;
	Kuerzel = kuerzel;
	Wertpapiernummer = wertpapiernummer;
	Kurse = new Kursdaten(MaxKursdaten);
}

Aktie::Aktie(const Aktie& other) {

	std::cout << "Copy-Constructing aktie" << std::endl;

	Name = other.Name;
	Kuerzel = other.Kuerzel;
	Wertpapiernummer = other.Wertpapiernummer;
	Kursdaten* Kurse(other.Kurse); //Copy Construktor aufrufen
}

Aktie & Aktie :: operator = (const Aktie& that) {

	std::cout << "aktie = aktie" << std::endl;

	Name = that.Name;
	Kuerzel = that.Kuerzel;
	Wertpapiernummer = that.Wertpapiernummer;
	Kursdaten* Kurse(that.Kurse); //Copy Construktor aufrufen
	return *this;
}


Aktie::~Aktie()
{
	std::cout << "Destructing aktie" << std::endl;
	//TODO: Make this!!!!!
}

void Aktie::FuegeKurseintragHinzu(std::string datum, float open, float high, float low, float close, float adjclose, int volume) {
	int test;
	//TODO: Make this!!!!!
}

std::string Aktie::AktuellsterKurseintrag() {
	//string, getrennt durch;
	//TODO: Make this!!!!!
	return "";
}

std::string Aktie::AlleKurseintraege() {
	//string, getrennt durch;
	//TODO: Make this!!!!!
	return "";
}
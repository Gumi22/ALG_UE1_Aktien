#include "stdafx.h"
#include "Aktie.h"
#include "Datum.h"
#include <string>
#include <sstream>

#include <iostream> //später weg

//Standard Constructor
//Aktie::Aktie()
//{
//	Kurse = new Kursdaten(MaxKursdaten);
//}

//Constructor
Aktie::Aktie(std::string name, std::string kuerzel, std::string wertpapiernummer)
{
	std::cout << "Constructing aktie" << std::endl;

	Name = name;
	Kuerzel = kuerzel;
	Wertpapiernummer = wertpapiernummer;
	Kurse = new Kursdaten(MaxKursdaten);
}

//Copy-Constructor
Aktie::Aktie(const Aktie& other) {

	std::cout << "Copy-Constructing aktie" << std::endl;

	Name = other.Name;
	Kuerzel = other.Kuerzel;
	Wertpapiernummer = other.Wertpapiernummer;
	Kursdaten* Kurse(other.Kurse); //Copy Construktor aufrufen
}

//Assignment operator
Aktie & Aktie :: operator = (const Aktie& that) {

	std::cout << "aktie = aktie" << std::endl;

	Name = that.Name;
	Kuerzel = that.Kuerzel;
	Wertpapiernummer = that.Wertpapiernummer;
	Kursdaten* Kurse(that.Kurse); //Copy Construktor aufrufen
	return *this;
}

//Destructor
Aktie::~Aktie()
{
	std::cout << "Destructing aktie" << std::endl;
	delete Kurse;
}


bool Aktie::FuegeKurseintragHinzu(std::string datum, float open, float high, float low, float close, float adjclose, int volume) {
	//Einfach Daten weitergeben
	return Kurse->NeuerEintrag(datum, open, high, low, close, adjclose, volume);
}

std::string Aktie::AktuellsterKurseintrag() {
	//string, getrennt durch;
	Aktienkurs* temp = Kurse->AktuellsterEintrag();
	std::stringstream ss;
	if (Kurse->KursCount() > 0) {
		ss << temp->Datum->getDatum() << ";" << temp->Open << ";" << temp->High << ";" << temp->Low << ";" << temp->Close << ";" << temp->AdjClose << ";" << temp->Volume << ";";
	}
	return ss.str();
}

std::string Aktie::AlleKurseintraege() {
	//string, getrennt durch;
	std::stringstream ss;
	if (Kurse->KursCount() > 0) {
		Aktienkurs* temp = Kurse->AlleKursdaten();
		for (int i = 0; i < Kurse->KursCount(); i++) {
			ss << temp[i].Datum->getDatum() << ";" << temp[i].Open << ";" << temp[i].High << ";" << temp[i].Low << ";" << temp[i].Close << ";" << temp[i].AdjClose << ";" << temp[i].Volume << '\n';
		}
	}
	return ss.str();
}

const std::string Aktie::GetName() {
	return Name;
}
const std::string Aktie::GetKuerzel() {
	return Kuerzel;
}
const std::string Aktie::GetWPN() {
	return Wertpapiernummer;
}
#pragma once

#include <string>
#include "Kursdaten.h"


class Aktie
{
public:
	Aktie(std::string, std::string, std::string); //Constructor
	Aktie(const Aktie&); //Copy Constructor
	Aktie & Aktie :: operator = (const Aktie& that); //Gleichsetzungsoperator
	virtual ~Aktie(); //Destructor
	void FuegeKurseintragHinzu(std::string, float, float, float, float, float, int);
	std::string AktuellsterKurseintrag(); //string, getrennt durch;
	std::string AlleKurseintraege(); //string getrennt durch;
	

private: 
	const int MaxKursdaten = 30;
	std::string Name;
	std::string Kuerzel;
	std::string Wertpapiernummer;
	Kursdaten* Kurse;
};


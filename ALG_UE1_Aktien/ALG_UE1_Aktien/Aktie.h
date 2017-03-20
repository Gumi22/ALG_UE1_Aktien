#pragma once

#include <string>
#include "Kursdaten.h"


class Aktie
{
public:
	Aktie(std::string, std::string, std::string); //Constructor
	Aktie(const Aktie&); //Copy Constructor
	virtual ~Aktie(); //Destructor
	void FuegeKurseintragHinzu(std::string, float, float, float, float, float, int);
	std::string Name;
	std::string Kuerzel;
	std::string Wertpapiernummer;

private: 
	const int MaxKursdaten = 30;


};


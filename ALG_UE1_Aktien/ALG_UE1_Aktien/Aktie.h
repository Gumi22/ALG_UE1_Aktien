#pragma once

#include <string>
#include "Kursdaten.h"
#include <fstream> //Filestream
#include <sstream> //Stringstream


class Aktie
{
public:
	//Aktie(); //Standard contructor
	Aktie(std::string, std::string, std::string); //Constructor
	Aktie(const Aktie&); //Copy Constructor
	Aktie & Aktie :: operator = (const Aktie& that); //Gleichsetzungsoperator
	virtual ~Aktie(); //Destructor
	bool FuegeKurseintragHinzu(std::string, float, float, float, float, float, int);
	std::string AktuellsterKurseintrag(); //string, getrennt durch;
	std::string AlleKurseintraege(); //string getrennt durch;
	const std::string GetName();
	const std::string GetKuerzel();
	const std::string GetWPN();
	void WriteDataToFile(std::string);

private: 
	const int MaxKursdaten = 30;
	std::string Name;
	std::string Kuerzel;
	std::string Wertpapiernummer;
	Kursdaten* Kurse;
};


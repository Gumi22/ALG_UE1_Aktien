#pragma once
#include <string>

class Datum
{
public:
	//Constructor
	Datum(std::string);
	//Destructor
	~Datum();
	//Gib das Datum als String zurück
	std::string getDatum()const;
	//Vergleiche ein anderes Datum mit diesem hier und gib zurück ob es aktueller ist.
	bool istAktuellerAls(const Datum&)const;

private:
	int Jahr;
	int Monat;
	int Tag;
};


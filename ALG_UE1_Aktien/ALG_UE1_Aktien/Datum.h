#pragma once
#include <string>

class Datum
{
public:
	//Constructor
	Datum(std::string);
	//Destructor
	~Datum();
	//Gib das Datum als String zur�ck
	std::string getDatum()const;
	//Vergleiche ein anderes Datum mit diesem hier und gib zur�ck ob es aktueller ist.
	bool istAktuellerAls(const Datum&)const;

private:
	int Jahr;
	int Monat;
	int Tag;
};


#include "stdafx.h"
#include "Datum.h"
#include <string>
#include <sstream>


//Erstellt ein Datum aus einem string mit der Formatierung: JJJJ-MM-TT
Datum::Datum(std::string datum) {
	for (int i = 0; i<datum.length(); i++) //Ersetze die '-' mit ' '
	{
		if (datum[i] == '-') {
			datum[i] = ' ';
		}
	}
	std::stringstream ss; //neuer Stringstream
	ss.str(datum); //Datum in den Stringstream schreiben
	ss >> Jahr; //Jahr in Jahr speichern usw.
	ss >> Monat;
	ss >> Tag;
}

//Destructor
Datum::~Datum()
{
}

std::string Datum::getDatum() const {
	std::stringstream ss; //neuer Stringstream
	ss << Jahr << "-" << Monat << "-" << Tag;
	return ss.str();
}

//Gibt true zurück wenn das übergebene Datum kleiner ist als das Datum des aufrufenden Objekts. Bei gleichem Datum wurd true zurückgegeben.
bool Datum::istAktuellerAls(const Datum& other) const{
	if (other.Jahr < this->Jahr) {
		return true;
	}
	else if (other.Jahr == this->Jahr) {
		if (other.Monat < this->Monat) {
			return true;
		}
		else if (other.Monat == this->Monat) {
			if (other.Tag < this->Tag) {
				return true;
			}
			else if (other.Tag == this->Tag) {
				return true;
			}
			return false;
		}
		return false;
	}
	return false;
}

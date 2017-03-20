#pragma once
#include "Datum.h"

struct Aktienkurs {
	Datum* Datum; //Datum des Kurseintrags
	float Open; //Startkurs
	float High; //Höchster Wert
	float Low; //Niedrigster Wert
	float Close; //Endkurs
	float AdjClose; //Berichtigter Kurs
	int Volume; //Volumen
	struct number *next; //Nächster Kurs
};

class Kursdaten
{
public:
	Kursdaten(int); //Constructor
	Kursdaten(const Kursdaten&); //Copy Constructor
	virtual ~Kursdaten();
	void FuegeKurseintragHinzu(std::string, float, float, float, float, float, int);
	const struct Aktienkurs AktuellsterEintrag();
	const struct Aktienkurs* AlleKursdaten();

private:
	int Size, Start, End; //Größe des Ringbuffers, Aktuellster-,  und Letzter Eintrag.
	Aktienkurs* AktuellsteDaten; //Ringbuffer der Kursdaten

	struct Aktienkurs* NeueAktie(Datum*, float, float, float, float, float, int);
	int IndexPosition(bool, int);
};



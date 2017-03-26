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
};

class Kursdaten
{
public:
	Kursdaten(int); //Constructor
	Kursdaten(const Kursdaten&); //Copy Constructor
	virtual ~Kursdaten();
	bool NeuerEintrag(std::string, float, float, float, float, float, int);
	struct Aktienkurs* AktuellsterEintrag();
	struct Aktienkurs* AlleKursdaten();
	int KursCount();

private:
	int Size, Start, End, Count; //Größe des Ringbuffers, Aktuellster-,  und Letzter Eintrag.
	Aktienkurs* AktuellsteDaten; //Ringbuffer der Kursdaten

	struct Aktienkurs* NeueAktie(Datum*, float, float, float, float, float, int);
	int IndexPosition(bool, int);
};



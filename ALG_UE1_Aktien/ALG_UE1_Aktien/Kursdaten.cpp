#include "stdafx.h"
#include "Kursdaten.h"
#include "Datum.h"

#include <iostream> //später weg


//Constructor
Kursdaten::Kursdaten(int size)
{

	std::cout << "Constructing Kursdaten" << std::endl;

	AktuellsteDaten = new Aktienkurs[size];
	Size = size;
	Start = 0;
	End = 0;
	Count = 0;
}

//Copy-Constructor:
Kursdaten::Kursdaten(const Kursdaten& other) {

	std::cout << "Constructing Kursdaten" << std::endl;

	Size = other.Size; //Kopiere die Member
	Start = other.Start;
	End = other.End;
	Count = other.Count;

	//Kopiere auch die Daten auf die der Pointer zeigt:
	Datum* temp; //Datum kopieren ist Kritisch, da der Member ein Pointer ist, wir aber die Daten kopieren wollen
	AktuellsteDaten = new Aktienkurs[other.Size]; //Dazu erstmal Speicher allokieren
	for (int i = 0; i < Size; i++) {
		AktuellsteDaten[i] = other.AktuellsteDaten[i]; //Kopiere die Member
		temp = new Datum(other.AktuellsteDaten[i].Datum->getDatum());
		AktuellsteDaten[i].Datum = temp;
	}
}

//Destructor
Kursdaten::~Kursdaten()
{
	std::cout << "Destructing Kursdaten" << std::endl;
	//Löschen aller Datumsklassen im Struct
	for (int i = 0; i < Count; i++) {
		delete AktuellsteDaten[(Start+i)%Size].Datum;
	}
	//Löschen des Arrays selber
	delete[] AktuellsteDaten; 
}

//Neuen Kurseintrag in die Aktie einfügen, falls er aktuell ist :)
bool Kursdaten::NeuerEintrag(std::string datum, float open, float high, float low, float close, float adjclose, int volume) {
	Datum* Date = new Datum(datum); //Erstelle ein Datum mit dem die aktuellen Daten verglichen werden können
	if (Count > 0) { //Wenn bereits Einträge vorhanden:
		if (!(AktuellsteDaten[End].Datum->istAktuellerAls(*Date))) //Ist die neue Aktie aktueller als zumindest die letzte gespeicherte Aktie?
		{
			if (!(AktuellsteDaten[Start].Datum->istAktuellerAls(*Date))) //Ist das neue Datum aktueller als das alte aktuellste? 
			{
				//Wenn ja, vorne anhängen
				AktuellsteDaten[IndexPosition(true, Start)] = *NeueAktie(Date, open, high, low, close, adjclose, volume);
				//Start vorverschieben
				Start = IndexPosition(true, Start);
				//Wenn Start nun dort hinzeigt wo Ende war, verschiebe das Ende auch eines nach vor.
				if (Start == End) {
					End = IndexPosition(true, End);
					Count--;
				}
				Count++;
				return true;
			}
			else {
				//Iterier durch, fügs ins entsprechende ein und tausche den rest
				int Platz = Start;
				while (AktuellsteDaten[Platz].Datum->istAktuellerAls(*Date)) {
					Platz = IndexPosition(false, Platz);
				}
				//Erstelle ein neues Element
				Aktienkurs newer = *NeueAktie(Date, open, high, low, close, adjclose, volume);

				//Tausche von hinten nach vorne das vorherige Element bis zum"Platz"
				for (int i = End; i != Platz; i = IndexPosition(true, i)) {
					//Tauschen :D
					AktuellsteDaten[i] = Aktienkurs(AktuellsteDaten[IndexPosition(true, i)]);
				}
				//Füge das neue Element an seinem Platz ein.
				AktuellsteDaten[Platz] = newer;
				return true;
			}
		}
		else {
			if (Count < Size) { //!(IndexPosition(true, Start) == End)
				//Ist das neue Datum älter als das Älteste und ist die Tabelle noch ned voll? -> hinten anhängen, End ändern
				End = IndexPosition(false, End);
				AktuellsteDaten[End] = *NeueAktie(Date, open, high, low, close, adjclose, volume);
				Count++;
				return true;
			}
			else {
				//Tabelle voll und Datum nicht aktuell? -> Lösche Datum und füg den Dateneintrag nicht ein ^^
				delete Date;
				return false;
			}
		}
		return false;
	}
	else { //Wenn noch kein Eintrag vorhanden:
		Count++;
		AktuellsteDaten[End] = *NeueAktie(Date, open, high, low, close, adjclose, volume);
		return true;
	}
}

//Gibt den aktuellsten Kurseintrag zurück
struct Aktienkurs* Kursdaten::AktuellsterEintrag() {
	return &AktuellsteDaten[Start];
}

//Gibt alle Kursdaten zurück
struct Aktienkurs* Kursdaten::AlleKursdaten() {
	return AktuellsteDaten;
}

//Erstellt neuen Kurseintrag
struct Aktienkurs* Kursdaten::NeueAktie(Datum* datum, float open, float high, float low, float close, float adjclose, int volume) {
	Aktienkurs* temp = new Aktienkurs(); //Lege neuen Aktienkurs an und befülle die Werte.
	temp->Datum = datum;
	temp->Open = open;
	temp->High = high;
	temp->Low = low;
	temp->Close = close;
	temp->AdjClose = adjclose;
	temp->Volume = volume;
	return temp;
}

//Gibt den Index der Angeforderten Position zurück. Vor = true: Index vor Pos, Vor = false: Index nach Pos
int Kursdaten::IndexPosition(bool Vor, int Pos) {
	if (Vor) {
		return (((Pos - 1) % Size) < 0) ? ((Pos - 1) % Size) + Size : ((Pos - 1) % Size);
	}
	else {
		return ((Pos + 1) % Size);
	}
	return 0;
}

//Gibt die Anzahl an gespeicherten Kursen zurück, bei leerer Liste, wird 1 zurückgegeben
int  Kursdaten::KursCount() {
	return Count;//(End >= Start) ? End - Start + 1 : (Size - (Start - End)) + 1;
}
#include "stdafx.h"
#include "Kursdaten.h"
#include "Datum.h"

//Constructor
Kursdaten::Kursdaten(int size)
{
	AktuellsteDaten = new Aktienkurs[size];
	Size = size;
	Start = 0;
	End = 0;
}

//Copy-Constructor:
Kursdaten::Kursdaten(const Kursdaten& other) {
	Size = other.Size; //Kopiere die Member
	Start = other.Start;
	End = other.End;

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
	//ToDo: Alle Sachen innerhalb von Aktiellste Daten löschen, also auch das Datum und das Struct :D
	for (int i = 0; i < Size; i++) {
		delete AktuellsteDaten[i].Datum;
	}
	delete[] AktuellsteDaten; 
}

//Neuen Kurseintrag in die Aktie einfügen, falls er aktuell ist :)
void Kursdaten::FuegeKurseintragHinzu(std::string datum, float open, float high, float low, float close, float adjclose, int volume) {
	Datum* Date = new Datum(datum); //Erstelle ein Datum mit dem die aktuellen Daten verglichen werden können

	if (!(AktuellsteDaten[End].Datum->istAktuellerAls(*Date))) //Ist die neue Aktie aktueller als zumindest die letzte gespeicherte Aktie?
	{
		if(!(AktuellsteDaten[Start].Datum->istAktuellerAls(*Date))) //Ist das neue Datum aktueller als das alte aktuellste? 
		{
			//Wenn ja, vorne anhängen
			AktuellsteDaten[IndexPosition(true, Start)] = *NeueAktie(Date, open, high, low, close, adjclose, volume);
			//Start vorverschieben
			Start = IndexPosition(true, Start);
			//Wenn Start nun dort hinzeigt wo Ende war, verschiebe das Ende auch eines nach vor.
			if(Start == End) {
				End = IndexPosition(true, End);
			}
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
		}
	}
	else {
		if (!(IndexPosition(true, Start) == End)) {
			//Ist das neue Datum älter als das Älteste und ist die Tabelle noch ned voll? -> hinten anhängen, End ändern
			End = IndexPosition(false, End);
			AktuellsteDaten[End] = *NeueAktie(Date, open, high, low, close, adjclose, volume);
		}
		else {
			//Tabelle voll und Datum nicht aktuell? -> Lösche Datum und füg den Dateneintrag nicht ein ^^
			delete Date;
		}
	}
	//AktuellsteDaten[Start] = *NeueAktie(Date, open, high, low, close, adjclose, volume);
}

const struct Aktienkurs Kursdaten::AktuellsterEintrag() {
	return AktuellsteDaten[Start];
}

const struct Aktienkurs* Kursdaten::AlleKursdaten() {
	Aktienkurs* temp = new Aktienkurs[Size];
	for (int i = 0; i < Size; i++) {
		temp[0] = Aktienkurs(AktuellsteDaten[((i + Start) % Size)]); //Rufe Copy-Costructor auf um Daten zu kopieren.
	}
	return temp;
}

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
		return ((Pos - 1) % Size);
	}
	else {
		return ((Pos + 1) % Size);
	}
	return 0;
}
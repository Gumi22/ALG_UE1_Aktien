// ALG_UE1_Aktien.cpp : Definiert den Einstiegspunkt fuer die Konsolenanwendung.
// Erstellt das Menu und fuehrt die ausgewaehlte Funktion aus, solange nicht beendet wird.

#include "stdafx.h"
#include <iostream> //I-O-Stream
#include <fstream> //Filestream
#include <sstream> //Stringstream
#include <string> //strings
#include "Hashtable.h"
#include "Aktie.h"


#define hashtablesize 1999
bool Add(Hashtable<Aktie*>*, Hashtable<Aktie*>*, std::string, std::string, std::string);
bool Del(Hashtable<Aktie*>*, Hashtable<Aktie*>*, std::string);

int main()
{
	using namespace std; //Wir wollen ja nicht immer std::cout und so tippen ^^
	bool AenderungenVorhanden = false;
	string menu;

	//How to create Hashtable:
	//Hashtable<int or Aktie> mytable(3);
	
	Hashtable<Aktie*>* Namen = new Hashtable<Aktie*>(hashtablesize); //Hashtable mit dem Namen als Key & Pointer auf Aktien :D
	Hashtable<Aktie*>* Kuerzel = new Hashtable<Aktie*>(hashtablesize); //Hashtable mit dem Kürzel als Key & Pointer auf Aktien :D
	//Menu und endlosschleife
	do {
		menu = "";
		//Print menu
		cout << "-------------------------------------------------------------------------------------------------------------------------" << endl;
		cout << "Hauptmenu:" << endl;
		cout << "1 - ADD: Aktienname Aktienkuerzel Wertpapiernummer: Eine Aktie mit Namen und Kuerzel wird hinzugefuegt." << endl;
		cout << "2 - DEL [Aktienname|Aktienkuerzel]: Aktie wird geloescht." << endl;
		cout << "3 - IMPORT Dateiname: Kurswerte fuer eine Aktie werden aus einer csv Datei importiert." << endl;
		cout << "4 - SEARCH [Aktienname|Aktienkuerzel]: Programm gibt den aktuellsten Kurseintrag der gesuchten Aktie aus." << endl;
		cout << "5 - PLOT [Aktienname|Aktienkuerzel]: Die Schlusskurse der letzten 30 Tage einer Aktie werden als ASCII Grafik ausgegeben." << endl;
		cout << "6 - SAVE Dateiname: Programm speichert die Hashtabelle in eine Datei ab." << endl;
		cout << "7 - LOAD Dateiname: Programm laedt die Hashtabelle aus einer Datei." << endl;
		cout << "8 - QUIT: Programm wird beendet." << endl;
		cout << "Bitte waehlen Sie: " << endl;
		cin >> menu;

		

		if (menu == "ADD" || menu == "1") {
			AenderungenVorhanden = true;
			string n, k, wpn;
			cin >> n >> k >> wpn;
			//Füge Verweise zur Aktie hinzu:
			if (Add(Namen, Kuerzel, n, k, wpn)) {
				cout << "Hinzufuegen der Aktie war erfolgreich" << endl;
			}
			else {
				cout << "Hinzufuegen der Aktie gescheitert, versuchen Sie es erneut. Speicher zu " << Kuerzel->Fullness() * 100 << "% voll" << endl;
			}
		}
		else if (menu == "DEL" || menu == "2") {
			AenderungenVorhanden = true;
			string in;
			cin >> in; //input einlesen: Kann Name oder Kürzel sein
			if (Del(Namen, Kuerzel, in)) {
				cout << "Loeschen erfolgreich." << endl;
			}
			else {
				cout << "Loeschen nicht erfolgreich." << endl;
			}
					}
		else if (menu == "IMPORT" || menu == "3") {
			AenderungenVorhanden = true;
			//ToDo: Fertigprogrammieren!!!!
			ifstream infile("c:/in.txt"); // for example
			string line = "";
			while (getline(infile, line)) {
				stringstream strstr(line);
				string word = "";
				while (getline(strstr, word, ';')) cout << word << '\n';
			}
		}
		else if (menu == "SEARCH" || menu == "4") {
			string Key = "";
			cin >> Key;
			Aktie * Gesucht;
			try {
				Gesucht = Namen->Suche(Key);
				cout << "Name: " << Gesucht->GetName() << endl << "Kuerzel: " << Gesucht->GetKuerzel() << endl << "Wertpapiernummer: " << Gesucht->GetWPN() << endl;
				cout << "Aktuellser Kurseintrag:" << Gesucht->AktuellsterKurseintrag() << endl;
			}
			catch (exception &e) {
				try {
					Gesucht = Kuerzel->Suche(Key);
					cout << "Name: " << Gesucht->GetName() << endl << "Kuerzel: " << Gesucht->GetKuerzel() << endl << "Wertpapiernummer: " << Gesucht->GetWPN() << endl;
					cout << "Aktuellser Kurseintrag:" << Gesucht->AktuellsterKurseintrag() << endl;
				}
				catch (exception &e) {
					cout << e.what() << endl;
				}
			}
			
		}
		else if (menu == "PLOT" || menu == "5") {

			//Ausgabe der Aktiendaten

		}
		else if (menu == "SAVE" || menu == "6") {
			AenderungenVorhanden = false;

			//speichern des zustandes des gesamten Hashtables (Serialisierung)

		}
		else if (menu == "LOAD" || menu == "7") {
			AenderungenVorhanden = true;

			//Lade hashtable export

		}
		else if (menu == "QUIT" || menu == "8") {
			if (AenderungenVorhanden) {
				cout << "Beim Beenden werden Ihre Aenderungen verworfen. Beenden: [1|J] Abbrechen: [2|N]";
				char Antwort;
				cin >> Antwort;
				if (Antwort == 'J' || Antwort == '1') { return 0; }
			}
			else {
				return 0;
			}
		}
	}
	while (true); //menu != "8" && menu != "QUIT"

    return 0;
}

//Fügt eine Aktie zu bestehenden Hashtables hinzu. 
//Bei Erfolg: true, bei Misserfolg: false;
bool Add(Hashtable<Aktie*>* namenalskey, Hashtable<Aktie*>* kuerzelalskey, std::string name, std::string kuerzel, std::string wertpapiernummer) {
	Aktie* ziel = new Aktie(name, kuerzel, wertpapiernummer);
	if (namenalskey->Add(ziel, name)) {
		if (kuerzelalskey->Add(ziel, kuerzel)) {
			return true;
		}
		else {
			try {
				namenalskey->Remove(name);//Nameneintrag löschen
			}
			catch (std::exception &e) {
				std::cout << e.what() << std::endl;
			}
			delete ziel;
			return false;
		}
	}
	else {
		delete ziel;
		return false;
	}
	return true;
}

//Löscht eine Aktie aus bestehenden Hashtables, anhand eines Keys, der entweder Name oder Kürzel der Aktie ist. 
//Bei Erfolg: true, bei Misserfolg: false;
bool Del(Hashtable<Aktie*>* namenalskey, Hashtable<Aktie*>* kuerzelalskey, std::string key) {
	try {
		Aktie* na = namenalskey->Remove(key); //Versuche den Input als Namen zu interpretieren
		try {
			Aktie* ku = kuerzelalskey->Remove(na->GetKuerzel()); //Versuche das Kürzel der Aktie in der anderen Liste zu löschen
			if (na == ku) { //Sind die Pointer ehh dieselben?
				delete na; //Dann lösche die Aktie
				return true;
			}
			else {
				namenalskey->Add(na, na->GetName()); //Wieder einfügen
				kuerzelalskey->Add(ku, ku->GetKuerzel()); //Wieder einfügen
				return false;
			}
		}
		catch (std::exception &e) {
			namenalskey->Add(na, na->GetName()); //Wieder einfügen
			std::cout << e.what() << std::endl;
			return false;
		}
	}
	catch (std::exception &e) {
		try {
			Aktie* ku = kuerzelalskey->Remove(key); //Versuche den Input als Kürzel zu interpretieren
			try {
				Aktie* na = namenalskey->Remove(ku->GetName()); //Versuche den Namen der Aktie in der anderen Liste zu löschen
				if (na == ku) { //Sind die Pointer ehh dieselben?
					delete na; //Dann lösche die Aktie
					return true;
				}
				else {
					namenalskey->Add(na, na->GetName()); //Wieder einfügen
					kuerzelalskey->Add(ku, ku->GetKuerzel()); //Wieder einfügen
					return false;
				}
			}
			catch (std::exception &e) {
				kuerzelalskey->Add(ku, ku->GetKuerzel()); //Wieder einfügen
				std::cout << e.what() << std::endl;
				return false;
			}
		}
		catch (std::exception &e) {
			std::cout << e.what() << std::endl;
			return false;
		}
		std::cout << e.what() << std::endl;
	}
	return true;
}








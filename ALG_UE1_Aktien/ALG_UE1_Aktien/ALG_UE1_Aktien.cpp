// ALG_UE1_Aktien.cpp : Definiert den Einstiegspunkt fuer die Konsolenanwendung.
// Erstellt das Menu und fuehrt die ausgewaehlte Funktion aus, solange nicht beendet wird.

#include "stdafx.h"
#include <iostream> //I-O-Stream
#include <fstream> //Filestream
#include <string> //strings
#include "Hashtable.h"
#include "Aktie.h"


#define hashtablesize 1999


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
			cin >> n;
			cin >> k;
			cin >> wpn;
			Aktie* neueAktie = new Aktie(n, k, wpn);
			//Füge Verweise zur Aktie hinzu:
			if (Namen->Add(neueAktie, n)) {
				if (Kuerzel->Add(neueAktie, k)) {
					cout << "Hinzufuegen der Aktie war erfolgreich" << endl;
				}
				else {
					cout << "Hinzufuegen der Aktie gescheitert, versuchen Sie es erneut. Speicher zu " << Kuerzel->Fullness() * 100 << "% voll" << endl;
					try {
						Namen->Remove(n);//Nameneintrag löschen
					}
					catch (exception &e) {
						cout << e.what() << endl;
					}
					delete neueAktie; //löschen, falls hinzufügen nicht geklappt hat
				}
			}
			else {
				cout << "Hinzufuegen der Aktie gescheitert, versuchen Sie es erneut. Speicher zu " << Namen->Fullness()*100 << "% voll" << endl;
				delete neueAktie; //löschen, falls hinzufügen nicht geklappt hat
			}
		}
		else if (menu == "DEL" || menu == "2") {
			AenderungenVorhanden = true;
			string in;
			cin >> in; //input einlesen: Kann Name oder Kürzel sein
			try {
				Aktie* na = Namen->Remove(in); //Versuche den Input als Namen zu interpretieren
				try {
					Aktie* ku = Kuerzel->Remove(na->GetKuerzel()); //Versuche das Kürzel der Aktie in der anderen Liste zu löschen
					if (na == ku) { //Sind die Pointer ehh dieselben?
						delete na; //Dann lösche die Aktie
						cout << "Loeschen erfolgreich." << endl;
					}
					else {
						Namen->Add(na, na->GetName()); //Wieder einfügen
						Kuerzel->Add(ku, ku->GetKuerzel()); //Wieder einfügen
						cout << "Loeschen nicht erfolgreich." << endl;
					}
				}
				catch (exception &e) {
					Namen->Add(na, na->GetName()); //Wieder einfügen
					cout << "Loeschen nicht erfolgreich." << endl;
					cout << e.what() << endl;
				}
			}
			catch (exception &e) {
				try {
					Aktie* ku = Kuerzel->Remove(in); //Versuche den Input als Kürzel zu interpretieren
					try {
						Aktie* na = Namen->Remove(ku->GetName()); //Versuche den Namen der Aktie in der anderen Liste zu löschen
						if (na == ku) { //Sind die Pointer ehh dieselben?
							delete na; //Dann lösche die Aktie
							cout << "Loeschen erfolgreich." << endl;
						}
						else {
							Namen->Add(na, na->GetName()); //Wieder einfügen
							Kuerzel->Add(ku, ku->GetKuerzel()); //Wieder einfügen
							cout << "Loeschen nicht erfolgreich." << endl;
						}
					}
					catch (exception &e) {
						Kuerzel->Add(ku, ku->GetKuerzel()); //Wieder einfügen
						cout << "Loeschen nicht erfolgreich." << endl;
						cout << e.what() << endl;
					}
				}
				catch (exception &e) {
					cout << "Loeschen nicht erfolgreich." << endl;
					cout << e.what() << endl;
				}
				//cout << e.what() << endl;
			}

		}
		else if (menu == "IMPORT" || menu == "3") {
			AenderungenVorhanden = true;


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




// ALG_UE1_Aktien.cpp : Definiert den Einstiegspunkt fuer die Konsolenanwendung.
// Erstellt das Menu und fuehrt die ausgewaehlte Funktion aus, solange nicht beendet wird.

#include "stdafx.h"
#include <iostream>
#include <string>
#include "Hashtable.h"

#include <time.h> 

#define hashtablesize 1999


int main()
{
	using namespace std; //Wir wollen ja nicht immer std::cout und so tippen ^^
	bool AenderungenVorhanden = false;
	string menu;

	//How to create Hashtable:
	//Hashtable<int or Aktie> mytable(3);

	//Menu und endlosschleife
	Hashtable<string>* mytable = new Hashtable<string>(hashtablesize);
	do {
		menu = "";
		//Print menu
		cout << "Hauptmenu:" << endl;
		cout << "1 - ADD: Aktienname Aktienkuerzel [Wertpapiernummer]Eine Aktie mit Namen und Kuerzel wird hinzugefuegt." << endl;
		cout << "2 - DEL [Aktienname|Aktienkuerzel]: Aktie wird geloescht." << endl;
		cout << "3 - IMPORT Dateiname: Kurswerte fuer eine Aktie werden aus einer csv Datei importiert." << endl;
		cout << "4 - SEARCH [Aktienname|Aktienkuerzel]: Programm gibt den aktuellsten Kurseintrag der gesuchten Aktie aus." << endl;
		cout << "5 - PLOT [Aktienname|Aktienkuerzel]: Die Schlusskurse der letzten 30 Tage einer Aktie werden als ASCII Grafik ausgegeben." << endl;
		cout << "6 - SAVE Dateiname: Programm speichert die Hashtabelle in eine Datei ab." << endl;
		cout << "7 - LOAD Dateiname: Programm laedt die Hashtabelle aus einer Datei." << endl;
		cout << "8 - QUIT: Programm wird beendet." << endl;
		cout << "Bitte waehlen Sie: " << endl;
		cin >> menu;

		
		if (menu == "0") { //TESTFUNKTION :D
			string X = "dddd";
			static const char alphanum[] =
				"0123456789"
				"ABCDEFGHIJKLMNOPQRSTUVWXYZ"
				"abcdefghijklmnopqrstuvwxyz";

			string* Y = new string[hashtablesize];
			for (int i = 0; i < hashtablesize; i++) {

				try {
					for (int i = 0; i < 4; ++i) {
						X[i] = alphanum[rand() % (sizeof(alphanum) - 1)];
					}
					Y[i] = X;
				}
				catch (exception &e) {
					//cout << e.what() << endl;
				}
			}

			double time1 = 0.0, tstart;      // time measurment variables
			tstart = clock();
			for (int i = 0; i < hashtablesize; i++) {
				mytable->Add(Y[i], Y[i]);
			}
			time1 += clock() - tstart;     // end
			time1 = time1 / CLOCKS_PER_SEC;  // rescale to seconds
			cout << "  time = " << time1 << " sec." << endl;
		}




		if (menu == "ADD" || menu == "1") {
			AenderungenVorhanden = true;

			
		}
		else if (menu == "DEL" || menu == "2") {
			AenderungenVorhanden = true;


		}
		else if (menu == "IMPORT" || menu == "3") {
			AenderungenVorhanden = true;


		}
		else if (menu == "SEARCH" || menu == "4") {
			cout << "Geben sie ihren Key ein" << endl;
			string Key = "";
			cin >> Key;
			try {
				cout << mytable->Suche(Key);
				cout << "Gefunden :D" << endl ;
			}
			catch (exception &e) {
				cout << e.what() << endl;
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
	while (menu != "8" && menu != "QUIT");

    return 0;
}




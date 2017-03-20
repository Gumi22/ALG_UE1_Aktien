// ALG_UE1_Aktien.cpp : Definiert den Einstiegspunkt für die Konsolenanwendung.
// Erstellt das Menu und führt die ausgewählte Funktion aus, solange nicht beendet wird.

#include "stdafx.h"
#include <iostream>
#include <string>
#include "Hashtable.h"

#define hashtablesize 1999


int main()
{
	using namespace std; //Wir wollen ja nicht immer std::cout und so tippen ^^
	string menu;

	//How to create Hashtable:
	//Hashtable<int or Aktie> mytable(3);

	//Menu und endlosschleife
	Hashtable<string>* mytable = new Hashtable<string>(1999);
	do {
		menu = "";
		//Print menu
		cout << "Hauptmenu:" << endl;
		cout << "1 - ADD: Eine Aktie mit Namen und Kürzel wird hinzugefügt." << endl;
		cout << "2 - DEL <Aktienname||Aktienkürzel>: Aktie wird gelöscht." << endl;
		cout << "3 - IMPORT <Dateiname>: Kurswerte für eine Aktie werden aus einer csv Datei importiert." << endl;
		cout << "4 - SEARCH <Aktienname||Aktienkürzel>: Programm gibt den aktuellsten Kurseintrag der gesuchten Aktie aus." << endl;
		cout << "5 - PLOT <Aktienname||Aktienkürzel>: Die Schlusskurse der letzten 30 Tage einer Aktie werden als ASCII Grafik ausgegeben." << endl;
		cout << "6 - SAVE <Dateiname>: Programm speichert die Hashtabelle in eine Datei ab." << endl;
		cout << "7 - LOAD <Dateiname>: Programm lädt die Hashtabelle aus einer Datei." << endl;
		cout << "8 - QUIT: Programm wird beendet." << endl;
		cout << "Bitte wählen Sie: " << endl;
		cin >> menu;

		
		
		if (menu == "ADD" || menu == "1") {
			string X = "asda";
			static const char alphanum[] =
				"0123456789"
				"ABCDEFGHIJKLMNOPQRSTUVWXYZ"
				"abcdefghijklmnopqrstuvwxyz";
			for (int i = 0; i < 1999; i++) {
				
				try {
					for (int i = 0; i < 4; ++i) {
						X[i] = alphanum[rand() % (sizeof(alphanum) - 1)];
					}
					cout << "versuche: "<< X << endl;
					mytable->Add(X, X);
				}
				catch(exception &e){
					cout << e.what() << endl;
				}
			}
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
		
	}
	while (menu != "8" && menu != "QUIT");

    return 0;
}




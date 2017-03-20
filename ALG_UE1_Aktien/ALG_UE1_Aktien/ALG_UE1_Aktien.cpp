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
			Hashtable<string> mytable(99991);
			string X = "asdassds dsd ss";
			static const char alphanum[] =
				"0123456789"
				"ABCDEFGHIJKLMNOPQRSTUVWXYZ"
				"abcdefghijklmnopqrstuvwxyz";
			for (int i = 0; i < 99991; i++) {
				
				try {
					for (int i = 0; i < 15; ++i) {
						X[i] = alphanum[rand() % (sizeof(alphanum) - 1)];
					}
					mytable.Add(X, X);
				}
				catch(exception &e){
					cout << e.what() << endl;
				}
			}
			cout << mytable.FindHighestStepstonecount() << endl;
			cout <<  mytable.FindHighestTimesJumped() << endl;
		}
		
	}
	while (menu != "8" && menu != "QUIT");

    return 0;
}




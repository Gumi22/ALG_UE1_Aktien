// ALG_UE1_Aktien.cpp : Definiert den Einstiegspunkt f�r die Konsolenanwendung.
// Erstellt das Menu und f�hrt die ausgew�hlte Funktion aus, solange nicht beendet wird.

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
		cout << "1 - ADD: Eine Aktie mit Namen und K�rzel wird hinzugef�gt." << endl;
		cout << "2 - DEL <Aktienname||Aktienk�rzel>: Aktie wird gel�scht." << endl;
		cout << "3 - IMPORT <Dateiname>: Kurswerte f�r eine Aktie werden aus einer csv Datei importiert." << endl;
		cout << "4 - SEARCH <Aktienname||Aktienk�rzel>: Programm gibt den aktuellsten Kurseintrag der gesuchten Aktie aus." << endl;
		cout << "5 - PLOT <Aktienname||Aktienk�rzel>: Die Schlusskurse der letzten 30 Tage einer Aktie werden als ASCII Grafik ausgegeben." << endl;
		cout << "6 - SAVE <Dateiname>: Programm speichert die Hashtabelle in eine Datei ab." << endl;
		cout << "7 - LOAD <Dateiname>: Programm l�dt die Hashtabelle aus einer Datei." << endl;
		cout << "8 - QUIT: Programm wird beendet." << endl;
		cout << "Bitte w�hlen Sie: " << endl;
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




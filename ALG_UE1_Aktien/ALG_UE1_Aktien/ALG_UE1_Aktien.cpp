// ALG_UE1_Aktien.cpp : Definiert den Einstiegspunkt fuer die Konsolenanwendung.
// Erstellt das Menu und fuehrt die ausgewaehlte Funktion aus, solange nicht beendet wird.

#include "stdafx.h"
#include <iostream> //I-O-Stream
#include <fstream> //Filestream
#include <sstream> //Stringstream
#include <string> //strings
#include <math.h>//Mathematics (so magic) --> just for rounding doubles ;)
#include "Hashtable.h"
#include "Aktie.h"
#include "spline.h" //Wird fürs Plot benutzt

#define hashtablesize 99991
bool Add(Hashtable<Aktie*>*, Hashtable<Aktie*>*, std::string, std::string, std::string);
bool Del(Hashtable<Aktie*>*, Hashtable<Aktie*>*, std::string);
void PlotAll(Aktie *, int, int);
void Load(std::string, Hashtable<Aktie*>*, Hashtable<Aktie*>*);


int main()
{
	using namespace std; //Wir wollen ja nicht immer std::cout und so tippen ^^
	bool AenderungenVorhanden = false;
	string menu;

	//How to create Hashtable:
	//Hashtable<int or Aktie> mytable(3);
	
	Hashtable<Aktie*>* Namen = new Hashtable<Aktie*>(hashtablesize); //Hashtable mit dem Namen als Key & Pointer auf Aktien :D
	Hashtable<Aktie*>* Kuerzel = new Hashtable<Aktie*>(hashtablesize); //Hashtable mit dem Kürzel als Key & Pointer auf Aktien :D
	
	//Menu und endlosschleife:
	do {
		menu = "";
		//Print menu
		cout << "-------------------------------------------------------------------------------------------------------------------------" << endl;
		cout << "Hauptmenu:" << endl;
		cout << "1 - ADD: Aktienname Aktienkuerzel Wertpapiernummer: Eine Aktie mit Namen und Kuerzel wird hinzugefuegt." << endl;
		cout << "2 - DEL [Aktienname|Aktienkuerzel]: Aktie wird geloescht." << endl;
		cout << "3 - IMPORT [Aktienname|Aktienkuerzel] Dateiname: Kurswerte fuer die angegebene Aktie werden aus einer csv Datei importiert." << endl;
		cout << "4 - SEARCH [Aktienname|Aktienkuerzel]: Programm gibt den aktuellsten Kurseintrag der gesuchten Aktie aus." << endl;
		cout << "5 - PLOT [Aktienname|Aktienkuerzel] Breite Hoehe: Die Schlusskurse einer Aktie werden als ASCII Grafik ausgegeben." << endl;
		cout << "6 - SAVE Dateiname: Programm speichert die Hashtabelle in eine Datei ab." << endl;
		cout << "7 - LOAD Dateiname: Programm laedt die Hashtabelle aus einer Datei." << endl;
		cout << "8 - QUIT: Programm wird beendet." << endl;
		cout << "Bitte waehlen Sie: " << endl;
		cin >> menu;

		//ToDo: Wenn das Kürzel einer Aktie gleich dem Namen einer anderen Aktie ist, kann man nie nach dem Kürzel suchen, da immer der Name der Aktie zuerst gesucht wird.
		///* Testfunktionen:
		if (menu == "0") {
			//Tests hier bitte:
			Namen->Test01();
		} //*/
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
			string Dateiname, Key;
			cin >> Key >> Dateiname; //Lies Dateiname und Key ein
			ifstream infile(Dateiname); // Öffne Filestream
			string line = "";
			Aktie* Ziel = nullptr; //Die Aktie zu der die Kursdaten hinzugefügt werden sollen.
			bool Sucherfolg = false; //Gibt an ob die Aktie gefunden wurde.

			//ToDo: Schreibe das in eine Funktion und benutze den Search dann im Add und Delete.
			try {
				Ziel = Namen->Suche(Key);
				Sucherfolg = true;
			}
			catch (exception &e) {
				//cout << e.what() << endl;
				try {
					Ziel = Kuerzel->Suche(Key);
					Sucherfolg = true;
				}
				catch (exception &e) {
					//cout << e.what() << endl;
				}
			}
			if (Sucherfolg) { // Wenn Suche geklappt hat, versuche das File zu lesen:
				getline(infile, line); //erste Zeile wird eingelesen und verworfen, da sie nur die Zeilenüberschriften enthält
			//Lies Kursdaten ein:
				while (getline(infile, line)) { //Solange das Einlesen der nächsten Zeile gelingt
					stringstream strstr(line); //Mach aus der Zeile einen eigenen Stream
					string Date, Open, High, Low, Close, Volume, AdjClose;
					//Lies die Werte aus der Zeile aus
					getline(strstr, Date, ',');
					getline(strstr, Open, ',');
					getline(strstr, High, ',');
					getline(strstr, Low, ',');
					getline(strstr, Close, ',');
					getline(strstr, Volume, ',');
					getline(strstr, AdjClose);
					//cout << Date << ',' << Open << ',' << High << ','  << Low << ',' << Close << ',' << Volume << ',' << AdjClose << endl;
					//Konvertiere die Werte in die richtigen Datenformate und füge sie als Kurseintrag zur Aktie hinzu
					Ziel->FuegeKurseintragHinzu(Date, 
						stof(Open, nullptr),
						stof(High, nullptr),
						stof(Low, nullptr),
						stof(Close, nullptr),
						stof(AdjClose, nullptr),
						stoi(Volume, nullptr, 10));
				}
				//cout << Ziel->AlleKurseintraege() << endl;
				cout << "Daten wurden eingelesen." << endl;
			}
			else {
				cout << "Zielaktie wurde nicht gefunden." << endl;
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
			string Key = "";
			string Breite = "";
			string Hoehe = "";
			cin >> Key >> Breite >> Hoehe;
			Aktie * Gesucht;
			try {
				Gesucht = Namen->Suche(Key);
				cout << "Name: " << Gesucht->GetName() << endl << "Kuerzel: " << Gesucht->GetKuerzel() << endl << "Wertpapiernummer: " << Gesucht->GetWPN() << endl;
				PlotAll(Gesucht, stoi(Breite), stoi(Hoehe));
			}
			catch (exception &e) {
				try {
					Gesucht = Kuerzel->Suche(Key);
					cout << "Name: " << Gesucht->GetName() << endl << "Kuerzel: " << Gesucht->GetKuerzel() << endl << "Wertpapiernummer: " << Gesucht->GetWPN() << endl;
					PlotAll(Gesucht, stoi(Breite), stoi(Hoehe));
				}
				catch (exception &e) {
					cout << e.what() << endl;
				}
			}
			

			
			

		}
		else if (menu == "SAVE" || menu == "6") {
			AenderungenVorhanden = false;
			//speichern des zustandes des gesamten Hashtables (Serialisierung)
			string Dateiname;
			cin >> Dateiname; //Lies Dateiname ein
			fstream file; 
			
			file.open(Dateiname, fstream::in | fstream::out | fstream::trunc); // Öffne Filestream
			//Schreib Überschrift und Anzahl der Aktien rein:
			file << Namen->GetDataCount() << endl;
			file.close();

			Aktie** Data;
			Data = Namen->GetAllData(); //Hol die Pointer auf alle Aktien;

			//Für jede Aktie rufe die WriteDataToFile Funktion der Aktie auf
			for (int i = 0; i < Namen->GetDataCount(); i++) {
				Data[i]->WriteDataToFile(Dateiname);
			}

			cout << "Hashtable erfolgreich gespeichert" << endl;
			

		}
		else if (menu == "LOAD" || menu == "7") {
			AenderungenVorhanden = true;
			
			string data_name = "";

			std::cin >> data_name;

			Load(data_name, Namen, Kuerzel);
			

			//Lade hashtable export

		}
		else if (menu == "QUIT" || menu == "8") {
			if (AenderungenVorhanden) {
				cout << "Beim Beenden werden Ihre Aenderungen verworfen. Beenden: [1|J] Abbrechen: [2|N]";
				char Antwort;
				cin >> Antwort;
				if (Antwort == 'J' || Antwort == '1') {
					//ToDo: Lösche Hashtables
					return 0; 
				}
			}
			else {
				//ToDo: Lösche Hashtables
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

///Funktion zeichnet in einerm Array die Schlusskurse der letzten 30 Tage.
void PlotAll(Aktie * MeineAktie, int Width, int Height)

{
	//Höhe und Breite auf mindestgrößen stellen
	if (Width < 30) {
		Width = 30;
	}
	if (Height < 10) {
		Height = 10;
	}

	using namespace std;

	double close[30] = { 0 };

	//Erzeugen eines dynamischen 2 dimensionalen Char[]
	char** myGraph = new char*[Height];
	for (int i = 0; i < Height; i++) {
		myGraph[i] = new char[Width];
		for (int j = 0; j < Width; j++) {
			myGraph[i][j] = ' ';
		}
	}

	//Erzeugen unseres Arrays, dass die Kurve enthält in der richtigen "Auflösung"
	double* InterpolatedClose = new double[Width];

	char test[11][30] = { ' ' };


	int a = 0;
	
	string AlleKursdaten = MeineAktie->AlleKurseintraege();
	
	stringstream str(AlleKursdaten);

	string line = "";

	string temp2 = "";

	int AnzahlKursdaten = 0;

	while (getline(str, line, '\n'))
	{
		AnzahlKursdaten++;
		stringstream temp1(line);

		for (int i = 0; i <= 4; i++)
		{
			getline(temp1, temp2, ';');
		}

		close[a] = stod(temp2);
		
		a++;
	}

	double min = close[0];
	double max = close[0];
	double diff = 0;

	for (int i = 1; i < 30; i++)
	{
		if (close[i] > max)
		{
			max = close[i];
		}
		else if (close[i] < min && close[i] != 0)
		{
			min = close[i];
		}
	}

	diff = max - min;

	//cout << diff << " " << max << " " << min << " " << endl;
	double c = 0;

	for (int i = 0; i < 30; i++)
	{
		if (close[i] > 0)
		{
			c = (close[i] - min) / diff;
			close[i] = c;
		}
		else
		{
			close[i] = 0;
		}
		
	}

	//Erzeuge die Vektoren fürs "Interpolieren":
	std::vector<double> X(AnzahlKursdaten), Y(AnzahlKursdaten);
	for (int i = 0; i < AnzahlKursdaten; i++) {
		X[i] = i;
		Y[i] = close[i];
	}

	tk::spline s; //erzeuge Interpolationsfunktion
	s.set_points(X, Y);    //Setze die Vektoren :D

	double Scale = ((double)AnzahlKursdaten - 1) / ((double)Width - 1);
	//Berechnen der Interpolationen aus dem close[] und schreiben der Daten in InterpolatedClose;
	for (int i = 0; i < Width; i++) { //Berechne dir für jeden Punkt im Array InterpolatedClose die correspondierenden %
		InterpolatedClose[i] = s(((double)i*Scale)); //Berechne dir den Punkt an dem wir die Höhe haben wollen.
	}
	cout << "Schlusskurse der letzten 30 Tage: " << endl;
	//Ausgeben der Interpolierten Punkte;

	for (int i = 0; i < Width; i++)
	{
		myGraph[Height-1 - (int)round(InterpolatedClose[i] * (Height-1))][i] = '#';
	}



	for (int i = 0; i < Height; i++)
	{
		for (int j = 0; j < Width; j++)
		{
			std::cout << myGraph[i][j];
		}
		std::cout << std::endl;
	}

	cout << endl;
	
	/*
	std::cout << "Schlusskurse der letzten 30 Tage: " << std::endl;
	std::cout << std::endl;
	
	///Initialisiert das char Array mit Sternen und fügt am linken und unteren Rand Linien für die Achsen inklusive Bezeichnungen hinzu!
	///Skalierung wurde mit 10 zu 30 gewählt da man nur die letzten 30 Schlussdaten ausgeben muss und diese sich in einem Bereich von 0-100 bewegen. (Kursdaten/10)

	///Initialisiert Array mit Sternen (blank-Canvas)
	///No functional stuff done here 
	for (int i = 0; i <= 10; i++)
	{
		for (int j = 0; j < 30; j++)
		{
			test[i][j] = '*';
			test[10][j] = '-';
			test[i][0] = '|';
		}
	}

	for (int i = 0; i < 30; i++)
	{
		test[10-(int)round(close[i]*10)][i] = '#';
	}

	for (int i = 0; i <= 10; i++)
	{
		for (int j = 0; j < 30; j++)
		{
			std::cout << test[i][j];
		}
		std::cout << std::endl;
	}
	*/

	//Löschen der Variablen
	for (int i = 0; i < Height; i++) {
		delete[] myGraph[i];
	}
	delete[] myGraph;
	delete[] InterpolatedClose;
}

void Load(std::string name, Hashtable<Aktie*>* hash_name, Hashtable<Aktie*>* hash_kuerzel)
{
	using namespace std;

	

	ifstream input(name);
	string line = "";

	getline(input, line);

	string first_line = line;

	int count = stoi(line);

	for (int i = 0; i < count; i++)
	{
		string Name;
		string Kuerzel;
		string WPN;
		string figure;


		getline(input, Name, ' ');
		getline(input, Kuerzel, ' ');
		getline(input, WPN, ' ');
		getline(input, figure, '\n');

		Aktie* newAktie = new Aktie(Name, Kuerzel, WPN);

		int data_count = 0;
		int number = stoi(figure);

		data_count = stoi(figure);

		hash_name->Add(newAktie, Name);

		hash_kuerzel->Add(newAktie, Kuerzel);

		for (int j = 0; j < number; j++)
		{
			string aktien_line;
			getline(input, aktien_line);

			stringstream strstr(aktien_line); //Mach aus der Zeile einen eigenen Stream

			string Date, Open, High, Low, Close, Volume, AdjClose;

			//Lies die Werte aus der Zeile aus
			getline(strstr, Date, ';');
			getline(strstr, Open, ';');
			getline(strstr, High, ';');
			getline(strstr, Low, ';');
			getline(strstr, Close, ';');
			getline(strstr, Volume, ';');
			getline(strstr, AdjClose);

			//cout << Date << ',' << Open << ',' << High << ','  << Low << ',' << Close << ',' << Volume << ',' << AdjClose << endl;
			//Konvertiere die Werte in die richtigen Datenformate und füge sie als Kurseintrag zur Aktie hinzu

			newAktie->FuegeKurseintragHinzu(Date,
				stof(Open, nullptr),
				stof(High, nullptr),
				stof(Low, nullptr),
				stof(Close, nullptr),
				stof(AdjClose, nullptr),
				stoi(Volume, nullptr, 10));
		}
	}

}








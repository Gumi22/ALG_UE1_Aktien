#pragma once

#include <string>
#include <stdexcept>
#include <math.h>

#include <iostream> //sp�ter weg, Ben�tigt f�r Testfunktionen
#include <ctime> //Ben�tigt f�r Testfunktionen

template <class Type> class Hashtable
{
	public:
		///* Testfunktion, um bestimmte Sachen zu messen:
		void Test01() {
			std::clock_t start0;
			std::clock_t start1;
			std::clock_t start2;
			std::clock_t start3;
			std::clock_t start4;
			int AnzahlDerTests = 1999;
			Aktie* Dummy = new Aktie("t", "t", "1");
			double duration;
			static const char alphanum[] =
				"0123456789"
				"ABCDEFGHIJKLMNOPQRSTUVWXYZ"
				"abcdefghijklmnopqrstuvwxyz";

			//Messen der Zeit f�r AnzahlDerTests hashes eines strings mit 4 L�nge:
			start1 = std::clock();
			for (int i = 0; i < AnzahlDerTests; i++) {
				hash("test");
			}
			duration = (std::clock() - start1) / (double)CLOCKS_PER_SEC;
			std::cout << "4 Laenge hashed: " << duration << "Sekunden \n";

			//Messen der Zeit f�r AnzahlDerTests hashes eines strings mit 30 L�nge:
			start2 = std::clock();
			for (int i = 0; i < AnzahlDerTests; i++) {
				hash("1234567890qwertzuioplkjhgfdsay");
			}
			duration = (std::clock() - start2) / (double)CLOCKS_PER_SEC;
			std::cout << "30 Laenge hashed: " << duration << "Sekunden \n";

			//Messen der Zeit f�r AnzahlDerTests inserts eines strings mit 4 L�nge:
			std::string seed1 = "test";
			std::string* keys1 = new std::string[AnzahlDerTests];
			for (int y = 0; y < AnzahlDerTests; y++) {
				for (int i = 0; i < 4; ++i) {
					seed1[i] = alphanum[rand() % (sizeof(alphanum) - 1)];
				}
				seed1[4] = 0;
				keys1[y] = seed1;
			}
			start3 = std::clock();
			for (int i = 0; i < AnzahlDerTests; i++) {
				Add(Dummy, keys1[i]);
			}
			duration = (std::clock() - start3) / (double)CLOCKS_PER_SEC;
			std::cout << "4 Laenge insert: " << duration << "Sekunden \n";
			start3 = std::clock();
			for (int i = 0; i < AnzahlDerTests; i++) {
				try {
					Remove(keys1[i]);
				}
				catch(std::exception){
					//nothinge
				}
			}
			duration = (std::clock() - start3) / (double)CLOCKS_PER_SEC;
			std::cout << "4 Laenge delete: " << duration << "Sekunden \n";
			//Messen der Zeit f�r AnzahlDerTests inserts eines strings mit 30 L�nge:
			std::string seed2 = "1234567890qwertzuioplkjhgfdsay";
			std::string* keys2 = new std::string[AnzahlDerTests];
			for (int y = 0; y < AnzahlDerTests; y++) {
				for (int i = 0; i < 30; ++i) {
					seed2[i] = alphanum[rand() % (sizeof(alphanum) - 1)];
				}
				seed2[30] = 0;
				keys2[y] = seed2;
			}
			start4 = std::clock();
			for (int i = 0; i < AnzahlDerTests; i++) {
				Add(Dummy, keys2[i]);
				if (i % 3000 == 0) {
					std::cout << "30 Laenge insert Nr. "<< i <<": " << (std::clock() - start4) / (double)CLOCKS_PER_SEC << "Sekunden \n";
				}
			}
			duration = (std::clock() - start4) / (double)CLOCKS_PER_SEC;
			std::cout << "30 Laenge insert: " << duration << "Sekunden \n";
			start4 = std::clock();
			for (int i = 0; i < AnzahlDerTests; i++) {
				try{
					Remove(keys2[i]);
					if (i % 3000 == 0) {
						std::cout << "30 Laenge delete Nr. " << i << ": " << (std::clock() - start4) / (double)CLOCKS_PER_SEC << "Sekunden \n";
					}
				}
				catch (std::exception) {
					//nothing
				}
			}
			duration = (std::clock() - start4) / (double)CLOCKS_PER_SEC;
			std::cout << "30 Laenge delete: " << duration << "Sekunden \n";
		}
		//*/

		//Constructor der einen Hashtable mit einer bestimmten Gr��e anlegt
		Hashtable(int size) {

			std::cout << "Constructing Hashtable" << std::endl;

			TableSize = size;
			DataCount = 0;

			Key = new std::string[size]; //Reserviere den Platz f�r die keys
			TimesJumped = new int[size];//Reserviere den Platz
			StepstoneCount = new int[size];//Reserviere den Platz
			Data = new Type[size]; //Reserviere den Platz f�r die Daten

			for (int i = 0; i < size; i++) {
				Key[i] = ""; //Initialisiere die Keys mit einem leeren String
			}
			for (int i = 0; i < size; i++) {
				TimesJumped[i] = 0; //Initialisiere die Jumps mit 0
			}
			for (int i = 0; i < size; i++) {
				StepstoneCount[i] = 0; //Initialisiere die Stepstones mit 0
			}
		};

		//Copy Constructor:
		Hashtable(const Hashtable& other) {

			std::cout << "Copy Constructing Hashtable" << std::endl;

			//Diese Werte kopieren
			TableSize = other.TableSize;
			DataCount = other.DataCount;

			Key = new std::string[TableSize]; //Reserviere den Platz f�r die neuen keys
			TimesJumped = new int[size]; //Reserviere den Platz
			StepstoneCount = new int[size];//Reserviere den Platz
			Data = new Type[TableSize]; //Reserviere den Platz f�r die neuen Daten

			for (int i = 0; i < TableSize; i++) {
				TimesJumped[i] = other.TimesJumped[i]; //Kopiere die Jumps vom anderen Hashtable
			}
			for (int i = 0; i < TableSize; i++) {
				StepstoneCount[i] = other.StepstoneCount[i]; //Kopiere die Counts vom anderen Hashtable
			}
			for (int i = 0; i < TableSize; i++) {
				Key[i] = other.Key[i]; //Kopiere die Keys vom anderen Hashtable
			}
			for (int i = 0; i < TableSize; i++) {
				Data[i] = other.Data[i]; //Kopiere die Daten vom anderen Hashtable
			}
		}

		//Destructor
		virtual ~Hashtable<Type>() {

			std::cout << "Destructing Hashtable" << std::endl;

			delete[] Key;
			delete[] TimesJumped;
			delete[] StepstoneCount;
			delete[] Data;
		};

		//Hinzuf�gen von neuen Eintr�gen in die Hashtabelle. Gibt true bei Erfolg und false bei Misserfolg zur�ck
		bool Add(Type &newData, std::string key) {
			bool returnvalue = true;
			if (Fullness() == 1) { //Gib false zur�ck, wenn Tabelle schon voll
				returnvalue = false;
			}

			int j = 0; //counter (darf nicht gr��er TableSize werden)

			//Nutze die Hashfunktion um die Position des Eintrags zu bestimmen
			int Pos = hash(key) % TableSize; //Originalposition
			int temp = Pos; //verschobene Position bei Data-Hit
			//Versuche so lange einzuf�gen bis es gelingt:
			do //Maximale Anzahl der Versuche = Gr��e der Hashtabelle
			{
				//Versuche die Daten einzuf�gen
				if (Key[temp] == "") { //Wenn das Array an der Stelle leer ist
					Key[temp] = key;
					Data[temp] = newData; //F�ge Daten ein
					TimesJumped[temp] = j; //Speichere die Anzahl der Spr�nge.
					DataCount++;
					//std::cout << key << " = " << temp << ", J = " << j << std::endl;
					break; //Fertig :D
				}
				else { //Wenn Stelle schon besetzt war:
					if (Key[temp] == key) {
						//Fehlgeschlagene Versuche r�ckg�ngig machen !!!
						int deltemp = 0;
						for (int i = 0; i < j; i++) {
							deltemp = QuadraticProbing(Pos, i);
							StepstoneCount[deltemp]--;
						}
						returnvalue = false;
					}
					else {
						//std::cout << temp << "-> ";
						j++; //Anzahl der gebrauchten Versuche erh�hen
						StepstoneCount[temp]++; //Speichere an der Position des mislungenen Einf�gens, dass die Position zum suchen relevant bleibt
												//	Errechne n�chsten Index (nach der quadratischen Probing Methode, in der sich das Vorzeichen jedes Mal �ndert)
						temp = QuadraticProbing(Pos, j);//Siehe https://en.wikipedia.org/wiki/Quadratic_probing#Alternating_sign
					}
				}
			} while (j < TableSize && returnvalue);
			
			//Wenn nun j > TableSize+1 ist, ist die Tabelle schon voll, da wir jede m�gliche Position versucht haben
			if (j >= TableSize) {
				//Fehlgeschlagene Versuche r�ckg�ngig machen !!!
				int deltemp = 0;
				for (int i = 0; i < TableSize; i++) {
					deltemp = QuadraticProbing(Pos, i);
					StepstoneCount[deltemp]--;
				}
				returnvalue = false;
			}
			return returnvalue;
		};

		//Suche in der Hashtabelle nach dem key, wenn gefunden gib den Datensatz zur�ck :D
		Type& Suche(std::string key)
		{
			int index = IndexOf(key); //Can be -1
			if (index < 0) { //wenn -1 dann ist etwas schiefgelaufen :(
				index = 0;
				throw std::overflow_error("Eintrag nicht gefunden :C");
			}
			return Data[index];//return the right one :D
		};

		//Entfernen von Daten mit bestimmten key aus der Hashtabelle, falls vorhanden
		Type& Remove(std::string key) {
			int x = IndexOf(key); //Hol dir die Position falls vorhanden
			if (x < 0) { //wenn -1 dann ist etwas schiefgelaufen :(
				x = 0;
				throw std::overflow_error("Eintrag nicht gefunden :C");
			}
			//Zur�cksetzen der Stepstonecounts die das Objekt beim Einf�gen hinterlassen hat
			if (TimesJumped[x] > 0) {
				int originalindex = hash(key);
				int deltemp = 0;
				for (int i = 0; i < TimesJumped[x]; i++) {
					deltemp = QuadraticProbing(originalindex, i);
					//std::cout << "Von " << StepstoneCount[deltemp];
					if (StepstoneCount[deltemp] > 0) {
						StepstoneCount[deltemp]--;
					}
					//std::cout << " auf " << StepstoneCount[deltemp] << " count: " << i << std::endl;
				}
			}
			TimesJumped[x] = 0; //reset this field
			Key[x] = ""; //Remove Key
			DataCount--; //Nun ist ein Datensatz weniger vorhanden :D
			return Data[x]; //Den Datensatz als Referenz zur�ckgeben, damit er dann evtl wo anders gel�scht werden kann.
		};

		//Gibt die Gr��e des Hashtables zur�ck
		int Size() {
			return TableSize;
		}

		//Gibt den Bef�llungsgrad als Faktor (0-1) zur�ck.
		double Fullness() {
			double befuellungsgrad = 0;
			befuellungsgrad = ((double)DataCount/(double)TableSize);
			return befuellungsgrad;
		}

	private:
		Type* Data;
		std::string* Key;
		int TableSize;
		int DataCount;
		int* TimesJumped; //Gibt an wie oft ein Eintrag gesprungen ist bevor er an seinen endg�ltigen Speicherplatz gelangt ist.
		int* StepstoneCount; //Gibt an wie oft andere Eintr�ge wegen diesem Eintrag nicht an der position gespeichert werden konnten. 

		//hashed den Key und erzeugt eine "pseudozuf�llige Zahl"
		int hash(std::string key) {
			unsigned long hash = 5381;
			int i=0;
			int c;
			while (c = key[i]) {
				i++;
				hash = ((hash << 5) + hash) + c; /* hash * 33 + c */
			}
			int hashint = hash & INT_MAX;
			return hashint;
		}

		//Sucht den Index eines Eintrags
		int IndexOf(std::string key) {

			int j = 0; //counter (darf nicht gr��er TableSize werden)
			//Nutze die Hashfunktion um die Soll-Position des Eintrags zu bestimmen
			int Pos = hash(key) % TableSize; //Originalposition
			int temp = Pos; //verschobene Position bei Nicht-Fund
			
			//Suche so lange bis es gelingt:
			do {
				//Versuche den Eintrag zu finden:
				 if(Key[temp] == key){ //Wenn die Datens�tze �bereinstimmen
					//std::cout << key << " = " << temp << std::endl;
					return temp; //Datensatz gefunden :D
				}
				else{ //Wenn die Datens�tze nicht �bereinstimmen, aber es m�glicherweise dahinter stehen k�nnte:
					if (StepstoneCount[temp] > 0) {
						//Nicht gefunden, aber weitermachen
						j++; //Anzahl der gebrauchten Versuche erh�hen
						//N�chste Position errechnen
						temp = QuadraticProbing(Pos, j); // -> ((j % 2) == 1) ? ((Pos + (j*j)) % TableSize) : ((Pos - (j*j)) % TableSize); //Siehe https://en.wikipedia.org/wiki/Quadratic_probing#Alternating_sign
					}
					else {
						//Bisher keine �bereinstimmung entdeckt :/
						//throw std::overflow_error("Eintrag nicht gefunden :C");
						//std::cout << key << " = " << -1 << std::endl;
						return -1;
						//break; //Fertig, da kein Datensatz hinter diesem wartet.
					}
				}
				
			} while (j <= TableSize); //Maximale Anzahl der Versuche = Gr��e der Hashtabelle

			//Wenn nun j >= TableSize ist, haben wir unsere Suche erfolglos beendet, da wir jede m�gliche Position versucht haben
			if (j > TableSize+1) {
				//std::cout << key << " = overflow " << std::endl;
				return -1;
				//throw std::overflow_error("Eintrag nicht gefunden :C");
			}
			
			

			return (int)temp;
		}

		//Gibt die n�chste Arrayposition zur�ck Pos=Originalposition, Count = Anzahl des Einf�ge/Ausleseversuchs.
		int QuadraticProbing(int Pos, int Count) {
			int j = ceil((double)Count / (double)2);//macht aus 1 2 3 4 ... -> 1 1 2 2 ... weil wir ja +1 -1 +4 -4 +9 -9 ... wollen
			int newPos;

			if (Count % 2 == 1) {//Vorzeichen !!!
				newPos = ((Pos + (j*j)) % TableSize);
			}
			else {
				if(Pos < (j*j)){
					newPos = (Pos - (j*j)) % TableSize + TableSize;
				}
				else {
					newPos = ((Pos - (j*j)) % TableSize);
				}
			}
			return newPos;
		}

};

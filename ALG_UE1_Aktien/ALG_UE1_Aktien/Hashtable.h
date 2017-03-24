#pragma once

#include <string>
#include <stdexcept>
#include <math.h>

#include <iostream> //später weg

template <class Type> class Hashtable
{
	public:
		//Constructor der einen Hashtable mit einer bestimmten Größe anlegt
		Hashtable(int size) {

			std::cout << "Constructing Hashtable" << std::endl;

			TableSize = size;
			DataCount = 0;

			Key = new std::string[size]; //Reserviere den Platz für die keys
			TimesJumped = new int[size];//Reserviere den Platz
			StepstoneCount = new int[size];//Reserviere den Platz
			Data = new Type[size]; //Reserviere den Platz für die Daten

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

			Key = new std::string[TableSize]; //Reserviere den Platz für die neuen keys
			TimesJumped = new int[size]; //Reserviere den Platz
			StepstoneCount = new int[size];//Reserviere den Platz
			Data = new Type[TableSize]; //Reserviere den Platz für die neuen Daten

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

		//Hinzufügen von neuen Einträgen in die Hashtabelle. Gibt true bei Erfolg und false bei Misserfolg zurück
		bool Add(Type &newData, std::string key) {
			if (1 - Fullness() < 0.001) { //Gib false zurück, wenn Tabelle schon voll
				return false;
			}

			int j = 0; //counter (darf nicht größer TableSize werden)

			//Nutze die Hashfunktion um die Position des Eintrags zu bestimmen
			unsigned long Pos = hash(key) % TableSize; //Originalposition
			unsigned long temp = Pos; //verschobene Position bei Data-Hit
			//Versuche so lange einzufügen bis es gelingt:
			do{
				//Versuche die Daten einzufügen
				if (Key[temp] == "") { //Wenn das Array an der Stelle leer ist
					Key[temp] = key;
					Data[temp] = newData; //Füge Daten ein
					TimesJumped[temp] = j; //Speichere die Anzahl der Sprünge.
					DataCount++;
					break; //Fertig :D
				}
				else { //Wenn Stelle schon besetzt war:
					if (Key[temp] == key) {
						//Fehlgeschlagene Versuche rückgängig machen !!!
						for (int i = 0; i < j; i++) {
							unsigned long deltemp = QuadraticProbing(Pos, i); //((i % 2) == 1) ? ((Pos + (i*i)) % TableSize) : ((Pos - (i*i)) % TableSize);
							StepstoneCount[deltemp]--;
						}
						return false;
					}
					j++; //Anzahl der gebrauchten Versuche erhöhen
					StepstoneCount[temp]++; //Speichere an der Position des mislungenen Einfügens, dass die Position zum suchen relevant bleibt
					//	Errechne nächsten Index (nach der quadratischen Probing Methode, in der sich das Vorzeichen jedes Mal ändert)
					temp = QuadraticProbing(Pos, j);//((j % 2) == 1) ? ((Pos + (j*j)) % TableSize) : ((Pos - (j*j)) % TableSize); //Siehe https://en.wikipedia.org/wiki/Quadratic_probing#Alternating_sign
				}
			}
			while (j < TableSize); //Maximale Anzahl der Versuche = Größe der Hashtabelle
			
			//Wenn nun j >= TableSize ist, ist die Tabelle schon voll, da wir jede mögliche Position versucht haben
			if (j >= TableSize) {
				//Fehlgeschlagene Versuche rückgängig machen !!!
				for (int i = 0; i < TableSize; i++) {
					unsigned long deltemp = ((i % 2) == 1) ? ((Pos + (i*i)) % TableSize) : ((Pos - (i*i)) % TableSize);
					StepstoneCount[deltemp]--;
				}
				return false;
			}

			return true;

		};

		//Suche in der Hashtabelle nach dem key, wenn gefunden gib den Datensatz zurück :D
		Type& Suche(std::string key)
		{
			int index = IndexOf(key); //Always the right one, if not search would have thrown exception

			return Data[index];//return the right one :D
		};

		//Entfernen von Daten mit bestimmten key aus der Hashtabelle, falls vorhanden
		bool Remove(std::string key) {
			int x = IndexOf(key); //Hol dir die Position falls vorhanden

			//Zurücksetzen der Stepstonecounts die das Objekt beim Einfügen hinterlassen hat
			for (int i = 1; i <= TimesJumped[x]; i++) {
				unsigned long deltemp = QuadraticProbing(Pos, i); //((i % 2) == 1) ? ((Pos + (i*i)) % TableSize) : ((Pos - (i*i)) % TableSize);
				StepstoneCount[deltemp]--;
			}
			TimesJumped[x] = 0; //reset this field
			delete Data[x]; //Delete Data
			Key[x] = ""; //Remove Key
			return true;
		};

		//Gibt die Größe des Hashtables zurück
		int Size() {
			return TableSize;
		}

		//Gibt den Befüllungsgrad als Faktor (0-1) zurück.
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
		int* TimesJumped; //Gibt an wie oft ein Eintrag gesprungen ist bevor er an seinen endgültigen Speicherplatz gelangt ist.
		int* StepstoneCount; //Gibt an wie oft andere Einträge wegen diesem Eintrag nicht an der position gespeichert werden konnten. 

		//hashed den Key und erzeugt eine "pseudozufällige Zahl"
		unsigned long hash(std::string key) {
			unsigned long hash = 5381;
			int i=0;
			int c;
			while (c = key[i]) {
				i++;
				hash = ((hash << 5) + hash) + c; /* hash * 33 + c */
			}

			return hash;
		}

		//Sucht den Index eines Eintrags
		int IndexOf(std::string key) {

			int j = 0; //counter (darf nicht größer TableSize werden)
			//Nutze die Hashfunktion um die Soll-Position des Eintrags zu bestimmen
			unsigned long Pos = hash(key) % TableSize; //Originalposition
			unsigned long temp = Pos; //verschobene Position bei Nicht-Fund
			
			//Suche so lange bis es gelingt:
			do {
				//Versuche den Eintrag zu finden:
				 if(Key[temp] == key){ //Wenn die Datensätze übereinstimmen
					return temp; //Datensatz gefunden :D
				}
				else{ //Wenn die Datensätze nicht übereinstimmen, aber es möglicherweise dahinter stehen könnte:
					if (StepstoneCount[temp] != 0) {
						//Nicht gefunden, aber weitermachen
						j++; //Anzahl der gebrauchten Versuche erhöhen
						//Nächste Position errechnen
						temp = QuadraticProbing(Pos, j); // -> ((j % 2) == 1) ? ((Pos + (j*j)) % TableSize) : ((Pos - (j*j)) % TableSize); //Siehe https://en.wikipedia.org/wiki/Quadratic_probing#Alternating_sign
					}
					else {
						//Bisher keine Übereinstimmung entdeckt :/
						throw std::overflow_error("Eintrag nicht gefunden :C");
						break; //Fertig, da kein Datensatz hinter diesem wartet.
					}
				}
				
			} while (j < TableSize); //Maximale Anzahl der Versuche = Größe der Hashtabelle

			//Wenn nun j >= TableSize ist, haben wir unsere Suche erfolglos beendet, da wir jede mögliche Position versucht haben
			if (j >= TableSize) {
				throw std::overflow_error("Eintrag nicht gefunden :C");
			}

			return (int)temp;
		}

		//Gibt die nächste Arrayposition zurück Pos=Originalposition, Count = Anzahl des Einfüge/Ausleseversuchs.
		unsigned long QuadraticProbing(unsigned long Pos, int Count) {
			int j = ceil((double)Count / 2); //macht aus 1 2 3 4 ... -> 1 1 2 2 ... weil wir ja +1 -1 +4 -4 +9 -9 ... wollen
			return ((Count % 2) == 1) ? ((Pos + (j*j)) % TableSize) : (((Pos - (j*j)) % TableSize) < 0) ? ((Pos - (j*j)) % TableSize) + TableSize : ((Pos - (j*j)) % TableSize); //Ändert das Vorzeichen jedes Mal und schaut drauf, dass negative ergebnisse korrekt Modulo gerechnet werden.
		}
};

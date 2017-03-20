#pragma once

#include <string>
#include <stdexcept>

template <class Type> class Hashtable
{
	public:
		//Constructor der einen Hashtable mit einer bestimmten Gr��e anlegt
		Hashtable(int size) {
			TableSize = size;


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
			//Diese Werte kopieren
			TableSize = other.TableSize;

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
			delete[] Key;
			delete[] TimesJumped;
			delete[] StepstoneCount;
			delete[] Data;
		};

		//Hinzuf�gen von neuen Eintr�gen in die Hashtabelle. 
		void Add(Type &newData, std::string key) {

			int j = 0; //counter (darf nicht gr��er TableSize werden)

			//Nutze die Hashfunktion um die Position des Eintrags zu bestimmen
			unsigned long Pos = hash(key) % TableSize; //Originalposition
			unsigned long temp = Pos; //verschobene Position bei Data-Hit
			//Versuche so lange einzuf�gen bis es gelingt:
			do{
				//Versuche die Daten einzuf�gen
				if (Key[temp] == "") { //Wenn das Array an der Stelle leer ist
					Key[temp] = key;
					Data[temp] = newData; //F�ge Daten ein
					TimesJumped[temp] = j; //Speichere die Anzahl der Spr�nge.
					break; //Fertig :D
				}
				else { //Wenn Stelle schon besetzt war:
					if (Key[temp] == key) {
						//Fehlgeschlagene Versuche r�ckg�ngig machen !!!
						for (int i = 0; i < j; i++) {
							unsigned long deltemp = ((i % 2) == 1) ? ((Pos + (i*i)) % TableSize) : ((Pos - (i*i)) % TableSize);
							StepstoneCount[deltemp]--;
						}
						throw std::overflow_error("Eintrag bereits vorhanden :C");
					}
					j++; //Anzahl der gebrauchten Versuche erh�hen
					StepstoneCount[temp]++; //Speichere an der Position des mislungenen Einf�gens, dass die Position zum suchen relevant bleibt
					//	Errechne n�chsten Index (nach der quadratischen Probing Methode, in der sich das Vorzeichen jedes Mal �ndert)
					temp = ((j % 2) == 1) ? ((Pos + (j*j)) % TableSize) : ((Pos - (j*j)) % TableSize); //Siehe https://en.wikipedia.org/wiki/Quadratic_probing#Alternating_sign
				}
			}
			while (j < TableSize); //Maximale Anzahl der Versuche = Gr��e der Hashtabelle
			
			//Wenn nun j >= TableSize ist, ist die Tabelle schon voll, da wir jede m�gliche Position versucht haben
			if (j >= TableSize) {
				//Fehlgeschlagene Versuche r�ckg�ngig machen !!!
				for (int i = 0; i < TableSize; i++) {
					unsigned long deltemp = ((i % 2) == 1) ? ((Pos + (i*i)) % TableSize) : ((Pos - (i*i)) % TableSize);
					StepstoneCount[deltemp]--;
				}

				throw std::overflow_error("Hashtable voll :C");
			}
		};

		//Suche in der Hashtabelle nach dem key, wenn gefunden gib den Datensatz zur�ck :D
		Type Suche(std::string key)
		{
			int index = IndexOf(key);

			return Data[index];//return the right one :D
		};

		//Entfernen von Daten mit bestimmten key aus der Hashtabelle, falls vorhanden
		void Remove(std::string key) {

		};

		int Size() {
			return TableSize;
		}

	private:
		Type* Data;
		std::string* Key;
		int TableSize;
		int* TimesJumped; //Gibt an wie oft ein Eintrag gesprungen ist bevor er an seinen endg�ltigen Speicherplatz gelangt ist.
		int* StepstoneCount; //Gibt an wie oft andere Eintr�ge wegen diesem Eintrag nicht an der position gespeichert werden konnten. 

		//hashed den Key und erzeugt eine "pseudozuf�llige Zahl"
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

			int j = 0; //counter (darf nicht gr��er TableSize werden)
			//Nutze die Hashfunktion um die Soll-Position des Eintrags zu bestimmen
			unsigned long Pos = hash(key) % TableSize; //Originalposition
			unsigned long temp = Pos; //verschobene Position bei Nicht-Fund
			
			//Suche so lange bis es gelingt:
			do {
				//Versuche den Eintrag zu finden:
				 if(Key[temp] == key){ //Wenn die Datens�tze �bereinstimmen
					return temp; //Datensatz gefunden :D
				}
				else{ //Wenn die Datens�tze nicht �bereinstimmen, aber es m�glicherweise dahinter stehen k�nnte:
					if (StepstoneCount[temp] != 0) {
						//Nicht gefunden, aber weitermachen
						j++; //Anzahl der gebrauchten Versuche erh�hen
						//N�chste Position errechnen
						temp = ((j % 2) == 1) ? ((Pos + (j*j)) % TableSize) : ((Pos - (j*j)) % TableSize); //Siehe https://en.wikipedia.org/wiki/Quadratic_probing#Alternating_sign
					}
					else {
						//Bisher keine �bereinstimmung entdeckt :/
						throw std::overflow_error("Eintrag nicht gefunden :C");
						break; //Fertig, da kein Datensatz hinter diesem wartet.
					}
				}
				
			} while (j < TableSize); //Maximale Anzahl der Versuche = Gr��e der Hashtabelle

			//Wenn nun j >= TableSize ist, haben wir unsere Suche erfolglos beendet, da wir jede m�gliche Position versucht haben
			if (j >= TableSize) {
				throw std::overflow_error("Eintrag nicht gefunden :C");
			}

			return temp;
		}
};

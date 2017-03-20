#pragma once

#include <string>
#include <stdexcept>

template <class Type> class Hashtable
{
	public:
		//Constructor der einen Hashtable mit einer bestimmten Größe anlegt
		Hashtable(int size) {
			TableSize = size;


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
			//Diese Werte kopieren
			TableSize = other.TableSize;

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
			delete[] Key;
			delete[] TimesJumped;
			delete[] StepstoneCount;
			delete[] Data;
		};

		//Test:
		int FindHighestStepstonecount() {
			int temp = 0;
			for (int i = 0; i < TableSize; i++) {
				if (StepstoneCount[i] > temp) {
					temp = StepstoneCount[i];
				}
			}
			return temp;
		}

		//Test:
		int FindHighestTimesJumped() {
			int temp = 0;
			for (int i = 0; i < TableSize; i++) {
				if (TimesJumped[i] > temp) {
					temp = TimesJumped[i];
				}
			}
			return temp;
		}


		//Hinzufügen von neuen Einträgen in die Hashtabelle. 
		void Add(Type &newData, std::string key) {

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
					break; //Fertig :D
				}
				else { //Wenn Stelle schon besetzt war:
					j++; //Anzahl der gebrauchten Versuche erhöhen
					StepstoneCount[temp]++; //Speichere an der Position des mislungenen Einfügens, dass die Position zum suchen relevant bleibt
					//	Errechne nächsten Index (nach der quadratischen Probing Methode, in der sich das Vorzeichen jedes Mal ändert)
					temp = ((j % 2) == 1) ? ((Pos + (j*j)) % TableSize) : ((Pos - (j*j)) % TableSize); //Siehe https://en.wikipedia.org/wiki/Quadratic_probing#Alternating_sign
				}
			}
			while (j < TableSize); //Maximale Anzahl der Versuche = Größe der Hashtabelle
			
			//Wenn nun j >= TableSize ist, ist die Tabelle schon voll, da wir jede mögliche Position versucht haben
			if (j >= TableSize) {
				throw std::overflow_error("Hashtable voll :C");
			}
		};

		//Suche in der Hashtabelle nach dem key, wenn gefunden gib den Datensatz zurück :D
		template <class Type> Type Search(std::string key)
		{
			
			return Data[0];//return the right one :D
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
};

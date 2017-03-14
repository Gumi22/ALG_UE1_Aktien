#pragma once

#include <string>
#include <stdexcept>

template <class Type> class Hashtable
{
	public:
		//Constructor der einen Hashtable mit einer bestimmten Gr��e anlegt
		Hashtable(int size) {
			TableSize = size;

			Data = new Type[size]; //Reserve the space needed

			for (int i = 0; i < size; i++) {
				Data[i] = NULL; //initialize every Entry as Null
			}
		};
		//Destructor
		virtual ~Hashtable<Type>() {};

		//Hinzuf�gen von neuen Eintr�gen in die Hashtabelle. 
		void Add(Type &newData, std::string key) {

			int j = 0; //counter (darf nicht gr��er TableSize werden)

			//Nutze die Hashfunktion um die Position des Eintrags zu bestimmen
			unsigned long Pos = hash(key) % TableSize; //Originalposition
			unsigned long temp = Pos; //verschobene Position bei Data-Hit
			//Versuche so lange einzuf�gen bis es gelingt:
			do{
				//Versuche die Daten einzuf�gen
				if (Data[temp] == NULL) { //Wenn das Array an der Stelle leer ist
					Data[temp] = newData; //F�ge Daten ein
					throw std::overflow_error( std::to_string(newData) );
					break; //Fertig :D
				}
				else { //Wenn Stelle schon besetzt war:
					j++; //Anzahl der gebrauchten Versuche erh�hen
					//	Errechne n�chsten Index (nach der quadratischen Probing Methode, in der sich das Vorzeichen jedes Mal �ndert)
					temp = ((j % 2) == 1) ? ((Pos + (j*j)) % TableSize) : ((Pos - (j*j)) % TableSize); //Siehe https://en.wikipedia.org/wiki/Quadratic_probing#Alternating_sign
				}
			}
			while (j < TableSize); //Maximale Anzahl der Versuche = Gr��e der Hashtabelle
			
			//Wenn nun j >= TableSize ist, ist die Tabelle schon voll, da wir jede m�gliche Position versucht haben
			if (j >= TableSize) {
				throw std::overflow_error("Hashtable voll :C");
			}
		};

		//Suche in der Hashtabelle nach dem key, wenn gefunden gib den Datensatz zur�ck :D
		template <class Type> Type Search(std::string key)
		{
			
			return Data[0];//return the right one :D
		};

		//Entfernen von Daten mit bestimmten key aus der Hashtabelle, falls vorhanden
		void Remove(std::string key) {

		};


	private:
		Type* Data;
		int TableSize;

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
};

#include "stdafx.h"
#include "Hashtable.h"
#include <string>

template <class Type> Hashtable<Type>::Hashtable() {
	//Standard Constructor
}

template <class Type> Hashtable<Type>::Hashtable(int size) {
	//Constructor with size
	_size = size;
	Data = new Type[size];
}

template <class Type> Hashtable<Type>::~Hashtable()
{
	//Add code to destroy this Hashtable
}

template <class Type> void Hashtable<Type>::Add(Type &Data, std::string key) {

}

// No need to call this TemporaryFunction() function,
// it's just to avoid link error.
void TemporaryFunction()
{
	Hashtable<int> TempObj;
}
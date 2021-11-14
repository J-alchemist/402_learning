#include "animal.h"

template <class T>
Animal<T>::Animal()
{
    //ctor
}

template <class T>
Animal<T>::Animal(T name1, T name2)
{
    this->ani1 = name1;
    this->ani2 = name2;
}

template <class T>
Animal<T>::~Animal()
{
    //dtor
}

template <class T>
T Animal<T>::getAnimala()
{
    return this->ani1;
}

template <class T>
T Animal<T>::getAnimalb()
{
    return this->ani2;
}


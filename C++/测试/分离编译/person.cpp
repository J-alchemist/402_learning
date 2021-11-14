#include "person.h"

Person::Person()
{

}
Person::Person(int height, int age)
{
    this->height = height;
    this->age = age;
}
Person::~Person()
{

}

int Person::getheight()
{
    return this->height;
}

int Person::getage()
{
    return this->age;
}

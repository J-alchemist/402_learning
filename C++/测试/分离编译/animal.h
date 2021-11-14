#ifndef ANIMAL_H
#define ANIMAL_H

//Ä£°åÀà
template <class T>
class Animal
{
    public:
        Animal();
        Animal(T, T);
        virtual ~Animal();

        T getAnimala();
        T getAnimalb();

    protected:

    private:

        T ani1;
        T ani2;
};

#endif // ANIMAL_H

#ifndef PERSON_H
#define PERSON_H

//∆’Õ®¿‡
class Person
{
    public:
        Person();
        Person(int, int);
        virtual ~Person();

        int getheight();
        int getage();

    protected:

    private:
        int height;
        int age;
};

#endif // PERSON_H

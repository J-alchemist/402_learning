#include <iostream>
#include <string>
#include "linklist.cpp"

using namespace std;

typedef struct Teacher
{
	int age;

}Teacher;

int main()
{
    Teacher t1,t2,t3,tx;
    t1.age = 1;
    t2.age = 2;
    t3.age = 3;

    LinkList<Teacher> list;

    //²åÈë
    list.insert_val(t1, 0);
    list.insert_val(t2, 0);
    list.insert_val(t3, 0);

    //±éÀú
    for(int i = 0; i< list.get_len(); i++)
    {
        list.get_val(tx, i);
        cout << tx.age << " ";
    }
    cout << endl;
    //É¾³ı
    while( list.get_len()>0 )
    {
        list.delete_val(tx, 0);
        cout << tx.age << " ";
    }
    cout << endl;

    return 0;
}

#include <iostream>
//#include "SeqList.h"
#include "SeqList.cpp"

using namespace std;

typedef struct _Teacher
{
    int sex;
    int age;
}Teacher;

int main()
{
    Teacher t1,t2,t3,tmp;
    t1.age = 1;
    t2.age = 2;
    t3.age = 3;
//����

    SeqList<Teacher> list(10);//��������SeqList����list
    list.insertVal(t1, 0);
    list.insertVal(t2, 0);
    list.insertVal(t3, 0);

//����
    for(int i=0; i<list.getLen(); i++)
    {
        list.getVal(tmp, i);
        cout << tmp.age << " ";
    }
    cout << endl;
//ɾ��
    while(list.getLen()>0)
    {
        list.delVal(tmp, list.getLen()-1);
        cout << tmp.age << " ";
    }
    cout << endl;
    return 0;
}

#include <iostream>
#include <string>
#include "person.h"
#include "animal.h"
#include "animal.cpp"

using namespace std;
/*
ģ����\ģ�庯����֧�ַ�����룡����
ģ����\ģ�庯��ֻ���ڵ��õ�ʱ��Ż�ʵ����
ģ������뷽ʽ��1������.cpp
                2������.hpp�ļ��������Ͷ������ͬһ���ļ���
*/
int main(int argc, char** argv)
{

//-----
    Person p1(177, 22);
    cout << "P1 Data: " << p1.getage() << " " \
                           << p1.getheight() << endl;
//-----
    Animal<string> ani("monkey", "tiger");
    cout << "Animal name: " << ani.getAnimala() << " " \
                            << ani.getAnimalb() << endl;

//------







    return 0;

}



#include <iostream>
#include <string>
#include "person.h"
#include "animal.h"
#include "animal.cpp"

using namespace std;
/*
模板类\模板函数不支持分离编译！！！
模板类\模板函数只有在调用的时候才会实例化
模板类编译方式：1、包含.cpp
                2、创建.hpp文件，声明和定义放在同一个文件中
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



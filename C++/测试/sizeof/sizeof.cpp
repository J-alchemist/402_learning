#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

using namespace std;

//sizeofͳ���ַ�����ĳ��ȡ������ַ�����
int main( )
{
    cout << "---1------------------" <<   endl;
    char* c1 = "abc";
    cout <<      sizeof(c1)    <<endl;  //ָ���С   sizeof(char*)
    cout <<      sizeof(char* )    <<endl;  //�����ַ��С
    cout <<      sizeof(*c1)    <<endl; //��һ���ַ���С
    cout <<     strlen(c1)  <<endl;

    cout << "---2------------------" <<   endl;

    char c2[] = "abc";
    cout <<      sizeof(c2)    <<endl;
    cout <<      sizeof(*c2)    <<endl;     //��һ���ַ���С
    cout <<     strlen(c2)  <<endl;

    cout << "---3------------------" <<   endl;

    char c3[6] = "abc";
    cout <<      sizeof(c3)    <<endl;
    cout <<     strlen(c3)  <<endl;




    return 0;


}


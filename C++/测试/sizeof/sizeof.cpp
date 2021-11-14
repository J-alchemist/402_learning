#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

using namespace std;

//sizeof统计字符数组的长度。。。字符数组
int main( )
{
    cout << "---1------------------" <<   endl;
    char* c1 = "abc";
    cout <<      sizeof(c1)    <<endl;  //指针大小   sizeof(char*)
    cout <<      sizeof(char* )    <<endl;  //输出地址大小
    cout <<      sizeof(*c1)    <<endl; //第一个字符大小
    cout <<     strlen(c1)  <<endl;

    cout << "---2------------------" <<   endl;

    char c2[] = "abc";
    cout <<      sizeof(c2)    <<endl;
    cout <<      sizeof(*c2)    <<endl;     //第一个字符大小
    cout <<     strlen(c2)  <<endl;

    cout << "---3------------------" <<   endl;

    char c3[6] = "abc";
    cout <<      sizeof(c3)    <<endl;
    cout <<     strlen(c3)  <<endl;




    return 0;


}


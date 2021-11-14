#include <stdio.h>
#include <stdlib.h>
union myoinfo {
	int age;
	int height;
	int heavy;
	
};



int main(int argc, char *argv[])
{
	int a = time(NULL); 
	union myoinfo gj;
	
	gj.age  = 23;
	gj.heavy = 177;
	printf("myinfo.age : %d\n", gj.age);//只会输出最后一个赋值的成员
	
	printf("%d", a);
    return 0;
}


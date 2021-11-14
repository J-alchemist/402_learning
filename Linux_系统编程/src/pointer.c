#include <stdio.h>
#include <stdlib.h>
int main()
{
	printf("%d\n",sizeof(int*));//int*型指针大小

	//错误！
	int* p1 = 1;
	printf("%d\n", p1);//此时1被认为是地址，而地址单元1可能未的分配，导致p是一个野指针，*p无内容导致错误
	//printf("%d\n", *p1);

	int* p = (void* )1;
	printf("%d\n", p);

	//正确！
	int* p2 = (int* )malloc(sizeof(int));//记得free
	*p2 = 1;
	printf("%d\n", *p2);

/*	//错误！
	int* p3 = NULL;
	*p3 = 1;
	//printf("%d\n", p3);//无论打印p还是*p都会出现错误，无地址
	//printf("%d\n", *p3);
*/
	//若要使用NULL，后续也需要关联指针！！
	int a=10;
	int* p4 = NULL;
	p4 = &a;
	printf("%d\n", *p4);
//huozhe
	int* p5 = &a;
	printf("%d\n", *p5);

//常量
	const int b = 10;
	printf("%d\n",b);printf("%d\n",&b);

	printf("%d\n",sizeof(int*));


	return 0;
}

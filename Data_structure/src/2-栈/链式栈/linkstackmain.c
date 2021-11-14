#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "linkstack.h"

int main(int argc, char **argv)
{

	int a[10],  i;

	LinkStack *stack = LinkStack_Create();

	for (i=0; i<10; i++)
	{
		a[i] = i;
		LinkStack_Push(stack, &a[i]);
	}
	printf("top: %d \n",  *((int *)LinkStack_Top(stack)));
	printf("size: %d \n", LinkStack_Size(stack));

	//删除栈中所有元素
	while (LinkStack_Size(stack) > 0)
	{
	    int temp = *((int*)LinkStack_Pop(stack));
		printf("linkstack pop: %d \n",  temp );
	}
	LinkStack_Destroy(stack);

	system("pause");

    return 0;
}

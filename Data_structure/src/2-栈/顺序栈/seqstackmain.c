#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "seqstack.h"


int main()
{

	int a[10], i = 0;
	int *pTmp = NULL;

	SeqStack* stack = SeqStack_Create(10);

	for (i=0; i<10; i++)//ÍùÕ»Ñ¹ÔªËØ
	{
		a[i] = i;
		SeqStack_Push(stack, &a[i]);
	}

	pTmp = (int *)SeqStack_Top(stack);//Õ»¶¥ÔªËØ
	printf("top:%d \n", *pTmp);

	printf("capacity:%d \n", SeqStack_Capacity(stack));

	printf("size:%d \n", SeqStack_Size(stack));

	//ÔªËØ³öÕ»
	while (SeqStack_Size(stack) > 0)
	{
		printf("pop:%d \n", *((int *)SeqStack_Pop(stack)) );//³öÕ»
	}

	SeqStack_Destroy(stack);

	return 0;
}

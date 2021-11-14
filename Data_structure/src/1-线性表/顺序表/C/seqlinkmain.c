#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "seqlist.h"
/*
typedef struct _tag_SeqList
{
	int capacity;
	int length;
	unsigned int **node;
}TSeqList;
*/

int main(int argc, char **argv)
{
/*	int b=10;
	int *a=&b;
	int **p = &a;
	printf("%d\n", *p[0]);
*/

	int i = 0;

	SeqList *list =  SeqList_Create(10);

	int t1=1, t2=2, t3=3;

	//头插
	SeqList_Insert(list, (SeqListNode*)&t1, 0);
	SeqList_Insert(list, (SeqListNode*)&t2, 0);
	SeqList_Insert(list, (SeqListNode*)&t3, 0);

	//遍历
	for (i=0; i<SeqList_Length(list); i++)
	{
		int *tmp = (int *) SeqList_Get(list, i);
		if (tmp != NULL)
		{
			printf("tmp val:%d\n", *tmp);
		}
	}

	//删除
	for (i=0; i<SeqList_Length(list); i++)
	{
		SeqList_Delete(list, 0);
	}
	SeqList_Destroy(list);

	system("pause");
}

#include <stdio.h>
#include <stdlib.h>
#include "DLinkList.h"

struct Value
{
	DLinkListNodePtr node;
	int v;
};

int main(int argc, char *argv[])
{
	int i = 0;

	DLinkList* list = DLinkList_Create();

	struct Value* pv = NULL;
	struct Value v1, v2, v3, v4, v5;

	v1.v = 1;	v2.v = 2;	v3.v = 3;	v4.v = 4;   v5.v = 5;

    //头插法
	DLinkList_Insert(list, (DLinkListNodePtr*)&v1, 0);
	DLinkList_Insert(list, (DLinkListNodePtr*)&v2, 0);
	//尾插法
	DLinkList_Insert(list, (DLinkListNodePtr*)&v3, DLinkList_Length(list));
	DLinkList_Insert(list, (DLinkListNodePtr*)&v4, 1);
	DLinkList_Insert(list, (DLinkListNodePtr*)&v5, DLinkList_Length(list));

	for(i=0; i<DLinkList_Length(list); i++)
	{
		pv = (struct Value*)DLinkList_Get(list, i);

		printf("%d\n", pv->v);
	}

	printf("\n");
/*
    //删除
   	DLinkList_Delete(list, 0);
   	DLinkList_Delete(list, 0);
	DLinkList_Delete(list, 3);


	for(i=0; i<DLinkList_Length(list); i++)
	{
		pv = (struct Value *)DLinkList_Get(list,i);
		printf("%d\n", pv->v);
	}

	printf("\n");
*/
    //游标操作
	DLinkList_ResetSL(list);
	DLinkList_NextSL(list);

	pv = (struct Value *)DLinkList_CurrentSL(list);
	printf("%d\n", pv->v);

	DLinkList_DeleteNode(list, (DLinkListNodePtr *)pv);
	printf("Length: %d\n", DLinkList_Length(list));

	pv = (struct Value *)DLinkList_CurrentSL(list);
	printf("%d\n", pv->v);

	DLinkList_PreSL(list);
	pv = (struct Value *)DLinkList_CurrentSL(list);
	printf("%d\n", pv->v);


	DLinkList_Destroy(list);

	system("pause");

	return 0;
}

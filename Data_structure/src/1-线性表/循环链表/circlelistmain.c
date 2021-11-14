#include <stdio.h>
#include <stdlib.h>
#include "CircleList.h"

typedef struct Value
{
	CircleListNodePtr node;
	int v;
}Value;

int  main()
{
	int i = 0;
	CircleList* list = CircleList_Create();

	Value v1;	v1.v = 1;
	Value v2;	v2.v = 2;
	Value v3;	v3.v = 3;


    //头插法
	CircleList_Insert(list, (CircleListNodePtr *)&v1, 0);
	//尾插法
	CircleList_Insert(list, (CircleListNodePtr *)&v2, CircleList_GetLength(list));
	//普通插入
	CircleList_Insert(list, (CircleListNodePtr *)&v3, 1);

	for(i=0; i< 2*CircleList_GetLength(list); i++)  //循环次数2倍，验证是否真的是循环链表
	{
		Value* pv = (Value *)CircleList_GetData(list, i);
		printf("%d\n", pv->v);
	}
	printf("-------------\n");
/*    //删除元素
	while( CircleList_GetLength(list) > 0 )
	{
		Value* pv = (struct Value*)CircleList_Delete(list, 0);

		printf("%d\n", pv->v);
	}

	printf("-------------\n");*/
	//用游标删除元素
	CircleList_ResetSL(list);//重置游标

	while( CircleList_GetLength(list) > 0 )
	{
		Value* pv = NULL;

		for(i=0; i<2; i++)//移动游标1次
		{
			CircleList_NextSL(list);
		}

		pv = (Value *)CircleList_CurrentSL(list);
		printf("%d\n", pv->v);

		CircleList_DeleteNode(list, (CircleListNodePtr *)pv);
	}

	CircleList_Destroy(list);

	system("pause");

	return 0;

}



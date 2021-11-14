#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "linklist.h"
/*
指针域：被头节点和数据节点所包含
头节点
数据节点
*/
typedef struct Teacher  //数据节点信息
{
	LinkListNodePtr node;  //数据节点的指针域,指针域与节点地址重叠
	int age;               //数据域

}Teacher;

int main(int argc, char *argv[]) {

	Teacher t1,t2,t3;
	int i=0;

	t1.age = 1;
	t2.age = 2;
	t3.age = 3;
/*
	printf("%d\n", &t1);
	printf("%d\n", &(t1.node));

	LinkListNodePtr* p1 = (LinkListNodePtr *)&t1;
	printf("%d\n", p1->next);
	printf("%d\n", t1.node.next);

	printf("\n");*/

	LinkList *list = LinkList_Create();//空链表
	if(list == NULL)
	{
		return -1;
	}

	int ret = LinkList_GetLength(list);
    printf("before linkList lenth: %d\n", ret);

	//插入
	LinkList_Insert(list, (LinkListNodePtr *)&t1, 2);
	LinkList_Insert(list, (LinkListNodePtr *)&t2, 1);
	LinkList_Insert(list, (LinkListNodePtr *)&t3, 0);

	ret = LinkList_GetLength(list);
    printf("add elem later linkList lenth: %d\n", ret);

	//遍历
	for(i = 0; i< LinkList_GetLength(list); i++)
	{
		Teacher *tmp  = (Teacher *)LinkList_GetData(list, i);
		if(tmp == NULL)
		{
			return -1;
		}
		printf("data: %d\n", tmp->age);
	}
	//删除
	while( LinkList_GetLength(list)>0 )
		LinkList_Delete(list, 0);


    system("pause");

	return 0;

}



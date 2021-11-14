#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "linkstack.h"
#include "linklist.h"

LinkStack* LinkStack_Create()
{
	//创建一个栈，通过线性表去模拟
	return LinkList_Create();
}

void LinkStack_Destroy(LinkStack* stack)
{
    LinkStack_Reset(stack);
	LinkList_Destroy(stack);
}

//涉及到栈的元素声明周期的管理
//所有入栈节点都是malloc，所有要free
void LinkStack_Reset(LinkStack* stack)
{
    if(stack == NULL)
    {
        return;
    }
    while(LinkList_GetLength(stack)>0)
    {
        LinkStack_Pop(stack);//进行free
    }

	return ;
}


//向栈中放元素，相当于 向线性表 头插 一个元素
//将栈的业务节点转化为链表的业务节点
int LinkStack_Push(LinkStack* stack, void* item)
{
	int ret = 0;

	LinkStackNode *pTe = (LinkStackNode *)malloc(sizeof(LinkStackNode));//给栈元素分配空间
	if (pTe == NULL)
	{
		return -1;
	}
	pTe->item = item;

	//头插法 ，向线性表中插入元素
	ret = LinkList_Insert(stack, (LinkListNodePtr *)(&pTe->node),0 );
	if (ret != 0)
	{
		free(pTe);
	}

	return ret;

}
//弹出元素，相当于从线性表的头部删除元素
void* LinkStack_Pop(LinkStack* stack)
{
	void *myItem = NULL;
	LinkStackNode *pTmp = NULL;

	pTmp = (LinkStackNode *)LinkList_Delete(stack, 0);
	if (pTmp == NULL)
	{
		return NULL;
	}
	myItem = pTmp->item;

	//注意向线性表中，插入元素的时，打造节点，分配内存；
	//弹出元素时，需要释放节点内存，不要忘记
	if (pTmp != NULL)
	{
		free(pTmp);
	}
	return myItem;

}

void* LinkStack_Top(LinkStack* stack)
{

    LinkStackNode* tmp = (LinkStackNode *)LinkList_GetData(stack, 0);

    if(tmp == NULL )
    {
        return NULL;
    }

	return tmp->item;
}
//求栈的大小相当于求线性表的lenth
int LinkStack_Size(LinkStack* stack)
{
	return LinkList_GetLength(stack);
}

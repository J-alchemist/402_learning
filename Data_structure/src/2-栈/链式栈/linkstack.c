#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "linkstack.h"
#include "linklist.h"

LinkStack* LinkStack_Create()
{
	//����һ��ջ��ͨ�����Ա�ȥģ��
	return LinkList_Create();
}

void LinkStack_Destroy(LinkStack* stack)
{
    LinkStack_Reset(stack);
	LinkList_Destroy(stack);
}

//�漰��ջ��Ԫ���������ڵĹ���
//������ջ�ڵ㶼��malloc������Ҫfree
void LinkStack_Reset(LinkStack* stack)
{
    if(stack == NULL)
    {
        return;
    }
    while(LinkList_GetLength(stack)>0)
    {
        LinkStack_Pop(stack);//����free
    }

	return ;
}


//��ջ�з�Ԫ�أ��൱�� �����Ա� ͷ�� һ��Ԫ��
//��ջ��ҵ��ڵ�ת��Ϊ�����ҵ��ڵ�
int LinkStack_Push(LinkStack* stack, void* item)
{
	int ret = 0;

	LinkStackNode *pTe = (LinkStackNode *)malloc(sizeof(LinkStackNode));//��ջԪ�ط���ռ�
	if (pTe == NULL)
	{
		return -1;
	}
	pTe->item = item;

	//ͷ�巨 �������Ա��в���Ԫ��
	ret = LinkList_Insert(stack, (LinkListNodePtr *)(&pTe->node),0 );
	if (ret != 0)
	{
		free(pTe);
	}

	return ret;

}
//����Ԫ�أ��൱�ڴ����Ա��ͷ��ɾ��Ԫ��
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

	//ע�������Ա��У�����Ԫ�ص�ʱ������ڵ㣬�����ڴ棻
	//����Ԫ��ʱ����Ҫ�ͷŽڵ��ڴ棬��Ҫ����
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
//��ջ�Ĵ�С�൱�������Ա��lenth
int LinkStack_Size(LinkStack* stack)
{
	return LinkList_GetLength(stack);
}

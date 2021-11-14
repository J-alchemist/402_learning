#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "linklist.h"

LinkList* LinkList_Create()//创建空链表
{
	LinkListH *ptr = (LinkListH *)malloc(sizeof(LinkListH));
	if (ptr == NULL)
	{
		return NULL;
	}
	memset(ptr, 0, sizeof(LinkListH));

	ptr->header.next = NULL;
	ptr->length = 0;

	return ptr;
}

void LinkList_Destroy(LinkList* list)
{
	if (list == NULL)
	{
		return ;
	}

	free(list);
	return ;
}

//让链表恢复到初始状态
void LinkList_Reset(LinkList* list)
{

	if (list == NULL)
	{
		return ;
	}

	LinkListH *tmpList = (LinkListH *)list;
	tmpList->length = 0;
	tmpList->header.next = NULL;

	return ;
}

int LinkList_GetLength(LinkList* list)
{

	LinkListH *tmpList = (LinkListH *)list;
	if (tmpList == NULL)
	{
		return -1;
	}

	return tmpList->length;
}
//插入新节点，让前一节点连接它，它再连接后一节点
int LinkList_Insert(LinkList* list, LinkListNodePtr* node, int pos)
{
	int i = 0;
	if(list==NULL || node==NULL || pos<0)
	{
		return -1;
	}
	LinkListH* tmpList  = (LinkListH *)list;    //tmpList

	LinkListNodePtr* cur = &tmpList->header; //辅助指针指向链表头部

	for (i=0; i<pos && (cur->next!=NULL); i++)  //cur->next!=NULL下一个节点指针域非空
	{
		cur = cur->next;//指针一次往后移
	}

	//让node节点链接后续链表
	node->next = cur->next ;
	//让前边的链表, 链接node
	cur->next = node;       //存放整个数据块的地址

	tmpList->length ++;

	return 0;
}

LinkListNodePtr* LinkList_GetData(LinkList* list, int pos)
{

	int i = 0;

	LinkListH *tmpList  = (LinkListH *)list;
	LinkListNodePtr *cur = NULL;
	LinkListNodePtr *ret = NULL;

	if (list == NULL || pos <0 )
	{
		return NULL;
	}
	//辅助指针指向链表头节点
	cur = &tmpList->header;
	for (i=0; i<pos &&(cur->next!=NULL); i++)
	{
		cur = cur->next;
	}
	ret = cur->next;

	return ret;
}
//记录删除的元素，将待删除的元素的左右元素进行连接
LinkListNodePtr* LinkList_Delete(LinkList* list, int pos)
{
	int i = 0;

	LinkListH *tmpList  = (LinkListH *)list;

	LinkListNodePtr *cur = NULL;	//指针域
	LinkListNodePtr *ret = NULL;


	if (list == NULL || pos <0)
	{
		return NULL;
	}

	cur = &tmpList->header;
	for (i=0; i<pos && (cur->next!=NULL); i++)
	{
		cur = cur->next;    //将下一个域的指针赋予辅助指针cur
	}
	ret = cur->next;

	//删除算法
	cur->next = ret->next;
	tmpList->length--;

	return ret;
}




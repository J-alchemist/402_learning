#include <stdio.h>
#include <malloc.h>
#include "DLinkList.h"

typedef struct _tag_DLinkListH
{
	DLinkListNodePtr header;
	DLinkListNodePtr* slider;
	int length;
} DLinkListH;

DLinkList* DLinkList_Create()
{
	DLinkListH* ret = (DLinkListH*)malloc(sizeof(DLinkListH));

	if( ret != NULL )
	{
		ret->length = 0;
		ret->header.next = NULL;
		ret->header.pre = NULL;
		ret->slider = NULL;
	}

	return ret;
}

void DLinkList_Destroy(DLinkList* list)
{
	if (list != NULL)
	{
		free(list);
	}else return;
}

void DLinkList_Clear(DLinkList* list)
{
	DLinkListH* tmpList = (DLinkListH *)list;

	if( tmpList != NULL )
	{
		tmpList->length = 0;
		tmpList->header.next = NULL;
		tmpList->header.pre = NULL;
		tmpList->slider = NULL;
	}
}

int DLinkList_Length(DLinkList* list)
{
	DLinkListH* tmpList = (DLinkListH *)list;
	int ret = -1;

	if( tmpList != NULL )
	{
		ret = tmpList->length;
	}

	return ret;
}
//0元素插入处理
int DLinkList_Insert(DLinkList* list, DLinkListNodePtr* node, int pos)
{
        int ret = 0, i = 0;
        DLinkListH* tmpList = (DLinkListH *)list;

        if (list==NULL || node==NULL || pos<0)
        {
            return -1;
        }

		DLinkListNodePtr* cur = (DLinkListNodePtr *)tmpList;//插入位置的前一个地址
		DLinkListNodePtr* next = NULL;//插入位置的后一个地址

		for(i=0; (i<pos) && (cur->next != NULL); i++)
		{
			cur = cur->next;
		}

		next = cur->next;

		//步骤1-2
		cur->next = node;
		node->next = next;

		//步骤3-4
		if( next != NULL ) //当链表插入第0个元素，需要特殊处理
		{
			next->pre = node;
		}
		node->pre = cur;    //若是0位置插入cur此时为null

        //当链表插入第0个元素处理游标
		if( tmpList->length == 0 )
		{
			tmpList->slider = node;
		}
/*
		//若在0位置插入，需要特殊处理 新来结点next前pre指向null
		if( cur == (DLinkListNodePtr *)tmpList )
		{
			node->pre = NULL;
		}
*/
		tmpList->length++;

        return ret;
}

DLinkListNodePtr* DLinkList_Get(DLinkList* list, int pos)
{
	DLinkListH* tmpList = (DLinkListH *)list;
	DLinkListNodePtr* ret = NULL;
	int i = 0;

	if( (tmpList != NULL) && ((0 <= pos) && (pos <= tmpList->length-1)) )
	{
		DLinkListNodePtr* cur = (DLinkListNodePtr *)tmpList;

		for(i=0; i<pos; i++)
		{
			cur = cur->next;
		}

		ret = cur->next;
	}

	return ret;
}

//插入第一个节点
//删除尾结点的处理
DLinkListNodePtr* DLinkList_Delete(DLinkList* list, int pos)
{
        DLinkListH* tmpList = (DLinkListH *)list;
        DLinkListNodePtr* ret = NULL;
        int i = 0;

        if (tmpList == NULL )
        {
            return NULL;
        }
         //可做容错处理。。。
        if (pos < 0)  pos=0;
        if( pos >= tmpList->length )  pos = tmpList->length-1;


		DLinkListNodePtr* cur = (DLinkListNodePtr *)tmpList;
		DLinkListNodePtr* next = NULL;

		for(i=0; i<pos; i++)
		{
			cur = cur->next;
		}

		ret = cur->next;//暂存待删除元素地址

		next = ret->next;//next指针指向待删除元素的后面一个元素

		//步骤1
		cur->next = next;

		//步骤2
		if( next != NULL )//需要特殊处理
		{
			next->pre = cur;

		/*	if( cur == (DLinkListNodePtr *)tmpList ) //若第0个位置，需要特殊处理
			{
				next->pre = NULL;
			}*/
		}

		if( tmpList->slider == ret )
		{
			tmpList->slider = next;
		}

		tmpList->length--;

        return ret;
}

DLinkListNodePtr* DLinkList_DeleteNode(DLinkList* list, DLinkListNodePtr* node)
{
	DLinkListH* tmpList = (DLinkListH *)list;
	DLinkListNodePtr* ret = NULL;//存储删除元素的地址
	int i = 0;

	if( tmpList != NULL )
	{
		DLinkListNodePtr* cur = (DLinkListNodePtr *)tmpList;

		for(i=0; i<tmpList->length; i++)
		{
			if( cur->next == node )
			{
				ret = cur->next;
				break;
			}

			cur = cur->next;
		}

		if( ret != NULL )
		{
			DLinkList_Delete(tmpList, i);
		}
	}

	return ret;
}

DLinkListNodePtr* DLinkList_ResetSL(DLinkList* list)
{
	DLinkListH* tmpList = (DLinkListH *)list;
	DLinkListNodePtr* ret = NULL;

	if( tmpList != NULL )
	{
		tmpList->slider = tmpList->header.next;
		ret = tmpList->slider;
	}

	return ret;
}

DLinkListNodePtr* DLinkList_CurrentSL(DLinkList* list)
{
	DLinkListH* tmpList = (DLinkListH *)list;
	DLinkListNodePtr* ret = NULL;

	if( tmpList != NULL )
	{
		ret = tmpList->slider;
	}

	return ret;
}

DLinkListNodePtr* DLinkList_NextSL(DLinkList* list)
{
	DLinkListH* tmpList = (DLinkListH *)list;
	DLinkListNodePtr* ret = NULL;

	if( (tmpList != NULL) && (tmpList->slider != NULL) )
	{
		ret = tmpList->slider;
		tmpList->slider = ret->next;
	}

	return ret;
}

DLinkListNodePtr* DLinkList_PreSL(DLinkList* list)
{
	DLinkListH* tmpList = (DLinkListH *)list;
	DLinkListNodePtr* ret = NULL;

	if( (tmpList != NULL) && (tmpList->slider != NULL) )
	{
		ret = tmpList->slider;
		tmpList->slider = ret->pre;
	}

	return ret;
}



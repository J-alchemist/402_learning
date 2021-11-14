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
//0Ԫ�ز��봦��
int DLinkList_Insert(DLinkList* list, DLinkListNodePtr* node, int pos)
{
        int ret = 0, i = 0;
        DLinkListH* tmpList = (DLinkListH *)list;

        if (list==NULL || node==NULL || pos<0)
        {
            return -1;
        }

		DLinkListNodePtr* cur = (DLinkListNodePtr *)tmpList;//����λ�õ�ǰһ����ַ
		DLinkListNodePtr* next = NULL;//����λ�õĺ�һ����ַ

		for(i=0; (i<pos) && (cur->next != NULL); i++)
		{
			cur = cur->next;
		}

		next = cur->next;

		//����1-2
		cur->next = node;
		node->next = next;

		//����3-4
		if( next != NULL ) //����������0��Ԫ�أ���Ҫ���⴦��
		{
			next->pre = node;
		}
		node->pre = cur;    //����0λ�ò���cur��ʱΪnull

        //����������0��Ԫ�ش����α�
		if( tmpList->length == 0 )
		{
			tmpList->slider = node;
		}
/*
		//����0λ�ò��룬��Ҫ���⴦�� �������nextǰpreָ��null
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

//�����һ���ڵ�
//ɾ��β���Ĵ���
DLinkListNodePtr* DLinkList_Delete(DLinkList* list, int pos)
{
        DLinkListH* tmpList = (DLinkListH *)list;
        DLinkListNodePtr* ret = NULL;
        int i = 0;

        if (tmpList == NULL )
        {
            return NULL;
        }
         //�����ݴ�������
        if (pos < 0)  pos=0;
        if( pos >= tmpList->length )  pos = tmpList->length-1;


		DLinkListNodePtr* cur = (DLinkListNodePtr *)tmpList;
		DLinkListNodePtr* next = NULL;

		for(i=0; i<pos; i++)
		{
			cur = cur->next;
		}

		ret = cur->next;//�ݴ��ɾ��Ԫ�ص�ַ

		next = ret->next;//nextָ��ָ���ɾ��Ԫ�صĺ���һ��Ԫ��

		//����1
		cur->next = next;

		//����2
		if( next != NULL )//��Ҫ���⴦��
		{
			next->pre = cur;

		/*	if( cur == (DLinkListNodePtr *)tmpList ) //����0��λ�ã���Ҫ���⴦��
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
	DLinkListNodePtr* ret = NULL;//�洢ɾ��Ԫ�صĵ�ַ
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



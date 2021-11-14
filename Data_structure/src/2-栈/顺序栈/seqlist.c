#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "seqlist.h"//˳��� 


SeqList *SeqList_Create(int capacity)
{
	if (capacity < 0)
	{
		return NULL;
	}
	
	TSeqList *ret = (TSeqList *)malloc( sizeof(TSeqList) );
	if (ret == NULL)
	{
		return NULL;
	}
	memset(ret, 0, sizeof(TSeqList)); 
	
	ret->node = (unsigned int **)malloc( sizeof( capacity * sizeof(unsigned int) ) ); 
	ret->capacity = capacity;
	ret->length = 0;
	return ret;
}

void SeqList_Destroy(SeqList *list)
{
	if (list == NULL)
	{
		return ;
	}
	free(list);
	return ;
}

//��������
void SeqList_Clear(SeqList *list)
{
	if (list == NULL)
	{
		return ;
	}
	
	TSeqList *tList  = (TSeqList *)list;
	tList->length = 0;
	
	return ;
}

int SeqList_Length(SeqList *list)
{
	if (list == NULL)
	{
		return -1;
	}
	
	TSeqList *tList = (TSeqList *)list; 	
	return tList->length;
}

int SeqList_Capacity(SeqList *list)
{
	TSeqList *tList = (TSeqList *)list; 
	if (list == NULL)
	{
		return -1;
	}

	return tList->capacity;
}
//ͷ�巨����ĳ��λ�ò��� �����ݺ��� 
int SeqList_Insert(SeqList *list, SeqListNode *node, int pos)
{
	int i=0; 
	TSeqList *tList = (TSeqList *)list; 

	if (list == NULL || node == NULL) 
	{
		return -1;
	}

	//�����Ƿ���� 
	if (tList->length >= tList->capacity)
	{
		return -2;
	}

	//λ�úϷ��� 
	if (pos<0 || pos>=tList->capacity)
	{
		return -3;
	}

	//�Ż����ݴ�
	if (pos >= tList->length) 
	{
		pos = tList->length;
	}

	//�����㷨
	//��posλ�ô���ʼ��������ĩβ���˺���
	for(i=tList->length; i>pos; i--)
	{
		//��ǰ��Ԫ��������
		tList->node[i] = tList->node[i-1];
	}
	//ѭ�������Ժ�pos�����ǣ�Ҫ�����λ��
	tList->node[pos] = node; 
	tList->length ++;
	
	return 0;
}

SeqListNode* SeqList_Get(SeqList* list, int pos)
{

	SeqListNode *ret = NULL;
	TSeqList *tList = NULL;
	tList = (TSeqList *)list;
	if (list == NULL || pos<0 || pos>=tList->length)
	{
		return NULL;
	}
	ret = (SeqListNode *)tList->node[pos];//��pos��Ԫ�صĵ�ַ 
	return ret;
}

SeqListNode* SeqList_Delete(SeqList* list, int pos)
{
	int				i;
	TSeqList		*tList = (TSeqList *)list;
	SeqListNode		*ret = NULL; 

	if (list==NULL || pos<0 || pos>=tList->length)
	{
		return NULL;
	}
	
	//����a3֮ǰ��Ҫ��a3Ԫ�ػ�������
	ret = (SeqListNode *)tList->node[pos];//����ɾ��Ԫ�ص�ַ 
	//ɾ���㷨
	for (i=pos+1; i<tList->length; i++)
	{
		tList->node[i-1] = tList->node[i];
	}
	tList->length --;

	return ret;
}

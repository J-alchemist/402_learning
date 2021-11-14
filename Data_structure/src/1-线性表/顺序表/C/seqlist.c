#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "seqlist.h"//顺序表 


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
	ret->lenth = 0;
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

//链表清零
void SeqList_Clear(SeqList *list)
{
	if (list == NULL)
	{
		return ;
	}
	
	TSeqList *tList  = (TSeqList *)list;
	tList->lenth = 0;
	
	return ;
}

int SeqList_Length(SeqList *list)
{
	if (list == NULL)
	{
		return -1;
	}
	
	TSeqList *tList = (TSeqList *)list; 	
	return tList->lenth;
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
//头插法：在某个位置插入 ，数据后移 
int SeqList_Insert(SeqList *list, SeqListNode *node, int pos)
{
	int i=0; 
	TSeqList *tList = (TSeqList *)list; 

	if (list == NULL || node == NULL) 
	{
		return -1;
	}

	//链表是否溢出 
	if (tList->lenth >= tList->capacity)
	{
		return -2;
	}

	//位置合法性 
	if (pos<0 || pos>=tList->capacity)
	{
		return -3;
	}

	//优化的容错
	if (pos >= tList->lenth) 
	{
		pos = tList->lenth;
	}

	//插入算法
	//从pos位置处开始，把数组末尾依此后移
	for(i=tList->lenth; i>pos; i--)
	{
		//把前的元素往后移
		tList->node[i] = tList->node[i-1];
	}
	//循环跳出以后，pos正好是，要出入的位置
	tList->node[pos] = node; 
	tList->lenth ++;
	
	return 0;
}

SeqListNode* SeqList_Get(SeqList* list, int pos)
{

	SeqListNode *ret = NULL;
	TSeqList *tList = NULL;
	tList = (TSeqList *)list;
	if (list == NULL || pos<0 || pos>=tList->lenth)
	{
		return NULL;
	}
	ret = (SeqListNode *)tList->node[pos];//第pos个元素的地址 
	return ret;
}

SeqListNode* SeqList_Delete(SeqList* list, int pos)
{
	int				i;
	TSeqList		*tList = (TSeqList *)list;
	SeqListNode		*ret = NULL; 

	if (list==NULL || pos<0 || pos>=tList->lenth)
	{
		return NULL;
	}
	
	//赋给a3之前，要把a3元素缓存下来
	ret = (SeqListNode *)tList->node[pos];//返回删除元素地址 
	//删除算法
	for (i=pos+1; i<tList->lenth; i++)
	{
		tList->node[i-1] = tList->node[i];
	}
	tList->lenth --;

	return ret;
}

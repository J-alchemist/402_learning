#ifndef  __SEPLIST_H
#define  __SEPLIST_H

typedef void SeqList;
typedef void SeqListNode;

//实际长度  <=  容量!!!
typedef struct _tag_SeqList
{
	int capacity;	//链表的容量 
	int lenth;		//链表实际长度 
	unsigned int **node; //unsigned int *node[]，使用二级指针，提高不同平台的兼容性 
}TSeqList;


SeqList *SeqList_Create(int capacity); //！ 

void SeqList_Destroy(SeqList *list);

void SeqList_Clear(SeqList *list);

int SeqList_Length(SeqList *list);

int SeqList_Capacity(SeqList *list);

int SeqList_Insert(SeqList *list, SeqListNode *node, int pos);//！

SeqListNode *SeqList_Get(SeqList *list, int pos);

SeqListNode *SeqList_Delete(SeqList *list, int pos);//！


#endif 




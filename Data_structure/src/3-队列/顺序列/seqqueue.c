#include <stdio.h>
#include <string.h>
#include <stdio.h>

#include "seqlist.h"
#include "seqqueue.h"


//创建队列，相当于创建一个线性表
SeqQueue* SeqQueue_Create(int capacity)
{
	return SeqList_Create(capacity);
}

void SeqQueue_Destroy(SeqQueue* queue)
{
	 SeqList_Destroy(queue);
}

void SeqQueue_Clear(SeqQueue* queue)
{
	 SeqList_Clear(queue);
}

//向队列中添加元素，相当于 向线性表中 尾部插入 元素（也可以统一头插）
int SeqQueue_Append(SeqQueue* queue, void* item)
{
	return SeqList_Insert(queue, item, SeqList_Length(queue));
}

//出队列，从队列中删除元素，相当于从线性表中删除0元素（先进先出fifo）
void* SeqQueue_Retrieve(SeqQueue* queue)
{
	return SeqList_Delete(queue, 0);
}

//获取队列头元素
void* SeqQueue_Header(SeqQueue* queue)
{
	return SeqList_Get(queue, 0);
}

int SeqQueue_Length(SeqQueue* queue)
{
	return SeqList_Length(queue);
}

int SeqQueue_Capacity(SeqQueue* queue)
{
	return SeqList_Capacity(queue);
}

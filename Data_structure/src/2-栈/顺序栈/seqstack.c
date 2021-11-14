#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "seqlist.h"  //线性表的顺序存储头文件
#include "seqstack.h"



SeqStack* SeqStack_Create(int capacity)
{
	return SeqList_Create(capacity);
}

void SeqStack_Destroy(SeqStack* stack)
{
	 SeqList_Destroy(stack);
}

void SeqStack_Clear(SeqStack* stack)
{
	 SeqList_Clear(stack);
}

//往栈中放元素，相当于向线性表 尾插元素
int SeqStack_Push(SeqStack* stack, void* item)
{
	return SeqList_Insert(stack, item, SeqList_Length(stack));
}

//从栈中弹出元素，相当于从线性表中删除元素
void* SeqStack_Pop(SeqStack* stack)
{
	return SeqList_Delete(stack, SeqList_Length(stack) -1);
}
//获取栈顶元素 相当于获取线性表末尾元素
void* SeqStack_Top(SeqStack* stack)
{
	return SeqList_Get(stack, SeqList_Length(stack)-1);;
}

int SeqStack_Size(SeqStack* stack)
{
	return SeqList_Length(stack);
}

int SeqStack_Capacity(SeqStack* stack)
{
	return SeqList_Capacity(stack);
}

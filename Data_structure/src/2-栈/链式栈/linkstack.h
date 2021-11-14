#ifndef _MY_LINKSTACK_H_
#define _MY_LINKSTACK_H_

#include "linklist.h"

typedef void LinkStack;


typedef struct _tag_LinkStackNode
{
	LinkListNodePtr node;
	void *item;
}LinkStackNode;

LinkStack* LinkStack_Create();

void LinkStack_Destroy(LinkStack* stack);

void LinkStack_Reset(LinkStack* stack);

int LinkStack_Push(LinkStack* stack, void* item);

void* LinkStack_Pop(LinkStack* stack);

void* LinkStack_Top(LinkStack* stack);

int LinkStack_Size(LinkStack* stack);

#endif



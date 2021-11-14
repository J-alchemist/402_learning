#ifndef _MY_DLINKLIST_H_
#define _MY_DLINKLIST_H_

typedef void DLinkList;

typedef struct _tag_DLinkListNodePtr
{
	struct _tag_DLinkListNode* next;
	struct _tag_DLinkListNode* pre;
}DLinkListNodePtr;


DLinkList* DLinkList_Create();

void DLinkList_Destroy(DLinkList* list);

void DLinkList_Clear(DLinkList* list);

int DLinkList_Length(DLinkList* list);

int DLinkList_Insert(DLinkList* list, DLinkListNodePtr* node, int pos);

DLinkListNodePtr* DLinkList_Get(DLinkList* list, int pos);

DLinkListNodePtr* DLinkList_Delete(DLinkList* list, int pos);

//-- add
DLinkListNodePtr* DLinkList_DeleteNode(DLinkList* list, DLinkListNodePtr* node);

DLinkListNodePtr* DLinkList_ResetSL(DLinkList* list);//将游标指向0元素

DLinkListNodePtr* DLinkList_CurrentSL(DLinkList* list);//当前游标位置

DLinkListNodePtr* DLinkList_NextSL(DLinkList* list);//游标的下一个元素

DLinkListNodePtr* DLinkList_PreSL(DLinkList* list);//游标的前一个元素

#endif

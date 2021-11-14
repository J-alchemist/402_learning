#ifndef _MYLINKLIST_H_
#define _MYLINKLIST_H_

typedef  void  LinkList;//泛型指针，兼容性更好

struct  _tag_LinkListNodePtr;
typedef  struct _tag_LinkListNodePtr LinkListNodePtr;
struct _tag_LinkListNodePtr	//让大千世界包含的 节点指针域
{
	LinkListNodePtr* next;
};



LinkList* LinkList_Create();

void LinkList_Destroy(LinkList* list);

void LinkList_Reset(LinkList* list);

int LinkList_GetLength(LinkList* list);

int LinkList_Insert(LinkList* list, LinkListNodePtr* node, int pos);

LinkListNodePtr* LinkList_GetData(LinkList* list, int pos);

LinkListNodePtr* LinkList_Delete(LinkList* list, int pos);

#endif





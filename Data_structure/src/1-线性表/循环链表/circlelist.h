#ifndef _CIRCLELIST_H_
#define _CIRCLELIST_H_

typedef void CircleList;

typedef struct _tag_CircleListNodePtr
{
	struct _tag_CircleListNodePtr * next;
}CircleListNodePtr;

/*
插入和删除0位置元素需注意
*/

CircleList* CircleList_Create();

void List_Destroy(CircleList* list);

void CircleList_Reset(CircleList* list);

int CircleList_GetLength(CircleList* list);

int CircleList_Insert(CircleList* list, CircleListNodePtr* node, int pos);

CircleListNodePtr* CircleList_GetData(CircleList* list, int pos);

CircleListNodePtr* CircleList_Delete(CircleList* list, int pos);//根据节点位置删除

//add
CircleListNodePtr* CircleList_DeleteNode(CircleList* list, CircleListNodePtr* node);//根据节点值删除（值-->找到位置，删除）

CircleListNodePtr* CircleList_ResetSL(CircleList* list);//重置，指向0号元素

CircleListNodePtr* CircleList_CurrentSL(CircleList* list);//当前游标的指向

CircleListNodePtr* CircleList_NextSL(CircleList* list);//移动游标指向下一个元素

#endif

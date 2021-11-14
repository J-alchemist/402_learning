#ifndef _CIRCLELIST_H_
#define _CIRCLELIST_H_

typedef void CircleList;

typedef struct _tag_CircleListNodePtr
{
	struct _tag_CircleListNodePtr * next;
}CircleListNodePtr;

/*
�����ɾ��0λ��Ԫ����ע��
*/

CircleList* CircleList_Create();

void List_Destroy(CircleList* list);

void CircleList_Reset(CircleList* list);

int CircleList_GetLength(CircleList* list);

int CircleList_Insert(CircleList* list, CircleListNodePtr* node, int pos);

CircleListNodePtr* CircleList_GetData(CircleList* list, int pos);

CircleListNodePtr* CircleList_Delete(CircleList* list, int pos);//���ݽڵ�λ��ɾ��

//add
CircleListNodePtr* CircleList_DeleteNode(CircleList* list, CircleListNodePtr* node);//���ݽڵ�ֵɾ����ֵ-->�ҵ�λ�ã�ɾ����

CircleListNodePtr* CircleList_ResetSL(CircleList* list);//���ã�ָ��0��Ԫ��

CircleListNodePtr* CircleList_CurrentSL(CircleList* list);//��ǰ�α��ָ��

CircleListNodePtr* CircleList_NextSL(CircleList* list);//�ƶ��α�ָ����һ��Ԫ��

#endif

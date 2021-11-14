#include <stdio.h>
#include <malloc.h>
#include "CircleList.h"

typedef struct _tag_CircleListH
{
	CircleListNodePtr header;

	CircleListNodePtr* slider;  //����ǰ��ָ��: �α�
	int length;

} CircleListH;

/*
cur��ָ�����ȡԪ�ص�ǰһ���ڵ㣬��Ϊ�����ſ��Եõ�����ȡ�ڵ�ĵ�ַ

*/
CircleList* CircleList_Create()
{
	CircleListH* ret = (CircleListH *)malloc(sizeof(CircleListH));
	if (ret == NULL)
	{
		return NULL;
	}

	ret->length = 0;
	ret->header.next = NULL;
	ret->slider = NULL;

	return ret;
}

void CircleList_Destroy(CircleList* list)
{
	if (list == NULL)
	{
		return ;
	}
	free(list);
}
//�ָ���ʼ��
void CircleList_Reset(CircleList* list)
{
	CircleListH* tmpList = (CircleListH *)list;
	if (tmpList == NULL)
	{
		return ;
	}
	tmpList->length = 0;
	tmpList->header.next = NULL;
	tmpList->slider = NULL;
}

int CircleList_GetLength(CircleList* list)
{
	CircleListH* tmpList = (CircleListH *)list;

	if (list == NULL)
	{
		return -1;
	}
	int ret = tmpList->length;
	return ret;
}
/*
ѭ���б�Ĳ����㷨��ע��ͷ���β��������
*/
int CircleList_Insert(CircleList* list, CircleListNodePtr* node, int pos)
{
        int ret = 0, i=0;
        CircleListH* tmpList = (CircleListH *)list;

        if (list == NULL || node== NULL || pos<0)
        {
            return -1;
        }
        //CircleListNodePtr* cur = &tmpList->header;    //��Ч�¾�
		CircleListNodePtr* cur = (CircleListNodePtr *)tmpList;

		for(i=0; (i<pos) && (cur->next != NULL); i++)
		{
			cur = cur->next;
		}

		//cur->next 0�Žڵ�ĵ�ַ
		node->next = cur->next; //1
		cur->next = node; //2

		//����һ�β���ڵ�
		if( tmpList->length == 0 )//���α�ָ��0�Žڵ�
		{
			tmpList->slider = node;
		}

        tmpList->length++;  //���Ѿ������ˣ�Ҫ�ȼ����ж��Ƿ���ͷ��

		//��ͷ�巨,cur��Ȼָ��ͷ���ģ�Ҳ������pos==0�жϣ�tmpList->header�ĵ�ַ��tmpList��ַ���ص���
		//if( cur == (CircleListNodePtr *)tmpList )
		//if( pos == 0 )
		if( cur == &tmpList->header )//curָ��δ�ƶ���˵��ͷ�巨
		{
			//��ȡ���һ��Ԫ��
			CircleListNodePtr* last = CircleList_GetData(tmpList, tmpList->length - 1);
			//last->next = cur->next; //3  ��Ч�¾�
			last->next = node;
		}



        return ret;
}

CircleListNodePtr* CircleList_GetData(CircleList* list, int pos)
{
        CircleListH* tmpList = (CircleListH*)list;
        CircleListNodePtr* ret = NULL;
        int i = 0;

        if (list==NULL || pos<0)
        {
            return NULL;
        }

		CircleListNodePtr* cur = (CircleListNodePtr *)tmpList;

		for(i=0; i<pos; i++)
		{
			cur = cur->next;
		}

		ret = cur->next;


        return ret;
}

CircleListNodePtr* CircleList_Delete(CircleList* list, int pos)
{
	CircleListH* tmpList = (CircleListH *)list;
	CircleListNodePtr* ret = NULL;
	int i = 0;

	if( (tmpList != NULL) && (pos >= 0) && (tmpList->length > 0) )
	{
		CircleListNodePtr* cur = (CircleListNodePtr *)tmpList;
		CircleListNodePtr* last = NULL;

		for(i=0; i<pos; i++)
		{
			cur = cur->next;
		}

		ret = cur->next;//����ɾ����Ԫ�صĵ�ַ
		cur->next = ret->next;//����

		tmpList->length--;

		//��ɾ����0��Ԫ�أ���ȡ���һ��Ԫ��
		if( cur == (CircleListNodePtr *)tmpList && tmpList->length!=0 )//��һ��Ԫ�ص�����
        //if( cur == (CircleListNodePtr *)tmpList)
		{
			last = (CircleListNodePtr *)CircleList_GetData(tmpList, tmpList->length - 1);


			//�ж������Ƿ�Ϊ��
           // if( last != NULL )
           // {
                last->next = ret->next;
           // }
		}

		//��ɾ����Ԫ��Ϊ�α���ָ��Ԫ�أ���ָ����һ��Ԫ��
		if( tmpList->slider == ret )
		{
			tmpList->slider = ret->next;
		}

		//��ɾ��Ԫ�غ�������Ϊ0
		if( tmpList->length == 0 )
		{
			tmpList->header.next = NULL;
			tmpList->slider = NULL;
		}
	}

	return ret;
}
//���ݽڵ�ֵɾ���ڵ�
CircleListNodePtr* CircleList_DeleteNode(CircleList* list, CircleListNodePtr* node)
{
	CircleListH* tmpList = (CircleListH *)list;
	CircleListNodePtr* ret = NULL;
	int i = 0;

	if( tmpList != NULL )
	{
		CircleListNodePtr* cur = (CircleListNodePtr *)tmpList;

		//����node��ѭ�������е�λ��i
		for(i=0; i<tmpList->length; i++)
		{
			if( cur->next == node )
			{
				ret = cur->next;
				break;
			}

			cur = cur->next;//����
		}

		//���ret�ҵ�������iȥɾ��
		if( ret != NULL )//���ⵥ��Ԫ������
		{
			CircleList_Delete(tmpList, i);
		}
	}

	return ret;
}
//�����α�ָ��0��Ԫ��
CircleListNodePtr* CircleList_ResetSL(CircleList* list)
{
	CircleListH* tmpList = (CircleListH *)list;
	CircleListNodePtr* ret = NULL;

	if( tmpList != NULL )
	{
		tmpList->slider = tmpList->header.next;
		ret = tmpList->slider;
	}

	return ret;
}

CircleListNodePtr* CircleList_CurrentSL(CircleList* list)
{
	CircleListH* tmpList = (CircleListH *)list;
	CircleListNodePtr* ret = NULL;

	if( tmpList != NULL )
	{
		ret = tmpList->slider;
	}

	return ret;
}

CircleListNodePtr* CircleList_NextSL(CircleList* list)
{
	CircleListH* tmpList = (CircleListH *)list;
	CircleListNodePtr* ret = NULL;

	if( (tmpList != NULL) && (tmpList->slider != NULL) )
	{
		ret = tmpList->slider;
		tmpList->slider = ret->next;
	}

	return ret;
}


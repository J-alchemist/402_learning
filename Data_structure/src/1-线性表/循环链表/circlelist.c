#include <stdio.h>
#include <malloc.h>
#include "CircleList.h"

typedef struct _tag_CircleListH
{
	CircleListNodePtr header;

	CircleListNodePtr* slider;  //“当前”指针: 游标
	int length;

} CircleListH;

/*
cur：指向待获取元素的前一个节点，因为这样才可以得到带获取节点的地址

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
//恢复初始化
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
循环列表的插入算法，注意头插和尾插有区别
*/
int CircleList_Insert(CircleList* list, CircleListNodePtr* node, int pos)
{
        int ret = 0, i=0;
        CircleListH* tmpList = (CircleListH *)list;

        if (list == NULL || node== NULL || pos<0)
        {
            return -1;
        }
        //CircleListNodePtr* cur = &tmpList->header;    //等效下句
		CircleListNodePtr* cur = (CircleListNodePtr *)tmpList;

		for(i=0; (i<pos) && (cur->next != NULL); i++)
		{
			cur = cur->next;
		}

		//cur->next 0号节点的地址
		node->next = cur->next; //1
		cur->next = node; //2

		//若第一次插入节点
		if( tmpList->length == 0 )//让游标指向0号节点
		{
			tmpList->slider = node;
		}

        tmpList->length++;  //链已经接上了，要先加再判断是否是头插

		//若头插法,cur仍然指向头部的，也可以用pos==0判断，tmpList->header的地址与tmpList地址是重叠的
		//if( cur == (CircleListNodePtr *)tmpList )
		//if( pos == 0 )
		if( cur == &tmpList->header )//cur指针未移动，说明头插法
		{
			//获取最后一个元素
			CircleListNodePtr* last = CircleList_GetData(tmpList, tmpList->length - 1);
			//last->next = cur->next; //3  等效下句
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

		ret = cur->next;//返回删除的元素的地址
		cur->next = ret->next;//链接

		tmpList->length--;

		//若删除第0个元素，获取最后一个元素
		if( cur == (CircleListNodePtr *)tmpList && tmpList->length!=0 )//非一个元素的链表
        //if( cur == (CircleListNodePtr *)tmpList)
		{
			last = (CircleListNodePtr *)CircleList_GetData(tmpList, tmpList->length - 1);


			//判断链表是否为空
           // if( last != NULL )
           // {
                last->next = ret->next;
           // }
		}

		//若删除的元素为游标所指的元素，则指向下一个元素
		if( tmpList->slider == ret )
		{
			tmpList->slider = ret->next;
		}

		//若删除元素后，链表长度为0
		if( tmpList->length == 0 )
		{
			tmpList->header.next = NULL;
			tmpList->slider = NULL;
		}
	}

	return ret;
}
//根据节点值删除节点
CircleListNodePtr* CircleList_DeleteNode(CircleList* list, CircleListNodePtr* node)
{
	CircleListH* tmpList = (CircleListH *)list;
	CircleListNodePtr* ret = NULL;
	int i = 0;

	if( tmpList != NULL )
	{
		CircleListNodePtr* cur = (CircleListNodePtr *)tmpList;

		//查找node在循环链表中的位置i
		for(i=0; i<tmpList->length; i++)
		{
			if( cur->next == node )
			{
				ret = cur->next;
				break;
			}

			cur = cur->next;//遍历
		}

		//如果ret找到，根据i去删除
		if( ret != NULL )//避免单个元素链表
		{
			CircleList_Delete(tmpList, i);
		}
	}

	return ret;
}
//重置游标指向0号元素
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


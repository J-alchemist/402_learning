#include <stdio.h>
#include <stdlib.h>
#include "CircleList.h"

typedef struct Value
{
	CircleListNodePtr node;
	int v;
}Value;

int  main()
{
	int i = 0;
	CircleList* list = CircleList_Create();

	Value v1;	v1.v = 1;
	Value v2;	v2.v = 2;
	Value v3;	v3.v = 3;


    //ͷ�巨
	CircleList_Insert(list, (CircleListNodePtr *)&v1, 0);
	//β�巨
	CircleList_Insert(list, (CircleListNodePtr *)&v2, CircleList_GetLength(list));
	//��ͨ����
	CircleList_Insert(list, (CircleListNodePtr *)&v3, 1);

	for(i=0; i< 2*CircleList_GetLength(list); i++)  //ѭ������2������֤�Ƿ������ѭ������
	{
		Value* pv = (Value *)CircleList_GetData(list, i);
		printf("%d\n", pv->v);
	}
	printf("-------------\n");
/*    //ɾ��Ԫ��
	while( CircleList_GetLength(list) > 0 )
	{
		Value* pv = (struct Value*)CircleList_Delete(list, 0);

		printf("%d\n", pv->v);
	}

	printf("-------------\n");*/
	//���α�ɾ��Ԫ��
	CircleList_ResetSL(list);//�����α�

	while( CircleList_GetLength(list) > 0 )
	{
		Value* pv = NULL;

		for(i=0; i<2; i++)//�ƶ��α�1��
		{
			CircleList_NextSL(list);
		}

		pv = (Value *)CircleList_CurrentSL(list);
		printf("%d\n", pv->v);

		CircleList_DeleteNode(list, (CircleListNodePtr *)pv);
	}

	CircleList_Destroy(list);

	system("pause");

	return 0;

}



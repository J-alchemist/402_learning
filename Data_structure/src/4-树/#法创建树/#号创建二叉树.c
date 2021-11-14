#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct BiTNode
{
	int data;
	struct BiTNode *lchild, *rchild;
}BiTNode, *BiTree;

//���������������н�����������
BiTNode* BiTree_Create1()
{
	BiTNode *tmp = NULL;
	char ch;
	printf("\n�������ַ�: ");
	scanf("%c", &ch);
	if (ch == '#')
	{
		return NULL;
	}
	else
	{
		tmp = (BiTNode *)malloc(sizeof(BiTNode));
		if (tmp == NULL)
		{
			return NULL;
		}
		tmp->data = ch; //���ɸ����
		tmp->lchild = BiTree_Create1();//����������
		tmp->rchild = BiTree_Create1();//����������
		return tmp;
	}
}

void preOrder(BiTNode *root)//�������
{
	if (root != NULL)
	{
		printf("%c ", root->data);
		preOrder(root->lchild);
		preOrder(root->rchild);
	}
}

//���������������н������������ͷŶ�����
void  BiTree_Free(BiTNode* T)
{
	BiTNode *tmp = NULL;
	if (T!= NULL)
	{
		if (T->rchild != NULL) BiTree_Free(T->rchild);
		if (T->lchild != NULL) BiTree_Free(T->lchild);
		if (T != NULL)
		{
			free(T);
			T = NULL;
		}
	}
}


int main()
{
	int nCount = 0, depthval = 0;
	BiTNode* my = BiTree_Create1();

	preOrder(my);
    printf("\n������������\n");
	BiTree_Free(my);
	printf("���ͷ����\n");

	printf("\n");

	return 0;

}

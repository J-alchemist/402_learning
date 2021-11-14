#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "tree_operate.h"

//树的链式存储
/*
//二叉链表示法
typedef struct BiTNode
{
	int data;
	struct BiTNode *lchild, *rchild;
}BiTNode, *BiTree;
*/

int main(void)
{
	BiTNode t1, t2, t3, t4, t5;
	memset(&t1, 0, sizeof(BiTNode));
	memset(&t2, 0, sizeof(BiTNode));
	memset(&t3, 0, sizeof(BiTNode));
	memset(&t4, 0, sizeof(BiTNode));
	memset(&t5, 0, sizeof(BiTNode));
	t1.data = 1;    t2.data = 2;
	t3.data = 3;    t4.data = 4;
	t5.data = 5;

	//建立关系  t1为根节点
	t1.lchild = &t2;
	t1.rchild = &t3;
	t2.lchild = &t4;
	t3.lchild = &t5;


	//1-树的遍历
	printf("preOrder\n");
	preOrder(&t1);

	printf("\ninorder\n");
	inOrder(&t1);

	printf("\npostOrder\n");
	postOrder(&t1);

	printf("\n");


/*
    //求叶子
    //1
	Leaf_Sum = 0;
	coutLeaf(&t1);
	printf("Leaf_Sum: %d \n", Leaf_Sum);

	//2
	{
		int Leaf_Sum = 0;
		coutLeaf2(&t1, &Leaf_Sum);
		printf("Leaf_Sum: %d \n", Leaf_Sum);
	}
*/
/*    //树深度
    int deep = GetDepth(&t1);
    printf("tree deep: %d\n", deep);

    //复制树
    {
        BiTNode* tree;
        tree = CopyTree(&t1);

        printf("copy tree is: \n");
        preOrder(tree);
        printf("\n");
    }
*/

	system("pause");
	return 0;

}
/*
//阶乘递归
int fun(int nu)
{
    int sum;
    if( nu==1 || nu ==0 )
        return 1;
    else
        sum = nu * fun(nu-1);

    return sum;
}

int main(void)
{
    int a = fun (1);
    printf("%d", a);

    return 0;
}
*/

#include "tree_operate.h"
#include <stdio.h>


//先序遍历
void preOrder(BiTNode *root)
{
	if (root == NULL)
	{
		return;
	}
	printf("%d ", root->data);

	//遍历左子树
	preOrder(root->lchild);

	//遍历右子树
	preOrder(root->rchild);
}
//中序遍历
void inOrder(BiTNode *root)
{
	if (root == NULL)
	{
		return;
	}
	//遍历左子树
	inOrder(root->lchild);

	printf("%d ", root->data);
	//遍历右子树
	inOrder(root->rchild);
}
//后续遍历
void postOrder(BiTNode *root)
{
	if (root == NULL)
	{
		return;
	}
	//遍历左子树
	postOrder(root->lchild);

	//遍历右子树
	postOrder(root->rchild);

	printf("%d ", root->data);
}


//------------------------求二叉树叶子结点数（度=0的结点）
//无论采用先序、中序、后序遍历都一样
int Leaf_Sum;
void coutLeaf(BiTNode *root)
{
	if (root != NULL)
	{
		if ( root->lchild == NULL && root->rchild == NULL )//先序
		{
			Leaf_Sum ++ ;
		}
		if ( root->lchild )
		{
			coutLeaf( root->lchild );
		}

		if ( root->rchild )
		{
			coutLeaf( root->rchild );
		}
	}
}
//优化，避免多进程访问使用全局变量
void coutLeaf2(BiTNode *root, int *Leaf_Sum)
{
	if (root != NULL)
	{
		if (root->lchild == NULL && root->rchild==NULL)
		{
			(*Leaf_Sum)++;
		}
		if (root->lchild )
		{
			coutLeaf2(root->lchild, Leaf_Sum);
		}

		if (root->rchild)
		{
			coutLeaf2(root->rchild, Leaf_Sum);
		}
	}
}

//复制树
//函数嵌套调用（递归），再一一返回
//最后一层返回的是最上层根结点
BiTNode* CopyTree(BiTNode *root)
{
	BiTNode* newNode = NULL;
	BiTNode* newLp = NULL;
	BiTNode* newRp = NULL;

	if (root == NULL)
	{
		return NULL;
	}

	//copy左子树
	if (root->lchild != NULL)
	{
		newLp = CopyTree(root->lchild); //copy左子树
	}
	else
	{
		newLp = NULL;
	}

	//copy右子树
	if (root->rchild != NULL)
	{
		newRp = CopyTree(root->rchild);
	}
	else
	{
		newRp = NULL;
	}

	//malloc创建根节点
	/*
	每个结点都看作根，只是有的无子节点，有的有子节点
	*/
	newNode = (BiTNode *)malloc(sizeof(BiTNode));
	if (newNode == NULL)
	{
		return NULL;
	}
	newNode->lchild = newLp;
	newNode->rchild = newRp;
	newNode->data = root->data;

	return newNode;
}

/*
递归到最底层的一个根节点，比较返回
*/
int GetDepth(BiTNode *root)
{
	int		deptleft = 0;
	int		deptright = 0;
	int		deptval = 0;

	if (root == NULL)
	{
		deptval = 0;
		return deptval;
	}

	//求左子树的高度
	deptleft = GetDepth(root->lchild);

	//求右子树的高度
	deptright = GetDepth(root->rchild);

	//深度+1
	deptval = 1 + (deptleft>deptright ? deptleft : deptright);

	return deptval;

}







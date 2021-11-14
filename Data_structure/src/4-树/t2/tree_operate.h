#ifndef __TREE_OPERATE
#define __TREE_OPERATE



//二叉链表示法
struct BiTNode
{
	int data;       //结点数据
	struct BiTNode *lchild, *rchild;//左子节点、右子节点
};
typedef struct BiTNode		BiTNode;//变量类型
typedef struct BiTNode*		BiTree;//指针类型


//遍历
void preOrder(BiTNode *root);
void inOrder(BiTNode *root);
void postOrder(BiTNode *root);

//求叶子数
void coutLeaf(BiTNode *root);
extern int Leaf_Sum;
void coutLeaf2(BiTNode *root, int *Leaf_Sum);

//复制树
BiTNode* CopyTree(BiTNode *root);
//树深度
int GetDepth(BiTNode *root);


#endif


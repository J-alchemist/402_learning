#include <stdlib.h>
#include <string.h>
#include <stdio.h>


/*
typedef struct BiTNode
{
	int data;
	struct BiTNode *lchild, *rchild;
}BiTNode, *BiTree;
*/


//二叉链表示法
struct BiTNode
{
	int data;
	struct BiTNode *lchild, *rchild;
};
typedef struct BiTNode		BiTNode;
typedef struct BiTNode*		BiTree;

//三叉链表示法
typedef struct TriTNode
{
	int data;

	struct TriTNode *lchild, *rchild;	//左右孩子指针
	struct TriTNode *parent;        //双亲指针
}TriTNode, *TriTree;

//双亲链表示法
#define MAX_TREE_SIZE 100
typedef struct BPTNode  //结点类型
{
	int data;
	int parentPosi; //指向双亲的指针 //数组下标
	char LRTag;     //标记孩子是左、还是右
}BPTNode;

typedef struct BPTree
{
	BPTNode nodes[MAX_TREE_SIZE]; //因为节点之间是分散的，需要把节点存储到数组中
	int num_node;  //节点数目
	int root; //根结点的位置
}BPTree;


void main()
{
	BPTree tree;

	//根结点：tree.nodes[0]
	tree.nodes[0].parentPosi = 10000;
    tree.nodes[0].data = 'A';
	//B结点：tree.nodes[1]
	tree.nodes[1].parentPosi = 0;
	tree.nodes[1].data = 'B';
	tree.nodes[1].LRTag = 1;//左

	//c结点：tree.nodes[2]
	tree.nodes[2].parentPosi = 0;
	tree.nodes[2].data = 'C';
	tree.nodes[2].LRTag = 2;//右

	tree.num_node = 3;
    tree.root = 0;

	system("pause");

}



void main02()
{
   // BiTree p1 , p2, p3 p4, p5;
	BiTNode *p1, *p2, *p3, *p4, *p5;
	p1 = (BiTNode *)malloc(sizeof(BiTNode));
	p2 = (BiTNode *)malloc(sizeof(BiTNode));
	p3 = (BiTNode *)malloc(sizeof(BiTNode));
	p4 = (BiTNode *)malloc(sizeof(BiTNode));
	p5 = (BiTNode *)malloc(sizeof(BiTNode));

	p1->data = 1;
	p2->data = 2;
	p3->data = 3;
	p4->data = 4;
	p5->data = 5;

	//建立关系
	p1->lchild = p2;
	p1->rchild = p3;
	p2->lchild = p4;
	p3->lchild = p5;

	//树的遍历
    //......

	system("pause");
	return ;
}

void main01()
{
	BiTNode t1, t2, t3, t4, t5;
	memset(&t1, 0, sizeof(BiTNode));
	memset(&t2, 0, sizeof(BiTNode));
	memset(&t3, 0, sizeof(BiTNode));
	memset(&t4, 0, sizeof(BiTNode));
	memset(&t5, 0, sizeof(BiTNode));
	t1.data = 1;
	t2.data = 2;
	t3.data = 3;
	t4.data = 4;
	t5.data = 5;

	//建立关系
	t1.lchild = &t2;
	t1.rchild = &t3;
	t2.lchild = &t4;
	t3.lchild = &t5;

    //树的遍历
	//......

	system("pause");
	return ;
}


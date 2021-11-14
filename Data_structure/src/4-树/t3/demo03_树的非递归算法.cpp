#include <iostream>
#include <stack>    //c++栈操作文件
#include <cstring>

using namespace std;

/*
非递归中序遍历：
步骤1：
如果结点有左子树，该结点入栈；
如果结点没有左子树，访问该结点；
步骤2：
如果结点有右子树，重复步骤1；
如果结点没有右子树（结点访问完毕），根据栈顶指示回退，访问栈顶元素，并访问右子树，重复步骤1
如果栈为空，表示遍历结束。
总思路：从左下到右下
*/

//二叉链表
typedef struct BiNode
{
	int data;
	struct BiNode  *lchild, *rchild;
}BiNode, *BiTree;

BiNode* GoFarLeft(BiNode *T, stack<BiNode *> &s)
{
	if (T == NULL)
	{
		return NULL;
	}
	while (T->lchild)
	{
		s.push(T);
		T = T->lchild;
	}
	return T;
}
void InOrder2(BiNode *T)
{
	 stack<BiNode *> s;

	 //步骤1：一直往左走，找到中序遍历的起点
	 BiTree t = GoFarLeft(T, s);

	 while (t != NULL)
	 {
		 cout << t->data << " " ;//中序遍历打印

		 //如果t节点有右子树，那么重复步骤1
		 if (t->rchild != NULL)
		 {
			t =  GoFarLeft(t->rchild, s);
		 }
		 //如果t没有右子树，根据栈顶指示，访问栈顶元素
		 else if (!s.empty())//栈是否为空
		 {
			 t = s.top();   //获取栈顶元素
			 s.pop();       //从栈中删除栈顶元素
		 }
		 //如果t没有右子树，并且栈为空
		 else
		 {
			 t = NULL;
		 }
	 }

}
int main()
{
	BiNode t1, t2, t3, t4, t5;
	memset(&t1, 0, sizeof(BiNode));
	memset(&t2, 0, sizeof(BiNode));
	memset(&t3, 0, sizeof(BiNode));
	memset(&t4, 0, sizeof(BiNode));
	memset(&t5, 0, sizeof(BiNode));
	t1.data = 1;    t2.data = 2;
	t3.data = 3;    t4.data = 4;
	t5.data = 5;

	t1.lchild = &t2;
	t1.rchild = &t3;
	t2.lchild = &t4;
	t3.lchild = &t5;

	InOrder2(&t1);

	return 0;
}


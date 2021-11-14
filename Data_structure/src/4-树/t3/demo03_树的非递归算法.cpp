#include <iostream>
#include <stack>    //c++ջ�����ļ�
#include <cstring>

using namespace std;

/*
�ǵݹ����������
����1��
�����������������ý����ջ��
������û�������������ʸý�㣻
����2��
�����������������ظ�����1��
������û������������������ϣ�������ջ��ָʾ���ˣ�����ջ��Ԫ�أ����������������ظ�����1
���ջΪ�գ���ʾ����������
��˼·�������µ�����
*/

//��������
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

	 //����1��һֱ�����ߣ��ҵ�������������
	 BiTree t = GoFarLeft(T, s);

	 while (t != NULL)
	 {
		 cout << t->data << " " ;//���������ӡ

		 //���t�ڵ�������������ô�ظ�����1
		 if (t->rchild != NULL)
		 {
			t =  GoFarLeft(t->rchild, s);
		 }
		 //���tû��������������ջ��ָʾ������ջ��Ԫ��
		 else if (!s.empty())//ջ�Ƿ�Ϊ��
		 {
			 t = s.top();   //��ȡջ��Ԫ��
			 s.pop();       //��ջ��ɾ��ջ��Ԫ��
		 }
		 //���tû��������������ջΪ��
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


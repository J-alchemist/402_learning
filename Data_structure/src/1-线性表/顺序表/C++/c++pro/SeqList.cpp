#include "SeqList.h"
#include <stdlib.h>
template <class T>
SeqList<T>::SeqList(int cap)
{
    node = new T[cap]; //���� new int[10]

    this->capacity = cap;
    this->lenth = 0;
}

template <class T>
SeqList<T>::~SeqList()
{
    delete[] node;
    this->node = NULL;
    this->lenth = 0;
    this->capacity = 0;
}
//-------------------------------------

template <class T>
int SeqList<T>::getLen()
{
    return this->lenth;
}

template <class T>
int SeqList<T>::getCap()
{
    return this->capacity;//return capacity;һ��
}

template <class T>
int SeqList<T>::insertVal(T &t, int pos)
{
    int i;
    if ( pos <0 )
	{
		return -1;
	}
	//�����㷨
	//��posλ�ô���ʼ��������ĩβ���˺���

	for( i=getLen(); i>pos; i--)
	{
		//��ǰ��Ԫ��������
		node[i] = node[i-1];
	}

	//ѭ�������Ժ�pos�����ǣ�Ҫ�����λ��
	node[pos] = t;
	lenth ++;

    return 0;
}


template <class T>
int SeqList<T>::getVal(T &t, int pos)
{
	if ( pos<0 )
	{
		return -1;
	}
	t = node[pos];//��pos��Ԫ�صĵ�ַ

    return 0;
}

template <class T>
int SeqList<T>::delVal(T &t, int pos)
{
    int i;
    if ( pos<0 )
	{
		return -1;
	}

	//����a3֮ǰ��Ҫ��a3Ԫ�ػ�������
	t = node[pos];
	//ɾ���㷨
	for (i=pos+1; i<lenth; i++)
	{
		node[i-1] = node[i];
	}
	lenth --;

    return 0;
}


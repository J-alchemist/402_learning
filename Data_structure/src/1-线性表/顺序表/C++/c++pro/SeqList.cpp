#include "SeqList.h"
#include <stdlib.h>
template <class T>
SeqList<T>::SeqList(int cap)
{
    node = new T[cap]; //比照 new int[10]

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
    return this->capacity;//return capacity;一样
}

template <class T>
int SeqList<T>::insertVal(T &t, int pos)
{
    int i;
    if ( pos <0 )
	{
		return -1;
	}
	//插入算法
	//从pos位置处开始，把数组末尾依此后移

	for( i=getLen(); i>pos; i--)
	{
		//把前的元素往后移
		node[i] = node[i-1];
	}

	//循环跳出以后，pos正好是，要出入的位置
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
	t = node[pos];//第pos个元素的地址

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

	//赋给a3之前，要把a3元素缓存下来
	t = node[pos];
	//删除算法
	for (i=pos+1; i<lenth; i++)
	{
		node[i-1] = node[i];
	}
	lenth --;

    return 0;
}


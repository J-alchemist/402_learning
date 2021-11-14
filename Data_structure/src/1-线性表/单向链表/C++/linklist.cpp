#include "linklist.h"
#include <iostream>

template <class T>
LinkList<T>::LinkList()
{
    header = new Node<T>;
    header->next = NULL;
    this->lenth = 0;
}

template <class T>
LinkList<T>::~LinkList()
{
    Node<T>* tmp = NULL;

    while(header != NULL)
    {
        tmp = header->next;//暂存下一个结点的地址，否则释放头节点后找不着
        delete header;
        header = tmp;
    }

    lenth = 0;
    //header->next = NULL;//错误
    header = NULL;
}

template <class T>
int LinkList<T>::clear_linklist()
{
    //先干掉所有内存
    Node<T>* tmp = NULL;

    while(header != NULL)
    {
        tmp = header->next;//暂存下一个结点的地址，否则释放头节点后找不着
        delete header;
        header = header->next;
    }
    //再重新分配头指针
    header = new Node<T>;
    header->next = NULL;
    this->lenth = 0;

    return 0;
}

template <class T>
int LinkList<T>::get_len()
{
    return this->lenth;
}

template <class T>
int LinkList<T>::insert_val(T &t, int pos)
{
    Node<T>* cur = header;

    for(int i = 0; i<pos; i++)
    {
        cur = cur->next;
    }

    Node<T>* node = new Node<T>;
    node->t = t;//缓存外部数据

    node->next = NULL;
    //链接
    node->next = cur->next;
    cur->next = node;

    this->lenth++;

    return 0;
}

template <class T>
int LinkList<T>::get_val(T &t, int pos)
{
    Node<T>* cur = header;

    for(int i = 0; i<pos; i++)
    {
        cur = cur->next;
    }

    t = cur->next->t;//把缓存的t传给调用者


    return 0;
}

template <class T>
int LinkList<T>::delete_val(T &t, int pos)
{
    Node<T>* cur = header;
    Node<T>* ret = NULL;

    for(int i = 0; i<pos; i++)
    {
        cur = cur->next;
    }
    ret = cur->next;//被删除元素
    t = ret->t;//传出

    cur->next = ret->next;

    lenth--;

    delete ret;

    return 0;
}


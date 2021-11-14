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
        tmp = header->next;//�ݴ���һ�����ĵ�ַ�������ͷ�ͷ�ڵ���Ҳ���
        delete header;
        header = tmp;
    }

    lenth = 0;
    //header->next = NULL;//����
    header = NULL;
}

template <class T>
int LinkList<T>::clear_linklist()
{
    //�ȸɵ������ڴ�
    Node<T>* tmp = NULL;

    while(header != NULL)
    {
        tmp = header->next;//�ݴ���һ�����ĵ�ַ�������ͷ�ͷ�ڵ���Ҳ���
        delete header;
        header = header->next;
    }
    //�����·���ͷָ��
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
    node->t = t;//�����ⲿ����

    node->next = NULL;
    //����
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

    t = cur->next->t;//�ѻ����t����������


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
    ret = cur->next;//��ɾ��Ԫ��
    t = ret->t;//����

    cur->next = ret->next;

    lenth--;

    delete ret;

    return 0;
}


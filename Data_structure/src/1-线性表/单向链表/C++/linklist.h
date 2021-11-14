#ifndef LINKLIST_H
#define LINKLIST_H

template <class T>
struct Node
{
    T t;
	Node<T>* next;

};

template <class T>
class LinkList
{
    public:
        LinkList();
        virtual ~LinkList();


        int clear_linklist();
        int get_len();
        int insert_val(T &t, int pos);
        int get_val(T &t, int pos);
        int delete_val(T &t, int pos);

    private:

        int lenth;
        Node<T>* header;
};

#endif




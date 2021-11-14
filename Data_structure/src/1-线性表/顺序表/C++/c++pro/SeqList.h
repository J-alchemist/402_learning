#ifndef __SEQLIST_H
#define __SEQLIST_H

template <class T>
class SeqList
{
    public:
        SeqList(int cap);
        virtual ~SeqList();

        int getLen();//用来访问私有变量
        int getCap();

        int insertVal(T &t, int pos);
        int getVal(T &t, int pos);
        int delVal(T &t, int pos);

    private:
        	int capacity;	//链表的容量
            int lenth;		//链表实际长度
            T* node;        //结点
};

#endif



#ifndef __SEQLIST_H
#define __SEQLIST_H

template <class T>
class SeqList
{
    public:
        SeqList(int cap);
        virtual ~SeqList();

        int getLen();//��������˽�б���
        int getCap();

        int insertVal(T &t, int pos);
        int getVal(T &t, int pos);
        int delVal(T &t, int pos);

    private:
        	int capacity;	//���������
            int lenth;		//����ʵ�ʳ���
            T* node;        //���
};

#endif



#include <iostream>
#include <thread>

using namespace std;
/*
������ܣ�detach�����̵߳ı����ͷ��ˣ��������̻߳���ʹ�ã����»�ȡ����
*/

void myPrint(const int &i, char* pmybuf)
{
	//����̴߳����߳�detach��
	//i����mvar���������ã�ʵ����ֵ���ݣ���ʹ���߳���������ˣ����߳���i��Ȼ�ǰ�ȫ�ģ����Բ��Ƽ���������
	//�Ƽ���Ϊconst int i
	cout << i << endl;
	//pmybuf����ָ��ԭ�����ַ�����������ôд�ǲ���ȫ��
	cout << pmybuf << endl;

}

int main1()
{

	int mvar = 1;
	//int& mvary = mvar;
	char mybuf[] = "this is a test";
	thread myThread( myPrint, mvar, mybuf );//��һ�������Ǻ������������������Ǻ����Ĳ���
	//myThread.join();
	myThread.detach();

	cout << "���߳��ͷ�!" << endl;

	return 0;

}



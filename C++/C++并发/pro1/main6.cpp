#include <iostream>
#include <thread>
#include <atomic>

using namespace std;

std::atomic<int> g_count(0); //��װ��һ������Ϊint�� ����ֵ��

void mythread1() {
	for (int i = 0; i < 2000000; i++) {

         //֧�ֵ�ԭ�Ӳ���
		g_count++;


		//��Ȼgg_countʹ����ԭ�Ӳ���ģ�壬��������д���ȶ���д��
		 //�ᵼ�¼�������
         //gg_count = gg_count + 1;

	}



}

/*
ԭ�Ӳ���֮��ÿ���̶߳���ִ��2000000��
*/

int main6() {

	std::thread t1(mythread1);
	std::thread t2(mythread1);
	t1.join();
	t2.join();
	cout << "��������½��Ӧ����400000�Σ�ʵ����" << g_count << endl;

}

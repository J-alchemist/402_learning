#include <thread>
#include <iostream>
#include <list>
#include <mutex>
#include <condition_variable>

using namespace std;

class A {
public:
    void inMsgRecvQueue() {
        for (int i = 0; i < 100000; ++i)
        {
            cout << "inMsgRecvQueue����һ��Ԫ��" << i << endl;

            std::unique_lock<std::mutex> sbguard1(mymutex1);
            msgRecvQueue.push_back(i);
            //���԰�wait()�̻߳���,ִ�������У�
            //��ôoutMsgRecvQueue()���wait�ͻᱻ����
            //ֻ�е�����һ���߳�����ִ��wait()ʱnotify_one()�Ż���Ч������û������
            condition.notify_one();
        }
	}

	void outMsgRecvQueue() {
        int command = 0;
        while (true) {
            std::unique_lock<std::mutex> sbguard2(mymutex1);
            // wait()������һ������
            // ����ڶ���������lambda���ʽ����ֵ��false����ôwait()��������������������������
            // ������ʲôʱ��Ϊֹ�أ�����������ĳ���̵߳���notify_one()��Ա����Ϊֹ��
            //�� wait() �� notify_one() ����ʱ������ִ������ �����жϱ��ʽ �Ƿ�Ϊ true��
            //���Ϊtrue�Ż��������ִ��
            condition.wait(sbguard2, [this] {
                if (!msgRecvQueue.empty())
                    return true;
                return false;});
            command = msgRecvQueue.front();
            msgRecvQueue.pop_front();
            //��Ϊunique_lock������ԣ����ǿ�����ʱunlock��������ס̫��ʱ��
            sbguard2.unlock();
            cout << "outMsgRecvQueue()ִ�У�ȡ����һ��Ԫ��" << endl;
        }
	}

private:
	std::list<int> msgRecvQueue;
	std::mutex mymutex1;
	std::condition_variable condition;
};

int main4() {
	A myobja;
	std::thread myoutobj(&A::outMsgRecvQueue, &myobja);
	std::thread myinobj(&A::inMsgRecvQueue, &myobja);
	myinobj.join();
	myoutobj.join();
}

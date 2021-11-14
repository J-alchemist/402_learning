#include <iostream>
#include <thread>

using namespace std;

void myPrint()
{
    cout << "���߳�id��" << std::this_thread::get_id() << endl;

	cout << "���߳̿�ʼ����" << endl;
	//-------------
	//-------------
	cout << "���߳��������" << endl;

	return;

}

int main0()
{
	//(1)�������̣߳��߳�ִ����㣨��ڣ���myPrint��(2)ִ���߳�
	thread Thread1(myPrint);

    cout << "���߳�id��" << std::this_thread::get_id() << endl;

	//(2)�������̲߳��ȴ�myPrintִ���꣬��myPrintִ����ϣ�join()��ִ����ϣ����̼߳�������ִ��
	//join��Ϊ��ϣ����̺߳����̻߳غ�
	 //Thread1.join();

	//(3)��ͳ���̳߳����У����߳�Ҫ�ȴ����߳�ִ����ϣ�Ȼ���Լ���������ִ��
	//detach:���룬���̲߳��������̻߳�ϣ����ٵȴ����߳�
	//detach�����̺߳����߳�ʧȥ������פ���ں�̨����C++����ʱ��ӹܣ�ִ������ƶ�����
	Thread1.detach();

	//(4)joinable()�ж��Ƿ���Գɹ�ʹ��join()����detach()
	//�������true��֤�����Ե���join()����detach()
	//�������false��֤�����ù�join()����detach()��join()��detach()�������ٵ�����
	if (Thread1.joinable())
	{
		cout << "���Ե��ÿ��Ե���join()����detach()" << endl;
	}
	else
	{
		cout << "���ܵ��ÿ��Ե���join()����detach()" << endl;
	}

	cout << "Hello World!" << endl;

	return 0;

}

//���������̵߳ķ���
/*
//1
class Ta
{
public:
	void operator()()
	{
		cout << "�ҵ��߳̿�ʼ����" << endl;
		//-------------
		//-------------
		cout << "�ҵ��߳��������" << endl;
	}
};

//main������ģ�
	Ta ta;
	thread Thread1(ta);
	Thread1.join();

//2
//main������
auto lambdaThread = [] {
		cout << "�ҵ��߳̿�ʼִ����" << endl;
		//-------------
		//-------------
		cout << "�ҵ��߳̿�ʼִ����" << endl;
	};

	thread Thread1(lambdaThread);
	Thread1.join();

//3
class Data_
{
public:
    void GetMsg(){}
    void SaveMsh(){}
};
//main������
    //��һ��&��˼��ȡַ���ڶ���&��˼�����ã��൱��std::ref(s)
    //thread oneobj(&Data_::SaveMsh,s)��ֵҲ�ǿ��Ե�
    //�������Ĺ��캯����&obj�ǲ���������õģ��ᱻ����ȡ��ַ
    //���÷�ʽ�������Ա������ַ����ʵ����[��Ա��������]
	//�ڶ����������Դ��ݶ���s��Ҳ���Դ�������std::ref(s)��&s
	//����s������ÿ������캯�������߳�������һ���µĶ���
	//����&�����߳��л����õ�ԭ���Ķ������ԾͲ���detach����Ϊ���߳�������ϻ�Ѹö����ͷŵ�

	Data_ s;
    thread oneobj(&Data_::SaveMsh,&s);
    thread twoobj(&Data_::GetMsg,&s);
    oneobj.join();
    twoobj.join();



*/


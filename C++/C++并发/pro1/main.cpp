#include <iostream>
#include <thread>

using namespace std;

void myPrint()
{
    cout << "子线程id：" << std::this_thread::get_id() << endl;

	cout << "子线程开始运行" << endl;
	//-------------
	//-------------
	cout << "子线程运行完毕" << endl;

	return;

}

int main0()
{
	//(1)创建了线程，线程执行起点（入口）是myPrint；(2)执行线程
	thread Thread1(myPrint);

    cout << "主线程id：" << std::this_thread::get_id() << endl;

	//(2)阻塞主线程并等待myPrint执行完，当myPrint执行完毕，join()就执行完毕，主线程继续往下执行
	//join意为汇合，子线程和主线程回合
	 //Thread1.join();

	//(3)传统多线程程序中，主线程要等待子线程执行完毕，然后自己才能向下执行
	//detach:分离，主线程不再与子线程汇合，不再等待子线程
	//detach后，子线程和主线程失去关联，驻留在后台，由C++运行时库接管，执行完后制动回收
	Thread1.detach();

	//(4)joinable()判断是否可以成功使用join()或者detach()
	//如果返回true，证明可以调用join()或者detach()
	//如果返回false，证明调用过join()或者detach()，join()和detach()都不能再调用了
	if (Thread1.joinable())
	{
		cout << "可以调用可以调用join()或者detach()" << endl;
	}
	else
	{
		cout << "不能调用可以调用join()或者detach()" << endl;
	}

	cout << "Hello World!" << endl;

	return 0;

}

//其他创建线程的方法
/*
//1
class Ta
{
public:
	void operator()()
	{
		cout << "我的线程开始运行" << endl;
		//-------------
		//-------------
		cout << "我的线程运行完毕" << endl;
	}
};

//main函数里的：
	Ta ta;
	thread Thread1(ta);
	Thread1.join();

//2
//main函数中
auto lambdaThread = [] {
		cout << "我的线程开始执行了" << endl;
		//-------------
		//-------------
		cout << "我的线程开始执行了" << endl;
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
//main函数里
    //第一个&意思是取址，第二个&意思是引用，相当于std::ref(s)
    //thread oneobj(&Data_::SaveMsh,s)传值也是可以的
    //在其他的构造函数中&obj是不会代表引用的，会被当成取地址
    //调用方式：对象成员函数地址，类实例，[成员函数参数]
	//第二个参数可以传递对象s，也可以传递引用std::ref(s)或&s
	//传递s，会调用拷贝构造函数在子线程中生成一个新的对象
	//传递&，子线程中还是用的原来的对象，所以就不能detach，因为主线程运行完毕会把该对象释放掉

	Data_ s;
    thread oneobj(&Data_::SaveMsh,&s);
    thread twoobj(&Data_::GetMsg,&s);
    oneobj.join();
    twoobj.join();



*/


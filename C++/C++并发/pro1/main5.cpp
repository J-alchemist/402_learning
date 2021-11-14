#include <iostream>
#include <future>
using namespace std;
class A {
public:
	int mythread(int mypar) {
		cout << mypar << endl;
		return mypar;
	}
};


int mythread() {
	cout << "mythread() start" << "threadid = " << std::this_thread::get_id() << endl;
	std::chrono::milliseconds dura(2000);
	std::this_thread::sleep_for(dura);
	cout << "mythread() end" << "threadid = " << std::this_thread::get_id() << endl;
	return 5;
}


int main5() {
	A a;
	int tmp = 12;
	cout << "main" << "threadid = " << std::this_thread::get_id() << endl;
	std::future<int> result1 = std::async(mythread);
	cout << "continue........" << endl;
	//cout << result1.get() << endl; //卡在这里等待mythread()执行完毕，拿到结果

	//类成员函数
//	std::future<int> result2 = std::async(&A::mythread, &a, tmp); //第二个参数是对象引用才能保证线程里执行的是同一个对象
//	cout << result2.get() << endl;
   //或者result2.wait();
	cout << "good luck" << endl;

	return 0;

}



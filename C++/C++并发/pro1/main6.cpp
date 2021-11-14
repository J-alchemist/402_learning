#include <iostream>
#include <thread>
#include <atomic>

using namespace std;

std::atomic<int> g_count(0); //封装了一个类型为int的 对象（值）

void mythread1() {
	for (int i = 0; i < 2000000; i++) {

         //支持的原子操作
		g_count++;


		//虽然gg_count使用了原子操作模板，但是这种写法既读又写，
		 //会导致计数错误
         //gg_count = gg_count + 1;

	}



}

/*
原子操作之后，每个线程都会执行2000000次
*/

int main6() {

	std::thread t1(mythread1);
	std::thread t2(mythread1);
	t1.join();
	t2.join();
	cout << "正常情况下结果应该是400000次，实际是" << g_count << endl;

}

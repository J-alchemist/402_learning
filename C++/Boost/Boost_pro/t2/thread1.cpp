#include <boost/thread.hpp> 
#include <iostream> 
#include <boost/timer.hpp>

using namespace std;
using namespace boost;

void Mywait(int seconds) ;
void Mythread() ;
void Mythread2() ;

int main(int argc, char** argv) 
{ 
/*
//创建线程
  	boost::thread t(Mythread); //新线程
  	t.join(); //阻塞调用：它可以暂停当前线程，直到调用 join() 的线程运行结束
	Mythread();//main函数的线程
*/
//中断线程
	std::cout << boost::this_thread::get_id() << std::endl;//打印主线程id 
 	boost::thread t(Mythread2); //新的线程开始执行
  	Mywait(3); //主线程等待3s
  	t.interrupt(); //在中断点，中断相应的线程
 	t.join();



	return 0;
} 
//------------------
void Mywait(const int ns) 
{ 
	  boost::this_thread::sleep(boost::posix_time::seconds(ns)); //sleep()函数提供线程的中断点

} 

void Mythread() 
{ 
	  for (int i = 1; i <= 5; ++i) 
	  { 
	    Mywait(1); 
	    cout << i << endl; 
	  } 
} 

void Mythread2() 
{ 
  std::cout << boost::this_thread::get_id() << std::endl;//打印线程id 
  try //正常运行
  { 
    for (int i = 1; i <= 5; ++i) 
    { 
      Mywait(1); 
      cout << i << endl; 
    } 
  } 
  catch (boost::thread_interrupted&) //异常捕获
  { 
	cout << "boost::thread_interrupted ! " << endl;
  } 
} 


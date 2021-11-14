#include <boost/thread.hpp> 
#include <iostream> 
#include <boost/timer.hpp>

using namespace std;
using namespace boost;

void Mywait(int seconds) ;
void Mythread() ;

boost::mutex mutex1; //多线程程序使用所谓的互斥对象来同步, boost::Thread提供的一种互斥类
boost::timed_mutex mutex2;

int main(int argc, char** argv) 
{ 
	  boost::thread t1(Mythread); 
	  boost::thread t2(Mythread); 
	  t1.join(); 
 	  t2.join(); 	

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
	/*
		//法1、2	
		//mutex1.lock(); 
		{
		boost::lock_guard<boost::mutex> lock(mutex1); //创建即加锁，作用域结束自动析构并解锁，无需手工解锁
	    cout <<  "Thread->" << boost::this_thread::get_id()<< ":" << i << endl; 
		}
		//mutex1.unlock(); 
	*/
		//法3
		boost::unique_lock<boost::timed_mutex> lock(mutex2, boost::try_to_lock);//尝试获得互斥量
		if(!lock.owns_lock())//未获得
			lock.timed_lock(boost::get_system_time() + boost::posix_time::seconds(1));//等待1s时间取尝试获得
		std::cout << "Thread->" << boost::this_thread::get_id() << ": " << i << std::endl;

		// boost::timed_mutex* m = lock.release(); //手动释放（其可以自动释放，可注释）
   		// m->unlock(); 
	  } 
} 
//法1：mutex1.lock(); mutex1.unlock(); 
//法2：boost::lock_guard<boost::mutex> lock(...);
//法3：boost::unique_lock<boost::timed_mutex> lock(...);	//独占锁

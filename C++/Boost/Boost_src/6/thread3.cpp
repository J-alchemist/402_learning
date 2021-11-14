#include <boost/thread.hpp> 
#include <iostream> 
#include <vector> 
#include <cstdlib> 
#include <ctime> 

using namespace std;
using namespace boost;

std::vector<int> v_random_numbers; 
boost::mutex mutex1; //独立互斥量
boost::shared_mutex mutex2; //共享互斥量
boost::condition_variable_any cond; //条件变量,同步线程不等待

void Myfill() 
{ 
  std::srand(static_cast<unsigned int>(std::time(0))); 
  for (int i = 0; i < 3; ++i) 
  { 
    boost::unique_lock<boost::mutex> lock(mutex1); 
    v_random_numbers.push_back(std::rand()); 
    cond.notify_all();//唤醒每个哪些正在分别通过调用wait() 等待此通知的线程
    cond.wait(mutex1); //会释放相应的被参数传入的互斥量
  } 
} 

void Myprint() 
{ 
  std::size_t next_size = 1; 
  for (int i = 0; i < 3; ++i) 
  { 
    boost::unique_lock<boost::mutex> lock(mutex1); 
    while (v_random_numbers.size() != next_size) 
    	cond.wait(mutex1); 

    cout << v_random_numbers.back() << endl; 
    ++next_size; 
    cond.notify_all(); 
  } 
} 


int main(int argc, char** argv) 
{ 
	  boost::thread t1(Myfill); //独占锁，产生数据
	  boost::thread t2(Myprint); 

	  t1.join(); 
	  t2.join(); 



	  return 0;
}





#include <boost/interprocess/managed_shared_memory.hpp> 
#include <boost/interprocess/sync/named_mutex.hpp> 
#include <boost/interprocess/sync/named_condition.hpp> 
#include <boost/interprocess/sync/scoped_lock.hpp> 
#include <iostream> 

using namespace std;
using namespace boost;

int main(int argc, char** argv) 
{ 

  boost::interprocess::managed_shared_memory managed_shm(boost::interprocess::open_or_create, "shm", 1024); 

  int *i = managed_shm.find_or_construct<int>("Integer")(0); 
//命名对象
  boost::interprocess::named_mutex named_mtx(boost::interprocess::open_or_create, "mtx"); 
  boost::interprocess::named_condition named_cnd(boost::interprocess::open_or_create, "cnd"); //命名条件变量
// boost::interprocess::interprocess_condition *cnd = managed_shm.find_or_construct<boost::interprocess::interprocess_condition>("cnd")(); //匿名条件变量
  boost::interprocess::scoped_lock<boost::interprocess::named_mutex> lock(named_mtx); //区域锁
  while (*i < 10) 
  { 
    if (*i % 2 == 0) //偶数
    { 
      ++(*i); 
      named_cnd.notify_all(); //通知其他进程
      named_cnd.wait(lock); //释放锁
    } 
    else //奇数
    { 
      cout << *i << endl; 
      ++(*i); 
      named_cnd.notify_all(); 
      named_cnd.wait(lock); 
    } 
  } 

//销毁
  named_cnd.notify_all(); 
  boost::interprocess::shared_memory_object::remove("shm"); 
  boost::interprocess::named_mutex::remove("mtx"); 
  boost::interprocess::named_condition::remove("cnd"); 

  return 0;


}


 

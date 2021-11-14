#include <boost/interprocess/managed_shared_memory.hpp> 
#include <boost/interprocess/sync/named_mutex.hpp> 
#include <boost/interprocess/sync/interprocess_mutex.hpp>
#include <iostream> 

using namespace std;
using namespace boost;

/*共享内存中使用容器*/

int main(int argc, char** argv) 
{ 

  boost::interprocess::managed_shared_memory managed_shm(boost::interprocess::open_or_create, "shm", 1024); 

  int *i = managed_shm.find_or_construct<int>("Integer")(0); 
//创建并使用一个命名互斥对象
  boost::interprocess::named_mutex named_mtx(boost::interprocess::open_or_create, "mtx"); 
  named_mtx.lock(); 

  ++(*i); 
  cout << *i << endl; 

  named_mtx.unlock(); 
//创建并使用一个匿名对象
  boost::interprocess::managed_shared_memory managed_shm2(boost::interprocess::open_or_create, "shm2", 1024); 

  int *i2 = managed_shm.find_or_construct<int>("Integer2")(0); 

  boost::interprocess::interprocess_mutex *mtx2 = managed_shm2.find_or_construct<boost::interprocess::interprocess_mutex>("mtx2")(); 
  
  mtx2->lock(); 
  ++(*i2); 
  cout << *i2 << endl; 
  mtx2->unlock(); 

//清理共享内存
  if(*i>10 || *i2>10)
  {
     boost::interprocess::shared_memory_object::remove("shm"); 
     boost::interprocess::shared_memory_object::remove("shm2");

  }

  return 0;


}


 

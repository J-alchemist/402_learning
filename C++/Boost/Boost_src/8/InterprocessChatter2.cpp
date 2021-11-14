#include <boost/interprocess/managed_shared_memory.hpp> 
#include <boost/interprocess/allocators/allocator.hpp> 
#include <boost/interprocess/containers/string.hpp> 
#include <boost/interprocess/containers/vector.hpp>// boost::interprocess::vector
#include <boost/interprocess/containers/map.hpp>//boost::interprocess::map
#include <iostream> 

using namespace std;
using namespace boost;

/*共享内存中使用容器*/

int main(int argc, char** argv) 
{ 
  boost::interprocess::shared_memory_object::remove("Highscore"); 

  boost::interprocess::managed_shared_memory managed_shm(boost::interprocess::open_or_create, "Highscore", 1024); 

  typedef boost::interprocess::allocator<char, boost::interprocess::managed_shared_memory::segment_manager>  CharAllocator; //定义段管理器，负责管理位于托管共享 内存之内 的 内存 （共享内存中用new分配的）
  typedef boost::interprocess::basic_string<char, std::char_traits<char>, CharAllocator>  string; 

  string *s = managed_shm.find_or_construct<string>("String")("Hello!", managed_shm.get_segment_manager()); 

  s->insert(5, " world"); //第5个元素位置开始插入，o后面开始，！退到最后
  cout << *s << endl; 


  return 0;


}


 

#include <boost/interprocess/shared_memory_object.hpp> 
#include <boost/interprocess/mapped_region.hpp> 
#include <boost/interprocess/managed_shared_memory.hpp> 
#include <iostream> 

using namespace std;
using namespace boost;


int main(int argc, char** argv) 
{ 
/*construct出错情况*/
    boost::interprocess::shared_memory_object::remove("Highscore"); 

    boost::interprocess::managed_shared_memory managed_shm(boost::interprocess::open_or_create, "Highscore", 1024); 
  try 
  { 
//给定名称的对象已经在托管的共享内存中
    int *i = managed_shm.construct<int>("Integer")(99);     
    int *i1 = managed_shm.find_or_construct<int>("Integer")(20);//find_or_construct：存在就找到，不存在就构建，存在的话赋值20不起作用，不存在构建20才起作用，等于construct+find
	cout << *i1 <<endl;

//超过托管内存的大小量 
  int *i2 = managed_shm.construct<int>("Integer2")[4096](99); 
  
  } 
  catch (boost::interprocess::bad_alloc &ex) 
  { 
	cerr << ex.what() << endl; //标准错误输出

	if(ex.what() == "boost::interprocess::bad_alloc")	
	{
    
	  //managed_shm.destroy_ptr<int>(i2);//i2指针的作用域限制再量try{}里，此处无法识别到i2指针，但用法这样用
	  managed_shm.destroy<int>("Integer2"); //摧毁后再查找，p指针为空
	  std::pair<int*, std::size_t> p = managed_shm.find<int>("Integer2"); 

	  cout << p.first << endl; 	
        }
  } 


  return 0;


}


 

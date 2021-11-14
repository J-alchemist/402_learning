#include <boost/interprocess/shared_memory_object.hpp> 
#include <boost/interprocess/mapped_region.hpp> 
#include <boost/interprocess/managed_shared_memory.hpp> 
#include <iostream> 

using namespace std;
using namespace boost;

/*使用共享内存通常是进程间通讯最快的形式*/

int main(int argc, char** argv) 
{ 

  boost::interprocess::shared_memory_object  shdmem(boost::interprocess::open_or_create, 
      "Highscore", boost::interprocess::read_write); 
     
	//建立一个共享内存，属性（共享内存如果存在就将其打开，否则创建之），唯一标识，其他进程的权限
      
  shdmem.truncate(1024); //请求共享内存的大小, rw属性时才可调用，可从复多次                                      
  cout <<  shdmem.get_name()  << ": "; //获取名称

  boost::interprocess::offset_t  size; 
  if (shdmem.get_size(size)) //获取大小
    cout << size << " Bytes" << endl;
//地址映射
  boost::interprocess::mapped_region region1(shdmem, boost::interprocess::read_write);	 //read_write权限
  int *i1 = static_cast<int*>(region1.get_address()); 
  *i1 = 99;
  cout << region1.get_address() <<endl;
//另一端映射，可以fork一个子进程，来进行共享空间的访问
  boost::interprocess::mapped_region region2(shdmem, boost::interprocess::read_only); 	 //read_only权限
  int *i2 = static_cast<int*>(region2.get_address()); 
  cout << region2.get_address() <<endl;//共享空间映射到具体进程的地址不同，但共享的仍是同一个空间
  cout << *i2 << endl;

//删除共享内存
  bool isremoved = boost::interprocess::shared_memory_object::remove("Highscore"); 
  cout << isremoved << endl;

		//******托管共享内存******//
 boost::interprocess::managed_shared_memory managed_shm(boost::interprocess::open_or_create, "Highscore", 1024);
 
 // int *i = managed_shm.construct<int>("Integer")(99); //创建一个名为"Integer"的int型对象，值为99
 // cout << *i << endl; 
  int *i = managed_shm.construct<int>("Integer")[3](10);//创建10个数int型数组，元素为99
  i[1] = 20; 
  i[2] = 30;
  cout << i[0] << " " << i[1] << " " << i[2] << endl; 
  
  std::pair<int*, std::size_t> p = managed_shm.find<int>("Integer"); 
  if (p.first) //为0未找到
  {
    cout << *p.first << " " << *(p.first+1) << " " << *(p.first+2)<< endl; //数据
    cout << p.second << endl; //个数
  }



  return 0;


}


 

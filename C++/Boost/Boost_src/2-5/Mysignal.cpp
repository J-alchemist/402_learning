#include <iostream> 
#include <boost/signals2.hpp> 
#include <boost/function.hpp> 
#include <boost/bind.hpp>
#include <memory> 

using namespace std;
using namespace boost;

void func(int a) 
{ 
  cout << "Hello, world!" << a << endl; 
} 

void func2(int a) 
{ 
  cout << "Today：2021/7/" << a << endl; 
} 

void func3() 
{ 
  cout << "Nice day for study boost lib!"  << endl; 
} 

class world : 
	public boost::signals2::trackable//使得一旦对象 w 被销毁，连接就会自动释放
{ 
  public: 
    void hello() const 
    { 
      cout << "Hello, world!" << endl; 
    } 
};
//main
int main(int argc, char** argv) 
{ 
	  int a1=20;
	/*单个绑定*/
//boost::signals2实现
/*	
	  boost::signals2::signal<void (int)> s; 
	  s.connect(func); 
	  s(a1); //触发信号s，并传递参数
//boost::function实现	  
	  boost::function<void (int)> f; 
 	  f = func; 
  	  f(a1); 
*/
	/*多函数绑定，只能信号实现*/   
/*	boost::signals2::signal<void (int)> ss;
	ss.connect(0, func);
	ss.connect(1, func2);
	//ss.disconnect(func);//解除绑定
	//ss.num_slots();//返回该信号关联的函数数量
	//ss.disconnect_all_slots();//解邦所有函数
	ss(a1);

	//连接管理boost::signals::connection
  	boost::signals2::signal<void ()> s2; 
	boost::signals2::connection c2=s2.connect(func3);
	s2();
	c2.disconnect();//解除绑定
	s2();
*/
	/*使用 Boost.Bind 将一个对象的方法关联至一个信号*/
	boost::signals2::signal<void ()> sx; 
	{//表示auto_ptr作用域
		std::auto_ptr<world>  w(new world());
		sx.connect( boost::bind(&world::hello, *w.get()) ); 	//&为取地址,绑定类的成员函数方法
	}
	cout << sx.num_slots() << endl; 
	sx(); 
	
	return 0;
} 

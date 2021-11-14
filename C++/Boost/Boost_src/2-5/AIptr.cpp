#include <iostream> 
#include <boost/scoped_ptr.hpp> 
#include <boost/scoped_array.hpp> 
#include <boost/shared_ptr.hpp> 
#include <vector>
#include <boost/shared_array.hpp> 
#include <boost/ptr_container/ptr_vector.hpp> 
#include <string>
using namespace std;
using namespace boost;

int main(int argc, char** argv)
{
//---------------------------scoped_ptr作用域指针
	cout << "[scoped_ptr]:" << endl;

	scoped_ptr<string> i(new string); //scoped_ptr<int> i(new int(1));//定义时初始化
	*i = "hello1"; 
	cout << *i << endl;

	*i.get() = "hello2"; 	//= *(i.get())
	cout << *i << endl;
	cout << i.get() << endl;

	i.reset(new string); 
	cout << i.get() << endl;

//---------------------------scoped_array作用域数组
	cout << "[scoped_array]:" << endl;

	scoped_array<int> j(new int[2]); 
	cout << j[0] << " " << j[1] << endl;

	*j.get() = 1; 	//*(j[0].get())=1; 错误
	//j[1] = 2;
	*(j.get()+1) = 2;		//不允许++
	cout << j[0] << " " << j[1] << endl;

  	j.reset(new int[3]);
//---------------------------shared_ptr共享指针
	cout << "[shared_ptr]:" << endl;
	//容器
	std::vector< shared_ptr<int> > v; 
	v.push_back(shared_ptr<int>(new int(1))); 
	v.push_back(shared_ptr<int>(new int(2))); 
	cout << *v[0] << " " << *v[1] <<endl;
	//指针容器，相较于上面的方式，更高效
	boost::ptr_vector<int> v0; 
	v0.push_back(new int(1)); 
	v0.push_back(new int(2));
	cout << v0[0] << " " << v0[1] << " " << &v0 << endl;
	//共享指针
  	shared_ptr<int> i1(new int(1)); 
 	shared_ptr<int> i2(i1); //此处为浅拷贝,地址相同
	cout << i1.get() << " " << i2.get() <<endl;
	cout << *i1 << " " << *i2 <<endl;

  	i2.reset(new int(2));//i2重新分配空间，i1,i2分开
	cout << i1.get() << " " << i2.get() <<endl;
	cout << *i1 << " " << *i2 <<endl;
//---------------------------shared_array共享数组
	cout << "[shared_array]:" << endl;

	shared_array<int> a(new int[2]); 
	shared_array<int> a0(a);
	a[0] = 10; 
	a[1] = 20; 
	cout << a[0] << " " << a[1] << endl;
	cout << a0[0] << " " << a0[1] << endl;

	return 0;
}








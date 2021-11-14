#include <iostream> 
#include <boost/scoped_ptr.hpp> 
#include <memory>

using namespace std;
using namespace boost;

int main(int argc, char** argv)
{

//std::auto_ptr
	{//作用域限定
	std::auto_ptr<int> s1(new int(22));	//允许指针传递
	std::auto_ptr<int> s2(s1);//此时s1指向的空间的使用权交付给了s2,s1没有了，再打印s1会出错
		

//	cout << *s1 << endl;
	cout << *s2 << endl;
	}
//---------------理解------------scoped_ptr作用域指针
	scoped_ptr<int> i(new int(2)); //独享对象 
	//scoped_ptr<int> i(s2);	//在auto指针作用域内，允许传递
	cout << *i << endl;
//错误1
	//scoped_ptr<int> i2;
	//i2 = i;		
//错误2
	//scoped_ptr<int> i2(i);
	//cout << *i2 << endl;
	

//普通指针
	int* i0(new int(10));	//都指向同一片区域
	int* i1(i0);

	cout << *i0 << endl;
	cout << *i1 << endl;
	
	//*i0 = 11;	//改变，大家都会变
	*i1 = 11;
	
	cout << *i0 << endl;
	cout << *i1 << endl;
	
	delete i0,i1;	//手动释放


	return 0;
}








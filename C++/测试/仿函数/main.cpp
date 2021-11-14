#include <string>
#include <iostream>
/*
重载函数调用操作符的类，其对象常称为函数对象
函数对象使用重载的()时，行为类似函数调用，也叫仿函数
bool类型的仿函数称为谓词: 一个形参: 一元谓词
*/
using namespace std;

//1、函数对象在使用时，可以像普通函数那样调用, 可以有参数，可以有返回值
class MyAdd
{
public :
	int operator()(int v1, int v2) //仿函数
	{
		return v1 + v2;
	}
};

void test01()
{
	MyAdd myAdd;

	//1
	cout << myAdd(10, 10) << endl;
	//2
	int val =  myAdd(10, 10) ;
    cout << val << endl;

}

//2、函数对象可以有自己的状态
class MyPrint
{
public:
	MyPrint()
	{
		count = 0;
	}
	void operator()(string test)
	{
		cout << test << endl;
		count++; //统计使用次数的状态
	}

	int count;
};
void test02()
{
	MyPrint myPrint;
	myPrint("hello world！");
	myPrint("hello world！");
	myPrint("hello world！");
	cout << "myPrint调用次数为： " << myPrint.count << endl;
}

//3、函数对象可以作为参数传递
void doPrint(MyPrint &mp , string test)
{
	mp(test);
}

void test03()
{
	MyPrint myPrint;
	doPrint(myPrint, "Hello C++");
}

int main() {

	//test01();
	//test02();
	test03();

	system("pause");

	return 0;
}

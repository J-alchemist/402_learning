#ifndef __STL_ALGORITHM__
#define __STL_ALGORITHM__


#include <iostream>
#include <algorithm>
#include <functional>
#include <numeric>

using namespace std;

class TransForm
{
public:
	int operator()(int val)
	{
		return val;
	}

};

class MyPrint
{
public:
	void operator()(int val)
	{
		cout << val << " ";
	}
};

class Greater3
{
public:
	bool operator()(int val)
	{
		return val > 3;
	}
};
//------------
void for_each_test();//遍历
void find_test();   //查找
void sort_test();   //排序
void copy_test();   //拷贝
//------------
void accumulate_test(); //算术库
void set_test();    //集合算法




#endif // __STL_ALGORITHM__

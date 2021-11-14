#include <iostream>
#include <algorithm>
#include <functional> 
#include <numeric>
#include <vector> 
#include <boost/bind.hpp> 
#include <boost/lambda/lambda.hpp>

using namespace std;
using namespace boost;

void print(int i) 
{ 
  cout << i << endl; 
} 
void add(int i, int j) 
{ 
  cout << i + j << endl; 
} 
bool compare(int i, int j) 
{ 
  return i > j; 
} 
void add(int i, int j, std::ostream &os) 
{ 
  os << i + j << std::endl; 
}
//main
int main(int argc, char** argv)
{

	  std::vector<int> v; 
	  v.push_back(1); 
	  v.push_back(3); 
	  v.push_back(2); 
	//遍历，for_each只接受一个参数的函数
	  std::for_each(v.begin(), v.end(), print); 
	//若现在需要传入两个参数的函数
	//法1：函数转化为函数对象（复杂）
	//法2：boost::bind()，此时bind为一元函数
	std::for_each(v.begin(), v.end(), boost::bind(add, _1, 10)); 
	//排序，sort需要一个二元函数
	std::sort(v.begin(), v.end(), boost::bind(compare, _1, _2));
	//std::sort(v.begin(), v.end(), compare);
	std::for_each(v.begin(), v.end(), print); 
	
	//boost::ref()：引用流
	 std::for_each(v.begin(), v.end(), boost::bind(add, 10, _1, boost::ref(std::cout))); 
	
	return 0;

}









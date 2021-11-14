#include <locale> 
#include <iostream> 
#include <cstring>
#include <boost/algorithm/string.hpp> 

using namespace boost;
using namespace std;

int main(int argc, char** argv) 
{ 
	std::locale loc; //访问的全局区域设置
	cout << loc.name() << endl; 
	
	//std::locale::global(std::locale("German")); //更改区域设置	
	//std::string 中的函数是与区域设置无关
	std::string s = "Si Chuan No.1!"; 
	cout << boost::algorithm::to_upper_copy(s, std::locale("C")) << endl; //转为大写，全局区域设置可省虐
	cout << boost::algorithm::lexicographical_compare(s, "Si Chuan No.2!") << endl; //按字典排序	，返回布尔

 	return 0;
}

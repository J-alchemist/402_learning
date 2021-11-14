#ifndef __STL_CONTAINS_H
#define __STL_CONTAINS_H

#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
#include <deque>
#include <stack>
#include <queue>
#include <list>
#include <set>
#include <map>



class CompareReg1
{
public:
	bool operator()(int v1, int v2) {       //仿函数：二元谓词
		return v1 > v2;
	}
};

class CompareReg2
{
public:
	bool operator()(std::string v1, std::string v2) {       //仿函数
		return v1 > v2;
	}
};

using namespace std;

void string_test();
void vector_test();
void deque_test();
void stack_test();
void queue_test();
void list_test();

void set_test();
void map_test();


#endif // __STL_CONTAINS_H

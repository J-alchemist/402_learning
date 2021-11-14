#include "Person.h"

int Person::age = 0; 

//构造函数的重载 
Person::Person(){
}
//采用列表初始化 
Person::Person(string n) : name(n){
	cout << "列表构造完毕！" << endl;
} 
Person::Person(int age, int h, string n){
	this->age = age;
	height = new int(h);
	this->name = n;
	cout << "普通构造完毕！" <<endl;
}
/*
Person::Person(const Person& p) {
		cout << "拷贝构造函数!" << endl;
		//如果不利用深拷贝在堆区创建新内存，会导致浅拷贝带来的重复释放堆区问题
		this->age = p.age;
		
		
}
*/
Person::~Person(){
	
		if (height != NULL)
		{
			delete height;
		}
			cout << "已释放！" <<endl;
}
//------------------------
int Person::getAge(){
	return this->age;
	
}
int Person::getHeight(){
	return *height;
}
string Person::getName(){
	return this->name;
}



#include "Person.h"

int Person::age = 0; 

//���캯�������� 
Person::Person(){
}
//�����б��ʼ�� 
Person::Person(string n) : name(n){
	cout << "�б�����ϣ�" << endl;
} 
Person::Person(int age, int h, string n){
	this->age = age;
	height = new int(h);
	this->name = n;
	cout << "��ͨ������ϣ�" <<endl;
}
/*
Person::Person(const Person& p) {
		cout << "�������캯��!" << endl;
		//�������������ڶ����������ڴ棬�ᵼ��ǳ�����������ظ��ͷŶ�������
		this->age = p.age;
		
		
}
*/
Person::~Person(){
	
		if (height != NULL)
		{
			delete height;
		}
			cout << "���ͷţ�" <<endl;
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



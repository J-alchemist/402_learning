#include <iostream>
#include <string>
#include "Person.h"
using namespace std;

class Animal;
Animal *animal = NULL;

class Animal {
public:

	Animal()
	{
		cout << "Animal ���캯�����ã�" << endl;
	}
	virtual void Speak() = 0;

	//������������virtual�ؼ��֣��������������
	//virtual ~Animal()
	//{
	//	cout << "Animal�������������ã�" << endl;
	//}

	virtual	~Animal();
//	virtual ~Animal() = 0;
};

Animal::~Animal()
{
	cout << "Animal ���������������ã�" << endl;
}

//�Ͱ�����ͨ���麯������һ���������˴���������������Ҳ��һ�������ࡣ���ܹ���ʵ������

class Cat : public Animal {
public:
	Cat(string name)
	{
		cout << "Cat���캯�����ã�" << endl;
		m_Name = new string(name);
	}
	virtual void Speak()
	{
		cout << *m_Name <<  "Сè��˵��!" << endl;
	}
	~Cat()
	{
		cout << "Cat������������!" << endl;
		if (this->m_Name != NULL) {
			delete m_Name;
			m_Name = NULL;
		}
	}

public:
	string *m_Name;
};

void test01()
{
	animal = new Cat("Tom");

	animal->Speak();

    cout << "-----------------" << endl;
	//ͨ������ָ��ȥ�ͷţ��ᵼ�����������������ɾ�������ڴ�й©
	//��ô���������������һ������������
	//���������������������ͨ������ָ���ͷ��������
	delete animal;

	cout << "-----------------" << endl;

}


/*
*/
int main() {

	test01();

    Person p1("gj");

	return 0;
}


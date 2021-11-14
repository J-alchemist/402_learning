#include <iostream>
#include <memory>
#include <string>
#include "myc++class.h"

using namespace std;

int main(int argc, char **argv)
{

	//对象
	{
		PracticeClass::PersonBase p1(22);
		p1.hello_Person();
		cout << p1.getAge() << " " << p1.getName() << endl;
	}
	//指针
	PracticeClass::PersonBase *p3 = new PracticeClass::PersonBase(22, "xxx");
	delete p3; //需要手动释放

	//shared_ptr的初始化方式，第一种最安全
	{
		PracticeClass::PersonBase::ptr p2 = make_shared<PracticeClass::PersonBase>(22, "xxx");
		//PracticeClass::PersonBase::ptr p2(new PracticeClass::PersonBase(22, "xxx"));
		cout << p2->getAge() << " " << p2->getName() << endl; //作用域外自动释放
	}
	//静态
	cout << PracticeClass::PersonBase::height << endl; //静态变量的访问，该类的所有对象共享一份数据
	//cout << p1.height << endl;
	cout << PracticeClass::PersonBase::getWorH("W") << endl;
	//常对象
	{
		const PracticeClass::PersonSon s1(99.9);	//常对象：只能调用常函数（const修饰在函数末尾才是常函数），本质：不允许函数改变this指针的指向
		//cout.precision(3);	//设置浮点位数
		//cout << s1.getScores() << endl;

		s1.setSex("male");
		cout << s1.getSex() << endl;
	}
	//protected
	{
		PracticeClass::PersonSon s2;	//子类访问父类的protected
		s2.setBaseConvert(999);
		cout << s2.getBaseConvert() << endl;
	}

	//多态中父类对象如何调用子类多态函数---(对应)---子类对象调用父类同名函数问题
	//父类指针释放子类堆空间的问题（先有父再有儿）------父类增加虚析构函数
	{
		cout << "--------智能指针如何释放-------------" << endl;
		PracticeClass::PersonBase::ptr op1(new PracticeClass::PersonSon("good1"));
		op1->hello_Person();
		//智能指针释放时，会自动释放掉关联的内存区域
	}
	{
		cout << "--------普通指针如何释放-------------" << endl;
		PracticeClass::PersonBase* op2(new PracticeClass::PersonSon("good2"));
		op2->hello_Person();
		delete op2; 
		//此处不明白可以注释掉PersonBase的析构函数的virtual看子类空间能否释放。
	}

	return 0;
}

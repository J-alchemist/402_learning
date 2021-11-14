#ifndef __LOG_H
#define __LOG_H

#include <iostream>
#include <memory>

namespace PracticeClass
{

    using namespace std;

/*
构造函数不可以使用virtual
析构函数可以使用virtual
tips：一般在函数声明时加override、static、virtual等关键词，再类外实现时不加
    （const函数特殊，需在定义和声明都加）
    若在类内声明+实现，要加修饰的关键字。

    虚函数：虚析构函数-->帮助父类释放子类空间
            虚普通函数-->开放给子类的自由实现的接口

    静态变量：私有：只能由静态函数访问，其余情况正常访问

    常对象：只能调用常函数（const修饰在函数末尾才是常函数）
    常函数：只能修改由mutable修饰的成员
    常函数本质：不允许函数改变this指向的对象（因此无法改变成员值，除了mutable修饰的）
*/
    class PersonBase
    {
    public:
        typedef std::shared_ptr<PersonBase> ptr;
        PersonBase();
        PersonBase(int age, std::string name = "gj"); //只设置一个默认参数时只能在末尾，默认参数只需在声明时设置，定义时不要
        virtual ~PersonBase();                        //虚函数

        virtual void hello_Person();    //子类重写

        int getAge();
        std::string getName();
        static int getWorH(std::string choose); //私有静态变量只能由静态函数访问，公有的正常访问

    private:
        int age;
        std::string name;
        static int weight; //私有静态

    public:
        static int height; //类内声明，类外初始化（在c文件）

    protected:
        int convert;    //子类可以直接访问父类的protected属性的成员


    };
/*
继承了PersonBase类，在一个PersonSon对象释放时，PersonBase析构也会被调用一次
*/
    class PersonSon : public PracticeClass::PersonBase
    { //命名空间不可缺！！

    public:
        typedef std::shared_ptr<PersonSon> ptr;
        PersonSon();
        PersonSon(double s);
        PersonSon(std::string chr);
        ~PersonSon();

        virtual void hello_Person() override; //override：该函数是重写了父类的函数(函数形式完全一致)
        int getBaseConvert();           //子类可以直接访问父类的protected属性的成员
        void setBaseConvert(const int& val);

        double getScores();
        std::string *getCharacter();
        
        void setSex(const string& s) const; //const放在尾后是常函数，放在前头则是修饰返回值
        std::string& getSex() const;   

    private:
        double scores;
        std::string *character = nullptr;

        mutable std::string sex;
        

    };


};

#endif

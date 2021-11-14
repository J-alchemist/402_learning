#include "myc++class.h"
#include "string.h"

namespace PracticeClass
{ //命名空间

    using namespace std;

    int PersonBase::height = 177;
    int PersonBase::weight = 120;

    PersonBase::PersonBase()
    {
        cout << "PersonBase 对象构造！" << endl;
    }
    PersonBase::PersonBase(int a, std::string name) : age(a)
    { //初始化列表

        //this->age = age;
        this->name = name;
    }

    PersonBase::~PersonBase()
    {
        std::cout << "PersonBase 对象释放！" << std::endl;
    }

    void PersonBase::hello_Person()
    {
        std::cout << "hello class: PersonBase" << endl;
    }

    int PersonBase::getAge()
    {

        return age;
    }

    std::string PersonBase::getName()
    {

        return name;
    }

    int PersonBase::getWorH(std::string choose)
    {
        if (choose == "W")
        {
            return weight;
        }
        else if (choose == "H")
        {
            return height;
        }

        return -1;
    }
    //---------------------------------------------
    PersonSon::PersonSon()
    {

        std::cout << "PersonSon 对象构造！" << std::endl;
    }

    PersonSon::PersonSon(std::string chr)
    {

        character = new string(chr);

        std::cout << "PersonSon 对象构造！" << std::endl;
    }

    PersonSon::PersonSon(double s) : scores(s)
    {
    }

    PersonSon::~PersonSon()
    {
        //通过父类指针去释放，会导致子类对象可能清理不干净，造成内存泄漏
        //怎么解决？给基类增加一个虚析构函数
        //虚析构函数就是用来解决通过父类指针释放子类对象
        if (character != nullptr)
        {
            delete character;
            character = nullptr;
        }

        std::cout << "PersonSon 对象释放！" << std::endl;
    }

    double PersonSon::getScores()
    {

        return scores;
    }
    std::string* PersonSon::getCharacter()
    {
        return character;
    }

    void PersonSon::hello_Person() 
    {

        cout << "hello class PersonSon is: " << *(PersonSon::getCharacter()) << endl;
    }

    void PersonSon::setSex(const string& s) const {

        this->sex = s;  //常函数：只能修改由mutable修饰的成员
                        //常对象：只能调用常函数（const修饰在函数末尾才是常函数）
                        //常函数本质：不允许函数改变this指向的对象（因此无法改变成员值，除了mutable修饰的）
    }

    string& PersonSon::getSex() const {
        
        return this->sex;       
    }

    int PersonSon::getBaseConvert() {
        //子类可以直接访问父类的protected属性的成员
        return PersonBase::convert;
    }

    void PersonSon::setBaseConvert(const int& val) {

        //this->PersonBase::convert = val;
        PersonBase::convert = val;
    }


};



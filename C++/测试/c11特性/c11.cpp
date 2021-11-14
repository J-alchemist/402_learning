#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;


int main()
{
    /*1-使用大括号初始化*/
    int value[]{1,2,3};    //int value[] = {1,2,3};
    vector<string> v1 {"sb1", "sb2"};//vector是一种数据结构，string是存储的数据类型
    cout << value[0] << " " << v1[0] << endl;

    /*2-新for循环*/
    for(int i : {1,2,3,4,5}){

        cout << i << " ";
    }
    cout << endl;
    for(auto& i : v1){      //for(string& i : v1)

        cout << i << " ";
    }
    cout << endl;
    /*3- nullptr、auto、decltype */
    int* p = nullptr;   //解决NULL二义性问题
    auto k = 2;
    decltype(k) k2{1};  //自动类型推导  k2为int型
    cout << k << " " << k2 << endl;

    int const a = 10;
    decltype((a)) k3 = k;    //k3为int& 引用型 必须初始化
    cout << a << " " << k3 << endl;

    /* 4- Lambda */
    /*
    []：要想使用的外部变量，传=表示外部所有可用变量
    ()：形参列表
    ->int:返回值
    {}：函数体
    */
    vector<int> iv{5, 4, 3};
    for_each(iv.begin(), iv.end(), [k](int& x)->int{
                                        cout << x+k << endl;
                                        return 0;
                                    }
    );

    /* 5- 变长参数模板 */
    //template<class T1, class T2>

    return 0;
}

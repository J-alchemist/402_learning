#include "stl_algorithm.h"
#include <vector>
#include <ctime>
/*
注意一些内置谓词或函数对象的使用 #include<functional>
*/

using namespace std;

void  for_each_test()
{
    //1-遍历
    vector<int> v1{1,2,3,4,5};
    //for_each( v1.begin(), v1.end(), [](int& x){ cout << x << " "; });//lambda
    for_each( v1.begin(), v1.end(), MyPrint() );//使用一元函数或者函数对象

    //2-搬运
    vector<int> v2;
    v2.resize(v1.size());//目标容器必须要提前开辟空间

    transform(v1.begin(), v1.end(), v2.begin(), TransForm() );//使用函数或者函数对象
    for_each( v1.begin(), v1.end(), MyPrint() );
    for_each( v2.begin(), v2.end(), MyPrint() );
}

void find_test()
{
    //find
    vector<int> v1{1,2,2,4,5};
    vector<int>::iterator it = find(v1.begin(), v1.end(), 5);
    if( it != v1.end() )
            cout << *it << endl;

    //find_if   //条件查找
    it = find_if(v1.begin(), v1.end(), Greater3());  //使用谓词 内置了条件：大于3
    if( it != v1.end() )
            cout << *it << endl;

    //adjacent_find  //查找相邻重复元素,返回相邻元素的第一个位置的迭代器
    it = adjacent_find(v1.begin(), v1.end());
    if( it != v1.end() )
            cout << *it << endl;
    //binary_search     //查找指定元素是否存在，必须有序序列（此为二分查找法）
    bool ret = binary_search(v1.begin(), v1.end(), 6);
    if( ret == true)
        cout << "存在该元素" << endl;
    else
        cout << "不存在该元素" << endl;

    //cout //统计元素个数
    int num = count(v1.begin(), v1.end(), 5);
        cout << num << endl;

    //count_if //按条件统计元素个数
    num = count_if(v1.begin(), v1.end(), Greater3());
        cout << num << endl;
}

void sort_test()
{
    //sort
    vector<int> v1{5,2,2,4,1};
    sort(v1.begin(), v1.end(), greater<int>());   //使用谓词
    for_each( v1.begin(), v1.end(), MyPrint() );
    cout << endl;

    //random_shuffle   //指定范围内的元素随机调整次序
    srand((unsigned int)time(NULL));    //必须产生种子
    random_shuffle(v1.begin(), v1.end());
    for_each( v1.begin(), v1.end(), MyPrint() );
    cout << endl;

    //merge //合并容器 , 必须是有序的  且目标容器要提前开辟空间
    vector<int> v2{1, 2, 3}, v3{2, 4, 9}, v4;
    v4.resize(v2.size() + v3.size());
    merge( v2.begin(), v2.end(), v3.begin(), v3.end() , v4.begin() );
    for_each( v4.begin(), v4.end(), MyPrint() );
    cout << endl;

    //reverse //反转元素（倒着排列）
    reverse( v4.begin(), v4.end() );
    for_each( v4.begin(), v4.end(), MyPrint() );
    cout << endl;

}

void copy_test()
{
    vector<int> v1{1, 2, 3, 4, 5}, v2;
    v2.resize(v1.size() );
    //copy
    copy( v1.begin(), v1.end(), v2.begin());
    for_each( v2.begin(), v2.end(), MyPrint() );
    cout << endl;

    //replace // 将区间内旧元素 替换成 新元素
    replace( v1.begin(), v1.end(), 5, 1);
    for_each( v1.begin(), v1.end(), MyPrint() );
    cout << endl;

    //replace_if    //满足条件的替换
    replace_if( v1.begin(), v1.end(), Greater3(),  1);        //使用谓词
    for_each( v1.begin(), v1.end(), MyPrint() );
    cout << endl;

    //swap  //交换的容器要同种类型
    swap(v1, v2);
    for_each( v1.begin(), v1.end(), MyPrint() );
    for_each( v2.begin(), v2.end(), MyPrint() );

}

void accumulate_test()
{
    vector<int> v1{1, 2, 3, 4, 5};

    //accumulate // 计算容器元素累计总和
    int total = accumulate( v1.begin(), v1.end(), 0 );    //最后一个参数为附加值
        cout << total << endl;

    //fill // 向容器中添加元素 原有的值也会被覆盖
    v1.resize(10);
    fill( v1.begin(), v1.end(), 3);
    for_each( v1.begin(), v1.end(), MyPrint() );
}

void set_test()//  必须的有序序列
{
    vector<int> v1{1, 2, 3, 4, 5};
    vector<int> v2{1, 2, 6, 9, 10};
    vector<int> v3;
    v3.resize( min(v1.size(), v2.size()) );

    //set_intersection // 求两个容器的交集 返回交集最后一个元素的地址
    vector<int>::iterator itEnd = set_intersection( v1.begin(), v1.end(), v2.begin(), v2.end(), v3.begin() );
    for_each( v3.begin(), itEnd, MyPrint() );
    cout << endl;

    //set_union //并集
    v3.resize( v1.size() + v2.size() );
    fill(v3.begin(), v3.begin(), 0);

    itEnd = set_union( v1.begin(), v1.end(), v2.begin(), v2.end(), v3.begin() );
    for_each( v3.begin(), itEnd, MyPrint() );
    cout << endl;

    //set_difference //差集
    v3.resize( max(v1.size() , v2.size()) );
    fill(v3.begin(), v3.begin(), 0);
        //1- v1与v2的差集
    itEnd = set_difference( v1.begin(), v1.end(), v2.begin(), v2.end(), v3.begin() );
    for_each( v3.begin(), itEnd, MyPrint() );
    cout << endl;
    fill(v3.begin(), v3.begin(), 0);
        //1- v2与v1的差集
    itEnd = set_difference( v2.begin(), v2.end(), v1.begin(), v1.end(), v3.begin() );
    for_each( v3.begin(), itEnd, MyPrint() );
    cout << endl;


}













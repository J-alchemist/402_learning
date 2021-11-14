#include "stl_algorithm.h"
#include <vector>
#include <ctime>
/*
ע��һЩ����ν�ʻ��������ʹ�� #include<functional>
*/

using namespace std;

void  for_each_test()
{
    //1-����
    vector<int> v1{1,2,3,4,5};
    //for_each( v1.begin(), v1.end(), [](int& x){ cout << x << " "; });//lambda
    for_each( v1.begin(), v1.end(), MyPrint() );//ʹ��һԪ�������ߺ�������

    //2-����
    vector<int> v2;
    v2.resize(v1.size());//Ŀ����������Ҫ��ǰ���ٿռ�

    transform(v1.begin(), v1.end(), v2.begin(), TransForm() );//ʹ�ú������ߺ�������
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

    //find_if   //��������
    it = find_if(v1.begin(), v1.end(), Greater3());  //ʹ��ν�� ����������������3
    if( it != v1.end() )
            cout << *it << endl;

    //adjacent_find  //���������ظ�Ԫ��,��������Ԫ�صĵ�һ��λ�õĵ�����
    it = adjacent_find(v1.begin(), v1.end());
    if( it != v1.end() )
            cout << *it << endl;
    //binary_search     //����ָ��Ԫ���Ƿ���ڣ������������У���Ϊ���ֲ��ҷ���
    bool ret = binary_search(v1.begin(), v1.end(), 6);
    if( ret == true)
        cout << "���ڸ�Ԫ��" << endl;
    else
        cout << "�����ڸ�Ԫ��" << endl;

    //cout //ͳ��Ԫ�ظ���
    int num = count(v1.begin(), v1.end(), 5);
        cout << num << endl;

    //count_if //������ͳ��Ԫ�ظ���
    num = count_if(v1.begin(), v1.end(), Greater3());
        cout << num << endl;
}

void sort_test()
{
    //sort
    vector<int> v1{5,2,2,4,1};
    sort(v1.begin(), v1.end(), greater<int>());   //ʹ��ν��
    for_each( v1.begin(), v1.end(), MyPrint() );
    cout << endl;

    //random_shuffle   //ָ����Χ�ڵ�Ԫ�������������
    srand((unsigned int)time(NULL));    //�����������
    random_shuffle(v1.begin(), v1.end());
    for_each( v1.begin(), v1.end(), MyPrint() );
    cout << endl;

    //merge //�ϲ����� , �����������  ��Ŀ������Ҫ��ǰ���ٿռ�
    vector<int> v2{1, 2, 3}, v3{2, 4, 9}, v4;
    v4.resize(v2.size() + v3.size());
    merge( v2.begin(), v2.end(), v3.begin(), v3.end() , v4.begin() );
    for_each( v4.begin(), v4.end(), MyPrint() );
    cout << endl;

    //reverse //��תԪ�أ��������У�
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

    //replace // �������ھ�Ԫ�� �滻�� ��Ԫ��
    replace( v1.begin(), v1.end(), 5, 1);
    for_each( v1.begin(), v1.end(), MyPrint() );
    cout << endl;

    //replace_if    //�����������滻
    replace_if( v1.begin(), v1.end(), Greater3(),  1);        //ʹ��ν��
    for_each( v1.begin(), v1.end(), MyPrint() );
    cout << endl;

    //swap  //����������Ҫͬ������
    swap(v1, v2);
    for_each( v1.begin(), v1.end(), MyPrint() );
    for_each( v2.begin(), v2.end(), MyPrint() );

}

void accumulate_test()
{
    vector<int> v1{1, 2, 3, 4, 5};

    //accumulate // ��������Ԫ���ۼ��ܺ�
    int total = accumulate( v1.begin(), v1.end(), 0 );    //���һ������Ϊ����ֵ
        cout << total << endl;

    //fill // �����������Ԫ�� ԭ�е�ֵҲ�ᱻ����
    v1.resize(10);
    fill( v1.begin(), v1.end(), 3);
    for_each( v1.begin(), v1.end(), MyPrint() );
}

void set_test()//  �������������
{
    vector<int> v1{1, 2, 3, 4, 5};
    vector<int> v2{1, 2, 6, 9, 10};
    vector<int> v3;
    v3.resize( min(v1.size(), v2.size()) );

    //set_intersection // �����������Ľ��� ���ؽ������һ��Ԫ�صĵ�ַ
    vector<int>::iterator itEnd = set_intersection( v1.begin(), v1.end(), v2.begin(), v2.end(), v3.begin() );
    for_each( v3.begin(), itEnd, MyPrint() );
    cout << endl;

    //set_union //����
    v3.resize( v1.size() + v2.size() );
    fill(v3.begin(), v3.begin(), 0);

    itEnd = set_union( v1.begin(), v1.end(), v2.begin(), v2.end(), v3.begin() );
    for_each( v3.begin(), itEnd, MyPrint() );
    cout << endl;

    //set_difference //�
    v3.resize( max(v1.size() , v2.size()) );
    fill(v3.begin(), v3.begin(), 0);
        //1- v1��v2�Ĳ
    itEnd = set_difference( v1.begin(), v1.end(), v2.begin(), v2.end(), v3.begin() );
    for_each( v3.begin(), itEnd, MyPrint() );
    cout << endl;
    fill(v3.begin(), v3.begin(), 0);
        //1- v2��v1�Ĳ
    itEnd = set_difference( v2.begin(), v2.end(), v1.begin(), v1.end(), v3.begin() );
    for_each( v3.begin(), itEnd, MyPrint() );
    cout << endl;


}













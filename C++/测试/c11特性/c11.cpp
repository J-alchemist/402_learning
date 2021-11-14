#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;


int main()
{
    /*1-ʹ�ô����ų�ʼ��*/
    int value[]{1,2,3};    //int value[] = {1,2,3};
    vector<string> v1 {"sb1", "sb2"};//vector��һ�����ݽṹ��string�Ǵ洢����������
    cout << value[0] << " " << v1[0] << endl;

    /*2-��forѭ��*/
    for(int i : {1,2,3,4,5}){

        cout << i << " ";
    }
    cout << endl;
    for(auto& i : v1){      //for(string& i : v1)

        cout << i << " ";
    }
    cout << endl;
    /*3- nullptr��auto��decltype */
    int* p = nullptr;   //���NULL����������
    auto k = 2;
    decltype(k) k2{1};  //�Զ������Ƶ�  k2Ϊint��
    cout << k << " " << k2 << endl;

    int const a = 10;
    decltype((a)) k3 = k;    //k3Ϊint& ������ �����ʼ��
    cout << a << " " << k3 << endl;

    /* 4- Lambda */
    /*
    []��Ҫ��ʹ�õ��ⲿ��������=��ʾ�ⲿ���п��ñ���
    ()���β��б�
    ->int:����ֵ
    {}��������
    */
    vector<int> iv{5, 4, 3};
    for_each(iv.begin(), iv.end(), [k](int& x)->int{
                                        cout << x+k << endl;
                                        return 0;
                                    }
    );

    /* 5- �䳤����ģ�� */
    //template<class T1, class T2>

    return 0;
}

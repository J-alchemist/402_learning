#include <iostream>
#include <thread>
#include <vector>

using namespace std;


void TextThread()
{
     cout << "�����߳�" << this_thread::get_id() << endl;
     /*  ��  */
     //cout << "�߳�" << this_thread::get_id() << "ִ�н���" << endl;
}


int main3(){


 //main������,��thread������뵽�����й���
     vector<thread> threadagg;

     for (int i = 0; i < 5; ++i)
     {
         threadagg.push_back(thread(TextThread));
     }
     for (int i = 0; i < 5; ++i)
     {
         threadagg[i].join();
     }

        cout << " ���߳̽����� " << this_thread::get_id() << endl;


     return 0;

}



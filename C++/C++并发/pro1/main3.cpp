#include <iostream>
#include <thread>
#include <vector>

using namespace std;


void TextThread()
{
     cout << "我是线程" << this_thread::get_id() << endl;
     /*  …  */
     //cout << "线程" << this_thread::get_id() << "执行结束" << endl;
}


int main3(){


 //main函数里,把thread对象放入到容器中管理
     vector<thread> threadagg;

     for (int i = 0; i < 5; ++i)
     {
         threadagg.push_back(thread(TextThread));
     }
     for (int i = 0; i < 5; ++i)
     {
         threadagg[i].join();
     }

        cout << " 主线程结束： " << this_thread::get_id() << endl;


     return 0;

}



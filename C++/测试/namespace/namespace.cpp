#include <iostream>

using namespace std;

namespace My_robot {

    int speed = 100;

    bool testfun()
    {
        cout << speed-99 << endl;
    }

};


int main(int argc, char** argv)
{
    cout << "Hello world!" << endl;
    cout << My_robot::speed << endl;
    My_robot::testfun();

    return 0;
}

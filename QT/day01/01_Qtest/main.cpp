#include "mywidget.h"
#include <QApplication>

/*
QT头文件前两字母大写
没有.h后缀
*/
int main(int argc, char *argv[])
{
    /*QApplication应用程序类，只有一个应用程序类的对象，如a*/
    QApplication a(argc, argv);


    /*MyWidget是QWidget的一个子类
     *MyWidget也是窗口类
     *w则是一个窗口
    */
    MyWidget w;
    //窗口显示
    w.show();
    //a.exec()里面有一个死循环，等待事件发生
    return a.exec();
}

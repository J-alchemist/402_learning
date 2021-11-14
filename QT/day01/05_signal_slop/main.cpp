/*功能：CONFIG += C++11
 *Lambda表达式，匿名函数对象
 */

#include "mainwidget.h"
#include <QApplication>
/*
 * 程序执行到定义类对象的语句时，会再执行其析构函数，在执行下条语句
 * 再析构函数里去是实现功能
 * 信号和槽connet();
 */
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    MainWidget w;//析构函数去执行
    w.show();

    return a.exec();//等待事件发生
}

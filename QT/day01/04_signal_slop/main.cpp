/*
 *信号重载：
 *自定义信号和槽函数（带参数）
 *以及如何调用connect
 *并附加qt4的调用的使用方法
 */
#include <QObject>
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

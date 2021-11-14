/*
 * 1)指定父对象 2）必须直接或间接继承于QObject（按f1，查看）
 * 满足以上条件，则程序结束系统将自动delete动态空间
 */


#include "mywidget.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MyWidget w;
    w.show();

    return a.exec();
}

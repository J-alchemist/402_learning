#include "serverwidget.h"
#include <QApplication>
#include "clientwidget.h"

/*
QT += network
CONFIG += C++11（注意没有分号，cao）
QT设计师界面类
*/

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    ServerWidget w;
    w.show();

    ClientWidget w2;
    w2.show();

    return a.exec();
}

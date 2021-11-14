#include "widget.h"
#include <QApplication>
#include "clientfiletcp.h"
/*
tcp传输粘包问题，必须注意！！！
connect嵌套使用情况
*/
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Widget w;
    w.show();

    ClientFileTcp w2;
    w2.show();

    return a.exec();
}

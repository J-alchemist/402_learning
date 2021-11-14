#include "mywidget.h"
#include <QApplication>
/*
在QLable中使用鼠标事件（用户触发）
在Mywidget中使用键盘事件（用户触发）
            定时器事件（自动触发）
QPushbutton中事件的忽略与传递（最终传递给父组件，不是父类）
event()事件分发器
一般情况下都不要抽重写enentFilter()和event()，要处理直接改写处理函数
*/
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MyWidget w;
    w.show();

    return a.exec();
}

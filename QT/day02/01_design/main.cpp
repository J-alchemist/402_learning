#include "mainwindow.h"
#include <QApplication>
/*
 * 添加Qt资源文件，复制路径
 * 自定义一个滑块小空间，并在ui界面使用,使用提升为
 * 信号连接时，函数重载如何强制转换
 * ui界面按钮快捷设计槽函数（选中按钮，右键转到槽）
 * Qt样式表（背景图，颜色设置，一些变化效果）
 */
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    return a.exec();
}

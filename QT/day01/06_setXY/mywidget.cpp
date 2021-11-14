#include "mywidget.h"
#include <QPushButton>
#include <QString>
#include <QDebug>

MyWidget::MyWidget(QWidget *parent)
    : QWidget(parent)
{
    /* 主窗口以桌面左上角为坐标0点
     * 子窗口以父窗口左上角为坐标0点
     * 窗口是以它继承的父窗口右上角为坐标0点
     */
    move(0, 0);//主窗

    QPushButton *b0 = new QPushButton(this);
    b0->setText(QString("youz@_@"));
    //以上两步可以--》 QPushButton *b0 = new QPushButton("youz@_@", this);
    b0->move(100 ,100);
    b0->resize(200, 100);

    QPushButton *b1 = new QPushButton(b0);
    b1->move(10, 10);
    b1->setText("My^_^");

    //setGeometry();//窗口位置坐标，窗口大小
}

MyWidget::~MyWidget()
{

}

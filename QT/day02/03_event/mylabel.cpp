#include "mylabel.h"
#include <QMouseEvent>
#include <QDebug>

Mylabel::Mylabel(QWidget *parent) :
    QLabel(parent)
{
    //设置鼠标初始为激活态
    this->setMouseTracking(true);
}

//鼠标按下
void Mylabel::mousePressEvent(QMouseEvent *ev)
{
    //获取xy坐标
    int i = ev->x();
    int j = ev->y();

    //鼠标左键，右键，中间
//    if(ev->button() == Qt::LeftButton)
//    {}
//    else if(ev->button() == Qt::RightButton)
//    {}
//    else if(ev->button() == Qt::MidButton)
//    {}

    //<center><h1>：居中显示，加粗
        QString text = QString("<center><h1>Mouse Press:(%1, %2)</h1></center>")
                                        .arg(i).arg(j);

        this->setText(text);
}

//鼠标抬起
void Mylabel::mouseReleaseEvent(QMouseEvent *ev)
{
    QString text = QString("<center><h1>Mouse Release:(%1, %2)</h1></center>")
                                    .arg(ev->x()).arg(ev->y());

    this->setText(text);

}

//鼠标移动
void Mylabel::mouseMoveEvent(QMouseEvent *ev)
{
    QString text = QString("<center><h1>Mouse Move:(%1, %2)</h1></center>")
                                    .arg(ev->x()).arg(ev->y());

    this->setText(text);

}

void Mylabel::enterEvent(QEvent *e)
{

    QString text = QString("<center><h1>Mouse enter</h1></center>");
    this->setText(text);

}
void Mylabel::leaveEvent(QEvent *e)
{

    QString text = QString("<center><h1>Mouse leave</h1></center>");

    this->setText(text);

}










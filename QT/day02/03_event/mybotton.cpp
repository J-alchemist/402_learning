#include "mybotton.h"
#include <QPushButton>
#include <QMouseEvent>
#include <QDebug>

Mybotton::Mybotton(QWidget *parent) :
    QPushButton(parent)
{
}


void Mybotton::mousePressEvent(QMouseEvent *ev)
{
    //如果鼠标左键按下
        if(ev->button() == Qt::LeftButton)
        {

            qDebug() << "鼠标左键按下！";
            /* 在此处信号被处理之后，不会往后传，及不会响应mywidget中的clicked信号
             * 若信号一直传递，最终会传给父组件*/

            //若此处调用此函数，则信号会继续传递 //此函数经常用法见closeEvent函数
            //e->ignore();
        }
        else
        {
            QPushButton::mousePressEvent(ev);
        }
}

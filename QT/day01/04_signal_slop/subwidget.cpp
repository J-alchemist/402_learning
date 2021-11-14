#include "subwidget.h"

subwidget::subwidget(QWidget *parent) :
    QWidget(parent)
{
     this->setWindowTitle("子窗口");
     b4.setParent(this);
     b4.setText("切换到主窗口");
     b4.move(100,100);
//按下按钮发送信号
     connect(&b4, &QPushButton::clicked, this, &subwidget::SendSlot);
     resize(400,300);
}
void subwidget::SendSlot()
{
    emit mySignal();
    emit mySignal(250, "i am your sonWin");
}

#include "mywidget.h"
#include "ui_mywidget.h"
#include <QKeyEvent>
#include <QDebug>
#include <QTimerEvent>
#include <QMessageBox>
#include <QEvent>

MyWidget::MyWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MyWidget)
{
    ui->setupUi(this);//ui界面将在这里被调用

    timerID1 = this->startTimer(1000);//每1s启动一次定时器,并将id返回
    timerID2 = this->startTimer(2000);

    //处理按钮信号
    connect(ui->pushButton, &Mybotton::clicked,
            [=]()
            {
                 qDebug() << "按钮被按下";
            }

            );

    ui->label_2->setMouseTracking(true);
    //安装过滤器,指定由this处理
    ui->label_2->installEventFilter(this);
}

//键盘事件key()
void MyWidget::keyPressEvent(QKeyEvent *e)
{
    char keyval = (char)e->key();//本身ascii码，（char）转换为字符型

    switch(keyval)
    {
        case Qt::Key_A: qDebug() << "你好拽啊";
                        break;
         default : qDebug() << "你shabi!";break;
    }
}


void MyWidget::timerEvent(QTimerEvent *e)
{
    static int sec_count = 0;

    if(e->timerId() == timerID1)//如果是1事件
        {

            ui->label->setText(QString("<center><h1>Timer1:%1</h1></center>").arg(sec_count++));
            if(sec_count == 10)
                this->killTimer(timerID1);
        }
    else if(e->timerId() == timerID2)//如果是2事件
    {
        ui->label_2->setText(QString("<center><h1>Timer2:%1</h1></center>").arg(sec_count++));
        if(sec_count == 5)
            this->killTimer(timerID2);


    }


}

void MyWidget::closeEvent(QCloseEvent *e)
{

    int ret = QMessageBox::question(this, "question", "是否需要关闭窗口？");

    if(ret == QMessageBox::Yes)
    {
        e->accept();//处理事件，不传递
    }
    else
    {
        e->ignore();//忽略事件后继续传递

    }



}
//事件分发器
/*
返回true则，事件终止传递
*/
bool MyWidget::event(QEvent *e)
{

//   switch(e->type())//获取事件触发类型,注意类型转换
//   {
//    case QEvent::Close :closeEvent(e);break;
//    case QEvent::MouseMove :mouseMoveEvent(e);break;
//    default:break;

//   }

}
//事件分发器
//要先安装分发器
//返回true则，事件终止传递
bool MyWidget::eventFilter(QObject *obj, QEvent *e)
{
    if(obj == ui->label_2)
    {
        //类型转换,将QEvent*类型的e转换为QMouseEvent*
        QMouseEvent *ev = static_cast<QMouseEvent *>(e);\
        //判断事件
        if(ev->type() == QEvent::MouseMove)
        {
            ui->label_2->setText(QString("Mouse move:(1%, 2%)").arg(ev->x()).arg(ev->y()));
            return true;

        }

    }
    else
    {

        return QWidget::eventFilter(obj, e);
    }

}

MyWidget::~MyWidget()
{
    delete ui;
}

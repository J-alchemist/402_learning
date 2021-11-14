#include "mainwidget.h"
#include <QPushButton>
#include <QDebug>//打印信息头文件

MainWidget::MainWidget(QWidget *parent)
    : QWidget(parent)
{
    b.setParent(this);       //用函数指定父类
    b.setText("关");
    b.move(66,66);

    /*指针使用要分配内存!!!*/
    b2 = new QPushButton(this);   //构造函数指定父类
    b2->setParent(this);
    b2->setText("*_*");
    b2->move(166,166);

    //信号:QPushButton+f1,找signal
    connect(&b, &QPushButton::pressed, this, &MainWidget::close);

    connect(b2, &QPushButton::released, this, &MainWidget::Myslop);

    /**/
    setWindowTitle("主窗口");
    b3.setParent(this);
    b3.setText("切换到子窗口");
    b3.move(90,90);

    connect(&b3, &QPushButton::pressed, this, &MainWidget::ChangeWin);

    //处理子窗口的信号（带参信号）
    //如果信号或者槽函数是用来重载，就用函数指针,与c++不同的是要加上作用域
    //此处只以信号重载为例
    /*框架：(如果fun函数带参数，就将参数列表写在p后，注意fun后没有括号)
        void *p() = &fun;
     */
    //方式①
//    void (subwidget::*p1_Signal)() = &subwidget::mySignal;
//    connect(&w2, p1_Signal, this, &MainWidget::Changeback);

//    void (subwidget::*p2_Signal)(int, QString) = &subwidget::mySignal;
//    connect(&w2, p2_Signal, this, &MainWidget::DealSlot);
    //方式②
    //qt4处理方法：SIGNAL()、SLOT()
    //槽函数必须用slots关键字来修饰，否则在SLOT()中无法找到
    connect(&w2, SIGNAL(mySignal()), this, SLOT(Changeback()));
    connect(&w2, SIGNAL(mySignal(int,QString)), this, SLOT(DealSlot(int,QString)));

    //设置窗口大小
    resize(400,300);
}

void MainWidget::DealSlot(int a, QString str)
{
    //qDebug()与cout用法一样
    //x.toUtf8().data();转换成char显示
    qDebug() << a << str.toUtf8().data();



}

void MainWidget::Myslop()
{
    b2->setText("我变了");

}

void MainWidget::ChangeWin()
{
//子窗口显示
    w2.show();
//主窗口隐藏
    this->hide();
}
void MainWidget::Changeback()
{
    //主窗口显示
        this->show();
    //子窗口隐藏
        w2.hide();
}
MainWidget::~MainWidget()
{

}

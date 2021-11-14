#include "mainwidget.h"
#include <QPushButton>
#include <QDebug>
/*
 * 选项--》文本编辑器--》utf-8字符
 *
 */
MainWidget::MainWidget(QWidget *parent)
    : QWidget(parent)
{

    b.setParent(this);       //用函数指定父类
    b.setText("关");
    b.move(66,66);

    /*指针使用要分配内存!!!*/
    b2 = new QPushButton(this);   //构造函数指定父类，并未指针分配空间
    b2->setParent(this);
    b2->setText("*_*");
    b2->move(166,166);

    //信号:QPushButton+f1,找signal
    connect(&b, &QPushButton::pressed, this, &MainWidget::close);
    /*
     * 信号发送者（指针类型）
     * 发送者类名::信号名字
     * 信号接收者（指针类型）
     * 接收者类名::槽函数（信号处理函数）
     */
    /*信号没有返回值，槽函数就没用返回值
     *自定义槽函数，一般声明在类里，实现在其.cpp文件
     */
    connect(b2, &QPushButton::released, this, &MainWidget::Myslop);

    /**/
    setWindowTitle("主窗口");
    b3.setParent(this);
    b3.setText("切换到子窗口");
    b3.move(90,90);

    //独立显示子窗口（因为子窗口没有关联父类）
    //w2.show();
    //修改为子主窗口相互切换
    connect(&b3, &QPushButton::pressed, this, &MainWidget::ChangeWin);

    //处理子窗口的信号
    connect(&w2, &subwidget::mySignal, this, &MainWidget::Changeback);

    //Lambda表达式，匿名函数对象
    QPushButton *b5 = new QPushButton(this);
    b5->setText("Lambda！");
    b5->move(150,150);
    //信号发送者，信号类型
    /*值传递：复制副本操作
     *引 用：对原体操作
        {}:要执行的函数体
        []:要作用到这函数体的外部信号（变量）
        [=]:表示外部局部变量，和类中所以成员以值传递(即这些变量只读，不可再函数体进行修改)方式传进来
        [this]:类中所有成员以值传递
            ！！！破：括号后加mutable修饰
        [&]:表示外部局部变量以引用方式传递，外部定义为指针时，慎用！！！
        ():信号函数的参数
    */
    //此处void clicked(bool checked = false)
    connect(b5, &QPushButton::clicked,
            [=](bool a) mutable
            {
                qDebug() << a;  //打印时就会打印false
                                //所以即为信号函数参数会传递给()列表里面的参数

            }


            );


    //设置窗口大小
    resize(400,300);
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

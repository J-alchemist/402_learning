#include "mainwidget.h"
#include <QPushButton>

/*
 * 选项--》文本编辑器--》utf-8
 *
 */
MainWidget::MainWidget(QWidget *parent)
    : QWidget(parent)
{
    /*
    //直接再在构造函数里定义是局部变量不行，必须定义在类里，主函数才可以调用生效
    QPushButton b;
    b.setParent(this);
    b.setText("-_-");
    b.move(66,66);
·   */
    b.setParent(this);       //用函数指定父类
    b.setText("关");
    b.move(66,66);

    /*指针使用要分配内存!!!*/
    b2 = new QPushButton(this);   //构造函数指定父类
    b2->setParent(this);
    b2->setText("hello world");
    b2->move(166,166);

    //信号:QPushButton+f1,找signal
    connect(&b, &QPushButton::pressed, this, &MainWidget::hide);
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

    //设置窗口大小
    resize(400,300);
}

void MainWidget::Myslop()
{
   // b2->setText("我变了");

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

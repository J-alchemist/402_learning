#include "mainwindow.h"
#include <QMenu>
#include <QMenuBar>
#include <QAction>
#include <QDialog>//模态对话框头文件
#include <QDebug>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    QMenuBar *mBar = menuBar();
    setMenuBar(mBar);
    QMenu *mymenu = mBar->addMenu("File");

    QAction *p1 = mymenu->addAction("模态对话框");
    connect(p1, &QAction::triggered,
            [=]()
            {
                QDialog dlg;
                dlg.exec();
                qDebug() << "用户已操作";
            }
            );

    QAction *p2 = mymenu->addAction("非模态对话框");
    connect(p2, &QAction::triggered,
            [=]()
            {
        /*这样写会导致每进入这个页面就会动态分配一次内存，导致内存占用过多*/
//              QDialog *dlg2 = new QDialog(this);

        //方式1，QDialog dlg2定义在MainWindow类里，作为类成员就不会释放
        //。。。。。。。
        //方式2  调用特有函数，手动释放（不指定父对象）
                QDialog *dlg2 = new QDialog;
                dlg2->setAttribute(Qt::WA_DeleteOnClose);//每次关闭就释放


                dlg2->show();
                qDebug() << "非模态对话框，可随意操作页面";
            }
            );

}

MainWindow::~MainWindow()
{

}

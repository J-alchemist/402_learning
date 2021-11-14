#include "mainwindow.h"
#include <QMenu>
#include <QMenuBar>
#include <QAction>
#include <QDialog>//模态对话框头文件
#include <QDebug>
#include <QMessageBox>//标准对话框  //f1->Static Public Members
#include <QFileDialog>

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
    //标准对话框
    QAction *p3 = mymenu->addAction("关于对话框");
    connect(p3, &QAction::triggered,
            [=]()
            {
               QMessageBox::about(this,  "about", "关于qt");
               //父对象，标题，内容
            }
            );

    QAction *p4 = mymenu->addAction("问题对话框");
    connect(p4, &QAction::triggered,
            [=]()
            {
              int ret = QMessageBox::question(this,  "question", "are you ok?", QMessageBox::Cancel | QMessageBox::Ok);
               //父对象，标题，内容, 按钮
              switch(ret)
              {
                case QMessageBox::Cancel:
                  qDebug() << "已拒绝！";
                  break;
                case QMessageBox::Ok:
                  qDebug() << "已接受！";
                  break;
                default : break;
              }
            }
            );
    QAction *p5 = mymenu->addAction("文件对话框");
    connect(p5, &QAction::triggered,
            [=]()
            {
               QString path = QFileDialog::getOpenFileName(this, "open file", "../",
                                                           "souce1(*.cpp *.h);;"
                                                           "souce2(*.txt);;"
                                                           "all(*.*)"
                                                            );
               //父对象，标题，打开的路径, 过滤文件选项
               qDebug() << path;
            }
            );


}

MainWindow::~MainWindow()
{

}

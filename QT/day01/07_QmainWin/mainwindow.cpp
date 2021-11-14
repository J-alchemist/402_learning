#include "mainwindow.h"
/*
 * 对应函数按f1看帮助，找头文件及返回值
 */
#include <QMenuBar>//菜单栏头文件
#include <QMenu>
#include <QAction>
#include <QDebug>
#include <QToolBar>
#include <QPushButton>
#include <QStatusBar>
#include <QLabel>
#include <QTextEdit>
#include <QDockWidget>
/*
分割线添加要在创建选项之后
*/
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)//便于再指定父对象时的连接
{
    /*1、菜单栏（一个空白长条）  *mBar  */
    QMenuBar *mBar = menuBar();
    setMenuBar(mBar);//设置一下菜单栏默认值（可不要）
    //添加菜单选项        *pFile
    QMenu *pFile = mBar->addMenu("File");

    //添加菜单项（动作） *pnNew
    QAction *p1New = pFile->addAction("New");
    connect(p1New, &QAction::triggered,
            [=]()
            {
                qDebug() << "新建成功！";
            }
            );
    pFile->addSeparator();//添加分割线
    QAction *p2New = pFile->addAction("Open");
    connect(p2New, &QAction::triggered,
            [=]()
            {
                qDebug() << "打开成功！";
            }
            );
    /*2、工具栏，就是菜单项的快捷方式   *toolBar */
    QToolBar *toolBar = addToolBar("toolBar");

    //添加快捷键（将之前动作的指针拿过来就可以）
    //添加按键
    toolBar->addAction(p1New);

    QPushButton *b = new QPushButton(this);
    b->setText("o_o");
    //添加小控件（将按钮作为toolBar的小控件）
    toolBar->addWidget(b);
    connect(b, &QPushButton::clicked,
            [=]()
            {
                b->setText("x_x");
            }
            );
    /*3、状态栏  *sBar */
//    QStatusBar *sBar = new QStatusBar(this);//自己创建，但是有statusBar()函数就不用这样创建
    QStatusBar *sBar = statusBar();//申请一个状态栏
    //添加标签，用于字符显示
    QLabel *laber = new QLabel(this);
    laber->setText("normal");

    sBar->addWidget(laber);
    //快速添加
    sBar->addWidget(new QLabel("2", this));//左到右
    sBar->addPermanentWidget(new QLabel("1", this));//右到左

    /*4、核心控件（编辑区）  *textEdit  */
    QTextEdit *textEdit = new QTextEdit(this);
    setCentralWidget(textEdit);//改变编辑区设为中心区域

    /*5、浮动窗口(拖动框)  *mydock  */
    QDockWidget *mydock = new QDockWidget(this);
    addDockWidget(Qt::LeftDockWidgetArea, mydock);

    //给浮动框添加可编辑区（类似上面）
    QTextEdit *textEdit2 = new QTextEdit(this);
    mydock->setWidget(textEdit2);

}

MainWindow::~MainWindow()
{

}

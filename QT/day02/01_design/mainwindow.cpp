#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include <QPushButton>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    //以下写代码格式：ui->对象名->接口函数
    //qt样式表
    //设置颜色，QLabel是label_2该对象的域名
    //前景色color或者自己配色color:rgb(255, 0 ,0)
    //背景色background-color
    //背景图border-image:url(图片路径)
    //this作为对象，则是全局该类型都设置成统一格式（对有图片区域不起作用）
    this->setStyleSheet("QMainWindow{"
                                "color:red;"
                                "background-color:white;"
                                "border-image:url(://Frame.jpg)"
                                "}"
                        );
    //处理一些信号
    ui->pushButton->setStyleSheet("QPushButton:pressed{"
                                     "border-image:url(://butterfly.png)"
                                                     "}"
                         );

}

MainWindow::~MainWindow()
{
    delete ui;
}
//登录验证，获取编辑栏内容
void MainWindow::on_pushButton_clicked()
{

    if(ui->lineEdit->text() == QString("guojianbaba") && ui->lineEdit_3->text() == QString("123456"))
    {
        qDebug() << "登录成功！";
    }
    else
    {
        //清除内容并定位光标
        ui->lineEdit->clear();
        ui->lineEdit_3->clear();
        ui->lineEdit->setFocus();
        qDebug() << "非法用户！";

    }
}

void MainWindow::on_pushButton_2_clicked()
{
    qDebug() << "正在退出！";
    this->close();

}

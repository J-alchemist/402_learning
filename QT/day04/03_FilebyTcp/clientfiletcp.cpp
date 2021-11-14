#include "clientfiletcp.h"
#include "ui_clientfiletcp.h"
#include <QDebug>
#include <QMessageBox>
#include <QHostAddress>
#include <QDir>

ClientFileTcp::ClientFileTcp(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ClientFileTcp)
{
    ui->setupUi(this);

    tcpSocket = new QTcpSocket(this);

    setWindowTitle("客户端");
    start_flag = true;
    ui->progressBar->setValue(0);//设置进度调

    connect(tcpSocket, &QTcpSocket::connected,
    [=]()
    {
        //提示连接成功
        ui->textEdit->clear();
        ui->textEdit->append("和服务器连接成功，等待服务器传送文件……");
    }
    );

    connect(tcpSocket, &QTcpSocket::readyRead,
            [=]()
            {
                //取出所有的内容
                QByteArray buf = tcpSocket->readAll();

                if(start_flag == true)
                {
                    start_flag = false;

                    //解析数据
                    /*拆包函数
                        section: 第一个参数：分割符
                                 第二第三个参数：解析从第几段到第几段，0为开始段
                     */
                    fileName = QString(buf).section("$$$", 0, 0);
                    fileSize = QString(buf).section("$$$", 1, 1).toInt();
                    receivesize = 0;

                    //打开文件
                    file.setFileName(fileName);
                    QDir::setCurrent("./..");//指定存放目录
                    bool isOk = file.open(QIODevice::WriteOnly);
                    if(isOk == false)//如果出错
                    {
                        qDebug() << "WriteOnly文件出错！";
                        tcpSocket->disconnectFromHost();
                        tcpSocket->close();

                        return;
                    }
                    //弹出提示框，接受的文件信息
                    QString str = QString("要接收的文件：[%1:%2MB]").arg(fileName).arg(fileSize/1024/1024);
                 //   QMessageBox::information(this, "文件信息", str);
                    ui->textEdit->append("str");
                    ui->textEdit->append("正在接收文件......");


                    //归一化一下进度条
                    ui->progressBar->setMinimum(0);
                    ui->progressBar->setMaximum(fileSize/1024);//以kb显示进度条
                    ui->progressBar->setValue(0);

                }
                else//正式接受内容
                {
                      qint64 len = file.write(buf);
                      if(len > 0)
                        receivesize += len;

                     //更新进度条
                      ui->progressBar->setValue(receivesize/1024);
                     // 如果接受完成
                      if(receivesize == fileSize)
                      {
                          //发送完
                          tcpSocket->write("File done!");

                          QMessageBox::information(this, "完成", "文件接收完成！");
                          file.close();
                          //接受完成，断开
                          tcpSocket->disconnectFromHost();
                          tcpSocket->close();
                      }

                }

             }
            );


}

ClientFileTcp::~ClientFileTcp()
{
    delete ui;
}

void ClientFileTcp::on_buttonConnect_clicked()
{
    //获取服务器ip和端口
    QString ip = ui->lineEditIP->text();
    quint16 port = ui->lineEditPort->text().toInt();


    tcpSocket->connectToHost(QHostAddress(ip), port);


}







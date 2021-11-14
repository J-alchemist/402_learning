#include "widget.h"
#include "ui_widget.h"
#include <QFileInfo>//文件信息获取
#include <QDebug>


Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);

    tcpServer = new QTcpServer(this);
    tcpServer->listen(QHostAddress::Any, 8080);
    setWindowTitle("服务器8080");

    //初始状态未有客户端连接时，按钮变灰
    ui->buttonLoad->setEnabled(false);
    ui->buttonSend->setEnabled(false);

    connect(tcpServer, &QTcpServer::newConnection,
            [=]()
            {
                tcpSocket = tcpServer->nextPendingConnection();

                QString ip = tcpSocket->peerAddress().toString();
                quint16 port = tcpSocket->peerPort();
                //显示连接用户
                QString str = QString("[%1:%2]:成功连接！")
                                      .arg(ip)
                                      .arg(port);
                ui->textEdit->setText(str);
                //连接成功后，可以使用按钮
                ui->buttonLoad->setEnabled(true);

                //接收来自文件传输后的语言
                connect(tcpSocket, &QTcpSocket::readyRead,
                        [=]()
                        {
                           QByteArray buf = tcpSocket->readAll();
                           if(QString(buf) == "File done!")
                           {
                               ui->textEdit->append("文件发送完毕！");
                               file.close();

                               tcpSocket->disconnectFromHost();
                               tcpSocket->close();

                           }


                        }

                        );

            }
            );
    //触发定时事件,触发发送内容，避免粘包
    connect(&timer, &QTimer::timeout,
            [=]()
            {
                timer.stop();
                sendData();//发送内容
            }
            );

}

Widget::~Widget()
{
    delete ui;
}

//选择文件
void Widget::on_buttonLoad_clicked()
{
    QString filepath = QFileDialog::getOpenFileName(this, "open", "../");
    //如果选择路径非空
    if(false == filepath.isEmpty())
    {
        //先清除一下变量
        fileName.clear();
        fileSize = 0;
        //获取文件信息
        QFileInfo info(filepath);
        fileName = info.fileName();
        fileSize = info.size();

        sendsize = 0;
        //以只读方式打开
        file.setFileName(filepath);
        bool isOk = file.open(QIODevice::ReadOnly);
        if(false == isOk)
        {
            qDebug() << "文件打开失败！";

        }
        //提示文件打开路径
        ui->textEdit->append(filepath);
        //按钮使能
        ui->buttonLoad->setEnabled(false);
        ui->buttonSend->setEnabled(true);

    }
    else
    {
        qDebug() << "选择文件路径出错！";

    }

}


//文件发送
void Widget::on_buttonSend_clicked()
{

    //文件头信息格式串,与客户端拆包函数对应
    QString head = QString("%1$$$%2").arg(fileName).arg(fileSize);
    //先发送文件头信息
    qint64 len = tcpSocket->write( head.toUtf8() );
    if(len > 0 )//先发送文件头信息发送成功
    {
        //防止粘包，需要通过定时器延时再发送内容
        timer.start(20);

    }
    else
    {
        qDebug() << "头部信息发送失败！";
        file.close();
        ui->buttonLoad->setEnabled(true);
        ui->buttonSend->setEnabled(false);

    }


}

void Widget::sendData()
{
    qint64 len;

    ui->textEdit->append("正在发送文件......");
    do
    { //每次发送数据大小
        char buf[4*1024] = {0};
        len = 0;
      //读取多少发多少
        len = file.read(buf, sizeof(buf));
        len = tcpSocket->write(buf, len);

        //累积发送大小
        sendsize += len;

    }while(len > 0);

//    if(sendsize == fileSize)
//    {
//        ui->textEdit->append("文件发送完成！");
//        file.close();

//        //发送完成后自动关闭客户端
//        tcpSocket->disconnectFromHost();
//        tcpSocket->close();

//    }


}











































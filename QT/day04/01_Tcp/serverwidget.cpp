#include "serverwidget.h"
#include "ui_serverwidget.h"
#include <QNetworkProxy>

ServerWidget::ServerWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ServerWidget)
{
    ui->setupUi(this);


    tcpServer = NULL;
    tcpSocket = NULL;

    //创建监听套接字
    tcpServer = new QTcpServer(this);
    //设置监听当前所有网卡地址，端口
    tcpServer->listen(QHostAddress::Any, 8080);
    //设置服务器标题
    setWindowTitle("服务器：8080");
    //获取连接信号 newConnection信号
    connect(tcpServer, &QTcpServer::newConnection,
           [=]()
           {
               //取出建立好连接的套接字
               tcpSocket = tcpServer->nextPendingConnection();

               //获取对方的ip和端口(从获取的套接字中)
               QString ip = tcpSocket->peerAddress().toString();
               qint16 port = tcpSocket->peerPort();

               QString temp = QString("[%1:%2]:成功连接！").arg(ip).arg(port);

               //显示获取内容
               ui->textEditReceive->setText(temp);


               //接收
               connect(tcpSocket, &QTcpSocket::readyRead,
                       [=]()
                       {
                               //取出所有内容
                               QByteArray array = tcpSocket->readAll();
                               //追加显示，不会覆盖前面的消息
                               ui->textEditReceive->append(array);
                       }
                       );


            }
            );


}

ServerWidget::~ServerWidget()
{
    delete ui;
}

void ServerWidget::on_buttonClose_clicked()
{
    if(tcpSocket == NULL)//在未建立连接前不执行操作
    {
        return;
    }
     //主动和客户端断开连接
    tcpSocket->disconnectFromHost();
    tcpSocket->close();
    tcpSocket = NULL;
}

void ServerWidget::on_buttonSend_clicked()
{
    if(tcpSocket == NULL)//在未建立连接前不执行操作
    {
        return;
    }
    //获取编辑区内容
    QString str = ui->textEditSend->toPlainText();

    tcpSocket->write( str.toUtf8().data());
}






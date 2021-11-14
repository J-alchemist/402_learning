#include "clientwidget.h"
#include "ui_clientwidget.h"
#include <QNetworkProxy>

ClientWidget::ClientWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ClientWidget)
{
    ui->setupUi(this);

    tcpSocket = NULL;

    tcpSocket = new QTcpSocket(this);

    setWindowTitle("Client");
    //和服务器连接成功会出发connected信号
    connect(tcpSocket, &QTcpSocket::connected,
            [=]()
            {
                ui->EditReceive->setText("成功连接服务器！");
            }
            );
    //收
    connect(tcpSocket, &QTcpSocket::readyRead,
            [=]()
    {
        //取出所有内容
        QByteArray array = tcpSocket->readAll();
        //追加显示，不会覆盖前面的消息
        ui->EditReceive->append(array);
    }


            );

}

ClientWidget::~ClientWidget()
{
    delete ui;
}

void ClientWidget::on_buttonConnect_clicked()
{
    //获取服务器ip和端口
    QString ip = ui->EditIP->text();
    qint16 port = ui->EditPort->text().toInt();

    //主动和服务器建立连接
    tcpSocket->connectToHost(QHostAddress(ip), port);

}





void ClientWidget::on_buttonSend_clicked()
{

    if(tcpSocket == NULL)//在未建立连接前不执行操作
    {
        return;
    }
    //获取编辑区内容
    QString str = ui->EditSend->toPlainText();
    //发送
    tcpSocket->write( str.toUtf8().data());

}

void ClientWidget::on_buttonClose_clicked()
{
    if(tcpSocket == NULL)//在未建立连接前不执行操作
    {
        return;
    }

    //主动和服务器断开连接
   tcpSocket->disconnectFromHost();
   tcpSocket->close();

}

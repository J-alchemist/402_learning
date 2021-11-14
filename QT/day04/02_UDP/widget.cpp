#include "widget.h"
#include "ui_widget.h"
#include <QHostAddress>

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);

    udpSocket = new QUdpSocket(this);

    //绑定端口
    udpSocket->bind(8888);
    setWindowTitle("本服务器端口：8888");

    //收到信息触发readyRead
    connect(udpSocket, &QUdpSocket::readyRead,
            [=]()
            {
                //读取信息,存储的数组，保存的对方套接字的信息变量，返回读取大小
                char buf[1024] = {0};
                QHostAddress ip;
                quint16 port;
                qint64 len = udpSocket->readDatagram(buf, sizeof(buf), &ip, &port);
                if(len > 0)
                {
                    //显示格式
                    QString str = QString("[%1:%2]: %3")
                            .arg(ip.toString())
                            .arg(port)
                            .arg(buf);
                    //显示到编辑区
                    ui->textEdit->setText(str);
                }

            }
            );


}

Widget::~Widget()
{
    delete ui;
}

void Widget::on_buttonSend_clicked()
{
    //获取对方的ip和端口
    QString ip = ui->lineEditIP->text();
    quint16 port = ui->lineEditPort->text().toInt();

    if(!ip.toInt())
    {
        return;
    }

    //获取编辑区内容
    QString str = ui->textEdit->toPlainText();

    //给指定ip发数据
    udpSocket->writeDatagram(str.toUtf8(), QHostAddress(ip), port);

}

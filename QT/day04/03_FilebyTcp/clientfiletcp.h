#ifndef CLIENTFILETCP_H
#define CLIENTFILETCP_H

#include <QWidget>
#include <QTcpSocket>
#include <QFile>

namespace Ui {
class ClientFileTcp;
}

class ClientFileTcp : public QWidget
{
    Q_OBJECT

public:
    explicit ClientFileTcp(QWidget *parent = 0);
    ~ClientFileTcp();

private slots:
    void on_buttonConnect_clicked();

private:
    Ui::ClientFileTcp *ui;

    QTcpSocket *tcpSocket;

    QFile file;//文件对象

    QString fileName;//文件名
    qint64 fileSize;//文件大小

    qint64 receivesize;//记录已经接收文件大小

    bool start_flag;


};

#endif // CLIENTFILETCP_H

#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QTcpServer>
#include <QTcpSocket>
#include <QFile>
#include <QFileDialog>
#include <QTimer>

namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();

    void sendData();

private slots:
    void on_buttonLoad_clicked();

    void on_buttonSend_clicked();




private:
    Ui::Widget *ui;

    QTcpServer *tcpServer;
    QTcpSocket *tcpSocket;

    QFile file;
    QString fileName;//文件名
    qint64 fileSize;//文件大小

    qint64 sendsize;//记录已经发送文件大小
    QTimer timer;

};

#endif // WIDGET_H

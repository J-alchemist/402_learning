#ifndef MYWIDGET_H
#define MYWIDGET_H

#include <QWidget>

namespace Ui {
class MyWidget;
}

class MyWidget : public QWidget
{
    Q_OBJECT

public:
    explicit MyWidget(QWidget *parent = 0);
    ~MyWidget();

protected:
    void keyPressEvent(QKeyEvent *e);
    void timerEvent(QTimerEvent *e);

    void closeEvent(QCloseEvent *e);
//重写event函数
    bool event(QEvent *e);
//事件过滤器
    bool eventFilter(QObject *obj, QEvent *e);
private:
    Ui::MyWidget *ui;

    int timerID1;
    int timerID2;
};

#endif // MYWIDGET_H

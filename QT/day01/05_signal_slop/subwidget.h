#ifndef SUBWIDGET_H
#define SUBWIDGET_H

#include <QWidget>
#include <QPushButton>

class subwidget : public QWidget
{
    Q_OBJECT
public:
    explicit subwidget(QWidget *parent = 0);


    void SendSlot();
/*signals关键字，信号没有返回值，可以有参数，即使函数声明，无需定义
 *使用：emit 函数名();
 */
signals:
    void mySignal();
public slots:

private:
    QPushButton b4;

};

#endif // SUBWIDGET_H

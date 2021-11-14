#ifndef MAINWIDGET_H
#define MAINWIDGET_H

#include <QWidget>
#include <QPushButton>
#include "subwidget.h"

/*在类里定义要使用的变量*/

class MainWidget : public QWidget
{
    Q_OBJECT

public:
    MainWidget(QWidget *parent = 0);
    ~MainWidget();

public slots:
    void Myslop();/*自定义槽函数*/
    void ChangeWin();
    void Changeback();

    void DealSlot(int, QString);//带参槽函数

private:
    QPushButton b;
    QPushButton *b2;
    QPushButton b3;

    subwidget w2;
};

#endif // MAINWIDGET_H

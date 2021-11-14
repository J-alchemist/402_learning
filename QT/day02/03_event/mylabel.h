#ifndef MYLABEL_H
#define MYLABEL_H

/*此处Mylabel继承于QLabel，否则无法使用提升*/
#include <QLabel>
#include <QWidget>


class Mylabel : public QLabel
{
    Q_OBJECT
public:
    explicit Mylabel(QWidget *parent = 0);

signals:

public slots:

protected:
    void mousePressEvent(QMouseEvent *ev);//事件
    void mouseReleaseEvent(QMouseEvent *ev);
    void mouseMoveEvent(QMouseEvent *ev);

    void enterEvent(QEvent *);
    void leaveEvent(QEvent *);

};

#endif // MYLABEL_H

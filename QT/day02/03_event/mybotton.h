#ifndef MYBOTTON_H
#define MYBOTTON_H

#include <QPushButton>

class Mybotton : public QPushButton
{
    Q_OBJECT
public:
    explicit Mybotton(QWidget *parent = 0);

protected:
    void mousePressEvent(QMouseEvent *ev);



signals:

public slots:

};

#endif // MYBOTTON_H

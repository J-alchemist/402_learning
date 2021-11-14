#include "widget.h"
#include <QSpinBox>//带上下箭头的数字输入框
#include <QSlider>//滑块
#include <QHBoxLayout>//布局管理器
#include <QDebug>

Widget::Widget(QWidget *parent) :
    QWidget(parent)
{
    QSpinBox *spin = new QSpinBox(this);
    QSlider *slider = new QSlider(Qt::Horizontal, this);//指定水平滑块

    //添加控件到布局中，并指定父对象
    QHBoxLayout *boxlayout = new QHBoxLayout(this);
    boxlayout->addWidget(spin);
    boxlayout->addWidget(slider);
    //boxlayout布局未指定父对象时使用一下语句,将布局放在窗口里
    //setLayout(boxlayout);

    //信号连接处理 数字输入框he滑块
    connect(spin, static_cast<void (QSpinBox::*)(int)>(&QSpinBox::valueChanged),
                                   slider, &QSlider::setValue);
    connect(slider, &QSlider::valueChanged, spin, &QSpinBox::setValue);




}

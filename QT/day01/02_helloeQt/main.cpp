/* new project-》其他项目-》 空的qt项目
 * 项目文件导入模块 QT += widgets
 * 添加c++源文件，注意.cpp
 * 不知道构造函数如何时，F1帮助
 */
#include <QApplication>
#include <QWidget>//窗口控件基类
#include <QPushButton>//按钮头文件

int main(int argc, char **argv)
{
    QApplication app(argc, argv);
/*
   //不指定父对象---》对象与对象的窗口独立，且每个对象要显示都必须调用一次x.show();
    QWidget w;//定义一个窗口
    w.setWindowTitle("我真是天才");//设置标题
    w.show();

    QPushButton b;//定义一个按钮
    b.setText("ahaha");
    b.show();
*/
    //指定父对象的两种方法
    /*a指定b为他的父对象--》a窗口放在b上
     * ①setParent
     * ②通过构造函数传参
     */
    QWidget w;//定义一个窗口
    w.setWindowTitle("我真是天才");//设置标题
//①方式
    QPushButton b;//定义一个按钮
    b.setParent(&w);//指定w为其父类
    b.setText("-_-");
    b.move(66,66);//设置坐标
//②方式
    QPushButton b2(&w);//定义并指定父类 创建对象时，根据参数，调用不同的构造函数
    //定义一个按钮
    b2.setText("^_^");
    b2.move(166,166);//设置坐标

    w.show();

    app.exec();
    return 0;
}

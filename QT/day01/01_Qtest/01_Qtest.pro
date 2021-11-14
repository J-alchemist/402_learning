#-------------------------------------------------
#
# Project created by QtCreator 2020-03-25T19:49:46
#
#-------------------------------------------------

#项目文件
#模块：头文件中选择+F1 查找该类需要的模块
QT       += core gui
#兼容qt4
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

#应用程序的名字：项目文件 explorer 上一级文件 debug .exe文件
TARGET = 01_Qtest

#指定makefile类型：生成一个app，可生成库lib
TEMPLATE = app

#源文件路径：自动添加
SOURCES += main.cpp\
        mywidget.cpp

#头文件路径：自动添加
HEADERS  += mywidget.h

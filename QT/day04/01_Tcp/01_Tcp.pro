#-------------------------------------------------
#
# Project created by QtCreator 2020-04-02T12:07:08
#
#-------------------------------------------------

QT       += core gui
QT += network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = 01_Tcp
TEMPLATE = app


SOURCES += main.cpp\
        serverwidget.cpp \
    clientwidget.cpp

HEADERS  += serverwidget.h \
    clientwidget.h

FORMS    += serverwidget.ui \
    clientwidget.ui


CONFIG += C++11



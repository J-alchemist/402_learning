#-------------------------------------------------
#
# Project created by QtCreator 2020-04-02T19:03:18
#
#-------------------------------------------------

QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = 03_FilebyTcp
TEMPLATE = app


SOURCES += main.cpp\
        widget.cpp \
    clientfiletcp.cpp

HEADERS  += widget.h \
    clientfiletcp.h

FORMS    += widget.ui \
    clientfiletcp.ui

CONFIG += C++11

#-------------------------------------------------
#
# Project created by QtCreator 2020-03-31T00:03:07
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = 03_event
TEMPLATE = app


SOURCES += main.cpp\
        mywidget.cpp \
    mylabel.cpp \
    mybotton.cpp

HEADERS  += mywidget.h \
    mylabel.h \
    mybotton.h

FORMS    += mywidget.ui

CONFIG += C++11



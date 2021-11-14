#-------------------------------------------------
#
# Project created by QtCreator 2020-03-29T12:18:28
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = 01_design
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    widget.cpp

HEADERS  += mainwindow.h \
    widget.h

FORMS    += mainwindow.ui

CONFIG += C++11

RESOURCES += \
    ../../image/resource.qrc



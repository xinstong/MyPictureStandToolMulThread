#-------------------------------------------------
#
# Project created by QtCreator 2018-02-24T15:57:26
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = MyQtPicStandardTool
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    myworkthread.cpp

HEADERS  += mainwindow.h \
    myworkthread.h

FORMS    += mainwindow.ui

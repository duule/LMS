#-------------------------------------------------
#
# Project created by QtCreator 2016-08-24T18:01:22
#
#-------------------------------------------------

QT       += core gui
QT       += sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = LMS
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    date.cpp \
    bookinfo.cpp \
    readerinfo.cpp \
    list.cpp \
    search.cpp

HEADERS  += mainwindow.h \
    date.h \
    bookinfo.h \
    readerinfo.h \
    list.h \
    search.h

FORMS    += mainwindow.ui \
    search.ui

#-------------------------------------------------
#
# Project created by QtCreator 2014-01-08T20:09:22
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = dmut
TEMPLATE = app

CONFIG	+= c++11

SOURCES += src/main.cpp \
    src/mainwindow.cpp \
    src/newcharacterdialog.cpp

HEADERS  += \
    src/mainwindow.h \
    src/newcharacterdialog.h

FORMS    += src/mainwindow.ui \
    src/newcharacterdialog.ui

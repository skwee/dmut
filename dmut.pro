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
    src/newcharacterdialog.cpp \
    src/frame.cpp \
    src/framelistview.cpp \
    src/framemodel.cpp \
    src/spritetoframefactory.cpp \
    src/animation.cpp \
    src/animationmodel.cpp \
    src/animationlistview.cpp \
    src/framelistframe.cpp

HEADERS  += \
    src/mainwindow.h \
    src/newcharacterdialog.h \
    src/frame.h \
    src/framelistview.h \
    src/framemodel.h \
    src/spritetoframefactory.h \
    src/animation.h \
    src/animationmodel.h \
    src/animationlistview.h \
    src/framelistframe.h

FORMS    += src/mainwindow.ui \
    src/newcharacterdialog.ui \
    src/framelistframe.ui

RESOURCES += \
    iconset.qrc

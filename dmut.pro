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
    src/animationlistframe.cpp \
    src/animation.cpp \
    src/animationmodel.cpp \
    src/spritefactory.cpp \
    src/frame.cpp \
    src/framelistframe.cpp \
    src/framemodel.cpp \
    src/block.cpp \
    src/item.cpp \
    src/animationitemdelegate.cpp \
    src/frameitemdelegate.cpp

HEADERS  += \
    src/mainwindow.h \
    src/newcharacterdialog.h \
    src/animationlistframe.h \
    src/animation.h \
    src/animationmodel.h \
    src/spritefactory.h \
    src/frame.h \
    src/framelistframe.h \
    src/framemodel.h \
    src/block.h \
    src/iteminterface.h \
    src/item.h \
    src/animationitemdelegate.h \
    src/frameitemdelegate.h

FORMS    += src/mainwindow.ui \
    src/newcharacterdialog.ui \
    src/animationlistframe.ui \
    src/framelistframe.ui

RESOURCES += \
    iconset.qrc

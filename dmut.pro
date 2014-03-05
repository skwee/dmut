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
    src/spriteatlasmodel.cpp \
    src/newcharacterdialog.cpp \
    src/sprite.cpp \
    src/character.cpp \
    src/item.cpp \
    src/animation.cpp \
    src/frame.cpp \
    src/characterdocument.cpp \
    src/charactermodel.cpp \
    src/characterhierarchywidget.cpp \
    src/namer.cpp \
    src/rootitem.cpp \
    src/itempropertieswidget.cpp \
    src/characterdetailseditor.cpp \
    src/animationdetailseditor.cpp \
    src/framedetailseditor.cpp \
    src/spriteatlasdialog.cpp \
    src/spriteatlasscene.cpp \
    src/animationpreviewwidget.cpp

HEADERS  += \
    src/mainwindow.h \
    src/spriteatlasmodel.h \
    src/newcharacterdialog.h \
    src/sprite.h \
    src/character.h \
    src/item.h \
    src/animation.h \
    src/frame.h \
    src/characterdocument.h \
    src/charactermodel.h \
    src/characterhierarchywidget.h \
    src/namer.h \
    src/rootitem.h \
    src/itempropertieswidget.h \
    src/characterdetailseditor.h \
    src/animationdetailseditor.h \
    src/framedetailseditor.h \
    src/spriteatlasdialog.h \
    src/spriteatlasscene.h \
    src/animationpreviewwidget.h

FORMS    += src/mainwindow.ui \
    src/newcharacterdialog.ui \
    src/characterhierarchywidget.ui \
    src/itempropertieswidget.ui \
    src/characterdetailseditor.ui \
    src/animationdetailseditor.ui \
    src/framedetailseditor.ui \
    src/spriteatlasdialog.ui \
    src/animationpreviewwidget.ui

RESOURCES += \
    icons.qrc

#-------------------------------------------------
#
# Project created by QtCreator 2018-08-03T12:00:45
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = ALF-nes_header_editor
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += \
    src/main.cpp \
    src/mainwindow.cpp \
    src/nesromparser.cpp \
    src/nesromheader.cpp

HEADERS += \
    src/mainwindow.h \
    src/nesromparser.h \
    src/nesromheader.h

FORMS += \
    gui/mainwindow.ui


unix|win32: LIBS += -L$$PWD/lib/ -lALF_std

INCLUDEPATH += $$PWD/include
DEPENDPATH += $$PWD/include

win32:!win32-g++: PRE_TARGETDEPS += $$PWD/lib/ALF_std.lib
else:unix|win32-g++: PRE_TARGETDEPS += $$PWD/lib/libALF_std.a

#-------------------------------------------------
#
# Project created by QtCreator
#
#-------------------------------------------------

QT       += core gui
QT       += printsupport
QT       += core

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = lexis
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    arxeio.cpp \
    eisagogi_lexis.cpp \
    diagrafi_lexis.cpp

HEADERS  += mainwindow.h \
    arxeio.h \
    eisagogi_lexis.h \
    diagrafi_lexis.h

FORMS    += mainwindow.ui \
    eisagogi_lexis.ui \
    diagrafi_lexis.ui

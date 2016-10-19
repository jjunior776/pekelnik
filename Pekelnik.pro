#-------------------------------------------------
#
# Project created by QtCreator 2016-04-12T15:19:33
#
#-------------------------------------------------

QT       += core gui printsupport

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Pekelnik
TEMPLATE = app


SOURCES += main.cpp\
        menu.cpp \
    continuousresultswindow.cpp \
    resultswindow.cpp \
    csvreader.cpp \
    teamresultswindow.cpp \
    propositionswindow.cpp

HEADERS  += menu.h \
    continuousresultswindow.h \
    resultswindow.h \
    csvreader.h \
    teamresultswindow.h \
    propositionswindow.h

FORMS    += menu.ui \
    continuousresultswindow.ui \
    resultswindow.ui \
    teamresultswindow.ui \
    propositionswindow.ui

RESOURCES += \
    img.qrc

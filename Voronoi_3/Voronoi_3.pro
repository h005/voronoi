#-------------------------------------------------
#
# Project created by QtCreator 2015-05-31T08:50:48
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Voronoi_3
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    imagelabel.cpp \
    beachline.cpp \
    dcel.cpp \
    edge.cpp \
    eventqueue.cpp \
    face.cpp \
    sitequeue.cpp \
    vertex.cpp

HEADERS  += mainwindow.h \
    imagelabel.h \
    beachline.h \
    dcel.h \
    edge.h \
    eventqueue.h \
    face.h \
    sitequeue.h \
    vertex.h

FORMS    += mainwindow.ui

#-------------------------------------------------
#
# Project created by QtCreator 2013-03-24T13:34:13
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = qt-segment
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    utility.cpp

HEADERS  += mainwindow.h\
        convolve.h\
        disjoint-set.h\
        filter.h\
        image.h\
        imconv.h\
        imutil.h\
        misc.h\
        pnmfile.h\
        segment-graph.h\
        segment-image.h \
    utility.h

FORMS    += mainwindow.ui

#-------------------------------------------------
#
# Project created by QtCreator 2016-02-07T21:25:23
#
#-------------------------------------------------

QT += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = lzr_editor
TEMPLATE = app

# CONFIG += qt debug

SOURCES += main.cpp\
        lzr_editor.cpp\
        frameview.cpp\
        grid.cpp\
        point.cpp\
        colordock.cpp

HEADERS  += lzr_editor.h frameview.h grid.h point.h colordock.h

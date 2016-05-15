#-------------------------------------------------
#
# Project created by Natural Language Processing Team
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = bin/main

TEMPLATE = app

OBJECTS_DIR=obj/

INCLUDEPATH=include/

MOC_DIR =moc_file

QMAKE_CXXFLAGS += -std=c++11

SOURCES += \
    source/main.cpp \
    source/interface.cpp \
    source/dictionary.cpp

HEADERS  += \
    include/interface.h \
  include/dictionary.h



QT += core
QT += network
QT -= gui

CONFIG += c++11

TARGET = bots
CONFIG += console
CONFIG -= app_bundle

TEMPLATE = app

SOURCES += main.cpp \
    macdalgo.cpp \
    algo.cpp \
    feeder.cpp

HEADERS += \
    algo.h \
    macdalgo.h \
    feeder.h

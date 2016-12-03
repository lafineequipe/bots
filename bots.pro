QT += core
QT -= gui

CONFIG += c++11

TARGET = bots
CONFIG += console
CONFIG -= app_bundle

TEMPLATE = app

SOURCES += main.cpp \
    macdalgo.cpp

HEADERS += \
    algo.h \
    macdalgo.h

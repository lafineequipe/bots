QT += core
QT -= gui

CONFIG += c++11

TARGET = bots
CONFIG += console
CONFIG -= app_bundle

TEMPLATE = app

SOURCES += main.cpp \
    macdalgo.cpp \
    algo.cpp \
    Bot.cpp \
    Simplebot.cpp \
    bollingers.cpp \
    assetprices.cpp

HEADERS += \
    algo.h \
    macdalgo.h \
    Bot.h \
    Simplebot.h \
    bollingers.h \
    assetprices.h

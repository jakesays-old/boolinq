#-------------------------------------------------
#
# Project created by QtCreator 2011-12-01T02:43:49
#
#-------------------------------------------------

QT       -= core gui

TARGET = boolinq
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app

SOURCES += \
    WhereRangeTest.cpp \
    main.cpp \
    LinqTest.cpp \
    IteratorRangeTest.cpp \
    ExtractRangeTest.cpp \
    ../gmock/src/gmock-all.cc \
    ../gmock/gtest/src/gtest-all.cc

HEADERS += \
    WhereRange.h \
    SelectRange.h \
    ReverseRange.h \
    IteratorRange.h \
    ExtractRange.h \
    ChainRange.h \
    boolinq.h

INCLUDEPATH += \
    "../gmock" \
    "../gmock/include" \
    "../gmock/gtest" \
    "../gmock/gtest/include"

QMAKE_CXXFLAGS += -std=c++0x -U__STRICT_ANSI__






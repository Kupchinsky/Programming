TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp \
    binarytree.cpp

HEADERS += \
    binarytree.hpp

QMAKE_CXXFLAGS += -std=c++11
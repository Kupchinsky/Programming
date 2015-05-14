TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp \
    contacttree.cpp \
    TaskMenu.cpp

HEADERS += \
    contacttree.hpp \
    TaskMenu.h

QMAKE_CXXFLAGS += -std=c++11
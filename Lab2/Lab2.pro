TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp \
    queue.cpp

HEADERS += \
    queue.hpp

QMAKE_CXXFLAGS += -std=c++11
TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp \
    list.tpp

include(deployment.pri)
qtcAddDeployment()

HEADERS += \
    list.hpp

QMAKE_CXXFLAGS += -std=c++11
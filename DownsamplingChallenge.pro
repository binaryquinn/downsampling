TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp \
    mappedheap.cpp

INCLUDEPATH += /usr/local/boost_1_55_0
QMAKE_CXXFLAGS += -std=c++0x -pthread
LIBS += -lpthread -lrt

HEADERS += \
    mappedheap.h

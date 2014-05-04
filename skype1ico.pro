#-------------------------------------------------
#
# Project created by QtCreator 2014-03-18T23:59:05
#
#-------------------------------------------------

QT       -= gui

TARGET = skype1ico
TEMPLATE = lib

DEFINES += SKYPE1ICO_LIBRARY

SOURCES += skype1ico.cpp \
    hashing.cpp

HEADERS += skype1ico.h\
        skype1ico_global.h \
    hashing.h

unix {
    target.path = /usr/lib
    INSTALLS += target
}

QMAKE_CXXFLAGS += -m32
LIBS = -L/usr/lib32 -L/usr/lib32/qt4 -L/usr/lib32 -L/usr/lib32/qt4


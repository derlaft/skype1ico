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
    isEmpty(PREFIX) {
        PREFIX = /usr
    }

    # thanks dat arch maintainer
    equals(QMAKE_HOST.arch, "x86_64") {
        target.path = $$PREFIX/lib32
    } else {
        target.path = $$PREFIX/lib
    }

    THEMES = $$PREFIX/share/skype1ico
    themes.path = $$THEMES
    themes.files += KFaenza KFaenza-Black KFaenza-Monochrome KFaenza-Ubuntu native

    DEFINES += THEMES_DIR=\\\"$$THEMES/\\\"
    DEFINES += DEFAULT_THEME=\\\"native\\\"

    desktop.path = $$PREFIX/share/applications/
    desktop.files += skype1ico.desktop

    INSTALLS += target themes desktop
}

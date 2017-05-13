#-------------------------------------------------
#
# Project created by QtCreator 2017-03-29T20:13:21
#
#-------------------------------------------------

QT       += core gui multimedia
QMAKE_CXXFLAGS += -std=c++0x

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = NBG_Ball
TEMPLATE = app


SOURCES += main.cpp \
    level.cpp \
    plate.cpp \
    ball.cpp \
    brick.cpp \
    bullet.cpp \
    message.cpp \
    fallingitem.cpp \
    mode.cpp \
    package.cpp

HEADERS  += \
    level.h \
    plate.h \
    ball.h \
    brick.h \
    bullet.h \
    message.h \
    fallingitem.h \
    mode.h \
    package.h

FORMS    +=

RESOURCES += \
    levels.qrc \
    catfaces.qrc \
    modes.qrc \
    packages.qrc \
    elements.qrc \
    level_music.qrc

DISTFILES +=

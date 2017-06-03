#-------------------------------------------------
#
# Project created by QtCreator 2017-03-29T20:13:21
#
#-------------------------------------------------

QT              += core gui multimedia network
QMAKE_CXXFLAGS  += -std=c++0x

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = NBG_Ball
TEMPLATE = app

RC_FILE = catface.rc

SOURCES += main.cpp \
    level.cpp \
    plate.cpp \
    ball.cpp \
    brick.cpp \
    bullet.cpp \
    message.cpp \
    fallingitem.cpp \
    mode.cpp \
    package.cpp \
    score.cpp

HEADERS  += \
    level.h \
    plate.h \
    ball.h \
    brick.h \
    bullet.h \
    message.h \
    fallingitem.h \
    mode.h \
    package.h \
    score.h

FORMS    += \
    score.ui

RESOURCES += \
    levels.qrc \
    modes.qrc \
    packages.qrc \
    sounds.qrc \
    levels_music.qrc \
    elements.qrc \
    catfaces.qrc

DISTFILES +=

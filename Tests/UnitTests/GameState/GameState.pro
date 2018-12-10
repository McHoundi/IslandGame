QT += testlib
QT -= gui
QT += widgets

CONFIG += qt console warn_on depend_includepath testcase
CONFIG -= app_bundle

TARGET = tst_gamestatetest

DESTDIR = bin

TEMPLATE = app

SOURCES +=  tst_gamestatetest.cpp \
            ../../../UI/gamestate.cpp \
            ../../../UI/player.cpp \
            ../../../UI/infobox.cpp
HEADERS += \
            ../../../GameLogic/Engine/igamestate.hh \
            ../../../UI/gamestate.hh \
            ../../../UI/player.hh \
            ../../../UI/infobox.hh


INCLUDEPATH += ../../../UI \
                ../../../GameLogic/Engine/
DEPENDPATH  += ../../../UI \
                ../../../GameLogic/Engine/

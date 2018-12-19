TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp \
    map.cpp \
    animation.cpp \
    background.cpp \
    enemies.cpp \
    player.cpp \
    camera.cpp \
    menu.cpp \
    characternaruto.cpp

CONFIG(release, debug|release): LIBS += -lsfml-audio -lsfml-graphics -lsfml-network -lsfml-window -lsfml-system
CONFIG(debug, debug|release): LIBS += -lsfml-audio -lsfml-graphics -lsfml-network -lsfml-window -lsfml-system

HEADERS += \
    background.h \
    enemies.h \
    map.h \
    player.h \
    camera.h \
    constants.h \
    menu.h \
    animation.h \
    characternaruto.h

TEMPLATE = app
CONFIG += console c++17
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
        circleobject.cpp \
        main.cpp \
        renderer.cpp

INCLUDEPATH += D:\ohjelmat\repos\personal\cpp\sfml\SFML-2.6.1-sources\SFML-2.6.1\include
DEPENDPATH += D:\ohjelmat\repos\personal\cpp\sfml\SFML-2.6.1-sources\SFML-2.6.1\include

LIBS += -LD:\ohjelmat\repos\personal\cpp\sfml\sfml_build\libs\

CONFIG(debug, debug|release): LIBS += -lsfml-audio-d -lsfml-graphics-d -lsfml-main-d -lsfml-network-d -lsfml-system-d -lsfml-window-d
CONFIG(release, debug|release): LIBS += -lsfml-audio -lsfml-graphics -lsfml-main -lsfml-network -lsfml-system -lsfml-window

HEADERS += \
    circleobject.h \
    renderer.h

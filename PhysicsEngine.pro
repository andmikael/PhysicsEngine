TEMPLATE = app
CONFIG += console c++17
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
        circlesolver.cpp \
        main.cpp \
        renderer.cpp


# -- SFML dependencies used with windows --
#INCLUDEPATH += <path to SFML source code include folder>
#DEPENDPATH += <path to SFML source code include folder>

#LIBS += -L<path to compiled SFML library folder>

#CONFIG(debug, debug|release): LIBS += -lsfml-audio-d -lsfml-graphics-d -lsfml-main-d -lsfml-network-d -lsfml-system-d -lsfml-window-d
#CONFIG(release, debug|release): LIBS += -lsfml-audio -lsfml-graphics -lsfml-main -lsfml-network -lsfml-system -lsfml-window
# -------------------------------
HEADERS += \
    circlesolver.h \
    renderer.h

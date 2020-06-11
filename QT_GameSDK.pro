QT       += core gui xml qml

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES +=  main.cpp \
    dialogs/layername.cpp \
    engine/base_window.cpp \
    engine/engine.cpp \
    engine/game.cpp \
    engine/game/game_window.cpp \
    engine/game/layergame.cpp \
    engine/game/objectgame.cpp \
    engine/game/sfmlcanvas.cpp \
    engine/game/systemgame.cpp \
    engine/scripts.cpp \
    engine/sdk.cpp \
    engine/sdk/project.cpp \
    engine/sdk/system.cpp \
    engine/sdk/window.cpp \
    tools/canvas.cpp \
    tools/canvas/layer.cpp \
    tools/canvas/object.cpp \
    tools/layers.cpp \
    tools/projects.cpp \
    tools/properties.cpp \
    tools/selectimage.cpp \
    tools/selectimage/mini_canvas.cpp \
    tools/tools.cpp

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

HEADERS += \
    dialogs/layername.h \
    engine/IEngine.h \
    engine/base_window.h \
    engine/engine.h \
    engine/game.h \
    engine/game/game_window.h \
    engine/game/layergame.h \
    engine/game/objectgame.h \
    engine/game/sfmlcanvas.h \
    engine/game/systemgame.h \
    engine/scripts.h \
    engine/sdk.h \
    engine/sdk/project.h \
    engine/sdk/system.h \
    engine/sdk/window.h \
    tools/canvas.h \
    tools/canvas/layer.h \
    tools/canvas/object.h \
    tools/layers.h \
    tools/projects.h \
    tools/properties.h \
    tools/selectimage.h \
    tools/selectimage/mini_canvas.h \
    tools/tools.h

FORMS += \
    mainwindow.ui

# Load SFML-2.5.1 lib (QT 5.10.0 supported)
win32:CONFIG(release, debug|release): LIBS += -L$$PWD/SFML-2.5.1/lib/ -lsfml-audio -lsfml-graphics -lsfml-network -lsfml-window -lsfml-system
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/SFML-2.5.1/lib/ -lsfml-audio-d -lsfml-graphics-d -lsfml-network-d -lsfml-window-d -lsfml-system-d
else:unix: LIBS += -L$$PWD/SFML-2.5.1/lib/ -lsfml-audio -lsfml-graphics -lsfml-network -lsfml-window -lsfml-system

INCLUDEPATH += $$PWD/SFML-2.5.1/include
DEPENDPATH += $$PWD/SFML-2.5.1/include

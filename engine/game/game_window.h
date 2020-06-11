#ifndef GAME_WINDOW_H
#define GAME_WINDOW_H

#include <QtCore>
#include <QtWidgets>
#include "engine/game/sfmlcanvas.h"

class WindowGame : public QMainWindow
{
public:
    WindowGame(QWidget* parent = 0);
    virtual ~WindowGame() = default;
};

#endif // GAME_WINDOW_H

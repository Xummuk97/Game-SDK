#include "game_window.h"
#include "engine/game/sfmlcanvas.h"
#include "engine/game/systemgame.h"

WindowGame::WindowGame(QWidget* parent)
    : QMainWindow(parent)
{
    setWindowTitle("Игровой движок @ Режим игры");
    setMinimumSize(QSize(800, 600));

    SystemGame::mCanvas = new MyCanvas(this, QPoint(0, 0), QSize(800, 600));
    SystemGame::mCanvas->show();

    SystemGame::loadProject();
}

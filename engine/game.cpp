#include "game.h"
#include "engine/game/game_window.h"

void EngineStartGame::start()
{
    WindowGame* window = new WindowGame();
    window->show();
}

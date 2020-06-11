#include "engine.h"

Engine::Engine(EngineStartType type)
{
    switch (type)
    {
    case EngineStartType::SDK:
        this->mStart = new EngineStartSDK();
        break;
    case EngineStartType::Game:
        this->mStart = new EngineStartGame();
        break;
    }
}

void Engine::start()
{
    mStart->start();
}

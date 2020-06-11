#ifndef ENGINE_H
#define ENGINE_H

#include "sdk.h"
#include "game.h"

class Engine
{
public:
    Engine(EngineStartType type);
    ~Engine() = default;

    void start();

private:
    IEngineStart* mStart;
};

#endif // ENGINE_H

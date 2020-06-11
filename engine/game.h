#ifndef GAME_H
#define GAME_H

#include "IEngine.h"

class EngineStartGame : public IEngineStart
{
public:
    EngineStartGame() = default;
    virtual ~EngineStartGame() = default;

    void start() override;
    EngineStartType type() override { return EngineStartType::Game; }
};

#endif // GAME_H

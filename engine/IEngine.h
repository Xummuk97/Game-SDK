#ifndef IENGINE_H
#define IENGINE_H

enum struct EngineStartType
{
    SDK,
    Game
};

class IEngineStart
{
public:
    IEngineStart() = default;
    ~IEngineStart() = default;

    virtual void start() = 0;
    virtual EngineStartType type() = 0;
};

#endif // IENGINE_H

#ifndef SDK_H
#define SDK_H

#include "IEngine.h"

class EngineStartSDK : public IEngineStart
{
public:
    EngineStartSDK() = default;
    virtual ~EngineStartSDK() = default;

    void start() override;
    EngineStartType type() override { return EngineStartType::SDK; }
};
#endif // SDK_H

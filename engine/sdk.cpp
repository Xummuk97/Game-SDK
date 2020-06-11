#include "sdk.h"
#include "engine/sdk/window.h"

void EngineStartSDK::start()
{
    WindowSDK* window = new WindowSDK();
    window->show();
}

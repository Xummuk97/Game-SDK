#ifndef WINDOW_H
#define WINDOW_H

#include "engine/base_window.h"

class WindowSDK : public BaseWindow
{
public:
    WindowSDK(QWidget* parent = Q_NULLPTR);
    virtual ~WindowSDK() = default;

private:
    void onLoad() override;
    void loadMenu();
};

#endif // WINDOW_H

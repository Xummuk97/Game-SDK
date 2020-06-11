#ifndef SELECTIMAGE_H
#define SELECTIMAGE_H

#include <QtCore>
#include <QtWidgets>
#include "tools/selectimage/mini_canvas.h"

class ToolSelectImage : public QDockWidget
{
public:
    ToolSelectImage(QWidget *parent = nullptr);
    virtual ~ToolSelectImage() = default;

    MiniCanvas* miniCanvas();

private:
    MiniCanvas* mCanvas;
};

#endif // SELECTIMAGE_H

#include "selectimage.h"

ToolSelectImage::ToolSelectImage(QWidget *parent)
    : QDockWidget(parent)
{
    setWindowTitle("Изображение");
    setMinimumHeight(200);

    mCanvas = new MiniCanvas(parent);
    setWidget(mCanvas);
}

MiniCanvas *ToolSelectImage::miniCanvas()
{
    return mCanvas;
}

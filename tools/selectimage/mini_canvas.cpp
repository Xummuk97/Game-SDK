#include "mini_canvas.h"
#include "engine/sdk/system.h"

MiniCanvas::MiniCanvas(QWidget *parent)
    : QGraphicsView(parent),
      mScene(new QGraphicsScene(this))
{
    setFrameShape(QFrame::NoFrame);
    setScene(mScene);
}

void MiniCanvas::update()
{
    mScene->clear();

    ToolCanvas* canvas = System::mCurrentProject->canvas();
    QList<QRect> imageBounds = canvas->imageBounds();

    for (QRect rect : imageBounds)
    {
        QGraphicsPixmapItem* item = mScene->addPixmap(canvas->imageCopy(rect));
        item->setPos(rect.x(), rect.y());
    }
}

void MiniCanvas::mouseDoubleClickEvent(QMouseEvent *event)
{
    QPoint tileSize = System::mCurrentProject->canvas()->tileSize();
    QPointF scenePos = mapToScene(event->pos());
    scenePos.setX(int(scenePos.x() / tileSize.x()) * tileSize.x());
    scenePos.setY(int(scenePos.y() / tileSize.y()) * tileSize.y());

    int i = 0;
    for (QGraphicsItem* item : mScene->items())
    {
        if (item->pos() == scenePos)
        {
            int index = mScene->items().size() - 1 - i;
            System::mCurrentProject->canvas()->setCurrentImageBounds(index);
        }

        i++;
    }
}

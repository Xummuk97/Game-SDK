#ifndef MINI_CANVAS_H
#define MINI_CANVAS_H

#include <QtCore>
#include <QtWidgets>

class MiniCanvas : public QGraphicsView
{
public:
    MiniCanvas(QWidget* parent = 0);
    virtual ~MiniCanvas() = default;

    void update();

    void mouseDoubleClickEvent(QMouseEvent *event) override;

private:
    QGraphicsScene* mScene;
};

#endif // MINI_CANVAS_H

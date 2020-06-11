#ifndef LAYERGAME_H
#define LAYERGAME_H

#include <QtCore>
#include <QtWidgets>
#include "engine/game/objectgame.h"

class LayerGame
{
public:
    LayerGame(const QString& name);
    ~LayerGame() = default;

    void addObject(int idImageBounds, const QPointF &position, const QString& type);
    QString name() const;

    void update();
    void draw();

private:
    QString mName;
    QList<ObjectGame*> mObjects;
};

#endif // LAYERGAME_H

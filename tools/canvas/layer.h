#ifndef LAYER_H
#define LAYER_H

#include <QGraphicsItemGroup>
#include "tools/canvas/object.h"

class Layer : public QObject, public QGraphicsItemGroup
{
public:
    Layer(const QString& name, QGraphicsItem *parent = nullptr);
    virtual ~Layer() = default;

    void addObject(Object* object);
    QString name() const;

private:
    QString mName;
};

#endif // LAYER_H

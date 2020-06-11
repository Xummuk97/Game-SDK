#include "layer.h"

Layer::Layer(const QString& name, QGraphicsItem *parent)
    : QObject(),
      QGraphicsItemGroup(parent),
      mName(name)
{

}

void Layer::addObject(Object *object)
{
    addToGroup(object);
}

QString Layer::name() const
{
    return mName;
}

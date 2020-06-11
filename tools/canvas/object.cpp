#include "object.h"
#include "engine/sdk/system.h"
#include <QtWidgets>

Object::Object(const QString& type, QGraphicsItem *parent)
    : QObject(),
      QGraphicsPixmapItem(parent),
      mType(type)
{
}

Object *Object::pixmapItemToObject(QGraphicsPixmapItem *item)
{
    return qgraphicsitem_cast<Object*>(item);
}

QGraphicsPixmapItem *Object::objectToPixmapItem(Object *object)
{
    return qgraphicsitem_cast<QGraphicsPixmapItem*>(object);
}

Object *Object::itemToObject(QGraphicsItem *item)
{
    return qgraphicsitem_cast<Object*>(item);
}

QGraphicsItem *Object::objectToItem(Object *object)
{
    return qgraphicsitem_cast<QGraphicsItem*>(object);
}

void Object::updateProperties()
{
    System::mToolProperties->clearProperties();

    QLineEdit* propType = new QLineEdit(mType);

    propType->connect(propType, &QLineEdit::textChanged, propType, [this](const QString& text)
    {
        this->mType = text;
    });

    QPoint tileSize = System::mCurrentProject->canvas()->tileSize();
    QPoint tilesCount = System::mCurrentProject->canvas()->tilesCount();
    QPointF position = pos();

    QSpinBox* propIndexX = new QSpinBox();
    propIndexX->setValue(position.x() / tileSize.x());
    propIndexX->setMinimum(0);
    propIndexX->setMaximum(tilesCount.x() - 1);

    propIndexX->connect(propIndexX, QOverload<int>::of(&QSpinBox::valueChanged), propIndexX, [this, tileSize](int value)
    {
        setX(value * tileSize.x());
    });

    QSpinBox* propIndexY = new QSpinBox();
    propIndexY->setValue(position.y() / tileSize.y());
    propIndexY->setMinimum(0);
    propIndexY->setMaximum(tilesCount.y() - 1);

    propIndexY->connect(propIndexY, QOverload<int>::of(&QSpinBox::valueChanged), propIndexY, [this, tileSize](int value)
    {
        setY(value * tileSize.y());
    });

    System::mToolProperties->addParent("Базовые");
    System::mToolProperties->addProperty("Базовые", "Тип", propType);
    System::mToolProperties->addProperty("Базовые", "Индекс по X", propIndexX);
    System::mToolProperties->addProperty("Базовые", "Индекс по Y", propIndexY);
}

void Object::setPosition(const QPointF& position)
{
    setPos(position);
    updateProperties();
}

QString Object::objectType() const
{
    return mType;
}

void Object::setIdImageBounds(int idImageBounds)
{
    mIdImageBounds = idImageBounds;
}

int Object::idImageBounds() const
{
    return mIdImageBounds;
}

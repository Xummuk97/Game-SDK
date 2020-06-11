#include "objectgame.h"
#include "engine/game/systemgame.h"

ObjectGame::ObjectGame(int idImageBounds, const QPointF &position, const QString& type)
    : QObject(),
      mType(type),
      mSelf(SystemGame::mScripts->getNewQObject(this))
{
    mSprite = new sf::Sprite();
    mSprite->setTexture(*SystemGame::mTexture);
    mSprite->setTextureRect(SystemGame::mImageBounds[idImageBounds]);
    mSprite->setPosition(position.x(), position.y());
}

void ObjectGame::draw()
{
    SystemGame::mCanvas->draw(*mSprite);
}

QJSValue ObjectGame::self()
{
    return mSelf;
}

QString ObjectGame::objectType() const
{
    return mType;
}

void ObjectGame::move(float x, float y)
{
    mSprite->move(x, y);
}

QJSValue ObjectGame::position()
{
    QJSValue value = SystemGame::mScripts->getNewObject();
    sf::Vector2f pos = mSprite->getPosition();
    value.setProperty("x", pos.x);
    value.setProperty("y", pos.y);
    return value;
}

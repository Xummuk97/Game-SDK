#include "layergame.h"
#include "engine/game/systemgame.h"

LayerGame::LayerGame(const QString& name)
    : mName(name)
{

}

void LayerGame::addObject(int idImageBounds, const QPointF &position, const QString &type)
{
    mObjects.push_back(new ObjectGame(idImageBounds, position, type));
}

QString LayerGame::name() const
{
    return mName;
}

void LayerGame::update()
{
    static sf::Clock clock;
    float deltaTime = clock.getElapsedTime().asSeconds();
    clock.restart();

    for (ObjectGame* obj : mObjects)
    {
        SystemGame::mScripts->variable("callbackUpdateObjects").call(QJSValueList() << obj->self() << deltaTime);
    }
}

void LayerGame::draw()
{
    for (ObjectGame* obj : mObjects)
    {
        obj->draw();
    }
}

#ifndef OBJECTGAME_H
#define OBJECTGAME_H

#include <QtCore>
#include <QtWidgets>
#include <QtQml>
#include <SFML/Graphics.hpp>

class ObjectGame : public QObject
{
    Q_OBJECT
public:
    Q_INVOKABLE ObjectGame(int idImageBounds, const QPointF &position, const QString& type);
    virtual ~ObjectGame() = default;

    void draw();

    QJSValue self();

public slots:
    QString objectType() const;
    void move(float x, float y);

    QJSValue position();

private:
    QString mType;
    sf::Sprite* mSprite;
    QJSValue mSelf;
};

#endif // OBJECTGAME_H

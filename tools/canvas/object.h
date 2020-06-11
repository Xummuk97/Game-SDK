#ifndef OBJECT_H
#define OBJECT_H

#include <QGraphicsPixmapItem>

class Object : public QObject, public QGraphicsPixmapItem
{
public:
    explicit Object(const QString& type = "Base", QGraphicsItem *parent = nullptr);
    virtual ~Object() = default;

    static Object* pixmapItemToObject(QGraphicsPixmapItem* item);
    static QGraphicsPixmapItem* objectToPixmapItem(Object* object);
    static Object* itemToObject(QGraphicsItem* item);
    static QGraphicsItem* objectToItem(Object* object);

    void updateProperties();
    void setPosition(const QPointF& position);
    QString objectType() const;

    void setIdImageBounds(int idImageBounds);
    int idImageBounds() const;

private:
    int mIdImageBounds;
    QString mType;
};

#endif // OBJECT_H

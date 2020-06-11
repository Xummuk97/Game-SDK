#include "canvas.h"
#include "engine/sdk/system.h"

ToolCanvas::ToolCanvas(QWidget *parent, const QPoint& tilesCount, const QPoint& tileSize)
    : QGraphicsView(parent),
      mScene(new QGraphicsScene(this)),
      mTilesCount(tilesCount),
      mTileSize(tileSize),
      mCurrentLayer(nullptr),
      mIsLoadImage(false),
      mMoveObject(nullptr),
      mCurrentObject(nullptr)
{
    setMouseTracking(true);
    setFrameShape(QFrame::NoFrame);
    setScene(mScene);

    QPoint mapSize = sizeMap();
    setSceneRect(0, 0, mapSize.x(), mapSize.y());
}

QPoint ToolCanvas::tilesCount() const
{
    return mTilesCount;
}

QPoint ToolCanvas::tileSize() const
{
    return mTileSize;
}

QPoint ToolCanvas::sizeMap() const
{
    return QPoint(mTilesCount.x() * mTileSize.x(), mTilesCount.y() * mTileSize.y());
}

void ToolCanvas::drawBackground(QPainter *painter, const QRectF &rect)
{
    QPoint mapSize = sizeMap();

    painter->fillRect(rect, QBrush(QColor("#bababa")));
    painter->fillRect(QRectF(0, 0, mapSize.x(), mapSize.y()), QBrush(QColor("#757575")));
}

void ToolCanvas::drawForeground(QPainter *painter, const QRectF &)
{
    QPoint mapSize = sizeMap();

    QPen penLines;
    penLines.setColor(QColor("#000"));
    penLines.setWidthF(0.4);
    penLines.setStyle(Qt::PenStyle::DotLine);
    painter->setPen(penLines);

    for (int x = 0; x <= mTilesCount.x(); x++)
    {
        painter->drawLine(x * mTileSize.x(), 0, x * mTileSize.x(), mapSize.y());
    }

    for (int y = 0; y <= mTilesCount.y(); y++)
    {
        painter->drawLine(0, y * mTileSize.y(), mapSize.x(), y * mTileSize.y());
    }
}

void ToolCanvas::wheelEvent(QWheelEvent *event)
{
    const double scaleFactor = 1.15;

    if (event->delta() > 0)
    {
        scale(scaleFactor, scaleFactor);
    }
    else
    {
        scale(1.0 / scaleFactor, 1.0 / scaleFactor);
    }
}

void ToolCanvas::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::MouseButton::LeftButton)
    {
        if (System::mToolsType == ToolsType::Move && mMoveObject)
        {
            mMoveObject = nullptr;
            return;
        }

        if (!mIsLoadImage)
        {
            QMessageBox::critical(this, "Ошибка", "Вы не загрузили изображение!");
            return;
        }

        if (!mCurrentLayer)
        {
            QMessageBox::critical(this, "Ошибка", "Вы не создали слой!");
            return;
        }

        QPointF scenePos = mapToScene(event->pos());
        scenePos = normalCoord(scenePos);

        Object* object = objectFromPosition(mCurrentLayer, scenePos);

        switch (System::mToolsType)
        {
        case ToolsType::Select:
            if (object)
            {
                object->updateProperties();
                mCurrentObject = object;
            }
            break;

        case ToolsType::Add:
            if (!object)
            {
                Object* object = addObject(mCurrentLayer, mCurrentImageBounds, scenePos);
                mCurrentObject = object;
            }
            else
            {
                removeObject(mCurrentLayer, object);
                Object* object = addObject(mCurrentLayer, mCurrentImageBounds, scenePos);
                mCurrentObject = object;
            }
            break;

        case ToolsType::Move:
            if (object)
            {
                object->updateProperties();
                mMoveObject = object;
                mCurrentObject = object;
            }
            break;

        case ToolsType::Remove:
            if (object)
            {
                removeObject(mCurrentLayer, object);
            }
            break;
        }
    }
}

void ToolCanvas::mouseMoveEvent(QMouseEvent *event)
{
    if (mMoveObject)
    {
        QPointF scenePos = mapToScene(event->pos());
        scenePos = normalCoord(scenePos);

        mMoveObject->setPosition(scenePos);
    }
}

void ToolCanvas::loadImage(const QString &path)
{
    mIsLoadImage = true;
    mImageFileName = QFileInfo(path).fileName();
    mImageFileFormat = QFileInfo(path).suffix();

    mImage.load(path);

    loadImageBounds();
}

QPixmap ToolCanvas::imageCopy(const QRect &rect)
{
    return mImage.copy(rect);
}

QList<QRect> ToolCanvas::imageBounds() const
{
    return mImageBounds;
}

void ToolCanvas::setCurrentImageBounds(int index)
{
    mCurrentImageBounds = index;
}

QString ToolCanvas::imageFileName() const
{
    return mImageFileName;
}

QString ToolCanvas::imageFileFormat() const
{
    return mImageFileFormat;
}

QPixmap ToolCanvas::imageObject()
{
    return mImage;
}

void ToolCanvas::addLayer(const QString &name)
{
    Layer* layer = new Layer(name);
    layer->setZValue(mLayers.size() - 1);

    mLayers.push_back(layer);

    mScene->addItem(layer);
}

void ToolCanvas::setCurrentLayer(Layer* layer)
{
    mCurrentLayer = layer;
}

QList<Layer*> ToolCanvas::layers() const
{
    return mLayers;
}

Layer *ToolCanvas::currentLayer()
{
    return mCurrentLayer;
}

void ToolCanvas::removeLayer(Layer* layer)
{
    for (QGraphicsItem* item : layer->childItems())
    {
        Object* object = Object::itemToObject(item);
        removeObject(layer, object);
    }

    mScene->removeItem(layer);

    for (QList<Layer*>::iterator it = mLayers.begin(); it != mLayers.end();)
    {
        if (*it == layer)
        {
            bool isCurrentLayer = *it == mCurrentLayer;
            it = mLayers.erase(it);

            if (*it && isCurrentLayer)
            {
                mCurrentLayer = *it;
                setCurrentLayer(*it);
            }

            updateLayersZValue();
            return;
        }
        else
        {
            it++;
        }
    }
}

void ToolCanvas::layerToUp(Layer *layer)
{
    for (int i = 0; i < mLayers.size(); i++)
    {
        if (mLayers[i] == layer)
        {
            mLayers.swapItemsAt(i, i + 1);

            updateLayersZValue();
            return;
        }
    }
}

void ToolCanvas::layerToDown(Layer *layer)
{
    for (int i = 0; i < mLayers.size(); i++)
    {
        if (mLayers[i] == layer)
        {
            mLayers.swapItemsAt(i - 1, i);

            updateLayersZValue();
            return;
        }
    }
}

Object* ToolCanvas::addObject(Layer* layer, int idImageBounds, const QPointF &position, const QString& type)
{
    if (layer)
    {
        Object* object = new Object(type);
        object->setPixmap(mImage.copy(mImageBounds[idImageBounds]));
        object->setPos(position);
        object->setIdImageBounds(idImageBounds);
        object->updateProperties();
        layer->addObject(object);

        mScene->addItem(object);
        return object;
    }
    return nullptr;
}

void ToolCanvas::removeObject(Layer* layer, Object *object)
{
    if (layer)
    {
        mScene->removeItem(object);
        layer->removeFromGroup(object);
    }
}

Object *ToolCanvas::objectFromPosition(Layer* layer, QPointF normalPosition)
{
    if (layer)
    {
        for (QGraphicsItem* item : layer->childItems())
        {
            if (item->pos() == normalPosition)
            {
                return Object::itemToObject(item);
            }
        }
    }
    return nullptr;
}

Object *ToolCanvas::moveObject()
{
    return mMoveObject;
}

Object *ToolCanvas::currentObject()
{
    return mCurrentObject;
}

QPointF ToolCanvas::normalCoord(QPointF coord)
{
    QPointF _coord;
    _coord.setX(int(coord.x() / mTileSize.x()) * mTileSize.x());
    _coord.setY(int(coord.y() / mTileSize.y()) * mTileSize.y());
    return _coord;
}

void ToolCanvas::saveToFile(const QString &path)
{
    QRect rect = QRect(0, 0, sizeMap().x(), sizeMap().y());

    QPixmap pixmap(rect.size());
    QPainter painter(&pixmap);

    render(&painter, pixmap.rect(), rect);
    pixmap.save(path);
}

void ToolCanvas::loadImageBounds()
{
    mCurrentImageBounds = 0;
    mImageBounds.clear();

    QSize imageSize = mImage.size();
    int countX = imageSize.width() / mTileSize.x();
    int countY = imageSize.height() / mTileSize.y();

    for (int y = 0; y < countY; y++)
    {
        for (int x = 0; x < countX; x++)
        {
            QRect rect = QRect(x * mTileSize.x(), y * mTileSize.y(), mTileSize.x(), mTileSize.y());
            mImageBounds.push_back(rect);
        }
    }
}

void ToolCanvas::updateLayersZValue()
{
    int zValue = 0;

    for (Layer* layer : mLayers)
    {
        layer->setZValue(zValue);

        zValue++;
    }
}

Layer *ToolCanvas::layerFromName(const QString &name)
{
    for (Layer* layer : mLayers)
    {
        if (layer->name() == name)
        {
            return layer;
        }
    }
    return nullptr;
}

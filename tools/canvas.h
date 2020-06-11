#ifndef CANVAS_H
#define CANVAS_H

#include <QtCore>
#include <QtWidgets>
#include "tools/canvas/layer.h"

class ToolCanvas : public QGraphicsView
{
public:
    ToolCanvas(QWidget* parent, const QPoint& tilesCount, const QPoint& tileSize);
    virtual ~ToolCanvas() = default;

    QGraphicsScene* scene();
    QPoint tilesCount() const;
    QPoint tileSize() const;
    QPoint sizeMap() const;

    void drawBackground(QPainter *painter, const QRectF &rect) override;
    void drawForeground(QPainter *painter, const QRectF &rect) override;
    void wheelEvent(QWheelEvent* event) override;
    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;

    void loadImage(const QString& path);
    QPixmap imageCopy(const QRect& rect);
    QList<QRect> imageBounds() const;
    void setCurrentImageBounds(int index);
    QPixmap imageObject();
    QString imageFileName() const;
    QString imageFileFormat() const;

    void addLayer(const QString& name);
    void setCurrentLayer(Layer* layer);
    QList<Layer*> layers() const;
    Layer* currentLayer();
    void removeLayer(Layer* layer);
    void layerToUp(Layer* layer);
    void layerToDown(Layer* layer);
    Layer* layerFromName(const QString& name);

    Object* addObject(Layer* layer, int idImageBounds, const QPointF& position, const QString& type = "Base");
    void removeObject(Layer* layer, Object* object);
    Object* objectFromPosition(Layer* layer, QPointF normalPosition);
    Object* moveObject();
    Object* currentObject();

    QPointF normalCoord(QPointF coord);

    void saveToFile(const QString& path);

private:
    QGraphicsScene* mScene;
    QPoint mTilesCount, mTileSize;
    bool mIsLoadImage;
    QPixmap mImage;
    QList<Layer*> mLayers;
    Layer* mCurrentLayer;
    QList<QRect> mImageBounds;
    int mCurrentImageBounds;
    Object *mMoveObject, *mCurrentObject;
    QString mImageFileName, mImageFileFormat;

    void loadImageBounds();
    void updateLayersZValue();
};

#endif // CANVAS_H

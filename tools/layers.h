#ifndef TOOLLAYERS_H
#define TOOLLAYERS_H

#include <QtCore>
#include <QtWidgets>

class ToolLayers : public QDockWidget
{
public:
    ToolLayers(QWidget *parent = nullptr);
    virtual ~ToolLayers() = default;

    void update();

private:
    QListWidget* mListWidget;

    void addItem(const QString& currentLayer, const QString& layerName, bool isVisible);
    void update(const QString& currentLayer);
};

#endif // TOOLLAYERS_H

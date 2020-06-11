#ifndef PROJECT_H
#define PROJECT_H

#include <QtCore>
#include <QtWidgets>
#include "tools/canvas.h"

class Project
{
public:
    Project(QWidget* parent, const QString& name, const QString& description, const QString& version, const QPoint& tilesCount, const QPoint& tileSize);
    ~Project() = default;

    QString name() const;
    QString description() const;
    QString version() const;

    ToolCanvas* canvas();
    void saveToXMLFile(const QString& path);

    static Project* loadFromXMLFile(QWidget* parent, const QString& path);

private:
    QString mName, mDescription, mVersion;
    ToolCanvas* mCanvas;
    QPixmap mImage;
};

#endif // PROJECT_H

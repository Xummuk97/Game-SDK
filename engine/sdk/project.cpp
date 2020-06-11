#include "project.h"
#include "engine/sdk/system.h"
#include <QtXml>

/*
    TODO: qxmlstreamwriter
*/

Project::Project(QWidget* parent, const QString& name, const QString& description, const QString& version, const QPoint& tilesCount, const QPoint& tileSize)
    : mName(name),
      mDescription(description),
      mVersion(version),
      mCanvas(new ToolCanvas(parent, tilesCount, tileSize))
{
    parent->setWindowTitle(QString("Игровой движок @ %1").arg(mName));
    System::mToolProjects->addTab(mCanvas, mName);
}

QString Project::name() const
{
    return mName;
}

QString Project::description() const
{
    return mDescription;
}

QString Project::version() const
{
    return mVersion;
}

ToolCanvas *Project::canvas()
{
    return mCanvas;
}

void Project::saveToXMLFile(const QString &path)
{
    QDomDocument doc;
    QDomNode header = doc.createProcessingInstruction("xml", "version=\"1.0\" encoding=\"charset-1251\"");
    doc.appendChild(header);



    QDomElement docRoot = doc.createElement("project");

    docRoot.setAttribute("name", mName);
    docRoot.setAttribute("description", mDescription);
    docRoot.setAttribute("version", mVersion);
    docRoot.setAttribute("image", QString("../res/%1").arg(mCanvas->imageFileName()));
    docRoot.setAttribute("js", "main.js");

    QDomElement docCanvas = doc.createElement("canvas");

    for (Layer* layer : mCanvas->layers())
    {
        if (layer->isVisible())
        {
            QDomElement docLayer = doc.createElement("layer");

            docLayer.setAttribute("name", layer->name());

            for (QGraphicsItem* item : layer->childItems())
            {
                QDomElement docObject = doc.createElement("object");

                Object* object = Object::itemToObject(item);

                QString type = object->objectType();
                QPointF position = object->pos();
                int idImageBounds = object->idImageBounds();

                docObject.setAttribute("type", type);
                docObject.setAttribute("x", position.x());
                docObject.setAttribute("y", position.y());
                docObject.setAttribute("idImageBounds", idImageBounds);

                docLayer.appendChild(docObject);
            }

            docCanvas.appendChild(docLayer);
        }
    }

    docRoot.appendChild(docCanvas);
    doc.appendChild(docRoot);

    QDir dir;
    QString _path = QString("%1/%2").arg(path).arg(name());
    dir.mkdir(_path);

    QFile mFile(QString("%1/main.js").arg(_path));
    mFile.open(QIODevice::WriteOnly);
    mFile.close();

    QFile file(QString("%1/%2.xml").arg(_path).arg(name()));
    if (file.open(QIODevice::WriteOnly))
    {
        QTextStream(&file) << doc.toString();
        file.close();
    }

    _path = QString("%1/res").arg(path);
    dir.mkdir(_path);

    mCanvas->imageObject().save(QString("%1/%2").arg(_path).arg(mCanvas->imageFileName()));
}

Project *Project::loadFromXMLFile(QWidget* parent, const QString &path)
{
    if (path == "")
    {
        return nullptr;
    }

    QDomDocument doc;
    QFile file(path);

    if (!file.open(QIODevice::ReadOnly))
    {
        return nullptr;
    }

    if (!doc.setContent(&file))
    {
        file.close();
        return nullptr;
    }
    file.close();

    QDomElement root = doc.documentElement();

    QString name = root.attribute("name");
    QString description = root.attribute("description");
    QString version = root.attribute("version");
    QString image = root.attribute("image");

    Project* project = new Project(parent, name, description, version, QPoint(32, 32), QPoint(64, 64));

    image = QString("%1/%2").arg(QFileInfo(path).path()).arg(image);
    project->canvas()->loadImage(image);

    QMessageBox::about(0, "", QString("%1").arg(image));

    QDomElement canvas = root.firstChildElement("canvas");

    for (QDomElement layer = canvas.firstChildElement("layer"); !layer.isNull(); layer = layer.nextSiblingElement("layer"))
    {
        QString layerName = layer.attribute("name");
        project->canvas()->addLayer(layerName);

        for (QDomElement object = layer.firstChildElement("object"); !object.isNull(); object = object.nextSiblingElement("object"))
        {
            int idImageBounds = object.attribute("idImageBounds").toInt();
            int x = object.attribute("x").toInt();
            int y = object.attribute("y").toInt();
            QString type = object.attribute("type");

            QMessageBox::about(0, "", QString("%1 %2 %3 %4").arg(idImageBounds).arg(x).arg(y).arg(type));

            project->canvas()->addObject(project->canvas()->layerFromName(layerName), idImageBounds, QPointF(x, y), type);
        }
    }

    return project;
}

#include <QApplication>
#include "engine/engine.h"
#include <QtXml>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QString mode;

    QDomDocument doc;
    QFile file("settings.xml");

    if (!file.open(QIODevice::ReadOnly))
    {
        return 0;
    }

    if (!doc.setContent(&file))
    {
        file.close();
        return 0;
    }
    file.close();

    QDomElement root = doc.documentElement();

    for (QDomElement element = root.firstChildElement("setting"); !element.isNull(); element = element.nextSiblingElement("setting"))
    {
        if (element.attribute("key") == "mode")
        {
            mode = element.attribute("value");
        }
    }

    EngineStartType startType = mode == "sdk" ? EngineStartType::SDK : EngineStartType::Game;

    Engine engine(startType);
    engine.start();
    return a.exec();
}

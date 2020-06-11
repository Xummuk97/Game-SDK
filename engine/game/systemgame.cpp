#include "systemgame.h"
#include <QtXml>

Scripts*                SystemGame::mScripts;
MyCanvas*               SystemGame::mCanvas;
QGridLayout*            SystemGame::mGrid;
sf::Texture*            SystemGame::mTexture;
QList<sf::IntRect>      SystemGame::mImageBounds;
QList<LayerGame*>       SystemGame::mLayers;

SystemGame::SystemGame()
    : QObject()
{

}

void SystemGame::loadProject()
{
    QDomDocument doc;
    QFile file("projects/new/new.xml");

    if (!file.open(QIODevice::ReadOnly))
    {
        return;
    }

    if (!doc.setContent(&file))
    {
        file.close();
        return;
    }
    file.close();

    QDomElement root = doc.documentElement();

    QString name = root.attribute("name");
    QString description = root.attribute("description");
    QString version = root.attribute("version");
    QString image = root.attribute("image");
    QString js = root.attribute("js");

    SystemGame::mScripts = new Scripts(QString("%1/%2").arg(QFileInfo("projects/new/new.xml").path()).arg(js));
    SystemGame::mScripts->setVariable("game", new SystemGame);

    const int BUTTONS_SIZE = BUTTONS.size();
    for (int i = 0; i < BUTTONS_SIZE; i++)
    {
        SystemGame::mScripts->setVariable("KB_" + BUTTONS[i].toUpper(), i);
    }

    SystemGame::mScripts->eval("setup()");

    image = QString("%1/%2").arg(QFileInfo("projects/new/new.xml").path()).arg(image);
    SystemGame::mTexture = new sf::Texture();
    SystemGame::mTexture->loadFromFile(image.toStdString());

    sf::Vector2u imageSize = SystemGame::mTexture->getSize();
    int countX = imageSize.x / 64;
    int countY = imageSize.y / 64;

    for (int y = 0; y < countY; y++)
    {
        for (int x = 0; x < countX; x++)
        {
            SystemGame::mImageBounds.push_back(sf::IntRect(x * 64, y * 64, 64, 64));
        }
    }

    QDomElement canvas = root.firstChildElement("canvas");

    for (QDomElement layer = canvas.firstChildElement("layer"); !layer.isNull(); layer = layer.nextSiblingElement("layer"))
    {
        QString layerName = layer.attribute("name");
        LayerGame* layerObj = new LayerGame(layerName);

        for (QDomElement object = layer.firstChildElement("object"); !object.isNull(); object = object.nextSiblingElement("object"))
        {
            int idImageBounds = object.attribute("idImageBounds").toInt();
            int x = object.attribute("x").toInt();
            int y = object.attribute("y").toInt();
            QString type = object.attribute("type");

            layerObj->addObject(idImageBounds, QPointF(x, y), type);
        }

        SystemGame::mLayers.push_back(layerObj);
    }
}

void SystemGame::setCallbackUpdateObjects(QJSValue value)
{
    SystemGame::mScripts->setVariable("callbackUpdateObjects", value);
}

bool SystemGame::isKeyPressed(int key)
{
    return sf::Keyboard::isKeyPressed((sf::Keyboard::Key)key);
}

void SystemGame::messageBox_about(const QString &message)
{
    QMessageBox::about(nullptr, "Сообщение", message);
}

void SystemGame::messageBox_critical(const QString &message)
{
    QMessageBox::critical(nullptr, "Ошибка", message);
}

void SystemGame::grid_create()
{
    mGrid = new QGridLayout(mCanvas);
}

void SystemGame::grid_createButton(const QString &text, int x, int y, QJSValue callbackClicked)
{
    if (mGrid)
    {
        QPushButton* button = new QPushButton(text);
        mGrid->addWidget(button, y, x);

        static int id = 0;
        QString callbackId = QString("button_callback_%1").arg(id);
        id++;

        mScripts->setVariable(callbackId, callbackClicked);

        button->connect(button, &QPushButton::clicked, button, [&, callbackId]()
        {
            SystemGame::mScripts->variable(callbackId).call();
        });
    }
}

void SystemGame::grid_horizontalSpacer(int x, int y)
{
    if (mGrid)
    {
        mGrid->addItem(new QSpacerItem(1, 1, QSizePolicy::Expanding, QSizePolicy::Minimum), y, x);
    }
}

void SystemGame::grid_verticalSpacer(int x, int y)
{
    if (mGrid)
    {
        mGrid->addItem(new QSpacerItem(1, 1, QSizePolicy::Minimum, QSizePolicy::Expanding), y, x);
    }
}

#ifndef SYSTEMGAME_H
#define SYSTEMGAME_H

#include <QtQml>
#include <QtCore>
#include <QtWidgets>
#include "engine/scripts.h"
#include "engine/game/sfmlcanvas.h"
#include <SFML/Graphics.hpp>
#include "engine/game/layergame.h"

const QVector<QString> BUTTONS =
{
    "A", "B", "C", "D", "E", "F", "G", "H", "I", "J", "K", "L", "M", "N", "O", "P", "Q", "R", "S", "T", "U", "V", "W", "X", "Y", "Z",

    "Num0","Num1", "Num2", "Num3", "Num4","Num5", "Num6", "Num7", "Num8", "Num9",

    "Escape", "LControl", "LShift","LAlt", "LSystem", "RControl", "RShift", "RAlt", "RSystem", "Menu", "LBracket",
    "RBracket", "Semicolon", "Comma", "Period","Quote", "Slash", "Backslash", "Tilde", "Equal", "Hyphen", "Space",
    "Enter","Backspace", "Tab", "PageUp", "PageDown","End", "Home", "Insert", "Delete",	"Add", "Subtract", "Multiply", "Divide",

    "Left", "Right", "Up", "Down",

    "Numpad0", "Numpad1", "Numpad2", "Numpad3", "Numpad4", "Numpad5", "Numpad6", "Numpad7","Numpad8", "Numpad9",

    "F1", "F2","F3", "F4", "F5", "F6","F7", "F8", "F9", "F10","F11", "F12", "F13", "F14","F15",

    "Pause"
};

class SystemGame : public QObject
{
    Q_OBJECT
public:
    Q_INVOKABLE SystemGame();
    virtual ~SystemGame() = default;

    static Scripts* mScripts;
    static MyCanvas* mCanvas;
    static QGridLayout* mGrid;
    static sf::Texture* mTexture;
    static QList<sf::IntRect> mImageBounds;
    static QList<LayerGame*> mLayers;

    static void loadProject();

public slots:
    static void setCallbackUpdateObjects(QJSValue value);

    static bool isKeyPressed(int key);

    static void messageBox_about(const QString& message);
    static void messageBox_critical(const QString& message);

    static void grid_create();
    static void grid_createButton(const QString& text, int x, int y, QJSValue callbackClicked);
    static void grid_horizontalSpacer(int x, int y);
    static void grid_verticalSpacer(int x, int y);
};

#endif // SYSTEMGAME_H

#ifndef SFMLCANVAS_H
#define SFMLCANVAS_H

#include <SFML/Graphics.hpp>
#include <QtCore>
#include <QtWidgets>

class QSFMLCanvas : public QWidget, public sf::RenderWindow
{
public:
    QSFMLCanvas(QWidget* Parent, const QPoint& Position, const QSize& Size, unsigned int FrameTime = 0);
    virtual ~QSFMLCanvas();

private:
    virtual void OnInit();

    virtual void OnUpdate();

    virtual QPaintEngine* paintEngine() const;

    virtual void showEvent(QShowEvent*);

    virtual void paintEvent(QPaintEvent*);

    QTimer myTimer;
    bool   myInitialized;
};

class MyCanvas : public QSFMLCanvas
{
public:
    MyCanvas(QWidget* Parent, const QPoint& Position, const QSize& Size);
    virtual ~MyCanvas() = default;

private :
    void OnInit();
    void OnUpdate();
};

#endif // SFMLCANVAS_H

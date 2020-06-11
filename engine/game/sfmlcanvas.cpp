#include "sfmlcanvas.h"
#include "engine/game/systemgame.h"

QSFMLCanvas::QSFMLCanvas(QWidget *Parent, const QPoint &Position, const QSize &Size, unsigned int FrameTime) :
    QWidget       (Parent),
    myInitialized (false)
{
    // Setup some states to allow direct rendering into the widget
        setAttribute(Qt::WA_PaintOnScreen);
        setAttribute(Qt::WA_OpaquePaintEvent);
        setAttribute(Qt::WA_NoSystemBackground);

        // Set strong focus to enable keyboard events to be received
        setFocusPolicy(Qt::StrongFocus);

        // Setup the widget geometry
        move(Position);
        resize(Size);

        // Setup the timer
        myTimer.setInterval(FrameTime);
}

QSFMLCanvas::~QSFMLCanvas()
{

}

void QSFMLCanvas::OnInit()
{

}

void QSFMLCanvas::OnUpdate()
{

}

QPaintEngine *QSFMLCanvas::paintEngine() const
{
    return 0;
}

void QSFMLCanvas::showEvent(QShowEvent *)
{
    if (!myInitialized)
        {
            // SFML will get an updated view of the windows
            // Create the SFML window with the widget handle
            sf::Window::create(sf::WindowHandle(winId()));

            // Let the derived class do its specific stuff
            OnInit();

            // Setup the timer to trigger a refresh at specified framerate
            connect(&myTimer, SIGNAL(timeout()), this, SLOT(repaint()));
            myTimer.start();

            myInitialized = true;
        }
}

void QSFMLCanvas::paintEvent(QPaintEvent *)
{
    // Let the derived class do its specific stuff
        OnUpdate();

        // Display on screen
        display();
}

MyCanvas::MyCanvas(QWidget *Parent, const QPoint &Position, const QSize &Size)
    : QSFMLCanvas(Parent, Position, Size)
{

}

void MyCanvas::OnInit()
{

}

void MyCanvas::OnUpdate()
{
    // update
    for (LayerGame* layer : SystemGame::mLayers)
    {
        layer->update();
    }

    clear(sf::Color(255, 255, 255));

    // draw
    for (LayerGame* layer : SystemGame::mLayers)
    {
        layer->draw();
    }
}

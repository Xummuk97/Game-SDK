#ifndef BASEWINDOW_H
#define BASEWINDOW_H

#include <QMainWindow>

class BaseWindow : public QMainWindow
{
    Q_OBJECT
public:
    BaseWindow(QWidget* parent = Q_NULLPTR);
    virtual ~BaseWindow() = default;

    static QSize minSize() { return { 800, 600 }; }

protected:
    virtual void onLoad();
};

#endif // BASEWINDOW_H

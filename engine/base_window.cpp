#include "base_window.h"
#include <QMessageBox>

BaseWindow::BaseWindow(QWidget* parent)
    : QMainWindow(parent)
{
}

void BaseWindow::onLoad()
{
    setMinimumSize(BaseWindow::minSize());
    showMaximized();
}

#include "engine/sdk/window.h"
#include "engine/sdk/system.h"
#include <QMessageBox>
#include "tools/canvas/object.h"
#include <QtXml>

WindowSDK::WindowSDK(QWidget* parent)
    : BaseWindow(parent)
{
    onLoad();
}

void WindowSDK::onLoad()
{
    System::mToolProjects = new ToolProjects(this);
    setCentralWidget(System::mToolProjects);

    System::mToolProjects->addProject(new Project(this, "new", "", "1.0.0", QPoint(32, 32), QPoint(64, 64)));


    System::mToolSelectImage = new ToolSelectImage(this);
    addDockWidget(Qt::RightDockWidgetArea, System::mToolSelectImage);


    System::mToolLayers = new ToolLayers(this);
    addDockWidget(Qt::RightDockWidgetArea, System::mToolLayers);


    System::mToolProperties = new ToolProperties(this);
    addDockWidget(Qt::RightDockWidgetArea, System::mToolProperties);


    System::mToolsType = ToolsType::Add;


    loadMenu();
    BaseWindow::onLoad();
}

void WindowSDK::loadMenu()
{
    {
        QMenu* menu = menuBar()->addMenu("Файл");

        QAction* openProject = new QAction("Открыть проект");
        QAction* saveProject = new QAction("Сохранить проект");
        QAction* saveAsProject = new QAction("Сохранить проект как...");
        QAction* saveAsImageMap = new QAction("Сохранить изображение карты как...");
        QAction* quit = new QAction("Выход");

        menu->addAction(openProject);
        menu->addSeparator();
        menu->addAction(saveProject);
        menu->addAction(saveAsProject);
        menu->addSeparator();
        menu->addAction(saveAsImageMap);
        menu->addSeparator();
        menu->addAction(quit);

        quit->connect(quit, &QAction::triggered, quit, [&]() { close(); });

        openProject->setEnabled(false);
        saveProject->setEnabled(false);

        openProject->connect(openProject, &QAction::triggered, openProject, [&]()
        {
            QString path = QFileDialog::getOpenFileName(this, "Открыть проект", QDir::currentPath(), "Проект (*.xml)");
            Project* project = Project::loadFromXMLFile(this, path);
            System::mToolProjects->addProject(project);
        });

        saveAsProject->connect(saveAsProject, &QAction::triggered, saveAsProject, [&]()
        {
            QString path = QFileDialog::getExistingDirectory(this, "Выберите папку для сохранения проекта", QDir::currentPath());
            System::mCurrentProject->saveToXMLFile(path);
        });

        saveAsImageMap->connect(saveAsImageMap, &QAction::triggered, saveAsImageMap, [&]()
        {
            QString path = QFileDialog::getSaveFileName(this, "Сохранить изображение карты как...", QDir::currentPath(), "Изображение (*.jpeg *.png)");
            System::mCurrentProject->canvas()->saveToFile(path);
        });
    }

    {
        QMenu* menu = menuBar()->addMenu("Проект");

        QAction* setImage = new QAction("Установить изображение");

        menu->addAction(setImage);

        setImage->connect(setImage, &QAction::triggered, setImage, [&]()
        {
            QString path = QFileDialog::getOpenFileName(this, "Выберите изображение", QDir::currentPath(), "Изображение (*.jpeg *.png)");

            if (!path.isEmpty())
            {
                System::mCurrentProject->canvas()->loadImage(path);
                System::mToolSelectImage->miniCanvas()->update();
            }
        });
    }

    {
        QMenu* menu = menuBar()->addMenu("Инструменты");

        QAction* selectObjects = new QAction("Выбирать объекты");
        QAction* addObjects = new QAction("Добавлять объекты");
        QAction* moveObjects = new QAction("Перемещать объекты");
        QAction* removeObjects = new QAction("Удалять объекты");

        menu->addAction(selectObjects);
        menu->addAction(addObjects);
        menu->addAction(moveObjects);
        menu->addAction(removeObjects);

        selectObjects->connect(selectObjects, &QAction::triggered, selectObjects, [&]()
        {
            System::mToolsType = ToolsType::Select;
        });

        addObjects->connect(addObjects, &QAction::triggered, addObjects, [&]()
        {
            System::mToolsType = ToolsType::Add;
        });

        moveObjects->connect(moveObjects, &QAction::triggered, moveObjects, [&]()
        {
            System::mToolsType = ToolsType::Move;
        });

        removeObjects->connect(removeObjects, &QAction::triggered, removeObjects, [&]()
        {
            System::mToolsType = ToolsType::Remove;
        });
    }

    {
        QMenu* menu = menuBar()->addMenu("Справка");

        QAction* help = new QAction("Справка");
        QAction* author = new QAction("Автор");

        menu->addAction(help);
        menu->addAction(author);
    }
}

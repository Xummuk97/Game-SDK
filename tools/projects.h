#ifndef TOOL_PROJECTS_H
#define TOOL_PROJECTS_H

#include <QtCore>
#include <QTabWidget>
#include "engine/sdk/project.h"

class ToolProjects : public QTabWidget
{
public:
    ToolProjects(QWidget* parent = Q_NULLPTR);
    virtual ~ToolProjects() = default;

    void addProject(Project* project);
};

#endif // TOOL_PROJECTS_H

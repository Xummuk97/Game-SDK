#include "projects.h"
#include "engine/sdk/system.h"

ToolProjects::ToolProjects(QWidget* parent)
    : QTabWidget(parent)
{
}

void ToolProjects::addProject(Project* project)
{
    System::mProjects[project->name()] = project;
    System::mCurrentProject = project;
}

#ifndef SYSTEM_H
#define SYSTEM_H

#include <QtCore>
#include "tools/projects.h"
#include "engine/sdk/project.h"
#include "tools/properties.h"
#include "tools/tools.h"
#include "tools/selectimage.h"
#include "tools/layers.h"

class System
{
public:
    static ToolProjects* mToolProjects;
    static QMap<QString, Project*> mProjects;
    static Project* mCurrentProject;

    static ToolProperties* mToolProperties;

    static ToolsType mToolsType;

    static ToolSelectImage* mToolSelectImage;
    static ToolLayers* mToolLayers;
};

#endif // SYSTEM_H

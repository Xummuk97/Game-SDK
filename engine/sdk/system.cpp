#include "system.h"

ToolProjects*                   System::mToolProjects;
QMap<QString, Project*>         System::mProjects;
Project*                        System::mCurrentProject;

ToolProperties*                 System::mToolProperties;

ToolsType                       System::mToolsType;

ToolSelectImage*                System::mToolSelectImage;
ToolLayers*                     System::mToolLayers;

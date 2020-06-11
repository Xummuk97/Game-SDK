#include "properties.h"

ToolProperties::ToolProperties(QWidget *parent)
    : QDockWidget(parent)
{
    this->setWindowTitle("Свойства");

    this->mTree = new QTreeWidget();
    this->mTree->header()->setSectionResizeMode(0, QHeaderView::ResizeToContents);

    QStringList headers;
    headers << "Свойство" << "Значение";
    this->mTree->setHeaderLabels(headers);

    this->setWidget(this->mTree);
}

void ToolProperties::addParent(const QString &name)
{
    QTreeWidgetItem* item = new QTreeWidgetItem(this->mTree);
    item->setText(0, name);
    item->setExpanded(true);
    this->mParents[name] = item;
}

void ToolProperties::addProperty(const QString& parent, const QString &name, QWidget *widget)
{
    QTreeWidgetItem* item;

    if (this->mParents.find(parent) != this->mParents.end())
    {
        item = new QTreeWidgetItem(this->mParents[parent]);
    }
    else
    {
        item = new QTreeWidgetItem(this->mTree);
    }

    item->setText(0, name);
    this->mTree->setItemWidget(item, 1, widget);
}

void ToolProperties::clearProperties()
{
    this->mTree->clear();
}

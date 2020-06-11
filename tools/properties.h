#ifndef TOOLPROPERTIES_H
#define TOOLPROPERTIES_H

#include <QtCore>
#include <QtWidgets>

class ToolProperties : public QDockWidget
{
public:
    ToolProperties(QWidget* parent = Q_NULLPTR);
    virtual ~ToolProperties() = default;

    void addParent(const QString& name);
    void addProperty(const QString& parent, const QString& name, QWidget* widget);
    void clearProperties();

private:
    QTreeWidget* mTree;
    QMap<QString, QTreeWidgetItem*> mParents;
};

#endif // TOOLPROPERTIES_H

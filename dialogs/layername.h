#ifndef LAYERNAME_H
#define LAYERNAME_H

#include <QtCore>
#include <QtWidgets>

class LayerName : public QDialog
{
public:
    LayerName(QWidget *parent = nullptr);
    virtual ~LayerName() = default;

    QString name() const;
    bool isValide() const;

private:
    QLineEdit* mName;
    bool mIsValide;
};

#endif // LAYERNAME_H

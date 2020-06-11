#include "layername.h"
#include "engine/sdk/system.h"

LayerName::LayerName(QWidget *parent)
    : QDialog(parent),
      mIsValide(false)
{
    setWindowTitle("Создание слоя");
    setModal(true);

    QHBoxLayout* layout = new QHBoxLayout();
    setLayout(layout);

    mName = new QLineEdit();
    QPushButton* createLayer = new QPushButton("Создать слой");

    layout->addWidget(mName);
    layout->addWidget(createLayer);

    createLayer->connect(createLayer, &QPushButton::clicked, createLayer, [&]()
    {
        QString text = mName->text();

        Layer* layer = System::mCurrentProject->canvas()->layerFromName(text);

        if (!layer)
        {
            System::mCurrentProject->canvas()->addLayer(text);
            System::mCurrentProject->canvas()->setCurrentLayer(System::mCurrentProject->canvas()->layerFromName(text));
            mIsValide = true;
            close();
        }
        else
        {
            mName->setText("");
            QMessageBox::critical(this, "Ошибка", "Слой с данным именем уже существует!");
        }
    });
}

QString LayerName::name() const
{
    return mName->text();
}

bool LayerName::isValide() const
{
    return mIsValide;
}

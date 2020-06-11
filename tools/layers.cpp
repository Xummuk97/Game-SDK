#include "layers.h"
#include "dialogs/layername.h"
#include "engine/sdk/system.h"

ToolLayers::ToolLayers(QWidget *parent)
    : QDockWidget(parent)
{
    setWindowTitle("Слои");
    setMinimumHeight(200);

    QWidget* widget = new QWidget(parent);
    setWidget(widget);

    QPalette pal(palette());

    // устанавливаем цвет фона
    pal.setColor(QPalette::Window, Qt::white);
    widget->setAutoFillBackground(true);
    widget->setPalette(pal);
    widget->show();

    QVBoxLayout* vLayout = new QVBoxLayout();
    widget->setLayout(vLayout);

    QHBoxLayout* hLayout = new QHBoxLayout();
    QPushButton* addLayer = new QPushButton("+", parent);
    QPushButton* removeLayer = new QPushButton("-", parent);
    QPushButton* layerToUp = new QPushButton("up", parent);
    QPushButton* layerToDown = new QPushButton("down", parent);

    addLayer->connect(addLayer, &QPushButton::clicked, addLayer, [&]()
    {
        LayerName layerName(this);
        layerName.show();
        layerName.exec();

        if (!layerName.isValide())
        {
            return;
        }

        QString _layerName = layerName.name();
        addItem(_layerName, _layerName, true);
    });

    removeLayer->connect(removeLayer, &QPushButton::clicked, removeLayer, [&]()
    {
        QListWidgetItem* currentItem = mListWidget->currentItem();

        if (!currentItem)
        {
            return;
        }

        System::mCurrentProject->canvas()->removeLayer(System::mCurrentProject->canvas()->currentLayer());
        delete currentItem;
    });

    layerToUp->connect(layerToUp, &QPushButton::clicked, layerToUp, [&]()
    {
        QListWidgetItem* currentItem = mListWidget->currentItem();

        if (!currentItem)
        {
            return;
        }

        if (mListWidget->currentRow() == 0)
        {
            return;
        }

        Layer* layer = System::mCurrentProject->canvas()->currentLayer();
        QString currentLayerName = layer->name();
        System::mCurrentProject->canvas()->layerToDown(System::mCurrentProject->canvas()->currentLayer());

        update(currentLayerName);
    });

    layerToDown->connect(layerToDown, &QPushButton::clicked, layerToDown, [&]()
    {
        QListWidgetItem* currentItem = mListWidget->currentItem();

        if (!currentItem)
        {
            return;
        }

        if (mListWidget->currentRow() == mListWidget->count() - 1)
        {
            return;
        }

        Layer* layer = System::mCurrentProject->canvas()->currentLayer();
        QString currentLayerName = layer->name();
        System::mCurrentProject->canvas()->layerToUp(System::mCurrentProject->canvas()->currentLayer());

        update(currentLayerName);
    });

    addLayer->setFixedSize(32, 32);
    removeLayer->setFixedSize(32, 32);
    addLayer->setFixedSize(32, 32);
    layerToUp->setFixedSize(32, 32);
    layerToDown->setFixedSize(32, 32);

    hLayout->addWidget(addLayer);
    hLayout->addWidget(removeLayer);
    hLayout->addWidget(layerToUp);
    hLayout->addWidget(layerToDown);
    hLayout->addSpacerItem(new QSpacerItem(10, 10, QSizePolicy::Expanding, QSizePolicy::Minimum));

    vLayout->addLayout(hLayout);

    mListWidget = new QListWidget(this);
    vLayout->addWidget(mListWidget);

    mListWidget->connect(mListWidget, &QListWidget::currentItemChanged, mListWidget, [&](QListWidgetItem *current, QListWidgetItem *)
    {
        if (!current)
        {
            return;
        }

        QWidget* widget = mListWidget->itemWidget(current);
        QHBoxLayout* layout = qobject_cast<QHBoxLayout*>(widget->layout());

        QLabel* label = qobject_cast<QLabel*>(layout->itemAt(1)->widget());
        System::mCurrentProject->canvas()->setCurrentLayer(System::mCurrentProject->canvas()->layerFromName(label->text()));
    });
}

void ToolLayers::update()
{
    mListWidget->clear();

    for (Layer* layer : System::mCurrentProject->canvas()->layers())
    {
        addItem(layer->name(), layer->name(), layer->isVisible());
    }
}

void ToolLayers::addItem(const QString& currentLayer, const QString &layerName, bool isVisible)
{
    QWidget* _widget = new QWidget();
    QHBoxLayout* _layout = new QHBoxLayout();
    _widget->setLayout(_layout);

    QCheckBox* isEnabled = new QCheckBox();
    isEnabled->setCheckState(isVisible ? Qt::Checked : Qt::Unchecked);

    isEnabled->connect(isEnabled, &QCheckBox::stateChanged, isEnabled, [layerName](int state)
    {
        System::mCurrentProject->canvas()->layerFromName(layerName)->setVisible(state == Qt::Checked);
    });

    QLabel* label = new QLabel(layerName);

    _layout->addWidget(isEnabled);
    _layout->addWidget(label);
    _layout->addSpacerItem(new QSpacerItem(10, 10, QSizePolicy::Expanding, QSizePolicy::Fixed));

    QListWidgetItem* item = new QListWidgetItem();
    item->setSizeHint(_widget->sizeHint());

    mListWidget->addItem(item);
    mListWidget->setItemWidget(item, _widget);

    if (layerName == currentLayer)
    {
        mListWidget->setCurrentItem(item);
    }
}

void ToolLayers::update(const QString &currentLayer)
{
    mListWidget->clear();

    for (Layer* layer : System::mCurrentProject->canvas()->layers())
    {
        addItem(currentLayer, layer->name(), layer->isVisible());
    }
}

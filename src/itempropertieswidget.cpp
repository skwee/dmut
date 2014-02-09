#include "itempropertieswidget.h"
#include "ui_itempropertieswidget.h"

#include "item.h"

ItemPropertiesWidget::ItemPropertiesWidget(QWidget *parent) :
    QWidget(parent),
    mUi(new Ui::ItemPropertiesWidget)
{
    mUi->setupUi(this);
}

ItemPropertiesWidget::~ItemPropertiesWidget()
{
    delete mUi;
}

void ItemPropertiesWidget::itemSelectionChanged(const QModelIndex& selected, const QModelIndex& deselected) {

}

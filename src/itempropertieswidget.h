#ifndef ITEMPROPERTIESWIDGET_H
#define ITEMPROPERTIESWIDGET_H

#include <QWidget>

#include "animation.h"
#include "character.h"
#include "frame.h"

namespace Ui {
class ItemPropertiesWidget;
}

class ItemPropertiesWidget : public QWidget
{
    Q_OBJECT

public:
    explicit ItemPropertiesWidget(QWidget *parent = 0);
    ~ItemPropertiesWidget();

public slots:
    void itemSelectionChanged(const QModelIndex& selected, const QModelIndex& deselected);

private:
    Ui::ItemPropertiesWidget *mUi;
};

#endif // ITEMPROPERTIESWIDGET_H

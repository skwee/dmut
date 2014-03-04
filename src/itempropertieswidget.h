#ifndef ITEMPROPERTIESWIDGET_H
#define ITEMPROPERTIESWIDGET_H

#include <QWidget>
#include <QDataWidgetMapper>

#include "characterdocument.h"
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

    void startSession(CharacterDocument* document);
    void finishSession();

public slots:
    void itemSelectionChanged(const QModelIndex& selected, const QModelIndex& deselected);
    void setSelectedItem(const QModelIndex& index);

private:
    Ui::ItemPropertiesWidget *mUi;
    QDataWidgetMapper* mCharacterMapper;
    QDataWidgetMapper* mAnimationMapper;
    QDataWidgetMapper* mFrameMapper;
};

#endif // ITEMPROPERTIESWIDGET_H

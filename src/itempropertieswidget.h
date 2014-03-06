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

signals:
    void onSpriteAtlasCreated(const QString& name);

public slots:
    void itemSelectionChanged(const QModelIndex& selected, const QModelIndex& deselected);
    void setSelectedItem(const QModelIndex& index);

private slots:
    void spriteSelected(Sprite* sprite);

private:
    Ui::ItemPropertiesWidget *mUi;
    QDataWidgetMapper* mCharacterMapper;
    QDataWidgetMapper* mAnimationMapper;
    QDataWidgetMapper* mFrameMapper;
    QModelIndex mSelectedItem;
};

#endif // ITEMPROPERTIESWIDGET_H

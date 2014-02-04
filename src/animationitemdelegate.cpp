#include "animationitemdelegate.h"

#include "item.h"
#include "animation.h"

#include <QLineEdit>
#include <QSpinBox>

AnimationItemDelegate::AnimationItemDelegate(QObject *parent) :
    QItemDelegate(parent)
{
}

void AnimationItemDelegate::setEditorData(QWidget *editor, const QModelIndex &index) const {
    if(!index.isValid()) return;

    Item* item = static_cast<Item*>(index.internalPointer());
    if(!item) return;

    QSharedPointer<Animation> animation = item->block().staticCast<Animation>();
    if(index.column() == 0) {
        static_cast<QLineEdit*>(editor)->setText(animation->name());
    } else if(index.column() == 1) {
        static_cast<QSpinBox*>(editor)->setValue(animation->fps());
    }
}

void AnimationItemDelegate::setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const {
    if(!index.isValid()) return;

    Item* item = static_cast<Item*>(index.internalPointer());
    if(!item) return;

    QSharedPointer<Animation> animation = item->block().staticCast<Animation>();
    if(index.column() == 1) {
        animation->setFps(static_cast<Animation::FramesPerSecond>(
                              static_cast<QSpinBox*>(editor)->value()
                              ));
    }
}

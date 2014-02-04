#include "frameitemdelegate.h"

#include "item.h"
#include "animation.h"

#include <QLineEdit>
#include <QSpinBox>

FrameItemDelegate::FrameItemDelegate(QObject *parent) :
    QItemDelegate(parent)
{
}

void FrameItemDelegate::setEditorData(QWidget *editor, const QModelIndex &index) const {
    if(!index.isValid()) return;

    Item* item = static_cast<Item*>(index.internalPointer());
    if(!item) return;

    QSharedPointer<AnimationFrame> frame = item->block().staticCast<AnimationFrame>();
    if(index.column() == 0) {
        static_cast<QLineEdit*>(editor)->setText(frame->frame()->name());
    } else if(index.column() == 1) {
        static_cast<QSpinBox*>(editor)->setValue(frame->hold());
    }
}

void FrameItemDelegate::setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const {
    if(!index.isValid()) return;

    Item* item = static_cast<Item*>(index.internalPointer());
    if(!item) return;

    QSharedPointer<AnimationFrame> frame = item->block().staticCast<AnimationFrame>();
    if(index.column() == 1) {
        frame->setHold(static_cast<AnimationFrame::FrameHold>(
                           static_cast<QSpinBox*>(editor)->value()
                           ));
    }
}

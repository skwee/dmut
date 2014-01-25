#include "framelistwidget.h"

#include <QMessageBox>
#include <QDebug>

FrameListItem::FrameListItem(Frame *frame) :
    QListWidgetItem(frame->getPixmap(), frame->getName()), mFrame(frame)
{
    setFlags(Qt::ItemIsEditable | Qt::ItemIsEnabled | Qt::ItemIsSelectable);
    setToolTip(mFrame->getName());
}

void FrameListItem::setNameFromFrame() {
    setText(mFrame->getName());
    setToolTip(mFrame->getName());
}

void FrameListItem::setNameFromItem() {
    mFrame->setName(text());
}


FrameListWidget::FrameListWidget(QWidget *parent) :
    QListWidget(parent), mFrameSet(nullptr), mIgnoreDuplicateNameCheck(false)
{
    setViewMode(QListView::ListMode);
    setAcceptDrops(false);
    setUniformItemSizes(true);
    setEditTriggers(QAbstractItemView::SelectedClicked | QAbstractItemView::EditKeyPressed);

    QObject::connect(this, SIGNAL(itemChanged(QListWidgetItem*)),
                     this, SLOT(onItemChanged(QListWidgetItem*)));
}

void FrameListWidget::populate(const QString &spriteFileName, const Frame::Options& frameOptions) {
    if(mFrameSet != nullptr) delete mFrameSet;

    mFrameSet = new FrameSet(spriteFileName, frameOptions);
    unsigned int totalFrames = mFrameSet->totalItems();

    clear();
    for(unsigned int i = 0; i < totalFrames; ++i) {
        addItem(new FrameListItem(mFrameSet->frameAt(i)));
    }
    show();
}

void FrameListWidget::onItemChanged(QListWidgetItem *item) {
    if(item != nullptr) {
        FrameListItem* it = reinterpret_cast<FrameListItem*>(item);
        QString newName = it->text();
        if(newName.isEmpty()) {
            QMessageBox::warning(this, tr("Empty name"), tr("Frame name can not be empty"));
            mIgnoreDuplicateNameCheck = true;
            it->setNameFromFrame();
        } else if(!mIgnoreDuplicateNameCheck && !mFrameSet->isNameUnique(newName, it->getFrame())) {
            QMessageBox::warning(this, tr("Duplicate name"), tr("Frame with such name already exists"));
            mIgnoreDuplicateNameCheck = true;
            it->setNameFromFrame();
        } else {
            it->setNameFromItem();
            mIgnoreDuplicateNameCheck = false;
        }
    }
}

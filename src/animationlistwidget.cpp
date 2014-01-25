#include "animationlistwidget.h"

#include <QMessageBox>

unsigned int AnimationListItem::sIndex = 1;

AnimationListItem::AnimationListItem()
{
    setText(0, QString("Animation_%1").arg(sIndex++));
    mPreviousName = text(0);
    setFlags(Qt::ItemIsEditable | Qt::ItemIsEnabled | Qt::ItemIsSelectable);
}

void AnimationListItem::resetName() {
    setText(0, mPreviousName);
}

void AnimationListItem::updatePreviousName() {
    mPreviousName = text(0);
}


FrameAnimationListItem::FrameAnimationListItem(Frame *frame) :
    mFrame(frame)
{
    setText(0, mFrame->getName());
    setIcon(0, mFrame->getPixmap());
    setFlags(Qt::ItemIsDragEnabled | Qt::ItemIsDropEnabled | Qt::ItemIsEnabled | Qt::ItemIsSelectable);
}


AnimationListWidget::AnimationListWidget(QWidget *parent) :
    QTreeWidget(parent)
{
    setEditTriggers(QAbstractItemView::SelectedClicked | QAbstractItemView::EditKeyPressed);

    QObject::connect(this, SIGNAL(itemChanged(QTreeWidgetItem*,int)),
                     this, SLOT(onItemChanged(QTreeWidgetItem*,int)));
}

void AnimationListWidget::addNewAnimation() {
    addTopLevelItem(new AnimationListItem());
}

void AnimationListWidget::removeSelectedAnimations() {
    auto itms = selectedItems();
    for(auto it : itms) {
        delete it;
    }
}

void AnimationListWidget::onItemChanged(QTreeWidgetItem *item, int column) {
    if(item != nullptr) {
        AnimationListItem* it = reinterpret_cast<AnimationListItem*>(item);
        QString name = it->text(column);

        if(name.isEmpty()) {
            QMessageBox::warning(this, tr("Empty nam"), tr("Animation name can not be empty"));
            it->resetName();
        } else if(!isNameUnique(name, column, item)) {
            QMessageBox::warning(this, tr("Duplicate name"), tr("Animation with such name already exists"));
            it->resetName();
        } else {
            it->updatePreviousName();
        }
    }
}

bool AnimationListWidget::isNameUnique(const QString &name, int column, QTreeWidgetItem *ignore) {
    unsigned int total = topLevelItemCount();
    for(unsigned int i = 0 ; i < total; ++i) {
        auto it = topLevelItem(i);
        if(it == ignore) continue;
        if(it->text(column).compare(name) == 0) return false;
    }

    return true;
}

void AnimationListWidget::onFrameAdd(QListWidgetItem *item) {
    if(selectedItems().empty()) return;

    Frame* frame = reinterpret_cast<FrameListItem*>(item)->getFrame();

    QTreeWidgetItem* currentAnimation = selectedItems().at(0);

    unsigned int totalTop = topLevelItemCount();
    bool found = false;
    for(unsigned int i = 0; i < totalTop; ++i) {
        if(currentAnimation == topLevelItem(i)) {
            found = true;
            break;
        }
    }

    if(!found) {
        QMessageBox::warning(this, tr("Invalid animation"), tr("Frame can not be a child of another frame"));
        return;
    }

    unsigned int totalChildren = currentAnimation->childCount();
    for(unsigned int i = 0; i < totalChildren; ++i) {
        Frame* test = reinterpret_cast<FrameAnimationListItem*>(currentAnimation->child(i))->getFrame();
        if(test == frame) {
            QMessageBox::warning(this, tr("Already exists"), tr("This frame already present in this animation"));
            return;
        }
    }

    FrameAnimationListItem* it = new FrameAnimationListItem(frame);
    currentAnimation->addChild(it);
    currentAnimation->setExpanded(true);
}

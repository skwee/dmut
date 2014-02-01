#include <QMessageBox>

#include "animationlistframe.h"
#include "ui_animationlistframe.h"

AnimationListFrame::AnimationListFrame(QWidget *parent) :
    QFrame(parent), mUi(new Ui::AnimationListFrame), mAnimationModel(nullptr)
{
    mUi->setupUi(this);

    mAnimationModel = new AnimationModel(mUi->animationList);
    mUi->animationList->setModel(mAnimationModel);

    mUi->animationList->setAcceptDrops(false);
    mUi->animationList->setEditTriggers(QAbstractItemView::SelectedClicked | QAbstractItemView::EditKeyPressed);

    QObject::connect(
                mUi->animationList->selectionModel(), SIGNAL(selectionChanged(QItemSelection,QItemSelection)),
                this, SLOT(onAnimationSelectionChanged(QItemSelection,QItemSelection))
                );

    QObject::connect(
                mAnimationModel, SIGNAL(onNameChanged(Item::RenameResult)),
                this, SLOT(onAnimationNameChanged(Item::RenameResult))
                );

    QObject::connect(
                mAnimationModel, SIGNAL(frameAddFailedDuplicate()),
                this, SLOT(onAddedFrameIsDuplicate())
                );
}

AnimationListFrame::~AnimationListFrame()
{
    if(mAnimationModel) delete mAnimationModel;
    delete mUi;
}

void AnimationListFrame::setDisabled(bool disabled) {
    QFrame::setDisabled(disabled);
    updateButtonsState();
}

void AnimationListFrame::clear() {
    mAnimationModel->removeAll();
}

void AnimationListFrame::addFrame(Block::ptr frame) {
    const QItemSelection s = mUi->animationList->selectionModel()->selection();
    if((s.indexes().length() > 0) && (!s.indexes().first().parent().isValid()))
        mAnimationModel->addFrameToAnimation(s.indexes().first(), frame);
}

void AnimationListFrame::refresh() {
    emit mUi->animationList->dataChanged(QModelIndex(), QModelIndex());
}

void AnimationListFrame::updateButtonsState() {
    if(mUi->animationList->selectionModel()->selection().indexes().length() == 0)
        mUi->removeAnimationButton->setDisabled(true);
    else
        mUi->removeAnimationButton->setDisabled(false);
}

void AnimationListFrame::on_addAnimationButton_clicked() {
    mAnimationModel->addAnimation();
}

void AnimationListFrame::on_removeAnimationButton_clicked() {
    const QItemSelection s = mUi->animationList->selectionModel()->selection();
    if(s.indexes().length() > 0) {
        QModelIndex index = s.indexes().first();
        mAnimationModel->remove(index);
    }
}

void AnimationListFrame::onAnimationSelectionChanged(const QItemSelection &selected, const QItemSelection &deselected) {
    updateButtonsState();
}

void AnimationListFrame::onAnimationNameChanged(Item::RenameResult result) {
    switch(result) {
    case Item::RenameResult::Empty:
        QMessageBox::warning(this, tr("Name is empty"), tr("Animation name can not be empty"));
        break;
    case Item::RenameResult::TooLong:
        QMessageBox::warning(this, tr("Name too long"), tr(QString("Animation name can not be longer than %1 characters").arg(Item::MAX_NAME_LENGTH).toUtf8()));
        break;
    case Item::RenameResult::Duplicate:
        QMessageBox::warning(this, tr("Name already exists"), tr("Animation with such name already exists"));
        break;
    case Item::RenameResult::Ok:
    case Item::RenameResult::NotValid:
        break;
    }
}

void AnimationListFrame::onAddedFrameIsDuplicate() {
    QMessageBox::warning(this, tr("Duplicate frame"), tr("Failed to add frame to animation because this animation already contains that frame"));
}

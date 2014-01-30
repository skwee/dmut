#include <QMessageBox>

#include "animationlistframe.h"
#include "ui_animationlistframe.h"

AnimationListFrame::AnimationListFrame(QWidget *parent) :
    QFrame(parent), mUi(new Ui::AnimationListFrame), mAnimationModel(nullptr)
{
    mUi->setupUi(this);

    mAnimationModel = new AnimationModel(mUi->animationList);
    mUi->animationList->setModel(mAnimationModel);

    QObject::connect(
                mUi->animationList->selectionModel(), SIGNAL(selectionChanged(QItemSelection,QItemSelection)),
                this, SLOT(onAnimationSelectionChanged(QItemSelection,QItemSelection))
                );

    QObject::connect(
                mAnimationModel, SIGNAL(nameChangeAttempt(bool,Animation::Namer::NameValidity)),
                this, SLOT(onAnimationNameChanged(bool,Animation::Namer::NameValidity))
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

void AnimationListFrame::tryAddSprite(Frame * frame) {
    const QItemSelection s = mUi->animationList->selectionModel()->selection();
    if(s.indexes().length() > 0 && !s.indexes().first().parent().isValid()) {
        mAnimationModel->addFrameToAnimation(s.indexes().first(), frame);
    }
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
    if(s.indexes().length() > 0)
        mAnimationModel->removeAnimation(s.indexes().first());
}

void AnimationListFrame::onAnimationSelectionChanged(const QItemSelection &selected, const QItemSelection &deselected) {
    updateButtonsState();
}

void AnimationListFrame::onAnimationNameChanged(bool succeed, Animation::Namer::NameValidity reason) {
    if(!succeed) {
        switch(reason) {
        case Animation::Namer::NameValidity::Empty:
            QMessageBox::warning(this, tr("Name is empty"), tr("Animation name can not be empty"));
            break;
        case Animation::Namer::NameValidity::TooLong:
            QMessageBox::warning(this, tr("Name too long"), tr(QString("Animation name can not be longer than %1 characters").arg(Animation::Namer::MAX_LENGTH).toUtf8()));
            break;
        case Animation::Namer::NameValidity::Duplicate:
            QMessageBox::warning(this, tr("Name already exists"), tr("Animation with such name already exists"));
            break;
        case Animation::Namer::NameValidity::Valid:
            break;
        }
    }
}

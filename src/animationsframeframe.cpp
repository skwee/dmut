#include "animationsframeframe.h"
#include "ui_animationsframeframe.h"

AnimationsFrameFrame::AnimationsFrameFrame(QWidget *parent) :
    QFrame(parent),
    mUi(new Ui::AnimationsFrameFrame)
{
    mUi->setupUi(this);

    mModel = static_cast<AnimationModel*>(mUi->animationsList->model());

    QObject::connect(
                mUi->animationsList->selectionModel(), SIGNAL(selectionChanged(QItemSelection,QItemSelection)),
                this, SLOT(onAnimationSelected(QItemSelection,QItemSelection))
                );

    mUi->animationsRemoveButton->setDisabled(true);
}

AnimationsFrameFrame::~AnimationsFrameFrame()
{
    delete mUi;
}

void AnimationsFrameFrame::setDisabled(bool disabled) {
    mUi->animationsList->setDisabled(disabled);
    mUi->animationsAddButton->setDisabled(disabled);
    mUi->animationsFramesList->setDisabled(disabled);
}

void AnimationsFrameFrame::onFrameAboutToBeAdded(Frame::Ptr frame) {
    const QItemSelection s = mUi->animationsList->selectionModel()->selection();
    if(!s.indexes().isEmpty())
        mModel->addFrame(s.indexes().first(), frame);
}

void AnimationsFrameFrame::onAnimationSelected(const QItemSelection& current, const QItemSelection& previous) {
    mUi->animationsRemoveButton->setDisabled(current.indexes().isEmpty());
}

void AnimationsFrameFrame::on_animationsAddButton_clicked()
{
    mModel->addAnimation();
}

void AnimationsFrameFrame::on_animationsRemoveButton_clicked()
{
    const QItemSelection s = mUi->animationsList->selectionModel()->selection();
    if(!s.indexes().isEmpty())
        mModel->removeAnimation(s.indexes().first());
}


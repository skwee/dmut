#include "animationlistwidget.h"
#include "ui_animationlistwidget.h"
#include "textinputdialog.h"
#include "animation.h"

AnimationListWidget::AnimationListWidget(QWidget *parent) :
    QWidget(parent),
    mUi(new Ui::AnimationListWidget), mCurrentSelectedItem(nullptr)
{
    mUi->setupUi(this);
    mUi->removeAnimationButton->setDisabled(true);
}

AnimationListWidget::~AnimationListWidget()
{
    delete mUi;
}

void AnimationListWidget::on_addAnimationButton_clicked()
{
    TextInputDialog d;
    d.setWindowTitle("New Animation");
    if(d.exec() == QDialog::Accepted) {
        //@TODO make sure its not empty
        Animation* animation = new Animation(d.getText());
        mUi->animationsList->addItem(animation);
    }
}

void AnimationListWidget::on_removeAnimationButton_clicked()
{
    if(mCurrentSelectedItem != nullptr) {
        delete mCurrentSelectedItem;
        mCurrentSelectedItem = mUi->animationsList->currentItem();
        if(mCurrentSelectedItem == nullptr)
            mUi->removeAnimationButton->setDisabled(true);
    }
}

void AnimationListWidget::on_animationsList_currentItemChanged(QListWidgetItem *current, QListWidgetItem *previous)
{
    mUi->removeAnimationButton->setDisabled(false);
    mCurrentSelectedItem = current;
}

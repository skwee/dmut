#include "animationpreviewwidget.h"
#include "ui_animationpreviewwidget.h"

#include <QPixmapCache>

AnimationPreviewWidget::AnimationPreviewWidget(QWidget *parent) :
    QWidget(parent),
    mUi(new Ui::AnimationPreviewWidget), mAnimation(nullptr),
    mScene(nullptr), mTimer(nullptr), mAnimationState(AnimationState::STOPPED)
{
    mUi->setupUi(this);

    mScene = new QGraphicsScene(mUi->animationView);
    mUi->animationView->setScene(mScene);

    mTimer = new QTimer(this);
    QObject::connect(
                mTimer, SIGNAL(timeout()),
                this, SLOT(updateAnimation())
                );

    setDisabled(true);
}

AnimationPreviewWidget::~AnimationPreviewWidget()
{
    if(mScene) delete mScene;
    if(mTimer) {
        mTimer->stop();
        delete mTimer;
    }
    delete mUi;
}

void AnimationPreviewWidget::itemSelectionChanged(const QModelIndex &selected) {
    if(selected.isValid()) {
        Item* item = static_cast<Item*>(selected.internalPointer());
        if(item->type() == Item::Type::ANIMATION) {
            mAnimation = static_cast<Animation*>(item);
        } else if(item->type() == Item::Type::FRAME) {
            mAnimation = static_cast<Animation*>(item->parent());
        }

        if(mAnimation && mAnimation->children().length() > 0) {
            setDisabled(false);
            setActiveAnimation();
            return;
        }
    }

    mAnimation = nullptr;
    setDisabled(true);
}

void AnimationPreviewWidget::setActiveAnimation() {
    mUi->timeframeSlider->setRange(0, mAnimation->children().length() - 1);
    mUi->timeframeSlider->setValue(0);
}

void AnimationPreviewWidget::updateAnimation() {
    QList<Item*> children = mAnimation->children();

    int frameIndex = mUi->timeframeSlider->value();

    if(mAnimationState == AnimationState::START) {
        mAnimationState = AnimationState::RUNNING;
    } else if(mAnimationState == AnimationState::RUNNING) {
        frameIndex ++;
    }

    if(frameIndex >= children.length()) {
        if(mAnimation->getWrapMode() == Animation::WrapLoop) {
            setAnimationState(AnimationState::START);
        } else {
            setAnimationState(AnimationState::STOPPED);
        }
    } else {
        Frame* frame = static_cast<Frame*>(children.at(frameIndex));
        mUi->timeframeSlider->setValue(frameIndex);

        mTimer->start((mAnimation->spf() * 1000) * frame->getHold());
    }
}

void AnimationPreviewWidget::on_buttonPlayPause_clicked() {
    if((mAnimationState == AnimationState::RUNNING) || (mAnimationState == AnimationState::START)) {
        setAnimationState(AnimationState::PAUSED);
    } else if(mAnimationState == AnimationState::PAUSED) {
        setAnimationState(AnimationState::RUNNING);
    } else if(mAnimationState == AnimationState::STOPPED) {
        setAnimationState(AnimationState::START);
    }

    if((mAnimationState == AnimationState::RUNNING) || (mAnimationState == AnimationState::START))
        updateAnimation();
}

void AnimationPreviewWidget::on_buttonStop_clicked() {
    setAnimationState(AnimationState::STOPPED);
}

void AnimationPreviewWidget::setAnimationState(AnimationState state) {
    if(state == mAnimationState) return;

    switch(state) {
    case AnimationState::START:
        mUi->timeframeSlider->setValue(0);
        break;

    case AnimationState::STOPPED:
        mTimer->stop();
        mUi->timeframeSlider->setValue(0);
        break;

    case AnimationState::PAUSED:
        mTimer->stop();
        break;

    case AnimationState::RUNNING:
        break;
    }

    QString file;
    bool flag = false;
    if((state == AnimationState::RUNNING) || (state == AnimationState::START)) {
        file = ":/icons/control-pause.png";
        flag = true;
    } else if ((state == AnimationState::PAUSED) || ((state == AnimationState::STOPPED) && (state != mAnimationState))) {
        file = ":/icons/control.png";
        flag = true;
    }

    if(flag) {
        QPixmap pixmap;
        if(!QPixmapCache::find(file, &pixmap)) {
            pixmap.load(file);
            QPixmapCache::insert(file, pixmap);
        }
        mUi->buttonPlayPause->setIcon(QIcon(pixmap));
    }

    mAnimationState = state;
}

void AnimationPreviewWidget::on_timeframeSlider_valueChanged(int value) {
    Frame* frame = static_cast<Frame*>(mAnimation->children().at(value));
    Sprite* sprite = frame->getSprite();

    mScene->clear();

    if(sprite) {
        QPixmap pixmap = sprite->pixmap();
        QGraphicsPixmapItem* item = new QGraphicsPixmapItem();
        item->setPixmap(pixmap);
        item->setPos(0, 0);
        mScene->addItem(item);
    } else {
        //@TODO add empty item
    }
}

#include "animationpreviewwidget.h"
#include "ui_animationpreviewwidget.h"

#include <QPixmapCache>

AnimationPreviewWidget::AnimationPreviewWidget(QWidget *parent) :
    QWidget(parent),
    mUi(new Ui::AnimationPreviewWidget), mAnimation(nullptr),
    mScene(nullptr),
    mCurrentFrameIndex(0), mTimer(nullptr), mAnimationState(AnimationState::STOPPED)
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
    mCurrentFrameIndex ++;

    if(mCurrentFrameIndex >= children.length()) {
        if(mAnimation->getWrapMode() == Animation::WrapLoop) {
            mCurrentFrameIndex = -1;
            updateAnimation();
        } else {
            mTimer->stop();
            mAnimationState = AnimationState::STOPPED;
        }
    } else {
        mScene->clear();
        mUi->timeframeSlider->setValue(mCurrentFrameIndex);

        Frame* frame = static_cast<Frame*>(children.at(mCurrentFrameIndex));
        Sprite* sprite = frame->getSprite();
        if(sprite) {
            QPixmap pixmap = sprite->pixmap();
            QGraphicsPixmapItem* item = new QGraphicsPixmapItem();
            item->setPixmap(pixmap);
            item->setPos(0, 0);
            mScene->addItem(item);
        } else {
            //@TODO add empty item
        }

        mTimer->start(frame->getDuration() * 1000);
    }
}

void AnimationPreviewWidget::on_buttonPlayPause_clicked()
{
    if(mAnimationState == AnimationState::STOPPED) {
        setAnimationState(AnimationState::RUNNING);
        mCurrentFrameIndex = -1;
    } else if(mAnimationState == AnimationState::PAUSED) {
        setAnimationState(AnimationState::RUNNING);
    } else if(mAnimationState == AnimationState::RUNNING) {
        setAnimationState(AnimationState::PAUSED);
    }

    if(mAnimationState == AnimationState::RUNNING) updateAnimation();
}

void AnimationPreviewWidget::setAnimationState(AnimationState state) {
    if(state == mAnimationState) return;

    mAnimationState = state;

    QString file;
    if(state == AnimationState::RUNNING) {
        file = ":/icons/control.png";
    } else if (state == AnimationState::PAUSED) {
        file = ":/icons/control-pause.png";
    } else {
        return;
    }

    QPixmap pixmap;
    if(!QPixmapCache::find(file, &pixmap)) {
        pixmap.load(file);
        QPixmapCache::insert(file, pixmap);
    }

    mUi->buttonPlayPause->setIcon(QIcon(pixmap));
}

#ifndef ANIMATIONPREVIEWWIDGET_H
#define ANIMATIONPREVIEWWIDGET_H

#include <QWidget>
#include <QTimer>
#include <QGraphicsScene>

#include "animation.h"
#include "frame.h"

namespace Ui {
class AnimationPreviewWidget;
}

class AnimationPreviewWidget : public QWidget
{
    Q_OBJECT
public:
    enum class AnimationState {
        STOPPED,
        PAUSED,
        RUNNING
    };

    explicit AnimationPreviewWidget(QWidget *parent = 0);
    ~AnimationPreviewWidget();

public slots:
    void itemSelectionChanged(const QModelIndex& selected);

private slots:
    void updateAnimation();

    void on_buttonPlayPause_clicked();

private:
    void setActiveAnimation();

    void setAnimationState(AnimationState state);

    Ui::AnimationPreviewWidget *mUi;
    Animation* mAnimation;
    QGraphicsScene* mScene;
    int mCurrentFrameIndex;
    QTimer* mTimer;
    AnimationState mAnimationState;
};

#endif // ANIMATIONPREVIEWWIDGET_H

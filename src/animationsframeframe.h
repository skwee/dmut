#ifndef ANIMATIONSFRAMEFRAME_H
#define ANIMATIONSFRAMEFRAME_H

#include <QFrame>
#include <QItemSelection>

#include "animationmodel.h"

namespace Ui {
class AnimationsFrameFrame;
}

class AnimationsFrameFrame : public QFrame
{
    Q_OBJECT

public:
    explicit AnimationsFrameFrame(QWidget *parent = 0);
    ~AnimationsFrameFrame();

    void setDisabled(bool disabled);

public slots:
    void onFrameAboutToBeAdded(Frame::Ptr frame);

private slots:
    void onAnimationSelected(const QItemSelection& current, const QItemSelection& previous);
    void on_animationsAddButton_clicked();
    void on_animationsRemoveButton_clicked();

private:
    Ui::AnimationsFrameFrame *mUi;
    AnimationModel* mModel;
};

#endif // ANIMATIONSFRAMEFRAME_H

#ifndef ANIMATIONLISTFRAME_H
#define ANIMATIONLISTFRAME_H

#include <QFrame>
#include <QItemSelection>

#include "animationmodel.h"

namespace Ui {
class AnimationListFrame;
}

class AnimationListFrame : public QFrame
{
    Q_OBJECT

public:
    explicit AnimationListFrame(QWidget *parent = 0);
    ~AnimationListFrame();

    void setDisabled(bool disabled);

public slots:
    void tryAddSprite(Frame* frame);

private slots:
    void on_addAnimationButton_clicked();
    void on_removeAnimationButton_clicked();

    void onAnimationSelectionChanged(const QItemSelection &selected, const QItemSelection &deselected);
    void onAnimationNameChanged(Item::RenameResult result);

private:
    void updateButtonsState();

    Ui::AnimationListFrame *mUi;
    AnimationModel* mAnimationModel;
};

#endif // ANIMATIONLISTFRAME_H

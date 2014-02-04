#ifndef ANIMATIONLISTFRAME_H
#define ANIMATIONLISTFRAME_H

#include <QFrame>
#include <QItemSelection>
#include <QDataWidgetMapper>

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

    void clear();

public slots:
    void addFrame(Block::ptr frame);
    void refresh();

private slots:
    void on_addAnimationButton_clicked();
    void on_removeAnimationButton_clicked();

    void onAnimationSelectionChanged(const QItemSelection &selected, const QItemSelection &deselected);
    void onAnimationNameChanged(Item::RenameResult result);

    void onAddedFrameIsDuplicate();

    void on_moveUpButton_clicked();

    void on_moveDownButton_clicked();

private:
    void updateButtonsState();

    Ui::AnimationListFrame *mUi;
    AnimationModel* mAnimationModel;
    QDataWidgetMapper* mAnimationDataMapper;
    QDataWidgetMapper* mFrameDataMapper;
};

#endif // ANIMATIONLISTFRAME_H

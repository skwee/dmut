#ifndef ANIMATIONSFRAMELISTVIEW_H
#define ANIMATIONSFRAMELISTVIEW_H

#include <QListView>

#include "animationframemodel.h"
#include "animation.h"

class AnimationsFrameListView : public QListView
{
    Q_OBJECT
public:
    explicit AnimationsFrameListView(QWidget *parent = 0);
    ~AnimationsFrameListView();

private:
    AnimationFrameModel* mModel;
};

#endif // ANIMATIONSFRAMELISTVIEW_H

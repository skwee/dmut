#include "animationsframelistview.h"

AnimationsFrameListView::AnimationsFrameListView(QWidget *parent) :
    QListView(parent), mModel(nullptr)
{
    setViewMode(QListView::ListMode);
    setUniformItemSizes(true);

    mModel = new AnimationFrameModel(this);
    setModel(mModel);
    show();
}

AnimationsFrameListView::~AnimationsFrameListView() {
    if(mModel) delete mModel;
}

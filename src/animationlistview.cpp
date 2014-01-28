#include "animationlistview.h"

#include <QMessageBox>

AnimationListView::AnimationListView(QWidget *parent) :
    QListView(parent), mModel(nullptr)
{
    setViewMode(QListView::ListMode);
    setAcceptDrops(false);
    setUniformItemSizes(true);
    setEditTriggers(QAbstractItemView::SelectedClicked | QAbstractItemView::EditKeyPressed);

    mModel = new AnimationModel(this);

    QObject::connect(
                mModel, SIGNAL(invalidName(AnimationModel::InvalidNameReason)),
                this, SLOT(onInvalidName(AnimationModel::InvalidNameReason)));

    setModel(mModel);

    show();
}

AnimationListView::~AnimationListView() {
    if(mModel) delete mModel;
}

void AnimationListView::onInvalidName(AnimationModel::InvalidNameReason reason) {
    if(reason == AnimationModel::InvalidNameReason::Empty) {
        QMessageBox::warning(this, tr("Empty name"), tr("Animation name can not be empty"));
    } else if(reason == AnimationModel::InvalidNameReason::Duplicate) {
        QMessageBox::warning(this, tr("Duplicate name"), tr("Animation with such name already exists"));
    }
}

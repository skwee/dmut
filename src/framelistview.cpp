#include "framelistview.h"

#include <QMessageBox>

FrameListView::FrameListView(QWidget *parent) :
    QListView(parent), mModel(nullptr)
{
    setViewMode(QListView::ListMode);
    setAcceptDrops(false);
    setUniformItemSizes(true);
    setEditTriggers(QAbstractItemView::SelectedClicked | QAbstractItemView::EditKeyPressed);
}

FrameListView::~FrameListView() {
    if(mModel != nullptr) delete mModel;
}

void FrameListView::populate(const QString &spriteFileName, const Frame::Options& frameOptions) {
    if(mModel != nullptr) delete mModel;

    mModel = new FrameModel(new FrameSet(spriteFileName, frameOptions));

    QObject::connect(
                mModel, SIGNAL(invalidName(FrameModel::InvalidNameReason)),
                this, SLOT(onInvalidNameSet(FrameModel::InvalidNameReason)));

    setModel(mModel);

    show();
}

void FrameListView::onInvalidNameSet(FrameModel::InvalidNameReason reason) {
    if(reason == FrameModel::InvalidNameReason::Empty) {
        QMessageBox::warning(this, tr("Empty name"), tr("Frame name can not be empty"));
    } else if(reason == FrameModel::InvalidNameReason::Duplicate) {
        QMessageBox::warning(this, tr("Duplicate name"), tr("Frame with such name already exists"));
    }
}

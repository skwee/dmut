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
    if(mModel) delete mModel;
}

void FrameListView::createNewFrameList(const QString &spriteFileName, const Frame::Options& frameOptions) {
    if(mModel != nullptr) delete mModel;

    mModel = new FrameModel(frameOptions, this);

    QObject::connect(
                mModel, SIGNAL(invalidName(FrameModel::InvalidNameReason)),
                this, SLOT(onInvalidName(FrameModel::InvalidNameReason)));

    setModel(mModel);

    SpriteToFrameFactory sff(spriteFileName, frameOptions);
    for(unsigned int i = 0; i < sff.totalItems(); ++i) {
        mModel->addFrame(sff.at(i));
    }

    show();
}

void FrameListView::onInvalidName(FrameModel::InvalidNameReason reason) {
    if(reason == FrameModel::InvalidNameReason::Empty) {
        QMessageBox::warning(this, tr("Empty name"), tr("Frame name can not be empty"));
    } else if(reason == FrameModel::InvalidNameReason::Duplicate) {
        QMessageBox::warning(this, tr("Duplicate name"), tr("Frame with such name already exists"));
    }
}

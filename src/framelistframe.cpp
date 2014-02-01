#include "framelistframe.h"
#include "ui_framelistframe.h"

#include <QMessageBox>

FrameListFrame::FrameListFrame(QWidget *parent) :
    QFrame(parent), mUi(new Ui::FrameListFrame), mFrameModel(nullptr)
{
    mUi->setupUi(this);

    mFrameModel = new FrameModel(mUi->frameList);
    mUi->frameList->setModel(mFrameModel);

    mUi->frameList->setViewMode(QListView::ListMode);
    mUi->frameList->setAcceptDrops(false);
    mUi->frameList->setUniformItemSizes(true);
    mUi->frameList->setEditTriggers(QAbstractItemView::SelectedClicked | QAbstractItemView::EditKeyPressed);

    QObject::connect(
                mFrameModel, SIGNAL(onNameChange(Item::RenameResult)),
                this, SLOT(onNameChanged(Item::RenameResult))
                );

    QObject::connect(
                mUi->frameList, SIGNAL(doubleClicked(QModelIndex)),
                this, SLOT(onItemDoubleClicked(QModelIndex))
                );

    updateButtons();
}

FrameListFrame::~FrameListFrame()
{
    if(mFrameModel) delete mFrameModel;
    delete mUi;
}

void FrameListFrame::createSpriteList(const QString &spriteFileName, const Frame::Options &options) {
    mFrameModel->removeAll();

    SpriteFactory sf(spriteFileName, options);
    unsigned int total = sf.totalItems();
    Frame::Namer::initialize(total);

    for(unsigned int i = 0; i < total; ++i)
        mFrameModel->add(sf.at(i));
}

void FrameListFrame::updateButtons() {
    mUi->changeLayoutButton->setToolTip(
                mUi->frameList->viewMode() == QListView::ListMode
                ? tr("Switch to Icon View Mode")
                : tr("Switch to List View Mode")
                );
}

void FrameListFrame::on_changeLayoutButton_clicked()
{
    if(mUi->frameList->viewMode() == QListView::IconMode) {
        mUi->frameList->setViewMode(QListView::ListMode);
    } else {
        mUi->frameList->setViewMode(QListView::IconMode);
    }

    updateButtons();
}

void FrameListFrame::onNameChanged(Item::RenameResult result) {
    switch(result) {
    case Item::RenameResult::Empty:
        QMessageBox::warning(this, tr("Name is empty"), tr("Sprite name can not be empty"));
        break;
    case Item::RenameResult::TooLong:
        QMessageBox::warning(this, tr("Name too long"), tr(QString("Sprite name can not be longer than %1 characters").arg(Item::MAX_NAME_LENGTH).toUtf8()));
        break;
    case Item::RenameResult::Duplicate:
        QMessageBox::warning(this, tr("Name already exists"), tr("Sprite with such name already exists"));
        break;
    case Item::RenameResult::Ok:
        emit pleaseRefreshOtherElements();
        break;
    case Item::RenameResult::NotValid:
        break;
    }
}

void FrameListFrame::onItemDoubleClicked(const QModelIndex &index) {
    Block::ptr frame = mFrameModel->at(index);
    if(frame)
        emit addFrameToAnimation(frame);
}

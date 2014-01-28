#include "framelistframe.h"
#include "ui_framelistframe.h"

FrameListFrame::FrameListFrame(QWidget *parent) :
    QFrame(parent),
    mUi(new Ui::FrameListFrame)
{
    mUi->setupUi(this);
}

FrameListFrame::~FrameListFrame()
{
    delete mUi;
}

void FrameListFrame::setDisabled(bool disabled) {
    mUi->frameList->setDisabled(disabled);
    mUi->changeLayoutButton->setDisabled(disabled);
    updateButtons();
}

void FrameListFrame::createFrameList(const QString &spriteFileName, const Frame::Options &frameOptions) {
    mUi->frameList->createNewFrameList(spriteFileName, frameOptions);
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

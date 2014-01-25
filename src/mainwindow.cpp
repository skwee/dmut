#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QFileDialog>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    mUi(new Ui::MainWindow)
{
    mUi->setupUi(this);
    mUi->frameList->setDisabled(true);
    mUi->frameListOptsChangeViewTypeButton->setDisabled(true);
    mUi->animationsTree->setDisabled(true);
    mUi->animationAddButton->setDisabled(true);
    mUi->animationRemoveButton->setDisabled(true);

    updateOptsChangeButton();

    QObject::connect(mUi->frameList, SIGNAL(itemDoubleClicked(QListWidgetItem*)),
                     mUi->animationsTree, SLOT(onFrameAdd(QListWidgetItem*)));
}

MainWindow::~MainWindow()
{
    delete mUi;
}

void MainWindow::on_actionQuit_triggered()
{
    this->close();
}

void MainWindow::on_actionNew_triggered()
{
    auto file = QFileDialog::getOpenFileName(
                this,
                tr("Open sprite file"),
                QDir::homePath(),
                tr("Images (*.png)")
                );

    QFileInfo fileInfo(file);

    if(!fileInfo.exists()) return;

    NewCharacterDialog ncDialog(this, fileInfo.baseName());
    auto ret = ncDialog.exec();
    if(ret == QDialog::Accepted) {
        startNewSession(file, ncDialog.getCharacterFrameOptions());
    } else if(ret == QDialog::Rejected) {
        return;
    }
}

void MainWindow::startNewSession(const QString &spriteFileName, const Frame::Options &frameOptions) {
    mUi->frameList->setDisabled(false);
    mUi->frameListOptsChangeViewTypeButton->setDisabled(false);

    mUi->animationsTree->setDisabled(false);
    mUi->animationAddButton->setDisabled(false);

    mUi->frameList->populate(spriteFileName, frameOptions);
}

void MainWindow::on_frameListOptsChangeViewTypeButton_clicked()
{
    if(mUi->frameList->viewMode() == QListView::IconMode) {
        mUi->frameList->setViewMode(QListView::ListMode);
    } else {
        mUi->frameList->setViewMode(QListView::IconMode);
    }

    updateOptsChangeButton();
}

void MainWindow::updateOptsChangeButton() {
    mUi->frameListOptsChangeViewTypeButton->setToolTip(
                mUi->frameList->viewMode() == QListView::ListMode
                ? tr("Switch to Icon Mode")
                : tr("Switch to List Mode")
                  );
}

void MainWindow::on_animationAddButton_clicked()
{
    mUi->animationsTree->addNewAnimation();
}

void MainWindow::on_animationsTree_itemSelectionChanged()
{
    mUi->animationRemoveButton->setEnabled(!mUi->animationsTree->selectedItems().empty());
}

void MainWindow::on_animationRemoveButton_clicked()
{
    mUi->animationsTree->removeSelectedAnimations();
}

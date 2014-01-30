#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QFileDialog>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    mUi(new Ui::MainWindow)
{
    mUi->setupUi(this);

    mUi->frameListFrame->setDisabled(true);
    mUi->animationListFrame->setDisabled(true);

    mUi->splitter->setStretchFactor(0, 1);
    mUi->splitter->setStretchFactor(1, 2);

    QObject::connect(
                mUi->frameListFrame, SIGNAL(spriteToBeAddedToAnimation(Frame*)),
                mUi->animationListFrame, SLOT(tryAddSprite(Frame*))
                );
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
        startNewSession(file, ncDialog.getCharacterSpriteOptions());
    } else if(ret == QDialog::Rejected) {
        return;
    }
}

void MainWindow::startNewSession(const QString &spriteFileName, const Frame::Options &frameOptions) {
    mUi->frameListFrame->createSpriteList(spriteFileName, frameOptions);

    mUi->frameListFrame->setDisabled(false);
    mUi->animationListFrame->setDisabled(false);
}

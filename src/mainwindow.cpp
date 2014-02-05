#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QFileDialog>

#include "newcharacterdialog.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    mUi(new Ui::MainWindow)
{
    mUi->setupUi(this);

    mUi->spriteAtlas->setDisabled(true);
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

    NewCharacterDialog nc(fileInfo.baseName(), this);
    auto ret = nc.exec();
    if(ret == QDialog::Accepted) {
        startNewSession(file, nc.getSpriteSize());
    } else {
        return;
    }
}

void MainWindow::startNewSession(const QString &fileName, const Sprite::Size &size) {
    mUi->spriteAtlas->setAtlas(fileName, size);
    mUi->spriteAtlas->setDisabled(false);
}

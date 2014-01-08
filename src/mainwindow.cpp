#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QFileDialog>
#include <QGraphicsView>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow), m_CharacterScene(nullptr)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
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
        NewCharacterDialog::NewCharacterCreationData newCharacterData = ncDialog.getCharacterCreationData();
        startNewSession(file, newCharacterData);
    } else if(ret == QDialog::Rejected) {
        return;
    }
}

void MainWindow::startNewSession(const QString &file, NewCharacterDialog::NewCharacterCreationData &characterCreationData) {
    if(m_CharacterScene == nullptr) {
        m_CharacterScene = new QGraphicsScene;
        ui->characterView->setScene(m_CharacterScene);
    }

    m_CharacterScene->clear();
    m_CharacterScene->addPixmap(QPixmap(file));

    ui->characterView->show();
}

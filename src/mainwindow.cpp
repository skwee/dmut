#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QFileDialog>

#include "newcharacterdialog.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    mUi(new Ui::MainWindow), mCharacterDocument(nullptr)
{
    mUi->setupUi(this);
}

MainWindow::~MainWindow()
{
    if(mCharacterDocument) delete mCharacterDocument;
    delete mUi;
}

void MainWindow::on_actionQuit_triggered()
{
    this->close();
}

void MainWindow::on_actionNew_triggered()
{
    finishSession();
    mCharacterDocument = CharacterDocument::create(this);
    startSession();
}

void MainWindow::finishSession() {
    mUi->characterHierarchy->finishSession();
    mUi->itemProperties->finishSession();
    if(mCharacterDocument) delete mCharacterDocument;
}

void MainWindow::startSession() {
    if(mCharacterDocument) {
        mUi->characterHierarchy->startSession(mCharacterDocument);
        mUi->itemProperties->startSession(mCharacterDocument);

        QObject::connect(
                    mCharacterDocument, SIGNAL(onItemSelectionChanged(QModelIndex,QModelIndex)),
                    mUi->itemProperties, SLOT(itemSelectionChanged(QModelIndex,QModelIndex))
                    );

        QObject::connect(
                    mCharacterDocument, SIGNAL(onModelChanged()),
                    this, SLOT(dataChanged())
                    );
    }
}

void MainWindow::dataChanged() {
    mUi->itemProperties->itemSelectionChanged(mUi->characterHierarchy->currentSelectedIndex(), QModelIndex());
}

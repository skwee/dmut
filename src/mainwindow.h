#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QListWidgetItem>

#include "characterdocument.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_actionQuit_triggered();
    void on_actionNew_triggered();

private:
    void finishSession();
    void startSession();

    Ui::MainWindow *mUi;
    CharacterDocument* mCharacterDocument;
};

#endif // MAINWINDOW_H

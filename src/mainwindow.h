#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "newcharacterdialog.h"

#include <QMainWindow>
#include <QGraphicsScene>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    void startNewSession(const QString &file, NewCharacterDialog::NewCharacterCreationData &characterCreationData);

private slots:
    void on_actionQuit_triggered();

    void on_actionNew_triggered();

private:
    Ui::MainWindow *ui;
    QGraphicsScene *m_CharacterScene;
};

#endif // MAINWINDOW_H

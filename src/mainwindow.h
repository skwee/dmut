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

private slots:
    void on_actionQuit_triggered();
    void on_actionNew_triggered();

private:
    Ui::MainWindow *mUi;
};

#endif // MAINWINDOW_H

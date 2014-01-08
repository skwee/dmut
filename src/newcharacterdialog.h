#ifndef NEWCHARACTERDIALOG_H
#define NEWCHARACTERDIALOG_H

#include <QDialog>

namespace Ui {
class NewCharacterDialog;
}

class NewCharacterDialog : public QDialog
{
    Q_OBJECT

public:
    typedef struct {
        QString name;
        struct {
            unsigned int w;
            unsigned int h;
        }frame;
        struct {
            unsigned int x;
            unsigned int y;
        }margin;
        struct {
            unsigned int x;
            unsigned int y;
        }spacing;
    }NewCharacterCreationData;

public:
    explicit NewCharacterDialog(QWidget *parent, const QString &characterName);
    ~NewCharacterDialog();

    NewCharacterCreationData getCharacterCreationData() const;

private:
    Ui::NewCharacterDialog *ui;
};

#endif // NEWCHARACTERDIALOG_H

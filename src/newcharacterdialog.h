#ifndef NEWCHARACTERDIALOG_H
#define NEWCHARACTERDIALOG_H

#include <QDialog>

#include "spriteatlasmodel.h"

namespace Ui {
class NewCharacterDialog;
}

class NewCharacterDialog : public QDialog
{
    Q_OBJECT

public:
    explicit NewCharacterDialog(const QString& characterName, QWidget *parent = 0);
    ~NewCharacterDialog();

    QString getCharacterName() const;
    Sprite::Size getFrameSize() const;

private:
    Ui::NewCharacterDialog *mUi;
};

#endif // NEWCHARACTERDIALOG_H

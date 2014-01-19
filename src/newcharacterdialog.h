#ifndef NEWCHARACTERDIALOG_H
#define NEWCHARACTERDIALOG_H

#include <QDialog>
#include "dmut.h"

namespace Ui {
class NewCharacterDialog;
}

class NewCharacterDialog : public QDialog
{
    Q_OBJECT

public:
    explicit NewCharacterDialog(QWidget *parent, const QString &characterName);
    ~NewCharacterDialog();

    Dmut::Data getCharacterCreationData() const;

private:
    Ui::NewCharacterDialog *mUi;
};

#endif // NEWCHARACTERDIALOG_H

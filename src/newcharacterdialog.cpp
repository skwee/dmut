#include "newcharacterdialog.h"
#include "ui_newcharacterdialog.h"

NewCharacterDialog::NewCharacterDialog(QWidget *parent, const QString &characterName) :
    QDialog(parent),
    mUi(new Ui::NewCharacterDialog)
{
    mUi->setupUi(this);
    mUi->characterNameEdit->setText(characterName);
}

NewCharacterDialog::~NewCharacterDialog()
{
    delete mUi;
}

Dmut::Data NewCharacterDialog::getCharacterCreationData() const {
    Dmut::Data d;

    d.name = mUi->characterNameEdit->text();
    d.frame.w = mUi->frameWidthBox->value();
    d.frame.h = mUi->frameHeightBox->value();

    return d;
}

#include "newcharacterdialog.h"
#include "ui_newcharacterdialog.h"

NewCharacterDialog::NewCharacterDialog(const QString& characterName, QWidget *parent) :
    QDialog(parent),
    mUi(new Ui::NewCharacterDialog)
{
    mUi->setupUi(this);
    mUi->nameLineEdit->setText(characterName);
}

NewCharacterDialog::~NewCharacterDialog()
{
    delete mUi;
}

QString NewCharacterDialog::getCharacterName() const {
    return mUi->nameLineEdit->text();
}

Sprite::Size NewCharacterDialog::getFrameSize() const {
    Sprite::Size s;
    s.width = mUi->frameSizeWidthSpinBox->value();
    s.height = mUi->frameSizeHeightSpinBox->value();

    return s;
}
